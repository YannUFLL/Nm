/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:05:25 by ydumaine          #+#    #+#             */
/*   Updated: 2022/03/11 23:21:53 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	size;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(sizeof(char) * (size + 1));
	if (ptr == NULL)
		return (0);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	size = i;
	i = 0;
	while (s2[i])
	{
		ptr[size + i] = s2[i];
		i++;
	}
	ptr[size + i] = 0;
	return (ptr);
}
/*
#include <stdio.h>
int	main()
{
	char a[] = "";
	char b[] = "";
	char *ptr; 

	ptr = ft_strjoin(a, b);
	printf("%s", ptr);
}
*/
