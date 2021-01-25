/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 18:35:10 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/25 18:39:56 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)
{
	// THIS IS FOR CRTL-C only
    printf("Caught signal %d\n", sig);
}