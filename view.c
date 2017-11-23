/* 
 * File:   view.c
 * Author: Bryan Daniel
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "view.h"
#include "fileutil.h"
#include "baseutil.h"

void print_main_menu()
{
    printf("************************************************\n");
    printf("*                                              *\n");
    printf("*           SORTING ALGORITHM TESTER           *\n");
    printf("*                                              *\n");
    printf("************************************************\n");
    printf("Main Menu:\n");
    printf("1. Test Sorting Algorithms\n");
    printf("2. Create New Test File.\n");
    printf("3. Options.\n");
    printf("4. Exit program.\n");
}

void print_algorithm_menu()
{
    printf("Algorithm Options:\n");
    printf("1. Bubble Sort\n");
    printf("2. Quick Sort\n");
    printf("3. Merge Sort\n");
    printf("4. Return to Main Menu\n");
}

int print_file_menu(MenuOption *menu_options, char *directory_path)
{
    int count = collect_directory_contents(menu_options, directory_path);
    strcpy(menu_options[count].selection, "Return to Main Menu");
    menu_options[count].menu_number = ++count;

    printf("File Selection:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d. %s\n", menu_options[i].menu_number, menu_options[i].selection);
    }

    return count;
}

void print_options_menu(ProgramOptions *options)
{
    char choice;
    int exit_options = 0;
    while (exit_options == 0)
    {
        printf("Options:\n");
        if (options->PrintList == ON)
        {
            printf("Printing currently turned on.\n");
            printf("Turn printing off? Enter 'Y' for yes or 'N' to exit.\n");
            scanf(" %c", &choice);
            if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
            {
                printf("Invalid input.\n");
            }
            else if (choice == 'Y' || choice == 'y')
            {
                options->PrintList = OFF;
                exit_options = 1;
                printf("Printing successfully turned off.\n");
            }
            else
            {
                exit_options = 1;
            }
        }
        else
        {
            printf("Printing currently turned off.\n");
            printf("Turn printing on? Enter 'Y' for yes or 'N' to exit.\n");
            scanf(" %c", &choice);
            if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
            {
                printf("Invalid input.\n");
            }
            else if (choice == 'Y' || choice == 'y')
            {
                options->PrintList = ON;
                exit_options = 1;
                printf("Printing successfully turned on.\n");
            }
            else
            {
                exit_options = 1;
            }
        }
    }
}

void print_file_creation_menu()
{
    printf("New Test File:\n");
    printf("1. Randomize existing test file\n");
    printf("2. Create custom test file\n");
    printf("3. Return to Main Menu\n");
}

int print_randomize_existing_file_options(MenuOption *menu_options)
{
    printf("Test Files:\n");
    int count = collect_directory_contents(menu_options, ProgramValues.test_directory_name);
    strcpy(menu_options[count].selection, "Return to Previous Menu");
    menu_options[count].menu_number = ++count;
    for (int i = 0; i < count; i++)
    {
        printf("%d. %s\n", menu_options[i].menu_number, menu_options[i].selection);
    }
    
    return count;
}
