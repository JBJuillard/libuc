/*
** fifo_pop function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
** Updated: 2018/03/12 by Juillard Jean-Baptiste
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

#include <stdlib.h>			/* Dev: a modifier après impantation de free */
#include <libuc/errno.h>
#include <libuc/stdlst.h>

void	*fifo_pop(fifo_t **que)
{
	register fifo_t	*tmp;
	register void	*key;

	errno = 0;
	if (!que)
	{
		errno = EINVAL;
		return (NULL);
	}
	else if (!*que)
		return (NULL);
	tmp = (*que)->next;
	if (*que == tmp)
		*que = (fifo_t *)(NULL);
	else
		(*que)->next = tmp->next;
	key = tmp->key;
	tmp->key = NULL;
	tmp->size = 0;
	tmp->next = (fifo_t *)(NULL);
	free((void *)(tmp));
	return (key);
}
