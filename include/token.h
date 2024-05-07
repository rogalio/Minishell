/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:43:08 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/07 11:47:25 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "error.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIRECT,
	TOKEN_PIPE,
}t_token_type;

/*
	Represents a token.
	type:	type of the token
	value:	graphical representation
*/
typedef struct s_token
{
	t_token_type	type;
	char			*value;
}t_token;

typedef struct s_token_list
{
	t_token				*token;
	struct s_token_list	*next;
}t_token_list;

/* create_token_list.c */
t_token_list	*create_token_list(const char *str, t_error *error);

/* parse_token.c */
t_token			*parse_token(const char *str, t_error *error);

/* new_token.c */
t_token			*new_token(t_token_type type, char *value);
t_token			*new_token_word(const char *str, t_error *error);
t_token_list	*new_token_node(t_token *token);

/* new_token_utils.c */
char			*handle_qtes(const char *str, t_error *error);
char			*handle_rest(const char *str, t_error *error);
int				ft_isquote(char c, char quote);

/* print_token.c*/
void			print_token(const t_token *t);
void			print_token_list(t_token_list *list);

/* free_token.c */
void			free_token(t_token *token);
void			free_token_list(t_token_list **list);

/* utils.c */
int				skip_whitespace(const char **str);
int				check_regex(const char *s);

#endif