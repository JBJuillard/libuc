/*
** ut_slst_deln.c
**
** Unit tests for slst_deln function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/01/17 by Juillard Jean-Baptiste
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

#include <libuc/stdlib.h>
#include <libuc/stdint.h>
#include <libuc/stdlst.h>
#include <libuc/errno.h>
#include "test.h"


typedef struct			test_s
{
	int					lst;
	unsigned long long	n;
	void				*f;
	int					err;
}						test_t;


int	ut_slst_deln_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	int				err;
	int				i;
	int				j;
	static test_t	ut_list[6] = {	{ 0, 1, ((void *)(&_ofree)), EINVAL },
					{ 1, 0, ((void *)(&_ofree)), EINVAL },
					{ 1, (SIZE_MAX + 1), ((void *)(&_ofree)), EINVAL },
					{ 1, 1, NULL, EINVAL },
					{ 1, 1, ((void *)(&_ofree)), 0 },
					{ 1, 1, ((void *)(&_ofree)), 0 }};

	i = 0;
	err = 0xFF;
	while (i < 6)
	{
		lst = (slst_t *)(NULL);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
		j = 0;
		if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
			return (errno);
		while (j++ < N)
		{
			errno = 0;
			slst_deln(lptr, (size_t)((ut_list[i]).n), (void (*)(void *, size_t))((ut_list[i]).f));
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

int	ut_slst_deln_memchk(int N)
{
	slst_t	*lst;

	lst =(slst_t *)(NULL);
	if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
		return (errno);
	errno = 0;
	while (lst && N-- >= 0)
	{
		slst_deln(&lst, 1, &_ofree);
		if (errno)
		{
			slst_purge(&lst, &_ofree);
			return (errno);
		}
	}
	return (0);
}

int	ut_slst_deln_timeout(int N)
{
	return (ut_slst_deln_memchk(N));
}
