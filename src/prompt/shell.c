/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:02:05 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/22 17:59:38 by cabdli           ###   ########.fr       */
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
	if (!*input)
		return (0);
	minishell->token_list = create_token_list(input, &(minishell->error));
	if (!(minishell->token_list))
		return (print_err_msg(&(minishell->error)), 0);
	print_token_list(minishell->token_list);
	if (!syntax_analyzer(minishell->token_list, &(minishell->error)))
	{
		print_err_msg(&(minishell->error));
		return (free_token_list(&minishell->token_list), 0);
	}
	minishell->pipeline = create_pipeline(minishell->token_list, \
	minishell->data->env, &(minishell->error));
	print_pipeline(minishell->pipeline);
	if (!minishell->pipeline)
	{
		print_err_msg(&(minishell->error));
		return (free_token_list(&minishell->token_list), 0);
	}
	return (1);
}

/*
static void	free_cmd_resources(t_minishell *minishell)
{
	free_token_list(&minishell->token_list);
	free_pipeline(&minishell->pipeline);
}
*/

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
		{
			if (handle_heredocs(minishell->pipeline, minishell))
				execute_pipeline(minishell->pipeline, minishell->data, minishell);
			free_cmd_resources(minishell);
		}
		free(input);
	}
	return ;
}
