/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 02:55:31 by marvin            #+#    #+#             */
/*   Updated: 2021/12/31 02:55:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_text(int fd, char *text)
{
	char	*buffer;
	int		readed_chars;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	readed_chars = 1;
	while (!ft_strchr(text, '\n') && readed_chars != 0)
	{
		readed_chars = read(fd, buffer, BUFFER_SIZE);
		if (readed_chars == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[readed_chars] = '\0';
		text = ft_strjoin(text, buffer);
	}
	free(buffer);
	return (text);
}

static char	*ft_get_line(char	*text)
{
	int		i;
	char	*line;

	if (!text[0])
		return (NULL);
	i = 0;
	while (text[i] && text[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (text[i])
	{
		line[i] = text[i];
		if (line[i] == '\n')
			break ;
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_get_diff(char *text)
{
	int		i;
	int		j;
	char	*diff;

	i = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (!text[i])
	{
		free(text);
		return (NULL);
	}
	diff = (char *)malloc(sizeof(char) * (ft_strlen(text) - i + 1));
	if (!diff)
		return (NULL);
	i++;
	j = 0;
	while (text[i])
		diff[j++] = text[i++];
	diff[j] = '\0';
	free(text);
	return (diff);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*text[257];

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	text[fd] = ft_read_text(fd, text[fd]);
	if (!text[fd])
		return (NULL);
	line = ft_get_line(text[fd]);
	text[fd] = ft_get_diff(text[fd]);
	return (line);
}
