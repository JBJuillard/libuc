/*
** ut_bcmp.c
**
** Unit tests for bcmp function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/01/26 by Juillard Jean-Baptiste
** Updated: 2018/03/12 by Juillard Jean-Baptiste
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
	int			s1;
	int			s1len;
	int			s1;
	int			err;
	int			returnValue;
}				test_t;

int	ut_bcmp_interface(int N)
{
	char			*s1;
	char			*s2;
	size_t			sizeN;
	int			ret;
	int				i;
	int				err;
	static test_t	ut_list[2] = {	{ 0, EINVAL, 1 },
									{ 1, 0, 0 }	};

	i = 0;
	err = 0xFF;
	while (i < 2)
	{
		if ((s1 = (char *)_gen_str(N)) == (char *)(NULL)
			|| (s2 = (char *)_gen_str(N)) == (char *)(NULL))
		{
			if (s1)
				free((void *)(s1));
			return (errno);
		}
		sizeN = N;
		ret = bcmp(s1, s2, sizeN);
		free((void *)(s1));
		free((void *)(s2));
		if (ret)
			return (err);
		i++;
		err--;
	}
	return (0);
}

int	ut_bcmp_memchk(int N)
{
	fifo_t	*que;
	void	*k;

	if ((que = (fifo_t *)_gen_sclst(1, N, 1)) == (fifo_t *)(NULL))
		return (errno);
	while (que && N-- > 0)
	{
		if (!(k = fifo_pop(&que)) || errno)
		{
			if (k)
				free(k);
			fifo_purge(&que, &_ofree);
			if (errno)
				return (errno);
			return (0xFF);
		}
		free(k);
	}
	return (0);
}

int	ut_bcmp_timeout(int N)
{
	return (ut_bcmp_memchk(N));
}
