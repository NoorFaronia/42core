/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:39:19 by nfaronia          #+#    #+#             */
/*   Updated: 2025/09/16 12:39:22 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_s(char *str)
{
	int	count;

	if (!str)
		str = "(null)";
	count = 0;
	while (str[count])
	{
		write(1, &str[count], 1);
		count++;
	}
	return (count);
}
