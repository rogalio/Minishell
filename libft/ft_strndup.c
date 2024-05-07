/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:48:22 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/07 10:50:07 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*new_str;
	size_t	len;
	int		i;

	len = 0;
	i = -1;
	while (s1[len] && len < n)
		len++;
	new_str = (char *)ft_calloc(len + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (++i < len)
		new_str[i] = s1[i];
	return (new_str);
}
