#include "lib.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <type_traits>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>

using Ip = std::vector<unsigned char>;

template<typename T>
inline constexpr bool is_integral_v = std::is_integral<T>::value;

template<bool B, typename T>
using enable_if_t = typename std::enable_if<B, T>::type;

template <typename T>
struct is_string {
    static const bool value = false;
};

template<>
struct is_string<std::string> {
    static const bool value = true;
};

template<typename T>
inline constexpr bool is_string_v = is_string<T>::value;

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
void printIp(enable_if_t<is_integral_v<T>, T> rawIp) {
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

template<typename T>
void printIp(enable_if_t<is_string_v<T>, T> strIp) {
    std::cout << strIp << std::endl;
}

template<typename T>
void printIp(enable_if_t<is_container_v<T>, T> cntIp) {
    auto last = --cntIp.end();
    for(auto i = cntIp.begin(); i != cntIp.end(); ++i) {
        std::cout << *i;
        if (i != last) {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    char ip1 = -1;
    printIp<char>(ip1);
    short ip2 = 0;
    printIp<short>(ip2);
    int ip3 = 2130706433;
    printIp<int>(ip3);
    long ip4 = 8875824491850138409;
    printIp<long>(ip4);
    auto ip5 = std::string("127.0.0.1");
    printIp<std::string>(ip5);
    auto ip6 = std::vector<int>{12,12,12,12};
    printIp<decltype(ip6)>(ip6);
    auto ip7 = std::list<int>{13,13,13,13};
    printIp<decltype(ip7)>(ip7);
    return 0;
}
