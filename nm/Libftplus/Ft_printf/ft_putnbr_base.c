/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:48:11 by ydumaine          #+#    #+#             */
/*   Updated: 2022/03/16 16:54:40 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_adres(int i, int unsigned nbr, int *temp)
{
	int	u;

	u = 0;
	while (nbr > 0 || nbr < 0)
	{
		if (nbr > 0)
			temp[u] = nbr % i;
		if (nbr < 0)
			temp[u] = - (nbr % i);
		nbr = nbr / i;
		u++;
	}
	return (u);
}

int	ft_putnbr_base(int old_nbr, char *base, int count)
{
	int				i;
	int				temp[100];
	int				u;
	unsigned int	nbr;

	nbr = old_nbr;
	i = 0;
	if (nbr == 0)
		count = ft_putchar(base[0], count);
	else
	{
		while (base[i])
			i++;
		if (nbr < 0)
		{
			nbr = 4294967285 - old_nbr;
		}
		u = ft_adres(i, nbr, temp);
		while (--u >= 0)
		{
			ft_putchar(base[temp[u]], 1);
			count++;
		}
	}
	return (count);
}
