/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:55 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/02 16:49:04 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RDP_H
# define RDP_H
# include "libft.h"

#define MAX_ARGS 10

typedef struct s_redirection
{
    char *type;
    char *file;
} t_redirection;

typedef struct s_command
{
    char **args;
    t_redirection *redirect;
} t_command;

typedef struct s_pipeline
{
    t_command **commands;
    int command_count;
} t_pipeline;

t_pipeline *parse_rdp(t_list *tokens);

#endif
