/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabdli <cabdli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:47:51 by cabdli            #+#    #+#             */
/*   Updated: 2023/11/30 17:55:23 by cabdli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* if (!save), faut-il free(buff) avant de return null ?*/

static char	*ft_read_save(int fd, char *save)
{
	char	*buff;
	char	*tmp;
	int		read_bytes;

	read_bytes = 1;
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while ((!ft_strchr(save, '\n')) && (read_bytes != 0))
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (free(save), NULL);
		}
		buff[read_bytes] = '\0';
		tmp = save;
		save = ft_strjoin(save, buff);
		free(tmp);
		if (!save)
			return (free(buff), NULL);
	}
	free(buff);
	return (save);
}

static char	*ft_get_line(char *save)
{
	int		i;
	char	*str;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	str = malloc((i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		str[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

static char	*ft_save(char *save)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i] || !save[i + 1])
	{
		free(save);
		return (NULL);
	}
	str = malloc((ft_strlen(save) - i) * sizeof(char));
	if (!str)
		return (free(save), NULL);
	while (save[++i])
		str[j++] = save[i];
	str[j] = '\0';
	free(save);
	return (str);
}

static int	check_lines(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'C' \
			&& line[i] != 'E' && line[i] != 'P' && line[i] != '\n' \
			&& line[i] != '2')
			return (ft_printf("Error, the map contains a wrong char !\n"), 0);
		i++;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;
	char		*wrong;

	wrong = "wrong_char";
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX - 1)
		return (NULL);
	save = ft_read_save(fd, save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	if (!line)
		return (free(save), NULL);
	save = ft_save(save);
	if (!check_lines(line))
	{
		free(save);
		free(line);
		return (wrong);
	}
	return (line);
}
