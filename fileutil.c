/* 
 * File:   fileutil.c
 * Author: Bryan Daniel
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "fileutil.h"
#include "sorting.h"
#include "baseutil.h"

int count_lines(char *selected_file_name)
{
    FILE* chosen_file;
    if ((chosen_file = fopen(selected_file_name, "r")) == NULL)
    {
        printf("Unable to open chosen file.\n");
        return 0;
    }
    int ch = 0;
    int number_of_lines = 0;

    do
    {
        ch = fgetc(chosen_file);
        if (ch == '\n')
            number_of_lines++;
    }
    while (ch != EOF);

    if (ch != '\n' && number_of_lines != 0)
        number_of_lines++;

    fclose(chosen_file);

    return number_of_lines;
}

int collect_directory_contents(MenuOption *menu_options, char *directory_path)
{
    DIR *directory = NULL;

    directory = opendir(directory_path);
    if (directory == NULL)
        return -1;

    struct dirent *file;
    int count = 0;

    while ((file = readdir(directory)) != NULL && count < ProgramValues.max_menu_options - 2)
    {
        if (strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0)
        {
            strcpy(menu_options[count].selection, file->d_name);
            menu_options[count].menu_number = ++count;
        }
    }

    if (closedir(directory) < 0)
        return -1;
    return count;
}

int retrieve_file_contents(char *path_to_file, FileLine *lines)
{

    FILE *in;
    char line[ProgramValues.line_max_length];
    int i = 0;

    if ((in = fopen(path_to_file, "r")) == NULL)
    {
        printf("Unable to open output file.\n");
        return 1;
    }

    while (fgets(line, sizeof line, in) != NULL)
    {
        strcpy(lines[i].file_line, line);
        i++;
    }
    fclose(in);

    return 0;
}

int write_ordered_file_contents(char *path_to_file, int line_count,
                                FileLine *lines, int *order)
{

    FILE *out;
    int i = 0;
    if ((out = fopen(path_to_file, "ab+")) == NULL)
    {
        printf("Unable to open output file.\n");
        return 1;
    }
    for (i = 0; i < line_count; i++)
    {
        fprintf(out, "%s", lines[order[i]].file_line);
    }
    fclose(out);

    return 0;
}