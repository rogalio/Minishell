/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:55 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/02 16:06:15 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RDP_H
# define RDP_H

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

typedef struct s_expansion
{
	t_env	*env;
	char	**var_name;
	char	**var_value;
	int		nw_len;
	char	*new_word;
}t_expansion;

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

/* expand_var.c */
void		handle_expand_quotes(char **word, t_env *env);

/* get_nw_len.c */
int			get_nw_len(char *word, t_expansion *exp);

/* get_nw_len_expand.c */
int			get_nw_len_expand(char *word, int len, t_expansion *exp);

/* expand_size */
int			len_plus_exp_size(int len, t_expansion *exp);
char		*get_env_value(t_env *env, const char *var_name);

/* handle_expand.c */
void		handle_expand(char **word, char *new_word, char *var_value, int *i, int *j);

/* handle_quotes.c */
void		handle_single_quote(char *word, char *new_word, int *i, int *j);
int		handle_double_quote(char *word, char *new_word, char *var_value, int *i, int *j);

t_pipeline	*create_pipeline2(t_token_list *token_list, t_env *env);
t_pipeline	*init_pipeline(void);


#endif
