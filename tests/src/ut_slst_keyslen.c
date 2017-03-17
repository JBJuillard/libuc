/*
** Units tests of slst_keyslen function for Undefined-C library
**
** Created: 02/08/2017 by Juillard Jean-Baptiste
** Updated: 02/10/2017 by Juillard Jean-Baptiste
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
#include <limits.h>
#include "stdlst.h"
#include "test.h"

typedef struct			test_s
{
	int					lst;
	int					err;
	unsigned long long	ret;
}						test_t;

int	ut_slst_keyslen_interface(int N)
{
	slst_t				*lst;
	slst_t				**lptr;
	unsigned long long	ret;
	int					err;
	int					i;
	static test_t		ut_list[2] = {	{0,EINVAL,0},
										{1,0,0}};

	i = 0;
	err = 0xFF;
	(ut_list[1]).ret = (unsigned long long)(N * sizeof(long long));
	while (i < 2)
	{
		if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
			return (errno);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
		errno = 0;
		ret = (unsigned long long)slst_keyslen(lptr);
		if (errno != (ut_list[i]).err
			|| (ret != (ut_list[i]).ret))
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

int	ut_slst_keyslen_memchk(int N)
{
	slst_t				*lst;
	unsigned long long	ret;

	errno = 0;
	if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
		return (errno);
	if ((ret = (unsigned long long)slst_keyslen(&lst)) != (unsigned long long)(N * sizeof(long long)) || errno)
	{
		slst_purge(&lst, &_ofree);
		if (errno)
			return (errno);
		return (0xFF);
	}
	slst_purge(&lst, &_ofree);
	return (0);
}

int	ut_slst_keyslen_timeout(int N)
{
	return (ut_slst_keyslen_memchk(N));
}
