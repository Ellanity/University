#!/bin/bash
raw_file_name=$1
result_file_name=$2
if gcc $raw_file_name -o $result_file_name; then
./$result_file_name;
else echo "Ошибки компиляции";
fi
