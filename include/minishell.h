/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:37 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/08 20:40:03 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft.h"
# include "builtins.h"
# include "token.h"
# include "rdp.h"

typedef struct s_minishell
{
	t_data			*data;
	t_token_list	*token_list;
	t_pipeline		*pipeline;
	int				exit_status;
}t_minishell;

void free_minishell(t_minishell **minishell);

// test


#endif
