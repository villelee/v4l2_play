/**
 * File Name:
 *      example.c
 * Description:
 *      This file shows how to get all the data formats
 *      supported by the v4l2 driver.
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 * Used V4L2 Infrastruct:
 *  struct:
 *      struct v4l2_fmtdesc.
 *  IO Control:
 *      VIDIOC_ENUM_FMT.
 *      V4L2_BUF_TYPE_VIDEO_CAPTURE. (Note: Macro for buf type)
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

struct v4l2_fmtdesc fmtdesc;

int main(void) {
    int fd, retval = 0;

    if (-1 == (fd = open(VIVI_DEV_PATH, O_RDWR, S_IWUSR))) {
        perror("Can not VIVI device!\nExit\n");
        retval = -1;
        goto error;
    }

    if (-1 == list_supported_data_fmts(fd, &fmtdesc))
        retval = -1;

error:
    if (0 < fd) {
        close(fd);
    }
    exit(retval);
}

