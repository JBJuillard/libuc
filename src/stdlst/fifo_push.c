/*
** fifo_push.c
**
** fifo_push function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/03/09 by Juillard Jean-Baptiste
** Updated: 2018/03/14 by Juillard Jean-Baptiste
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

#include <libuc/stddef.h>
#include <libuc/errno.h>
#include <stdlib.h>			/* Dev: a modifier après implantation de malloc */
#include <libuc/stdint.h>
#include <libuc/stdlst.h>

fifo_t	*fifo_push(fifo_t **que, void *key, size_t size)
{
	register fifo_t	*tmp;

	if (!que || !key || !size || size > SIZE_MAX)
	{
		errno = EINVAL;
		return ((fifo_t *)(NULL));
	}
	errno = 0;
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
