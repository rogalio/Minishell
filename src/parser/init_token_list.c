/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:19:30 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/29 16:18:52 by rogalio          ###   ########.fr       */
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














void print_tokenlist2(t_token_list *token_list, int i)
{
	t_token_list	*tmp;

	tmp = token_list;
	while (tmp)
	{
		printf("token %d\n", i);
		printf("type: %d\n", tmp->token->type);
		printf("value: %s\n", tmp->token->value);
		tmp = tmp->next;
		i++;
	}
}



t_token_list	*init_token_listv2(void)
{
	t_token_list	*list;

	list = ft_calloc(1, sizeof(t_token_list));
	if (!list)
		return (NULL);
	list->token = ft_calloc(1, sizeof(t_token));
	if (!list->token)
	{
		free(list);
		return (NULL);
	}
	return (list);
}


void add_token_to_list2(t_token_list **list, t_token *token)
{
	t_token_list	*new_element;
	t_token_list	*temp;

	if (!list || !token)
		return ;
	new_element = ft_calloc(1, sizeof(t_token_list));
	if (!new_element)
		return ;
	new_element->token = token;
	new_element->next = NULL;
	if (!*list)
	{
		*list = new_element;
	}
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_element;
	}
}

t_token_list	*create_token_list2(const char *str)
{
	t_token_list	*list;
	t_token			*token;

	list = init_token_listv2();
	if (!list)
		return (NULL);
	while (*str)
	{
		if (skip_whitespace(&str) == 0)
			break ;
		token = find_next_token(&str);
		if (token)
			add_token_to_list2(&list, token);
	}
	return (list);
}
