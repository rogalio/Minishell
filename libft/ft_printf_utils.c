/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:35:42 by cabdli            #+#    #+#             */
/*   Updated: 2023/07/20 11:53:25 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr(char *str)
{
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	ft_putstr_fd(str, 1);
	return ((int)ft_strlen(str));
}

int	ft_print_itoa(int nb)
{
	char	*str;
	int		len;

	len = 0;
	str = ft_itoa(nb);
	if (!str)
		return (0);
	len = ft_printstr(str);
	free(str);
	return (len);
}
