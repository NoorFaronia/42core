/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:23:41 by nfaronia          #+#    #+#             */
/*   Updated: 2026/06/17 15:47:41 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (0);
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	p;

	p = 1;
	res = 0;
	i = 0;
	if (!is_valid(str))
		return (-1);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			p = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (p * res);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + (time.tv_usec / 1000)));
}

void	ft_usleep(long ms, t_philo *philo)
{
	long	start;
	long	elapsed_time;

	start = get_time();
	while (1)
	{
		if (is_sim_stop(philo->philo_state))
			break ;
		elapsed_time = get_time() - start;
		if (elapsed_time >= ms)
			break ;
		if (ms - elapsed_time > 1)
			usleep(500);
		else
			usleep(100);
	}
}

void	print_state(t_philo *philo, char *state, char *color)
{
	long	time;

	time = get_time() - philo->philo_state->start_time;
	pthread_mutex_lock(&philo->philo_state->print_mutex);
	if (!is_sim_stop(philo->philo_state))
		printf("%s%ld %d %s\n", color, time, philo->id, state);
	pthread_mutex_unlock(&philo->philo_state->print_mutex);
}
