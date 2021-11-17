#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    FILE *image_fp, *copy_fp;
    if(argc != 3){
        printf("usage: ./a.out <filename> <copy_dest>\n");
        return 1;
    }

    /* open file pointers */
    image_fp = fopen(argv[1], "r");
    if(image_fp == NULL){
        printf("error: file not found: %s\n", argv[1]);
    }
    copy_fp = fopen(argv[2], "w");    /* need to truncate the file before first write */

    /* get length of file */
    int img_size;
    fseek(image_fp, 0, SEEK_END);
    img_size = ftell(image_fp);
    fseek(image_fp, 0, SEEK_SET);

    /* fill buffer with image */
    char *buffer = malloc(img_size * sizeof(char *));
    int retno = fread(buffer, img_size, 1, image_fp);
    if(retno == 0){
        printf("error reading from %s\n", argv[1]);
        return 1;
    }

    /* write bmp header, without bit manipulation */
    fwrite(buffer, 54, 1, copy_fp);
    /* write bmp contents, with bit manipulation */
    for(int i = 54; i < img_size; i++){
        int *temp = malloc(1);
        memcpy(temp, buffer + i, 1);
        /* *temp <<= 1; include this line to bit manipulate*/
        fwrite(temp, 1, 1, copy_fp);
    }
    for(int i = img_size; i < 8192; i++){
        char *temp = malloc(1);
        *temp = i % 256;
        fwrite(temp, 1, 1, copy_fp);
    }

    free(buffer);
    fclose(image_fp);
    fclose(copy_fp);
    return 0;
}
