/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:07:13 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/26 11:51:02 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	error(char *str)
{
	ft_printf("Error : %s\n", str);
	exit(EXIT_FAILURE);
}

double	dot(const char *str, int i)
{
	double	res;
	double	factor;

	res = 0;
	factor = 0.1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res += (str[i] - '0') * factor;
		factor *= 0.1;
		i++;
	}
	return (res);
}

int	all_num(const char *str)
{
	int	i;
	int	num_sign;
	int	num_dot;

	i = 0;
	num_sign = 0;
	num_dot = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '.'
			&& str[i] != '-' && str[i] != '+')
			return (0);
		if (str[i] == '-' || str[i] == '+')
			num_sign++;
		if (str[i] == '.')
			num_dot++;
		i++;
	}
	if (num_sign > 1)
		return (0);
	if (num_dot > 1)
		return (0);
	return (1);
}

double	ft_atod(const char *str)
{
	double	res;
	int		i;
	int		sign;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	if (str[i] == '.')
		res += dot(str, ++i);
	return (res * sign);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
