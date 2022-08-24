#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

static void	sig_handler(int signo, siginfo_t *sig_info, void *uc)
{
	printf("signal = %d\n", signo);
	(void)uc;
}
int	main(void)
{
	struct sigaction	sig_struct;
	sigset_t			sig_mask;

	sigemptyset(&sig_mask);
	sigaddset(&sig_mask, SIGTERM);
	sigaddset(&sig_mask, SIGINT);
	sigaddset(&sig_mask, SIGQUIT);
	sigaddset(&sig_mask, SIGTTIN);
	sigaddset(&sig_mask, SIGTTOU);
	sigaddset(&sig_mask, SIGTSTP);
	sigaddset(&sig_mask, SIGHUP);
	sig_struct.sa_sigaction = sig_handler;
	sig_struct.sa_flags = SA_SIGINFO;
	sig_struct.sa_mask = sig_mask;
	sigaction(SIGTERM, &sig_struct, NULL);
	sigaction(SIGINT, &sig_struct, NULL);
	sigaction(SIGQUIT, &sig_struct, NULL);
	sigaction(SIGTTIN, &sig_struct, NULL);
	sigaction(SIGTTOU, &sig_struct, NULL);
	sigaction(SIGTSTP, &sig_struct, NULL);
	sigaction(SIGHUP, &sig_struct, NULL);
	while(true)
		;
	return (0);
}
