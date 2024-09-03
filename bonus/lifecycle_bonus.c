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

void	*dispatch_lifecycle(t_phi *phi)
{
	while (!is_dead(phi, FLAG_QUERY))
	{
		if (phi->meta_s->sem_fork >= 2)
		{
			sem_wait(&phi->meta_s->sem_fork);
			sem_wait(&phi->meta_s->sem_fork);
			eat(phi);
			sem_post(&phi->meta_s->sem_fork);
			sem_post(&phi->meta_s->sem_fork);
		}
		else
		{
			
		}
		if (phi->n_eaten == phi->meta_s->n_eats)
		{
			sem_wait(&phi->meta_s->sem_stop);
			if (++phi->meta_s->n_p_eat_fl == phi->meta_s->n_phi)
			{
				sem_post(&phi->meta_s->sem_stop);
				is_dead(phi, FLAG_STOP);
			}
			sem_post(&phi->meta_s->sem_stop);
		}
	}
	return (NULL);
}

int	manage_philos_lifecycle(t_meta *meta)
{
	int		i;

	i = 0;
	meta->t_start = get_timestamp();
	while (i < meta->n_phi)
	{
		meta->phi[i].pid = fork();
		if (meta->phi[i].pid == -1)
		{
			perror("Error");
			return (-1);
		}
		if (meta->phi[i].pid == 0)
			dispatch_lifecycle(&meta->phi[i]);
		else
			check_death(&meta->phi[i]);
		i++;
	}
	i = 0;
	while (i < meta->n_phi)
	{
		waitpid(meta->phi[i].pid, NULL, 0);
		i++;
	}
	return (0);
}

