/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:47:29 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/20 12:53:19 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_data
{
  char	**env;
  char	**args;
}	t_data;

typedef struct s_builtins
{
  char	*name;
  int	(*func)(t_data *);
}	t_builtins;

typedef struct s_env
{
  char	*name;
  char	*value;
  struct s_env	*next;
}	t_env;



void	print_env(t_env *env);
t_env	*init_env(char **envp);



#endif