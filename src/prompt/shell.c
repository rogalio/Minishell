/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:02:05 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/04 13:50:32 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "exec.h"
#include "token.h"
#include "parser.h"
#include "pipeline.h"
#include "builtins.h"
#include "signals.h"

static int	parse_input(t_minishell *minishell, char *input)
{
	minishell->token_list = create_token_list2(input);
	if (!(minishell->token_list))
		return (ft_putstr_fd("Error: malloc failure\n", STDERR_FILENO), 0);
	if (!syntax_analyzer(minishell->token_list))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", \
		STDERR_FILENO);
		return (free_token_list(&(minishell->token_list)), 0);
	}
	minishell->pipeline = create_pipeline2(minishell->token_list, \
	minishell->data->env);
	if (!minishell->pipeline)
	{
		ft_putstr_fd("Error: malloc failure\n", STDERR_FILENO);
		return (free_token_list(&(minishell->token_list)), 0);
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
		{
			free(input);
			return ;
		}
		free_token_list(&minishell->token_list);
		free_pipeline(minishell->pipeline);
		free(input);
	}
	return ;
}

/*
static int	parse_input(t_minishell *minishell, char *input)
{
	minishell->token_list = init_token_list(input);
	if (!(minishell->token_list))
		return (0);
	if (!syntax_analyzer(minishell->token_list))
		return (ft_putstr_fd("minishell: syntax error near unexpected token\n", \
		STDERR_FILENO), 0);
	minishell->pipeline = parse_rdp(minishell->token_list, \
	minishell->data->env);
	if (!minishell->pipeline)
		return (0);
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
		if (parse_input(minishell, input))
			execute_pipeline(minishell->pipeline, minishell->data);
		free(input);
		free_token_list(minishell->token_list);
		free_pipeline(minishell->pipeline);
	}
}
*/
