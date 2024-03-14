/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:37:07 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/14 15:10:06 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

int	skip_whitespace(const char **str)
{
	while (ft_isspace(**str))
		(*str)++;
	return (**str);
}

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
			return (write(2, "Error, wrong char used\n", 23), 0);
	}
	return (1);
}
