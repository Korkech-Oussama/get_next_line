/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okorkech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 13:14:29 by okorkech          #+#    #+#             */
/*   Updated: 2025/12/19 13:14:32 by okorkech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

char	*get_next_line(int fd);
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif
