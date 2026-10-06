/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 10:31:55 by nfaronia          #+#    #+#             */
/*   Updated: 2026/06/17 15:37:11 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philo *philo)
{
	print_state(philo, "is thinking", "\033[35m");
	ft_usleep(1, philo);
}

static void	philo_eat(t_philo *philo, t_philo_state *philo_state)
{
	int		left_fork;
	int		right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo_state->number_of_philos;
	if (one_philo(philo, philo_state, left_fork))
		return ;
	if (left_fork < right_fork)
		lock_left_right(philo, philo_state, left_fork, right_fork);
	else
		lock_right_left(philo, philo_state, left_fork, right_fork);
	lock_meal(philo);
	print_state(philo, "is eating", "\033[32m");
	ft_usleep(philo_state->time_to_eat, philo);
	pthread_mutex_unlock(&philo_state->forks[left_fork]);
	pthread_mutex_unlock(&philo_state->forks[right_fork]);
}

static void	philo_sleep(t_philo *philo, t_philo_state *philo_state)
{
	print_state(philo, "is sleeping", "\033[34m");
	ft_usleep(philo_state->time_to_sleep, philo);
}

void	*philo_life(void *arg)
{
	t_philo			*philo;
	t_philo_state	*philo_state;

	philo = (t_philo *)arg;
	philo_state = philo->philo_state;
	if (philo->id % 2 == 0)
		ft_usleep(philo_state->time_to_eat / 2, philo);
	while (!is_sim_stop(philo_state))
	{
		philo_think(philo);
		if (is_sim_stop(philo_state))
			break ;
		philo_eat(philo, philo_state);
		if (is_sim_stop(philo_state))
			break ;
		philo_sleep(philo, philo_state);
	}
	return (NULL);
}
