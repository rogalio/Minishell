/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:14:59 by cabdli            #+#    #+#             */
/*   Updated: 2024/05/07 11:49:07 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*new_str;
	size_t	total_length;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_length = s1_len + ft_strlen(s2) + ft_strlen(s3);
	new_str = (char *)malloc(sizeof(char) * (total_length + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_len + 1);
	ft_strlcat(new_str, s2, s1_len + s2_len + 1);
	ft_strlcat(new_str, s3, total_length + 1);
	return (new_str);
}

char	**env_to_char_array(t_env *env)
{
	int		i;
	char	**envp;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	tmp = env;
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->name, "=");
		envp[i] = ft_strjoin(envp[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

// char	**ft_split2(char const *s, char c)
// {
// 	char	**tab;
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = 0;
// 	j = 0;
// 	if (!s)
// 		return (0);
// 	tab = ft_calloc((ft_strlen(s) + 1), sizeof(char *));
// 	if (!tab)
// 		return (0);
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		k = i;
// 		while (s[i] && s[i] != c)
// 			i++;
// 		if (i > k)
// 		{
// 			tab[j] = ft_calloc((i - k + 1), sizeof(char));
// 			if (!tab[j])
// 				return (0);
// 			ft_strlcpy(tab[j], s + k, i - k + 1);
// 			j++;
// 		}
// 	}
// 	tab[j] = 0;
// 	return (tab);
// }
