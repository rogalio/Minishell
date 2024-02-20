/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rogalio <rmouchel@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:43 by rogalio           #+#    #+#             */
/*   Updated: 2024/02/20 13:57:25 by rogalio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


int echo(t_data *data)
{
    int i;

    i = 1;
    while (data->args[i])
    {
        printf("%s", data->args[i]);
        if (data->args[i + 1])
            printf(" ");
        i++;
    }
    printf("\n");
    return 0;
}

