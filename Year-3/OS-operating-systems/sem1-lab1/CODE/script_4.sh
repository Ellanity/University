#!/bin/bash
folder_name=$1
echo "Catalog name: $folder_name"
for f in $folder_name/*; do 
echo -n "File:	 ";
echo 
ls -l $f
done
