/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:02:05 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/05 13:10:43 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "token.h"
#include "parser.h"
#include "pipeline.h"
#include "exec.h"
#include "builtins.h"
#include "signals.h"

static int	parse_input(t_minishell *minishell, char *input)
{
	minishell->token_list = create_token_list(input, &(minishell->error));
	if (!(minishell->token_list))
		return (print_err_msg(&(minishell->error)), 0);
	if (!syntax_analyzer(minishell->token_list, &(minishell->error)))
		return (print_err_msg(&(minishell->error)), \
		free_token_list(minishell->token_list), 0);
	minishell->pipeline = create_pipeline2(minishell->token_list, \
	minishell->data->env);
	if (!minishell->pipeline)
	{
		ft_putstr_fd("Error: malloc failure\n", STDERR_FILENO);
		return (free_token_list(minishell->token_list), 0);
	}
	print_pipeline(minishell->pipeline);
	return (1);
}


void	run_shell(t_minishell *minishell)
{
	char			*input;

	input = NULL;
	while (1)
	{
		init_signals();
		input = display_and_readline();
		if (!input)
			break ;
		if (!parse_input(minishell, input))
			free(input);
		else
		{
			free_token_list(minishell->token_list);
			free_pipeline(minishell->pipeline);
			free(input);
		}
	}
	return ;
}

/*
void	run_shell(t_minishell *minishell)
{
	char			*input;

	input = NULL;
	while (1)
	{
		init_signals();
		input = display_and_readline();
		if (!input)
			break ;
		if (parse_input(minishell, input))
			execute_pipeline(minishell->pipeline, minishell->data);
		free(input);
		free_token_list(minishell->token_list);
		free_pipeline(minishell->pipeline);
	}
}
*/
