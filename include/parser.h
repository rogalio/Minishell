/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:40:36 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/22 13:06:44 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "token.h"
# include "builtins.h"

# define SYNT_ERR	"minishell: syntax error near unexpected token `%s'\n"
# define STATE_SIZE		6

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

/*
typedef struct s_expansion
{
	char	*new_word; // Le mot après expansion
	int		new_word_len; // Longueur actuelle du nouveau mot
	int		new_word_capacity; // Capacité allouée pour new_word
}t_expansion;
*/
typedef struct s_expansion
{
	char	*new_word;
	int		new_word_len;
	int		new_word_capacity;
}t_expansion;

int				init_syntax_analyzer(t_token_list *token_list);
t_token_list	*init_token_list(const char *s);

void			expand_variables_and_handle_quotes(char **word, t_env *env);

#endif
