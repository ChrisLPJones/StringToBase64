#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <string.h> // For strcpy_s on Windows
#else
// Custom implementation of strcpy_s for Linux and other platforms
int strcpy_s(char* dest, size_t dest_size, const char* src) {
    if (strlen(src) + 1 > dest_size) {
        return 1; // Error: source is too large
    }
    strcpy(dest, src);
    return 0;
}
#endif

int main(int argc, char* argv[]) {
    //--------------------------------//
    // Get input and determine length //
    //--------------------------------//

    char* input = NULL;
    size_t length = 0;

    // Handle input from command-line argument or standard input
    if (argc > 1) {
        // Get input from the first command-line argument
        input = argv[1];
        length = strlen(input);
    }
    else {
        // Read input from standard input
        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Failed to read input\n");
            return 1;
        }
        // Remove the newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';
        length = strlen(buffer);

        // Allocate memory for input and copy the buffer content
        input = malloc(length + 1);
        if (input == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        strcpy_s(input,length +1, buffer);
    }

    // Ensure input is valid
    if (length == 0) {
        printf("Input string is empty\n");
        if (argc == 1) free(input); // Free if input was allocated dynamically
        return 1;
    }

    //---------------------------------------------------//
    // Convert each ASCII character to 8bit binary array //
    //---------------------------------------------------//

    // Allocate memory to store the binary representation of the input string
    char* binaryBitArray = malloc(sizeof(char) * length * 8);

    // Check for errors when allocating memory
    if (binaryBitArray == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    int position = 0;
    for (int i = 0; i < length; i++) {
        // Get ASCII value of the character
        int result = (int)input[i];
        // Convert ASCII value to binary and store in binaryBitArray
        for (int j = 7; j >= 0; j--) {
            binaryBitArray[j + position] = result % 2;
            result /= 2; // Shift to the next bit
        }
        position += 8;
    }

    //// DEBUG print output of binaryBitArray
    //printf("\n8-Bit Binary:\n");
    //for (int i = 0; i < length * 8; i++) {
    //    printf("%d", binaryBitArray[i]);
    //    if ((i + 1) % 8 == 0) printf(" "); // Space after each 8-bit group
    //}
    //printf("\n");

    //-----------------------------------------//
    // Split binary numbers into group of 6bits //
    //-----------------------------------------//

    // Calculate the number of 6-bit groups needed
    int binary6BitLength = (int)ceil((double)length * 8 / 6);

    // Allocate memory for storing 6-bit groups
    int** binary6bitArrays = malloc(sizeof(int*) * binary6BitLength);

    // Check for errors when allocating memory
    if (binary6bitArrays == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Allocate memory for each 6-bit group
    for (int i = 0; i < binary6BitLength; i++) {
        binary6bitArrays[i] = malloc(sizeof(int) * 6);

        // Check for errors when allocating memory
        if (binary6bitArrays[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(binary6bitArrays[j]);
            }
            free(binary6bitArrays);
            free(binaryBitArray);
            return 1;
        }
    }

    //--------------------------------------------------------//
    // Convert data from the 8bit arrays into the 6bit arrays //
    //--------------------------------------------------------//

    size_t binaryBitArrayLength = length * 8;
    int bitIndex = 0;
    int padding = 0;

    // Populate the 6-bit arrays from the binary array
    for (int i = 0; i < binary6BitLength; i++) {
        for (int j = 0; j < 6; j++) {
            if (bitIndex < binaryBitArrayLength) {
                binary6bitArrays[i][j] = binaryBitArray[bitIndex];
                bitIndex++;
            }
            else {
                binary6bitArrays[i][j] = 0; // Add padding if needed
                padding++;
            }
        }
    }

    free(binaryBitArray);

    //// DEBUG Print content of arrays
    //printf("\n6-Bit Binary:\n");
    //for (int i = 0; i < binary6BitLength; i++) {
    //    for (int j = 0; j < 6; j++) {
    //        printf("%d", binary6bitArrays[i][j]);
    //    }
    //    printf(" ");
    //}
    //printf("\n");

    //--------------------//
    // Convert to decimal //
    //--------------------//

    // Allocate memory to store the decimal representation of the 6-bit groups
    char* decimal6BitArray = malloc(sizeof(char) * binary6BitLength);

    // Check for errors when allocating memory
    if (decimal6BitArray == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Convert each 6-bit group to its decimal equivalent
    for (int i = 0; i < binary6BitLength; i++) {
        int decimal = 0;
        for (int j = 0; j < 6; j++) {
            decimal += binary6bitArrays[i][j] * (int)pow(2, 5 - j);
        }
        decimal6BitArray[i] = decimal;
    }

    // Free the 6-bit array memory
    for (int i = 0; i < binary6BitLength; i++) {
        free(binary6bitArrays[i]);
    }
    free(binary6bitArrays);

    //// DEBUG Print content of decimal array
    //printf("\nDecimal:\n");
    //for (int i = 0; i < binary6BitLength; i++) {
    //    printf("%d ", decimal6BitArray[i]);
    //}
    //printf("\n");

    //---------------------------------------------------------------//
    // Use Base64 table to find out corresponding character encoding //
    //---------------------------------------------------------------//

    const char base64Table[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/"; // Fixed Base64 table

    // Calculate the Base64 string length and allocate memory
    int base64Length = (int)ceil((double)binary6BitLength / 4) * 4; // Ensure length is a multiple of 4
    char* base64Char = malloc((size_t)base64Length * sizeof(char) + 1);
    if (base64Char == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Map 6-bit values to Base64 characters
    for (int i = 0; i < binary6BitLength; i++) {
        if (decimal6BitArray[i] >= 0 && decimal6BitArray[i] < 64) {
            base64Char[i] = base64Table[decimal6BitArray[i]];
        }
    }

    // Add padding characters `=` if needed
    for (int i = binary6BitLength; i < base64Length; i++) {
        base64Char[i] = '=';
    }

    free(decimal6BitArray);

    // Null-terminate the string
    base64Char[base64Length] = '\0';

    // Print the final Base64 encoded string
    printf("%s\n", base64Char);

    free(base64Char);

    return 0;
}
