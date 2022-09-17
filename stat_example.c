#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    struct stat statbuf;

    if (stat(argv[1], &statbuf) < 0) {
        fprintf(stderr, "stat error\n");
		printf("errno : %d\n", errno);
        exit(1);
    }
    // statbuf.st_size = 파일의 크기
    printf("%s %lld bytes\n", argv[1], statbuf.st_size);
	printf("errno : %d\n", errno);
    exit(0);
}
