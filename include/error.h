/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:45:16 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/06 18:22:42 by cabdli           ###   ########.fr       */
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
	HDOC_SIGN,
}t_error;

/* error.c */
void	print_err_msg(t_error *error);

#endif