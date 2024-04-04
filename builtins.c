/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:31:16 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/04 13:48:22 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include <limits.h>

void	built_echo(char **args)
{
	int	i;

	i = 1;
	if (!ft_strcmp(args[i], "-n"))
	{
		i++;
		while (args[i])
		{
			ft_putstr_fd(args[i++], 1);
			if (args[i])
				write(1, ' ', 1);
		}
	}
	else
	{
		while (args[i])
		{
			ft_putstr_fd(args[i++], 1);
			if (args[i])
				write(1, ' ', 1);
		}
		write(1, '\n', 1);
	}
}

void	built_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", STDOUT_FILENO);
	}
	else
	{
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}
}

void	update_pwd_env(char **envp)
{
	
}

void	go_user_directory(void)
{
	char	*home_directory;

	home_directory = getenv("HOME");
	if (!home_directory)
	{
		write(stderr, "getenv() error\n", 16);
		exit(EXIT_FAILURE);
	}
	if (chdir(home_directory) == -1)
	{
		perror("chdir");
		exit(EXIT_FAILURE);
	}
	update_pwd_env(envp);
}

/*
- Changer le cwd dans env ?

- OK : si cd est suivi d'args non valides, retourner un msg d'erreur
du type -> bash: cd: src/pwd: No such file or directory

- OK : si il y a plus d'un argument a la suite de cd -> bash: cd: too many arguments

- si cd est seul, donc aucun argument, changer le repertoire courant vers le
repertoire de l'utilisateur

 - les ".." pour revenir en arrire sont-ils geres ?
*/
void	built_cd(t_command *cmd, char **envp)
{
	char	*home_directory;

	if (cmd->args_count > 2)
		write(STDOUT_FILENO, "cd: too many arguments", 22);
	if (cmd->args_count == 1)
		go_user_directory();
	else
	{
		if (chdir(cmd->args[1]) == -1)
		{
			perror("cd:");
			exit(EXIT_FAILURE);
		}
		update_pwd_env(envp);
	}
}
