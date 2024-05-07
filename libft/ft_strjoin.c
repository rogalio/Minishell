/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:20:21 by cabdli            #+#    #+#             */
/*   Updated: 2023/10/09 21:34:56 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2));
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[len] = '\0';
	return (str);
}

/*#include <stdio.h>
int	main()
{
	char const	str1[] = "Hello";
	char const	str2[] = " World !";
	//char const	*str3 = NULL;
	
	//if ((ft_strjoin(str1, str3)) == NULL)
		//printf("ptr = NULL");
	printf("%s\n", ft_strjoin(str1, str2));
	free (ft_strjoin(str1, str2));
	return (0);
}*/