/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:52:29 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 14:14:39 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (i < ft_strlen(s1))
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		ptr[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	ptr[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (ptr);
}

/*
#include <stdio.h>

int	main(void)
{
	char const *s1 = "noor";
	char const *s2 = " faronia";
	printf("s1 + s2 = %s \n", ft_strjoin(s1, s2));
	return (0);
}*/
