#!/bin/bash

for file in /home/noe/Téléchargements/BOWS2OrigEp3/*.pgm
do
    echo $(./avg $file) $file >> out.txt
done
