/**
 * File Name:
 *      example.c
 * Description:
 *      This file shows how to set audio input.
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 * Used V4L2 Infrastruct:
 *  struct:
 *      struct v4l2_audio.
 *  IO Control:
 *      VIDIOC_S_AUDIO
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

struct v4l2_audio audio;

int main(void) {
    int fd, index = -1, num = 0, errno = 0;

    if (-1 == (fd = open(VIVI_DEV_PATH, O_RDWR, S_IWUSR))) {
        perror("Can not VIVI device!\nExit\n");
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
    audio.index = index;

    if (-1 == switch_to_input(fd, &audio)) {
        errno = -1;
    }

error:
    if (0 < fd) {
        close(fd);
    }
    exit(errno);
}

