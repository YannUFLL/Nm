/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:15:41 by ydumaine          #+#    #+#             */
/*   Updated: 2022/03/28 19:26:59 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_letter(char c)
{
	char	*char_ok;

	char_ok = "cspdiuxX%";
	while (char_ok)
	{
		if (*char_ok == c)
			return (1);
		char_ok++;
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			count;

	va_start (args, str);
	count = 0;
	while (*str)
	{
		if (*str == '%' && ft_check_letter(*(str + 1)))
		{
			str++;
			if (*str == '%')
				count = ft_putchar2('%', count);
			else
				count = ft_select_f(va_arg(args, long long int), *str, count);
			str++;
		}
		else
		{
			write(1, &*str, 1);
			count++;
			str++;
		}
	}
	va_end(args);
	return (count);
}

int	ft_select_f(long long int arg, char c, int count)
{
	if (c == 'c')
		count = ft_putchar2((char)arg, count);
	if (c == 's')
		count = ft_putstr2((char *)arg, count);
	if (c == 'p')
		count = ft_putadd_base2((unsigned long long int)arg, count);
	if (c == 'd')
		count = ft_putnbr2((int)arg, count);
	if (c == 'i')
		count = ft_putnbr2((int)arg, count);
	if (c == 'u')
		count = ft_putnbr_unsigned2((unsigned int)arg, count);
	if (c == 'x')
		count = ft_putnbr_base2((int)arg, "0123456789abcdef", count);
	if (c == 'X')
		count = ft_putnbr_base2((int)arg, "0123456789ABCDEF", count);
	return (count);
}
