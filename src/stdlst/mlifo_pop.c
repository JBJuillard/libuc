/*
** mlifo_pop.c
**
** mlifo_pop function of Undefined-C library
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

#include <stdlib.h>			/* Dev: a modifier après implataion de free */
#include <libuc/errno.h>
#include <libuc/stdlst.h>

void	**mlifo_pop(mlifo_t **mstk)
{
	register mlifo_t	*tmp;
	register void		**kptr;

	errno = 0;
	if (!mstk)
	{
		errno = EINVAL;
		return (NULL);
	}
	else if (!*mstk)
		return (NULL);
	tmp = *mstk;
	*mstk = tmp->next;
	kptr = tmp->kptr;
	tmp->kptr = (void **)(NULL);
	tmp->sptr = (size_t *)(NULL);
	tmp->next = (mlifo_t *)(NULL);
	free((void *)(tmp));
	return (kptr);
}
