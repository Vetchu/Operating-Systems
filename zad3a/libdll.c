//
// Created by vetch on 10.03.19.
//
#include "libdll.h"

char* (*_setup_temp_file)(char* name);
char** (*_init_array)(size_t size);
struct DirFile* (*_set_dir_file)(char *newDir, char *newFile);
char* (*_search)(struct DirFile *dirAndFile,char* tmpfile);
int (*_insert_from_tmp_file)(char **array, unsigned int size, char *tmp_file);
void (*_remove_block)(char **array, unsigned int size, unsigned int index);

void *_return_if_correct(void *handle, char *command) {
    void *result = dlsym(handle, command);
    if (result == NULL) {
        fprintf(stderr, "NIE ISTNIEJE METODA %s", command);
    }
    return result;
}

void *dll_init() {
    void *handle = dlopen("./libshared_find.so", RTLD_LAZY);
    if (handle == NULL) {
        fputs("Wrong handle", stderr);
        exit(OTHER_ERROR);
    }

    _setup_temp_file = _return_if_correct(handle, "setup_temp_file");
    _init_array = _return_if_correct(handle, "init_array");
    _set_dir_file = _return_if_correct(handle, "set_dir_file");
    _search = _return_if_correct(handle, "search");
    _insert_from_tmp_file = _return_if_correct(handle, "insert_from_tmp_file");
    _remove_block = _return_if_correct(handle, "remove_block");
    return handle;
}

char* setup_temp_file(char* name) {
    return (*_setup_temp_file)(name);
}

char **init_array(size_t size) {
    return (*_init_array)(size);
}

struct DirFile *set_dir_file(char *newDir, char *newFile) {
    return (*_set_dir_file)(newDir, newFile);
}

char *search(struct DirFile *dirAndFile, char *tmpfile) {
    return (*_search)(dirAndFile,tmpfile);
}

int insert_from_tmp_file(char **array, unsigned int size, char* tmp_file) {
    return (*_insert_from_tmp_file)(array, size, tmp_file);
}

void remove_block(char **array, unsigned int size, unsigned int index) {
    return (*_remove_block)(array, size, index);
}