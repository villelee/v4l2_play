/**
 * File Name:
 *      example.c
 * Description:
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 * Used V4L2 Infrastruct:
 *  struct:
 *      struct v4l2_format.
 *      struct v4l2_pix_format.
 *      enum v4l2_buf_type
 *  IO Control:
 *      VIDIOC_TRY_FMT.
 *      VIDIOC_G_FMT.
 *      VIDIOC_S_FMT.
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

struct v4l2_format fmt;

int main(void) {
    int fd, retval = 0;

    if (-1 == (fd = open(VIVI_DEV_PATH, O_RDWR, S_IWUSR))) {
        perror("Can not VIVI device!\nExit\n");
        retval = -1;
        goto error;
    }

    /* main function */
    /* get current fmt as a template */
    retval = ioctl(fd, VIDIOC_G_FMT, &fmt);
    if (-1 == retval) {
        /* Can not get info from driver, initalize it */
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
        retval = 0;
    }
    fmt.fmt.pix.width = 176;
    fmt.fmt.pix.height = 144;

    if (-1 == set_data_fmt(fd, &fmt)) {
        retval = -1;
    }

error:
    if (0 < fd) {
        close(fd);
    }
    exit(retval);
}

