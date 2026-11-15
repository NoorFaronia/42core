/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:22:18 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/26 13:45:52 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clean_exit(t_mlx *fractol)
{
	if (fractol == NULL)
		exit(EXIT_SUCCESS);
	if (fractol->img && fractol->mlx)
	{
		mlx_destroy_image(fractol->mlx, fractol->img);
		fractol->img = NULL;
	}
	if (fractol->win && fractol->mlx)
	{
		mlx_destroy_window(fractol->mlx, fractol->win);
		fractol->win = NULL;
	}
	if (fractol->mlx)
	{
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
		fractol->mlx = NULL;
	}
	exit(EXIT_SUCCESS);
}

int	close_window(void *param)
{
	t_mlx	*fractol;

	fractol = (t_mlx *)param;
	clean_exit(fractol);
	return (0);
}
