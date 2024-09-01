/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:09:27 by linyao            #+#    #+#             */
/*   Updated: 2024/09/01 15:09:32 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_death(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pause(philo->meta_shared->time_die + 1);
	pthread_mutex_lock(philo->meta_shared->m_stop);
	pthread_mutex_lock(philo->meta_shared->m_eat);
	if ((get_timestamp() - philo->lastmeal) >= \
		(long)(philo->meta_shared->time_die) && \
		!is_dead(philo, FLAG_QUERY))
	{
		pthread_mutex_unlock(philo->meta_shared->m_stop);
		pthread_mutex_unlock(philo->meta_shared->m_eat);
		put_msg(philo, " died\n");
		is_dead(philo, FLAG_DEATH);
	}
	pthread_mutex_unlock(philo->meta_shared->m_stop);
	pthread_mutex_unlock(philo->meta_shared->m_eat);
	return (NULL);
}

int	get_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	put_msg(philo, " has taken left fork\n");
	if (philo->meta_shared->n_philos == 1)
	{
		pause(philo->meta_shared->time_die * 2);
		pthread_mutex_unlock(philo->fork_l);
		return (0);
	}
	pthread_mutex_lock(philo->fork_r);
	put_msg(philo, " has taken right fork\n");
	return (1);
}
void	eat(t_philo *philo)
{
	put_msg(philo, " is eating\n");
	pthread_mutex_lock(philo->meta_shared->m_eat);
	philo->t_lastmeal = get_timestamp();
	philo->n_eaten++;
	pthread_mutex_unlock(philo->meta_shared->m_eat);
	pause(philo->meta_shared->time_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	put_msg(philo, " is sleeping\n");
	pause(philo->meta_shared->time_sleep);
	put_msg(philo, " is thinking\n");	
}

void	*dispatch_lifecycle(void *p)
{
	t_philo		*philo;
	pthread_t	t_monitor;

	philo = (t_philo *)p;
	if (philo->id % 2 == 1)
		pause(philo->meta_shared->time_eat / 10);
	while (!is_dead(philo, FLAG_QUERY))
	{
		pthread_create(&t_monitor, NULL, check_death, p);
		if(get_fork(philo))
			eat(philo);
		else
			return (pthread_detach(t_monitor), NULL);
		pthread_detach(t_monitor);
		if (philo->n_eaten == philo->meta_shared->n_eats)
		{
			pthread_mutex_lock(philo->meta_shared->m_stop);
			if (++philo->meta_shared->n_philos_eaten_full == \
					philo->meta_shared_n_philos)
			{
				pthread_mutex_unclok(philo->meta_shared->m_stop);
				is_dead(philo, FLAG_STOP);
			}
			pthread_mutex_unclok(philo->meta_shared->m_stop);
			return (NULL);
		}
	}
	return (NULL);
}

int	manage_philos_lifecycle(t_meta_shared *meta)
{
	int	i;

	i = 0;
	meta->time_start = get_timestamp();
	while (i < meta->n_philos)
	{
		if (pthread_create(&meta->philo[i].thread, NULL, \
				dispatch_lifecycle, &(meta->philo[i])) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < meta->n_philos)
	{
		if (pthread_join(meta->philo[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}
