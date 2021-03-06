/*
** abs.c
**
** abs function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/14 by Juillard Jean-Baptiste
** Updated: 2018/03/26 by Juillard Jean-Baptiste
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

#include <libuc/limits.h>
#include <libuc/errno.h>

int	abs(int n)
{
	if (n < INT_MIN || n > INT_MAX)
	{
		errno = EINVAL;
		return (INT_MIN);
	}
	else if (n == INT_MIN)
	{
		errno = ERANGE;
		return (INT_MIN);
	}
	errno = 0;
	if (n < 0)
		return (-n);
	return (n);
}
