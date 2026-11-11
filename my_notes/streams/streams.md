# Streams

## Bjarne Stroustrup on Streams
*"Designing and implementing a general input/output facility for a programming language is notoriously difficult"*

## What are streams ?
A steam is an **abstraction** of input and output for C++.
- Imagine an empty container called a stream which can hold characters of indefinite length.
- This container/stream which holds the characters can be a channel to input or output.
- Streams allow C++ programmer to convert between the string represenation of data, and data itself.
- Any *primitive type* can be inserted into a stream.
    ```cpp
    using std::cout;
    cout << "Hello!";
    cout << 3.1415;
    coud << 88 << "is greater than" << 3.1415; // Mixed types also work
    ```
- `cout` and `cin` are standard streams from STL.
- `cerr: used to output errors (Unbuffered)` and `clog: used for non-critical event logging (buffered)` are also a part of STL. 
- There are 2 types of streams:
    - **Output Streams**
        - All the output streams are of the type `std::ostream` they can **ONLY RECIEVE DATA**.
        - `std::cout` is an example which can only recieve data.
        - `<<` is an *insertion operator* which converts data --> `string` and **sends to stream**.
        - `std::ofstream` is a special type of `std::ostream` which can send data to a file.
        - Example:
            ```cpp
            using std::cout;
            using std::endl;
            // Write to console
            int num = 808;
            cout << "My number is: " << num << endl;

            // Write to a file
            std::ofstream myFile("log.txt");
            myFile << "Logging and keeping track of the number: " << num << endl;
            ```
        - We can write a method which can write to anystream.
            ```cpp
            writeToAnyStream(std::ostream& streamToWriteIn, int num)
            {
                streamToWriteIn << num << endl;
            }

            writeToAnyStream(cout, 88); // Will write 88 to cout
            writeToAnyStream(myFile, 88); // Will write 88 to log.txt
            ```

    - **Input Streams**
        - All the input streams are of the type `std::istream` they can **ONLY GIVE DATA**.
        - `std::cin` is an example which can only pull out data.
        - `>>` is an *extraction operator* which gets data **converts it into the appropriate type**.
        - `std::ifstream` is a special type of `std::istream` which can read data from a file.
        - Example:
            ```cpp
            // Read numbers from log.txt
            void readNumbers()
            {
                // Specify the file you want to open
                std::ifstream logFile("log.txt");

                int number = 0;  // Similarly can be done for words using string
                // Use while loop to read the contents
                while(true)
                {
                    logfile >> number;

                    if(logFile.fail())
                    {
                        break;
                    }
                    cout << "Number:" << num;
                }
            }
            ```
            ```cpp
            // Read lines from log.txt
            void readLines()
            {
                // Specify the file you want to open
                std::ifstream logFile("log.txt");

                std::string line = 0;  // Store the whole line in the var
                // Use while loop to read the contents
                while(true)
                {
                    // Store the line got from logFile and store it in to line
                    std::getline(logFile, line); 

                    if(logFile.fail())
                    {
                        break;
                    }
                    cout << "Line:" << line;
                }
            }
            ```
- **Stream Bits**: There are 4 bits, to give us information about their state:
    - Good bit -  No errors, the stream is good to go.
    - EOF bit - End-of-file was reached during a previous operation.
    - Fail bit - Logical error on a previous operation.
    - Bad bit - Likely unrecoverable error on previous operation.

- There are some additional methods we can use on streams built in the standard library.
    - Example:
        ```cpp
        std::ifstream myFile("log.txt");

        myFile.get(ch);          // reads one char at a time
        myFile.close();          // closes stream
        myFile.clear();          // resets any fail bits
        myFile.open("filename"); // open stream on file
        myFile.seekg(0);         // rewinds stream         
        ```

    - Examples:
        ```cpp
        // Print each character in log.txt
        
        std::ifstream myFile("log.txt");

        if (myFile.is_open())
        {
            char ch;
            while(myFile.get(ch))
            {
                std::cout << "The character is:" << ch << std::endl;
            }
            myFile.close();
        }
        ```
        ```cpp
        // Print each line in log.txt but set the cursor to 0 before doing that
        
        std::ifstream myFile("log.txt");

        if (myFile.is_open())
        {
            myFile.seekg(0); // Set the file cursor to start of file.

            std::string line;
            while (getline(input, line))
            {
                std::cout << "Read line: " << line << std::endl;
            }
        }   
        ```

## Buffering and Flushing

- **Buffering**: *Buffering is accumulating the characters in a temporary buffer/array.* 

