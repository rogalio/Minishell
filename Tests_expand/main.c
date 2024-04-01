/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:36:05 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/01 17:03:40 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rdp.h"

void	print_exp(t_expansion *exp)
{
	int	i;

	i = 0;
	printf("quotes = .%d.\n", exp->quotes);
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

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	char	*word;

	(void)ac;
	(void)av;
	word = strdup("\"sa\'lut $USER check $PWD $PWDe test\"");
	env = init_env(envp);
	if (!env)
		return (1);
	handle_expand_quotes(&word, env);
	printf("strlen word = %ld\n", strlen(word));
	free(word);
	free_env(env);
	return (0);
}
