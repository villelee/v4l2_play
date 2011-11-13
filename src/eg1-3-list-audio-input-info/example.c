/**
 * File Name:
 *      example.c
 * Description:
 *      This file is an example showing how to
 *      get information of v4l2 audio device inputs.
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 * Used V4L2 Infrastruct:
 *  struct:
 *      struct v4l2_audio
 *  IO Control:
 *      VIDIOC_G_AUDIO
 *      VIDIOC_ENUMAUDIO
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
    int fd, errno = 0;

    if (-1 == (fd = open(VIVI_DEV_PATH, O_RDWR, S_IWUSR))) {
        perror("Can not VIVI device!\nExit\n");
        errno = -1;
        goto error;
    }

    if (-1 == current_audio_input_info(fd, &audio)) {
        errno = -1;
        perror("Can not get audio input info\n");
        goto error;
    }
    memset(&audio, 0, sizeof(struct v4l2_audio));

    if (-1 == list_audio_input_info(fd)) { 
        errno = -1;
        perror("Can not get audio input info\n");
    }

error:
    if (0 < fd) {
        close(fd);
    }
    exit(errno);
}

