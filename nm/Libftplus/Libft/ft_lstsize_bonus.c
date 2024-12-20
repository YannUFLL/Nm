/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:30:40 by ydumaine          #+#    #+#             */
/*   Updated: 2022/03/06 17:26:24 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*ptr;

	if (lst == NULL)
		return (0);
	i = 1;
	ptr = lst->next;
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}
