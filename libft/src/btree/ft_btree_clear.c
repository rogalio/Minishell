/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 11:49:33 by asoursou          #+#    #+#             */
/*   Updated: 2020/04/25 17:03:35 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_btree.h"

static void	ft_clear(t_btree *root, t_gfunction del)
{
	if (!root)
		return ;
	ft_clear(root->left, del);
	ft_clear(root->right, del);
	if (del)
		del(root->content);
	free(root);
}

void		*ft_btree_clear(t_btree **root, t_gfunction del)
{
	ft_clear(*root, del);
	return (*root = NULL);
}
