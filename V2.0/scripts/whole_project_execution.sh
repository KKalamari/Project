#!/bin/bash



# Change to the directory containing the executable
cd /root/Project-1/V2.0/output || exit 1

echo -e "How many times you want to run the whole project" #times of executing the same instance
read loops

echo -e "Do you want to calculate the groundtruth from scratch?" #1 to calculate from scratch, 0 to read from txt
read Do_I_Calculate

echo -e "Do you want to run a single function or do a clean_run of the project?" 

read function_to_run

for thread_num in 1 2 4 8 16 32; do 
    /root/Project-1/V2.0/output/main $loops $thread_num $Do_I_Calculate $function_to_run
done

