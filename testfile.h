/* 
 * File:   testfile.h
 * Author: Bryan Daniel
 */

#ifndef TESTFILE_H
#define TESTFILE_H

/**
 * Creates a new file with randomized contents of the given file
 * 
 * @param path_to_file the file to randomize
 * @return the indication of success or failure
 */
int randomize_list(char *path_to_existing_file);

/**
 * Prompts the user for a file selection
 */
void prompt_for_randomize();

/**
 * Prompts the user for information to create a new test file.
 * 
 * @return the indication of success or failure
 */
int prompt_for_customize();

/**
 * Manages the process for creating a new test file
 */
void create_test_file();

#endif /* TESTFILE_H */

