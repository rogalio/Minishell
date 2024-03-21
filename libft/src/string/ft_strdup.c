/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 04:28:09 by asoursou          #+#    #+#             */
/*   Updated: 2024/03/21 13:22:27 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_string.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	n;
	char	*str;

	i = 0;
	n = ft_strlen(s);
	str = ft_calloc(n + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}
