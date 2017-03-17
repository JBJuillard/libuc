/*
** Units tests of sclst_next function for Undefined-C library
**
** Created: 17/01/2017 by Juillard Jean-Baptiste
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
#include "stdlst.h"
#include "test.h"

typedef struct			test_s
{
	int					lst;
	int					elm;
	int					err;
	int					returnNULLptr;
}						test_t;

int	ut_sclst_next_interface(int N)
{
	sclst_t			*lst;
	sclst_t			**lptr;
	sclst_t			*elm;
	sclst_t			*ret;
	int				err;
	int				i;
	static test_t	ut_list[3] = {	{0,1,EINVAL,1},
									{1,0,EINVAL,1},
									{1,1,0,0}};

	i = 0;
	err = 0xFF;
	while (i < 3)
	{
		if ((lst = _gen_sclst(1, N, 1)) == (sclst_t *)(NULL))
			return (errno);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (sclst_t **)(NULL);
		if ((ut_list[i]).elm)
			elm = lst->next;
		else
			elm = (sclst_t *)(NULL);
		errno = 0;
		ret = sclst_next(lptr, elm);
		if (errno != (ut_list[i]).err
			|| (!ret && !(ut_list[i]).returnNULLptr)
			|| (ret && ret != (lst->next)->next))
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

int	ut_sclst_next_memchk(int N)
{
	sclst_t	*lst;
	sclst_t	*tmp;

	errno = 0;
	if ((lst = _gen_sclst(1, N, 1)) == (sclst_t *)(NULL))
		return (errno);
	if (!(tmp = sclst_next(&lst, lst->next)) || errno)
	{
		sclst_purge(&lst, &_ofree);
		if (errno)
			return (errno);
		return (0xFF);
	}
	sclst_purge(&lst, &_ofree);
	return (0);
}

int	ut_sclst_next_timeout(int N)
{
	return (ut_sclst_next_memchk(N));
}
