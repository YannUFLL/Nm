/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:04:59 by ydumaine          #+#    #+#             */
/*   Updated: 2024/11/26 19:51:13 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_H
# define UTILS_H

int ft_strcmp_custom(const unsigned char *str1, const unsigned char *str2);
void ft_dprintf(const char *format, const char *str);


uint16_t read_uint16(uint16_t value, int is_little_endian);
uint32_t read_uint32(uint32_t value, int is_little_endian);
uint64_t read_uint64(uint64_t value, int is_little_endian);

#endif