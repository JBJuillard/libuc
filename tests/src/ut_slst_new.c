/*
** Units tests of slst_new function for Undefined-C library
**
** Created: 29/01/2017 by Juillard Jean-Baptiste
** Updated: 29/01/2017 by Juillard Jean-Baptiste
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
#include "stdlst.h"

int	ut_slst_new_interface(int N)
{
	slst_t	*tmp;
	int		r;

	N = N;
	tmp = (slst_t *)(NULL);
	r = 0;
	if ((tmp = slst_new()) == (slst_t *)(NULL))
		return (errno);
	if (tmp->key)
		r += -1;
	if (tmp->size)
		r += -2;
	if (tmp->next)
		r += -4;
	free((void *)(tmp));
	return ((r) ? (0xFF + r) : (0));
}

int	ut_slst_new_memchk(int N)
{
	int	i;
	int	r;

	i = 0;
	while (i < N)
		if ((r = ut_slst_new_interface(i++)))
			return (r);
	return (0);
}

int	ut_slst_new_timeout(int N)
{
	return (ut_slst_new_memchk(N));
}
