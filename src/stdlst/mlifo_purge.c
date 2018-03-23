/*
** mlifo_purge.c
**
** mlifo_purge function of Undefined-C library
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

void	mlifo_purge(mlifo_t **mstk)
{
	register mlifo_t	*tmp;
	register mlifo_t	*ms;

	if (!mstk)
	{
		errno = EINVAL;
		return ;
	}
	errno = 0;
	ms = *mstk;
	while (ms)
	{
		tmp = ms;
		ms = tmp->next;
		tmp->kptr = (void **)(NULL);
		tmp->sptr = (size_t *)(NULL);
		tmp->next = (mlifo_t *)(NULL);
		free((void *)(tmp));
	}
}
