/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:50:53 by linyao            #+#    #+#             */
/*   Updated: 2024/09/03 17:03:17 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	manage_philos_lifecycle(t_meta_shared *meta, sem_t *sem)
{
	int		i;
	pid_t	pid[MAX_P];

	i = 0;
	while (i < meta->n_philos)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			sem_wait(sem);
			sleep(2);
			sem_post(sem);
		}
		i++;
	}
	i = 0;
	while (i < meta->n_philos)
	{
		wait(NULL);
		i++;
	}
}

