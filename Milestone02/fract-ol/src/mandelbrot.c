/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:51:15 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/26 04:41:51 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot_iter(double real, double img)
{
	double	zreal;
	double	zimg;
	double	tmp;
	int		i;

	zreal = 0;
	zimg = 0;
	i = 0;
	while (zreal * zreal + zimg * zimg <= 4 && i < MAX_ITER)
	{
		tmp = zreal * zreal - zimg * zimg + real;
		zimg = 2 * zreal * zimg + img;
		zreal = tmp;
		i++;
	}
	return (i);
}

void	mandelbrot(t_mlx *fractol)
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
			real = (w - WIDTH / 2.0) * 4.0 / WIDTH / fractol->zoom;
			img = (h - HEIGHT / 2.0) * 4.0 / HEIGHT / fractol->zoom;
			iter = mandelbrot_iter(real, img);
			fractol->color = colorful_img(iter);
			my_mlx_pixel_put(fractol, w, h, fractol->color);
			h++;
		}
		w++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}
