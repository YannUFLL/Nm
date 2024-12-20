/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:23:09 by ydumaine          #+#    #+#             */
/*   Updated: 2022/03/01 14:48:33 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrsize(int n)
{
	if (n > 0)
		n = -n;
	if (n <= -10)
	{
		return (ft_nbrsize(n / 10) + 1);
	}
	else
		return (1);
}

void	ft_convert(int n, char *ptr)
{
	if (n > 0)
		n = -n;
	ptr--;
	if (n <= -10)
	{
		ft_convert(n / 10, ptr);
	}
		*ptr = (-(n % -10) + '0');
}

char	*ft_itoa(int n)
{
	int		size;
	char	*ptr;

	size = ft_nbrsize(n);
	if (n < 0)
		size++;
	ptr = malloc(sizeof(char) * (size + 1));
	if (ptr == NULL)
		return (NULL);
	ft_convert(n, (ptr + size));
	ptr[size] = 0;
	if (n < 0)
		ptr[0] = '-';
	return (ptr);
}
