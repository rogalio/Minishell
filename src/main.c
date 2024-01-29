/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/29 18:54:06 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "parser.h"
#include "ast.h"


// probleme a traiter :
// - les sigle quotes dans tokenize


void printAST(ASTNode *node, int level) {
    if (node == NULL) {
        return;
    }

    // Création de l'indentation
    for (int i = 0; i < level; i++) {
        printf("    ");
    }

    // Affichage du type de nœud et de sa valeur
    switch (node->type) {
        case AST_COMMAND:
            printf("[COMMAND] %s\n", node->value ? node->value : "null");
            break;
        case AST_REDIRECTION:
            printf("[REDIRECT] %s\n", node->value ? node->value : "null");
            break;
        case AST_PIPE:
            printf("[PIPE]\n");
            break;
    }

    // Appels récursifs pour les enfants gauche et droit
    printAST(node->left, level + 1);
    printAST(node->right, level + 1);
}


int		main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;


    /*
        int verify = validate_tokens(tokenize2(" cat -e 'hello world' "));
    if (verify == 1)
        printf("valid\n");
    else
        printf("invalid\n");

    */

   t_list *test = tokenize2("cat -e hello world | test | test2 ");

   ASTNode *root = parseInput(test);
   (void)root;

   printAST(root, 0);



    return (0);
}
