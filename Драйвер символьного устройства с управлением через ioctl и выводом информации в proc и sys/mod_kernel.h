#ifndef CUSTOM_DEVICE_H
#define CUSTOM_DEVICE_H

#include <linux/ioctl.h>

#define DEVICE_NAME "custom_device"
#define CLASS_NAME "custom"

#define IOCTL_SET_STATE _IOW('k', 1, int)
#define IOCTL_GET_STATE _IOR('k', 2, int)

#endif // CUSTOM_DEVICE_H
