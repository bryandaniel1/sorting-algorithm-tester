/* 
 * File:   baseutil.c
 * Author: Bryan Daniel
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "baseutil.h"

const struct ProgramConfiguration ProgramValues = {
    30,             //file_name_max_length
    300,            //line_max_length
    1000000,        //max_number_of_lines
    100,            //path_max_length
    102,            //max_menu_options
    100,            //max_message_size
    "./test_files/" //test_directory_name
};

void random_order(int range, int *array)
{
    // seed number generator
    srand(time(NULL));

    for (int i = 0; i < range; i++)
    {
        int number = rand() % range;
        if (!array_contains_value(number, array, range))
        {
            array[i] = number;
        }
        else
        {
            i--;
        }
    }
}

bool array_contains_value(int value, int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == value)
            return true;
    }
    return false;
}

