/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:36:27 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/26 15:28:14 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static char	*get_user_colored(void)
{
	char	*user;

	user = getenv("USER");
	if (!user)
		user = "user";
	return (ft_strjoin("\033[1;32m", user));
}

static char	*get_cwd_colored(void)
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

static char	*create_prompt(char *user_colored, char *cwd_display)
{
	char	*at_minishell;
	char	*prompt_part;
	char	*prompt;

	at_minishell = ft_strjoin(user_colored, "@minishell:");
	if (!at_minishell)
		return (NULL);
	prompt_part = ft_strjoin(at_minishell, cwd_display);
	if (!prompt_part)
		return (free(at_minishell), NULL);
	prompt = ft_strjoin(prompt_part, "> \033[0m");
	free(at_minishell);
	free(prompt_part);
	return (prompt);
}

char	*display_prompt(void)
{
	char	*user_colored;
	char	*cwd_colored;
	char	*prompt;

	user_colored = get_user_colored();
	if (!user_colored)
		return (NULL);
	cwd_colored = get_cwd_colored();
	if (!cwd_colored)
		return (free(user_colored), NULL);
	prompt = create_prompt(user_colored, cwd_colored);
	free(user_colored);
	free(cwd_colored);
	return (prompt);
}

char	*display_and_readline(t_minishell *minishell)
{
	char	*prompt;
	char	*input;

	input = NULL;
	prompt = display_prompt();
	if (!prompt)
		return (minishell->error = MALLOC, print_err_msg(&minishell->error), \
		minishell->exit_status = UNEXPEC_ERR, NULL);
	input = readline(prompt);
	free(prompt);
	if (!input)
		return (free(input), ft_putstr_fd("exit\n", STDOUT_FILENO), NULL);
	if (*input)
		add_history(input);
	return (input);
}
