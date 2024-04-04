/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:55 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/04 13:48:02 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include <stdio.h>
# include "libft.h"
# include "token.h"
# include "builtins.h"

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

t_pipeline	*parse_rdp(t_token_list *token_list, t_env *env);
void		*print_pipeline(t_pipeline *pipeline);

t_pipeline	*create_pipeline(t_token_list *token_list);
void		add_command_to_pipeline(t_pipeline *pipeline, t_command *cmd);

/* rdp_free.c */
void free_redirection(t_redirection *redirection);
void free_heredoc(t_heredoc *heredoc);
void free_command(t_command *command);
void free_commands(t_command **commands, int command_count);
void free_pipeline(t_pipeline *pipeline);

/* rdp_commands.c */
t_command	*create_cmd(void);

int			count_args(t_command *cmd);
void		add_argument_to_command(t_command *command, char *arg);

/* rdp_token_handlers.c */
void		handle_redirection(t_token_list **token_list, t_command *command);
void		handle_word(int *index, char *word, t_pipeline *pipeline, \
t_env *env);
void		handle_pipe(t_pipeline *pipeline, t_command **current_command);

/* rdp_pipeline_utils.c */
void		get_args_count(t_pipeline *pipeline, t_token_list *token_list);
int			get_pipe_count(t_token_list *token_list);

t_heredoc	*create_heredoc(int nb_heredocs);
int			get_nb_heredocs(t_token_list *tmp_list);

t_pipeline	*create_pipeline2(t_token_list *token_list, t_env *env);
t_pipeline	*init_pipeline(void);


#endif
