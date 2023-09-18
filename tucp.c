#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int isFile(char *file);
int isDirectory(char *path);
void overwriteFileOrCopyFile(char *file1, char *file2);
void addFileToNewDirectory(char *file, char *directory);
void addAllTheFilesToDirectory(int argc, char **argv);

//void copyFileAndPlaceInDirectory(char *file, char *directory);

int main(int argc, char **argv) {
    printf("Number of arguments: %d\n", argc);
    // printf("This is a file: %d, %s\n", isFile(argv[1]), argv[1]);
    // printf("This is a directory %d, %s\n", isDirectory(argv[2]), argv[2]);

    if (argc < 3) {
        perror("The number of arguments was less than 2");
        exit(EXIT_FAILURE);
    } 

    if (argc == 3) {
        printf("%s, %s, %s\n", argv[0], argv[1], argv[2]);
        if (isFile(argv[1])) {
            if (isFile(argv[1]) && isDirectory(argv[2])) {
                addFileToNewDirectory(argv[1], argv[2]);
            } else {
                overwriteFileOrCopyFile(argv[1], argv[2]);
            }
            //copyFileAndPlaceInDirectory(argv[1], argv[2]);
        } else {
            perror("There is an error in the arguments");
            exit(EXIT_FAILURE);
        }
    } else {
        addAllTheFilesToDirectory(argc, argv);
        //printf("%s", "Not meeting condition at the moment.");
    }



    // 3 possible cases of arguments
    /*
    1) 2 files provided. Copies one file's content to another file.
       1a) If file exists overwrite it 
       1b) File does not exist create the new file and write the contents 

    */
   return 0;

}

int isFile(char *file) {
    struct stat statName;

    if (stat(file, &statName) != 0) {
        fprintf(stderr, "stat() error on %s: %s\n", file, strerror(errno));
    } 
    if (S_ISREG(statName.st_mode)) {
        return 1;
    } 
    return 0;
}

int isDirectory(char *path) {
     struct stat statName;

    if (stat(path, &statName) != 0) {
        fprintf(stderr, "stat() error on %s: %s\n", path, strerror(errno));
    } 
    if (S_ISDIR(statName.st_mode)) {
        return 1;
    } 
    return 0; 
}

void overwriteFileOrCopyFile(char *file1, char *file2) {
    FILE *file;
    FILE *copy;
    char text;
    file = fopen(file1, "r");
    copy = fopen(file2, "w");

    if (file == NULL || copy == NULL) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }
    
    while ((text = fgetc(file)) != EOF) {
        fputc(text, copy);
    }
    fclose(file);
    fclose(copy);

}

void addFileToNewDirectory(char *file, char *directory) {
    printf("%s", "Is Entering here");
    char *isTheFileAPath = strrchr(file, '/');
    // Take care of having two "/" Folder1/Folder2/
    char newPathOfTheFileToDirectory[500];
    char newPath[200];
    if (isTheFileAPath != NULL) {
        strcpy(newPath, isTheFileAPath + 1);
        printf("New Path = %s\n", newPath);
        snprintf(newPathOfTheFileToDirectory, sizeof(newPathOfTheFileToDirectory), "%s%s", directory, newPath);
        printf("Directory of the file: %s\n", newPathOfTheFileToDirectory);
        overwriteFileOrCopyFile(newPath, newPathOfTheFileToDirectory);
    } else {
        snprintf(newPathOfTheFileToDirectory, sizeof(newPathOfTheFileToDirectory), "%s%s", directory, file);
        printf("Directory of the file: %s\n", newPathOfTheFileToDirectory);
        overwriteFileOrCopyFile(file, newPathOfTheFileToDirectory);
    }
}

void addAllTheFilesToDirectory(int argc, char **argv) {
    char *arr[argc];
    int count = 0;
    for (int i = 0; i < argc; i++) {
        arr[i] = argv[i];
    }
    for(int i = 1; i < argc-1; i++) {
        if (isFile(argv[i])) {
            count = count + 1;
            printf("%s, count = %d\n", argv[i], count);
        }
    }
    if (isDirectory(argv[argc-1])) {
        printf("This should be the directory: %s\n", argv[argc-1]);
        if (count == (argc - 2)) {
            for(int i = 1; i < argc-1; i++) {
                addFileToNewDirectory(argv[i], argv[argc-1]);
            }
        }
    } else {
        perror("The directory is not working");
    }
}