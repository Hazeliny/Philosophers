/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:51:35 by linyao            #+#    #+#             */
/*   Updated: 2024/09/04 17:43:10 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	handle_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

int	is_valid_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(char **av)
{
	if (is_valid_digit(av[1]) == 1 || ft_atoi1(av[1]) > MAX_PHILOS \
							|| ft_atoi1(av[1]) <= 0)
		return (printf("Incorrect number of philosophers\n"), 1);
	if (is_valid_digit(av[2]) == 1 || ft_atoi1(av[2]) <= 0)
		return (printf("Incorrect time to die\n"), 1);
	if (is_valid_digit(av[3]) == 1 || ft_atoi1(av[3]) <= 0)
		return (printf("Incorrect time to eat\n"), 1);
	if (is_valid_digit(av[4]) == 1 || ft_atoi1(av[4]) <= 0)
		return (printf("Incorrect time to sleep\n"), 1);
	if (av[5] && (is_valid_digit(av[5]) == 1 || ft_atoi1(av[5]) <= 0))
	{
		printf("Incorrect number of times each philo must eat\n");
		return (1);
	}
	return (0);
}

void	clean_sem(t_meta *meta)
{
/*
	int	i;

	i = 0;
	while (i < meta->n_phi)
		kill(meta->phi[i++].pid, SIGKILL);
*/
	sem_close(meta->sem_fork);
	sem_close(meta->sem_stop);
	sem_close(meta->sem_eat);
	sem_close(meta->sem_display);
	sem_close(meta->sem_dead);
	sem_unlink("/sem_fork");
	sem_unlink("/sem_stop");
	sem_unlink("/sem_eat");
	sem_unlink("/sem_display");
	sem_unlink("/sem_dead");
}

int	main(int ac, char **av)
{
	t_meta	meta;

	if (ac != 5 && ac != 6)
		return (write(2, "Incorrect number of arguments\n", 30), 1);
	if (check_args(av) == 1)
		return (1);
	init_meta(&meta, av);
	init_philo(&meta);
	if (manage_philos_lifecycle(&meta) != 0)
		return (1);
	clean_sem(&meta);
	return (0);
}
