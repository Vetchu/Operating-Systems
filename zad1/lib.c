//
// Created by vetch on 09.03.19.
//

#include "lib.h"
#include <stdio.h>
#include <fcntl.h>


char *setup_temp_file(char *name) {
    char *toreturn = calloc(6 + strlen(name), sizeof(char));
    sprintf(toreturn, "/tmp/%s", name);
    return toreturn;
}

//utworzenie tablicy wskaźników w której będą przechowywane wskaźniki na bloki pamięci zawierające wyniki przeszukiwań,
char **init_array(size_t size) {
    char **table = calloc(size, sizeof(char *));
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
    return table;
}

// ustawienie aktualnie przeszukiwanego katalogu oraz poszukiwanego pliku,
struct DirFile *set_dir_file(char *newDir, char *newFile) {
    struct DirFile *newDF = calloc(1, sizeof(struct DirFile));
    newDF->dir = newDir;
    newDF->file = newFile;
    return newDF;
}

// przeprowadzenie przeszukania tego katalogu i zapisanie wyniku poszukiwania w pliku tymczasowym
char *search(struct DirFile *dirAndFile, char *tmpname) {
    char *dir = dirAndFile->dir;
    char *file = dirAndFile->file;

    char *command = calloc((128 + strlen(dir) + strlen(file) + strlen(tmpname)), sizeof(char));
    sprintf(command, "find %s -name %s>%s 2> /dev/null", dir, file, tmpname);
    system(command);

    free(command);
    return tmpname;
}

// zarezerwowanie bloku pamięci o rozmiarze odpowiadającym rozmiarowi pliku tymczasowego i zapisanie w tej pamięci jego
// zawartości, ustawienie w tablicy wskaźników wskazania na ten blok, funkcja powinna zwrócić indeks stworzonego bloku w tablicy,
int insert_from_tmp_file(char **array, unsigned int size, char *tmp_file_name) {
    int fd = open(tmp_file_name, O_RDONLY);
    if (fd < 3) {
        close(fd);
        return -1;
    }
    off_t sz = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    char *new_block = calloc(sz + 1, sizeof(char));
    read(fd, new_block, sz + 1);

    int i = 0;
    while (i < size && array[i] != NULL) {
        i++;
    }

    if (i == size) {
        free(new_block);
        return -1;
    }

    array[i] = new_block;
    close(fd);
    return i;
}

// usunięcie z pamięci bloku o zadanym indeksie
void remove_block(char **array, unsigned int size, unsigned int index) {
    if (index < size && array[index] != NULL) {
        free(array[index]);
        array[index] = NULL;
    }
}


