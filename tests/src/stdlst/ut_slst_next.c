/*
** ut_slst_next.c
**
** Unit tests for slst_next function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/01/17 by Juillard Jean-Baptiste
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

typedef struct			test_s
{
	int					lst;
	int					elm;
	int					err;
	int					returnNULLptr;
}						test_t;

int	ut_slst_next_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	slst_t			*elm;
	slst_t			*ret;
	int				err;
	int				i;
	static test_t	ut_list[3] = {	{0,1,EINVAL,1},
									{1,0,EINVAL,1},
									{1,1,0,0}};

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
		if ((ut_list[i]).elm)
			elm = lst;
		else
			elm = (slst_t *)(NULL);
		errno = 0;
		ret = slst_next(lptr, elm);
		if (errno != (ut_list[i]).err
			|| (!ret && !(ut_list[i]).returnNULLptr)
			|| (ret && ret != lst->next))
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

int	ut_slst_next_memchk(int N)
{
	slst_t	*lst;
	slst_t	*tmp;

	errno = 0;
	if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
		return (errno);
	if (!(tmp = slst_next(&lst, lst)) || errno)
	{
		slst_purge(&lst, &_ofree);
		if (errno)
			return (errno);
		return (0xFF);
	}
	slst_purge(&lst, &_ofree);
	return (0);
}

int	ut_slst_next_timeout(int N)
{
	return (ut_slst_next_memchk(N));
}
