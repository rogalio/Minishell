/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:32:20 by cabdli            #+#    #+#             */
/*   Updated: 2023/09/13 17:22:32 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atoi(const char *str)
{
	int			i;
	int			m;
	long int	nb;

	i = 0;
	m = 1;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			m *= (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb *= 10;
		nb += str[i] - 48;
		i++;
	}
	return (m * nb);
}

//#include <stdio.h>
/*int	main(int ac, char *av[])
{
	if (ac == 2)
	{
		printf("ft_atoi = %d : atoi = %d", ft_atoi(av[1]), atoi(av[1]));
		return (0);
	}
}*/
