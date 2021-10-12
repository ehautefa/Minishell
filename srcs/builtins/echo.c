/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:21:45 by hlucie            #+#    #+#             */
/*   Updated: 2021/10/12 19:32:46 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **to_print)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (to_print[i])
	{
		while (to_print[i][j])
		{
			printf("%c", to_print[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
	printf("\n");
}