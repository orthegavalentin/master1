#!/bin/bash
for file in /media/nlephilippe/USB/BOWS2OrigEp3/*.pgm
do
    echo $(./avg $file) >> out.txt
done