/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:47:29 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/01 13:34:07 by cabdli           ###   ########.fr       */
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

int		echo(t_data *data, t_minishell *minishell);

int		cd(t_data *data, t_minishell *minishell);

int		pwd(t_data *data,	t_minishell *minishell);

int		unset(t_data *data, t_minishell *minishell);

int		export(t_data *data, t_minishell *minishell);

#endif