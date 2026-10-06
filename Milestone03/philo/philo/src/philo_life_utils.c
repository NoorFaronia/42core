/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 04:39:36 by nfaronia          #+#    #+#             */
/*   Updated: 2026/06/17 09:06:46 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_philo *philo, t_philo_state *philo_state, int left_fork)
{
	if (philo_state->number_of_philos == 1)
	{
		pthread_mutex_lock(&philo_state->forks[left_fork]);
		print_state(philo, "has taken a fork", "\033[36m");
		ft_usleep(philo_state->time_to_die, philo);
		pthread_mutex_unlock(&philo_state->forks[left_fork]);
		return (1);
	}
	return (0);
}

void	lock_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	lock_left_right(t_philo *philo, t_philo_state *philo_state,
		int left_fork, int right_fork)
{
	pthread_mutex_lock(&philo_state->forks[left_fork]);
	print_state(philo, "has taken a fork", "\033[36m");
	pthread_mutex_lock(&philo_state->forks[right_fork]);
	print_state(philo, "has taken a fork", "\033[36m");
}

void	lock_right_left(t_philo *philo, t_philo_state *philo_state,
		int left_fork, int right_fork)
{
	pthread_mutex_lock(&philo_state->forks[right_fork]);
	print_state(philo, "has taken a fork", "\033[36m");
	pthread_mutex_lock(&philo_state->forks[left_fork]);
	print_state(philo, "has taken a fork", "\033[36m");
}

int	is_sim_stop(t_philo_state *philo_state)
{
	int	stop;

	pthread_mutex_lock(&philo_state->death_mutex);
	stop = philo_state->sim_stop;
	pthread_mutex_unlock(&philo_state->death_mutex);
	return (stop);
}
