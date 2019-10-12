// Author:
// Muhammed Emin ÖMÜR
#include <iostream>

// Magic happens here
// x and y values are assumed positive values
template<int x, int y, bool can_continue = true>
struct Modulo
{
    static const int remainder = (x >= y) ? Modulo<x - y, y, (x >= y) ? true : false>::remainder : x;
};

template<int x, int y>
struct Modulo<x, y, false>
{
    static const int remainder = x;
};

int main()
{
    std::cout << Modulo<5, 2>::remainder << '\n'
              << Modulo<10, 1>::remainder << '\n'
              << Modulo<2, 5>::remainder << '\n';
    return 0;
}
