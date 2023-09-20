#!/bin/bash

programi="parallelAlgorithmCM*"
echo -e "2048:"
for program in $programi
do
    echo -e "$program"
    ./$program matA_2048 matB_2048
    ./$program matA_2048 matB_2048
    ./$program matA_2048 matB_2048
    ./$program matA_2048 matB_2048
    echo -e "\n"
done
echo -e "4096:"
for program in $programi
do
    echo -e "$program"
    ./$program matA_4096 matB_4096
    ./$program matA_4096 matB_4096
    ./$program matA_4096 matB_4096
    ./$program matA_4096 matB_4096
    echo -e "\n"
done