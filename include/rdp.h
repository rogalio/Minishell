/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:55 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/26 17:37:28 by cabdli           ###   ########.fr       */
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

/*
typedef struct s_expansion
{
	char	*new_word; // Le mot après expansion
	int		new_word_len; // Longueur actuelle du nouveau mot
}t_expansion;
*/
typedef struct s_expansion
{
	t_env	*env;
	char	*new_word;
	int		nw_len;
	char	**var_name;
}t_expansion;

t_pipeline	*parse_rdp(t_token_list *token_list, t_env *env);
void		*print_pipeline(t_pipeline *pipeline);
void		free_command(t_command *cmd);
void		free_pipeline(t_pipeline *pipeline);

t_pipeline	*create_pipeline(t_token_list *token_list);
void		add_command_to_pipeline(t_pipeline *pipeline, t_command *cmd);

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
int			get_nw_len(char *word, t_env *env, t_expansion *exp);

/* get_nw_len_expand.c */
int			get_nw_len_expand(char *word, int len, t_env *env, t_expansion *exp);

/* handle_expand.c */
void		handle_expand(char **word, char *new_word, t_env *env, int *i, int *j);
int			is_valid_variable_char(char c);

/* handle_quotes.c */
void		handle_single_quote(char *word, char *new_word, int *i, int *j);
void		handle_double_quote(char *word, char *new_word, t_env *env, int *i, int *j);

#endif
