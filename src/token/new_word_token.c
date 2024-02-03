/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_word_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:34:10 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/03 19:21:21 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token *new_word_token(const char *str)
{
    char *word;
    int i;

    i = 0;
    while (str[i] && !ft_isspace(str[i]))
        i++;
    word = ft_strndup(str, i);
    return new_token(TOKEN_WORD, word);
}