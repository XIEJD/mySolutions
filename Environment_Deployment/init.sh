#! /bin/bash

echo 'Powered By XJD To ZhuangBi.'
echo '!!! Make sure you have git. Or you should `sudo apt-get install git` first'
echo 'Only for Ubuntu.'

# download my vimrc file from my github repo.
wget -P ~/ https://raw.githubusercontent.com/XIEJD/mySolutions/master/Environment_Deployment/.vimrc
wget -P ~/ https://raw.githubusercontent.com/XIEJD/mySolutions/master/Environment_Deployment/.bash_profile

# extract bundles name in .vimrc
grep '^Plugin*' ~/.vimrc | grep -o \'.*\' | grep -o '[a-zA-Z0-9\.\/\-]*' > ~/.pathname

# download bundles automaticly using git.
for pathname in $(cat ~/.pathname)
do 
    repo=$(echo $pathname | grep -o '\/[a-zA-Z0-9\.\-]*$' | grep -o '[a-zA-Z0-9\.\-]*')
    echo $repo
    git clone --recursive https://github.com/${pathname}.git ~/.vim/bundle/$repo
done

# compile YCM
echo 'Compiling...'
cd ~/.vim/bundle/YouCompleteMe
./install.py --clang-completer

echo 'Done.'

