/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:09:28 by nfaronia          #+#    #+#             */
/*   Updated: 2026/06/17 14:41:55 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo	t_philo;

// philo state struct
typedef struct s_philo_state
{
	int				number_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				times_philo_must_eat;
	long			start_time;
	int				sim_stop;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_philo_state;

// philo struct
typedef struct s_philo
{
	int						id;
	pthread_t				philo;
	int						meals_eaten;
	long					last_meal_time;
	pthread_mutex_t			meal_mutex;
	t_philo_state			*philo_state;
}	t_philo;

// main.c
void	error_msg(char *msg);
int		valid_value(int argc, char **argv);

// utils.c ok
int		ft_atoi(const char *str);
long	get_time(void);
void	ft_usleep(long ms, t_philo *philo);
void	print_state(t_philo *philo, char *state, char *color);

// initializing.c ok
int		add_philo_state(int argc, char **argv, t_philo_state *philo_state);
int		init_philo(t_philo_state *philo_state);
int		init_fork(t_philo_state *philo_state);
int		init_all(int argc, char **argv, t_philo_state *philo_state);

// philo_life.c
void	*philo_life(void *arg);

// philo_life_utils.c
int		one_philo(t_philo *philo, t_philo_state *philo_state, int left_fork);
void	lock_meal(t_philo *philo);
void	lock_left_right(t_philo *philo, t_philo_state *philo_state,
			int left_fork, int right_fork);
void	lock_right_left(t_philo *philo, t_philo_state *philo_state,
			int left_fork, int right_fork);
int		is_sim_stop(t_philo_state *philo_state);

// philo_died.c
void	*philo_died(void *arg);

#endif