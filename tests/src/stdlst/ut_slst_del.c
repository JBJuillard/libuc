/*
** ut_slst_del.c
**
** Unit tests for slst_del function of Undefined-C library
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

#include <stdlib.h>			/* Dev: a modifier après implantation de malloc et de free */
#include <libuc/stdint.h>
#include <libuc/stdlst.h>
#include "test.h"

int	ut_slst_del_interface(int N)
{
	slst_t	*ptr;

	N = N;
	ptr = (slst_t *)(NULL);
	errno = 0;
	slst_del((slst_t **)(NULL), &_ofree);
	if (errno != EINVAL)
		return (0xFF);
	errno = 0;
	slst_del(&ptr, (void (*)(void*,size_t))(NULL));
	if (errno != EINVAL)
		return (0xFE);
	errno = 0;
	slst_del(&ptr, &_ofree);
	if (errno)
		return (0xFD);
	if ((ptr = (slst_t *)malloc(sizeof(slst_t))) == (slst_t *)(NULL)
		|| (ptr->key = malloc(sizeof(int))) == NULL)
    {
		if (ptr)
			free((void *)(ptr));
		return (errno);
	}
	ptr->size = sizeof(int);
	ptr->next = (slst_t *)(NULL);
	errno = 127;
	slst_del(&ptr, &_ofree);
	if (errno)
		return (0xFC);
	return (0);
}

int	ut_slst_del_memchk(int N)
{
	slst_t	*lst;

	if ((lst = _gen_slst(1, N, 1)) == (slst_t *)(NULL))
		return (errno);
	errno = 0;
	while (lst && N-- >= 0)
	{
		slst_del(&lst, &_ofree);
		if (errno)
		{
			slst_purge(&lst, &_ofree);
			return (errno);
		}
	}
	return (0);
}

int	ut_slst_del_timeout(int N)
{
	return (ut_slst_del_memchk(N));
}
