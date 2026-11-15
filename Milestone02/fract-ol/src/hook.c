/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 04:45:55 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/26 12:09:45 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int keycode, t_mlx *fractol)
{
	if (keycode == ESC)
		clean_exit(fractol);
	else if (keycode == MINUS)
	{
		fractol->zoom *= 0.8;
		fractol->redraw = 1;
	}
	else if (keycode == PLUS)
	{
		fractol->zoom *= 1.2;
		fractol->redraw = 1;
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_mlx *fractol)
{
	(void)x;
	(void)y;
	if (button == UP)
	{
		fractol->zoom *= 1.1;
		fractol->redraw = 1;
	}
	else if (button == DOWN)
	{
		fractol->zoom *= 0.9;
		fractol->redraw = 1;
	}
	return (0);
}

int	expose_hook(void *param)
{
	t_mlx	*fractol;

	fractol = (t_mlx *)param;
	if (!fractol)
		return (0);
	if (ft_strcmp(fractol->type, "mandelbrot") == 0)
		mandelbrot(fractol);
	else if (ft_strcmp(fractol->type, "julia") == 0)
		julia(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
	return (0);
}

int	loop_hook(t_mlx *fractol)
{
	if (fractol->redraw)
	{
		expose_hook(fractol);
		fractol->redraw = 0;
	}
	return (0);
}
