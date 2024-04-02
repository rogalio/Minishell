/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:36:05 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/02 15:00:46 by cabdli           ###   ########.fr       */
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
		return (free(word), 1);
	handle_expand_quotes(&word, env);
	printf("\nnew_word = %s\n", word);
	printf("strlen word = %ld\n", strlen(word));
	free(word);
	free_env(env);
	return (0);
}

/*
pb pour get_env en cas d'echec de strdup : comment differencier
un echec de strdup et une value non existante ?
create_node :
else
	{
		node->name = strdup(env_entry);
		node->value = NULL;
	}

Gerer echec de malloc et free de la list en cas de soucis :
retourner un int
static void	add_token_to_list(t_token_list **list, t_token *token)
{
	t_token_list		*new_elem;
	static t_token_list	*temp;

	new_elem = new_token_list(token);
	if (!new_elem)
		return ;
*/
