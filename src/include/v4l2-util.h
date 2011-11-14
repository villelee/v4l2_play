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
#include <errno.h>
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

/**
 * Name: enum_all_menuitems
 * Description:
 *      This function lists all the menu items of a ioctl.
 * Params:
 *      fd: file descriptor.
 *      menu: main querymenu struct in v4l2.
 *            This indicates that this ioctrl has a menu of N choices.
 *      mini: minimum value of the menu items.
 *      max : maxmum value of the menu items.
 * Return value
 *      -1 on fail while 0 on sucess.
 */
int enum_all_menuitems(int fd, struct v4l2_querymenu *menu, int mini, int max)
{
    for (menu->index = mini; menu->index < max; menu->index++) {
        if (0 == ioctl(fd, VIDIOC_QUERYMENU, menu)) {
            printf("Menu item[%d]:%s\n", menu->index, menu->name);
        } else {
            perror("Can not query menu\n");
            return -1;
        }
    }

    return 0;
}

/**
 * Name: enum_all_controls
 * Description:
 *      This function lists all the ioctls.
 * Params:
 *      fd: file descriptor.
 *      ctrl: main queryctrl struct in v4l2.
 *      menu: main querymenu struct in v4l2.
 *            This indicates that this ioctrl has a menu of N choices.
 * Return value
 *      -1 on fail while 0 on sucess.
 */
int enum_all_controls(int fd, struct v4l2_queryctrl *ctrl, struct v4l2_querymenu *menu)
{
    /**
     * FIXME:
     *      Should check if the params are valid.
     */
    /* clear the struct */
    memset(ctrl, 0, sizeof(struct v4l2_queryctrl));
    memset(menu, 0, sizeof(struct v4l2_querymenu));

    for (ctrl->id = V4L2_CID_BASE; ctrl->id <= V4L2_CID_LASTP1; ctrl->id++) {
        if (0 == ioctl(fd, VIDIOC_QUERYCTRL, ctrl)) {
            if (ctrl->flags & V4L2_CTRL_FLAG_DISABLED) {
                continue;
            }
            printf("Current control ID: %d, Name: %s\n", ctrl->id, ctrl->name);

            if (ctrl->type & V4L2_CTRL_TYPE_MENU) {
                /* call menu */
                menu->id = ctrl->id;
                enum_all_menuitems(fd, menu, ctrl->minimum, ctrl->maximum);
            }
        } else {
            if (errno == EINVAL)
                continue;
            perror("Do not support VIDIOC_QUERYCTRL\n");
            return -1;
        }
    }

    return 0;
}

/**
 * Name: ste_ctrl_val.
 * Description:
 *      This function set value to a specified control.
 *      Users of this function must set qctrl properly first.
 * Params:
 *      fd: file descriptor.
 *      ctrl: main queryctrl struct in v4l2.
 *      ctl: main control struct in v4l2.
 * Return value:
 *      -1 on fail while 0 on success.
 */
int set_ctrl_val(int fd, struct v4l2_queryctrl *qctrl, struct v4l2_control *ctrl, int value)
{
    /**
     * FIXME:
     *      Should check if params are valid.
     */
    /* check if device support this kind of control. */
    if (-1 == ioctl(fd, VIDIOC_QUERYCTRL, qctrl)) {
        if (errno != EINVAL) {
            perror("Do not support VIDIOC_QUERYCTRL\n");
            goto error;
        } else {
            perror("Do not support this kind of control\n");
            goto error;
        }
    } else if (qctrl->flags & V4L2_CTRL_FLAG_DISABLED) {
        perror("Do not support this kind of control\n");
        goto error;
    } else {
        /* device support this kond of control. */
        memset(ctrl, 0, sizeof(struct v4l2_control));
        ctrl->id = qctrl->id;
        ctrl->value = value;
        if (-1 == ioctl(fd, VIDIOC_S_CTRL, ctrl)) {
            printf("Can not set control[%d] to value[%d]", ctrl->id, ctrl->value);
            goto error;
        }
    }

    /* check if the value is right. */
    memset(ctrl, 0, sizeof(struct v4l2_control));
    ctrl->id = qctrl->id;
    if (-1 == ioctl(fd, VIDIOC_G_CTRL, ctrl)) {
        perror("Can not get control\n");
        goto error;
    } else {
        if (value != ctrl->value) {
            perror("Set value fails\n");
            goto error;
        }
    }

    return 0;
error:
    /**
     * we could add a local flag and identify 
     * different error types, then treat 
     * each kind of them in a proper way.
     */
    return -1;
}


/**
 * Name: enum_extended_ctrl.
 * Description:
 *      This function list all the supported extended controls.
 * Params:
 *      fd: file descriptor.
 *      qctrl: main query control struct in v4l2.
 * Return value:
 *      -1 on fail while 0 on success.
 */
int enum_extended_ctrl(int fd, struct v4l2_queryctrl *qctrl)
{
    /**
     * FIXME:
     *      SHould check if params are valid.
     */
    /**
     * id is an 32 bits integer.
     * |31 ~ 28|27     ~     16|15   ~   0|
     * | Flags | Control Class |control ID|
     */
    memset(qctrl, 0, sizeof(struct v4l2_queryctrl));
    qctrl->id = V4L2_CTRL_FLAG_NEXT_CTRL;    /* to query extends controls, must set this */

    while (0 == ioctl(fd, VIDIOC_QUERYCTRL, qctrl)) {
        printf("Extended Control Name: %s \nExtended Control:[%d]  Control Class:[%d]  Control ID:[%d]\n\n",
                    qctrl->name, qctrl->id,
                    (int)V4L2_CTRL_ID2CLASS(qctrl->id), (int)(qctrl->id & 0xffff));
        qctrl->id |= V4L2_CTRL_FLAG_NEXT_CTRL;
    }

    if (qctrl->id == V4L2_CTRL_FLAG_NEXT_CTRL) {
        perror("Do not support extended control\n");
        return -1;
    }

    return 0;
}

/**
 * Name: get_ctrls_in_class.
 * Description:
 *      This function list all the supported ctrl info in specified class.
 * Params:
 *      fd: file descriptor.
 *      qctrl: main query ctrl struct in v4l2.
 *      class: specified class ID.
 * Return value:
 *      -1 on fail while 0 on success.
 */
int get_ctrls_in_class(int fd, struct v4l2_queryctrl *qctrl, int class)
{
    /**
     * FIXME:
     *      Should check if params are valid.
     */
    memset(qctrl, 0, sizeof(struct v4l2_queryctrl));
    qctrl->id = V4L2_CTRL_FLAG_NEXT_CTRL | class;

    while (0 == ioctl(fd, VIDIOC_QUERYCTRL, qctrl)) {
        if (V4L2_CTRL_ID2CLASS(qctrl->id) != class)
            break;
        else {
            printf("Extended Control Name: %s \nExtended Control:[%d]  Control Class:[%d]  Control ID:[%d]\n\n",
                        qctrl->name, qctrl->id,
                        (int)V4L2_CTRL_ID2CLASS(qctrl->id), (int)(qctrl->id & 0xffff));
            qctrl->id |= V4L2_CTRL_FLAG_NEXT_CTRL;
        }
    }

    if (V4L2_CTRL_ID2CLASS(qctrl->id) == class) {
        perror("Can not get ctrl from control class");
        return -1;
    }

    return 0;
}

#endif
