/* 
 * File:   baseutil.h
 * Author: Bryan Daniel
 */

#ifndef BASEUTIL_H
#define BASEUTIL_H

#include <stdbool.h>

/**
 * Holds constant values used throughout the program
 */
extern const struct ProgramConfiguration
{
    int file_name_max_length;
    int line_max_length;
    int max_number_of_lines;
    int path_max_length;
    int max_menu_options;
    int max_message_size;
    char *test_directory_name;
} ProgramValues;

/**
 * This function is used to determine if the given array of integers contains 
 * the given integer value.
 * 
 * @param value the value
 * @param array the array
 * @param size the size of the array
 * @return true if the value is contained in the array, false otherwise
 */
bool array_contains_value(int value, int *array, int size);

/**
 * This function takes the given array and populates it with random numbers.  
 * The range signifies the size of the array as well as the value range for the 
 * random number operation.
 * 
 * @param range the range of values
 * @param array the array to populate
 */
void random_order(int range, int *array);

#endif /* BASEUTIL_H */

