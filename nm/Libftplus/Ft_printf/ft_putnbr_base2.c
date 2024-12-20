/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:48:11 by ydumaine          #+#    #+#             */
/*   Updated: 2022/03/28 19:26:20 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_adres2(int i, int unsigned nbr, int *temp)
{
	int	u;

	u = 0;
	while (nbr != 0)
	{
		if (nbr > 0)
			temp[u] = nbr % i;
		nbr = nbr / i;
		u++;
	}
	return (u);
}

int	ft_putnbr_base2(int old_nbr, char *base, int count)
{
	int				i;
	int				temp[100];
	int				u;
	unsigned int	nbr;

	nbr = old_nbr;
	i = 0;
	if (nbr == 0)
		count = ft_putchar2(base[0], count);
	else
	{
		while (base[i])
			i++;
		u = ft_adres2(i, nbr, temp);
		while (--u >= 0)
		{
			ft_putchar2(base[temp[u]], 1);
			count++;
		}
	}
	return (count);
}
