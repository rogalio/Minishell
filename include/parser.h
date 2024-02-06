/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:40:36 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/06 13:27:25 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "libft.h"
# include "token.h"

# define ERR_UNEXPECT	"minishell: syntax error near unexpected token `%s'\n"
# define STATE_SIZE		6

typedef enum e_state
{
  STATE_Q0,
  STATE_Q1,
  STATE_Q2,
  STATE_Q3,
  STATE_ERROR,
} t_state;

int init_syntax_analyzer(t_token_list *tokens);
t_token_list	*init_token_list(const char *s);




#endif
