/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:54:35 by mbraslav          #+#    #+#             */
/*   Updated: 2017/04/26 15:55:02 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(const char *error_msg, const char *str)
{
	write(2, error_msg, ft_strlen(error_msg));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	free_str_array(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int		is_dir(const char *path)
{
	struct stat	filestat;

	if (lstat(path, &filestat) == -1)
		return (-1);
	if ((filestat.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	else
		return (0);
}

size_t	arg_count(const char *str, char *delims)
{
	char	*s;
	int		count;

	s = (char *)str;
	while (ft_isspace(*s))
		s++;
	count = (ft_strlen(s)) ? 1 : 0;
	while (*s)
	{
		if (*s == '"' || *s == '\'')
			s = ft_strchr(s + 1, *s);
		if (*s && ft_strchr(delims, *s))
		{
			s++;
			while (ft_isspace(*s))
				s++;
			if (*s)
				count++;
			continue ;
		}
		s++;
	}
	return (count);
}

size_t	arg_len(const char *str, char *delims)
{
	char	*s;

	s = (char *)str;
	while (*s && !ft_strchr(delims, *s))
	{
		if (*s == '"' || *s == '\'')
			s = ft_strchr(s + 1, *s);
		s++;
	}
	return (s - str);
}
