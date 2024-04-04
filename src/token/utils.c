/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:00:51 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/04 18:02:28 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	skip_whitespace(const char **str)
{
	while (ft_isspace(**str))
		(*str)++;
	return (**str);
}

int	allowed_char(char c)
{
	const char	str[] = " <>\"'|$=.~_-?";
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
			return (write(2, "Error: use of wrong char\n", 23), 0);
	}
	return (1);
}
