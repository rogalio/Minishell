/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:02:05 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/16 00:23:33 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "minishell.h"
#include "exec.h"
#include "token.h"
#include "parser.h"
#include "rdp.h"
#include "builtins.h"
#include "signals.h"

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		//exit(EXIT_FAILURE);
		return (NULL);
	}
	data->env = init_env(envp);
	//data->token_list = NULL;
	//data->pipeline = NULL;
	data->args = NULL;
	return (data);
}

void	run_shell(char **envp)
{
	t_data			*data;
	t_token_list	*token_list;
	t_pipeline		*pipeline;
	char			*input;
	char			*prompt;

	data = init_data(envp);
	while (1)
	{
		init_signals();
		prompt = display_prompt();
		input = readline(prompt);
		if (!input || strcmp(input, "exit") == 0)
		{
			free(input);
			free(prompt);
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (*input)
			add_history(input);
		token_list = init_token_list(input);
		if (init_syntax_analyzer(token_list))
		{
			pipeline = parse_rdp(token_list, data->env);
			execute_pipeline(pipeline, data);
		}
		else
			ft_putstr_fd("minishell: syntax error near unexpected token\n", \
			STDERR_FILENO);
		free(input);
		free(prompt);
		//free_token_list(token_list);
	}
}
