/*
** ut_sclst_put function for Undefined-C library
**
** Created: 03/08/2017 by Juillard Jean-Baptiste
** Updated: 03/08/2017 by Juillard Jean-Baptiste
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
	int					lst;
	int					key;
	unsigned long long	size;
	int					err;
	int					returnNULLptr;
}						test_t;

int	ut_sclst_put_interface(int N)
{
	sclst_t			*lst;
	sclst_t			**lptr;
	void			*k;
	sclst_t			*ret;
	int				i;
	int				j;
	int				err;
	static test_t	ut_list[6] = {	{ 0, 1, sizeof(int), EINVAL, 1 },
									{ 1, 0, sizeof(int), EINVAL, 1 },
									{ 1, 1, 0, EINVAL, 1 },
									{ 1, 1, (SIZE_MAX + 1), EINVAL, 1 },
									{ 1, 1, sizeof(int), 0, 0 },
									{ 1, 1, sizeof(int), 0, 0 }	};

	i = 0;
	err = 0xFF;
	while (i < 6)
	{
		lst = (sclst_t *)(NULL);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (sclst_t **)(NULL);
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
			ret = sclst_put(lptr, k, (ut_list[i]).size);
			if (errno != (ut_list[i]).err
				|| (!ret && !((ut_list[i]).returnNULLptr))
				|| (ret && (ut_list[i]).returnNULLptr))
			{
				free(k);
				sclst_purge(&lst, &_ofree);
				return (err);
			}
			if (k && (ut_list[i]).err ==  EINVAL)
				free(k);
			j++;
		}
		sclst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_sclst_put_memchk(int N)
{
	sclst_t	*lst;
	void	*k;
	int		i;

	i = 0;
	lst = (sclst_t *)(NULL);
	while (i < N)
	{
		if ((k = malloc(sizeof(long long))) == NULL)
		{
			sclst_purge(&lst, &_ofree);
			if (!errno)
				errno = -16;
			break ;
		}
		*((long long *)(k)) = i;
		errno = 0;
		if (sclst_put(&lst, k, sizeof(long long)) == (slst_t *)(NULL) || errno)
		{
			free(k);
			sclst_purge(&lst, &_ofree);
			if (!errno)
				errno = -17;
			return (errno);
		}
		i++;
	}
	sclst_purge(&lst, &_ofree);
	return (0);
}

int	ut_sclst_put_timeout(int N)
{
	return (ut_sclst_put_memchk(N));
}
