#!/bin/sh

newsysc=$1

mkdir $newsysc
./copy.sh $newsysc
cd $newsysc
cp ../rename.sh .
./rename.sh $newsysc
rm rename.sh
cd ..
