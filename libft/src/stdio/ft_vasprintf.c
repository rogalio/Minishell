/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 01:44:27 by asoursou          #+#    #+#             */
/*   Updated: 2020/11/26 12:28:24 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_memory.h"
#include "ft_stdio.h"

int	ft_vasprintf(char **ret, const char *format, va_list ap)
{
	int size;

	size = ft_vsnprintf(NULL, 0, format, ap);
	if (size < 0 || !(*ret = (char*)ft_malloc((size + 1) * sizeof(char))))
		return (-1);
	return (ft_vsprintf(*ret, format, ap));
}
