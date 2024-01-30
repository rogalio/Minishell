/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:17:35 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/30 18:02:44 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"
// import fot printf
#include <stdio.h>

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


/*
ASTNode* parseCommand(t_list **currentToken) {
    ASTNode *commandNode = createASTNode(AST_COMMAND, ((t_token *)(*currentToken)->content)->value);
    *currentToken = (*currentToken)->next;
    while (*currentToken && ((t_token *)(*currentToken)->content)->type == TOKEN_WORD) {
        ASTNode *argNode = createASTNode(AST_COMMAND, ((t_token *)(*currentToken)->content)->value);
        attachLeft(argNode, commandNode->right);
        attachRight(argNode, NULL);
        attachLeft(commandNode, argNode);
        *currentToken = (*currentToken)->next;
    }
    return commandNode;
}

ASTNode* parseInput(t_list *tokens) {
// prend en compte pipe en top priorite puis redirection puis word . mettre une commande par noeux
    t_list *currentToken = tokens;
    ASTNode *root = NULL;
    ASTNode *currentNode = NULL;
    while (currentToken) {
        if (((t_token *)currentToken->content)->type == TOKEN_PIPE) {
            ASTNode *pipeNode = createASTNode(AST_PIPE, NULL);
            attachLeft(pipeNode, currentNode);
            attachRight(pipeNode, NULL);
            currentNode = pipeNode;
            if (root == NULL) {
                root = pipeNode;
            }
        } else if (((t_token *)currentToken->content)->type == TOKEN_REDIRECT) {
            ASTNode *redirectionNode = createASTNode(AST_REDIRECTION, ((t_token *)currentToken->content)->value);
            attachLeft(redirectionNode, currentNode);
            attachRight(redirectionNode, NULL);
            currentNode = redirectionNode;
            if (root == NULL) {
                root = redirectionNode;
            }
        } else if (((t_token *)currentToken->content)->type == TOKEN_WORD) {
            ASTNode *commandNode = parseCommand(&currentToken);
            attachLeft(commandNode, currentNode);
            attachRight(commandNode, NULL);
            currentNode = commandNode;
            if (root == NULL) {
                root = commandNode;
            }
        }
        currentToken = currentToken->next;
    }
    return root;
}

*/



