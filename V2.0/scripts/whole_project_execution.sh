#!/bin/bash



# Change to the directory containing the executable
cd /root/Project-1/V2.0/output || exit 1
echo -e "Enter how many times you want to run the whole project"

read loops

for thread_num in 1 2 4 8 16 32; do 
    output=$(/root/Project-1/V2.0/output/main $loops $thread_num)
done

