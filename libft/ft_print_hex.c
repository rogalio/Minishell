/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:49:45 by cabdli            #+#    #+#             */
/*   Updated: 2023/07/20 11:52:41 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hexlen(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len = 1;
	while (nb > 0)
	{
		nb /= 16;
		len++;
	}
	return (len);
}

static void	ft_puthex(unsigned int nb, const char type)
{
	if (nb > 15)
	{
		ft_puthex(nb / 16, type);
		ft_puthex(nb % 16, type);
	}
	else
	{
		if (nb < 10)
			ft_putchar_fd(nb + 48, 1);
		else
		{
			if (type == 'X')
				ft_putchar_fd((nb - 10 + 'A'), 1);
			else
				ft_putchar_fd((nb - 10 + 'a'), 1);
		}
	}
	return ;
}

int	ft_print_hex(unsigned int nb, const char type)
{
	ft_puthex(nb, type);
	return (ft_hexlen(nb));
}
