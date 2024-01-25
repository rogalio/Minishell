/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:14:00 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/25 17:24:53 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


t_list *ft_lst_new(void *content)
{
    t_list *l;

    if (!(l = (t_list *)malloc(sizeof(t_list))))
        return (NULL);
    l->content = content;
    l->next = NULL;
    return (l);
}

t_list *ft_lstadd_back(t_list **alst, t_list *new)
{
    t_list *l;

    if (!alst)
        return (NULL);
    if (!*alst)
        *alst = new;
    else
    {
        l = *alst;
        while (l->next)
            l = l->next;
        l->next = new;
    }
    return (new);
}

static int skip_whitespace(const char **str)
{
    while (**str && ft_isspace(**str))
        (*str)++;
    return **str != '\0';
}

static t_token *find_next_token(const char **str)
{
    t_token *token = token_find(*str);
    if (token)
        *str += ft_strlen(token->value);
    return token;
}

static t_token *create_word_token(const char **str)
{
    const char *start = *str;
    while (**str && !ft_isspace(**str) && !token_find(*str))
        (*str)++;

    if (*str > start)
        return token_new(TOKEN_WORD, ft_strndup(start, *str - start));
    return NULL;
}

static void add_token_to_list(t_list **list, t_token *token)
{
    if (token)
        ft_lstadd_back(list, ft_lst_new(token));
}

t_list *tokenize2(const char *str)
{
    t_list *list = NULL;
    t_token *token;

    while (*str)
    {
        if (!skip_whitespace(&str))
            break;

        token = find_next_token(&str);
        if (!token)
            token = create_word_token(&str);

        add_token_to_list(&list, token);
    }
    return list;
}






