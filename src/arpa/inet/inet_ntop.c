/*
** inet_ntop.c
**
** inet_ntop function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/28 by Juillard Jean-Baptiste
** Updated: 2018/04/15 by Juillard Jean-Baptiste
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

#include <libuc/arpa/inet.h>
#include <libuc/errno.h>
#include <libuc/netinet/in.h>
#include <libuc/stdlib.h>
#include <string.h>

static char	*inet_ntop_inaddr(struct in_addr in)
{
	static char				cp[32];
	register unsigned int	byte;
	register char			*str;
	register int			i;
	register size_t			offset;
	auto union
	{
		struct in_addr		in;
		uint8_t				byte[4];
	}						addr;

	i ^= i;
	offset ^= offset;
	addr.in = in;
	while (i < 4)
	{
		if (i >= 1)
			cp[offset++] = '.';
		byte = addr.byte[i] & 0xff;
		if ((str = utoa(byte)) == (char *)(NULL)
			|| strcpy((cp + offset), str) == (char *)(NULL))
			return ((char *)(NULL));
		offset += strlen(str);
	}
	cp[offset] = '\0';
	return (cp);
}

static char	*inet_ntop_in6addr(struct in6_addr in)
{
	static char				cp[64];
	register uint16_t		word;
	register char			*str;
	register int			i;
	register size_t			offset;
	register int			nonzero;

	i ^= i;
	offset ^= offset;
	nonzero ^= nonzero;
	while (i < 16)
	{
		word = ((uint16_t)(in.s6_addr[i]) << 8) | (uint16_t)(in.s6_addr[i + 1]);
		if (word || (!word && nonzero))
		{
			if (!nonzero && i)
			{
				strcpy(cp, ((i == 2) ? ":" : "::"));
				offset += ((i == 2) ? (1) : (2));
			}
			else if (nonzero)
				cp[offset++] = ':';
			nonzero++;
			if ((str = utostr(word, 16, 0)) == (char *)(NULL)
				|| strcpy((cp + offset), str) == (char *)(NULL))
				return ((char *)(NULL));
			offset += strlen(str);
		}
		i += 2;
	}
	cp[offset] = '\0';
	return (cp);
}

const char	*inet_ntop(int af, const void * restrict src,
						char * restrict dest, socklen_t size)
{
	register char	*str;

	if (!af || !src || !dest
		|| !size || size > (socklen_t)(SIZE_MAX))
	{
		errno = EINVAL;
		return ((const char *)(NULL));
	}
	else if ((af == AF_INET  && size < INET_ADDRSTRLEN)
				|| (af == AF_INET6 && size < INET6_ADDRSTRLEN))
	{
		errno = ENOSPC;
		return ((const char *)(NULL));
	}
	errno = 0;
	if (af == AF_INET)
	{
		if (!(str = inet_ntop_inaddr(*((struct in_addr *)(src))))
			|| strlen(str) > (size_t)(size)
			|| strcpy(dest, str) != dest)
			return ((const char *)(NULL));
	}
	else if (af == AF_INET6)
	{
		if (!(str = inet_ntop_in6addr(*((struct in6_addr *)(src))))
			|| strlen(str) > (size_t)(size)
			|| strcpy(dest, str) != dest)
			return ((const char *)(NULL));
	}
	else
	{
		errno = EAFNOSUPPORT;
		return ((const char *)(NULL));
	}
	return ((const char *)(dest));
}
