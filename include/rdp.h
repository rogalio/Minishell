/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:55 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/01 19:57:17 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RDP_H
# define RDP_H
# include "libft.h"

#define MAX_ARGS 10

typedef struct s_redirection {
    char *type; // "<", ">", ">>", etc.
    char *file;
} t_redirection;

typedef struct s_command {
    char *cmd;
    char **args; // Tableau de chaînes pour les arguments
    int arg_count;
    t_redirection *redirect; // Redirection associée à la commande
} t_command;

typedef struct s_pipeline {
    t_command **commands; // Tableau de commandes
    int command_count; // Nombre de commandes
    int *pipe_positions; // Positions des pipes
    int pipe_count; // Nombre de pipes
} t_pipeline;

t_pipeline *parse_rdp(t_list *tokens);

#endif
