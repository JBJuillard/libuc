/*
** ut_slst_delp function for Undefined-C library
**
** Created: 01/17/2017 by Juillard Jean-Baptiste
** Updated: 01/31/2017 by Juillard Jean-Baptiste
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
	int			elm;
	void		*f;
	int			err;
}				test_t;


int	ut_slst_delp_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	slst_t			*elm;
	int				err;
	int				i;
	int				j;
	static test_t	ut_list[5] = {	{ 0, 1, ((void *)(&_ofree)), EINVAL },
									{ 1, 0, ((void *)(&_ofree)), EINVAL },
									{ 1, 1, NULL, EINVAL },
									{ 1, 1, ((void *)(&_ofree)), 0 },
									{ 1, 1, ((void *)(&_ofree)), 0 }};

	i = 0;
	err = 0xFF;
	while (i < 5)
	{
		lst = (slst_t *)(NULL);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
	        if ((lst = _gen_slst(0, N, 1)) == (slst_t *)(NULL))
			return (errno);
		j = 0;
		while (lst && j++ < N)
		{
			errno = 0;
			if ((ut_list[i]).elm)
				elm = lst;
			else
				elm = (slst_t *)(NULL);
			slst_delp(lptr, elm, (void (*)(void *, size_t))((ut_list[i]).f));
			if (errno != (ut_list[i]).err)
			{
				slst_purge(&lst, &_ofree);
				return (err);
			}
			else if ((ut_list[i]).err == EINVAL)
			{
				slst_purge(&lst, &_ofree);
				break ;
			}
		}
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_delp_memchk(int N)
{
	slst_t	*lst;

	errno = 0;
	if ((lst = _gen_slst(0, N, 1)) == (slst_t *)(NULL))
		return (errno);
	while (lst && N-- >= 0)
	{
		slst_delp(&lst, lst, &_ofree);
		if (errno)
		{
			slst_purge(&lst, &_ofree);
			return (errno);
		}
	}
	return (0);
}

int	ut_slst_delp_timeout(int N)
{
	return (ut_slst_delp_memchk(N));
}
