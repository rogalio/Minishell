/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:37:32 by cabdli            #+#    #+#             */
/*   Updated: 2023/10/09 22:07:55 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	x;
	size_t	i;

	i = 0;
	x = ft_strlen((char *)src);
	if (destsize != 0)
	{
		while (src[i] != '\0' && i < destsize - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (x);
}
/*#include <stdio.h>
int	main()
{
	char	src[] = "coucou";
	char	dest[50] = "bonjour comment tu vas ?";

	//printf("ft_strlcpy = %d ; dest = %s", ft_strlcpy(dest, src, 50), dest);
	printf("strlcpy = %d ; dest = %s", strlcpy(dest, src, 50), dest);
	return (0);

}*/