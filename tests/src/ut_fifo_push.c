/*
** Units tests of fifo_push function for Undefined-C library
**
** Created: 03/10/2017 by Juillard Jean-Baptiste
** Updated: 03/10/2017 by Juillard Jean-Baptiste
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
#include <errno.h>
#include <stdint.h>
#include "stdlst.h"
#include "test.h"

typedef struct			test_s
{
	int					que;
	int					key;
	unsigned long long	size;
	int					err;
	int					returnNULLptr;
}						test_t;

int	ut_fifo_push_interface(int N)
{
	fifo_t			*que;
	fifo_t			**qptr;
	void			*k;
	fifo_t			*ret;
	int				i;
	int				j;
	int				err;
	static test_t	ut_list[6] = {	{ 0, 1, sizeof(long long), EINVAL, 1 },
									{ 1, 0, sizeof(long long), EINVAL, 1 },
									{ 1, 1, 0, EINVAL, 1 },
									{ 1, 1, (SIZE_MAX + 1), EINVAL, 1 },
									{ 1, 1, sizeof(long long), 0, 0 },
									{ 1, 1, sizeof(long long), 0, 0 }	};

	i = 0;
	err = 0xFF;
	while (i < 6)
	{
		que = (fifo_t *)(NULL);
		if ((ut_list[i]).que)
			qptr = &que;
		else
			qptr = (fifo_t **)(NULL);
		j = 0;
		while (j < N)
		{
			k = NULL;
			if ((ut_list[i]).key)
			{
				if ((k = malloc(sizeof(long long))) == NULL)
					break ;
				*((long long *)(k)) = j;
			}
			errno = 0;
			ret = fifo_push(qptr, k, (ut_list[i]).size);
			if (errno != (ut_list[i]).err
				|| (!ret && !((ut_list[i]).returnNULLptr))
				|| (ret && (ut_list[i]).returnNULLptr))
			{
				if (k && !ret)
					free(k);
				fifo_purge(&que, &_ofree);
				return (err);
			}
			if (k && (ut_list[i]).err ==  EINVAL)
				free(k);
			j++;
		}
		fifo_purge(&que, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_fifo_push_memchk(int N)
{
	fifo_t	*que;
	fifo_t	*ret;
	void	*k;
	int		i;

	i = 0;
	que = (fifo_t *)(NULL);
	while (i < N)
	{
		if ((k = malloc(sizeof(long long))) == NULL)
		{
			fifo_purge(&que, &_ofree);
			if (!errno)
				errno = -16;
			break ;
		}
		*((long long *)(k)) = i;
		errno = 0;
		if ((ret = fifo_push(&que, k, sizeof(long long))) == (fifo_t *)(NULL) || errno)
		{
			if (!ret)
				free(k);
			fifo_purge(&que, &_ofree);
			if (!errno)
				errno = -17;
			return (errno);
		}
		i++;
	}
	fifo_purge(&que, &_ofree);
	return (0);
}

int	ut_fifo_push_timeout(int N)
{
	return (ut_fifo_push_memchk(N));
}
