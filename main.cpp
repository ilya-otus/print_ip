#include "print_ip.h"

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
    printIp(ip5);
    auto ip6 = std::vector<int>{12, 12, 12, 12};
    printIp<decltype(ip6)>(ip6);
    auto ip7 = std::list<int>{13, 13, 13, 13};
    printIp<decltype(ip7)>(ip7);
    printIp(std::make_tuple(-1,15,15,15,1112143145));
    return 0;
}
