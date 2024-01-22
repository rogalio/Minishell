/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strforeach.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 00:26:01 by asoursou          #+#    #+#             */
/*   Updated: 2020/08/26 15:48:11 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strforeach(char *s, int (*f)(int))
{
	char *d;

	d = s;
	while (*s)
	{
		*s = f(*s);
		++s;
	}
	return (d);
}
