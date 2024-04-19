/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_quotes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:06:53 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/19 13:28:36 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXP_QUOTES_H
# define EXP_QUOTES_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "data.h"

typedef struct s_expansion
{
	t_env	*env;
	int		quotes;
	int		s_quotes;
	int		nb_expand;
	char	**var_name;
	char	**var_value;
	int		nw_len;
	char	*new_word;
}t_expansion;

/* free_exp.c */
void		free_exp_tab(char **exp_tab);
void		free_expansion(t_expansion *exp);
void		print_exp(t_expansion *exp);

/* init_exp.c */
t_expansion	*init_exp(void);
char		**create_var_name(char *word, t_expansion *exp);
char		**create_var_value(t_expansion *exp);

/* init_exp_utils.c */
char		*extract_var_name(char *word);
int			is_valid_variable_char(char c);
char		*get_env_value(t_env *env, const char *var_name);

/* handle_expand_quotes.c */
int			handle_expand_quotes(char **word, t_env *env);
int			check_if_quotes(char *word, t_expansion	*exp);

/* get_nw_len.c */
int			get_nw_len(char *word, t_expansion *exp);

/* expand_size */
int			len_plus_exp_size(int len, t_expansion *exp);

/* handle_expand.c */
void		handle_expand(char *word, t_expansion *exp, int *ije);

/* handle_quotes.c */
void		handle_quotes(char *word, t_expansion *exp, int *ije);

/* expand_quotes.c */
int			expand_quotes(char *word);

#endif