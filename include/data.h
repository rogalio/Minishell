/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:37:23 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/12 16:42:09 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_data
{
	t_env			*env;
	char			**args;
}t_data;

/* env.c */
void	print_env(t_env *env);
t_env	*init_env(char **envp);
void	free_env(t_env **env);


#endif