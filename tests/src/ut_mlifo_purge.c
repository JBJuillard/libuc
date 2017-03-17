/*
** Units tests of mlifo_purge function for Undefined-C library
**
** Created: 03/10/2017 by Juillard Jean-Baptiste
** Updated: 03/10/2017 by Juillard Jean-Baptiste
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 3, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
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
#include <stdint.h>
#include "stdlst.h"
#include "test.h"

typedef struct	test_s
{
	int			mstk;
	int			err;
}				test_t;


int	ut_mlifo_purge_interface(int N)
{
	lifo_t			*stk;
	mlifo_t			*mstk;
	mlifo_t			**mptr;
	int				err;
	int				i;
	static test_t	ut_list[2] = {	{ 0, EINVAL },
									{ 1, 0 }};

	i = 0;
	err = 0xFF;
	stk = (lifo_t *)(NULL);
	while (i < 2)
	{
		if ((stk = (lifo_t*)_gen_slst(1, N, 1)) == (lifo_t *)(NULL)
			|| (mstk = lifo_map(&stk)) == (mlifo_t *)(NULL))
		{
			if (stk)
				lifo_purge(&stk, &_ofree);
			return (errno);
		}
		if ((ut_list[i]).mstk)
			mptr = &mstk;
		else
			mptr = (mlifo_t **)(NULL);
		errno = 0;
		mlifo_purge(mptr);
		if (errno != (ut_list[i]).err)
		{
			while (mstk)
			{
				mptr = (mlifo_t **)(mstk->next);
				free((void *)(mstk));
				mstk = (mslst_t *)(mptr);
			}
			lifo_purge(&stk, &_ofree);
			if (errno != (ut_list[i]).err)
				return (err);
		}
		if ((ut_list[i]).err == EINVAL)
			mlifo_purge(&mstk);
		lifo_purge(&stk, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_mlifo_purge_memchk(int N)
{
	lifo_t	*stk;
	mlifo_t	*mstk;

	stk = (lifo_t *)(NULL);
	if ((stk = (lifo_t *)_gen_slst(1, N, 1)) == (lifo_t *)(NULL)
		|| (mstk = lifo_map(&stk)) == (mlifo_t *)(NULL))
	{
		if (stk)
			lifo_purge(&stk, &_ofree);
		return (errno);
	}
	errno = 0;
	mlifo_purge(&mstk);
	lifo_purge(&stk, &_ofree);
	if (errno)
		return (errno);
	return (0);
}

int	ut_mlifo_purge_timeout(int N)
{
	return (ut_mlifo_purge_memchk(N));
}
