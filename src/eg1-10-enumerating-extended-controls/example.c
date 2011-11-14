/**
 * File Name:
 *      example.c
 * Description:
 *      This file shows how to query extended control.
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 * Used V4L2 Infrastruct:
 *  struct:
 *      struct v4l2_queryctrl.
 *  IO Control:
 *      VIDIOC_QUERYCTRL.
 *      V4L2_CTRL_ID2CLASS.(Note: Macro to get Class value from control ID)
 *      V4L2_CTRL_FLAG_NEXT_CTRL.
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

struct v4l2_queryctrl qctrl;

int main(void) {
    int fd, retval = 0;

    if (-1 == (fd = open(VIVI_DEV_PATH, O_RDWR, S_IWUSR))) {
        perror("Can not VIVI device!\nExit\n");
        retval = -1;
        goto error;
    }

    if (-1 == enum_extended_ctrl(fd, &qctrl)) {
        retval = -1;
    }

error:
    if (0 < fd) {
        close(fd);
    }
    exit(retval);
}

