/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:11:26 by ydumaine          #+#    #+#             */
/*   Updated: 2022/02/26 20:05:50 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int unsigned	i;
	int unsigned	u;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		u = 0;
		if (haystack[i] == needle[u])
		{
			while (haystack[i + u] == needle[u] && ((i + u) < len))
			{
				if (needle[u + 1] == 0)
				{
					return ((char *)&haystack[i]);
				}
				u++;
			}
		}
	i++;
	}
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>
int	main()
{
	char a[] = ""; 
	char b[] = "b";
	char *c; 
	char *d; 

	c = strnstr(a, b, 6);
	d = ft_strnstr(a, b, 6);

	printf("\n%s", c);
	printf("\n%s", d);

}
*/
