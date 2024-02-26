/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:05:51 by reasuke           #+#    #+#             */
/*   Updated: 2024/02/26 16:01:35 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "utils.h"

int	open_infile(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == FAILURE)
		exit_with_message(__func__, strerror(errno));
	return (fd);
}
