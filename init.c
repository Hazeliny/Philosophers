/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:36:39 by linyao            #+#    #+#             */
/*   Updated: 2024/09/02 16:26:26 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_meta(t_meta_shared *meta, char **av)
{
	meta->stop = false;
	meta->n_p_eat_fl = 0;
	meta->n_philos = ft_atoi(av[1]);
	if (av[5])
		meta->n_eats = ft_atoi(av[5]);
	else
		meta->n_eats = -1;
	meta->time_die = ft_atoi(av[2]);
	meta->time_eat = ft_atoi(av[3]);
	meta->time_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&meta->m_stop, NULL);
	pthread_mutex_init(&meta->m_eat, NULL);
	pthread_mutex_init(&meta->m_display, NULL);
	pthread_mutex_init(&meta->m_dead, NULL);
}

void	init_philo(t_meta_shared *meta)
{
	int	i;

	i = 0;
	while (i < meta->n_philos)
	{
		meta->philo[i].id = i + 1;
		meta->philo[i].n_eaten = 0;
		meta->philo[i].t_lastmeal = 0;
		meta->philo[i].meta_shared = meta;
		pthread_mutex_init(&meta->philo[i].fork_l, NULL);
		meta->philo[i].fork_r = NULL;
		if (i == meta->n_philos - 1)
			meta->philo[i].fork_r = &meta->philo[0].fork_l;
		else
			meta->philo[i].fork_r = &meta->philo[i + 1].fork_l;
		i++;
	}
}
