/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:37 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/26 15:42:44 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft.h"
# include "data.h"
# include "token.h"
# include "pipeline.h"
# include "error.h"

extern int	g_exit_signal;

# define SUCCESS 0
# define UNEXPEC_ERR 1
# define SYNTAX_ERR 2
# define NOTFOUND_ERR 127
# define SIGINT_ERR 130
# define SIGQUIT_ERR 131
# define PERM_ERR 126
# define UNKNOWN_ERR 255

typedef struct s_minishell
{
	t_data			*data;
	t_token_list	*token_list;
	t_pipeline		*pipeline;
	int				exit_status;
	t_error			error;
}t_minishell;

void	free_minishell(t_minishell **minishell);
void	free_resources(t_minishell *minishell);

#endif
