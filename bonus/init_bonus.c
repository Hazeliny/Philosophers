/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:13:44 by linyao            #+#    #+#             */
/*   Updated: 2024/09/03 16:48:18 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_meta(t_meta_shared *meta, char **av, sem_t *sem, char *s)
{
	sem = sem_open(s, O_CREAT, 0644, meta->n_philos);
	if (sem == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
}

void	init_philo(t_meta_shared *meta)
{
	
}
