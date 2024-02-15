/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:15:33 by cabdli            #+#    #+#             */
/*   Updated: 2024/02/15 14:46:46 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	allowed_char(char c)
{
	const char	str[] = " <>\"'|$=.~_-";
	int			i;

	i = -1;
	while (str[++i])
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

int	check_regex(const char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!ft_isalnum((int)s[i]) && !allowed_char(s[i]))
			return (printf("Error, wrong char used\n"), 0);
	}
	return (1);
}
