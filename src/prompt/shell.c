/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:02:05 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/14 15:17:25 by cabdli           ###   ########.fr       */
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

void	run_shell(char **envp)
{
	t_data			*data;
	t_token_list	*token_list;
	t_pipeline		*pipeline;
	char			*input;
	char			*prompt;

	data = malloc(sizeof(t_data));
	if (!data)
		return ;
	data->env = init_env(envp);
	while (1)
	{
		init_signals();
		prompt = display_prompt(); // Générer le prompt personnalisé
		input = readline(prompt); // Utiliser le prompt généré
		if (!input || strcmp(input, "exit") == 0)
		{
			free(input);
			free(prompt);
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (input && *input)
			add_history(input); // Ajouter l'entrée à l'historique
		token_list = init_token_list(input);
		//print_token_list(token_list);
		if (init_syntax_analyzer(token_list))
		{
			pipeline = parse_rdp(token_list, data->env);
			// print_pipeline(pipeline);
			execute_pipeline(pipeline, data);
		}
		else
			printf("Error\n");
		free(input);
		free(prompt); // Libérer le prompt après chaque utilisation
		//free_token_list(token_list); // Libérer la liste de tokens
	}
}
