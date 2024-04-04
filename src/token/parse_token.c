/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:01:52 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/04 17:01:42 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token	*parse_token(const char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (new_token(TOKEN_REDIRECT, ft_strdup(">>")));
	else if (!ft_strncmp(str, "<<", 2))
		return (new_token(TOKEN_REDIRECT, ft_strdup("<<")));
	else if (!ft_strncmp(str, ">", 1))
		return (new_token(TOKEN_REDIRECT, ft_strdup(">")));
	else if (!ft_strncmp(str, "<", 1))
		return (new_token(TOKEN_REDIRECT, ft_strdup("<")));
	else if (!ft_strncmp(str, "|", 1))
		return (new_token(TOKEN_PIPE, ft_strdup("|")));
	else
		return (new_token_word(str));
	return (NULL);
}
