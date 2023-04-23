# User Defined Data Types

## Classes
> **A class is like a cookie cutter; it defines the shape of objects. </br>
Objects are like cookies; they are instances of the class**

- Its a data-type which groups together related pieces of information.
- Example: </br> [Without Class] Representing a geometric vector: </br> </br>
    ```cpp
        void offsetVector(double &x0, double &x1, double &y0, double &y1, double &offsetX, double &offsetY)
        {
            x0 += offsetX;
            x1 += offsetX;
            y0 += offsetY;
            y1 += offsetY;
        }
        void printVector(double x0, double x1, double y0, double y1)
        {
            cout << "(" << x0 << "," << y0 << ") -> (" << x1 << "," << y1 << ")\n";
        }
        int main()
        {
            double xStart = 1.2;
            double xEnd = 2.0;
            double yStart = 0.4;
            double yEnd = 1.6;

            offsetVector(xStart, xEnd, yStart, yEnd, 1.0, 1.5);
            printVector(xStart, xEnd, yStart, yEnd);
            // (2.2, 1.9) -> (3.8, 4.3)
        }
    ```

</br></br>

### **Class Definition Syntax**
- Class Name: `Vector`
    - It indicates that the new data type we're defining is called *Vector*.
- Class Fields/Members: `xStart xEnd yStart yEnd`
    - It indicates the related pieces of information the datatype consists of.
    - Members can have **different types** can be a combination of (int, char, float..) </br></br>
        ```cpp
        class Vector // Class Name
        {
            public:
                double xStart, xEnd, yStart, yEnd; // Class Fields
        };
        ```
- **Class Instance**
    - Its an occurance of a class.
    - Different instances can have their own set of values in their fields.
        ```cpp
        int main()
        {
            Vector v1;
            Vector v2;
            v1.xStart = 1.1;
            v1.xEnd = 0.7;
            v1.yStart = 2.3;
            v1.yEnd = 3.0
            v2.xStart = 2.1;
            v2.xEnd = 2.7;
            v2.yStart = 1.3;
            v2.yEnd = 1.0
        }
        ```
    - Members can also be class instances
        ```cpp
        class Point
        {
            public:
                double x, y;
        }
        class Vector
        {
            public:
                Point start, end;
        }
        int main()
        {
            Vector v1;
            v1.start.x = 3.0;
            v1.start.y = 4.0;
            v1.end.x = 1.0;
            v1.end.y = 2.0;
            Vector v2;
            v2.start = v1.start; // Copies v1.start.x and v1.end.y to v2.start.x and v2.end.y
        }
        ```

- **Class Methods**
    - These are functions which are a part of a class.
        ```cpp
            class Point
            {
                public:
                    double x, y;

                    void offsetPoint(double offsetX, double offsetY)
                    {
                        x += offsetX;
                        y += offsetY;
                    }

                    void printPoint()
                    {
                        coud << "(" << x << "," << y << ")\n";
                    }
            };

            class Vector
            {
                public:
                    Point start, end;

                    void offsetVector(double offsetX, double offsetY)
                    {
                        start.offsetPoint(offsetX, offsetY);
                        end.offsetPoint(offsetX, offsetY);
                    }
                    void printVector()
                    {
                        start.printPoint();
                        cout << " -> ";
                        end.printPoint();
                        cout << "\n";
                    }
            };

            int main()
            {
                Vector v1;
                v1.start.x = 3.0;
                v1.start.y = 4.0;
                v1.end.x = 1.0;
                v1.end.y = 2.0;
                v1.offsetVector(1.0, 2.0);
                v1.printVector();
            }
        ```

</br></br>

### **Passing classes to functions**

