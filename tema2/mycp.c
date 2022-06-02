#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int fd1, fd2, r;
    char *buf = malloc(1000);
    fd1 = open(argv[1], O_RDONLY);
    if (fd1<0){
        perror("opening first file");
	return errno;
    }
    fd2 = open(argv[2], O_WRONLY);
    if (fd2<0){
	perror("opening second file");
	return errno;
    }
    r = read(fd1, buf, 1000);
    if (r<0){
	perror("reading first file");
	return errno;
    }
    r = write(fd2, buf, 1000);
    if (r<0){
	perror("writing second file");
	return errno;
    }
    return 0;
}
