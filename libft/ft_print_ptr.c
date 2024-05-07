/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:07:16 by cabdli            #+#    #+#             */
/*   Updated: 2023/07/20 11:52:54 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ptrlen(uintptr_t nb)
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

static void	ft_putptr(uintptr_t nb)
{
	if (nb > 15)
	{
		ft_putptr(nb / 16);
		ft_putptr(nb % 16);
	}
	else
	{
		if (nb < 10)
			ft_putchar_fd(nb + 48, 1);
		else
			ft_putchar_fd((nb - 10 + 'a'), 1);
	}
	return ;
}

int	ft_print_ptr(uintptr_t ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
	{
		len += write(1, "(nil)", 5);
		return (len);
	}
	else
	{
		len = write(1, "0x", 2);
		ft_putptr(ptr);
		len += ft_ptrlen(ptr);
	}
	return (len);
}
