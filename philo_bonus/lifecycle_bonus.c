/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:50:53 by linyao            #+#    #+#             */
/*   Updated: 2024/09/04 17:41:47 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_death(t_phi *phi)
{
	ft_sleep(phi->meta_s->t_die + 1);
	sem_wait(phi->meta_s->sem_stop);
	sem_wait(phi->meta_s->sem_eat);
	if ((get_timestamp() - phi->t_lastmeal) >= (long)(phi->meta_s->t_die) \
									&& !is_dead(phi, FLAG_QUERY))
	{
		sem_post(phi->meta_s->sem_stop);
		sem_post(phi->meta_s->sem_eat);
		put_msg(phi, " died", -1);
		is_dead(phi, FLAG_DEATH);
	}
	sem_post(phi->meta_s->sem_stop);
	sem_post(phi->meta_s->sem_eat);
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
}

void	dispatch_lifecycle(t_phi *phi)
{
	while (!is_dead(phi, FLAG_QUERY))
	{
		if (phi->meta_s->n_phi == 1)
		{
			ft_sleep(phi->meta_s->t_die * 2);
			return ;
		}
		sem_wait(phi->meta_s->sem_fork);
		put_msg(phi, " has taken 1st fork", -1);
		sem_wait(phi->meta_s->sem_fork);
		put_msg(phi, " has taken 2nd fork", -1);
		eat(phi);
		if (phi->n_eaten == phi->meta_s->n_eats)
		{
			sem_wait(phi->meta_s->sem_stop);
			if (++phi->meta_s->n_p_eat_fl == phi->meta_s->n_phi)
			{
				sem_post(phi->meta_s->sem_stop);
				is_dead(phi, FLAG_STOP);
			}
			sem_post(phi->meta_s->sem_stop);
		}
	}
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
