/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:37:23 by rogalio           #+#    #+#             */
/*   Updated: 2024/05/01 16:01:17 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	int				check_equal;
	struct s_env	*next;
}t_env;

typedef struct s_data
{
	t_env			*env;
	char			**args;
}t_data;

#endif