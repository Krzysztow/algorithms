#include <iostream>

int bitModNo(unsigned int from, unsigned int to) {
    unsigned int flag = 0x01;
    unsigned int mask = 0x00 | flag;

    if (0 == from && 0 == to)
        return 0;

    int bitsToMod = 0;
    while (true) {
        if ((flag & from) != (flag & to)) {
            ++bitsToMod;
        }

        if ( (mask & from) == from &&
                (mask & to) == to )
            break;

        flag <<= 1;
        mask |= flag;
    }

    return bitsToMod;
}

int bitModNo2(unsigned int from, unsigned int to) {
    unsigned int xord = from ^ to;//right rotation - keep in mind to make it unsigned - otherwise 1 at the beginning may occur
    int retNo = 0;

    while (0 != xord) {
        if (0x01 & xord)
            ++retNo;

        xord >>= 1;
    }

    return retNo;
}

int main(int argc, const char *argv[]) {
    unsigned int first;
    unsigned int second;

    std::cout << "Input 1st number " << std::endl;
    std::cin >> first;

    std::cout << "Input 2nd number" << std::endl;
    std::cin >> second;

    std::cout << "\"Binary modification\" requires " << bitModNo(first, second) << " steps" << std::endl;
    std::cout << "\"Binary modification\" requires " << bitModNo2(first, second) << " steps" << std::endl;

    return 0;
}
