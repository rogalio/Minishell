/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:37:23 by rogalio           #+#    #+#             */
/*   Updated: 2024/03/22 13:01:03 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <libft.h>
# include <stdio.h>
# include <unistd.h>

/* utils.c */
int	skip_whitespace(const char **str);
int	check_regex(const char *s);

#endif