/*
** seed48.c
**
** seed48 function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/15 by Juillard Jean-Baptiste
** Updated: 2018/03/15 by Juillard Jean-Baptiste
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

#include <libuc/stddef.h>

struct						seed48_s
{
	unsigned short int		_x[3];
	unsigned short int		_old_x[3];
	unsigned long long int	a;
	unsigned short int		c;
	unsigned short int		init;
};

unsigned short int		*seed48(unsigned short int seed16v[3])
{
	if (!seed16v)
	{
		errno = EINVAL;
		return ((unsigned short int *)(NULL));
	}
	errno = 0;
	seed48_s._old_x[2] = seed48_s._x[2];
	seed48_s._old_x[1] = seed48_s._x[1];
	seed48_s._old_x[0] = seed48_s._x[0];
	seed48_s._x[2] = seed16v[2];
	seed48_s._x[1] = seed16v[1];
	seed48_s._x[0] = seed16v[0];
	seed48_s.a = 0x5DEECE66Dul;
	seed48_s.c = 0xB;
	seed48_s.init = 1;
	return (seed48_s._old_x);
}
