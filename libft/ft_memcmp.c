/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:34:59 by cabdli            #+#    #+#             */
/*   Updated: 2023/05/09 16:20:32 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i] && i < n - 1)
	{
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

//#include <stdio.h>

/*int	main()
{	
	char str1[] = "Hel~o world";
	char str2[] = "Hell world";
	char str3[] = "hello world";
	char str4[] = "hel world";
	char str5[] = "HellO";

	printf("%d : %d", ft_memcmp(str1, str2, 5), memcmp(str1, str2, 5));
	printf("\n%d : %d", ft_memcmp(str3, str4, 10), memcmp(str3, str4, 10));
	printf("\n%d : %d", ft_memcmp(str4, str3, 10), memcmp(str4, str3, 10));
	printf("\n%d : %d", ft_memcmp(str5, str5, 4), memcmp(str5, str5, 4));
	return 0;
}*/