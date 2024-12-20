/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:51:39 by ydumaine          #+#    #+#             */
/*   Updated: 2022/03/11 23:10:22 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

_Bool	ft_check(char const c, char const *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s2[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	size;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	size = ft_strlen(s1);
	while (ft_check(s1[i], s2) == 1 && s1[i])
		i++;
	while (size > 0 && ft_check(s1[size - 1], s2) == 1)
		size--;
	if (size == 0)
		i = 0;
	ptr = ft_substr((char *)&s1[i], 0, (size - i));
	return (ptr);
}
