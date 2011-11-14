/**
 * File Name:
 *      example.c
 * Description:
 *      This file shows how to query ctrls in a specified control class.
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 * Used V4L2 Infrastruct:
 *  struct:
 *      struct v4l2_queryctrl.
 *  IO Control:
 *      VIDIOC_QUERYCTRL.
 *      V4L2_CTRL_ID2CLASS.
 *      V4L2_CTRL_FLAG_NEXT_CTRL. (Note: Macro)
 *      V4L2_CTRL_CLASS_MPEG. (Note: Macro for MPEG Class)
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

    /* only for test, so make class V4L2_CTRL_CLASS_MPEG */
    if (-1 == get_ctrls_in_class(fd, &qctrl, (int)V4L2_CTRL_ID2CLASS(V4L2_CID_CAMERA_CLASS)))
        retval = -1;

error:
    if (0 < fd) {
        close(fd);
    }
    exit(retval);
}

