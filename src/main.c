/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:19 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/29 19:00:09 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "parser.h"
#include "ast.h"


// probleme a traiter :
// - les sigle quotes dans tokenize


void printTree(ASTNode *node, int space) {
    if (node == NULL) {
        return;
    }

    // Augmenter la distance entre les niveaux
    space += 10;

    // Traiter le nœud droit en premier (dessus)
    printTree(node->right, space);

    // Afficher le nœud courant après l'espace
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    if (node->type == AST_PIPE) {
        printf("[PIPE]\n");
    } else if (node->type == AST_REDIRECTION) {
        printf("[REDIRECT] %s\n", node->value ? node->value : "null");
    } else { // AST_COMMAND
        printf("[COMMAND] %s\n", node->value ? node->value : "null");
    }

    // Traiter le nœud gauche (dessous)
    printTree(node->left, space);
}

void printAST(ASTNode *root) {
    printTree(root, 0);
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

   printAST(root);



    return (0);
}
