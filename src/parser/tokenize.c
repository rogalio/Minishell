/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:56:18 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/23 11:02:43 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int			is_separator(int c)
{
	return (ft_isblank(c) || c == '\n');
}

static const char	*skip_unused(const char *s)
{
	if (!*s)
		return (NULL);
	if (*s == '#')
		return (ft_strchr(s + 1, '\n'));
	return (is_separator(*s) ? skip_unused(s + 1) : s);
}

static const char	*skip_word(const char *s)
{
	if (*s == '\\')
		return (s[1] ? s + 2 : NULL);
	if (*s == '\'')
		s = ft_strchr(s + 1, '\'');
	else if (*s == '"')
		while ((s = ft_strchr(s + 1, *s)) && s[-1] == '\\')
			continue ;
	return (s ? s + 1 : s);
}

static t_token		*token_eat(const char *s)
{
	const char	*s2;
	t_token		*t;
	ptrdiff_t	n;

	s2 = s;
	while (*s && !is_separator(*s) && *s != '#' && !(t = token_find(s)))
		if (!(s = skip_word(s)))
			return (token_new(TOKEN_MULTILINE, ft_strdup(s2)));
	n = s - s2;
	return (n ? token_new(TOKEN_WORD, ft_strndup(s2, n)) : t);
}

t_list				*tokenize(const char *s)
{
	t_list *l;

	l = NULL;
	while ((s = skip_unused(s)))
	{
		ft_list_push(&l, ft_list_new(token_eat(s)));
		s += ft_strlen(token(l->content)->value);
	}
	return (ft_list_rev(l));
}
