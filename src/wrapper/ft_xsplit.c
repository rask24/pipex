/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:48:29 by reasuke           #+#    #+#             */
/*   Updated: 2024/03/15 16:35:51 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wrapper.h"

char	**ft_xsplit(const char *s, char c)
{
	char	**ret;

	ret = ft_split(s, c);
	if (!ret)
		exit_with_message(__func__, strerror(errno), FUNCTION_FAIL);
	return (ret);
}
