/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:14:07 by bdenfir           #+#    #+#             */
/*   Updated: 2024/11/15 16:20:13 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_in_charset(char c, char const *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_get_start(char const *s1, char const *set)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && ft_in_charset(s1[i], set))
		i++;
	return (i);
}

int	ft_get_end(char const *s1, char const *set)
{
	unsigned int	i;

	if (ft_strlen(s1) == 0)
		return (0);
	i = ft_strlen(s1) - 1;
	while (i > 0 && ft_in_charset(s1[i], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	unsigned int	i;
	unsigned int	k;
	unsigned int	end;

	if (!s1 || !set)
		return (ft_strdup(s1));
	if (*set == '\0')
		return (ft_strdup(s1));
	i = ft_get_start(s1, set);
	end = ft_get_end(s1, set);
	if (i > end)
		return (ft_strdup(""));
	if (i == end)
		str = (char *)malloc(1);
	else
		str = (char *)malloc(sizeof(char) * (end - i + 1) + 1);
	if (!str)
		return (NULL);
	k = 0;
	while (i <= end)
		str[k++] = s1[i++];
	str[k] = '\0';
	return (str);
}
