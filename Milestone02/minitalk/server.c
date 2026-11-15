/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:52:24 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/17 12:48:43 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE	199309L
#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int	error(char *msg)
{
	ft_printf("Error : %s\n", msg);
	exit (1);
}

void	add_char_to_buffer(char c, char **msg, int *len)
{
	char	*new;
	int		i;

	new = malloc(*len + 2);
	if (!new)
		error("Memory allocation failed");
	i = 0;
	while (i < *len)
	{
		new[i] = (*msg)[i];
		i++;
	}
	new[*len] = c;
	new[*len + 1] = '\0';
	free(*msg);
	*msg = new;
	(*len)++;
}

void	msg_null(char **msg, int *len)
{
	if (*msg)
		ft_printf("%s\n", *msg);
	free(*msg);
	*msg = NULL;
	*len = 0;
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	c = 0;
	static int				bit_count = 0;
	static char				*msg = NULL;
	static int				len = 0;

	(void)ucontext;
	c <<= 1;
	if (sig == SIGUSR2)
		c |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		if (c == '\0')
			msg_null(&msg, &len);
		else
			add_char_to_buffer(c, &msg, &len);
		c = 0;
		bit_count = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		return ;
}

int	main(int argc, char **argv)
{
	struct sigaction	s;

	(void)argv;
	if (argc != 1)
		error("invalid input\nUsage: ./server (no arguments required)");
	ft_printf("📱  MINITALK SERVER BONUS\n");
	ft_printf("📡 PID: %d\n", getpid());
	ft_printf("✅ Server initialized successfully.\n");
	ft_printf("⚠️ NOTE : Press Ctrl+C to exit.\n");
	ft_printf("⏳ Waiting for messages...\n\n");
	s.sa_sigaction = handler;
	s.sa_flags = SA_SIGINFO;
	sigemptyset(&s.sa_mask);
	sigaction(SIGUSR1, &s, NULL);
	sigaction(SIGUSR2, &s, NULL);
	while (1)
		pause();
	return (0);
}
