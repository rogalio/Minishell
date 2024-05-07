/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:23:35 by cabdli            #+#    #+#             */
/*   Updated: 2023/10/09 22:08:20 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	int		i;
	char	*ptr;
	size_t	l;

	i = 0;
	if (str == NULL)
		return (NULL);
	l = ft_strlen((char *)str);
	ptr = ft_calloc((l + 1), sizeof (char));
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = (*f)(i, str[i]);
		i++;
	}
	return (ptr);
}

/*#include <stdio.h>

char	test(unsigned int nb, char c)
{
	c += (nb + 48);
	return (c);
}

int	main(void)
{
	char	(*p_test)(unsigned int, char);
	char	str[] = "1234";

	p_test = &test;
	printf("mapi = %s\n", ft_strmapi(str, p_test));
	free(ft_strmapi(str, p_test));
	return (0);
}*/