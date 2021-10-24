#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        perror("usage: ./a.out <src_dir> <dest_dir>");
    }
    DIR *src_dir;
    FILE *fp;
    struct dirent *curr_image;
    src_dir = opendir(argv[1]);
    if(src_dir == NULL){
        perror("unable to read source directory");
    }

    while( (curr_image = readdir(src_dir)) ){
        if(strcmp(curr_image->d_name, ".") != 0 && strcmp(curr_image->d_name, "..") != 0){
            printf("%s\n", curr_image->d_name);
            /* TO DO: concat ../ and argv[2] and / and d_name and "_edited" */
        }
    }

    return 0;
}