/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:19:06 by cabdli            #+#    #+#             */
/*   Updated: 2023/10/09 22:08:47 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	len_tofind;
	int		cmp;

	i = 0;
	cmp = 0;
	if (str == NULL && len == 0)
		return (NULL);
	len_tofind = ft_strlen((char *)to_find);
	if (len_tofind == 0)
		return ((char *)str);
	while ((str[i] != '\0') && (i + len_tofind <= len))
	{
		cmp = ft_strncmp(&str[i], to_find, len_tofind);
		if (cmp != 0)
			i++;
		else
			return ((char *)str + i);
	}
	if (cmp != 0)
		return (NULL);
	return (NULL);
}

/*#include <stdio.h>
#include <bsd/string.h>

int	main()
{
	const char	str1[] = "Salut comment tu vas ?";
	const char	find[] = "comment";

	printf("%s : %s\n", ft_strnstr(str1, find, 12), strnstr(str1, find, 12));
	return 0;
}*/