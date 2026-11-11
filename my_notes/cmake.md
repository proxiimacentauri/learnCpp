# CMakeLists

- Its a cross-platform build system generator and a config tool.
- It helps to manage the build process of software projects.
- It can build native build files for wide range of build systemsL
    - Makefiles
    - Ninja
    - Visual Studio
    - Xcode
- It uses a *scripting language* called `CMakeLists.txt` to define the build process.
- A single `CMakeLists.txt` can be used to generate build files for multiple platforms.

## cmake (Cross-Platform make)
- It was dev. by Kitware in year 2000 and is a popular build tool for C++ projects.

## Flow of Execution of cmake
- Create a project dir and store the source files and the CMakeLists.txt in there.
    ```bash
        mkdir -p my_project
        cd my_project
    ```
- `main.cpp`
    ```c++
        #include <iostream>
        int main()
        {
            std::cout << "Hello World!" << std::endl;
            return 0;
        }
    ```
- `CMakeLists.txt`
    ```cmake
        cmake_minimum_required(VERSION 3.0)
        project(my_project)
        add_executable(my_project main.cpp)
    ```
- Now to build the project via `cmake` be inside `my_project` dir
    ```bash
        $ cmake .
        -- The C compiler identification is GNU 7.5.0
        -- The CXX compiler identification is GNU 7.5.0
        -- Detecting C compiler ABI info
        -- Detecting C compiler ABI info - done
        -- Check for working C compiler: /usr/bin/cc - skipped
        -- Detecting C compile features
        -- Detecting C compile features - done
        -- Detecting CXX compiler ABI info
        -- Detecting CXX compiler ABI info - done
        -- Check for working CXX compiler: /usr/bin/c++ - skipped
        -- Detecting CXX compile features
        -- Detecting CXX compile features - done
        -- Configuring done
        -- Generating done
        -- Build files have been written to: /home/my_project
    ```
- This will create the following files and dirs:
    ```bash
        total 48K
        drwxrwxr-x 3 Ak Ak 4.0K Feb 28 13:21 ./
        drwxrwxr-x 3 Ak Ak 4.0K Feb 28 13:17 ../
        -rw-rw-r-- 1 Ak Ak  14K Feb 28 13:18 CMakeCache.txt             // New
        drwxrwxr-x 5 Ak Ak 4.0K Feb 28 13:20 CMakeFiles/                // New
        -rw-rw-r-- 1 Ak Ak 1.6K Feb 28 13:18 cmake_install.cmake        // New
        -rwxr-xr-x 1 Ak Ak   92 Feb 28 13:18 CMakeLists.txt*
        -rwxr-xr-x 1 Ak Ak   95 Feb 28 13:17 main.cpp*
        -rw-rw-r-- 1 Ak Ak 5.1K Feb 28 13:18 Makefile                   // New
    ```

- Now we can run `make` to build our project.

    ```bash
        $ make
        Scanning dependencies of target my_project
        [ 50%] Building CXX object CMakeFiles/my_project.dir/main.cpp.o
        [100%] Linking CXX executable my_project
        [100%] Built target my_project
    ```

## Simple Examples

- **Create Simple C++ Project**
    - A small project can be org. as follows:
        ```
            CMakeLists.txt
            src/main.cpp
            src/foo.cpp
            src/foo.hpp
        ```
    - `CMakeLists.txt`
        ```cmake
            cmake_minimum_required (VERSION 3.0)

            # Setup project name
            project (my_proj)

            # Compile and link main.cpp and foo.cpp into my_proj_bin
            add_executable(my_proj_bin src/main.cpp src/foo.cpp)
        ```
        - A project can contain multiple targets (either exexs or libs)
        - When the 2 files are compiled the compiler will search for header file `foo.h`.

</br>
</br>

- **CMake Scripting Language**
    - The commands are case **insensitive**.
    - All variable values are a `text` string.
    - The text strings can be evaluated as as `boolean exp.` for `IF()` and `WHILE()`
    - The values `FALSE` `OFF` `NO` or any string ending in `-NOTFOUND` evaluates to be `false` everything else is `true`.

    - `CMakeLists.txt`
        ```cmake
            cmake_minimum_required (VERSION 3.0)

            # Commands are case INsensitive
            SET( x 3 )     # x = "3"   # This and
            set( x 3 )     # x = "3"   # This are the Same

            # Text strings can represent multiple values as a list by seperating
            # entities using a semicolon.
            set( x 3 2 10 79)           # x = "3;2;10;79"
            set( y hello world !)       # y = "hello;world;!"
            set( z "hello world!" )     # y = "hello world!"

            message( x y )              # displays "xy"
            message( ${x}${y} )         # displays "31"

            message( ${x} )                 # prints "xy"
            message( "y = ${y} z = ${z}" )  # prints y = hello;world;! z = hello world!

            # Iteration of a list
            set( x 3 2)             # x = "3;2"
            foreach (val ${x})
                message(${val})
            endforeach(val)

            # prints:
            # 3
            # 2
        ```

