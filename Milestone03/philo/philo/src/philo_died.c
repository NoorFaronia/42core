/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_died.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 04:54:17 by nfaronia          #+#    #+#             */
/*   Updated: 2026/06/17 14:51:44 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *philo)
{
	long	time_last_meal;
	long	time_new_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	time_last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	time_new_meal = get_time();
	if ((time_new_meal - time_last_meal) > philo->philo_state->time_to_die)
		return (1);
	return (0);
}

static int	meals_are_over(t_philo_state *philo_state)
{
	int	i;
	int	meals;

	if (philo_state->times_philo_must_eat == -1)
		return (0);
	i = 0;
	meals = 0;
	while (i < philo_state->number_of_philos)
	{
		pthread_mutex_lock(&philo_state->philos[i].meal_mutex);
		if (philo_state->philos[i].meals_eaten
			>= philo_state->times_philo_must_eat)
			meals++ ;
		pthread_mutex_unlock(&philo_state->philos[i].meal_mutex);
		i++;
	}
	if (meals == philo_state->number_of_philos)
		return (1);
	return (0);
}

static void	death_lock(t_philo_state *philo_state)
{
	pthread_mutex_lock(&philo_state->death_mutex);
	philo_state->sim_stop = 1;
	pthread_mutex_unlock(&philo_state->death_mutex);
}

void	*philo_died(void *arg)
{
	t_philo_state	*philo_state;
	int				i;

	philo_state = (t_philo_state *)arg;
	while (!is_sim_stop(philo_state))
	{
		i = 0;
		while (i < philo_state->number_of_philos)
		{
			if (is_dead(&philo_state->philos[i]))
			{
				print_state(&philo_state->philos[i], "died", "\033[31m");
				death_lock(philo_state);
				return (NULL);
			}
			i++;
		}
		if (meals_are_over(philo_state))
		{
			death_lock(philo_state);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
