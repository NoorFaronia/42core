/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:27:19 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/26 13:53:42 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <math.h>

# include "mlx.h"
# include "libft.h"

# define WIDTH 1000
# define HEIGHT 800
# define MAX_ITER 150
# define ESC 65307
# define UP 4
# define DOWN 5
# define PLUS 65451
# define MINUS 65453

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;

	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	char	*type;

	int		color;

	double	zoom;
	int		redraw;

	double	jreal;
	double	jimg;
}			t_mlx;

// utail
int		error(char *str);
int		ft_strcmp(const char *s1, const char *s2);
double	dot(const char *str, int i);
int		all_num(const char *str);
double	ft_atod(const char *str);

// fractol
void	initialize(t_mlx *fractol, char *type);
void	jul(int argc, char **argv, t_mlx *fractol);

//hoks
int		key_hook(int keycode, t_mlx *fractol);
int		mouse_hook(int button, int x, int y, t_mlx *fractol);
int		expose_hook(void *param);
int		loop_hook(t_mlx *fractol);

// mandelbrot
void	mandelbrot(t_mlx *fractol);
int		mandelbrot_iter(double real, double img);

// julia
void	julia(t_mlx *fractol);
int		julia_iter(double real, double img, double freal, double fimg);

// colorful_img
int		colorful_img(int iter);
void	my_mlx_pixel_put(t_mlx *fractol, int x, int y, int color);

// close
void	clean_exit(t_mlx *fractol);
int		close_window(void *param);

#endif
