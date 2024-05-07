/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:30:40 by cabdli            #+#    #+#             */
/*   Updated: 2023/10/09 22:11:39 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	strlen;

	if (str == NULL)
		return (NULL);
	strlen = ft_strlen((char *)str);
	if (start > strlen)
		start = strlen;
	if (len > ft_strlen((char *)str + start))
		len = ft_strlen((char *)str + start);
	ptr = ft_calloc((len + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (str[start] && i < len)
	{
		ptr[i] = str[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*#include <stdio.h>
int	main()
{
	//char const	str1[] = "coucou";
	char const	*str2 = NULL;


	//printf("%s\n", ft_substr(str1, 8, 20));
	if ((ft_substr(str2, 8, 20)) == NULL)
		printf("le ptr = NULL");
	//free (ft_substr(str2, 2, 6));
	return (0);
}*/