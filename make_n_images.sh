#!/bin/bash

count=1
gcc image_copy.c
rm "-rf" "4kb_bmps"
mkdir 4kb_bmps
rm "-rf" "4300_bmps"
mkdir 4300_bmps
rm "-rf" "8kb_bmps"
mkdir 8kb_bmps
while [ "$count" -le $1 ]
do
    cp "8kb.bmp" "8kb_bmps/copy$count.bmp"
    cp "4300.bmp" "4300_bmps/copy$count.bmp"
    cp "mustang.bmp" "4kb_bmps/copy$count.bmp"
    ((count=count+1))
done

