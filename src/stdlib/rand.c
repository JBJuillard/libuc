/*
** rand.c
**
** rand function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/02/25 by Juillard Jean-Baptiste
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

#include <libuc/errno.h>
#include <libuc/limits.h>

static unsigned long	next = 1;

void	srand(unsigned int seed)
{
	if (!seed)
	{
		errno = EINVAL;
		return ;
	}
	errno ^= errno;
	next = seed;
}

int	rand(void)
{
	register unsigned long int	seed;

	seed = next;
	seed = seed * 1103515245 + 12345;
	next = seed;
	return((int)((seed / 65536) % 32768));
}
