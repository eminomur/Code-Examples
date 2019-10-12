// Author:
// Muhammed Emin ÖMÜR
#include <iostream>

// This template calculates approximate integer square root of given integer.
// There are two ternary operators outside of template:
//  1) First ternary operator checks if number is positive.
//  2) Second ternary operator checks if number is greator than or equal to two.
// There are three ternary operators inside of BinarySearchFloorSqrt<...> and 4 arguments.
//  1) Original number.
//  2 - 3) Decides values for start and end arguments (This approach alike binary search as you can see).
//  4) Final argument is used to check for exit conditions (If square root is found or if start value exceeded end value.
// Finally, there may be some other ways to make this template look prettier but I preferred using this approach (at least for now).
// If you have any suggestions feel please tell me so that I can improve this solution.
template<int number, int start, int end, bool can_continue = true>
struct BinarySearchFloorSqrt
{
    static const int result = (number >= 0) ? (number >= 2) ? BinarySearchFloorSqrt<number,
                                                                            ((((start + end) / 2) * ((start + end) / 2)) >= number) ? start : ((start + end) / 2) + 1,
                                                                            ((((start + end) / 2) * ((start + end) / 2)) > number) ? ((start + end) / 2) - 1 : end,
                                                                            ((((start + end) / 2) * ((start + end) / 2)) != number && start <= end) ? true : false>::result : number : -1;
};

template<int number, int start, int end>
struct BinarySearchFloorSqrt<number, start, end, false>
{
    static const int result = (start + end) / 2;
};

int main()
{
    const int n = 104743;
    std::cout << BinarySearchFloorSqrt<n, 0, n - 1>::result << '\n';
    return 0;
}
