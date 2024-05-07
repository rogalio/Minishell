/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:40:36 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/07 11:49:41 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "token.h"

/*
	STATE_Q0 = start
	STATE_Q1 = TOKEN_WORD
	STATE_Q2 = TOKEN_REDIRECT
	STATE_Q3 = TOKEN_PIPE
	STATE_ERROR = wrong transition
*/
typedef enum e_state
{
	STATE_Q0,
	STATE_Q1,
	STATE_Q2,
	STATE_Q3,
	STATE_ERROR,
}t_state;

/* syntax_analyser.c */
int	syntax_analyzer(t_token_list *token_list, t_error *error);

#endif
