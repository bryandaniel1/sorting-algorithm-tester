/* 
 * File:   main.c
 * Author: Bryan Daniel
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sorting.h"
#include "view.h"
#include "fileutil.h"
#include "baseutil.h"
#include "testfile.h"
#include "validate.h"

/*
 * The main method
 */
int main(int argc, char** argv)
{
    int exit_main = 0;
    int exit_file_selection = 0;
    int exit_algorithm_selection = 0;
    int exit_program = 0;
    int main_selection = 0;
    int algorithm_selection = 0;
    int file_selection = 0;
    int selected_file_size = 0;
    char selected_file_name[ProgramValues.file_name_max_length];
    char path_to_file[ProgramValues.path_max_length];
    ProgramOptions *options = malloc(sizeof (ProgramOptions));
    MenuOption *menu_options = malloc(ProgramValues.max_menu_options * sizeof (MenuOption));

    if (options == NULL || menu_options == NULL)
    {
        printf("Unable to allocate memory.\n");
        return 1;
    }

    options->PrintList = ON;

    do
    {
        exit_file_selection = 0;
        exit_algorithm_selection = 0;
        exit_program = 0;
        while (exit_main == 0 && exit_program == 0)
        {
            print_main_menu();
            char message[ProgramValues.max_message_size];
            snprintf(message, sizeof message, "%s\n", "Select an option from the menu.");
            main_selection = validate_numeric_input(message);
            switch (main_selection)
            {
            case 1:
                exit_main = 1;
                break;
            case 2:
                create_test_file();
                break;
            case 3:
                print_options_menu(options);
                break;
            case 4:
                printf("Have a nice day.\n");
                exit_program = 1;
                break;
            default: printf("Invalid entry.\n");
            }
        }
        exit_main = 0;

        while (exit_file_selection == 0 && exit_program == 0)
        {
            int count = print_file_menu(menu_options, ProgramValues.test_directory_name);
            char message[ProgramValues.max_message_size];
            snprintf(message, sizeof message, "%s\n", "Select a file from the menu.");
            file_selection = validate_numeric_input(message);
            if (file_selection < count)
            {
                strcpy(selected_file_name, menu_options[file_selection - 1].selection);
                snprintf(path_to_file, sizeof path_to_file, "%s%s", 
                         ProgramValues.test_directory_name, selected_file_name);
                selected_file_size = count_lines(path_to_file);
                exit_file_selection = 1;
            }
            else if (file_selection == count)
            {
                printf("Returning to main menu...\n");
                exit_file_selection = 1;
                exit_algorithm_selection = 1;
            }
            else
            {
                printf("Invalid entry.\n");
            }
        }

        while (exit_algorithm_selection == 0 && exit_program == 0)
        {
            print_algorithm_menu();
            char message[ProgramValues.max_message_size];
            snprintf(message, sizeof message, "%s\n", "Enter an algorithm selection from the menu.");
            algorithm_selection = validate_numeric_input(message);
            switch (algorithm_selection)
            {
            case 1:
                do_bubble_sort(path_to_file, selected_file_size, options);
                exit_algorithm_selection = 1;
                exit_main = 1;
                break;
            case 2:
                do_quick_sort(path_to_file, selected_file_size, options);
                exit_algorithm_selection = 1;
                exit_main = 1;
                break;
            case 3:
                do_merge_sort(path_to_file, selected_file_size, options);
                exit_algorithm_selection = 1;
                exit_main = 1;
                break;
            case 4:
                printf("Returning to main menu...\n");
                exit_algorithm_selection = 1;
                break;
            default: printf("Invalid entry.\n");
            }
        }
    }
    while (exit_program == 0);
    free(options);
    free(menu_options);

    return (EXIT_SUCCESS);
}