- Pass By Value
    - Passes a copy of the class instance to the function.
    - Any changes to those copies are not preserved.
    - Pass a class by value if the members dont need to be modified (Ex: to Print them)
        ```cpp
        class Point { public: double x, y;};
        void offsetPoint(Point p, double x, double y)  // Pass by Value (Point p)
        {
            p.x += x;
            p.y += y;
        }
        int main()
        {
            Point p;
            p.x = 3.0;
            p.y = 4.0;
            offsetPoint(p, 1.0, 2.0) // Does nothing
            cout << "(" << p.x << "," << p.y << ")";  // (3.0, 4.0)
        }
        ```
- Pass By Reference
    - It will edit the class fields.
        ```cpp
        class Point { public: double x, y;};
        void offsetPoint(Point &p, double x, double y)  // Pass by Value (Point &p)
        {
            p.x += x;
            p.y += y;
        }
        int main()
        {
            Point p;
            p.x = 3.0;
            p.y = 4.0;
            offsetPoint(p, 1.0, 2.0) // Works
            cout << "(" << p.x << "," << p.y << ")";  // (4.0, 6.0)
        }
        ```

</br></br>


### **Implementing Methods Separately**
- Function prototypes allowed us to declare those functions which will be implemented later.
- The header file `.hpp` can hold the function prototypes and the actual source code can be in the `.cpp` file which doesnt need to be shared with the user.
    ```cpp
    // vector.hpp - Header File
    class Point
    {
        public:
            double x, y;
            void offsetPoint(double offsetX, double offsetY);
            void printPoint();
    };

    class Vector
    {
        public:
            Point start, end;
            void offsetVector(double offsetX, double offsetY);
            void printVector();
    };
    ```

- The `::` indicates which classe's method is being implemented.
    ```cpp
    // vector.cpp - Source Code

    #include "vector.hpp"
    void Point::offsetPoint(double offsetX, double offsetY)
    {
        x += offsetX;
        y += offsetY;
    }
    void Point::printPoint()
    {
        coud << "(" << x << "," << y << ")\n";
    }

    void Vector::offsetVector(double offsetX, double offsetY)
    {
        start.offsetPoint(offsetX, offsetY);
        end.offsetPoint(offsetX, offsetY);
    }
    void Vector::printVector()
    {
        start.printPoint();
        cout << " -> ";
        end.printPoint();
        cout << "\n";
    }
    ```

</br></br>


### **Constructors**
> Constructors do NOT have a return type.
- It is a method which is called when an instance is created of a class.
- Its main use is to initialize the variables required for the instance to be ready to be used.
- We can have multiple constructors and the **name of the constructor has to be same as class name**
    ```cpp
    class Point
    {
        public:
            double x, y;
            Point()                         // Default Constructor
            {
                x = 0.0;
                y = 0.0;
                cout << "Default Constructor\n";
            }
            Point(double nx, double ny)   // Two Parameter Constructor
            {
                x = nx;
                y = ny;
                cout << "Two Parameter Constructor\n";
            }
    };

    int main()
    {
        Point p; // Default Constructor
        // p.x = 0.0 and p.y = 0.0
        Point q(2.0, 3.0); // Two Parameter Constructor
        // q.x = 2.0 and q.y = 3.0
    }
    ```

- When we assign 1 class instance to another it copies ALL fields and uses a `default` copy constructor to do this process.
    ```cpp
    // Considor the above example as it is
    int main()
    {
        Point q(2.0, 3.0); // Two Parameter Constructor
        // q.x = 2.0 and q.y = 3.0

        Point r = q; // C++ will invoke a DEFAULT Copy Constructor
        // r.x = 2.0 and r.y = 3.0
    }
    ```
- You can define you own `copy constructor`:
    ```cpp
    class Point
    {
        public:
            double x, y;
            Point(double nx, double ny)   // Two Parameter Constructor
            {
                x = nx;
                y = ny;
                cout << "Two Parameter Constructor\n";
            }
            Point(Point &o)
            {
                x = o.x;
                y = o.y;
                cout << "Custom Copy Constructor\n";
            }
    };
    ```
