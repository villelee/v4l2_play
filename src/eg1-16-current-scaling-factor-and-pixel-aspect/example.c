/**
 * File Name:
 *      example.c
 * Description:
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 * Used V4L2 Infrastruct:
 *  struct:
 *  IO Control:
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
double hscale;
double vscale;
double paspect;

int main(void) {
    int fd, retval = 0;
    double tmp;

    if (-1 == (fd = open(VIVI_DEV_PATH, O_RDWR, S_IWUSR))) {
        perror("Can not VIVI device!\nExit\n");
        retval = -1;
        goto error;
    }

    /* get cropcap */
    ccap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == get_cropcap_info(fd, &ccap)) {
        perror("Can not get cropcap\n");
        retval = -1;
        goto error;
    }
    /* get crop */
    crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == get_crop(fd, &crop)) {
        perror("Can not get crop\n");
        retval = -1;
        goto error;
    }
    /* get data format */
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == get_data_fmt(fd, &fmt)) {
        retval = -1;
        goto error;
    }

    /* calculate factors */
    hscale = fmt.fmt.pix.width / (double)crop.c.width;
    vscale = fmt.fmt.pix.height / (double)crop.c.height;
    /**
     * pixel aspect of source.
     * pixel aspect = horizational number of pixel / vertical number of pixel.
     */
    tmp = ccap.pixelaspect.numerator / 
                (double)ccap.pixelaspect.denominator;
    paspect = tmp * (hscale / vscale);

    printf("Pixel Aspect is %lf\n", paspect);

error:
    if (0 < fd) {
        close(fd);
    }
    exit(retval);
}

