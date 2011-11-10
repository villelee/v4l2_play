/**
 * File Name:
 *      example.c
 * Description:
 *      This file just give an example of how to
 *      change the input of video capture device
 *      to another by a prescribed index number.
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 * Used V4L2 Infrastruct:
 *  struct:
 *      None
 *  IO Control:
 *      VIDIOC_S_INPUT;
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

int main(void) {
    int fd, index = -1, num = 0, errno = 0;

    if (-1 == (fd = open(VIVI_DEV_PATH, O_RDWR, S_IWUSR))) {
        perror("Can not open VIVI device!\nExit\n");
        errno = -1;
        goto error;
    }

    /* set index to a value */
    while ((0 > index) || (81 < index)) {
        printf("Please enter the index value[0 ... 81]: ");
        scanf("%d", &index);
        if (10 < (++num)) {
            errno = -1;
            perror("Invalid index number!\n");
            break;
        }
    }

    if (10 >= num) {
        errno = change_input_by_idx(fd, &index);
        if (-1 == errno) {
            printf("Can not change input of VIVI to Input[%d]\n", index);
            goto error;
        }
    }

    /* To make sure get real input index of VIVI */
    index = -1;
    if (-1 == ioctl(fd, VIDIOC_G_INPUT, &index)) {
        errno = -1;
        perror("Can not get input index of VIVI\nExit\n");
    }
    printf("Success set input to Input[%d]\n", index);

error:
    if (0 < fd) {
        close(fd);
    }
    exit(errno);
}

