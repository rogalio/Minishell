/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:17:35 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/29 18:46:35 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"

typedef enum
{
    AST_COMMAND,
    AST_REDIRECTION,
    AST_PIPE
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    char *value;
    struct ASTNode *left;  // Utilisé pour les commandes et les arguments
    struct ASTNode *right; // Utilisé pour les pipes
} ASTNode;

// Fonctions auxiliaires (à implémenter)


ASTNode* createASTNode(ASTNodeType type, char *value)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void attachLeft(ASTNode *node, ASTNode *left) {
    node->left = left;
}

void attachRight(ASTNode *node, ASTNode *right) {
    node->right = right;
}

ASTNode* parseCommand(t_list **currentToken) {
    t_token *token = (t_token *)(*currentToken)->content;
    ASTNode *commandNode = createASTNode(AST_COMMAND, token->value);
    *currentToken = (*currentToken)->next;
    while (*currentToken) {
        token = (t_token *)(*currentToken)->content;
        if (token->type == TOKEN_WORD) {
            ASTNode *argumentNode = createASTNode(AST_COMMAND, token->value);
            attachRight(commandNode, argumentNode);
            *currentToken = (*currentToken)->next;
        } else {
            break;
        }
    }
    return commandNode;
}

ASTNode* parseInput(t_list *tokens)
{
    t_list *currentToken = tokens;
    ASTNode *root = parseCommand(&currentToken);
    while (currentToken) {
        t_token *token = (t_token *)currentToken->content;
        if (token->type == TOKEN_PIPE) {
            currentToken = currentToken->next;
            ASTNode *right = parseCommand(&currentToken);
            ASTNode *pipeNode = createASTNode(AST_PIPE, NULL);
            attachLeft(pipeNode, root);
            attachRight(pipeNode, right);
            root = pipeNode;
        } else {
            break;
        }
    }
    return root;
}
