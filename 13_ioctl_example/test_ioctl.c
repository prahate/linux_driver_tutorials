#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/fcntl.h>

#include "ioctl_cmd.h"

int main(int argc, char **argv)
{
	int fd;

	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		perror("Open");
		return -1;
	}

	int32_t value;

	ioctl(fd, RD_VALUE, (int32_t *)&value);
	printf("Read value is %d\n", value);

	value = 233;
	printf("Writing value %d\n", value);
	ioctl(fd, WR_VALUE, (int32_t *)&value);
	
	ioctl(fd, RD_VALUE, (int32_t *)&value);
	printf("Read value is %d\n", value);

	close(fd);
	return 0;
}
