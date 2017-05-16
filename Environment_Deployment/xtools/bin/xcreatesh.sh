#! /bin/bash
#: Title        : xcreatesh
#: Date         : 2017-05-13
#: Author       : Xie Jidong <cs.xiejidong@gmail.com>
#: Version      : 0.1
#: Discription  : help me create a bash script with templete
#: Options      : None

echo 'Powered By XJD To Zhuangbi.'
echo 'Only for macOS and Ubuntu.'

filename=$1
instdir=~/.xtools/bin

# set bash
mkdir -p ~/.tools/bin
echo '#! /bin/bash' > ${instdir}/$filename

# set title
echo "#: Title          : ${filename}" >> ${instdir}/$filename

# set date
echo "#: Date           : $(date +%F)" >> ${instdir}/$filename

# set author
echo '#: Author         : Xie Jidong <cs.xiejidong@gmail.com>' >> ${instdir}/$filename

# set version
echo '#: Version        : 1.0' >> ${instdir}/$filename

# set discription
echo '#: Discription    : None' >> ${instdir}/$filename

# set options
echo '#: Options        : None' >> ${instdir}/$filename

# set permission
chmod 750 ${instdir}/$filename

echo 'Done.'
