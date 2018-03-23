/*
** lifo_push.c
**
** lifo_push function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2016/12/28 by Juillard Jean-Baptiste
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

#include <libuc/stddef.h>
#include <libuc/errno.h>
#include <stdlib.h>			/* Dev: a modifier après implantation de malloc */
#include <libuc/stdint.h>
#include <libuc/stdlst.h>

lifo_t	*lifo_push(lifo_t **stk, void *key, size_t size)
{
	register lifo_t	*tmp;

	if (!stk || !key || !size || size > SIZE_MAX)
	{
		errno = EINVAL;
		return ((lifo_t *)(NULL));
	}
	errno = 0;
	if ((tmp = (lifo_t *)malloc(sizeof(lifo_t))) == (lifo_t *)(NULL))
	{
		if (!errno)
			errno = ENOMEM;
		return ((lifo_t *)(NULL));
	}
	tmp->key = key;
	tmp->size = size;
	tmp->next = *stk;
	*stk = tmp;
	return (tmp);
}
