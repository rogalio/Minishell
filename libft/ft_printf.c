/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:45:44 by cabdli            #+#    #+#             */
/*   Updated: 2023/07/20 11:57:22 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_conversion(va_list arg, const char type)
{
	int	len;

	len = 0;
	if (type == 'c')
		len += ft_putchar(va_arg(arg, int));
	else if (type == 's')
		len += ft_printstr(va_arg(arg, char *));
	else if (type == 'p')
		len += ft_print_ptr(va_arg(arg, uintptr_t));
	else if (type == 'd' || type == 'i')
		len += ft_print_itoa(va_arg(arg, int));
	else if (type == 'u')
		len += ft_print_uitoa(va_arg(arg, unsigned int));
	else if (type == 'x' || type == 'X')
		len += ft_print_hex(va_arg(arg, unsigned int), type);
	else if (type == '%')
		len += ft_putchar(type);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	params;

	i = 0;
	len = 0;
	if (str == NULL)
		return (-1);
	else
	{
		va_start(params, str);
		while (str[i])
		{
			if (str[i] == '%')
			{
				len += ft_conversion(params, str[i + 1]);
				i++;
			}
			else
				len += ft_putchar(str[i]);
			i++;
		}
		va_end(params);
	}
	return (len);
}
