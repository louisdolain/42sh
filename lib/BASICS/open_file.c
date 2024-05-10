/*
** EPITECH PROJECT, 2024
** RobotFactory
** File description:
** open_file
*/

#include "basics.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

char *open_file(char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    struct stat sb;
    size_t file_size = 0;
    char *buffer = NULL;

    if (fd == -1 || stat(filepath, &sb) != 0) {
        my_fputstr("Failed to open the file\n", 2);
        return NULL;
    }
    file_size = sb.st_size;
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
