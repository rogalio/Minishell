/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:17:35 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/30 13:16:59 by rogalio          ###   ########.fr       */
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

ASTNode* createASTNode(ASTNodeType type, char *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void attachLeft(ASTNode *parent, ASTNode *child) {
    parent->left = child;
}

void attachRight(ASTNode *parent, ASTNode *child) {
    parent->right = child;
}





ASTNode* parseCommand(t_list **currentToken) {
    t_token *token = (t_token *)(*currentToken)->content;
    ASTNode *commandNode = createASTNode(AST_COMMAND, ft_strdup(token->value));
    ASTNode *lastNode = NULL;

    *currentToken = (*currentToken)->next;
    while (*currentToken && ((t_token *)(*currentToken)->content)->type == TOKEN_WORD) {
        token = (t_token *)(*currentToken)->content;
        ASTNode *argNode = createASTNode(AST_COMMAND, ft_strdup(token->value));
        if (!lastNode) {
            commandNode->right = argNode; // Attache le premier argument à la commande
        } else {
            lastNode->right = argNode; // Attache les arguments suivants au précédent
        }
        lastNode = argNode; // Mise à jour du dernier nœud
        *currentToken = (*currentToken)->next;
    }

    return commandNode;
}

ASTNode* parseInput(t_list *tokens) {
    t_list *currentToken = tokens;
    ASTNode *root = NULL;
    ASTNode *lastNode = NULL;

    while (currentToken) {
        t_token *token = (t_token *)currentToken->content;

        if (token->type == TOKEN_PIPE) {
            ASTNode *pipeNode = createASTNode(AST_PIPE, NULL);
            if (root == NULL) {
                root = pipeNode;
            } else {
                attachLeft(pipeNode, root);
                root = pipeNode;
            }
            lastNode = pipeNode;
            currentToken = currentToken->next;
        } else if (token->type == TOKEN_REDIRECT) {
            ASTNode *redirectionNode = createASTNode(AST_REDIRECTION, ft_strdup(token->value));
            attachLeft(redirectionNode, lastNode);
            lastNode = redirectionNode;
            currentToken = currentToken->next;
        } else if (token->type == TOKEN_WORD) {
            ASTNode *commandNode = parseCommand(&currentToken);
            if (lastNode) {
                attachRight(lastNode, commandNode);
            } else {
                root = commandNode;
            }
            lastNode = commandNode;
        }
    }

    return root;
}

