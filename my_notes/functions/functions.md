# Functions

## Overview
```cpp
#include <iostream>

double mean (double a, double b)
{
  return (a + b) / 2;
}

int main ()
{
  std::cout << mean(2, 6) <<'\n';  // prints 4
  return 0;
}
```
![](functions.png)


- ## Return Types
    ![](return_type.png)

- ## Parameters/ Arguments
    ![](params.png)


- ## Overloading
    ![](overloading.png)

- ## Implementation
    - ### Recursion
        ![](recursion.png)
        

    - ### Declaration vs Definition
        - Can only call functions that are already known (from before/above).
        - Only one definition allowed per source file (translation unit).
        - It is ok to have any number of declarations = announcing the existence of a function by specifying its signature.
        ![](dec_def_1.png)
        ![](dec_def_2.png)



- ## Design
    *Interfaces should be easy to use correctly and hard to use incorrectly.* -- By Scott Meyers

    ![](design.png)


- ## Attribute
    ![](attribute.png)

- ## No-Throw Guarantee
    ![](noThrow.png)
