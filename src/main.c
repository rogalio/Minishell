/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/05 19:07:00 by rogalio          ###   ########.fr       */
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



    t_token_list *token_list = build_token_list("cat -e < infile1 > outfile1 | grep -v a > test >> outfile2 | wc -l > outfile3");
    int verify = init_syntax_analyzer(token_list);
    if (verify == 1)
    {
        t_pipeline *pipeline = parse_rdp(token_list);
        (void)pipeline;
        print_pipeline(pipeline);
    }
    else
    {
        printf("Error\n");
    }
}
