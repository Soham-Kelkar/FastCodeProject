#!/bin/sh
DIR="../results/"
for FILE in "$DIR"*Left.*
do
	echo $FILE
	echo ${FILE/Left./Right.}
	./sgm -d 64 -w 200 $FILE ${FILE/Left./Right.}
done

