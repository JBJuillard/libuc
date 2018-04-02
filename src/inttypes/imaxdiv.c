/*
** imaxdiv.c
**
** imaxdiv function of Undefined-C library
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
#include <libuc/inttypes.h>
#include <libuc/errno.h>

imaxdiv_t	imaxdiv(intmax_t numer, intmax_t denom)
{
    static imaxdiv_t	imaxdiv;

	imaxdiv.quot = 0;
	imaxdiv.rem = 0;
	if (!denom)
	{
		errno = EINVAL;
		return(imaxdiv);
	}
	errno = 0;
	imaxdiv.quot = numer / denom;
	imaxdiv.rem = numer % denom;
	return (imaxdiv);
}
