/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:16:58 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/22 14:49:49 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	ft_isquote(char c, char quote)
{
	return (c == quote);
}

char	*handle_qtes(const char *str, t_error *error)
{
	int		i;
	char	*word;
	char	*word2;
	char	*tmp;
	char	quote;

	i = 0;
	word = NULL;
	word2 = NULL;
	tmp = NULL;
	quote = str[i++];
	while (str[i] && !ft_isquote(str[i], quote))
		i++;
	if (!str[i])
		return (*error = QUOTES, NULL);
	word = ft_strndup(str, i + 1);
	if (!ft_isspace(str[++i]))
	{
		tmp = word;
		word2 = handle_rest((str + i), error);
		word = ft_strjoin(word, word2);
		free(tmp);
		free(word2);
	}
	return (word);
}

char	*handle_rest(const char *str, t_error *error)
{
	int		i;
	char	*word;
	char	*word2;
	char	*tmp;

	i = 0;
	word = NULL;
	word2 = NULL;
	tmp = NULL;
	while (str[i] && !ft_isspace(str[i]) && \
	!ft_isquote(str[i], '\'') && !ft_isquote(str[i], '\"'))
		i++;
	word = ft_strndup(str, i);
	if (str[i] && !ft_isspace(str[i]))
	{
		tmp = word;
		word2 = handle_qtes((str + i), error);
		word = ft_strjoin(word, word2);
		free(tmp);
		free(word2);
	}
	return (word);
}
