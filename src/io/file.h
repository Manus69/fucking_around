#ifndef FILE_H
#define FILE_H

#include "../structure/structure.h"
#include "../type/Str.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define READ_SIZE (1 << 10)

Str     file_to_Str(const char * filename);
Vector  file_to_lines(const char * filename);

#endif