#! /bin/bash

echo 'Powered By XJD To ZhuangBi.'
echo 'Only for Ubuntu.'

# settings
echo 'Which python version do you want to install ? EXAMPLE: 3.5.2'
echo -n $PS2
read VERSION
PYTHON=Python-$VERSION
INSTALL_DIR=~/Applications/$PYTHON
DOWNLOAD_URL=https://www.python.org/ftp/python/${VERSION}/${PYTHON}.tgz
DOWNLOAD_DIR=~/Downloads

echo Dowloading ${PYTHON} from $DOWNLOAD_URL saves to $DOWNLOAD_DIR
echo Installing to $INSTALL_DIR

# download
if [ -e $DOWNLOAD_DIR]; then
    echo 'Using exist files.'
else
    wget -P $DOWNLOAD_DIR $DOWNLOAD_URL
fi

# decompress
cd $DOWNLOAD_DIR
echo 'Decompressing...'
tar -zxf ./${PYTHON}.tgz
if [ -d $PYTHON ]; then
    cd $PYTHON
else
    echo 'Failed to decompress'
    exit
fi

# create working directory
if [ -d $INSTALL_DIR ]; then
    echo Existed directory. $INSTALL_DIR
else
    mkdir -p $INSTALL_DIR
    if [ -d $INSTALL_DIR ]; then
        echo Created directory. $INSTALL_DIR
    else
        echo 'Can not create' $INSTALL_DIR
        exit
    fi
fi

# configure
echo 'Configuring...'
./configure -q --prefix $INSTALL_DIR

# make
echo 'Compiling...'
make && make install
if [ $? -eq 0 ]; then
    echo 'Good make.'
else
    echo 'Bad make.'
    exit
fi

# environment, backup first
cat ~/.bashrc > ~/.bashrc.backup
cat ~/.bash_profile > ~/.bash_profile.backup
echo 'Setting environments...'
echo alias python=~/Applications/${PYTHON}/bin/python3 >> ~/.bashrc
echo alias pip=~/Applications/${PYTHON}/bin/pip3 >> ~/.bashrc
echo PYTHONPATH=~/Applications/${PYTHON}/bin >> ~/.bashrc

# update environment
source ~/.bashrc

echo 'Done.'
echo 'If fail to execute python, try `source ~/.bashrc` in your terminal.'
