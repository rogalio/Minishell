/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/25 20:14:24 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "parser.h"


// probleme a traiter :
// - les sigle quotes dans tokenize

int		main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;


    int verify = validate_tokens(tokenize2(" cat  | > file"));
    if (verify == 1)
        printf("valid\n");
    else
        printf("invalid\n");
    return (0);
}
