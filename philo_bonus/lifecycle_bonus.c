/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:50:53 by linyao            #+#    #+#             */
/*   Updated: 2024/09/05 16:29:14 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *p)
{
	t_phi	*phi;

	phi = (t_phi *)p;

	while (!is_dead(phi, FLAG_QUERY))
	{
		ft_sleep(phi->meta_s->t_die + 1);
		sem_wait(phi->meta_s->sem_eat);
		if ((get_timestamp() - phi->t_lastmeal) >= \
						(long)(phi->meta_s->t_die))
		{
			sem_post(phi->meta_s->sem_eat);
			sem_wait(phi->meta_s->sem_disposable);
			put_msg(phi, " died", -1);
			is_dead(phi, FLAG_DEATH);
			exit(1);
		}
		sem_post(phi->meta_s->sem_eat);
	}
	return (NULL);
}

int	get_fork(t_phi *phi)
{
	sem_wait(phi->meta_s->sem_fork);
	put_msg(phi, " has taken 1st fork", -1);
	if (phi->meta_s->n_phi == 1)
	{
		ft_sleep(phi->meta_s->t_die * 2);
		sem_post(phi->meta_s->sem_fork);
		return (0);
	}
	sem_wait(phi->meta_s->sem_fork);
	put_msg(phi, " has taken 2nd fork", -1);
	return (1);
}

void	eat(t_phi *phi)
{
	sem_wait(phi->meta_s->sem_eat);
	phi->t_lastmeal = get_timestamp();
	phi->n_eaten++;
	put_msg(phi, " is eating", phi->n_eaten);
	sem_post(phi->meta_s->sem_eat);
	ft_sleep(phi->meta_s->t_eat);
	sem_post(phi->meta_s->sem_fork);
	sem_post(phi->meta_s->sem_fork);
	put_msg(phi, " is sleeping", -1);
	ft_sleep(phi->meta_s->t_sleep);
	put_msg(phi, " is thinking", -1);
	if (phi->n_eaten == phi->meta_s->n_eats)
	{
		is_dead(phi, FLAG_STOP);
		sem_wait(phi->meta_s->sem_stop);
		if (++phi->meta_s->n_p_eat_fl == phi->meta_s->n_phi)
		{
			sem_post(phi->meta_s->sem_stop);
			exit (1);
		}
		sem_post(phi->meta_s->sem_stop);
	}
//	put_msg(phi, " is sleeping", -1);
//	ft_sleep(phi->meta_s->t_sleep);
//	put_msg(phi, " is thinking", -1);
}

int	dispatch_lifecycle(t_phi *phi)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, check_death, phi))
		handle_error("error in creating thread");
	if (phi->id % 2 == 0)
		ft_sleep(phi->meta_s->t_eat / 10);
	while (!is_dead(phi, FLAG_QUERY))
	{
		if (!get_fork(phi))
			break ;
		eat(phi);
		if (phi->n_eaten == phi->meta_s->n_eats)
			break ;
	}
	if (pthread_join(monitor, NULL))
		handle_error("error in joining thread");
	return (0);
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
			handle_error("error in creating process");
		if (meta->phi[i].pid == 0)
		{
			if (dispatch_lifecycle(&meta->phi[i]) != 0)
				return (-1);
		}
		i++;
	}
	terminate_process(meta);
	return (0);
}
