/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:52:57 by rogalio           #+#    #+#             */
/*   Updated: 2024/04/05 15:01:20 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

static t_pipeline	*init_pipeline(void)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	return (pipeline);
}

t_pipeline	*create_pipeline(t_token_list *token_list, t_env *env)
{
	t_pipeline	*pipeline;

	pipeline = init_pipeline();
	if (!pipeline)
		return (NULL);
	if (!create_commands(pipeline, token_list))
		return (free_pipeline(pipeline), NULL);
	if (!create_cmds_args(pipeline, token_list))
		return (free_pipeline(pipeline), NULL);
	if (!fill_pipeline(token_list, pipeline, env))
		return (free_pipeline(pipeline), NULL);
	return (pipeline);
}
