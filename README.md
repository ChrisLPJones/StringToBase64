# Base64 Encoding in C

This repository contains a C program that converts ASCII input into Base64 encoding. The program demonstrates various aspects of string manipulation, binary conversion, and memory management in C. It is a comprehensive example of working with command-line arguments, dynamic memory allocation, and data transformation.

## Features
- Handles input from both command-line arguments and standard input.
- Converts ASCII characters to their binary representation.
- Groups binary data into 6-bit chunks and maps them to Base64 characters using a predefined Base64 encoding table.
- Ensures proper padding and alignment for Base64 output.
- Includes custom implementations for cross-platform compatibility (`strcpy_s` for non-Windows platforms).
- Contains detailed comments to explain each step of the process.

## Use Cases
- Learn and practice binary and Base64 encoding techniques in C.
- Understand the handling of dynamic memory allocation and error checking in C programs.
- Explore cross-platform coding practices.

## Build Instructions

 ### Windows
 1. Open Microsoft Visual Studio.
 2. Create a new **Console Application** project:
    - Click **Create a new project**.
    - Select **Console App (C++)** (it works for C code as well).
    - Click **Next** and configure the project name and location.
 3. Add the provided `.c` file to the project:
    - Right-click on the **Source Files** folder in Solution Explorer.
    - Select **Add** → **Existing Item...** and choose the `.c` file.
 4. Set the project to compile as C:
    - Right-click on the project in Solution Explorer → **Properties**.
    - Navigate to **Configuration Properties** → **C/C++** → **Advanced**.
    - Set **Compile As** to **Compile as C Code (/TC)**.
 5. Build the project:
    - Press `Ctrl + Shift + B` or select **Build** → **Build Solution**.
 6. Run the program:
    - Press `F5` or select **Debug** → **Start Debugging**.

 ### Linux
 1. Open a terminal.
 2. Navigate to the directory containing the `.c` file:
    ```bash
    cd /path/to/your/project
    ```
 3. Use `gcc` to compile the program:
    ```bash
    gcc -o base64_encoder main.c -lm
    ```
    - `-o base64_encoder`: Specifies the output binary name.
    - `-lm`: Links the math library (required for `pow()`).
 4. Run the program:
    ```bash
    ./base64_encoder HelloWorld:
    ```
    or
    ```bash
    echo HelloWorld | ./base64_encoder
    ```
 

Feel free to clone, explore, and contribute to this repository! 
