/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 < anrodri2@student.42lyon.fr >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 23:13:20 by anrodri2          #+#    #+#             */
/*   Updated: 2023/09/05 14:36:03 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_thread *thread)
{
	philo_print_state(IS_THINKING, thread->philo_nb, ms_since_start(thread->time_saved_ms), thread);
}

void	eating(t_thread *thread)
{
	pthread_mutex_lock((*thread).mutex_left_fork);
	philo_print_state(IS_TAKING_FORK, thread->philo_nb, ms_since_start(thread->time_saved_ms), thread);
	pthread_mutex_lock((*thread).mutex_right_fork);
	philo_print_state(IS_TAKING_FORK, thread->philo_nb, ms_since_start(thread->time_saved_ms), thread);
	philo_print_state(IS_EATING, thread->philo_nb, ms_since_start(thread->time_saved_ms), thread);
	thread->last_time_eat = gettime();
	ft_usleep(1000 * thread->time_to_eat, thread);
	pthread_mutex_unlock((*thread).mutex_left_fork);
	pthread_mutex_unlock((*thread).mutex_right_fork);
}

void	sleeping(t_thread *thread)
{
	philo_print_state(IS_SLEEPING, thread->philo_nb, ms_since_start(thread->time_saved_ms), thread);
	ft_usleep(1000 * thread->time_to_sleep, thread);
}

void	check_philo_dead(t_thread *thread)
{
	time_t	time_since_last_meal;

	time_since_last_meal = gettime() - thread->last_time_eat;
	if (time_since_last_meal >= thread->time_to_die)
		philo_print_state(IS_DEAD, thread->philo_nb, ms_since_start(thread->time_saved_ms), thread);
	// printf("LAST TIME EATEN: %d\n", gettime() - thread->last_time_eat);
}