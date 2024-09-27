/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:04:59 by ydumaine          #+#    #+#             */
/*   Updated: 2024/09/27 18:26:39 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_H
# define UTILS_H


 int ft_strcmp(const char *str1, const char *str2);

typedef struct {
    void *mapped;
    size_t size;
} MappedFile;


#endif