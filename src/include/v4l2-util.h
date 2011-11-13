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

/**
 * Params:
 *      fd:
 *      audio: main struct in v4l2 for audio
 * Return Value:
 *      -1 if fails; 0 if success
 */
int current_audio_input_info(int fd, struct v4l2_audio *audio) {
    /**
     * FIXME:
     *      Should check if params are valid.
     */
    if (-1 == ioctl(fd, VIDIOC_G_AUDIO, audio)) {
        perror("Can not get Audio info\n");
        return -1;
    }

    printf("Audio Input[%d], name: %s\n", audio->index, audio->name);
    return 0;
}

/**
 * Params:
 *      fd:
 *      audio: main struct in v4l2 for audio
 * Return Value:
 *      -1 if fails; 0 if success
 */
int list_audio_input_info(int fd) {
    /**
     * FIXME:
     *      Should check if params are valid.
     */
    int index;
    struct v4l2_audio audio;
    audio.index = 0;
    while (-1 != ioctl(fd, VIDIOC_ENUMAUDIO, &audio)) {
        printf("Audio Input[%d], name: %s\n", audio.index, audio.name);
        index = audio.index;
        memset(&audio, 0, sizeof(struct v4l2_audio));
        audio.index = ++index;
    }

    if (0 == audio.index) {
        printf("Can not ENUM audio input\n");
        return -1;
    }

    return 0;
}

/**
 * Name:
 *      switch_to_input
 * Description:
 *      switch current input of audio device
 *      as audio.index indicated.
 * Params:
 *      fd: File description.
 *      audio: main struct in v4l2 audio.
 * Return value
 *      -1 if fails; 0 if success.
 */
int switch_to_input(int fd, struct v4l2_audio *audio)
{
    /**
     * FIXME:
     *      Should check if params are valid.
     */
    if (-1 == ioctl(fd, VIDIOC_S_AUDIO, audio)) {
        printf("Can not switch input to input[%d]\n", audio->index);
        return -1;
    }

    return 0;
}

/**
 * Name:
 *      get_current_input_std_info
 * Description:
 *     get infomation about the currntly used video standsrd 
 *     of current input.
 * Params:
 *      fd: file descriptor.
 *      std: v4l2 standard.
 *      std_id: v4l2 video standard id.
 * Return value:
 *      -1 on fail while 0 on success.
 */
int get_current_input_std_info(int fd, struct v4l2_standard *std, v4l2_std_id *std_id)
{
    /**
     * FIXME:
     *      Should check if params are valid.
     */
    if (-1 == ioctl(fd, VIDIOC_G_STD, std_id)) {
        perror("Can not get current input standard.\n");
        return -1;
    }

    memset(std, 0, sizeof(struct v4l2_standard));
    std->index = 0;

    while(0 == ioctl(fd, VIDIOC_ENUMSTD, std)) {
        if (std->id == *std_id) {
            printf("Current video standard: %s\n", std->name);
            return 0;
        }
        std->index++;
    }

    perror("Do ont support VIDIOC_ENUM\n");
    return -1;
}

/**
 * Name: list_supported_video_std.
 * Description:
 *      This function shows info of supported video 
 *      standards of a video capture input.
 * Params:
 *      fd: file descriptor.
 *      std: main struct in v4l2 standsrd.
 * Return value
 */
int list_supported_video_stds(int fd, struct v4l2_standard *std)
{
    /**
     * FIXME:
     *      Should check if params are valid.
     */
    memset(std, 0, sizeof(struct v4l2_standard));
    std->index = 0;
    printf("Supported Video Standard\n");
    while (-1 != ioctl(fd, VIDIOC_ENUMSTD, std)) {
        printf("Standard[%llu]: %s\n", std->id, std->name);
        std->index++;
    }

    if (0 == std->index) {
        perror("Can not get video standard info\n");
        return -1;
    }

    return 0;
}

/**
 * Name: switch_to_new_std.
 * Description:
 *      Switch video standard to a prescribed one.
 * Params:
 *      fd: file descriptor.
 *      id: v4l2 video standard id value.
 * Return value:
 *      -1 on fail while 0 on success.
 */
int switch_to_new_std(int fd, v4l2_std_id *id)
{
    /**
     * FIXME:
     *      Should check if params are valid.
     */
    if(-1 == ioctl(fd, VIDIOC_S_STD, id)) {
        printf("Can not switch to New Video Standard:%llu\n", *id);
        return -1;
    }

    return 0;
}
#endif
