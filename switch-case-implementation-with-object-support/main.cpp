#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <class Type, class FunctionType, class... FunctionArgs>
class Cases
{
public:
    Cases() = default;
    Cases(Type value, FunctionType function_to_call, bool is_break, FunctionArgs... args)
        : case_value{value}, function_to_call{function_to_call}, is_break_exist{is_break}, function_arguments_to_supply{std::make_tuple(args...)}
    {
    }

    const Type& get_case_value() const
    {
        return case_value;
    }

    void call_function()
    {
        std::apply(function_to_call, function_arguments_to_supply);
    }

    bool is_break() const
    {
        return is_break_exist;
    }
private:
    Type case_value;
    FunctionType function_to_call;
    bool is_break_exist;
    std::tuple<FunctionArgs...> function_arguments_to_supply;
};

template<class Type, class CurrentCase>
void switch_for_classes(Type data,
                        std::function<bool(Type left, Type right)> equality_function,
                        CurrentCase last_case)
{
    if (equality_function(data, last_case.get_case_value())) {
        last_case.call_function();
    }
}

template<class Type, class CurrentCase, class... CaseList>
void switch_for_classes(Type data,
                        std::function<bool(Type left, Type right)> equality_function,
                        CurrentCase current_case,
                        CaseList... cases)
{
    if (equality_function(data, current_case.get_case_value())) {
        current_case.call_function();
        if (!current_case.is_break()) {
            switch_for_classes<Type>(data, equality_function, cases...);
        }
    } else {
        switch_for_classes<Type>(data, equality_function, cases...);
    }
}

int main()
{
    Cases s{1, []() { std::cout << "You found me!\n"; }, false};

    // false means there is no break given at the end of a case
    switch_for_classes<int>(1,
        [](int a, int b) { return a == b; },
        Cases{1, []() { std::cout << "Yay\n"; }, false},
        Cases{2, []() { std::cout << "Hello There\n"; }, false},
        Cases{1, [](int a, int b) { std::cout << a + b << '\n'; }, false, 1, 2});

    return 0;
}
