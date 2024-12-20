/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:37:58 by ydumaine          #+#    #+#             */
/*   Updated: 2022/03/02 13:09:54 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*ptr1;
	char	*ptr2;

	if (dst == NULL && src == NULL)
		return (NULL);
	ptr1 = (char *)dst;
	ptr2 = (char *)src;
	i = 0;
	while (i < n)
	{
		ptr1[i] = ptr2[i];
		i++;
	}
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char *a;
	char *c;
	a = NULL;
	//b = 0;
	c = memcpy(a, "test", 3);
	//printf("%p", c);
	//printf("\n%s", c);
}*/
