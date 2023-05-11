#!/bin/bash
file_type=$3
folder_name=$2
result_file=$1
for f in $folder_name/*; do 
echo $f
if [[ "$f" == *"$file_type"* ]]; then
echo "$f" > $result_file;
fi
done
