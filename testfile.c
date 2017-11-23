/* 
 * File:   testfile.c
 * Author: Bryan Daniel
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "view.h"
#include "baseutil.h"
#include "fileutil.h"
#include "validate.h"

void get_new_file_name(char *entered_file_name)
{
    char message[ProgramValues.max_message_size];
    snprintf(message, sizeof message, "%s\n", "Enter a file name for the new test file.");
    validate_file_name_input(message, entered_file_name);
}

int randomize_list(char *path_to_existing_file)
{
    char entered_file_name[ProgramValues.file_name_max_length];
    char path_to_new_file[ProgramValues.path_max_length];

    printf("Counting file lines...\n");
    int line_count = count_lines(path_to_existing_file);
    int random_array[line_count];

    printf("Generating random line order...\n");
    random_order(line_count, random_array);

    get_new_file_name(entered_file_name);
    snprintf(path_to_new_file, sizeof path_to_new_file, "%s%s",
             ProgramValues.test_directory_name, entered_file_name);

    //getting original lines
    FileLine *original_lines = malloc(line_count * sizeof (FileLine));

    if (original_lines == NULL)
    {
        printf("Unable to allocate memory.\n");
        return 1;
    }

    if (retrieve_file_contents(path_to_existing_file, original_lines) == 0)
    {
        // writing new lines
        if (write_ordered_file_contents(path_to_new_file, line_count, original_lines,
                                        random_array) == 0)
        {
            printf("Test file successfully created.\n");
        }
        else
        {
            printf("Test file creation failed.\n");
        }
    }
    else
    {
        return 1;
    }
    free(original_lines);

    return (EXIT_SUCCESS);
}

void prompt_for_randomize()
{
    int exit_file_selection = 0;
    int file_selection = 0;
    char selected_file_name[ProgramValues.file_name_max_length];
    char path_to_existing_file[ProgramValues.path_max_length];
    MenuOption *menu_options = malloc(ProgramValues.max_menu_options * sizeof (MenuOption));

    while (exit_file_selection == 0)
    {
        int count = print_randomize_existing_file_options(menu_options);
        char message[ProgramValues.max_message_size];
        snprintf(message, sizeof message, "%s\n", "Select Test File to Randomize:");
        file_selection = validate_numeric_input(message);
        if (file_selection < count)
        {
            strcpy(selected_file_name, menu_options[file_selection - 1].selection);
            snprintf(path_to_existing_file, sizeof path_to_existing_file, "%s%s",
                     ProgramValues.test_directory_name, selected_file_name);
            randomize_list(path_to_existing_file);
            exit_file_selection = 1;
        }
        else if (file_selection == count)
        {
            printf("Returning to previous menu...\n");
            exit_file_selection = 1;
        }
        else
        {
            printf("Invalid entry.\n");
        }
    }
}

int prompt_for_customize()
{
    char new_file_name[ProgramValues.file_name_max_length];
    char path_to_new_file[ProgramValues.path_max_length];
    bool input_valid = false;
    int number_of_lines;
    char junk;

    // Get the new file name
    get_new_file_name(new_file_name);
    snprintf(path_to_new_file, sizeof path_to_new_file, "%s%s",
             ProgramValues.test_directory_name, new_file_name);

    // Get the number of lines
    while (!input_valid)
    {
        char message[ProgramValues.max_message_size];
        snprintf(message, sizeof message, "%s\n", "Enter the number of lines for this new test file.");
        number_of_lines = validate_numeric_input(message);
        if (number_of_lines > ProgramValues.max_number_of_lines)
        {
            printf("The number of lines must no greater than %d.\n", ProgramValues.max_number_of_lines);
        }
        else
        {
            input_valid = true;
        }
    }
    int order[number_of_lines];

    // Get the new content
    FileLine *new_lines = malloc(ProgramValues.max_number_of_lines * sizeof (FileLine));
    if (new_lines == NULL)
    {
        printf("Unable to allocate memory.\n");
        return 1;
    }

    while ((junk = getchar()) != '\n' && junk != EOF);
    for (int line_count = 0; line_count < number_of_lines; line_count++)
    {
        validate_file_contents(line_count, new_lines, order);
    }

    // Write the new file
    write_ordered_file_contents(path_to_new_file, number_of_lines, new_lines, order);
    free(new_lines);
    printf("Test file successfully created.\n");

    return 0;
}

void create_test_file()
{
    int main_selection = 0;
    int exit_test_file_menu = 0;

    do
    {
        exit_test_file_menu = 0;
        while (exit_test_file_menu == 0)
        {
            print_file_creation_menu();
            char message[ProgramValues.max_message_size];
            snprintf(message, sizeof message, "%s\n", "Select an option from the menu.");
            main_selection = validate_numeric_input(message);
            switch (main_selection)
            {
            case 1:
                prompt_for_randomize();
                break;
            case 2:
                prompt_for_customize();
                break;
            case 3:
                printf("Returning to main menu...\n");
                exit_test_file_menu = 1;
                break;
            default: printf("Invalid entry.\n");
            }
        }
    }
    while (exit_test_file_menu == 0);
}