/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:55 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/30 18:54:23 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RDP_H
# define RDP_H
# include "libft.h"

#define MAX_ARGS 10

typedef struct s_command {
    char *cmd;
    char **args; // Un tableau de chaînes pour les arguments
    int arg_count;
} t_command;

typedef struct s_redirection {
    char *type; // "<", ">", ">>", etc.
    char *file;
} t_redirection;



typedef struct s_pipeline {
    t_command **commands;
    t_redirection **redirects;
    int command_count;
    int redirect_count;
} t_pipeline;

t_pipeline *parse_rdp(t_list *tokens);

#endif
