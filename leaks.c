#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    while (1)
    {
        system("leaks -q minishell");
        sleep (1);
    }
}
