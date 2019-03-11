//
// Created by vetch on 08.03.19.
//

#ifndef ZAD1_LIBRARY_H
#define ZAD1_LIBRARY_H
#define OTHER_ERROR -1
#define ARGUMENT_ERROR -2
#define TYPE_MISMATCH -3

#include <stdio.h>
#include <unistd.h>
#include <libnet.h>

struct DirFile {
    char *dir;
    char *file;
};

char* setup_temp_file(char* name);
char **init_array(size_t size);
struct DirFile *set_dir_file(char *newDir, char *newFile);
char *search(struct DirFile *dirAndFile, char *string);
int insert_from_tmp_file(char **array, unsigned int size, char* tmp_file);
void remove_block(char **array, unsigned int size, unsigned int index);
long _convert_to_int(char *string);


#endif //ZAD1_LIBRARY_H
