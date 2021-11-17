#include "copy_images.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

int copy_image(char *image_path, char *copy_path, void *buffer){
    FILE *image_fp, *copy_fp;
    int img_size, retno;

    image_fp = fopen(image_path, "r");
    if(image_fp == NULL){
        printf("error: file not found: %s\n", image_path);
    }
    copy_fp = fopen(copy_path, "w");
    if(copy_fp == NULL){
        printf("error: file not found: %s\n", copy_path);
    }

    /* get length of file */
    fseek(image_fp, 0, SEEK_END);
    img_size = ftell(image_fp);
    fseek(image_fp, 0, SEEK_SET);

    /* fill buffer with image */
    buffer = malloc(img_size * sizeof(char *));
    retno = fread(buffer, img_size, 1, image_fp);
    if(retno == 0){
        printf("error reading from %s\n", image_path);
        return 1;
    }

    /* write bmp header, without bit manipulation */
    fwrite(buffer, 54, 1, copy_fp);
    /* write bmp contents, with bit manipulation */
    int i;
    for(i = 54; i < img_size; i++){
        int *temp = malloc(1);
        memcpy(temp, buffer + i, 1);

        /** bit manipulation to change the image:
         * << will pixelate the image slightly, and make the colors more vibrant
         * >> will darken all the bytes
         */
        *temp <<= 1;
        fwrite(temp, 1, 1, copy_fp);
    }

    fclose(image_fp);
    fclose(copy_fp);

    return 0;
}

struct Node *createNode(void *buff){
    struct Node *n = malloc(sizeof(struct Node));
    n->ptr = buff;
    n->next = NULL;
    return n;
}

void appendNode(struct Node **headRef, struct Node *new){
    struct Node **temp = headRef;
    while(*temp){
        temp = &(*temp)->next;
    }
    /* temp is now the last Node's next reference (points to NULL) */
    new->next = *temp;
    *temp = new;
}

void freeList(struct Node *head){
    struct Node *temp;

    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp->ptr);
        free(temp);
    }
}

int main(int argc, char *argv[]){
    if(argc != 3){
        perror("usage: ./a.out <src_dir> <dest_dir>");
        return -1;
    }
    DIR *src_dir;
    struct dirent *curr_image;
    src_dir = opendir(argv[1]);
    if(src_dir == NULL){
        perror("unable to read source directory");
    }

    char *in_name = malloc(100 * sizeof(char));
    in_name = strncpy(in_name, argv[1], strlen(argv[1]));
    in_name = strncat(in_name, "/", strlen(in_name) + 1);
    int in_len = strlen(in_name);

    char *out_name = malloc(100* sizeof(char));
    out_name = strncpy(out_name, argv[2], strlen(argv[2]));
    out_name = strncat(out_name, "/", strlen(out_name) + 1);
    int out_len = strlen(out_name);

    /* add error handling */
    mkdir(argv[2], 0700);

    struct Node *head = malloc(sizeof(struct Node));
    head = NULL;
    struct Node *curr;

    double timeSpent = 0.0;
    int fileCount = 0;

    clock_t start = clock();

    while( (curr_image = readdir(src_dir)) ){
        void *buffer = NULL;
        if(strcmp(curr_image->d_name, ".") != 0 && strcmp(curr_image->d_name, "..") != 0){
            fileCount++;
            /* construct path names to current targets from cwd */
            in_name = strncat(in_name, curr_image->d_name, strlen(in_name) + strlen(curr_image->d_name));
            out_name = strncat(out_name, curr_image->d_name, strlen(curr_image->d_name) - 4);
            out_name = strncat(out_name, "_edited.bmp", 11);

            copy_image(in_name, out_name, buffer);
            curr = createNode(buffer);
            appendNode(&head, curr);

            /* switch in_name and out_name back to only the directory + "/" */
            memset(in_name + in_len, 0, 1);
            memset(out_name + out_len, 0, 1);
        }
    }

    clock_t end = clock();
    timeSpent = (double)(end - start) / CLOCKS_PER_SEC;

    freeList(head);

    printf("time to copy %d files: %.4f seconds\n", fileCount, timeSpent);
    return 0;
}
