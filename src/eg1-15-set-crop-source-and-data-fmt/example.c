/**
 * File Name:
 *      example.c
 * Description:
 *      This file shows how to get crop capability
 *      , set crop and set data format.
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 * Used V4L2 Infrastruct:
 *  struct:
 *      struct v4l2_cropcap ccap;
 *      struct v4l2_crop crop;
 *      struct v4l2_format fmt;
 *  IO Control:
 *      VIDIOC_CROPCAP.
 *      VIDIOC_G_CROP.
 *      VIDIOC_S_CROP.
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

struct v4l2_cropcap ccap;
struct v4l2_crop crop;
struct v4l2_format fmt;

int main(void) {
    int fd, retval = 0;

    if (-1 == (fd = open(VIVI_DEV_PATH, O_RDWR, S_IWUSR))) {
        perror("Can not VIVI device!\nExit\n");
        retval = -1;
        goto error;
    }

    /* query crop capability */
    if (-1 == get_cropcap_info(fd, &ccap)) {
        perror("Can not get crop capability info\n");
        retval = -1;
        goto error;
    }
    /* get crop, must set type field. */
    crop.type = ccap.type;
    if (-1 == get_crop(fd, &crop)) {
        retval = -1;
        goto error;
    }
    /* set crop */
    crop.type = ccap.type;
    crop.c.left = ccap.bounds.width / 2;
    crop.c.top = ccap.bounds.height / 2;
    crop.c.width = ccap.defrect.width / 2;
    crop.c.height = ccap.defrect.height / 2; 
    if (-1 == set_crop(fd, &crop)) {
        retval = -1;
        goto error;
    }
    printf("Successfully set crop\n");

    /* set data format */
    fmt.fmt.pix.width = crop.c.width / 2;
    fmt.fmt.pix.height = crop.c.height / 2;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    fmt.type = crop.type;
    if (-1 == set_data_fmt(fd, &fmt)) {
        retval = -1;
    }

error:
    if (0 < fd) {
        close(fd);
    }
    exit(retval);
}

