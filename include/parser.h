/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:40:36 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/01 18:25:00 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "libft.h"
# include "token.h"

# define ERR_UNEXPECT	"minishell: syntax error near unexpected token `%s'\n"
# define STATE_SIZE		6

/*
** All known stack events.
** STACK_EMPTY:		if stack is empty
** STACK_NEMPTY:	if stack is not empty
** STACK_POP:		pop 1
** STACK_PUSH:		push 1
*/
enum	e_stack_event
{
	STACK_EMPTY = 1,
	STACK_NEMPTY,
	STACK_POP,
	STACK_PUSH
};
typedef enum e_stack_event	t_stack_event;

/*
** A transition rule in the pushdown automaton
** from:	The current state id
** to:		The next state id
** type:	The symbol associated with the transition
** event:	The stack event associated with the transition (0 for none)
*/
struct	s_rule
{
	int				from;
	int				to;
	t_token_type	type;
	t_stack_event	event;
};
typedef struct s_rule	t_rule;

/*
** The pushdown automaton used for minishell.
** final:	is final state?
** last:	temporary array for O(k) complexity where k is the number of rules
**			for the given state
** rules:	all transitions rules of the FSM
** stack:	used for parenthesis detection
*/
struct	s_pda
{
	bool			final[STATE_SIZE];
	int				last[STATE_SIZE];
	const t_rule	*rules;
	int				stack;
};
typedef struct s_pda	t_pda;

/*
** This function is called by is_valid.
*/
//void	pda_init(t_pda *p);
int		pda_init(t_list *list);
int pda_verify(t_list *tokens);
int validate_tokens(t_list *tokens);

/*
** Checks if the given list of tokens is a valid expression.
** Returns 1 if the expression is valid, 0 if invalid, -1 if multiline.
*/
int		is_valid(t_list *tokens);

/*
** Creates a list of tokens from a string.
** Returns the new list of tokens.
*/
t_list	*tokenize(const char *s);

#endif
