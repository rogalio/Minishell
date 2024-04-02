/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 02:21:09 by asoursou          #+#    #+#             */
/*   Updated: 2024/03/27 17:05:11 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_string.h"

char    *ft_strndup(const char *s1, size_t n)
{
    char    *new_str;
    size_t  len = 0;

    while (s1[len] && len < n)
        len++;
    new_str = (char *)ft_calloc(len + 1, sizeof(char));
    if (new_str == NULL)
        return (NULL);
    for (size_t i = 0; i < len; i++)
        new_str[i] = s1[i];
    return (new_str);
}
