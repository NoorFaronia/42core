/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 09:51:02 by nfaronia          #+#    #+#             */
/*   Updated: 2026/06/17 14:48:03 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	add_philo_state(int argc, char **argv, t_philo_state *philo_state)
{
	if (argc < 5 || argc > 6)
	{
		error_msg("The correct input : ./philo num_philo time_to_die"
			"time_to_eat time_to_sleep [times_philo_must_eat]");
		return (1);
	}
	philo_state->number_of_philos = ft_atoi(argv[1]);
	philo_state->time_to_die = ft_atoi(argv[2]);
	philo_state->time_to_eat = ft_atoi(argv[3]);
	philo_state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_state->times_philo_must_eat = ft_atoi(argv[5]);
	else
		philo_state->times_philo_must_eat = -1;
	philo_state->sim_stop = 0;
	philo_state->start_time = 0;
	philo_state->forks = NULL;
	philo_state->philos = NULL;
	if (philo_state->number_of_philos <= 0 || philo_state->time_to_die <= 0
		|| philo_state->time_to_eat <= 0 || philo_state->time_to_sleep <= 0)
	{
		error_msg("Invalid arguments");
		return (1);
	}
	return (0);
}

int	init_fork(t_philo_state *philo_state)
{
	int		i;

	philo_state->forks = malloc(sizeof(pthread_mutex_t)
			* philo_state->number_of_philos);
	if (!philo_state->forks)
		return (1);
	i = 0;
	while (i < philo_state->number_of_philos)
	{
		pthread_mutex_init(&philo_state->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo_state->print_mutex, NULL);
	pthread_mutex_init(&philo_state->death_mutex, NULL);
	return (0);
}

int	init_philo(t_philo_state *philo_state)
{
	int		i;

	i = 0;
	philo_state->philos = malloc(sizeof(t_philo)
			* philo_state->number_of_philos);
	if (!philo_state->philos)
		return (1);
	while (i < philo_state->number_of_philos)
	{
		philo_state->philos[i].id = i + 1;
		philo_state->philos[i].meals_eaten = 0;
		philo_state->philos[i].last_meal_time = 0;
		philo_state->philos[i].philo_state = philo_state;
		pthread_mutex_init(&philo_state->philos[i].meal_mutex, NULL);
		i++;
	}
	return (0);
}

int	init_all(int argc, char **argv, t_philo_state *philo_state)
{
	if (valid_value(argc, argv))
	{
		error_msg("Invalid arguments");
		return (1);
	}
	if (add_philo_state(argc, argv, philo_state))
		return (1);
	if (init_fork(philo_state))
		return (1);
	if (init_philo(philo_state))
		return (1);
	philo_state->start_time = get_time();
	return (0);
}
