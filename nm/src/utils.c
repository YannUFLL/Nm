/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:04:26 by ydumaine          #+#    #+#             */
/*   Updated: 2024/11/06 15:53:23 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdio.h>


 int ft_strcmp_custom(const unsigned char *str1, const unsigned char *str2 )
{
    int i = 0;
    int j = 0;
    static int counter = 0;


    while (str1[i] || str2[j])
    {
        while (str1[i] == '_' || str1[i] == '@')
            i++;
        while (str2[j] == '_' || str2[j] == '@')
            j++;

        if (ft_tolower(str1[i]) != ft_tolower(str2[j]))
        {
            // if (str1[i] == '@')
            //     return (1);
            // if (str2[j] == '@')
            //     return (-1);
            counter++;
            return (ft_tolower(str1[i]) - ft_tolower(str2[j]));
        }
        if (str1[i] == '\0' && str2[j] == '\0')
            break;
        i++;
        j++;
    }
    
    // The two string have the same number of letter, but the two strings can be different because of capital letters or underscore

    i = 0;
    j = 0;
    //__test__
    //_te___ST_

    while (str1[i] && str2[j])
    {
        while (str1[i] == '_')
            i++;
        while (str2[j] == '_')
            j++;
        if (str1[i] + 32 == str2[j] || str1[i] - 32 == str2[j])
        {
            return (str2[j] - str1[i]);
        }
        i++;
        j++;
    }
    i = 0;
    j = 0;
    // if the two strings are the same, we need to sort them by the number of underscore, more underscore = higher priority
    // this is the opposite way of the standard strcmp

    while (str1[i] && str2[j])
    {
        if (str1[i] != str2[j])
        {
            if (str1[i] == '_')
                return (-1);
            if (str2[j] == '_')
                return (1);
            return (str1[i] - str2[j]);
        }
        i++;
        j++;
    }
    return (str1[i] - str2[j]);
}