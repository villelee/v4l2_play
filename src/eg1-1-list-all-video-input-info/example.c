/**
 * File Name:
 *      eg1-1-current-video-input.c
 * Description:
 *      This file just gives an example of how to get
 *      information of current video inputs.
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 * Used V4L2 Infrastruct:
 *  struct:
 *      struct v4l2_input;
 *  IO Control:
 *      VIDIOC_G_INPUT;
 *      VIDIOC_S_INPUT;
 *      VIDIOC_ENUMINPUT;
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

char msg[MSG_LENGTH];

int main(void) {
    struct v4l2_input input;
    int fd, index = -1, errno = 0;

    if (-1 == (fd = open(VIVI_DEV_PATH, O_RDWR, S_IWUSR))) {
        snprintf(msg, (MSG_LENGTH - 1),"Can not open the VIVI virtual video device!\nExit\n");
        errno = -1;
        goto error;
    }

    if (-1 == (ioctl(fd, VIDIOC_G_INPUT, &index))) {
        snprintf(msg, (MSG_LENGTH - 1), "Do not support VIDIOC_G_INPUT\n");
        errno = -1;
        goto error;
    }

    printf("Input Information as following:\n");
    while (-1 != query_cur_input_info(fd, &input, index, msg)) {
        printf("%s\n", msg);
        index++;
    }

    if (-1 == index) {
        /* so can not get inputs info */
        printf("%s\n", msg);
        errno = -1;
        goto error;
    }

error:
    if (0 < fd) {
        close(fd);
    }
    exit(errno);
}

