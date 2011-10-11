#! /bin/bash

## This script is used to load v4l2 modules
is_install=2
kernel_version=`uname -r`
module_path=/lib/modules/${kernel_version}/build/drivers/media

if [ $# -ne 1 ] 
then
    echo "Only install or uninstall"
    exit
fi

# @1:we should make sure arg is install or uninstall
if [ "$1" = "install" ]
then
    is_install=1
elif [ "$1" = "uninstall" ]
then
    is_install=0
else
    echo "Only install or uninstall"
    exit
fi
# @2: if install, then install dependences and vivi.ko
if [ ${is_install} -eq 1 ]
then
    insmod ${module_path}/video/videobuf2-core.ko
    insmod ${module_path}/media.ko
    insmod ${module_path}/video/videodev.ko
    insmod ${module_path}/video/v4l2-common.ko
    insmod ${module_path}/video/videobuf2-memops.ko
    insmod ${module_path}/video/videobuf2-vmalloc.ko
    insmod ${module_path}/video/vivi.ko
    echo "Success install! Go to Play, Boy!  Girl should not touch these! ^_^"
    exit
fi

# @3: if uninstall, then check if modules have all been insmod.
##    if Yes, rmmod! if not, the module is used by others, should not be rmmod!
##  To-Be-FIXED!
if [ ${is_install} -eq 0 ]
then
    rmmod ${module_path}/video/vivi
    rmmod ${module_path}/video/v4l2_common
    rmmod ${module_path}/video/videodev
    rmmod ${module_path}/media
    rmmod ${module_path}/video/videobuf2_vmalloc
    rmmod ${module_path}/video/videobuf2_memops
    rmmod ${module_path}/video/videobuf2_core
    echo "Success uninstall! Go to Sleep, Boy!"
    exit
fi

