/* 
 * File:   sorting.h
 * Author: Bryan Daniel
 */

#ifndef SORTING_H
#define SORTING_H

/*Holds the file contents*/
typedef struct
{
    char file_line[300];
} FileLine;

/*Holds the options*/
typedef struct
{
    enum {ON, OFF} PrintList;
} ProgramOptions;

/*Holds a menu option*/
typedef struct
{
    int menu_number;
    char selection[30];
} MenuOption;

/**
 * This function creates two temporary arrays from the bottom and top halves of 
 * the given fileLines array. The two halves are compared to one another to sort 
 * the values of the file lines ascending in order.
 * 
 * @param file_lines the array of file lines
 * @param left_index the left index
 * @param midpoint_index the index of the midpoint
 * @param right_index the right index
 */
void merge(FileLine *file_lines, int left_index, int midpoint_index, int right_index);

/**
 * This function splits the given fileLines array into two halves to recursively 
 * call mergeSort on each half before calling merge on the array.
 * 
 * @param file_lines the array of file lines
 * @param left_index the left index of the array
 * @param right_index the right index of the array
 */
void merge_sort(FileLine *file_lines, int left_index, int right_index);

/**
 * This function manages the merge sort routine by collecting content from the 
 * file associated with the given file name and using the mergeSort and merge 
 * functions to sort the contents.
 * 
 * @param file_name the file name
 * @param contents_size the number of lines in the file
 * @param options the program options
 * @return the indication of success or failure
 */
int do_merge_sort(char *file_name, int contents_size, ProgramOptions *options);

/**
 * This function takes the given file contents from the pivot index to the max 
 * index and divides them into two groups, the contents with values greater than 
 * the pivot and the contents with values less than or equal to the pivot.  Once 
 * divided, the new midpoint index is returned.
 * 
 * @param file_lines the file contents to divide
 * @param pivot_index the pivot index
 * @param max_index the maximum index
 * @return the midpoint index
 */
int divide(FileLine *file_lines, int pivot_index, int max_index);

/**
 * This function takes the given file contents and the starting and ending 
 * indices, divides the contents, and recursively calls quickSort on the divided 
 * segments.
 * 
 * @param file_lines the file contents to sort
 * @param pivot_index the pivot index
 * @param max_index the maximum index
 */
void quick_sort(FileLine *file_lines, int pivot_index, int max_index);

/**
 * This function manages the quick sort routine by collecting content from the 
 * file associated with the given file name and using the quickSort and divide 
 * functions to sort the contents.
 * 
 * @param file_name the file name
 * @param contents_size the number of lines in the file
 * @param options the program options
 * @return the indication of success or failure
 */
int do_quick_sort(char *file_name, int contents_size, ProgramOptions *options);

/**
 * This function compares values in the given fileLines array to find and return 
 * the index of the greatest.
 * 
 * @param file_lines the array of words/lines
 * @param count the size of the array
 * @return the index of the greatest value
 */
int get_max(FileLine *file_lines, int count);

/**
 * This function swaps the values of the two given words.
 * 
 * @param one_word the first word
 * @param another_word the second word
 */
void swap_words(char *one_word, char *another_word);

/**
 * This function manages the bubble sort routine by collecting content from the 
 * file associated with the given file name and using the getMax and swapWords 
 * functions to sort the contents.
 * 
 * @param file_name the file name
 * @param contents_size the number of lines in the file
 * @param options the program options
 * @return the indication of success or failure
 */
int do_bubble_sort(char *file_name, int contents_size, ProgramOptions *options);

#endif /* SORTING_H */

