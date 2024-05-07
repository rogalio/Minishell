/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:08:37 by cabdli            #+#    #+#             */
/*   Updated: 2023/10/09 22:07:27 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (dest == NULL && destsize == 0)
		return (ft_strlen((char *)src));
	while (dest[j] && j < destsize)
		j++;
	while (src[i] && (j + i + 1) < destsize)
	{
		dest[j + i] = src[i];
		i++;
	}
	if (j < destsize)
		dest[j + i] = '\0';
	return (j + ft_strlen((char *)src));
}

/*#include <stdio.h>
int	main()
{
	char	src[] = "";
	char	dest1[20] = "";
	char	dest2[20] = "";
	printf("ft_strlcat = %u : strlcat = %zu\n", 
		ft_strlcat(dest1, src, 20), strlcat(dest2, src, 20));
	printf("ft = %s\nlcat = %s", dest1, dest2);
	return (0);
}*/