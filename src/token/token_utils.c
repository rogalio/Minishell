/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:16:58 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/14 15:09:23 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	ft_isquote(char c, char quote)
{
	return (c == quote);
}

char	*handle_quotes(const char *str)
{
	int		i;
	char	*word;
	char	quote;

	i = 0;
	word = NULL;
	quote = str[i++];
	while (str[i] && !ft_isquote(str[i], quote))
		i++;
	if (!str[i])
	{
		write(2, "Error : quotes not closed\n", 26);
		exit(EXIT_FAILURE);
	}
	word = ft_strndup(str, ++i);
	return (word);
}

char	*handle_rest(const char *str)
{
	int		i;
	char	*word;

	i = 0;
	word = NULL;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	word = ft_strndup(str, i);
	return (word);
}
