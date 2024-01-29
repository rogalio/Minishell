/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:20:24 by rogalio           #+#    #+#             */
/*   Updated: 2024/01/29 17:30:37 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum
{
    AST_COMMAND,
    AST_REDIRECTION,
    AST_PIPE
} ASTNodeType;

typedef struct ASTNode
{
    ASTNodeType type;
    char *value;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

ASTNode* parseInput(t_list *tokens);



#endif
