/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okorkech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:47:07 by okorkech          #+#    #+#             */
/*   Updated: 2025/12/19 21:47:09 by okorkech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*process(char **pre_line)
{
	size_t	i;
	char	*final_line;
	char	*tmp;

	i = 0;
	if (!pre_line || !*pre_line)
		return (NULL);
	if (**pre_line == '\0')
	{
		free (*pre_line);
		*pre_line = NULL;
		return (NULL);
	}
	while ((*pre_line)[i] && (*pre_line)[i] != '\n')
		i++;
	final_line = get_substr(*pre_line, 0, i + 1);
	if (!final_line)
		return (NULL);
	tmp = *pre_line;
	*pre_line = get_substr(tmp, i + 1, get_len(tmp));
	free(tmp);
	if (!*pre_line)
		return (NULL);
	return (final_line);
}

char	*get_line(int fd, char **pre_line)
{
	ssize_t	n;
	char	*buffer;
	char	*tmp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!get_strchr(*pre_line, '\n'))
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
			return (free(buffer), NULL);
		if (n == 0)
			break ;
		buffer[n] = '\0';
		tmp = *pre_line;
		*pre_line = get_strjoin(tmp, buffer);
		free(tmp);
		if (!*pre_line)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (process(pre_line));
}

char	*get_next_line(int fd)
{
	static char	*line[FD_MAX];

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	return (get_line(fd, &line[fd]));
}
