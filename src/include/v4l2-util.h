/**
 * File Name:
 *      v4l2_util.h
 * Description:
 *      This file supply other egXXX.c with function support.
 * Author:
 *      ville lee   <villelee1987@gmail.com>
 */
#ifndef __V4L2_UTIL_H__
#define __V4L2_UTIL_H__

#include <stdio.h>
#include <string.h>
#include <linux/videodev2.h>

#define MSG_LENGTH  128
#define VIVI_DEV_PATH    "/dev/video0"

/**
 * Param:
 *      fd:  file descriptor.
 *      input:  mainly used v4l2 infrastrure.
 *      index:  the index number of the current input.
 *      msg:    message including either input device info
 *              or error message.
 * Return:
 *      error number:   -1 if fail; 0 if success.
 */
int query_cur_input_info(int fd, struct v4l2_input *input, int index, char *msg) {
    /**
     * FIXME: 
     *      should make sure the params are valid.
     **/
    memset(msg, 0, MSG_LENGTH);
    memset(input, 0, sizeof(struct v4l2_input));
    input->index = index;
    
    if (-1 == ioctl(fd, VIDIOC_ENUMINPUT, input)) {
        snprintf(msg, (MSG_LENGTH - 1), "Can not get info about input[%d]\n", index);
        return -1;
    }

    snprintf(msg, (MSG_LENGTH - 1), "Input Index: %d\nInput Name: %s\n", input->index, input->name);
    return 0;
}

/**
 * Param:
 *      fd: file descriptor.
 *      index: index number of input to set.
 * Return:
 *      error number:   -1 if fail; 0 if success
 */
int change_input_by_idx(int fd, int *index) {
    /**
     * @FIXME:
     *      should check if the params are valid.
     */
    if (-1 == (ioctl(fd, VIDIOC_S_INPUT, index))) {
        printf("Can not set input to Input[%d]\n", *index);
        return -1;
    }

    return 0;
}

#endif
