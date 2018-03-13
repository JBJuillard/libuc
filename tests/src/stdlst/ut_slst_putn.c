/*
** ut_slst_putn.c
**
** Unit tests for slst_putn function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/01/29 by Juillard Jean-Baptiste
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

#include <stdlib.h>			/* Dev: a modifier après implantation de malloc et de free */
#include <libuc/errno.h>
#include <libuc/stdint.h>
#include <libuc/stdlst.h>
#include "test.h"

typedef struct			test_s
{
	int					lst;
	int					key;
	unsigned long long	size;
	unsigned long long	n;
	int					err;
	int					returnNULLptr;
}						test_t;

int	ut_slst_putn_interface(int N)
{
	slst_t			*lst;
	slst_t			**lptr;
	void			*k;
	slst_t			*ret;
	int				err;
	int				i;
	int				j;
	static test_t	ut_list[7] = {	{ 0, 1, sizeof(long long), 1, EINVAL, 1 },
									{ 1, 0, sizeof(long long), 1, EINVAL, 1 },
									{ 1, 1, 0, 1, EINVAL, 1 },
									{ 1, 1, (SIZE_MAX + 1), 1, EINVAL, 1 },
									{ 1, 1, sizeof(long long), 0, EINVAL, 1 },
									{ 1, 1, sizeof(long long), (SIZE_MAX + 1), EINVAL, 1 },
									{ 1, 1, sizeof(long long), 1, 0, 0 }	};

	i = 0;
	err = 0xFF;
	while (i < 7)
	{
		lst = (slst_t *)(NULL);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
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
			ret = slst_putn(lptr, k, (ut_list[i]).size, (ut_list[i]).n);
			if (errno != (ut_list[i]).err
				|| (!ret && !((ut_list[i]).returnNULLptr))
				|| (ret && (ut_list[i]).returnNULLptr))
			{
				if (k)
					free(k);
				slst_purge(&lst, &_ofree);
				return (err);;
			}
			if (k && (ut_list[i]).err == EINVAL)
				free(k);
			j++;
		}
		slst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_putn_memchk(int N)
{
	slst_t	*lst;
	void	*k;
	int		i;

	i = 0;
	lst = (slst_t *)(NULL);
	while (i < N)
	{
		if ((k = malloc(sizeof(long long))) == NULL)
		{
			slst_purge(&lst, &_ofree);
			if (!errno)
				errno = -16;
			break ;
		}
		*((long long *)(k)) = i;
		errno = 0;
		if (slst_putn(&lst, k, sizeof(long long), 1) == (slst_t *)(NULL) || errno)
		{
			free(k);
			slst_purge(&lst, &_ofree);
			if (!errno)
				errno = -17;
			return (errno);
		}
		i++;
	}
	slst_purge(&lst, &_ofree);
	return (0);
}

int	ut_slst_putn_timeout(int N)
{
	return (ut_slst_putn_memchk(N));
}
