/*
** ut_lifo_map.c
**
** Unit tests for lifo_map function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/03/10 by Juillard Jean-Baptiste
** Updated: 2018/03/13 by Juillard Jean-Baptiste
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

#include <libuc/stdlib.h>
#include <libuc/stdint.h>
#include <libuc/stdlst.h>
#include "test.h"

typedef struct	test_s
{
	int			stk;
	int			err;
	int			returnNULLptr;
}				test_t;


int	ut_lifo_map_interface(int N)
{
	lifo_t			*stk;
	lifo_t			**sptr;
	mlifo_t			*mstk;
	int				err;
	int				i;
	static test_t	ut_list[2] = {	{ 0, EINVAL, 1 },
									{ 1, 0, 0 }};

	i = 0;
	err = 0xFF;
	stk = (lifo_t *)(NULL);
	while (i < 2)
	{
		if ((stk = (lifo_t *)_gen_slst(1, N, 1)) == (lifo_t *)(NULL))
			return (errno);
		if ((ut_list[i]).stk)
			sptr = &stk;
		else
			sptr = (lifo_t **)(NULL);
		errno = 0;
		mstk = lifo_map(sptr);
		if (errno != (ut_list[i]).err
			||(!mstk && !(ut_list[i]).returnNULLptr)
			||(mstk && (ut_list[i]).returnNULLptr))
		{
			mlifo_purge(&mstk);
			lifo_purge(&stk, &_ofree);
			if (errno != (ut_list[i]).err)
				return (err);
		}
		mlifo_purge(&mstk);
		lifo_purge(&stk, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_lifo_map_memchk(int N)
{
	lifo_t	*stk;
	mlifo_t	*mstk;

	stk = (lifo_t *)(NULL);
	errno = 0;
	if ((stk = (lifo_t *)_gen_slst(1, N, 1)) == (lifo_t *)(NULL)
		|| (mstk = lifo_map(&stk)) == (mlifo_t *)(NULL))
	{
		lifo_purge(&stk, &_ofree);
		return (errno);
	}
	mlifo_purge(&mstk);
	lifo_purge(&stk, &_ofree);
	if (errno)
		return (errno);
	return (0);
}

int	ut_lifo_map_timeout(int N)
{
	return (ut_lifo_map_memchk(N));
}
