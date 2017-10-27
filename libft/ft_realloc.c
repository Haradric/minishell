/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 14:50:26 by mbraslav          #+#    #+#             */
/*   Updated: 2017/05/01 14:50:36 by mbraslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	unsigned char	*new;
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)ptr;
	new = (unsigned char *)malloc(size);
	i = 0;
	while (i < size)
	{
		*(new + i) = *(p + i);
		i++;
	}
	free(ptr);
	return (p);
}
