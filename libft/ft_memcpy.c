/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:35:15 by cabdli            #+#    #+#             */
/*   Updated: 2023/05/16 11:40:24 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*new_dest;
	const unsigned char	*new_src;

	i = 0;
	new_dest = dest;
	new_src = src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		new_dest[i] = new_src[i];
		i++;
	}
	return (dest);
}

/*#include <stdio.h>

int	main ()
{
	char	src1[] = "Coucou";
	char	dest1[] = "JeVaisBienMerci";
	char	src2[] = "Coucou";
	char	dest2[] = "JeVaisBienMerci";
	
	memcpy((void *)dest1, (const void *)src1, 6);
	printf("memcpy : %s\n", dest1);
	ft_memcpy((void *)dest2, (const void *)src2, 6);
	printf("ft_memcpy : %s", dest2);
	return (0);

}*/
