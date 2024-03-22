/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:02:05 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/22 13:52:08 by cabdli           ###   ########.fr       */
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

static int	parse_input(t_minishell *minishell, char *input)
{
	minishell->token_list = init_token_list(input);
	if (!minishell->token_list)
		return (0);
	if (!init_syntax_analyzer(minishell->token_list))
		return (ft_putstr_fd("minishell: syntax error near unexpected token\n", \
		STDERR_FILENO), 0);
	printf("\n\nTest debug\n\n");
	minishell->pipeline = parse_rdp(minishell->token_list, minishell->data->env);
	if (!minishell->pipeline)
		return (0);
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
		if (!input || strcmp(input, "exit") == 0)
			break ;
		if (parse_input(minishell, input))
			execute_pipeline(minishell->pipeline, minishell->data);
		free(input);
		//free_token_list(minishell->token_list);
		//free_pipeline(minishell->pipeline);
	}
}
