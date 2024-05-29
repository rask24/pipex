/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:02:39 by reasuke           #+#    #+#             */
/*   Updated: 2024/05/29 20:06:19 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	append_str(char **dst, const char *src)
{
	ft_strlcat(*dst, src, ft_strlen(*dst) + ft_strlen(src) + 1);
}
