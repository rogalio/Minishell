/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:14:43 by cabdli            #+#    #+#             */
/*   Updated: 2023/05/10 22:51:28 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nb_el, size_t size)
{
	void	*arr;
	size_t	total_size;

	total_size = nb_el * size;
	if ((size != 0) && (total_size / size) != nb_el)
		return (NULL);
	arr = (void *)malloc(total_size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, total_size);
	return (arr);
}
