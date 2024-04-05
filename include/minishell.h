/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:37 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/05 13:42:55 by cabdli           ###   ########.fr       */
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
# include "pipeline.h"

typedef struct s_minishell
{
	t_data			*data;
	t_token_list	*token_list;
	t_pipeline		*pipeline;
	int				exit_status;
	t_error			error;
}t_minishell;

#endif
