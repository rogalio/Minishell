/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/06 13:31:44 by rogalio          ###   ########.fr       */
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


    token_list = init_token_list("cat -e < infile1 > outfile1 | grep -v a > test >> outfile2 | wc -l > outfile3");
    verify = init_syntax_analyzer(token_list);
    if (verify)
    {
        pipeline = parse_rdp(token_list);
        print_pipeline(pipeline);
        free_pipeline(pipeline);
    }
    free_token_list(token_list);
    return 0;

}
