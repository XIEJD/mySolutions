#! /bin/bash

echo 'You are doing some dangerous things, baby.'
echo 'This script will delete all files related to python, include runtime files, reated modules and enviroment settings.'
echo -n 'Are you ready to remove all of them ? yes or no :'
read BIGBOY

if [ $BIGBOY == yes ]; then
    rm -rf ~/Applications/Python*
    cat ~/.bashrc.backup > ~/.bashrc
    cat ~/.bash_profile.backup > ~/.bash_profile
    echo 'You have already destroyed the Python world, T.T'
else
    echo 'Wish the world peaceful, god.'
fi
