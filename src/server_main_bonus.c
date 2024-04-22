/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:20:55 by bohlee            #+#    #+#             */
/*   Updated: 2023/05/27 13:26:47 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_wait;

static void	ft_put_char(char *charactor)
{
	int	length;

	length = write(1, charactor, 1);
	if (length < 0)
	{
		ft_printf("ERROR : failed write char.\n");
		exit(1);
	}
}

static void	ft_make_char(int sig, int pid, int retry_flag)
{
	static char	charactor;
	static int	bit_stack;
	static int	org_pid;

	g_wait = 0;
	if (retry_flag)
	{	
		kill(org_pid, sig);
		return ;
	}
	org_pid = pid;
	bit_stack++;
	charactor = charactor << 1;
	if (sig == SIGUSR1)
		charactor++;
	if (bit_stack == 8)
	{
		ft_put_char(&charactor);
		bit_stack = 0;
		charactor = 0;
	}
	kill(pid, SIGUSR1);
}

static void	ft_sigusr_handler(int sig, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (siginfo->si_pid <= 100)
	{
		ft_make_char(SIGUSR2, 0, 1);
		return ;
	}
	ft_make_char(sig, siginfo->si_pid, 0);
}

static void	ft_waiting_signal(void)
{
	static int	is_not_first;
	static int	no_feedback;

	if (is_not_first)
	{
		while (g_wait < 50)
		{
			usleep(1);
			g_wait++;
		}
		ft_make_char(SIGUSR1, 0, 1);
		no_feedback++;
		if (no_feedback > 100)
		{
			is_not_first--;
			no_feedback = 0;
		}
	}
	else
	{
		is_not_first++;
		pause();
	}	
}

int	main(void)
{
	struct sigaction	act_usr1;
	struct sigaction	act_usr2;

	act_usr1.sa_flags = SA_SIGINFO;
	act_usr2.sa_flags = SA_SIGINFO;
	act_usr1.sa_sigaction = ft_sigusr_handler;
	act_usr2.sa_sigaction = ft_sigusr_handler;
	sigemptyset(&(act_usr1.sa_mask));
	sigemptyset(&(act_usr2.sa_mask));
	sigaddset(&(act_usr1.sa_mask), SIGUSR1);
	sigaddset(&(act_usr1.sa_mask), SIGUSR2);
	sigaddset(&(act_usr2.sa_mask), SIGUSR1);
	sigaddset(&(act_usr2.sa_mask), SIGUSR2);
	if (sigaction(SIGUSR1, &act_usr1, 0) < 0)
		return (ft_printf("ERROR : sigaction error SIGUSR1.\n"));
	if (sigaction(SIGUSR2, &act_usr2, 0) < 0)
		return (ft_printf("ERROR : sigaction error SIGUSR2.\n"));
	if (ft_printf("PID : %d\n", getpid()) < 0)
		return (ft_printf("ERROR : failed write PID.\n"));
	while (1)
		ft_waiting_signal();
	return (0);
}
