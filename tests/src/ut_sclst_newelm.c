/*
** Units tests of sclst_newelm function for Undefined-C library
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
#include "stdlst.h"

int	ut_sclst_newelm_interface(int N)
{
	sclst_t	*tmp;
	int		r;

	N = N;
	tmp = (sclst_t *)(NULL);
	r = 0;
	if ((tmp = sclst_newelm()) == (sclst_t *)(NULL))
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

int	ut_sclst_newelm_memchk(int N)
{
	int	i;
	int	r;

	i = 0;
	while (i < N)
		if ((r = ut_sclst_newelm_interface(i++)))
			return (r);
	return (0);
}

int	ut_sclst_newelm_timeout(int N)
{
	return (ut_sclst_newelm_memchk(N));
}
