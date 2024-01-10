/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouchel <rmouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:00:42 by rmouchel          #+#    #+#             */
/*   Updated: 2023/05/09 19:35:44 by rmouchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char c)
{
    int i;
    int num_words;

    i = 0;
    num_words = 0;
    while (str[i])
    {
        if (str[i] != c)
        {
            num_words++;
            while (str[i] && str[i] != c)
                i++;
        }
        else
            i++;
    }
    return (num_words);
}

char **ft_split(char const *s, char c)
{
    char **arr;
    int i;
    int j;
    int k;

    arr = (char **)malloc(sizeof(char *) * (count_words((char *)s, c) + 1));
    if (!arr)
        return (NULL);
    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] != c)
        {
            k = 0;
            while (s[i + k] && s[i + k] != c)
                k++;
            arr[j] = (char *)malloc(sizeof(char) * (k + 1));
            if (!arr[j])
                return (NULL);
            k = 0;
            while (s[i] && s[i] != c)
                arr[j][k++] = s[i++];
            arr[j][k] = '\0';
            j++;
        }
        else
            i++;
    }
    arr[j] = NULL;
    return (arr);
}
/**
 * @file
 * @brief      Sépare une chaîne de caractères en fonction d'un caractère délimiteur et retourne un tableau de chaînes de caractères.
 *
 * @param[in]  s     La chaîne de caractères source.
 * @param[in]  c     Le caractère délimiteur pour séparer la chaîne de caractères.
 *
 * @return     Un tableau de chaînes de caractères séparées par le caractère délimiteur, ou NULL en cas d'échec de l'allocation de mémoire.
 *
 * @details    La fonction ft_split réalise les étapes suivantes :
 *             1. Si la chaîne source est NULL, retourne NULL.
 *             2. Alloue de la mémoire pour un tableau de pointeurs de chaînes de caractères, en utilisant le nombre de mots dans la chaîne source et ajoute un élément supplémentaire pour un pointeur NULL.
 *             3. Si l'allocation de mémoire échoue, retourne NULL.
 *             4. Parcourt la chaîne source, en sautant les occurrences du caractère délimiteur.
 *             5. Pour chaque mot trouvé, appelle la fonction ft_substr pour extraire le mot et l'ajouter au tableau.
 *             6. Ajoute un pointeur NULL à la fin du tableau pour marquer la fin du tableau.
 *             7. Retourne le tableau de chaînes de caractères.
 */

