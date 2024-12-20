/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:39:41 by ydumaine          #+#    #+#             */
/*   Updated: 2022/02/25 19:58:20 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	int		i;

	ptr = malloc(count * size);
	i = size * count;
	if (ptr == 0)
		return (0);
	while (i > 0)
	{
		(ptr[i - 1]) = 0;
		i--;
	}	
	return ((void *)ptr);
}
