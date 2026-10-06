/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_assignments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 01:37:05 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/18 01:37:06 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_assignment(char *arg)
{
	int	i;

	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (arg[i] == '=');
}

int	count_leading_assignments(char **args)
{
	int	i;

	i = 0;
	while (args[i] && is_assignment(args[i]))
		i++;
	return (i);
}
