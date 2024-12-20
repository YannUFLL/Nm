/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:18:24 by ydumaine          #+#    #+#             */
/*   Updated: 2022/03/28 19:29:20 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putchar2(char c, int count)
{
	write(1, &c, 1);
	count++;
	return (count);
}

int	ft_putstr2(char *str, int count)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (count + 6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
		count++;
	}
	return (count);
}

int	ft_putnbr_r2(int n, int count)
{
	if (n > 0)
		n = -n;
	if (n <= -10)
	{
		count = ft_putnbr_r2(n / 10, count);
	}
	ft_putchar2((- (n % -10) + '0'), 1);
	count++;
	return (count);
}

int	ft_putnbr2(int n, int count)
{
	if (n < 0)
	{
		ft_putchar2('-', 1);
		count++;
	}
	count = ft_putnbr_r2(n, count);
	return (count);
}

int	ft_putnbr_unsigned2(unsigned int n, int count)
{
	if (n >= 10)
	{
		count = ft_putnbr_unsigned2(n / 10, count);
	}
	ft_putchar2(((n % 10 + '0')), 1);
	count++;
	return (count);
}
