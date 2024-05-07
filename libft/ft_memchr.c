/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:34:39 by cabdli            #+#    #+#             */
/*   Updated: 2023/05/09 15:34:41 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)str)[i] == (unsigned char)c)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}

//#include <stdio.h>

/*int	main()
{
	char	str[] = "Hello world !";

	printf("Vérifi. : %s\n", str + 6);
	printf("memchr : %s\n", (char *)memchr(str, 'w', 13));
	printf("ft_memchr: %s", (char *)ft_memchr(str, 'w', 13));
	return (0);
}*/