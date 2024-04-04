/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:02:05 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/04 12:42:26 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "exec.h"
#include "token.h"
#include "parser.h"
#include "rdp.h"
#include "builtins.h"
#include "signals.h"

int	parse_input()
{
	
}

void	run_shell(t_minishell *minishell)
{
	char			*input;

	input = NULL;
	while (1)
	{
		init_signals();
		if (parse_input())
		input = display_and_readline();
		if (!input)
			break ;
		minishell->token_list = create_token_list2(input);
		if (!(minishell->token_list))
			return;
		if (!syntax_analyzer(minishell->token_list))
		{
			printf("syntax error\n");
			free_token_list(&minishell->token_list);
			return;
		}
		minishell->pipeline = create_pipeline2(minishell->token_list, \
		minishell->data->env);
		if (!minishell->pipeline)
		{
			printf("pipeline is NULL\n");
			free_token_list(&minishell->token_list);
			return;
		}
		free_token_list(&minishell->token_list);
		free_pipeline(minishell->pipeline);
		free(input);
	}
}
