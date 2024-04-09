/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:36:27 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/08 19:45:32 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static char	*get_user(void)
{
	char	*user;

	user = getenv("USER");
	if (!user)
		user = "user";
	return (ft_strjoin("\033[1;32m", user));
}

static char	*get_cwd_display(void)
{
	char	cwd[1024];
	char	*home;

	home = getenv("HOME");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_strdup("\033[1;34mminishell"));
	if (home && strncmp(cwd, home, strlen(home)) == 0)
		return (ft_strjoin("\033[1;34m~", cwd + strlen(home)));
	else
		return (ft_strjoin("\033[1;34m", cwd));
}

static char *create_prompt(char *user_colored, char *cwd_display)
{
    char *at_minishell;
    char *prompt_part;
    char *prompt;

		at_minishell = ft_strjoin(user_colored, "@minishell:");
		prompt_part = ft_strjoin(at_minishell, cwd_display);
		prompt = ft_strjoin(prompt_part, "> \033[0m");
    free(at_minishell);
    free(prompt_part); // S'assurer de libérer cette partie intermédiaire pour éviter les fuites
    return prompt;
}

char	*display_prompt(void)
{
	char	*user_colored;
	char	*cwd_display;
	char	*prompt;

	user_colored = get_user();
	cwd_display = get_cwd_display();
	prompt = create_prompt(user_colored, cwd_display);
	free(user_colored);
	free(cwd_display);
	return (prompt);
}

char	*display_and_readline(void)
{
	char	*prompt;
	char	*input;

	input = NULL;
	prompt = display_prompt();
	if (!prompt)
		return (NULL);
	input = readline(prompt);
	free(prompt);
	if (!input)
		return (free(input), ft_putstr_fd("exit\n", STDOUT_FILENO), NULL);
	if (*input)
		add_history(input);
	return (input);
}
