/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:36:27 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/12 14:02:37 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

// void display_welcome_message(void)
// {
//   printf("\033[2J");
//   printf("\n");
//   printf("\e[0;35m"
//        "███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗ ███████╗ ██╗      ██╗     \n"
//        "████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║ ██╔════╝ ██║      ██║     \n"
//        "██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║ █████╗   ██║      ██║     \n"
//        "██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║ ██╔══╝   ██║      ██║     \n"
//        "██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║ ███████╗ ███████╗ ███████╗\n"
//        "╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝\n"
//        "\033[0m"
//        "\033[1;34m"
//        "                      by rmouchel and cabdli\n"
//        "\033[0m");
//   printf("\n");

// }

static char *get_user(void)
{
    char *user = getenv("USER");
    if (!user)
        user = "user";
    return ft_strjoin("\033[1;32m", user);
}

static char *get_cwd_display(void)
{
    char cwd[1024];
    char *home = getenv("HOME");
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return ft_strdup("\033[1;34mminishell");
    if (home && strncmp(cwd, home, strlen(home)) == 0)
        return ft_strjoin("\033[1;34m~", cwd + strlen(home));
    else
        return ft_strjoin("\033[1;34m", cwd);
}

static char *create_prompt(char *user_colored, char *cwd_display)
{
    char *at_minishell = ft_strjoin(user_colored, "@minishell:");
    char *prompt = ft_strjoin(at_minishell, cwd_display);
    free(at_minishell);
    return ft_strjoin(prompt, "> \033[0m"); // Réinitialise la couleur à la fin.
}

char *display_prompt(void)
{
    char *user_colored = get_user();
    char *cwd_display = get_cwd_display();
    char *prompt = create_prompt(user_colored, cwd_display);

    free(user_colored);
    free(cwd_display);

    return prompt;
}