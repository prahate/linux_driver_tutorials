#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd;

	if( argc < 2) {
		printf("Usage: %s <device_file>\n", argv[0]);
		return 0;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}
	
	close(fd);
	
	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		perror("open");
		return -1;
	}
	
	close(fd);


	return 0;
}
