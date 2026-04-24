/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaloulid <jaloulid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 06:27:27 by yoessedr          #+#    #+#             */
/*   Updated: 2025/08/07 03:31:29 by jaloulid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *prefix, char *filename)
{
	if (prefix)
		ft_putendl_fd(prefix, 2);
	if (filename)
		ft_putendl_fd(filename, 2);
	perror("Error");
	return (1);
}

int	handle_file_error(char *filename, int error_code)
{
	if (error_code == ENOENT)
		return (print_error("minishell", filename));
	else if (error_code == EACCES)
		return (print_error("Permission denied", filename));
	else
		return (print_error("Unknown error", filename));
}
