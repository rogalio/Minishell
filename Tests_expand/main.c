/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:36:05 by cabdli            #+#    #+#             */
/*   Updated: 2024/03/27 14:09:40 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

void	print_exp(t_expansion *exp)
{
	int	i;

	i = -1;
	printf("quotes = .%d.\n", exp->quotes);
	printf("expand = .%d.\n", exp->expand);
	printf("Var_names_tab:\n");
	printf("Var_name = %p\n", exp->var_name);
	if (exp->var_name)
	{
		while (exp->var_name[++i])
			printf("* var_name[%d] = .%s.\n", i, exp->var_name[i]);
		printf("\n");
		i = -1;
	}
	printf("Var_value_tab:\n");
	printf("Var_value = %p\n", exp->var_value);
	if (exp->var_name)
	{
		while (exp->var_name[++i])
			printf("* var_value[%d] = .%s.\n", i, exp->var_value[i]);
		printf("\n");
	}
	printf("nw_len = .%d.\n", exp->nw_len);
	printf("new_word = .%s.\n", exp->new_word);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	char	*word;

	(void)ac;
	(void)av;
	word = "\"sa\'lut\"";
	env = init_env(envp);
	if (!env)
		return (1);
	handle_expand_quotes(&word, env);
	free_env(env);
	return (0);
}
