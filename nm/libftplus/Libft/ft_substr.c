/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:31:05 by ydumaine          #+#    #+#             */
/*   Updated: 2022/03/12 18:31:09 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned int	i;
	unsigned int	j;
	unsigned int	alloc_size;

	alloc_size = ft_strlen(&s[start]);
	if (s == NULL)
		return (NULL);
	if (len < alloc_size)
		ptr = malloc(sizeof(char) * (len + 1));
	else
		ptr = malloc(sizeof(char) * (alloc_size + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
			ptr[j++] = s[i];
		i++;
	}
	ptr[j] = 0;
	return (ptr);
}
/*
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
int	main()
{
	char *str = "01234";
	size_t size = 10;
	char *ptr;
	int	a;
	ptr = ft_substr(str, 10, size);
	a = strncmp(ptr, "", 1);
	printf("\n chaine ptr :%s", ptr);
	printf("\n difference chaine :%d", a);
}
*/
