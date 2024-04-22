/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/22 17:59:32 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "prompt.h"

int	g_exit_signal;

void	free_data(t_data **data)
{
	if (!data || !*data)
		return ;
	free_env(&(*data)->env);
	free(*data);
	*data = NULL;
}

void	free_minishell(t_minishell **minishell)
{
	if (!minishell || !*minishell)
		return ;
	free_data(&(*minishell)->data);
	free(*minishell);
	*minishell = NULL;
}

static t_data	*init_data(char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = init_env(envp);
	if (!data->env)
		return (free(data), NULL);
	return (data);
}

static t_minishell	*init_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
		return (NULL);
	minishell->data = init_data(envp);
	if (!minishell->data)
		return (free(minishell), NULL);
	return (minishell);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;

	(void)argv;
	minishell = NULL;
	if (argc != 1)
		return (ft_putstr_fd("Error: too many arguments\n", 2), 1);
	minishell = init_minishell(envp);
	if (!minishell)
		return (1);
	run_shell(minishell);
	free_minishell(&minishell);
	return (0);
}

/*
-> Fill_pipeline, redirection :
* gerer les caracteres speciaux ? = s'ils sont seuls les refuser sinon OK
* enlever les '\' ?
* refuser les '/' et les noms de fichier trop longs : OK, open s'en charge

-> changer free_pipeline en passant **pipeline, pour mettre pipeline a NULL
-> pareil que precedemment pour free_token (+mettre a NULL)

-> 255 = terminaison anormale des processus : voir msg elodie,
return values, pour gestion exit status, inverser verifications 
(return 0 si tout va bien et sinon return les bons codes error)

-> pb pour get_env en cas d'echec de strdup : comment differencier
un echec de strdup et une value non existante ?
create_node :
else
	{
		node->name = strdup(env_entry);
		node->value = NULL;
	}
*/
