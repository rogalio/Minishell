/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/25 14:48:01 by rogalio          ###   ########.fr       */
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


    t_token *t = token_new(TOKEN_REDIRECT, ">> ls -l || # cat -e");
    t_list *l = tokenize2(t->value);

    while (l)
    {
        printf(" type is '%d' and value is %s\n", ((t_token *)l->content)->type, ((t_token *)l->content)->value);
        l = l->next;
    }













    return (0);
}
