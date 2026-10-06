/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:38:44 by nfaronia          #+#    #+#             */
/*   Updated: 2025/09/16 12:38:45 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);

int	printf_c(char c);
int	printf_s(char *str);
int	printf_di(int n);
int	printf_u(unsigned int n);
int	printf_x(unsigned int n, int is_upper);
int	printf_p(void *ptr);
#endif
