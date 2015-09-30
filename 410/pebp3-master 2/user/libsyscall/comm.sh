#!/bin/sh

for file in $(ls *.S)
do
    if ( grep -q "SYSCALL_" $file ); then
        echo $file
    fi
done
