/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:16:37 by ydumaine          #+#    #+#             */
/*   Updated: 2022/03/02 13:11:40 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	b;

	b = 0;
	i = 0;
	s = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
			i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			s = 1;
		i++;
	}
	while (str [i] >= 48 && str[i] <= 57)
	{
		b = b * 10 - (str[i] - 48);
		i++;
	}
	if (s == 0)
		b = -b;
	return (b);
}
/*
int	main()
{
	printf("%d", ft_atoi("\n1"));
	printf("%d", ft_atoi("\n+1"));
	printf("%d", ft_atoi("\n+42paris"));
	printf("%d", ft_atoi("\n+101"));
}*/
