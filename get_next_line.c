/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okorkech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 13:12:54 by okorkech          #+#    #+#             */
/*   Updated: 2025/12/19 13:12:57 by okorkech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(int fd , char **pre_line)
{
	char	*buffer;
	
}

char	*get_next_line(int fd)
{
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	get_line(fd, &line);
	
}