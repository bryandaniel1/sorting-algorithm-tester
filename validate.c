/* 
 * File:   validate.c
 * Author: Bryan Daniel
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "validate.h"
#include "sorting.h"
#include "baseutil.h"

int validate_numeric_input(char *message)
{
    int valid_number;
    int input;
    do
    {
        printf("%s", message);
        valid_number = scanf("%d", &input);
        if (valid_number == 1)
        {
            if (input == 0)
            {
                printf("The input must be greater than zero.\n");
                valid_number = 0;
            }
        }
        else
        {
            printf("The input must be a number.\n");
            char c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    while (valid_number != 1);
    return input;
}

void validate_file_name_input(char *message, char *file_name)
{
    bool input_valid = false;
    char buffer[ProgramValues.file_name_max_length];
    char junk;
    while ((junk = getchar()) != '\n' && junk != EOF);
    while (!input_valid)
    {
        printf("%s", message);
        fgets(buffer, ProgramValues.file_name_max_length, stdin);
        for (int i = 0; i < ProgramValues.file_name_max_length; i++)
        {
            if (buffer[i] == '\n' && i > 0)
            {
                file_name[i] = '\0';
                input_valid = true;
                break;
            }
            else if (buffer[i] == '\n' && i == 0)
            {
                printf("A file name is required.\n");
                break;
            }
            else if (buffer[i] != '\n' && i < ProgramValues.file_name_max_length - 1)
            {
                file_name[i] = buffer[i];
            }
            else
            {
                while ((junk = getchar()) != '\n' && junk != EOF);
                printf("The file name must be less than %d characters.\n",
                       ProgramValues.file_name_max_length - 1);
                break;
            }
        }
    }
}

void validate_file_contents(int line_count, FileLine *new_lines, int *order)
{
    char buffer[ProgramValues.line_max_length];
    char new_line[ProgramValues.line_max_length];
    bool input_valid = false;
    char junk;
    while (!input_valid)
    {
        printf("Enter line %d for the new test file.\n", line_count + 1);
        fgets(buffer, ProgramValues.line_max_length, stdin);
        for (int char_count = 0; char_count < ProgramValues.line_max_length; char_count++)
        {
            if (buffer[char_count] == '\n' && char_count > 0
                    && char_count < ProgramValues.line_max_length - 1)
            {
                new_line[char_count] = buffer[char_count];
                new_line[char_count + 1] = '\0';
                strcpy(new_lines[line_count].file_line, new_line);
                order[line_count] = line_count;
                input_valid = true;
                break;
            }
            else if (buffer[char_count] == '\n' && char_count == 0)
            {
                printf("A non-empty line is required.\n");
                break;
            }
            else if (buffer[char_count] != '\n' && char_count < ProgramValues.line_max_length - 1)
            {
                new_line[char_count] = buffer[char_count];
            }
            else
            {
                while ((junk = getchar()) != '\n' && junk != EOF);
                printf("The line must be less than %d characters.\n",
                       ProgramValues.line_max_length - 1);
                break;
            }
        }
    }
}