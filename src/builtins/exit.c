/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:20:13 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/23 15:28:53 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/*
// modifier ce code pour qu'il fonctionne et gerer le free en cas de success()
int	exit_shell(t_data *data, t_minishell *minishell)
{
	(void)minishell;
	if (data->args[1])
	{
		if (!ft_isnumber(data->args[1]))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(data->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(EXIT_FAILURE);
			return (2);
		}
		if (data->args[2])
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			exit(EXIT_FAILURE);
			return (1);
		}
		return (ft_atoi(data->args[1]));
	}
	ft_putstr_fd("exit\n", 2);
	free_token_list(&minishell->token_list);
	free_pipeline(minishell->pipeline);
	free_minishell(&minishell);
	exit(EXIT_SUCCESS);
	return (0);
}
*/

void free_resources(t_minishell *minishell)
{
    // Libérer la liste des tokens, le pipeline, et d'autres allocations mémoire.
    free_token_list(&minishell->token_list);
    free_pipeline(&minishell->pipeline);
    free_minishell(&minishell);
}

int	exit_shell(t_data *data, t_minishell *minishell)
{
    // Annonce la commande exit.
    ft_putstr_fd("exit\n", 2);

    // Si un argument est fourni
    if (data->args[1])
    {
        // Si l'argument n'est pas un nombre
        if (!ft_isnumber(data->args[1]))
        {
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(data->args[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            // Libérer les ressources ici si nécessaire.
            free_resources(minishell); // Exemple de fonction de nettoyage.
            exit(EXIT_FAILURE);
        }
        // Si plus d'un argument est fourni
        if (data->args[2])
        {
            ft_putstr_fd("minishell: exit: too many arguments\n", 2);
            // Dans ce cas, nous n'arrêtons pas le shell selon les spécifications POSIX.
            return 1; // Retourne avec une erreur, mais ne quitte pas.
        }
        // Un seul argument numérique valide est fourni. Utilisez-le comme code de sortie.
        int exit_code = ft_atoi(data->args[1]);
        free_resources(minishell); // Nettoyage avant de quitter.
        exit(exit_code);
    }
    free_resources(minishell);
    exit(EXIT_SUCCESS);
}

