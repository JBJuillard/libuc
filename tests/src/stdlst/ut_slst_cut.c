/*
** ut_slst_cut.c
**
** Unit tests for slst_cut function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/02/23 by Juillard Jean-Baptiste
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
#include <libuc/limits.h>
#include <libuc/stdlst.h>
#include <libuc/errno.h>
#include "test.h"

typedef struct	test_s
{
	int			lst;
	int			err;
	int			returnNULLptr;
}				test_t;


int	ut_slst_cut_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	slst_t			*ret;
	int				err;
	int				i;
	static test_t	ut_list[2] = {	{0,EINVAL,1},
									{1,0,0}};

	i = 0;
	err = 0xFF;
	while (i < 2)
	{
		if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
			return (errno);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
		errno = 0;
		ret = slst_cut(lptr);
		if (errno != (ut_list[i]).err
			|| (!ret && !(ut_list[i]).returnNULLptr)
			|| (ret && (ut_list[i]).returnNULLptr))
		{
			slst_purge(&lst, &_ofree);
			slst_purge(&ret, &_ofree);
			return (err);
		}
		slst_purge(&lst, &_ofree);
		slst_purge(&ret, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_cut_memchk(int N)
{
	slst_t	*lst;
	slst_t	*ret;

	errno = 0;
	if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
		return (errno);
	if ((ret = slst_cut(&lst)) == (slst_t *)(NULL) || errno)
	{
		slst_purge(&lst, &_ofree);
		if (!errno)
			return (0xFF);
		slst_purge(&ret, &_ofree);
		return (errno);
	}
	slst_purge(&lst, &_ofree);
	slst_purge(&ret, &_ofree);
	return (0);
}

int	ut_slst_cut_timeout(int N)
{
	return (ut_slst_cut_memchk(N));
}
