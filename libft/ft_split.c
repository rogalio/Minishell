/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:00:59 by cabdli            #+#    #+#             */
/*   Updated: 2023/09/14 16:44:28 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countwords(char const *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			word++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (word);
}

static char	*string(char const *str, char c)
{
	char	*arr;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[len] != c && str[len])
		len++;
	arr = ft_calloc(len + 1, sizeof (char));
	if (!arr)
		return (NULL);
	while (i < len)
	{
		arr[i] = str[i];
		i++;
	}
	return (arr);
}

static void	split_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
}

char	**ft_split(char const *str, char c)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	tab = ft_calloc((countwords(str, c)) + 1, sizeof (char *));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		if (str[i] != c)
		{
			tab[j] = string(&str[i], c);
			if (!tab[j++])
				split_free(tab);
			while (str[i] != c && str[i])
				i++;
		}
		else
			i++;
	}
	return (tab);
}

/*#include <stdio.h>
int	main()
{
	char	**tab;
	int		i;
	char const	str[] = "Hello**World**!**ca***fonctionne   ****!!!**";
	
	tab = ft_split(str, '*');
	if (!tab)
		return (1); //return (NULL);
	i = 0;
	while (tab[i])
		printf("%s\n", tab[i++]);
	return (0);
}*/