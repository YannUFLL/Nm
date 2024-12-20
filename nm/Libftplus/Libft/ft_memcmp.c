/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:06:01 by ydumaine          #+#    #+#             */
/*   Updated: 2022/03/02 13:10:57 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned const char	*ps1;
	unsigned const char	*ps2;

	ps1 = s1;
	ps2 = s2;
	i = 0;
	while (i < n)
	{
		if (ps1[i] > ps2[i] || ps1[i] < ps2[i])
			return (ps1[i] - ps2[i]);
		i++;
	}
	return (0);
}
/*
#include <string.h>
int	main()
{	//char s[] = {255, 0, 127, 0};
//	char sCpy[] = {-128, 0, 127, 0};
	char s2[] = {0, 0, 127, 0};
	char s3[] = {0, 0, 42, 0};
	printf("\n%d", ft_memcmp(s2, s3, 4));
	printf("\n%d", (char)(s3[2]));
}
*/
