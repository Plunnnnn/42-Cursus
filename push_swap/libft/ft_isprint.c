/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:13:26 by bdenfir           #+#    #+#             */
/*   Updated: 2024/11/06 14:07:14 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
isprint check if a character is printable or not.
*/

int	ft_isprint(int c)
{
	return (c >= 32 && c < 127);
}