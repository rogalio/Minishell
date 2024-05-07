/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:32:44 by cabdli            #+#    #+#             */
/*   Updated: 2023/11/21 12:07:09 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t size)
{
	unsigned char	*ptr;

	ptr = str;
	while (size > 0)
	{
		*ptr = '\0';
		ptr++;
		size--;
	}
}

/*#include <stdio.h>
#include <strings.h>

int	main()
{
    char	str1[] = "Hello World !";
    char	str2[] = "Hello World !";

	printf("str = %s\n", str1);
	bzero((void *)str1, 4);
	printf("bzero : %s\n", str1);
	ft_bzero((void *)str2, 4);
	printf("ft_bzero : %s", str2);
	return (0);
}*/