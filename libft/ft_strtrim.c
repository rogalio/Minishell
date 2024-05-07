/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:58:30 by cabdli            #+#    #+#             */
/*   Updated: 2023/10/09 22:09:55 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	char	*start;
	char	*end;
	char	*trim;

	if (!str || !set)
		return (NULL);
	start = (char *)str;
	end = start + ft_strlen((char *)str) - 1;
	while (*start && is_set(*start, set))
		start++;
	while (start < end && is_set(*end, set))
		end--;
	trim = ft_substr(start, 0, end - start + 1);
	return (trim);
}

/*#include <stdio.h>
int	main()
{
	const char str[] = "Hellholalll";
	const char set[] = "Hel";

	printf("%s\n", ft_strtrim(str, set));
	free (ft_strtrim(str, set));
	return (0);
	
}*/