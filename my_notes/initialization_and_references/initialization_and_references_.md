# Initialization and References

## Reference
*A reference is an alias to an already-existing thing. (use: &)*
```cpp
int num = 5;
int& refToNum = num;
std::cout<< "Num: " << num << std::endl ;   // 5
refToNum = 10;                // Assign a new value by reference 
std::cout<< "Num: " << num << std::endl ;   // 10
```
- ## L-Value and R-Value
    - **L-Value**: It can be to the left **OR** right of an equal sign.
        ```cpp
        int y = 9;  // y is an L value
        int x;

        x = y; //  allowed   can be also on right
        ```

    - **R-Value**: It can be ONLY to the right of an equal sign.
        ```cpp
        int y = 9; // 9 is an R value
        int x;

        89 = x; // Not allowed, cant be on the left
        ```

    - **Pain of L & R Value**:
        - We can NOT pass `R-Value` by reference unless we change the function.
            ```cpp
            int squareN(int& num)           // Accepting references only
            {
                return std::pow(num, 2);
            }

            int main()
            {
                int lValue = 2;
                auto four = squareN(lValue); // This will work since lValue is an l-value.
                auto fourAgain = squareN(2); // This will not compile, as 2 is an r-value.
                std::cout << four << std::endl;
                return 0;
            }
            ```
            ```cpp
            int squareN(const int& num)       // A const reference will work to R-value
            {
                return std::pow(num, 2);
            }
            // OR the below

            int squareN(int num)
            {
                return std::pow(num, 2);
            }


            int main()
            {
                int lValue = 2;
                auto four = squareN(lValue); // This will work since lValue is an l-value.
                auto fourAgain = squareN(2); // This will compile
                std::cout << four << std::endl;
                return 0;
            }
            ```


- ## Pointers & References are Different
    - **Pointer:**
        - Here, `q` is declared as a pointer to an integer. The `&x` takes the address of `x`, meaning `q` stores the memory address where `x` is located.
        - You can modify `x` by dereferencing `q` with `*q`.
            ```cpp
            int x = 5;
            int* q = &x; // 'q' points to 'x'
            *q = 10;     // Modifies 'x' through 'q'
            ```

    - **Reference:**
        - Here, `q` is declared as a reference to an integer. This makes `q` another name `(alias) for x`. Any modification to q directly modifies `x`, and vice versa.
        - Unlike pointers, references cannot be reassigned to refer to a different variable after their initial assignment, and they do not need to be dereferenced using the * operator to access the value they refer to.
            ```cpp
            int x = 5;
            int& q = x; // 'q' is a reference (alias) to 'x'
            q = 10;     // Directly modifies 'x' through 'q'
            ```
- ## Pass by Reference
    - Passing in a variable by reference into a function just means `Hey take in the actual piece of memory, don't make a copy!`.

        ```cpp
        int square(int num)
        {
            return std::pow(num,2);
        }
        
        int num = 5;
        std::cout << "Num: " << num <<std::endl;
        result = square(num);           // We get a new number in a new variable
        std::cout << "Num: " << num << "Result: " << result <<std::endl;
        ```

        ```cpp
        void square(int& num)                // Pass by Ref.
        {
            num = std::pow(num,2);           // We update the num var
        }                                    // and place in the square in that loc in memory
        
        int num = 5;
        std::cout << "Num: " << num <<std::endl;
        square(num);           // num is now 25 (its prev. value is lost)
        std::cout << "Num: " << num  <<std::endl;
        ```

## Initialization
*It provides an initial value at the time of construction.* There are 3 types of initialization:
- Copy Initialization: `int val = 808`
- Direct Initialization: `int val(808)`
- Uniform Initialization: `int val{808}`
- Structured Binding

- ### Narrowing Conversion
    - When you convert a value from one type to another, and the target type cannot represent the original value without losing some data. 
        ```cpp
        double wideValue = 3.14159;  // A double can hold very precise floating-point numbers
        int narrowValue = wideValue; // Converting to int, which can only hold whole numbers
        ```


- ### Copy Initialization
    - **Use Case:** Simple and straightforward, suitable for basic types. It can involve extra copy/move for complex types, potentially impacting performance.
    - **Limitations:** Not suitable for types which have explicit constructors without implicit conversion (Ex: float --> int).

        ```cpp
        dataType variable = value;
        int val = 808;
        ```
- ### Direct Initialization
    - **Use Case:** Efficient for complex types by potentially avoiding extra copy/move. Necessary for types with explicit constructors.
    - **Limitations:** Does NOT perform type check, and implicit type conversion will take place.
    
        ```cpp
        dataType variable(value);

        int val(808);   // Will go through
        int val(99.71); // This will compile and will loose fractional part.
        ```

- ### Uniform Initialization (C++11 Onwards)
    - **Use Case:** Offers type safety by preventing narrowing conversions. Ideal for initializing objects, arrays, and ensuring all elements are initialized.
    - **Limitations:** Ambiguity when multiple constructors with same args present

        ```cpp
        dataType variable{value};
        int val{808};
        int val{99.71}; // This will NOT compile and will loose fractional part.
        ```
        ```cpp
        class Example
        {
            public:
                Example(std::initializer_list<int> list) {
                    // Initializes using initializer list
                }
                
                Example(int value) {
                    // Initializes with a single integer
                }
        };

        Example ex1{5}; // Ambiguity: initializer_list or single int constructor?

        ```

- ### Key Differences and When to Use:

    - **Copy Initialization**: is easy to use but may be less efficient for complex types due to potential extra copying. Prefer this for basic types when efficiency is not a concern.

        ```cpp
        Copy code
        double num = 3.14;  // Simple and clear
        ```

    - **Direct Initialization:** is preferred for complex types to ensure efficient use of constructors. It directly invokes the constructor, which can be more efficient.

        ```cpp
        Copy code
        std::vector<int> vec(10, 0);  // Directly initializes a vector of 10 integers to 0
        ```

    - **Uniform Initialization:** aims to provide a consistent initialization syntax across all types. It prevents narrowing conversions, enhancing safety and is the recommended approach when initializing objects, especially with C++11 and beyond.

        ```cpp
        Copy code
        std::vector<int> vec{10, 0};  // Initializes a vector with two elements, 10 and 0, avoiding narrowing conversions
        ```

    - In essence, choose copy initialization for simplicity with basic types, direct initialization for efficiency with complex types, and uniform initialization for consistency and safety across C++11 and newer codebases.

- ### Structured Binding (C++17 Onwards)
    - *It is about decomposing a single composite object (like a tuple, pair, array, or struct) into multiple variables.*
        ```cpp
        std::tuple<int, char, double> myTuple = {2, 'a', 3.6};
        auto [x, y, z] = myTuple;
        std::cout << "Tuple: " << x << ", " << y << ", " << z << std::endl;

        int myArray[3] = {3, 4, 5};
        auto [a, b, c] = myArray;
        std::cout << "Array: " << a << ", " << b << ", " << c << std::endl;
        ```
        ```cpp
        struct Person
        {
            std::string firstName;
            std::string lastName;
            int age;
            double bankBalance;
        };
        
        int main()
        {
            // Initialize a struct
            Person P1{"John", "Sharma", 23, 46789.98};
            
            // Use structured binding to decompose the person object
            auto [firstName, , age, bankBalance] = P1;

            cout << "First Name: " << firstName << "Last Name: " << lastName << "Age: "<< age << << "Bank Balance: "<< bankBalance << std::endl;

            return 0;
        }
        ```