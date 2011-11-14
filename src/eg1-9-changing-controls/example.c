/**
 * File Name:
 *      example.c
 * Description:
 *      This file shows how to set v4l2 control value.
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 * Used V4L2 Infrastruct:
 *  struct:
 *      struct v4l2_queryctrl.
 *      struct v4l2_control.
 *  IO Control:
 *      V4L2_CID_G_CTRL.
 *      V4L2_CID_S_CTRL.
 *      V4L2_CID_QUERYCTRL.
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

struct v4l2_queryctrl qctrl;
struct v4l2_control ctrl;

int main(void) {
    int fd, retval = 0;

    if (-1 == (fd = open(VIVI_DEV_PATH, O_RDWR, S_IWUSR))) {
        perror("Can not VIVI device!\nExit\n");
        retval = -1;
        goto error;
    }

    /* just an example */
    qctrl.id = V4L2_CID_BRIGHTNESS;
    if (-1 == set_ctrl_val(fd, &qctrl, &ctrl, 2)) {
        perror("Set value fails\n");
        retval = -1;
    }
    printf("Sucessfully set value!\n");

error:
    if (0 < fd) {
        close(fd);
    }
    exit(retval);
}

