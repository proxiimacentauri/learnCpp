# Fundamental Types

- ## Variable Declarations
    - Variables of fundamental types are **NOT** initialized by default.
    - In C++ *'you only pay for what you use'*. (Init. of large memory blocks can be very expensive.)
    - Always init. variables when delcaring them, to prevent bugs.

        ![](var_declaration.png)

- ## Overview
    ![](bool_char.png)
    ![](int.png)
    ![](float.png)

- ## Memory Sizes of Fundamental Types
    ![](mem_size.png)

- ## Type System
    - ### `const`
        ![](const.png)

    - ### `using`
        ![](using.png)

    - ### `auto`
        ![](auto.png)

    - ### `constexpr`
        - When you define something as `constexpr`, you're indicating to the *compiler that it should be able to compute the value of that expression or function at compile time*, rather than at runtime.
        ![](constexpr.png)


- ## Arithmatic Operations
    ![](arithmatic.png)

- ## Increment/Decrement
    ![](inc_dec.png)

- ## Boolean Logic
    ![](bool_logic.png)

- ## Comparisons
    ![](cmp.png)

- ## `std::numeric_limits<type>`
    ```cpp
    #include <iostream>
    #include <limits>

    int main ()
    {
        // smallest negative value:
        std::cout << "lowest:  " <<
        std::numeric_limits<double>::lowest() << '\n';
        
        // float/double: smallest value > 0
        // integers: smallest value
        std::cout << "min:     " <<
        std::numeric_limits<double>::min() << '\n';

        // largest positive value:
        std::cout << "max:     " <<
        std::numeric_limits<double>::max() << '\n';

        // smallest difference btw. 1 and next value:
        std::cout << "epsilon: " <<
        std::numeric_limits<double>::epsilon() << '\n';

        return 0;
    }
    ```
    ![](num_limits.png)

- ## Type Narrowing
    ![](type_narrow.png)

- ## Bitwise Operations
    ![](bit_logic.png)
    ![](bit_shift.png)

## References
`https://hackingcpp.com/cpp/lang/fundamental_types.html`
`https://hackingcpp.com/cpp/lang/type_system_basics.html`