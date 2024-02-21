/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/21 19:05:52 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	display_welcome_message();
	run_shell(envp);
	return (0);
}
