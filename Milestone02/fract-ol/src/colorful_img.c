/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorful_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:25:10 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/25 13:37:05 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	colorful_img(int iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter == MAX_ITER)
		return (0x000000);
	t = (double)iter / MAX_ITER;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((r << 16) | (g << 8) | b);
}

void	my_mlx_pixel_put(t_mlx *fractol, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel = fractol->addr + (y * fractol->size_line
				+ x * (fractol->bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}
