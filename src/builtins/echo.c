/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:43 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/17 18:34:22 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "pipeline.h"

static int is_valid_n_option(char *arg)
{
    int j;

    if (strncmp(arg, "-n", 2) != 0)
        return 0;
    j = 2;
    while (arg[j] != '\0')
    {
        if (arg[j] != 'n')
            return 0;
        j++;
    }
    return 1;
}

static void print_arguments(char **args, int start_index, int print_newline)
{
    int i;

    i = start_index;
    while (args[i] != NULL)
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1] != NULL)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (print_newline)
        write(STDOUT_FILENO, "\n", 1);
}

int echo(t_data *data, t_minishell *minishell)
{
    int i;
    int n_option;

    (void)minishell;
    i = 1;
    n_option = 0;
    while (data->args[i] != NULL && is_valid_n_option(data->args[i]))
    {
        i++;
        n_option = 1;
    }

    print_arguments(data->args, i, !n_option);
    return 0;
}




/*
int	echo(t_data *data, t_minishell *minishell)
{
	(void)minishell;
	int	i;

	i = 1;
	if (!ft_strcmp(data->args[i], "-n"))
	{
		i++;
		while (data->args[i])
		{
			ft_putstr_fd(data->args[i++], 1);
			if (data->args[i])
				write(1, " ", 1);
		}
	}
	else
	{
		while (data->args[i])
		{
			ft_putstr_fd(data->args[i++], STDOUT_FILENO);
			if (data->args[i])
				write(1, " ", STDOUT_FILENO);
		}
		write(1, "\n", STDOUT_FILENO);
	}
	return (0);
}
*/
