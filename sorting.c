/* 
 * File:   sorting.c
 * Author: Bryan Daniel
 */

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <time.h>
#include "sorting.h"
#include "baseutil.h"
#include "fileutil.h"

void merge(FileLine *file_lines, int left_index, int midpoint_index, int right_index)
{
    int lower_array_count, upper_array_count, file_lines_count;
    int lower_half_size = midpoint_index - left_index + 1;
    int upper_half_size = right_index - midpoint_index;

    // temporary arrays
    FileLine *lower_array = malloc(lower_half_size * sizeof (FileLine));
    FileLine *upper_array = malloc(upper_half_size * sizeof (FileLine));

    if (lower_array == NULL || upper_array == NULL)
    {
        printf("Unable to allocate memory.\n");
    }

    // temporary arrays loaded with file lines
    for (lower_array_count = 0; lower_array_count < lower_half_size; lower_array_count++)
    {
        lower_array[lower_array_count] = file_lines[left_index + lower_array_count];
    }

    for (upper_array_count = 0; upper_array_count < upper_half_size; upper_array_count++)
    {
        upper_array[upper_array_count] = file_lines[midpoint_index + 1 + upper_array_count];
    }

    // temporary array values compared and merged into file lines array
    lower_array_count = 0;
    upper_array_count = 0;
    file_lines_count = left_index;
    while (lower_array_count < lower_half_size && upper_array_count < upper_half_size)
    {
        if (strcmp(lower_array[lower_array_count].file_line, upper_array[upper_array_count].file_line) <= 0)
        {
            file_lines[file_lines_count] = lower_array[lower_array_count];
            lower_array_count++;
        }
        else
        {
            file_lines[file_lines_count] = upper_array[upper_array_count];
            upper_array_count++;
        }
        file_lines_count++;
    }

    // leftover lower half values are added
    while (lower_array_count < lower_half_size)
    {
        file_lines[file_lines_count] = lower_array[lower_array_count];
        lower_array_count++;
        file_lines_count++;
    }

    // leftover upper half values are added
    while (upper_array_count < upper_half_size)
    {
        file_lines[file_lines_count] = upper_array[upper_array_count];
        upper_array_count++;
        file_lines_count++;
    }

    // release memory for temporary arrays
    free(lower_array);
    free(upper_array);
}

void merge_sort(FileLine *file_lines, int left_index, int right_index)
{
    if (left_index < right_index)
    {
        int midpoint = ((right_index - left_index) / 2) + left_index;

        merge_sort(file_lines, left_index, midpoint);
        merge_sort(file_lines, midpoint + 1, right_index);
        merge(file_lines, left_index, midpoint, right_index);
    }
}

int do_merge_sort(char *file_name, int contents_size, ProgramOptions *options)
{
    FileLine *file_lines = malloc(contents_size * sizeof (FileLine));

    if (file_lines == NULL)
    {
        printf("Unable to allocate memory.\n");
        return 1;
    }
    
    if (retrieve_file_contents(file_name, file_lines) == 1)
    {
        return 1;
    }

    struct timespec start_time;
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    printf("time started = %ld milliseconds\n", start_time.tv_sec * 1000 + start_time.tv_nsec / 1000000);

    merge_sort(file_lines, 0, contents_size - 1);

    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    printf("time ended  = %ld milliseconds\n", end_time.tv_sec * 1000 + end_time.tv_nsec / 1000000);

    if (options->PrintList == ON)
    {
        printf("The sorted words are: \n");
        for (int i = 0; i < contents_size; i++)
        {
            printf("%s", file_lines[i].file_line);
        }
    }
    free(file_lines);

    printf("\nTime elapsed for merge sort: %ld milliseconds\n",
           (end_time.tv_sec - start_time.tv_sec) * 1000 + (end_time.tv_nsec - start_time.tv_nsec) / 1000000);
    fflush(stdout);

    return 0;
}

