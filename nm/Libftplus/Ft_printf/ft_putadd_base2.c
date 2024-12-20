/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd_base2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:48:11 by ydumaine          #+#    #+#             */
/*   Updated: 2022/03/28 19:25:42 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_addres_2(int i, unsigned long long int nbr, int *temp)
{
	int	u;

	u = 0;
	while (nbr != 0)
	{
		if (nbr > 0)
			temp[u] = nbr % i;
		nbr = nbr / (unsigned long long int)i;
		u++;
	}
	return (u);
}

int	ft_putadd_base2(unsigned long long int nbr, int count)
{
	int		i;
	int		temp[100];
	int		u;
	char	*base;

	base = "0123456789abcdef";
	write(1, "0x", 2);
	count = count + 2;
	i = 0;
	if (nbr == 0)
		count = ft_putchar2(base[0], count);
	else
	{
		while (base[i])
			i++;
		u = ft_addres_2(i, nbr, temp);
		while (--u >= 0)
		{
			ft_putchar2(base[temp[u]], 1);
			count++;
		}
	}
	return (count);
}
