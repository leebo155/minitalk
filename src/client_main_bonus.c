/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:21:10 by bohlee            #+#    #+#             */
/*   Updated: 2023/05/27 13:47:09 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_retry_flag;

static void	ft_sent_bit(int pid, int bit)
{
	if (kill(pid, bit) < 0)
	{
		ft_printf("ERROR : failed sending signal.\n");
		exit(1);
	}
	pause();
}

static void	ft_sent_char(int pid, unsigned char charactor)
{
	static int	bit_stack;

	while (bit_stack < 8)
	{
		bit_stack++;
		if (charactor > 127)
			ft_sent_bit(pid, SIGUSR1);
		else
			ft_sent_bit(pid, SIGUSR2);
		if (g_retry_flag)
		{
			bit_stack--;
			g_retry_flag = 0;
		}
		else
			charactor = charactor << 1;
	}
	bit_stack = 0;
}

static void	ft_sigusr_handler(int sig, siginfo_t *siginfo, void *context)
{
	(void)context;
	ft_printf("%p\n", context);
	(void)siginfo;
	if (sig == SIGUSR2)
		g_retry_flag = 1;
}

int	main(int argc, char *argv[])
{
	size_t				index;
	struct sigaction	act_usr1;
	struct sigaction	act_usr2;

	if (argc - 1 != 2)
		return (ft_printf("ERROR : client must have two arguments.\n"));
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
		return (ft_printf("ERROR : sigaction error (SIGUSR1).\n"));
	if (sigaction(SIGUSR2, &act_usr2, 0) < 0)
		return (ft_printf("ERROR : sigaction error (SIGUSR2).\n"));
	index = 0;
	while (argv[2][index])
		ft_sent_char(ft_atoi(argv[1]), argv[2][index++]);
	return (0);
}
