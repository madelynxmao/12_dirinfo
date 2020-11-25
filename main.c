#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

/*
Madelyn Mao
Systems Level Programming
HW12 -- Please follow the Dir[ections]
2020-11-22

sample run: ./main test
OR

./main
test (when prompted)
*/

int main(int argc, char **argv){
    char directory_to_scan[80];

    char backup[80]; //bc stdin makes the string end in \n and not \0

    if (argc == 2){
        strncpy(directory_to_scan, argv[1], sizeof(directory_to_scan)- 1);
    }
    else{
        printf("Enter a directory to scan: ");
        fgets(backup, sizeof(backup), stdin);
        strncpy(directory_to_scan,backup,sizeof(directory_to_scan)-1);
    }
    //Have the program scan the directory

    DIR *directory;
    directory = opendir(directory_to_scan);

    if (!directory){
        printf("Error: %s\n", strerror(errno));
    }

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
