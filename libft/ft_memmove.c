/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:02:31 by cabdli            #+#    #+#             */
/*   Updated: 2023/05/16 12:18:33 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	int					i;

	i = len - 1;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (src > dest)
		ft_memcpy(dest, src, len);
	else
	{
		while (i >= 0)
		{
			*((unsigned char *)dest + i) = *((const unsigned char *)src + i);
			i--;
		}
	}
	return (dest);
}

//#include <stdio.h>
/*int	main()
{
	char	src[] = "hello, comment ca va ?";
	char	src2[] = "hello, comment ca va ?";
	//char	dest[] = "Hello";

	printf("memmove :%s\n", (char *)memmove((void *)src + 3, 
		(const void *)src, 5));
	printf("ft_memmove :%s", (char *)ft_memmove((void *)src2 + 3, 
		(const void *)src2, 5));
	return (0);
}*/