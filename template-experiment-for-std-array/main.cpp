#include <iostream>
#include <array>
#include <algorithm>

void foo(std::array<int,11>& arr)
{
    std::cout << "foo:\n";
//     std::cout << sizeof (arr) / sizeof (int) << '\n';
    std::cout << arr.size() << '\n';
}

template<class T>
typename std::enable_if<std::is_same<T, std::array<typename std::remove_pointer<decltype (T().data())>::type, T().size()>>::value, void>::type
bar(T arr)
{
    std::cout << "bar:\n";
    std::cout << arr.size() << '\n';
}

int main()
{
    std::array<int, 11> arr {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    foo(arr);
    bar(arr);

    return 0;
}
