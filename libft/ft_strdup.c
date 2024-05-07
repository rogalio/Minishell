/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:22:41 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/07 11:18:17 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	str_len;
	char	*ptr;
	int		i;

	str_len = ft_strlen((char *)str);
	ptr = (char *)ft_calloc((str_len + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

//#include <stdio.h>
/*int	main()
{
	const char	str1[] = " ";

	printf("%s : %s\n", ft_strdup(str1), strdup(str1));
	free (ft_strdup(str1));
	free (strdup(str1));
	return (0);
}*/