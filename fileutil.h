/* 
 * File:   fileutil.h
 * Author: Bryan Daniel
 */

#ifndef FILEUTIL_H
#define FILEUTIL_H

#include "sorting.h"

/**
 * This function opens the file of the given name and counts the number of lines 
 * in the file.
 * 
 * @param selected_file_name the selected file name
 * @return the line count
 */
int count_lines(char *selected_file_name);

/**
 * This function reads directory contents for the given path and populates the 
 * given menu options with the file names found. A count of the options is 
 * returned.
 * 
 * @param menu_options the menu options to populate
 * @param directory_path the directory path
 * @return the count of options
 */
int collect_directory_contents(MenuOption *menu_options, char *directory_path);

/**
 * This function reads contents from the given file and populates the array of 
 * file lines.
 * 
 * @param path_to_file the file to read
 * @param lines the array of file lines to populate
 * @return the indication of success or failure
 */
int retrieve_file_contents(char *path_to_file, FileLine *lines);

/**
 * This function writes a new file with the contents in the given array of file 
 * lines according to the order provided.
 * 
 * @param path_to_file the new file created
 * @param line_count the number of lines
 * @param lines  the file contents
 * @param order the line order
 * @return the indication of success or failure
 */
int write_ordered_file_contents(char *path_to_file, int line_count,
                                FileLine *lines, int *order);

#endif /* FILEUTIL_H */

