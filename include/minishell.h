/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:56:37 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/12 15:05:37 by cabdli           ###   ########.fr       */
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



typedef struct s_minishell
{
	t_data			*data;
	t_token_list	*token_list;
	t_pipeline		*pipeline;
	int				exit_status;
	t_error			error;
}t_minishell;

void	free_minishell(t_minishell **minishell);


#endif
