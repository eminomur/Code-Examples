// Author:
// Muhammed Emin ÖMÜR
#include <iostream>

// Template metaprogramming square root
// Here, since there is a risk of overflow (compiler gave me warnings again and again),
// every int value is converted to long (this will most probably lead to inefficient program)
template<long number, long start, long end, bool can_continue = true>
struct BinarySearchFloorSqrt
{
    static const long result = (number >= 0) ? (number >= 2) ? BinarySearchFloorSqrt<number,
                                                                            ((((start + end) / 2) * ((start + end) / 2)) >= number) ? start : ((start + end) / 2) + 1,
                                                                            ((((start + end) / 2) * ((start + end) / 2)) > number) ? ((start + end) / 2) - 1 : end,
                                                                            ((((start + end) / 2) * ((start + end) / 2)) != number && start <= end) ? true : false>::result : number : -1;
};

template<long number, long start, long end>
struct BinarySearchFloorSqrt<number, start, end, false>
{
    static const long result = (start + end) / 2;
};
//

// Template metaprogramming modulo
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
//

// Important part is here
// Code is self-explanaory I guess
// First argument is value itself, second argument is divisor (inceremented by 1), third argument is square root of number itself
// and finally final argument is used for choosing destiny of recursion
// If value returned from Modulo is 0 or divisor exceeded upper_bound it will become false (base condition)
// otherwise recursion will continue working
template<int number, int divisor, int upper_bound, bool can_continue = true>
struct CheckForPrime
{
    static const bool result = (number < 3) ? (number == 2) ? true : false              // This line checks if number is less than 3 and if the number is equal to 2 then it is prime number, otherwise it is not prime number
                                            : CheckForPrime<number, divisor + 1, upper_bound, ((Modulo<number, divisor>::remainder == 0) || (divisor > upper_bound)) ? false : true>::result;
};

template<int number, int divisor, int upper_bound>
struct CheckForPrime<number, divisor, upper_bound, false>
{
    static const bool result = (divisor > upper_bound) ? true : false;
};

int main()
{
    const int n = 104743;
    std::cout << BinarySearchFloorSqrt<n, 0, n - 1>::result << '\n';
    std::cout << ((CheckForPrime<n, 2, BinarySearchFloorSqrt<n, 0, n - 1>::result>::result) ? "True" : "False") << '\n';
    return 0;
}