</br>
</br>

- **CLI Compile Options**
    - `cmake` allows end user to modify values of some variables.
    - It is usually used to deine properties of the build such as location of files, machine arch and string values.
        ```cmake
            set(<variable> <value> CACHE <type> <docstring>)
        ```
    - It sets the `variable` --> default  but allows that value to be changed when configuring the build using CLI or GUI. `<type>` can be one of the following:
        - `FILEPATH` = File chooser dialog
        - `PATH` = Dir chooser dialog
        - `STRING` - Arbitrary string
        - `BOOL` - Boolean ON/OFF checkbox.
        - `INTERNAL` - NO GUI Entry

        ```cmake
            cmake_minimum_required (VERSION 3.0)

            set(hello true CACHE BOOL "If true write hello")
            set(other_msg "Hi" CACHE STRING "Not hello value")

            if (${hello})
                message("Hello")
            else (${hello})
                message(${other_msg})
            endif (${hello})
        ```
        - To pass the change in variable via CLI.
        ```bash
            $ cmake -D hello=true .
            Hello
            -- Configuring done
            -- Generating done
            -- Build files have been written to: /home/my_proj

            $ cmake -D hello=false .
            Hi
            -- Configuring done
            -- Generating done
            -- Build files have been written to: /home/my_proj

            $ cmake -D hello=false -D other_msg=bar_foo .
            bar_foo
            -- Configuring done
            -- Generating done
            -- Build files have been written to: /home/my_proj

        ```

- **Searching for Source Files**
    - Use `find(GLOB var_name pattern)` to search for files within a dir. given one or more search patterns.

        ```cmake
            cmake_minimum_required (VERSION 3.0)

            project (HelloProject)

            file(GLOB sourcefiles
                    "src/*.hpp"
                    "src/*.cpp")

            add_executable(Hello ${sourcefiles})
        ```

- **External Libraries**
    - Statically Linked Libs
        - These libs are linked with the binary at compile-time.
        - It is common to use `CACHE` variables to specify the location of the external lib.
        - These libs are linked with the binary at run-time.
            ```cmake
                cmake_minimum_required (VERSION 3.0)

                project (HelloProject)

                set(fooinclude "/usr/local/include"
                        CACHE PATH "Location of foo header")
                set(foolib "/usr/local/lib/foo.a"
                        CACHE FILEPATH "Location of foo.a")

                include_directories(${fooinclude})

                add_executable(Hello someexe/main.cpp)
                target_link_libraries(Hello ${foolib})
            ```
            ```bash
                $ cmake -D fooinclude=/usr/local/nv/include -D foolib=/usr/local/lib/nv/foo.a .
            ```
    - Dynamically Linked Libs (DLL)
        - On Windows it is req. to link a lib. at compile time.
        - The exeutable needs to find the DLL in the runtime linkers search path.
        - If the DLL is NOT a system lib. easiest way is to copy the DLL next to the executable.
        - Working with DLL is platform specific, `CMake` offers support for built-in vars `WIN32`, `APPLE`, `UNIX`.
            ```cmake
                cmake_minimum_required (VERSION 3.0)

                project (HelloProject)

                set(fooinclude "/usr/local/include"
                        CACHE PATH "Location of foo header")
                set(foolib "/usr/local/lib/foo.lib"
                        CACHE FILEPATH "Location of foo.lib")
                set(foodll "/usr/local/lib/foo.dll"
                        CACHE FILEPATH "Location of foo.dll")

                include_directories(${fooinclude})

                add_executable(Hello someexe/main.cpp)
                target_link_libraries(Hello ${foolib})

                IF (WIN32)
                    file(COPY ${foodll} DESTINATION Debug)
                    file(COPY ${foodll} DESTINATION Release)
                ENDIF(WIN32)
            ```
- **Automatically Locating Libs**
    - `CMake` can automatically find standard libaries, based on a number of suggested locations.
        ```cmake
            set (CMAKE_CXX_STANDARD 14 )
            set (CMAKE_CXX_STANDARD_REQUIRED ON)
            set (CMAKE_CXX_EXTENSIONS OFF)

            set(CMAKE_CXX_FLAGS "-Wall -Werror -O3")
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
            set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -pedantic")
        ```