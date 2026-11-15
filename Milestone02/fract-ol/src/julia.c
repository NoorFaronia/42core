/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:08:50 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/25 14:57:52 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia_iter(double real, double img, double freal, double fimg)
{
	int		i;
	double	new_real;

	i = 0;
	while (i < MAX_ITER && (real * real + img * img) < 4.0)
	{
		new_real = real * real - img * img + freal;
		img = 2 * real * img + fimg;
		real = new_real;
		i++;
	}
	return (i);
}

void	julia(t_mlx *fractol)
{
	int		w;
	int		h;
	double	real;
	double	img;
	int		iter;

	w = 0;
	while (w < WIDTH)
	{
		h = 0;
		while (h < HEIGHT)
		{
			real = (w - WIDTH / 2.0) / (0.5 * WIDTH * fractol->zoom);
			img = (h - HEIGHT / 2.0) / (0.5 * HEIGHT * fractol->zoom);
			iter = julia_iter(real, img, fractol->jreal, fractol->jimg);
			fractol->color = colorful_img(iter);
			my_mlx_pixel_put(fractol, w, h, fractol->color);
			h++;
		}
		w++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}
