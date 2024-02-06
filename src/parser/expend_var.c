/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:56:15 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/06 18:24:33 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"
#include "token.h"
#include "parser.h"

char *get_env_value(char **env, const char *var)
{
    int i;
    int j;
    int k;
    char *value;

    i = 0;
    while (env[i])
    {
        j = 0;
        k = 0;
        while (env[i][j] && env[i][j] != '=')
            j++;
        if (ft_strncmp(env[i], var, j) == 0)
        {
            value = malloc(sizeof(char) * (ft_strlen(env[i]) - j));
            j++;
            while (env[i][j])
                value[k++] = env[i][j++];
            value[k] = '\0';
            return value;
        }
        i++;
    }
    return NULL;
}

int is_valid_variable_char(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}
char *extract_variable_name(const char *word, int *index)
{
    int start = *index;
    while (word[*index] && is_valid_variable_char(word[*index]))
        (*index)++;
    return ft_strndup(&word[start], *index - start);
}

void replace_variable(char **new_word, char **env, const char *var_name, int *j)
{
    char *value = get_env_value(env, var_name);
    int value_len = ft_strlen(value);
    *new_word = realloc(*new_word, sizeof(char) * (*j + value_len + 1));
    ft_strlcat(*new_word, value, *j + value_len + 1);
    *j += value_len;
    free(value);
}

void handle_single_quote(const char *word, char *new_word, int *i, int *j)
{
    (*i)++;
    while (word[*i] && word[*i] != '\'')
        new_word[(*j)++] = word[*i++];
}

void handle_variable(char **word, char *new_word, char **env, int *i, int *j)
{
    char *var_name;
    (*i)++;
    var_name = extract_variable_name(*word, i);
    replace_variable(&new_word, env, var_name, j);
    free(var_name);
}


void handle_double_quote(const char *word, char *new_word, char **env, int *i, int *j)
{
    (*i)++;
    while (word[*i] && word[*i] != '\"')
    {
        if (word[*i] == '$')
        {
            (*i)++;
            char *var_name = extract_variable_name(word, i);
            replace_variable(&new_word, env, var_name, j);
            free(var_name);
        }
        else
            new_word[(*j)++] = word[*i++];
    }
}

void expand_variables_and_handle_quotes(char **word, char **env)
{
    char *new_word;
    int i, j;

    new_word = malloc(sizeof(char) * (ft_strlen(*word) + 1));
    i = 0;
    j = 0;
    while ((*word)[i])
    {
        if ((*word)[i] == '\'')
            handle_single_quote(*word, new_word, &i, &j);
        else if ((*word)[i] == '\"')
            handle_double_quote(*word, new_word, env, &i, &j);
        else if ((*word)[i] == '$')
            handle_variable(word, new_word, env, &i, &j);
        else
            new_word[j++] = (*word)[i++];
    }
    new_word[j] = '\0';
    free(*word);
    *word = new_word;
}

