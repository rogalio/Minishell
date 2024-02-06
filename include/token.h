/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:43:08 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/06 13:30:49 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"

/*
** All known symbols type.
*/
enum		e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIRECT,
	TOKEN_PIPE,
};
typedef enum e_token_type	t_token_type;

/*
** Represents a token.
** type:	type of the token
** value:	graphical representation
*/
struct		s_token
{
	t_token_type	type;
	char			*value;
};
typedef struct s_token	t_token;


struct s_token_list
{
	t_token			*token;
	struct s_token_list	*next;
};
typedef struct s_token_list	t_token_list;




t_token *new_word_token(const char *str);
t_token		*new_token(t_token_type type, char *value);
void		print_token(const t_token *t);
t_token *parse_token(const char *str);
t_token_list *new_token_list(t_token *token);
t_token *parse_token(const char *str);
void	print_token_list(t_token_list *list);
void free_token_list(t_token_list *list);


#endif
