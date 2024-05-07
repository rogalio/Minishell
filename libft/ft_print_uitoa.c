/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uitoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:23:50 by cabdli            #+#    #+#             */
/*   Updated: 2023/07/20 11:53:15 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_uintlen(unsigned long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len = 1;
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static char	*ft_uitoa(unsigned int nb)
{
	char			*ptr;
	unsigned long	l_nb;
	int				i;

	l_nb = nb;
	i = ft_uintlen(l_nb);
	ptr = ft_calloc(i + 1, sizeof (char));
	if (!ptr)
		return (NULL);
	if (l_nb == 0)
		ptr[--i] = '0';
	while (l_nb > 0)
	{
		ptr[--i] = ((l_nb % 10) + 48);
		l_nb /= 10;
	}
	return (ptr);
}

int	ft_print_uitoa(unsigned int nb)
{
	char	*str;
	int		len;

	len = 0;
	str = ft_uitoa(nb);
	if (!str)
		return (0);
	len = ft_printstr(str);
	free(str);
	return (len);
}
