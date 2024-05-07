/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:23:05 by cabdli            #+#    #+#             */
/*   Updated: 2023/10/09 22:09:35 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				i;
	unsigned char	ch;

	i = (int)ft_strlen((char *)str) - 1;
	ch = c;
	if (ch == '\0')
		return ((char *)(str + i + 1));
	while (i >= 0)
	{
		if (str[i] == ch)
			return ((char *)(str + i));
		i--;
	}
	return (NULL);
}

//#include <stdio.h>

/*int	main()
{
	char	str[] = "Hello world !";

	//printf("Vérifi. : %p\n", str + 13);
	printf("strrchr : %s\n", strrchr(str, 'a'));
	printf("ft_strr : %s", ft_strrchr(str, 'a'));
	return (0);
}*/