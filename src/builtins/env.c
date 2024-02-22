/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:50:14 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/22 16:59:06 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

t_env   *create_env_node(char *env_entry)
{
    t_env   *node;
    char    *separator;

    node = malloc(sizeof(t_env));
    if (!node)
        return NULL;
    separator = strchr(env_entry, '=');
    if (separator)
    {
        node->name = strndup(env_entry, separator - env_entry);
        node->value = strdup(separator + 1);
    } else
    {
        node->name = strdup(env_entry);
        node->value = NULL;
    }
    node->next = NULL;
    return node;
}

t_env   *add_to_env_list(t_env *head, t_env *new_node)
{
    t_env   *temp;

    if (!head)
        return new_node;
    temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
    return head;
}


char   *get_env_var(t_env *env, char *name)
{
    while (env)
    {
        if (strcmp(env->name, name) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}

t_env   *init_env(char **envp)
{
    t_env   *env;
    int     i;

    env = NULL;
    i = 0;
    while (envp[i])
    {
        env = add_to_env_list(env, create_env_node(envp[i]));
        i++;
    }
    return env;
}

void set_env_var(t_env *env, char *name, char *value)
{
    while (env)
    {
        if (strcmp(env->name, name) == 0)
        {
            if (env->value)
                free(env->value);
            env->value = strdup(value);
            return;
        }
        env = env->next;
    }
    env = malloc(sizeof(t_env));
    env->name = strdup(name);
    env->value = strdup(value);
    env->next = NULL;
}

void    print_env(t_env *env)
{
    while (env) {
        if (env->value)
            printf("%s=%s\n", env->name, env->value);
        else
            printf("%s\n", env->name);
        env = env->next;
    }
}

void    free_env(t_env *env)
{
    t_env *tmp;

    while (env) {
        tmp = env->next;
        free(env->name);
        if (env->value)
            free(env->value);
        free(env);
        env = tmp;
    }
}





