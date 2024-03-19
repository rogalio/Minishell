/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/19 16:16:45 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "parser.h"
#include "rdp.h"
#include "builtins.h"
#include "exec.h"
#include "prompt.h"
#include "utils.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		return (write(2, "Error: too many arguments\n", 26), 1);
	run_shell(envp);
	return (0);
}
