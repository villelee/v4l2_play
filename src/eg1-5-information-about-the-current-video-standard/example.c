/**
 * File Name:
 *      example.c
 * Description:
 *      This file shows how to get information about
 *      video standard used by current video capture input.
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 * Used V4L2 Infrastruct:
 *  struct:
 *      struct v4l2_standard.
 *      v4l2_std_id. (Note: not a struct but a typedef og __u64)
 *  IO Control:
 *      VIDIOC_ENUMSTD.
 *      VIDIOC_G_STD.
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
v4l2_std_id std_id;

int main(void) {
    int fd, errno = 0;

    if (-1 == (fd = open(VIVI_DEV_PATH, O_RDWR, S_IWUSR))) {
        perror("Can not VIVI device!\nExit\n");
        errno = -1;
        goto error;
    }

    errno = get_current_input_std_info(fd, &std, &std_id);
error:
    if (0 < fd) {
        close(fd);
    }
    exit(errno);
}

