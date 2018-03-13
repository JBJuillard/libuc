/*
** ut_slst_map.c
**
** Unit tests for slst_map function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/02/05 by Juillard Jean-Baptiste
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
	int			lst;
	int			err;
	int			returnNULLptr;
}				test_t;


int	ut_slst_map_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	mslst_t			*mlst;
	int				err;
	int				i;
	static test_t	ut_list[2] = {	{ 0, EINVAL, 1 },
									{ 1, 0, 0 }};

	i = 0;
	err = 0xFF;
	lst = (slst_t *)(NULL);
	while (i < 2)
	{
		if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
			return (errno);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
		errno = 0;
		mlst = slst_map(lptr);
		if (errno != (ut_list[i]).err
			||(!mlst && !(ut_list[i]).returnNULLptr)
			||(mlst && (ut_list[i]).returnNULLptr))
		{
			mslst_purge(&mlst);
			slst_purge(&lst, &_ofree);
			if (errno != (ut_list[i]).err)
				return (err);
		}
		mslst_purge(&mlst);
		slst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_map_memchk(int N)
{
	slst_t	*lst;
	mslst_t	*mlst;

	lst = (slst_t *)(NULL);
	errno = 0;
	if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL)
		|| (mlst = slst_map(&lst)) == (mslst_t *)(NULL))
	{
		if (lst)
			slst_purge(&lst, &_ofree);
		return (errno);
	}
	mslst_purge(&mlst);
	slst_purge(&lst, &_ofree);
	if (errno)
		return (errno);
	return (0);
}

int	ut_slst_map_timeout(int N)
{
	return (ut_slst_map_memchk(N));
}
