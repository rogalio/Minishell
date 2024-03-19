/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:47:29 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/19 16:18:39 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"
# include "token.h"
# include "minishell.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_data
{
	t_env			*env;
	// int				return_val;
	// t_token_list	*token_list;
	// t_pipeline		*pipeline;
	char			**args;
}t_data;

typedef struct s_builtins
{
	char	*name;
	int		(*func)(t_data *);
}t_builtins;

void	print_env(t_env *env);
t_env	*init_env(char **envp);
void	free_env(t_env *env);

int		exit_shell(t_data *data);

int		echo(t_data *data);

int		cd(t_data *data);

int		pwd(t_data *data);

int		unset(t_data *data);

#endif