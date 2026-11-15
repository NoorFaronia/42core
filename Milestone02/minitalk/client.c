/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:52:31 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/17 12:48:22 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

volatile sig_atomic_t	g_ack = 0;

int	error(char *msg)
{
	ft_printf("Error : %s\n", msg);
	exit (1);
}

void	ack_handler(int sig)
{
	(void)sig;
	g_ack = 1;
}

void	client_to_server(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
		{
			if (kill(pid, SIGUSR2) != 0)
				error("In transmission");
		}
		else
		{
			if (kill(pid, SIGUSR1) != 0)
				error("In transmission");
		}
		while (!g_ack)
			pause();
		g_ack = 0;
		i--;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	int		i;

	signal(SIGUSR1, ack_handler);
	if (argc != 3)
		error("invalid input\nUsage : ./client <PID> <MESSAGE>\n");
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		error("invalid PID\n");
	i = 0;
	while (argv[2][i])
	{
		client_to_server(pid, argv[2][i]);
		i++;
	}
	client_to_server(pid, '\0');
	return (0);
}
