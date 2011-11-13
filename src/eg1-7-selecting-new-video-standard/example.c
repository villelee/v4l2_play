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
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

#include "../include/v4l2-util.h"

struct v4l2_standard std;
v4l2_std_id std_id;

int main(void) {
    int fd, errno = 0;

    if (-1 == (fd = open(VIVI_DEV_PATH, O_RDWR, S_IWUSR))) {
        perror("Can not VIVI device!\nExit\n");
        errno = -1;
        goto error;
    }

    if (-1 == list_supported_video_stds(fd, &std)) {
        errno = -1;
        goto error;
    }
    printf("Please input new video id value:");
    scanf("%llu", &std_id);
    errno = switch_to_new_std(fd, &std_id);


error:
    if (0 < fd) {
        close(fd);
    }
    exit(errno);
}

