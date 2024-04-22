/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:09:20 by bohlee            #+#    #+#             */
/*   Updated: 2023/05/27 12:40:24 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

static void	ft_make_char(int bit)
{
	static char	charactor;
	static int	bit_stack;

	bit_stack++;
	charactor = charactor << 1;
	if (bit == SIGUSR1)
		charactor++;
	if (bit_stack == 8)
	{
		ft_put_char(&charactor);
		bit_stack = 0;
		charactor = 0;
	}
}

static void	ft_sigusr1_handler(int sig)
{
	ft_make_char(sig);
}

static void	ft_sigusr2_handler(int sig)
{
	ft_make_char(sig);
}

int	main(void)
{
	signal(SIGUSR1, ft_sigusr1_handler);
	signal(SIGUSR2, ft_sigusr2_handler);
	if (ft_printf("PID : %d\n", getpid()) < 0)
		return (ft_printf("ERROR : failed write PID\n."));
	while (1)
		sleep(1);
	return (0);
}
