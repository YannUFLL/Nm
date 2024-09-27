/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:04:26 by ydumaine          #+#    #+#             */
/*   Updated: 2024/09/27 13:49:59 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdio.h>

 int ft_strcmp(const unsigned char *str1, const unsigned char *str2 )
{
    int i = 0;
    int j = 0;


    while (str1[i] && str2[j])
    {
        while (str1[i] == '_')
            i++;
        while (str2[j] == '_')
            j++;
        if (ft_tolower(str1[i]) != ft_tolower(str2[j]))
            return (ft_tolower(str1[i]) - ft_tolower(str2[j]));
        i++;
        j++;
    }
    return ((ft_tolower(str1[i])) - ft_tolower(str2[j]));
}