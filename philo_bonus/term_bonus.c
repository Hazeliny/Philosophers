/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:58:59 by linyao            #+#    #+#             */
/*   Updated: 2024/09/06 14:59:06 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	terminate_process(t_meta *meta)
{
	int	i;
	int	status;

	i = 0;
	while (i < meta->n_phi)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < meta->n_phi)
				kill(meta->phi[i].pid, SIGKILL);
			break ;
		}
		i++;
	}
}

