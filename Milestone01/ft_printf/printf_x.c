/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:23:21 by nfaronia          #+#    #+#             */
/*   Updated: 2025/09/16 15:23:59 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_x(unsigned int n, int is_upper)
{
	int				count;
	char			c;
	char			*hex;

	count = 0;
	if (is_upper)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	if (n >= 16)
		count += printf_x(n / 16, is_upper);
	c = hex[n % 16];
	write(1, &c, 1);
	count++;
	return (count);
}