- **Flushing**: When the buffer is filled as required, we write out *all contents of the buffer to the output stream all at once.*

    <table>
    <tr>
    <th>C++</th>
    <th>Output</th>
    </tr>
    <tr>
    <td>
    
    ```cpp
    void testBuffer(std::ostream& streamType)
    {
        streamType << "Before Loop -->";
        for(i=0; i < 800000000; i++)
        {
            //waste time
        }
        streamType << "<-- After Loop" << std::endl;
    }

    int main()
    {
        testBuffer(std::cout);
        return 0;
    }
    ```
    </td>
    <td>

    ```shell
    # As soon as the function is run 'Before Loop -->' will be in cout stream
    # but it will not be printed as it is NOT flushed
    # 
    # The loop will add a delay
    # and at once due to std::endl you will see
    
    Before Loop --><-- After Loop

    ```
    </td>
    </tr>
    </table>

    <table>
    <tr>
    <th>C++</th>
    <th>Output</th>
    </tr>
    <tr>
    <td>
    
    ```cpp
    void testFlushedBuffer(std::ostream& streamType)
    {
        streamType << "Before Loop -->" << std::flush;
        for(i=0; i < 800000000; i++)
        {
            //waste time
        }
        streamType << "<-- After Loop" << std::endl;
    }

    int main()
    {
        testFlushedBuffer(std::cout);
        return 0;
    }
    ```
    </td>
    <td>

    ```shell
    # As soon as the function is run 'Before Loop -->' will printed
    # as it is flushed
    # 
    # The loop will add a delay
    # Then because of std::endl you will see
    
    Before Loop --><-- After Loop
    
    ```
    </td>
    </tr>
    </table>


## Understanding Stream Operators
```cpp
std::cout << "Hello, " << "World!" << std::endl;

// Above can also be written as below
(((std::cout << "Hello, ") << "World!") << std::endl);
```
- `std::cout << "Hello, "` inserts `"Hello, "` into the standard output and returns a reference to `std::cout`.
- The **returned reference is then used immediately as the left-hand operand** of the next `<<` operation, allowing `"World!"` to be inserted into the same stream.
- Finally, `std::endl` is inserted into the stream, **which also performs a flush operation**, ensuring that all buffered output is written to the terminal.

## How to use stream in programs

<table>
<tr>
<th>Basic Way</th>
<th>Optimized</th>
</tr>
<tr>
<td>

```cpp
while(true)
{
    stream >> tmp;
    if (stream.fail())  break;
    do_something();
}

// Another way to check if the stream has a bad bit is
if(!stream) break

// We saw in the above section std::cout << "Hello, "
// returns a stream, we can write the above as 
if(!(stream >> tmp)) break
```
</td>
<td>

```cpp
// When there is a bad bit, stream will return a
// false and will break the while loop
while(stream >> tmp)
{
    do_something();
}

// Same case with getline()

while(getline(stream, tmp))
{
    do_something();
}

```
</td>
</tr>
</table>

## String Manipulations
There are some basic string manipulations we can do for a formatted output.

- By default the output is **right-justified**  in C++.

    ```cpp
    std::endl         // inserts a new line and flushes the stream
    std::ws           // skips all white space until it finds another char
    std::boolapha     // prints 'true' and 'false' for bools
    std::hex          // prints numbers in hex
    std::setprecision // adjusts the precision numbers print
    std::setw         // pads output
    std::setfill      // fills padding with character
    std::left         // left justified
    ```

    <table>
    <tr>
    <th>String Manipulators</th>
    <th>Output</th>
    </tr>
    <tr>
    <td>

    ```cpp
    std::cout << "[" << std::setw(10) << "Hi" << "]" << std::endl;
    std::cout << "[" << "Hi" << std::setw(10) << "]" << std::endl;

    std::cout << "[" << std::left << std::setw(10) << "Hi" << "]" << std::endl;
    std::cout << "[" << std::left << std::setfill('-') << std::setw(10) << "Hi" << "]" << std::endl;
    ```
    </td>
    <td>

    ```shell
    [        Hi]
    [Hi         ]

    [Hi        ]
    [Hi--------]
    ```
    </td>
    </tr>
    </table>



    <table>
    <tr>
    <th>String Manipulators</th>
    <th>Output</th>
    </tr>
    <tr>
    <td>

    ```cpp
    std::cout << std::hex << 12 << std::endl;
    std::cout << std::dec << 12 << std::endl;
    std::cout << std::oct << 12 << std::endl;
    ```
    </td>
    <td>

    ```shell
    c
    12
    14
    ```
    </td>
    </tr>
    </table>

## String Stream
- We want to be able to treat a string like a stream. It can be useful in:
    - Converting between datatypes.
    - Tokenizing a string.

    ```cpp
    #include <sstream>
    
    int main()
    {
        std::string userString = "137 2.718 Hello";
        int myInt;
        double myDouble;
        std::string myString;
        
        std::stringstream myStream(liuserStringne); 
    
        myStream >> myInt >> myDouble >> myString;
    
        std::cout << myInt <<  std::endl;
        std::cout << myDouble <<  std::endl;
        std::cout << myString <<  std::endl;

        return 0;
    }
    ```
