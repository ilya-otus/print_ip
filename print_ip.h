#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>

/*!
    \brief metafunction which unite boolean metafunctions.
    This implementation grabbed from latest STL
*/
template<typename...>
struct conjunction : std::true_type {};

template<typename B1>
struct conjunction<B1> : B1 {};

template<typename B1, typename... Bn>
struct conjunction<B1, Bn...> : std::conditional<bool(B1::value), conjunction<Bn...>, B1>::type {};

/*!
    \brief metafunction which detect containers std::list
    and std::vector
    \param T checked type
    \return value false in all cases except specializations
*/
template<typename T>
struct is_container {
    static const bool value = false;
};

/*!
    \brief is_container specialization for and std::vector
    \param T checked type
    \return value true for std::vector
*/
template<typename T, typename A>
struct is_container<std::vector<T, A>> {
    static const bool value = true;
};

/*!
    \brief is_container specialization for and std::list
    \param T checked type
    \return value true for std::list
*/
template<typename T, typename A>
struct is_container<std::list<T, A>> {
    static const bool value = true;
};

/*!
    \brief is_container<T>::value alias
    \param T checked type
*/
template<typename T>
inline constexpr bool is_container_v = is_container<T>::value;

/*!
    \brief function which prints ip address for different
    types. Default implementation do nothing
*/
template<typename T>
void printIp(T) {
    return;
}

/*!
    \brief function which prints ip address represented
    as integral type by octets.
    \param rawIp integral representation of IP address
    separates by octets and prints to stdout.
*/
template<typename T>
void printIp(typename std::enable_if<std::is_integral<T>::value, T>::type rawIp) {
    const size_t typeSize = sizeof(T);
    const int mask = 255;
    for(int i = typeSize - 1; i >= 0; --i) {
        int a = (rawIp >> i * 8) & mask;
        std::cout << a;
        if (i != 0) {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
}

/*!
    \brief function which prints ip address represented
    as std::string as is
    \param strIp string representation of IP address.
*/
template<>
void printIp(std::string strIp) {
    std::cout << strIp << std::endl;
}

/*!
    \brief function which prints ip address represented
    as container item by item
    \param std::vector or std::list representation
    of IP address.
*/
template<typename T>
void printIp(typename std::enable_if<is_container<T>::value, T>::type cntIp) {
    auto last = --cntIp.end();
    for(auto i = cntIp.begin(); i != cntIp.end(); ++i) {
        std::cout << *i;
        if (i != last) {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
}

/*!
    \brief function which prints std::tuple item by
    item recursively. There is general implementation.
    \param std::tuple
*/
template<typename T, size_t N>
struct PrintTuple {
static void print(T t) {
    PrintTuple<T, N-1>::print(t);
    std::cout << "." << std::get<N-1>(t);
}
};

/*!
    \brief function which prints std::tuple item by
    item recursively. There is specialization for the
    last item in the tuple.
    \param std::tuple
*/
template<typename T>
struct PrintTuple<T, 1> {
static void print(T t) {
    std::cout << std::get<0>(t);
}
};

/*!
    \brief function which prints ip address represented
    as std::tuple. This function throws static_assert
    when types inside the tuple aren't equal
    \param std::tuple with equal types which represent
    IP address.
*/
template<typename T, typename... Ts>
void printIp(std::tuple<T, Ts...> tplIp) {
    static_assert(conjunction<std::is_same<T, Ts>...>::value, "Types inside a tuple aren't equal!");
    PrintTuple<decltype(tplIp), std::tuple_size<decltype(tplIp)>::value>::print(tplIp);
    std::cout << std::endl;
}

