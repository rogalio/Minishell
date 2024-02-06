/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/06 19:24:59 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "parser.h"
#include "rdp.h"


int		main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;

    t_token_list *token_list;
    t_pipeline *pipeline;
    int verify;


    token_list = init_token_list("echo ""Your username is $USER amd directory is $HOME/document"" ");
    verify = init_syntax_analyzer(token_list);
    if (verify)
    {
        pipeline = parse_rdp(token_list, envp);
        print_pipeline(pipeline);

    }
    return 0;

}
