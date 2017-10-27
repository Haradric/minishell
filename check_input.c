/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 20:18:08 by mbraslav          #+#    #+#             */
/*   Updated: 2017/05/03 20:18:09 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*quote(const char *prompt)
{
	write(1, prompt, ft_strlen(prompt));
	return (read_input());
}

void		check_input(char **input)
{
	char	*new_input;
	char	*next_quote;
	char	*tmp;
	char	*s;

	s = *input;
	while (*s)
	{
		if (*s == '"' || *s == '\'')
		{
			if (!(next_quote = ft_strchr(s + 1, *s)))
			{
				tmp = *input;
				new_input = quote((*s == '"') ? "dquote> " : "quote> ");
				*input = ft_strjoin(tmp, new_input);
				free(tmp);
				free(new_input);
				s = *input;
				continue ;
			}
			else
				s = next_quote;
		}
		s++;
	}
}
