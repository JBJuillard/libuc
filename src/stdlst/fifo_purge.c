/*
** fifo_purge.c
**
** fifo_purge function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/03/09 by Juillard Jean-Baptiste
** Updated: 2018/03/21 by Juillard Jean-Baptiste
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

#include <stdlib.h>			/* Dev: a modifier après implantation de free */
#include <libuc/errno.h>
#include <libuc/stdlst.h>

void	fifo_purge(fifo_t **que, void (*fdel)(void *, size_t))
{
	register fifo_t	*tmp;
	register fifo_t	*q;
	register void	(*f)(void *, size_t);

	if (!que || !fdel)
	{
		errno = EINVAL;
		return ;
	}
	errno = 0;
	q = *que;
	*que = (fifo_t *)(NULL);
	f = fdel;
	while (q)
	{
		tmp = q->next;
		(*f)(tmp->key, tmp->size);
		if (errno)
		{
			*que = q;
			return ;
		}
		if (q == tmp)
			q = (fifo_t *)(NULL);
		else
			q->next = tmp->next;
		tmp->key = NULL;
		tmp->size = 0;
		tmp->next = (fifo_t *)(NULL);
		free((void *)(tmp));
	}
}
