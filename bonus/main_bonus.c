/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:51:35 by linyao            #+#    #+#             */
/*   Updated: 2024/09/03 16:30:41 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	handle_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_meta_shared	meta;

	if (ac != 5 && ac != 6)
		return (write(2, "Incorrect number of arguments\n", 30), 1);
	if (check_args(av) == 1)
		return (1);
	init_meta(&meta, av);
	init_philo(&meta);
	if (manage_philos_lifecycle(&meta) != 0)
		return (1);
	sem_close(&meta->sem_fork);
	sem_close(&meta->sem_stop);
	sem_close(&meta->sem_eat);
	sem_close(&meta->sem_display);
	sem_close(&meta->sem_dead);
	sem_unlink("/sem_fork");
	sem_unlink("/sem_stop");
	sem_unlink("/sem_eat");
	sem_unlink("/sem_display");
	sem_unlink("/sem_dead");
	return (0);
}
