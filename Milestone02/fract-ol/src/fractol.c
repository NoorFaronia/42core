/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:08:00 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/26 13:52:09 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	initialize(t_mlx *fractol, char *type)
{
	ft_bzero(fractol, sizeof(t_mlx));
	fractol->type = type;
	fractol->zoom = 1.0;
	fractol->mlx = mlx_init();
	if (WIDTH <= 0 || HEIGHT <= 0)
	{
		ft_printf("Error: Invalid window dimensions\n");
		close_window(fractol);
	}
	if (fractol->mlx == NULL)
		error("fails to set up the connection to the graphical system");
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "fractol");
	if (fractol->win == NULL)
		error("fails to create a new window");
	fractol->img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	if (!fractol->img)
		error("fails to create a new image");
	fractol->addr = mlx_get_data_addr(fractol->img,
			&fractol->bits_per_pixel, &fractol->size_line, &fractol->endian);
}

void	jul(int argc, char **argv, t_mlx *fractol)
{
	if (argc == 2)
	{
		fractol->jreal = 0;
		fractol->jimg = 0;
	}
	else if (argc == 4)
	{
		fractol->jreal = ft_atod(argv[2]);
		fractol->jimg = ft_atod(argv[3]);
	}
}

static void	v(char **argv, t_mlx *fractol)
{
	if (all_num(argv[2]) == 0 || all_num(argv[3]) == 0)
		error("Invalid real number");
	fractol->jreal = ft_atod(argv[2]);
	fractol->jimg = ft_atod(argv[3]);
	if (fractol->jreal < -2.0 || fractol->jreal
		> 2.0 || fractol->jimg < -2.0 || fractol->jimg > 2.0)
		error("Julia parameters should be between -2 and 2\n");
}

int	main(int argc, char **argv)
{
	t_mlx	fractol;

	if (argc == 2 && ft_strcmp(argv[1], "mandelbrot") == 0)
	{
		initialize(&fractol, "mandelbrot");
		mandelbrot(&fractol);
	}
	else if ((argc == 4 || argc == 2) && ft_strcmp(argv[1], "julia") == 0)
	{
		if (argc == 4)
			v(argv, &fractol);
		initialize(&fractol, "julia");
		jul(argc, argv, &fractol);
		julia(&fractol);
	}
	else
		error("Invalid Input\nTo show Mandelbrot, write : ./fractol mandelbrot"
			"\nTo show Julia, write : ./fractol julia <real> <imag>"
			" or ./fractol julia");
	mlx_expose_hook(fractol.win, expose_hook, &fractol);
	mlx_loop_hook(fractol.mlx, loop_hook, &fractol);
	mlx_mouse_hook(fractol.win, mouse_hook, &fractol);
	mlx_key_hook(fractol.win, key_hook, &fractol);
	mlx_hook(fractol.win, 17, 0, close_window, &fractol);
	mlx_loop(fractol.mlx);
}
