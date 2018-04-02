/*
** inet_pton.c
**
** inet_pton function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/30 by Juillard Jean-Baptiste
** Updated: 2018/03/30 by Juillard Jean-Baptiste
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

#include <netinet/in.h>
#include <libuc/errno.h>

#define RETURN_ECPY				-3
#define RETURN_EINVAL			-2
#define RETURN_EAFNOSUPPORT		-1
#define RETURN_EINADDR			0
#define RETURN_SUCCESS			1

static void	*inet_pton_inet(const char * restrict src)
{
	static struct in_addr	nl;
	register unsigned int	byte;
	register unsigned int	i;
	register size_t			offset;
	auto char				*end;

	errno = 0;
	i ^= i;
	offset ^= offset;
	while (i < 4)
	{
		if (((byte = strtou((char *)(src + offset), &end, 10)) == UINT_MAX
				&& errno)
			|| byte > 0xff)
			return (NULL);
		nl |= (byte << (8 * i));
		offset += (end - src - offset);
		if (i < 3 && (src + offset) != '.')
			return (NULL);
		++offset;
		++i;
	}
	if (*(src + offset))
		return (NULL);
	return ((void *)(&nl));
}

static void	*inet_pton_inet6(const char * restrict src)
{
	static struct in6_addr	nl;
	register unsigned int	word;
	register unsigned int	i;
	register size_t			offset;
	auto char				*end;
	auto const char			*tokens[8];

	if (!src)
	{
		errno = EINVAL;
		return (NULL);
	}
	errno = 0;
	i ^= i;
	tokens[i++] = src;
	offset ^= offset;
	while (*(src + offset))
	{
		if (((*(src + offset) < '0' || *(src + offset) > '9')
				&& (*(src + offset) < 'a' || *(src + offset) > 'f')
				&& (*(src + offset) < 'A' || *(src + offset) > 'F')
				&& *(src + offset) != ':')
			|| (*(src + offset) == ':'
				&& *(src + offset + 1)
				&& i == 8)
			|| (*(src + offset) == ':'
				&& !*(src + offset + 1)))
			return (NULL);
		if (*(src + offset) == ':')
			tokens[i++] = (const char *)(src + offset + 1);
		++offset;
	}
	offset = 15;
	while (1)
	{
		if (i)
		{
			if (((word = strtou(tokens[--i], (char **)(NULL), 16)) == UINT_MAX
					&& errno)
				|| word > 0xffff)
				return (NULL);
		}
		else
			word ^= word;
		nl[offset] = (uint8_t)(word & 0x00ff);
		nl[offset -  1] = (uint8_t)((word & 0xff00) >> 8);
		if (offset > 1)
			offset -= 2;
		else
			break ;
	}
	return ((void *)(&nl));
}

int			inet_pton(int af, const char * restrict src, void * restrict dest)
{
	register void	*nl;

	if (!af || !src || !dest)
	{
		errno = EINVAL;
		return (RETURN_EINVAL);
	}
	nl ^= nl;
	if (af == AF_INET)
	{
		if (!(nl = inet_pton_inet(src)))
			return (RETURN_EINADDR);
	}
	else if (af == AF_INET6)
	{
		if (!(nl = inet_pton_inet6(src)))
			return (RETURN_EINADDR);
	}
	else
	{
		errno = EAFNOSUPPORT;
		return (RETURN_EAFNOSUPPORT);
	}
	if (!memcpy(dest, nl, (af == AF_INET ? sizeof(in_addr) : sizeof(in6_addr))))
		return (RETURN_ECPY);
	return (RETURN_SUCCESS);
}
