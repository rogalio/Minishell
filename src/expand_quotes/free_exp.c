/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:55:15 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/19 17:38:13 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_quotes.h"

void	print_exp2(t_expansion *exp)
{
	int	i;

	i = 0;
	printf("Var_value_tab:\n");
	printf("Var_value = %p\n", exp->var_value);
	if (exp->var_value)
	{
		if (exp->var_value[i])
		{
			while (exp->var_value[i])
			{
				printf("* var_value[%d] = .%s.\n", i, exp->var_value[i]);
				i++;
			}
		}
	}
	printf("nw_len = .%d.\n", exp->nw_len);
	printf("new_word = .%s.\n\n", exp->new_word);
}

void	print_exp(t_expansion *exp)
{
	int	i;

	i = 0;
	printf("quotes = .%d.\n", exp->quotes);
	printf("s_quotes = .%d.\n", exp->s_quotes);
	printf("expand = .%d.\n", exp->nb_expand);
	printf("Var_name_tab:\n");
	printf("Var_name = %p\n", exp->var_name);
	if (exp->var_name)
	{
		if (exp->var_name[i])
		{
			while (exp->var_name[i])
			{
				printf("* var_name[%d] = .%s.\n", i, exp->var_name[i]);
				i++;
			}
			i = 0;
		}
	}
	print_exp2(exp);
}

void	free_exp_tab(char **exp_tab)
{
	char	*tmp;

	tmp = NULL;
	while (*exp_tab)
	{
		tmp = *exp_tab;
		exp_tab++;
		free(tmp);
	}
}

void	free_expansion(t_expansion *exp)
{
	if (exp)
	{
		if (exp->var_name)
		{
			free_exp_tab(exp->var_name);
			free(exp->var_name);
		}
		if (exp->var_value)
		{
			free_exp_tab(exp->var_value);
			free(exp->var_value);
		}
		free(exp);
	}
}
