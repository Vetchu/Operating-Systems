#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/times.h>

#ifdef DLL

#include "../zad3a/libdll.h"

#else
#include "../zad1/lib.h"
#endif

static clock_t st_time;
static clock_t en_time;
static struct tms st_cpu;
static struct tms en_cpu;

void start_clock() {
    st_time = times(&st_cpu);
}

char *stop_clock() {
    en_time = times(&en_cpu);
    int64_t clk_tck = sysconf(_SC_CLK_TCK);
    char *return_value = calloc(100, sizeof(char));
    sprintf(return_value, "%-12.2f %-12.2f %-12.2f %-12.2f  %-12.2f\n",
            (double) (en_time - st_time) / clk_tck,
            (double) (en_cpu.tms_utime - st_cpu.tms_utime) / clk_tck,
            (double) (en_cpu.tms_stime - st_cpu.tms_stime) / clk_tck,
            (double) (en_cpu.tms_cutime - st_cpu.tms_cutime) / clk_tck,
            (double) (en_cpu.tms_cstime - st_cpu.tms_cstime) / clk_tck);
    return return_value;
}

char *setup_report_file(char *name) {
    char *string = calloc(strlen(name) + 6, sizeof(char));
    sprintf(string, "raport%s", name);
    return string;
}

void write_to_report_file(char *filepath, char *operation, char *stopclock) {
    FILE *ofile = fopen(filepath, "a");

    if (strcmp(operation, "none") != 0) {
        fprintf(ofile, operation);
        fprintf(ofile, "\t");
    }
    fprintf(ofile, stopclock);
    printf("%s %s", operation, stopclock);
    fclose(ofile);
}

long _convert_to_int(char *string) {
    char *temp_string = calloc(strlen(string), sizeof(char));
    long converted = strtol(string, &temp_string, 10);

    long return_value = strcmp(temp_string, string) == 0 ? TYPE_MISMATCH : converted;
    return return_value;
}


int main(int args, char *argv[]) {
    void *handle = NULL;
#ifdef DLL
    handle = dll_init();
#endif
    size_t size = (size_t) _convert_to_int(argv[1]);
    char **newTable = NULL;

    if (size >= 0) {
        newTable = init_array(size);
    } else {
        fprintf(stderr, "Bledny rozmiar tablicy, podano %s", argv[1]);
        return ARGUMENT_ERROR;
    }

    long arg = 0;
    char *tmp_file = NULL;
    char *report_file = NULL;
    char *tmpname = NULL;
    struct DirFile *dirfile = NULL;

    start_clock();
    for (int i = 2; i < args - 1; i++) {
        if (strcmp(argv[i], "create") == 0) {
            if (newTable != NULL) {
                for (int j = 0; j < size; j++) {
                    if (newTable[j] != NULL) free(newTable[j]);
                }
                free(newTable);
            }
            newTable = init_array((size_t) argv[i + 1]);
        } else if (strcmp(argv[i], "search") == 0) {
            if (i + 3 < args) {
                //if (tmpname != NULL) free(tmpname);
                if (dirfile != NULL) free(dirfile);
                if (tmp_file != NULL) free(tmp_file);

                char *dir = argv[++i];
                char *file = argv[++i];
                tmpname = argv[++i];
                dirfile = set_dir_file(dir, file);
                tmp_file = search(dirfile, tmpname);
            } else {
                fprintf(stderr, "Bledna liczba argumentów do pozycji %d", i);
                return ARGUMENT_ERROR;
            }
        } else if (strcmp(argv[i], "remove") == 0) {
            arg = _convert_to_int(argv[++i]);
            if (arg != TYPE_MISMATCH) {
                remove_block(newTable, size, arg);
            } else {
                fprintf(stderr, "Bledny argument do operacji na pozycji %d", i);
                return TYPE_MISMATCH;
            }
        } else if (strcmp(argv[i], "output") == 0) {
            if (report_file != NULL) free(report_file);
            report_file = setup_report_file(argv[++i]);
        } else if (strcmp(argv[i], "insert") == 0) {
            if (tmp_file != NULL) {
                insert_from_tmp_file(newTable, size, tmp_file);
                /*
                printf("Wpisano do bloku: %d wyniki wyszukiwania w: %s\n",
                       insert_from_tmp_file(newTable, size, tmp_file),
                       dirfile->dir);
                       */
            } else {
                fputs("Jeszcze nie dokonano nowego wyszukania!", stderr);
                return ARGUMENT_ERROR;
            }
        } else if (strcmp(argv[i], "write") == 0) {
            char *stopclock = stop_clock();
            write_to_report_file(report_file, argv[++i], stopclock);
            free(stopclock);
            start_clock();
        } else {
            fprintf(stderr, "Bledny argument do operacji na pozycji %d", i);
            return ARGUMENT_ERROR;
        }
    }

    if (dirfile != NULL)
        free(dirfile);
    if (newTable != NULL)
        free(newTable);
    if (handle != NULL)
        dlclose(handle);
    if (report_file != NULL)
        free(report_file);

    return 0;
}