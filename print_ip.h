#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>

template<typename T>
struct is_container {
    static const bool value = false;
};

template<typename T, typename A>
struct is_container<std::vector<T, A>> {
    static const bool value = true;
};

template<typename T, typename A>
struct is_container<std::list<T, A>> {
    static const bool value = true;
};

template<typename T>
inline constexpr bool is_container_v = is_container<T>::value;

template<typename T>
void printIp(T ip) {
    return;
}

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

template<>
void printIp(std::string strIp) {
    std::cout << strIp << std::endl;
}

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

template<typename T, size_t N>
struct PrintTuple {
static void print(T t) {
    PrintTuple<T, N-1>::print(t);
    std::cout << "." << std::get<N-1>(t);
}
};

template<typename T>
struct PrintTuple<T, 1> {
static void print(T t) {
    std::cout << std::get<0>(t);
}
};

template<typename T, typename... Ts>
typename std::enable_if<std::conjunction<std::is_same<T, Ts>...>::value>::type printIp(std::tuple<T, Ts...> tplIp) {
    PrintTuple<decltype(tplIp), std::tuple_size<decltype(tplIp)>::value>::print(tplIp);
    std::cout << std::endl;
}

