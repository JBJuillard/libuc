/*
** Units tests of slst_apply function for Undefined-C library
**
** Created: 02/26/2017 by Juillard Jean-Baptiste
** Updated: 03/12/2017 by Juillard Jean-Baptiste
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
	int			lst;
	void		*f;
	int			err;
	int			ret;
}				test_t;


int	ut_slst_apply_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	int				err;
	int				i;
	int				ret;
	static test_t	ut_list[3] = {	{ 0, ((void *)(&_ofunc)), EINVAL, -1 },
									{ 1, NULL, EINVAL, -1 },
									{ 1, ((void *)(&_ofunc)), 0, 0 }};

	i = 0;
	err = 0xFF;
	while (i < 3)
	{
		if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
			return (errno);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
		errno = 0;
		ret = slst_apply(lptr, (int (*)(void **, size_t *))((ut_list[i]).f));
		if (errno != (ut_list[i]).err
			|| (ut_list[i]).ret != ret)
		{
			slst_purge(&lst, &_ofree);
			return (err);
		}
		slst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_apply_memchk(int N)
{
	slst_t	*lst;

	if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
		return (errno);
	errno = 0;
	slst_apply(&lst, &_ofunc);
	slst_purge(&lst, &_ofree);
	if (errno)
		return (errno);
	return (0);
}

int	ut_slst_apply_timeout(int N)
{
	return (ut_slst_apply_memchk(N));
}
