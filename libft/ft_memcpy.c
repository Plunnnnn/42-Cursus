/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:13:31 by bdenfir           #+#    #+#             */
/*   Updated: 2024/11/15 15:37:55 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned long int	i;
	char				*strd;
	char				*srcd;

	if (!dest && !src)
		return (NULL);
	strd = (char *)dest;
	srcd = (char *)src;
	i = -1;
	while (++i < n)
		strd[i] = srcd[i];
	return (dest);
}
