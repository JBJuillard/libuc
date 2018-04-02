/*
** imaxabs.c
**
** imaxabs function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/30 by Juillard Jean-Baptiste
** Updated: 2018/03/31 by Juillard Jean-Baptiste
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

#include <libuc/stdint.h>
#include <libuc/errno.h>

intmax_t	imaxabs(intmax_t n)
{
	if (n < INTMAX_MIN || n > INTMAX_MAX)
	{
		errno = EINVAL;
		return ((n > INTMAX_C(0)) ? (INTMAX_MAX) : (INTMAX_MIN));
	}
	else if (n == INTMAX_MIN)
	{
		errno = ERANGE;
		return (INTMAX_MIN);
	}
	errno = 0;
	if (n < INTMAX_C(0))
		return (-n);
	return (n);
}
