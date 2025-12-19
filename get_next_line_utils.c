/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okorkech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 13:13:50 by okorkech          #+#    #+#             */
/*   Updated: 2025/12/19 13:13:53 by okorkech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	get_len(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

char	*get_strdup(const char *s)
{
	char	*str_dup;
	size_t	s_len;
	int		i;

	s_len = get_len(s) + 1;
	str_dup = malloc(sizeof(char) * s_len);
	if (!str_dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str_dup[i] = s[i];
		i++;
	}
	str_dup[i] = '\0';
	return (str_dup);
}

int	get_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

char	*get_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = get_len(s);
	if (start >= s_len)
		return (get_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	sub_str = malloc(len + 1);
	if (!sub_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}

char	*get_strjoin(char const *s1, char const *s2)
{
	char	*str_joined;
	size_t	len_str_joined;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	len_str_joined = get_len(s1) + get_len(s2);
	str_joined = malloc(sizeof(char) * (len_str_joined + 1));
	if (!str_joined)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str_joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str_joined[i + j] = s2[j];
		j++;
	}
	str_joined[i + j] = '\0';
	return (str_joined);
}
