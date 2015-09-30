#!/bin/sh

rename_from="gettid"
rename_to=$1

for filename in *.{c,h,S}
do
    newname=$(echo "$filename" | sed -e "s/$rename_from/$rename_to/g")
    mv $filename $newname
done
