/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:04:26 by ydumaine          #+#    #+#             */
/*   Updated: 2024/12/19 15:17:24 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int ft_exclude_char(char c)
{
    if (c == '_' || c == '@' || c == '.' || c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ' ' || c == '\t' || c == '*' || c == '&' || c == ',' || c == '/' || c == '-')
        return (1);
    return (0);
}

int has_pattern(const unsigned char *str)
{
    while (*str)
    {
        if (*str == '(' && *(str + 1) == '*')
        {
            const unsigned char *end = str + 3;
            while (*end && *end != ')')
                end++;
            if (*end == ')')
                return (1);
        }
        str++;
    }
    return (0);
}


 int ft_strcmp_custom(const unsigned char *str1, const unsigned char *str2 )
{
    int i = 0;
    int j = 0;
    static int counter = 0;


    while (str1[i] || str2[j])
    {
        while (ft_exclude_char(str1[i]))
            i++;
        while (ft_exclude_char(str2[j]))
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
        while (ft_exclude_char(str1[i]))
            i++;
        while (ft_exclude_char(str2[j]))
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
    // then , if the two string are the same, but one strings containt (*<pattern>) and the other not, the one with the pattern is higher priority
    

    // if (has_pattern(str1) && !has_pattern(str2))
    //     return (-1);
    // if (!has_pattern(str1) && has_pattern(str2))
    //     return (1);

    // if the two strings are the same, we need to sort them by the number of underscore, more underscore = higher priority
    // this is the opposite way of the standard strcmp

    while (str1[i] && str2[j])
    {
        if (str1[i] != str2[j])
        {
            if (ft_exclude_char(str1[i]) && !ft_exclude_char(str2[j]))
                return (-1);
            if (ft_exclude_char(str2[j]) && !ft_exclude_char(str1[i]))
                return (1);
            return (str1[i] - str2[j]);
        }
        i++;
        j++;
    }
    return (str1[i] - str2[j]);

}

void ft_dprintf(const char *format, const char *str)
{
    while (*format)
    {
        if (*format == '%' && *(format + 1) == 's')
        {
            write(2, str, ft_strlen(str));
            format += 2; // skip %s
        }
        else
        {
            write(2, format, 1);
            format++;
        }
    }
}




uint16_t read_uint16(uint16_t value, int is_little_endian) {
    if (is_little_endian) {
        return value; 
    } else {
        return __builtin_bswap16(value); 
    }
}

uint32_t read_uint32(uint32_t value, int is_little_endian) {
    if (is_little_endian) {
        return value; 
    } else {
        return __builtin_bswap32(value);
    }
}

uint64_t read_uint64(uint64_t value, int is_little_endian) {
    if (is_little_endian) {
        return value; 
    } else {
        return __builtin_bswap64(value);
    }
}