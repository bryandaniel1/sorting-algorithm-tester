/* 
 * File:   view.h
 * Author: Bryan Daniel
 */

#ifndef VIEW_H
#define VIEW_H

#include "sorting.h"

/**
 * Prints the main menu of the program
 */
void print_main_menu();

/**
 * Prints a menu to select a sorting algorithm
 */
void print_algorithm_menu();

/**
 * Prints a menu to select a file for sorting
 * 
 * @param menu_options the menu options
 * @param directory_path the directory path
 * @return the number of options
 */
int print_file_menu(MenuOption *menu_options, char *directory_path);

/**
 * Prints a menu to set the program options
 */
void print_options_menu();

/**
 * Prints the menu for test file creation
 */
void print_file_creation_menu();

/**
 * Prints the menu for randomizing an existing test file
 * 
 * @param menu_options the menu options to populate
 * @return the number of options
 */
int print_randomize_existing_file_options(MenuOption *menu_options);

#endif /* VIEW_H */

