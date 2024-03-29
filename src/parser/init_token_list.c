/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:19:30 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/29 15:37:17 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "token.h"
#include "utils.h"

t_token	*find_next_token(const char **str)
{
	t_token	*token;

	token = parse_token(*str);
	if (token)
		*str += ft_strlen(token->value);
	return (token);
}

static void	add_token_to_list(t_token_list **list, t_token *token)
{
	t_token_list	*new_elem;
	t_token_list	*tmp;

	new_elem = ft_calloc(1, sizeof(t_token_list));
	if (!new_elem)
		return ;
	new_elem->token = token;
	if (!*list)
		*list = new_elem;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_elem;
	}
}





t_token_list	*init_token_list(const char *str)
{
	t_token_list	*list;
	t_token			*token;

	list = NULL;
	token = NULL;
	while (*str)
	{
		if (skip_whitespace(&str) == 0)
			break ;
		token = find_next_token(&str);
		if (token)
			add_token_to_list(&list, token);
	}
	//print_tokenlist2(list);
	return (list);
}



/*
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
*/



t_token_list	*init_token_listv2()
{
	t_token_list	*list;

	list = ft_calloc(1, sizeof(t_token_list));
	if (!list)
		return (NULL);
	list->token = NULL;
	list->next = NULL;
	return (list);
}


void print_tokenlist2(t_token_list *list)
{
	t_token_list	*tmp;

	tmp = list;
	while (tmp)
	{
		print_token(tmp->token);
		tmp = tmp->next;
	}
}



t_token_list	*create_token_list2(const char *str)
{
	t_token_list	*list;
	t_token			*token;

	list = NULL;
	list = init_token_listv2();
	while (*str)
	{
		if (skip_whitespace(&str) == 0)
			break ;
		token = find_next_token(&str);
		if (token)
			add_token_to_list(&list, token);
	}
	print_tokenlist2(list);
	return (list);
}
