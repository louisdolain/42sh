/*
** EPITECH PROJECT, 2024
** RobotFactory
** File description:
** open_file
*/

#include "basics.h"
#include <fcntl.h>
#include <unistd.h>

int get_file_size(char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    char buffer[2];
    int size = 0;

    while (read(fd, buffer, 1) > 0)
        size++;
    close(fd);
    return size;
}

char *open_file(char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    int file_size = 0;
    char *buffer = NULL;

    if (fd == -1) {
        my_fputstr("Failed to open the file\n", 2);
        return NULL;
    }
    file_size = get_file_size(filepath);
    buffer = smalloc(sizeof(char) * (file_size + 1));
    if (buffer != NULL) {
        read(fd, buffer, file_size);
        buffer[file_size] = '\0';
    }
    close(fd);
    return buffer;
}

void overwrite_file(char *filepath, char *string)
{
    int fd = open(filepath, O_RDWR | O_CREAT, 776);

    write(fd, string, my_strlen(string));
    close(fd);
}

void appendwrite_file(char *filepath, char *string)
{
    int fd = open(filepath, O_RDWR | O_CREAT | O_APPEND, 776);

    write(fd, string, my_strlen(string));
    close(fd);
}
