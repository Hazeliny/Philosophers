/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:13:44 by linyao            #+#    #+#             */
/*   Updated: 2024/09/05 12:43:52 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphore(t_meta *meta)
{
	sem_unlink("/sem_fork");
	sem_unlink("/sem_stop");
	sem_unlink("/sem_eat");
	sem_unlink("/sem_display");
	sem_unlink("/sem_dead");
	meta->sem_fork = sem_open("/sem_fork", O_CREAT, 0666, meta->n_phi);
	if (meta->sem_fork == SEM_FAILED)
		handle_error("sem_fork");
	meta->sem_stop = sem_open("/sem_stop", O_CREAT, 0666, 1);
	if (meta->sem_stop == SEM_FAILED)
		handle_error("sem_stop");
	meta->sem_eat = sem_open("/sem_eat", O_CREAT, 0666, 1);
	if (meta->sem_eat == SEM_FAILED)
		handle_error("sem_eat");
	meta->sem_display = sem_open("/sem_display", O_CREAT, 0666, 1);
	if (meta->sem_display == SEM_FAILED)
		handle_error("sem_display");
	meta->sem_dead = sem_open("/sem_dead", O_CREAT, 0666, 1);
	if (meta->sem_dead == SEM_FAILED)
		handle_error("sem_dead");
}

void	init_semaphore1(t_meta *meta)
{
	sem_unlink("/sem_disposable");
	meta->sem_disposable = sem_open("/sem_disposable", O_CREAT, 0600, 1);
	if (meta->sem_disposable == SEM_FAILED)
		handle_error("sem_disposable");
}

void	init_meta(t_meta *meta, char **av)
{
	meta->n_phi = ft_atoi1(av[1]);
	meta->t_die = ft_atoi1(av[2]);
	meta->t_eat = ft_atoi1(av[3]);
	meta->t_sleep = ft_atoi1(av[4]);
	if (av[5])
		meta->n_eats = ft_atoi1(av[5]);
	else
		meta->n_eats = -1;
	meta->n_p_eat_fl = 0;
	meta->stop = false;
	init_semaphore(meta);
	init_semaphore1(meta);
}

void	init_philo(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->n_phi)
	{
		meta->phi[i].id = i + 1;
		meta->phi[i].n_eaten = 0;
		meta->phi[i].t_lastmeal = 0;
		meta->phi[i].meta_s = meta;
		i++;
	}
}
