/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:43 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/22 16:49:49 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int echo(t_data *data)
{
    int i;

    i = 1;
    while (data->args[i])
    {
        ft_putstr_fd(data->args[i], STDOUT_FILENO);
        if (data->args[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    ft_putchar_fd('\n', STDOUT_FILENO);
    return (0);
}
