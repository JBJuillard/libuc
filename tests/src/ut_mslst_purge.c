/*
** Units tests of mslst_purge function for Undefined-C library
**
** Created: 01/29/2017 by Juillard Jean-Baptiste
** Updated: 01/29/2017 by Juillard Jean-Baptiste
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
	int			mlst;
	int			err;
}				test_t;


int	ut_mslst_purge_interface(int N)
{
	slst_t			*lst;
	mslst_t			*mlst;
	mslst_t			**mptr;
	int				err;
	int				i;
	static test_t	ut_list[2] = {	{ 0, EINVAL },
									{ 1, 0 }};

	i = 0;
	err = 0xFF;
	lst = (slst_t *)(NULL);
	while (i < 2)
	{
		if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL)
			|| (mlst = slst_map(&lst)) == (mslst_t *)(NULL))
		{
			if (lst)
				slst_purge(&lst, &_ofree);
			return (errno);
		}
		if ((ut_list[i]).mlst)
			mptr = &mlst;
		else
			mptr = (mslst_t **)(NULL);
		errno = 0;
		mslst_purge(mptr);
		if (errno != (ut_list[i]).err)
		{
			while (mlst)
			{
				mptr = (mslst_t **)(mlst->next);
				free((void *)(mlst));
				mlst = (mslst_t *)(mptr);
			}
			slst_purge(&lst, &_ofree);
			if (errno != (ut_list[i]).err)
				return (err);
		}
		if ((ut_list[i]).err == EINVAL)
			mslst_purge(&mlst);
		slst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_mslst_purge_memchk(int N)
{
	slst_t	*lst;
	mslst_t	*mlst;

	lst = (slst_t *)(NULL);
	if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL)
		|| (mlst = slst_map(&lst)) == (mslst_t *)(NULL))
	{
		if (lst)
			slst_purge(&lst, &_ofree);
		return (errno);
	}
	errno = 0;
	mslst_purge(&mlst);
	slst_purge(&lst, &_ofree);
	if (errno)
		return (errno);
	return (0);
}

int	ut_mslst_purge_timeout(int N)
{
	return (ut_mslst_purge_memchk(N));
}
