/*
** Units tests of slst_xtrc function for Undefined-C library
**
** Created: 17/01/2017 by Juillard Jean-Baptiste
** Updated: 02/03/2017 by Juillard Jean-Baptiste
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

#include <stdlib.h>
#include <stdint.h>
#include "stdlst.h"
#include "test.h"

typedef struct	test_s
{
	int			lst;
	int			err;
	int			returnNULLptr;
}				test_t;

int	ut_slst_xtrc_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	slst_t			*ret;
	int				err;
	int				i;
	int				j;
	static test_t	ut_list[2] = {	{ 0, EINVAL, 1 },
									{ 1, 0, 0 }	};

	i = 0;
	err = 0xFF;
	while (i < 2)
	{
		if ((lst = _gen_slst(0, N, 1)) == (slst_t *)(NULL))
			return(errno);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
		j = 0;
		while (j < N)
		{
			errno = 0;
			ret = slst_xtrc(lptr);
			if (errno != (ut_list[i]).err
				|| (!ret && !((ut_list[i]).returnNULLptr))
				|| (ret && (ut_list[i]).returnNULLptr))
			{
				if (ret)
				{
					free(ret->key);
					free((void *)(ret));
				}
				slst_purge(&lst, &_ofree);
				return (err);
			}
			if (ret)
			{
				free(ret->key);
				free((void *)(ret));
			}
			j++;
		}
		slst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_xtrc_memchk(int N)
{
	slst_t	*lst;
	slst_t	*ptr;

	if ((lst = _gen_slst(0, N, 1)) == (slst_t *)(NULL))
		return (errno);
	while (lst && N-- >= 0)
	{
		if (!(ptr = slst_xtrc(&lst)) || errno)
		{
			if (ptr)
			{
				free(ptr->key);
				free((void *)(ptr));
			}
			slst_purge(&lst, &_ofree);
			return (errno);
		}
		free(ptr->key);
		free((void *)(ptr));
	}
	return (0);
}

int	ut_slst_xtrc_timeout(int N)
{
	return (ut_slst_xtrc_memchk(N));
}
