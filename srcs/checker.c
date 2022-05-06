/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:36:15 by jrasser           #+#    #+#             */
/*   Updated: 2022/05/03 20:36:36 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
	{
		printf("Mauvais nombre d'argument\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		printf("argv[%d] : %s\n", i, argv[i]);
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("argument \"%s\" non valide\n", argv[i]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}