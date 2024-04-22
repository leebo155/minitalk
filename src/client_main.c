/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:32:39 by bohlee            #+#    #+#             */
/*   Updated: 2023/05/27 13:15:10 by bohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_sent_bit(int pid, int bit)
{
	int	status;

	if (bit)
		status = kill(pid, SIGUSR1);
	else
		status = kill(pid, SIGUSR2);
	if (status < 0)
	{
		ft_printf("ERROR : failed sending signal.\n");
		exit (1);
	}
}

static void	ft_sent_char(int pid, unsigned char charactor)
{
	static int	bit_stack;

	while (bit_stack < 8)
	{
		bit_stack++;
		if (charactor > 127)
			ft_sent_bit(pid, 1);
		else
			ft_sent_bit(pid, 0);
		charactor = charactor << 1;
		usleep(48);
	}
	bit_stack = 0;
}

int	main(int argc, char *argv[])
{
	int		pid;
	size_t	index;

	if (argc - 1 != 2)
		return (ft_printf("ERROR : client must have two arguments.\n"));
	pid = ft_atoi(argv[1]);
	index = 0;
	while (argv[2][index])
	{
		ft_sent_char(pid, argv[2][index]);
		index++;
	}
	return (0);
}
