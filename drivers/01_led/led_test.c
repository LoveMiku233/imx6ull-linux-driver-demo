 #include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>

// led_test /dev/yk_led0 on
// led_test /dev/yk_led0 off

int main(int argc, char **argv)
{
	int fd;
	char status;

	if (argc != 3) {
		printf("Usage: %s <dev> <on|off>\n", argv[0]);
		printf(" eg. %s /dev/yk_led0 on\n", argv[0]);
		return -1;
	}
	// open
	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		printf("can not open %s\n", argv[1]);
		return -1;
	}
	// write
	if (strcmp(argv[2], "on" ) == 0) {
		status = 1;
		printf("led on\n");
	} else if (strcmp(argv[2], "off") == 0) {
		status = 0;
		printf("led off\n");
	} else {
		printf("error param!\n");
		return -1; 
	}
	
	write(fd, &status, 1);
	return 0;
}
