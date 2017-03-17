/*
** fifo_push function for Undefined-C library
**
** Created: 03/09/2016 by Juillard Jean-Baptiste
** Updated: 03/09/2017 by Juillard Jean-Baptiste
**
** This file is a part free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 3, or
** (at your option) any later version.
** 
** There is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; see the file LICENSE.  If not, write to
** the Free Software Foundation, Inc., 51 Franklin Street, Fifth
** Floor, Boston, MA 02110-1301, USA.
*/

#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include "stdlst.h"

fifo_t	*fifo_push(fifo_t **que, void *key, size_t size)
{
	register fifo_t	*tmp;

	if (!que || !key || !size || size > SIZE_MAX)
	{
		errno = EINVAL;
		return ((fifo_t *)(NULL));
	}
	errno = 0;
	tmp = (fifo_t *)(NULL);
	if ((tmp = (fifo_t *)malloc(sizeof(fifo_t))) == (fifo_t *)(NULL))
	{
		if (!errno)
			errno = ENOMEM;
		return ((fifo_t *)(NULL));
	}
	tmp->key = key;
	tmp->size = size;
	if (*que)
	{
		tmp->next = (*que)->next;
		(*que)->next = tmp;
	}
	else
		tmp->next = tmp;
	*que = tmp;
	return (tmp);
}
