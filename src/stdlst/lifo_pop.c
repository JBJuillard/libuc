/*
** lifo_pop.c
**
** lifo_pop function of Undefined-C library
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

#include <stdlib.h>			/* Dev: a modifier après implantation de free */
#include <libuc/errno.h>
#include <libuc/stdlst.h>

void	*lifo_pop(lifo_t **stk)
{
	register lifo_t	*tmp;
	register void	*key;

	errno = 0;
	if (!stk)
	{
		errno = EINVAL;
		return (NULL);
	}
	else if (!(*stk))
		return (NULL);
	tmp = *stk;
	*stk = tmp->next;
	key = tmp->key;
	tmp->key = NULL;
	tmp->size = 0;
	tmp->next = (lifo_t *)(NULL);
	free((void *)(tmp));
	return (key);
}
