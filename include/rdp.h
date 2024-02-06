/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:55 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/06 13:14:16 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RDP_H
# define RDP_H
# include "libft.h"
# include <stdio.h>
# include "token.h"

#define MAX_ARGS 10

typedef struct s_redirection
{
    char *type;
    char *file;
} t_redirection;

typedef struct s_command
{
    char **args;
    t_redirection *redirect_in;
    t_redirection *redirect_out;
} t_command;

typedef struct s_pipeline
{
    t_command **commands;
    int command_count;
} t_pipeline;

t_pipeline *parse_rdp(t_token_list *tokens);
void print_pipeline(t_pipeline *pipeline);
void free_command(t_command *cmd);
void free_pipeline(t_pipeline *pipeline);

t_pipeline *init_pipeline();
void add_command_to_pipeline(t_pipeline *pipeline, t_command *cmd);

t_command *create_command(void);
int count_args(t_command *cmd);
char **allocate_new_args(t_command *cmd, int new_count);
void append_argument(char **args, int position, char *arg);
void add_argument_to_command(t_command *command, char *arg);

void handle_redirection(t_token_list **tokens, t_command *command);
void handle_word(t_command **current_command, char *word);
void handle_pipe(t_pipeline *pipeline, t_command **current_command);

#endif
