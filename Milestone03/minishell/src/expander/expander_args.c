/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:40:58 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/26 13:54:29 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**build_new_args(char **args, char **split, int i, int num_words)
{
	char	**new_args;
	int		len;
	int		j;

	len = 0;
	while (args[len])
		len++;
	new_args = malloc(sizeof(char *) * (len + num_words + 1));
	if (! new_args)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_args[j] = args[j];
		j++;
	}
	j = 0;
	while (j < num_words)
	{
		new_args[i + j] = ft_strdup(split[j]);
		j++;
	}
	return (new_args);
}

static void	fill_new_args_tail(char **new_args,
		char **args, int i, int num_words)
{
	int	j;
	int	len;

	len = 0;
	while (args[len])
		len++;
	j = i + 1;
	while (args[j])
	{
		new_args[j + num_words - 1] = args[j];
		j++;
	}
	new_args[len + num_words - 1] = NULL;
}

static int	check_split(char **split, char **args, int i)
{
	int	j;

	if (!split || !split[0])
	{
		free_str_array(split);
		free(args[i]);
		j = i;
		while (args[j + 1])
		{
			args[j] = args[j + 1];
			j++;
		}
		args[j] = NULL;
		return (0);
	}
	return (1);
}

static int	handle_no_quote(char ***args, int *i, char *exp)
{
	char	**split;
	char	**new_args;
	int		num_words;

	split = ft_split(exp, ' ');
	free(exp);
	if (!check_split(split, *args, *i))
		return (0);
	num_words = 0;
	while (split[num_words])
		num_words++;
	new_args = build_new_args(*args, split, *i, num_words);
	if (!new_args)
	{
		free_str_array(split);
		return (1);
	}
	fill_new_args_tail(new_args, *args, *i, num_words);
	free((*args)[*i]);
	free(*args);
	*args = new_args;
	free_str_array(split);
	*i += num_words;
	return (0);
}

int	expander_args(char ***args, int *args_quoted, t_exec *env)
{
	int		i;
	char	*exp;

	i = 0;
	while (*args && (*args)[i])
	{
		exp = expander_all((*args)[i], env);
		if (!exp)
		{
			error_msg("Expander", NULL, "failed to expand argument");
			return (1);
		}
		if (args_quoted[i] == NO_QUOTE)
		{
			if (handle_no_quote(args, &i, exp))
				return (1);
		}
		else
		{
			free((*args)[i]);
			(*args)[i] = exp;
			i++;
		}
	}
	return (0);
}
