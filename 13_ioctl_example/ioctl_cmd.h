#ifndef IOCTL_CMD_H
#define IOCTL_CMD_H

#include <linux/ioctl.h>

#define WR_VALUE _IOW('a', 'a', int32_t *)
#define RD_VALUE _IOR('a', 'b', int32_t *)

#endif