int divide(FileLine *file_lines, int pivot_index, int max_index)
{
    int i, j;
    FileLine pivot;
    FileLine temp;
    pivot = file_lines[pivot_index];
    i = pivot_index;
    j = max_index + 1;

    while (1)
    {
        do
            ++i;
        while (strcmp(file_lines[i].file_line, pivot.file_line) <= 0 && i <= max_index);

        do
            --j;
        while (strcmp(file_lines[j].file_line, pivot.file_line) > 0);

        if (i >= j)
        {
            break;
        }
        temp = file_lines[i];
        file_lines[i] = file_lines[j];
        file_lines[j] = temp;
    }
    temp = file_lines[pivot_index];
    file_lines[pivot_index] = file_lines[j];
    file_lines[j] = temp;
    return j;
}

void quick_sort(FileLine *file_lines, int pivot_index, int max_index)
{
    int midpoint;

    if (pivot_index < max_index)
    {
        midpoint = divide(file_lines, pivot_index, max_index);
        quick_sort(file_lines, pivot_index, midpoint - 1);
        quick_sort(file_lines, midpoint + 1, max_index);
    }
}

int do_quick_sort(char *file_name, int contents_size, ProgramOptions *options)
{
    FileLine *lines = malloc(contents_size * sizeof (FileLine));

    if (lines == NULL)
    {
        printf("Unable to allocate memory.\n");
        return 1;
    }
    
    if (retrieve_file_contents(file_name, lines) == 1)
    {
        return 1;
    }

    struct timespec start_time;
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    printf("time started = %ld milliseconds\n", start_time.tv_sec * 1000 + start_time.tv_nsec / 1000000);

    quick_sort(lines, 0, contents_size - 1);

    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    printf("time ended  = %ld milliseconds\n", end_time.tv_sec * 1000 + end_time.tv_nsec / 1000000);

    if (options->PrintList == ON)
    {
        printf("The sorted words are: \n");
        for (int i = 0; i < contents_size; i++)
        {
            printf("%s", lines[i].file_line);
        }
    }
    free(lines);

    printf("\nTime elapsed for quick sort: %ld milliseconds\n",
           (end_time.tv_sec - start_time.tv_sec) * 1000 + (end_time.tv_nsec - start_time.tv_nsec) / 1000000);
    fflush(stdout);

    return 0;
}

int get_max(FileLine *lines, int count)
{
    int max_element = 0;
    int i;
    for (i = 1; i < count; i++)
    {
        if (strcmp(lines[max_element].file_line, lines[i].file_line) < 0)
        {
            max_element = i;
        }
    }
    return max_element;
}

void swap_words(char *one, char *another)
{
    char temp[ProgramValues.line_max_length];

    strcpy(temp, one);
    strcpy(one, another);
    strcpy(another, temp);
}

int do_bubble_sort(char *file_name, int contents_size, ProgramOptions *options)
{
    int count;
    int max_index;
    FileLine *lines = malloc(contents_size * sizeof (FileLine));

    if (lines == NULL)
    {
        printf("Unable to allocate memory.\n");
        return 1;
    }
    
    if (retrieve_file_contents(file_name, lines) == 1)
    {
        return 1;
    }

    struct timespec start_time;
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    printf("time started = %ld milliseconds\n", start_time.tv_sec * 1000 + start_time.tv_nsec / 1000000);

    count = contents_size;
    while (count > 0)
    {
        max_index = get_max(lines, count);
        swap_words(lines[max_index].file_line, lines[count - 1].file_line);
        count--;
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    printf("time ended  = %ld milliseconds\n", end_time.tv_sec * 1000 + end_time.tv_nsec / 1000000);

    if (options->PrintList == ON)
    {
        printf("The sorted words are:\n");
        for (int i = 0; i < contents_size; i++)
        {
            printf("%s", lines[i].file_line);
        }
    }
    free(lines);

    printf("\nTime elapsed for bubble sort: %ld milliseconds\n",
           (end_time.tv_sec - start_time.tv_sec) * 1000 + (end_time.tv_nsec - start_time.tv_nsec) / 1000000);
    fflush(stdout);

    return 0;
}