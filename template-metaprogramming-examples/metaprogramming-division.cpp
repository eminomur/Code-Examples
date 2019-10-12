// Author:
// Muhammed Emin ÖMÜR
#include <iostream>
#include <climits>

// This part is about template metaprogramming
template<int dividend, int divisor, bool is_dividable = true>
struct Division
{
    static const int result = (dividend >= divisor) ? Division<dividend - divisor, divisor, (dividend >= divisor) ? true : false>::result + 1 : 0;
};

template<int dividend, int divisor>
struct Division<dividend, divisor, false>
{
    static const int result = 0;
};

template<int dividend, bool is_dividable>
struct Division<dividend, 0, is_dividable>
{
    static const int result = INT_MIN;
};

typedef Division<50, 10> typedef_version;
using using_version = Division<1, 0>;

int main()
{
    std::cout << Division<0, 10>::result << '\n';
    std::cout << typedef_version::result << '\n';
    std::cout << using_version::result << '\n';
    
    return 0;
}
