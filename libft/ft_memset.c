/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:36:38 by cabdli            #+#    #+#             */
/*   Updated: 2023/05/14 22:13:19 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	char	*ptr;

	ptr = str;
	while (len > 0)
	{
		*ptr = c;
		ptr++;
		len--;
	}
	return (str);
}

//#include <stdio.h>
/*int	main()
{
	char	str[] = "Salut,ca va ?"; 
	memset((void *)str, '1', 5);
	printf("memset : %s\n", str);
	ft_memset((void *)str, '2', 5);
	printf("ft_memset : %s", str);
	return (0);
}*/
