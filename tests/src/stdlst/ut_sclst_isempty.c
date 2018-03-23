/*
** ut_sclst_isempty.c
**
** Unit tests for sclst_isempty function of Undefined-C library
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

#include <libuc/stdlib.h>
#include <libuc/stdint.h>
#include <libuc/limits.h>
#include <libuc/stdlst.h>
#include <libuc/errno.h>
#include "test.h"

typedef struct	test_s
{
	int			lst;
	int			NULLlst;
	int			err;
	int			ret;
}				test_t;

int	ut_sclst_isempty_interface(int N)
{
	sclst_t			*lst;
	sclst_t			**lptr;
	int				ret;
	int				err;
	int				i;
	static test_t	ut_list[3] = {	{0,0,EINVAL,0},
									{1,1,0,1},
									{1,0,0,0}};

	i = 0;
	err = 0xFF;
	while (i < 3)
	{
		lst = (sclst_t *)(NULL);
		if (!(ut_list[i]).NULLlst
			&& (lst = _gen_sclst(1, N, 1)) == (sclst_t *)(NULL))
			return (errno);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (sclst_t **)(NULL);
		errno = 0;
		ret = sclst_isempty(lptr);
		if (errno != (ut_list[i]).err
			|| (ret != (ut_list[i]).ret))
		{
			sclst_purge(&lst, &_ofree);
			return (err);
		}
		sclst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_sclst_isempty_memchk(int N)
{
	sclst_t	*lst;
	int		ret;

	errno = 0;
	if ((lst = _gen_sclst(1, N, 1)) == (sclst_t *)(NULL))
		return (errno);
	if ((ret = sclst_isempty(&lst)) != 0 || errno)
	{
		sclst_purge(&lst, &_ofree);
		if (errno)
			return (errno);
		return (0xFF);
	}
	sclst_purge(&lst, &_ofree);
	return (0);
}

int	ut_sclst_isempty_timeout(int N)
{
	return (ut_sclst_isempty_memchk(N));
}
