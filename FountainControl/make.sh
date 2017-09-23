#!/bin/bash
[ -e FountainControl.pro ] || exit
[ -e Release ] || { mkdir Release || exit; }
cd Release || exit
qmake-qt5 ../FountainControl.pro && make
echo 'Done. Press any key to exit.'
read -s -n 1
