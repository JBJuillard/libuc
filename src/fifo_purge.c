/*
** fifo_purge function for Undefined-C library
**
** Created: 03/09/2017 by Juillard Jean-Baptiste
** Updated: 03/16/2017 by Juillard Jean-Baptiste
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

#include <stdlib.h>
#include <errno.h>
#include "stdlst.h"

void	fifo_purge(fifo_t **que, void (*fdel)(void *, size_t))
{
	register fifo_t	*tmp;

	if (!que || !fdel)
	{
		errno = EINVAL;
		return ;
	}
	errno = 0;
	while (*que)
	{
		tmp = (*que)->next;
		(*fdel)(tmp->key, tmp->size);
		if (errno)
			return ;
		if (*que == tmp)
			*que = (fifo_t *)(NULL);
		else
			(*que)->next = tmp->next;
		tmp->key = NULL;
		tmp->size = 0;
		tmp->next = (fifo_t *)(NULL);
		free((void *)(tmp));
	}
}
