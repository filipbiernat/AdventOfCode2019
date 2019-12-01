#!/bin/sh
set +x 

### SOURCE PATH
if [ -z "$1" ]
then
    day_to_copy=1
else
    day_to_copy=$1
fi
source_path="AdventOfCode/Day$day_to_copy"

### DEST PATH
latest_day=$(ls -d AdventOfCode/*/ | grep "AdventOfCode/Day" | sed 's/AdventOfCode\/Day//' | sed 's/\///' | sort -n | tail -1)
next_day=$((latest_day + 1))
dest_path="AdventOfCode/Day$next_day"

### COPY
echo "Copying directory $source_path to $dest_path..."
cp -r $source_path $dest_path

### RENAME
find $dest_path -iname "*Day$day_to_copy*"| while read file; do
    new_name=$(echo $file | sed "s/Day$day_to_copy/Day$next_day/")
    echo "Renaming file $file to $new_name..."
    mv $file $new_name
done

### REPLACE
echo "Replacing every occurence of Day$day_to_copy to Day$next_day in directory $dest_path..."
sed -i -e "s/Day$day_to_copy/Day$next_day/g" $dest_path/*
