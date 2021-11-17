#!/bin/bash

count=1
gcc image_copy.c
while [ "$count" -lt 2000001 ]
do
    cp "8kb.bmp" "8kb_bmps/copy$count.bmp"
    cp "4300.bmp" "4300_bmps/copy$count.bmp"
    cp "mustang.bmp" "4kb_bmps/copy$count.bmp"
    ((count=count+1))
done
