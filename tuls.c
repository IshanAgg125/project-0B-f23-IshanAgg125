#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int isFile(char *file);
void copyFileAndAddToSameDirectory(char *file1, char *file2);

int main(int argc, char **argv) {
    printf("Number of arguments: %d\n", argc);

    return 0;

    if (argc < 2) {
        perror("The number of arguments was less than 2");
        exit(EXIT_FAILURE);
    } if (argc == 2) {
        if (isFile(argv[0]) && isFile(argv[1])) { //both are file { 
            copyFileAndAddToSameDirectory(argv[0], argv[1]);
        } else {
            copyFileInNewDirectory(argv[0], argv[1]);
        }
    } else {
        copyFilesIntoNewDirectory(argv);
    }



    // 3 possible cases of arguments
    /*
    1) 2 files provided. Copies one file's content to another file.
       1a) If file exists overwrite it 
       1b) File does not exist create the new file and write the contents 

    */

}

int isFile(char *file) {
    struct stat statName;

    if (stat(file, &statName) != 0) {
        fprintf(stderr, "stat() error on %s: %s\n", file, strerror(errno));
    } 

    if (S_ISREG(statName.st_mode)) {
        return 1;
    } else if (S_ISDIR(statName.st_mode)) {
        return 0;
    } else {
        return -1;
    }
}

void copyFileAndAddToSameDirectory(char *file1, char *file2) {

}