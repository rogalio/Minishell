/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredocs_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:38:40 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/06 18:51:13 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

void	fill_name_tmp(char *name)
{
	name[0] = '/';
	name[1] = 't';
	name[2] = 'm';
	name[3] = 'p';
	name[4] = '/';
	name[5] = '.';
}

char	*generate_random_name(void)
{
	int		i;
	int		fd;
	char	c;
	char	*name;

	i = 6;
	fd = 0;
	c = '\0';
	name = ft_calloc(14, sizeof(char));
	if (!name)
		return (NULL);
	fill_name_tmp(name);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (free(name), NULL);
	while (i < 13)
	{
		if (read(fd, &c, 1) == -1)
			return (free(name), close(fd), NULL);
		if (ft_isalnum(c))
			name[i++] = c;
	}
	return (close(fd), name);
}

static void	fill_word_minus_quotes(char *new_word, char *prev_word)
{
	int		i;
	int		j;
	char	quote;

	i = -1;
	j = 0;
	quote = '\0';
	while (prev_word[++i])
	{
		if (prev_word[i] == '\'' || prev_word[i] == '\"')
		{
			quote = prev_word[i++];
			while (prev_word[i] && !ft_isquote(prev_word[i], quote))
				new_word[j++] = prev_word[i++];
		}
		else
			new_word[j++] = prev_word[i];
	}
}

int	remove_quotes(char **word)
{
	char	*tmp;
	int		nb_quotes;
	int		new_len;

	tmp = *word;
	nb_quotes = count_quotes(*word);
	new_len = (ft_strlen(*word) - nb_quotes);
	*word = ft_calloc((new_len + 1), sizeof(char));
	if (!(*word))
		return (free(tmp), 0);
	fill_word_minus_quotes(*word, tmp);
	return (free(tmp), 1);
}
