/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/12 13:23:09 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	if (argc != 1)
		return (write(2, "Error: too many arguments\n", 26), 1);
	//display_welcome_message();
	run_shell(envp);
	return (0);
}
