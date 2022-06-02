#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(){
    int r;
    r = write(0,"Hello, World!\n", 14);
    if (r<0){
        perror("write hello");
	return errno;
    }
    return 0;
}
