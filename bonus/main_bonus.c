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

int	main(int ac, char **av)
{
	t_meta_shared	meta;
	sem_t			sem;

	if (ac != 5 && ac != 6)
		return (write(2, "Incorrect number of arguments\n", 30), 1);
	if (check_args(av) == 1)
		return (1);
	init_meta(&meta, av, &sem, "/p_semaphore");
	init_philo(&meta);
	manage_philos_lifecycle(&meta);
	sem_close(&sem);
	sem_unlink("/p_semaphore");
	return (0);
}
