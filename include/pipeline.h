/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:55 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/06 13:34:27 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include <stdio.h>
# include "libft.h"
# include "token.h"
# include "error.h"
# include "builtins.h"
# include "exp_quotes.h"

typedef struct s_redirection
{
	char	*type;
	char	*file;
}t_redirection;

typedef struct s_heredoc
{
	char	*type;
	char	**delimiter;
	int		nb_heredocs;
}t_heredoc;

typedef struct s_command
{
	char			**args;
	int				args_count;
	t_redirection	*redirect_in;
	t_redirection	*redirect_out;
	t_heredoc		*heredoc;
}t_command;

typedef struct s_pipeline
{
	t_command	**commands;
	int			command_count;
}t_pipeline;

/* init_pipeline.c */
t_pipeline	*create_pipeline(t_token_list *token_list, t_env *env, \
t_error *error);

/* create_commands.c */
int			create_commands(t_pipeline *pipeline, t_token_list *token_list);

/* create_cmds_args.c */
int			create_cmds_args(t_pipeline *pipeline, t_token_list *token_list);

/* fill_pipeline.c*/
int			fill_pipeline(t_token_list *token_list, t_pipeline \
*pipeline, t_env *env);

/* init_redirection.c */
int			init_redirection(t_redirection **redirect, const char *type, \
const char *file);
int			init_heredoc(t_token_list **token_list, t_heredoc **heredoc, \
char *type);

/* print_pipeline.c */
void		*print_pipeline(t_pipeline *pipeline);

/* rdp_free.c */
void		free_redirection(t_redirection *redirection);
void		free_heredoc(t_heredoc *heredoc);
void		free_command(t_command *command);
void		free_commands(t_command **commands, int command_count);
void		free_pipeline(t_pipeline *pipeline);

#endif