- `constructor initialization list`
    - It is used to initialize:
        - Classes data members.
        - Initialize constructors of a Base class.

    - It initializes the data members directly, without any temporary copies.
    - This can be particularly important for complex objects or objects with expensive constructors.
    - Additionally, the initialization list can be used to initialize `const` and `reference` members, which cannot be assigned in the constructor body.
        ```cpp
        class Vehicle
        {
            protected:
                string license;
                int year;

            public:
                Vehicle(const string &myLicense, const int myYear)      // constructor of class --> Vehicle
                : license(myLicense), year(myYear) {}

        }
    - The method below initializes the data members within the constructor body.
    - It allows more complex initialization expressions and calculations, such as initializing a data member based on the value of another data member.
    - It may not be as efficient as the first method because it involves temporary copies of the data members.
    - Additionally, if a data member is not explicitly initialized in the constructor, it may be left uninitialized, which can lead to errors and undefined behavior.
        ```cpp
        class Vehicle
        {
            protected:
                string license;
                int year;

            public:
                Vehicle(const string &myLicense, const int myYear)      // constructor of class --> Vehicle
                {
                    license = myLicense;
                    year = myYear;
                }
        }
        ```
</br></br>


### **Access Modifiers**
- You can define where you class members and methods can be accessed from.
    - `public`: Can be accessed from anywhere.
        ```cpp
        class Point
        {
            public:
                double x, y;
                // Constructor
                Point (double nx, double ny)
                {
                    x = nx;
                    y = ny;
                }
        };
        int main()
        {
            Point p(2.0, 3.0);
            p.x = 5.0               // Allowed
        }
        ```
    - `private`: Can be accessed within the class only. (All classess are `private` by default)
        ```cpp
        class Point
        {
            private:
                double x, y;

            public:
                // Constructor
                Point (double nx, double ny)
                {
                    x = nx;
                    y = ny;
                }
        };
        int main()
        {
            Point p(2.0, 3.0);
            p.x = 5.0               // NOT Allowed
        }
        ```

        ```cpp
        class Point{
            double x, y;
        };
        // It is same as
        class Point{
            private:
                double x, y;
        };
        ```
    - `protected`:
        - Can be accessed by derieved classes
        - Use `getters` to allow read-only access to private fields.
        ```cpp
        class Point
        {
            private:
                double x, y;

            public:
                // Constructor
                Point (double nx, double ny)
                {
                    x = nx;
                    y = ny;
                }
                double getX()
                {
                    return x;
                }
                double getY()
                {
                    return y;
                }
        };
        int main()
        {
            Point p(2.0, 3.0);
            p.x = 5.0               // NOT Allowed
            cout << p.getX();       // Allowed to get values from the class.
        }
        ```

</br></br>


### `const` Member Functions
- These member functions are denied persmission to change the values of <u>*data members of their own class*</u>.
- `const` is appended to the function prototype and also to the function definition header.
- These `const` member functions can be called on any type of object const or non-const.
- An `object of a class` can also be declared as `const` which can only invoke these `const member functions`.
- It can be created by prefixing the `const` keyword to the object declaration.

    ```cpp
    class Vehicle
    {
        protected:
            string license;
            int year;

        public:
            Vehicle(const string &myLicense, const int myYear)
            : license(myLicense), year(myYear) {}

            const string getDesc() const
            {
                return license + " from " + stringify(year);
            }
            const string &getLicense() const
            {
                return license;
            }
            const int getYear() const
            {
                return year;
            }
    };
    ```




</br></br></br></br>



## Structures
- Structs are a carry-over from the C language.
- Struct : `public` by default.
    ```cpp
    struct Point{
        double x, y;
    };
    // Is Equivalent to
    struct Point{
        public:
            double x, y;
    };
    ```
- Class  : `private` by default.
    ```cpp
    class Point{
        double x, y;
    };
    // Is Equivalent to
    class Point{
        private:
            double x, y;
    };
    ```
