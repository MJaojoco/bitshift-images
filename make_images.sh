#!/bin/bash

count=1
gcc image_copy.c
while [ "$count" -lt 2001 ]
do
    cp "mustang.bmp" "bmps/mustang_copy$count.bmp"
    ((count=count+1))
done
