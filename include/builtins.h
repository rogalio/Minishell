/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:47:29 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/05 22:30:07 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"
# include "data.h"
# include "minishell.h"

typedef struct s_builtins
{
	char	*name;
	int		(*func)(t_data *, t_minishell *);
}t_builtins;

/* exit.c */
void	free_minishell(t_minishell **minishell);
void	free_resources(t_minishell *minishell);
int		exit_shell(t_data *data, t_minishell *minishell);

/* env.c */
int		env(t_data *data, t_minishell *minishell);
void	free_env(t_env **env);
int		add_to_env_list(t_env **head, char *envp);
t_env	*init_env(char **envp);

/* env_utils.c */
int		init_shlvl(t_env *env_list);

/* echo.c */
int		echo(t_data *data, t_minishell *minishell);

/* cd.c */
int		cd(t_data *data, t_minishell *minishell);

/* pwd.c */
int		pwd(t_data *data,	t_minishell *minishell);

/* unset.c */
int		unset(t_data *data, t_minishell *minishell);

/* export.c */
int		export(t_data *data, t_minishell *minishell);

#endif