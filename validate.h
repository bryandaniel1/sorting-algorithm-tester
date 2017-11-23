/* 
 * File:   validate.h
 * Author: Bryan Daniel
 */

#ifndef VALIDATE_H
#define VALIDATE_H

#include "sorting.h"

/**
 * This function takes the given message to prompt the user for numeric input.  
 * The input is validated and the numeric input is returned when valid.
 * 
 * @param message the prompt
 * @return the user input
 */
int validate_numeric_input(char *message);

/**
 * This function takes the given message to prompt the user for new file name 
 * input. The input is validated and written to the given file name array.
 * 
 * @param message the prompt
 * @param file_name the new file name
 */
void validate_file_name_input(char *message, char *file_name);

/**
 * This function prompts the user for new file line input. The input is 
 * validated and written to the given file line array.
 * 
 * @param line_count the number of lines
 * @param new_lines the new file lines
 * @param order the line order
 */
void validate_file_contents(int line_count, FileLine *new_lines, int *order);

#endif /* VALIDATE_H */

