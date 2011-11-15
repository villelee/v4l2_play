/**
 * File Name:
 *      example.c
 * Description:
 *      This file shows how to get crop capability info
 *      from capture device in v4l2.
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 * Used V4L2 Infrastruct:
 *  struct:
 *      struct v4l2_cropcap.
 *      struct v4l2_rect.
 *      struct v4l2_fract. (Note: numerator is horizontal pixel number 
 *                              while denominator is vertical pixel number)
 *  IO Control:
 *      VIDIOC_CROPCAP.
 */
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

#include "../include/v4l2-util.h"

struct v4l2_cropcap ccap;

int main(void) {
    int fd, retval = 0;

    if (-1 == (fd = open(VIVI_DEV_PATH, O_RDWR, S_IWUSR))) {
        perror("Can not VIVI device!\nExit\n");
        retval = -1;
        goto error;
    }

    if (-1 == get_cropcap_info(fd, &ccap))
        retval = -1;

error:
    if (0 < fd) {
        close(fd);
    }
    exit(retval);
}

