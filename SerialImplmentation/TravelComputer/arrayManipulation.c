#include"arrayManipulation.h"


short* remove_element(short* arr, short size, short pos) {
    // Check if pos is within bounds
    if (pos < 0 || pos >= size) {
        return arr; // Return the original array if pos is invalid
    }

    // Allocate memory for the new array
    short* new_arr = (short*) malloc((size - 1) * sizeof(short));

    // Copy the elements from arr to new_arr, except for the one at pos
    int j = 0; // Index for the new array
    for (int i = 0; i < size; i++) {
        if (i != pos) {
            new_arr[j] = arr[i];
            j++;
        }
    }

    // Free the memory used by the original array
    free(arr);

    // Return the new array
    return new_arr;
}

short* add_element(short* arr, short size, short element, short freeOldArray) {
    // Allocate memory for the new array
    short* new_arr = (short*) malloc((size + 1) * sizeof(short));

    // Copy the elements from arr to new_arr
    for (short i = 0; i < size; i++) {
        new_arr[i] = arr[i];
    }

    // Add the new element to the end of the new array
    new_arr[size] = element;

    if (freeOldArray)
    {
        // Free the memory used by the original array
        free(arr);
    }
    

    // Return the new array
    return new_arr;
}