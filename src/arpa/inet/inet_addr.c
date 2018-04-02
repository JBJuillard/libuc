/*
** inet_addr.c
**
** inet_addr function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/28 by Juillard Jean-Baptiste
** Updated: 2018/03/28 by Juillard Jean-Baptiste
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

#include <netinet/in.h>		/* in_addr_t */
#include <libuc/errno.h>
#include <libuc/limits.h>

in_addr_t	inet_addr(const char *cp)
{
	register size_t		i;
	register int		byte;
	auto const char		*end;
	register int		scale;
	register uin32_t	netlong;

	if (!cp)
	{
		errno = EINVAL;
		return (INADDR_NONE);
	}
	errno = 0;
	i ^= i;
	netlong ^= netlong;
	scale ^= scale;
	while (i++ < 4)
	{
		end = (const char *)(NULL);
		if ((byte = strtoi(cp, &end, 10)) < 0
			|| (!byte && errno == EINVAL)
			|| (byte == INT_MAX && errno == ERANGE)
			|| byte > 0xff
			|| (i < 3 && *end != '.'))
			return(INADDR_NONE);
		netlong |= (uint32_t)(byte << scale);
		scale += 8;
		cp = end + 1U;
	}
	return ((in_addr_t)(netlong));
}
