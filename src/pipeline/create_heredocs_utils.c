/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredocs_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:38:40 by cabdli            #+#    #+#             */
/*   Updated: 2024/04/18 12:09:55 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

char	*generate_random_name(void)
{
	int		i;
	int		fd;
	char	c;
	char	*name;

	i = 1;
	fd = 0;
	c = '\0';
	name = ft_calloc(8, sizeof(char));
	if (!name)
		return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (free(name), NULL);
	while (i < 7)
	{
		if (read(fd, &c, 1) == -1)
			return (free(name), close(fd), NULL);
		if (ft_isalnum(c))
			name[i++] = c;
	}
	name[0] = '.';
	return (close(fd), name);
}
