/**
 * File Name:
 *      example.c
 * Description:
 *      This file shows how to get info of all
 *      the supported video standards.
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 * Used V4L2 Infrastruct:
 *  struct:
 *      struct v4l2_standard.
 *  IO Control:
 *      VIDIOC_ENUMSTD.
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

#include "../include/v4l2-util.h"

struct v4l2_standard std;

int main(void) {
    int fd, errno = 0;

    if (-1 == (fd = open(VIVI_DEV_PATH, O_RDWR, S_IWUSR))) {
        perror("Can not VIVI device!\nExit\n");
        errno = -1;
        goto error;
    }
    
    errno = list_supported_video_stds(fd, &std);

error:
    if (0 < fd) {
        close(fd);
    }
    exit(errno);
}

