#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define P_READ  0
#define P_WRITE 1

void    child(int *fd, int idx)
{
    int read_ret;
    char line[2];

    if (idx == 0)
    {
        close(fd[P_READ]);
        printf("process = %d, connect %d to %d\n", idx, STDOUT_FILENO, fd[P_WRITE]);
        dup2(fd[P_WRITE], STDOUT_FILENO);
        close(fd[P_WRITE]);
    }
    else
    {
        printf("process = %d, connect %d to %d\n", idx, STDIN_FILENO, fd[P_READ]);
        close(fd[P_WRITE]);
        dup2(fd[P_READ], STDIN_FILENO);
        close(fd[P_READ]);
    }

    if (idx == 0)
        write(STDOUT_FILENO, "hello", 6);
    else
    {
        printf("\nprocess = %d, reading in %d\n", idx, STDIN_FILENO);
        while (1)
        {
            read_ret = read(STDIN_FILENO, line, 1);
            if (read_ret != 1)
            {
                printf("\n");
                break ;
            }
            line[1] = '\0';
            printf("%s", line);
        }
    }
    exit(GENERAL_EXIT_CODE);
}

int main(void)
{
    int     fd[2];
    pid_t   pid[2];
    int     idx;

    if (pipe(fd) == -1)
		return (1);
    idx = 0;
    while (idx < 2)
    {
        pid[idx] = fork();
        if (pid[idx] == -1)
            return (1);
        else if (pid[idx] == 0)
            child(fd, idx);
        idx++;
    }
    close(fd[P_READ]);
    close(fd[P_WRITE]);
    return (0);
}