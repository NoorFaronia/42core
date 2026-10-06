/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 01:36:43 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/18 01:36:44 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_cmd *commands)
{
	t_cmd	*current;
	int		count;

	count = 0;
	current = commands;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	close_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	free_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

static void	cleanup_pipes(int **pipes, int count)
{
	close_pipes(pipes, count);
	free_pipes(pipes, count);
}

int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * count);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			cleanup_pipes(pipes, i);
			return (NULL);
		}
		if (pipe(pipes[i]) < 0)
		{
			free(pipes[i]);
			cleanup_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
