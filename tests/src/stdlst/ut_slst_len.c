/*
** ut_slst_len.c
**
** Unit tests for slst_len function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/02/08 by Juillard Jean-Baptiste
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

#include <stdlib.h>			/* Dev: a modifier après implantation de malloc et de free */
#include <libuc/stdint.h>
#include <libuc/limits.h>
#include <libuc/stdlst.h>
#include <libuc/errno.h>
#include "test.h"

typedef struct			test_s
{
	int					lst;
	int					err;
	unsigned long long	ret;
}						test_t;

int	ut_slst_len_interface(int N)
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
	(ut_list[1]).ret = (unsigned long long)(N);
	while (i < 2)
	{
		if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
			return (errno);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
		errno = 0;
		ret = (unsigned long long)slst_len(lptr);
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

int	ut_slst_len_memchk(int N)
{
	slst_t				*lst;
	unsigned long long	ret;

	errno = 0;
	if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
		return (errno);
	if ((ret = (unsigned long long)slst_len(&lst)) != (unsigned long long)(N) || errno)
	{
		slst_purge(&lst, &_ofree);
		if (errno)
			return (errno);
		return (0xFF);
	}
	slst_purge(&lst, &_ofree);
	return (0);
}

int	ut_slst_len_timeout(int N)
{
	return (ut_slst_len_memchk(N));
}
