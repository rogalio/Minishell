/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:01:39 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/22 19:34:29 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"

static t_token	*find(const char *s, t_token *lexer, size_t i)
{
	if (!i)
		return (NULL);
	--i;
	if (!ft_strncmp(s, lexer[i].value, ft_strlen(lexer[i].value)))
		return (lexer + i);
	return (find(s, lexer, i));
}

t_token			*token_find(const char *s)
{
	static t_token	lexer[] = {
		{ TOKEN_PAR_LEFT, "(", },
		{ TOKEN_PAR_RIGHT, ")" },
		{ TOKEN_PIPE, "|" },
		{ TOKEN_SEMICOLON, ";" },
		{ TOKEN_REDIRECT, "<" },
		{ TOKEN_REDIRECT, ">" },
		{ TOKEN_REDIRECT, "<<" },
		{ TOKEN_REDIRECT, ">>" },
		{ TOKEN_LOGICAL_OP, "&&" },
		{ TOKEN_LOGICAL_OP, "||" }
	};

	return (find(s, lexer, sizeof(lexer) / sizeof(*lexer)));
}
