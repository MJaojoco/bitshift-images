#!/bin/bash

count=1871887
gcc image_copy.c
while [ "$count" -lt 2000001 ]
do
    cp "4300.bmp" "4300_bmps/copy$count.bmp"
    cp "mustang.bmp" "4kb_bmps/copy$count.bmp"
    ((count=count+1))
done
