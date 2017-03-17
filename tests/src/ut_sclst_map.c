/*
** Units tests of sclst_map function for Undefined-C library
**
** Created: 03/08/2017 by Juillard Jean-Baptiste
** Updated: 03/08/2017 by Juillard Jean-Baptiste
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
	int			err;
	int			returnNULLptr;
}				test_t;


int	ut_sclst_map_interface(int N)
{
	sclst_t			*lst;
	sclst_t			**lptr;
	msclst_t		*mlst;
	int				err;
	int				i;
	static test_t	ut_list[2] = {	{ 0, EINVAL, 1 },
									{ 1, 0, 0 }};

	i = 0;
	err = 0xFF;
	lst = (sclst_t *)(NULL);
	while (i < 2)
	{
		if ((lst = _gen_sclst(1, N, 1)) == (sclst_t *)(NULL))
			return (errno);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (sclst_t **)(NULL);
		errno = 0;
		mlst = sclst_map(lptr);
		if (errno != (ut_list[i]).err
			||(!mlst && !(ut_list[i]).returnNULLptr)
			||(mlst && (ut_list[i]).returnNULLptr))
		{
			msclst_purge(&mlst);
			sclst_purge(&lst, &_ofree);
			if (errno != (ut_list[i]).err)
				return (err);
		}
		msclst_purge(&mlst);
		sclst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_sclst_map_memchk(int N)
{
	sclst_t		*lst;
	msclst_t	*mlst;

	lst = (sclst_t *)(NULL);
	errno = 0;
	if ((lst = _gen_sclst(0, N, 1)) == (sclst_t *)(NULL)
		|| (mlst = sclst_map(&lst)) == (msclst_t *)(NULL))
	{
		if (lst)
			sclst_purge(&lst, &_ofree);
		return (errno);
	}
	msclst_purge(&mlst);
	sclst_purge(&lst, &_ofree);
	if (errno)
		return (errno);
	return (0);
}

int	ut_sclst_map_timeout(int N)
{
	return (ut_sclst_map_memchk(N));
}
