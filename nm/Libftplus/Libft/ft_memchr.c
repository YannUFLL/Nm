/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:37:51 by ydumaine          #+#    #+#             */
/*   Updated: 2022/03/01 20:15:46 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)ptr[i] == (unsigned char)c)
			return (&ptr[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main()
{
	char *ptr;
	unsigned char test;

	test = 256 + 2;
	char s[] = {0, 1, 2 ,3 ,4 ,5};
	ptr = ft_memchr(s, 2 + 256, 3);
	printf("%s", ptr);
	printf("test : %c", test);
}*/
