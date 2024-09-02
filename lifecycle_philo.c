/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:09:27 by linyao            #+#    #+#             */
/*   Updated: 2024/09/02 16:31:39 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_death(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	ft_sleep(philo->meta_shared->time_die + 1);
	pthread_mutex_lock(&philo->meta_shared->m_stop);
	pthread_mutex_lock(&philo->meta_shared->m_eat);
	if ((get_timestamp() - philo->t_lastmeal) >= \
		(long)(philo->meta_shared->time_die) && \
		!is_dead(philo, FLAG_QUERY))
	{
		pthread_mutex_unlock(&philo->meta_shared->m_stop);
		pthread_mutex_unlock(&philo->meta_shared->m_eat);
		put_msg(philo, " died", -1);
		is_dead(philo, FLAG_DEATH);
	}
	pthread_mutex_unlock(&philo->meta_shared->m_stop);
	pthread_mutex_unlock(&philo->meta_shared->m_eat);
	return (NULL);
}

int	get_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l);
	put_msg(philo, " has taken left fork", -1);
	if (philo->meta_shared->n_philos == 1)
	{
		ft_sleep(philo->meta_shared->time_die * 2);
		pthread_mutex_unlock(&philo->fork_l);
		return (0);
	}
	pthread_mutex_lock(philo->fork_r);
	put_msg(philo, " has taken right fork", -1);
	return (1);
}

void	eat(t_philo *philo)
{
//	put_msg(philo, " is eating\n");
	pthread_mutex_lock(&philo->meta_shared->m_eat);
	philo->t_lastmeal = get_timestamp();
	philo->n_eaten++;
	put_msg(philo, " is eating", philo->n_eaten);
	pthread_mutex_unlock(&philo->meta_shared->m_eat);
	ft_sleep(philo->meta_shared->time_eat);
	pthread_mutex_unlock(&philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	put_msg(philo, " is sleeping", -1);
	ft_sleep(philo->meta_shared->time_sleep);
	put_msg(philo, " is thinking", -1);
}

void	*dispatch_lifecycle(void *phi)
{
	t_philo		*p;
	pthread_t	t_monitor;

	p = (t_philo *)phi;
	if (p->id % 2 == 0)
		ft_sleep(p->meta_shared->time_eat / 10);
	while (!is_dead(p, FLAG_QUERY))
	{
		pthread_create(&t_monitor, NULL, check_death, phi);
		if (!get_fork(p))
			return (pthread_detach(t_monitor), NULL);
		eat(p);
		pthread_detach(t_monitor);
		if (p->n_eaten == p->meta_shared->n_eats)
		{
			pthread_mutex_lock(&p->meta_shared->m_stop);
			if (++p->meta_shared->n_p_eat_fl == p->meta_shared->n_philos)
			{
				pthread_mutex_unlock(&p->meta_shared->m_stop);
				is_dead(p, FLAG_STOP);
			}
			return (pthread_mutex_unlock(&p->meta_shared->m_stop), NULL);
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
