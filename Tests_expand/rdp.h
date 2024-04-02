/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:55 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/02 14:57:44 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RDP_H
# define RDP_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <ctype.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}t_env;

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
	int		quotes;
	int		nb_expand;
	char	**var_name;
	char	**var_value;
	int		nw_len;
	char	*new_word;
}t_expansion;

void		print_env(t_env *env);
t_env		*init_env(char **envp);
void		free_env(t_env *env);
void		print_exp(t_expansion *exp);

/* free_exp.c */
void		free_expansion(t_expansion *exp);
void		free_exp_tab(char **exp_tab);

/* init_exp.c */
t_expansion	*init_exp(void);
char		**create_var_name(char *word, t_expansion *exp);
char		**create_var_value(t_expansion *exp);

/* init_exp_utils.c */
char		*extract_var_name(char *word);
int			is_valid_variable_char(char c);
char		*get_env_value(t_env *env, const char *var_name);

/* expand_var.c */
int			handle_expand_quotes(char **word, t_env *env);

/* get_nw_len.c */
int			get_nw_len(char *word, t_expansion *exp);

/* expand_size */
int			len_plus_exp_size(int len, t_expansion *exp);

/* handle_expand.c */
void		handle_expand(char *word, t_expansion *exp, int *ije);

/* handle_quotes.c */
void		handle_quotes(char *word, t_expansion *exp, int *ije);

#endif
