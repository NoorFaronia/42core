/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:17:17 by nfaronia          #+#    #+#             */
/*   Updated: 2026/06/17 14:46:51 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

static void	free_philo(t_philo_state *philo_state)
{
	int	i;

	i = 0;
	while (i < philo_state->number_of_philos)
	{
		pthread_mutex_destroy(&philo_state->forks[i]);
		pthread_mutex_destroy(&philo_state->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&philo_state->print_mutex);
	pthread_mutex_destroy(&philo_state->death_mutex);
	free(philo_state->forks);
	free(philo_state->philos);
}

int	valid_value(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

static int	creat_philos(t_philo_state *philo_state)
{
	int	i;

	i = 0;
	while (i < philo_state->number_of_philos)
	{
		philo_state->philos[i].last_meal_time = philo_state->start_time;
		if (pthread_create(&philo_state->philos[i].philo, NULL,
				philo_life, &philo_state->philos[i]) != 0)
		{
			error_msg("Faild to creat philosopher thread");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_state	philo_state;
	pthread_t		monitor;
	int				i;

	if (init_all(argc, argv, &philo_state))
		return (1);
	if (creat_philos(&philo_state))
		return (1);
	if (pthread_create(&monitor, NULL, philo_died, &philo_state) != 0)
	{
		error_msg("Faild to creat monitor thread");
		return (1);
	}
	i = 0;
	while (i < philo_state.number_of_philos)
	{
		pthread_join(philo_state.philos[i].philo, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	free_philo(&philo_state);
	return (0);
}
