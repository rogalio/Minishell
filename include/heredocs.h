/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:16:20 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/22 17:29:03 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOCS_H
# define HEREDOCS_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell.h"


int	handle_heredocs(t_pipeline *pipeline, t_minishell *minishell);

#endif