/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:02:05 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/12 14:35:32 by cabdli           ###   ########.fr       */
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
	t_token_list	*token_list;
	t_pipeline		*pipeline;
	int				verify;
	char			*input;
	char			*prompt;

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
		verify = init_syntax_analyzer(token_list);
		if (verify)
		{
			pipeline = parse_rdp(token_list, envp);
			// print_pipeline(pipeline);
			execute_pipeline(pipeline, envp);
		}
		else
			printf("Error\n");
		free(input);
		free(prompt); // Libérer le prompt après chaque utilisation
		//free_token_list(token_list); // Libérer la liste de tokens
	}
}
