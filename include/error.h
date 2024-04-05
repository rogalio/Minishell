/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:45:16 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/05 13:01:53 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <unistd.h>
# include "libft.h"

typedef enum s_error
{
	MALLOC,
	QUOTES,
	SYNTAX,
}t_error;

void	print_err_msg(t_error *error);

#endif