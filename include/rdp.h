/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:55 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/05 18:36:53 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RDP_H
# define RDP_H
# include "libft.h"
# include <stdio.h>
# include "token.h"

#define MAX_ARGS 10

typedef struct s_redirection_in
{
    char *type;
    char *file;
} t_redirection_in;

typedef struct s_redirection_out
{
    char *type;
    char *file;
} t_redirection_out;

typedef struct s_command
{
    char **args;
    t_redirection_in *redirect_in;
    t_redirection_out *redirect_out;
} t_command;

typedef struct s_pipeline
{
    t_command **commands;
    int command_count;
} t_pipeline;

t_pipeline *parse_rdp(t_token_list *tokens);
void print_pipeline(t_pipeline *pipeline);

#endif
