#include <stdio.h>

// Macro to pass the array and its length to the function
#define testArray(array) testArray_pointer(array, sizeof(array) / sizeof(array[0]))

// Function to print the array elements
void testArray_pointer(char array[][100], size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%s\n", array[i]);
    }
}

int main() {
    char array[3][100] = {"Hello", "World", "Array"};
    
    // Use the macro to call the function
    testArray(array);
    
    return 0;
}

