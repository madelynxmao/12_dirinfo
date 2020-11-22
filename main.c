#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

/*
Madelyn Mao
Systems Level Programming
HW12 -- Please follow the Dir[ections]
2020-11-22
*/

int main(){

    //Have the program scan the current directory

    DIR *directory;
    directory = opendir(".");

    struct dirent *entry;
    entry = readdir(directory);

    struct stat file;
    int size = 0;

    char not_files[80]; 

    //list all the files in the directory
    printf("files: \n");
    while(entry){
        if(entry->d_type == DT_REG){
            printf("\t%s\n", entry->d_name);
            stat(entry->d_name, &file);
            size += file.st_size;
        }
        //specify which files are directories (if any)
        else{
            strcat(not_files, "\n\t");
            strcat(not_files,entry->d_name);
            strcat(not_files, "\n");
        }
        entry = readdir(directory);
    }

    printf("not files: %s \n", not_files);

    //show the total size of all the regular files the directory
    printf("total size of all the regular files in the directory: %d \n", size);

    closedir(directory);
    return 0;
}