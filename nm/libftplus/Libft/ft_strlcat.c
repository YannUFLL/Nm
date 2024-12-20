/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:41:12 by ydumaine          #+#    #+#             */
/*   Updated: 2022/02/28 16:50:33 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	u;
	size_t	length;

	i = 0;
	i = ft_strlen(dst);
	if (dstsize <= i)
		return (dstsize + ft_strlen(src));
	length = i;
	u = 0;
	while ((src[u] != '\0') && (i < (dstsize - 1)))
	{
		dst[i] = src[u];
		i++;
		u++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	i = 0;
	while (src[i++] != '\0')
		length++;
	return (length);
}
/*
#include <unistd.h>
#include <string.h>

int	main()
{
	char *dest;
	char *dest2;
	if (!(dest = (char *)malloc(sizeof(*dest) * 15)))
		return (0);
	memset(dest, 0, 15);
	memset(dest, 'r', 6);
	if (!(dest2 = (char *)malloc(sizeof(*dest) * 15)))
		return (0);
	memset(dest2, 0, 15);
	memset(dest2, 'r', 6);
	dest[11] = 'a';
	dest2[11] = 'a';
	int	c;
	int d; 
	
	d = ft_strlcat(dest, "lorem ipsum dolor sit amet", 5);
	c = strlcat(dest2, "lorem ipsum dolor sit amet", 5);
	printf("\n%s valeur de int %d", dest, d);
	printf("\n%s valeur de int %d", dest2, c);
}*/
