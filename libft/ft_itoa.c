/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:11:25 by cabdli            #+#    #+#             */
/*   Updated: 2023/05/11 10:11:33 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len = 1;
	if (nb < 0)
	{
		nb *= (-1);
		len = 1;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char	*ptr;
	long	l_nb;
	int		i;

	l_nb = nb;
	i = ft_intlen(l_nb);
	ptr = ft_calloc(i + 1, sizeof (char));
	if (!ptr)
		return (NULL);
	if (l_nb == 0)
		ptr[--i] = '0';
	if (l_nb < 0)
	{
		ptr[0] = '-';
		l_nb *= (-1);
	}
	i--;
	while (l_nb > 0)
	{
		ptr[i] = ((l_nb % 10) + 48);
		l_nb /= 10;
		i--;
	}
	return (ptr);
}

/*#include <stdio.h>

int	main()
{
	printf("%s", ft_itoa(2147483647));
	free(ft_itoa(2147483647));
	return (0);
}*/
