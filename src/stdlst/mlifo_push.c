/*
** mlifo_push function for Undefined-C library
**
** Created: 03/09/2017 by Juillard Jean-Baptiste
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

#include <libuc/stddef.h>
#include <libuc/errno.h>
#include <stdlib.h>			/* Dev: a modifier après implatation de malloc */
#include <libuc/stdlst.h>

mlifo_t	*mlifo_push(mlifo_t **mstk, void **kptr, size_t *sptr)
{
	register mlifo_t	*tmp;

	if (!mstk)
	{
		errno = EINVAL;
		return ((mlifo_t *)(NULL));
	}
	errno = 0;
	tmp = (mlifo_t *)(NULL);
	if ((tmp = (mlifo_t *)malloc(sizeof(mlifo_t))) == (mlifo_t *)(NULL))
	{
		if (!errno)
			errno = ENOMEM;
		return ((mlifo_t *)(NULL));
	}
	tmp->kptr = kptr;
	tmp->sptr = sptr;
	tmp->next = *mstk;
	*mstk = tmp;
	return (tmp);
}
