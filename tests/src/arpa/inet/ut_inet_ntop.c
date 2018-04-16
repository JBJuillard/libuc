/*
** ut_inet_ntop.c
**
** Unit tests for inet_ntop function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/14 by Juillard Jean-Baptiste
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

#include <libuc/errno.h>
#include <libuc/arpa/inet.h>
#include <endian.h>
#include <libuc/stdint.h>
#include <libuc/string.h>
#include <libuc/netinet/in.h>
#include "test.h"

typedef struct			test_s
{
	int					af;
	int					src;
	int					dst;
	struct in_addr		in;
	struct in6_addr		in6;
	char				*str;
	socklen_t			size;
	int					err;
}						test_t;

#include <stdio.h>

int	ut_inet_ntop_interface(int N)
{
	int				err;
	int				i;
	char			buff[64];
	test_t			tdat[14] = {{0, 1, 1, {htobe32(0x7f000001)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}, "127.0.0.1", (socklen_t)(INET_ADDRSTRLEN), EINVAL},
								{AF_INET, 0, 1, {htobe32(0x7f000001)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}, "127.0.0.1", (socklen_t)(INET_ADDRSTRLEN), EINVAL},
								{AF_INET, 1, 0, {htobe32(0x7f000001)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}, "127.0.0.1", (socklen_t)(INET_ADDRSTRLEN), EINVAL},
								{AF_INET, 1, 1, {htobe32(0x7f000001)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}, "127.0.0.1", (socklen_t)(0), EINVAL},
								{AF_INET, 1, 1, {htobe32(0x7f000001)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}, "127.0.0.1", (socklen_t)(1), ENOSPC},
								/*{(AF_INET + AF_INET6), 1, 1, {htobe32(0x7f000001)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}, "127.0.0.1", (socklen_t)(INET_ADDRSTRLEN), EAFNOSUPPORT},*/
								/*{AF_INET, 1, 1, {htobe32(0x7f000001)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}, "127.0.0.1", (socklen_t)(INET_ADDRSTRLEN), 0},*/
								{0, 1, 1, {htobe32(0)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}, "::1", (socklen_t)(INET6_ADDRSTRLEN), EINVAL},
								{AF_INET6, 0, 1, {htobe32(0)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}, "::1", (socklen_t)(INET6_ADDRSTRLEN), EINVAL},
								{AF_INET6, 1, 0, {htobe32(0)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}, "::1", (socklen_t)(INET6_ADDRSTRLEN), EINVAL},
								{AF_INET6, 1, 1, {htobe32(0)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}, "::1", (socklen_t)(0), EINVAL},
								{AF_INET6, 1, 1, {htobe32(0)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}, "::1", (socklen_t)(1), ENOSPC},
								/*{128, 1, 1, {htobe32(0)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}, "::1", (socklen_t)(INET6_ADDRSTRLEN), EAFNOSUPPORT},-*/
								{AF_INET6, 1, 1, {htobe32(0)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}, "::1", (socklen_t)(INET6_ADDRSTRLEN), 0} };
	const char		*ret;
	const void		*src;
	char			*dst;
	int				af;

	i ^= i;
	N = N;
	err = 0xff;
	while (i < 11)
	{
		errno = 0;
		af = (tdat[i]).af;
		if ((tdat[i]).src)
		{
			if ((tdat[i]).af == AF_INET)
				src = (const void *)(&((tdat[i]).in));
			else if ((tdat[i]).af == AF_INET6)
				src = (const void *)(&((tdat[i]).in6));
			else
				src = (const void *)(NULL);
		}
		else
			src = (const void *)(NULL);
		if ((tdat[i]).dst)
			dst = buff;
		else
			dst = (char *)(NULL);
		ret = inet_ntop(af, src, dst, (tdat[i]).size);
		if (errno != (tdat[i]).err
			|| (!((tdat[i]).err) && strcmp((tdat[i]).str, ret)))
		{
			printf("err: %i, ret: %s\n", errno, ret);
			return (err);
		}
		printf("ret: %s\n", ret);
		err--;
		i++;
	}
	return (0);
}

int	ut_inet_ntop_validity(int N)
{
	int				err;
	int				i;
	test_t			tdat[5] = {	{AF_INET, 1, 1, {htobe32(0x00000000)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}, "0.0.0.0", (socklen_t)(INET_ADDRSTRLEN), 0},
								{AF_INET, 1, 1, {htobe32(0x7f000001)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}, "127.0.0.1", (socklen_t)(INET_ADDRSTRLEN), 0},
								{AF_INET, 1, 1, {htobe32(0xffffffff)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}, "255.255.255.255", (socklen_t)(INET_ADDRSTRLEN), 0},
								{AF_INET, 1, 1, {htobe32(0xc0a80001)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}, "192.168.0.1", (socklen_t)(INET_ADDRSTRLEN), 0},
								{AF_INET6, 1, 1, {htobe32(0)}, {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}, "::1", (socklen_t)(INET6_ADDRSTRLEN), 0} };
	char			ret[64];
	const void		*src;

	i ^= i;
	N = N;
	err = 0xff;
	while (i < 5)
	{
		errno = 0;
		if ((tdat[i]).af == AF_INET)
			src = (const void *)(&((tdat[i]).in));
		else if ((tdat[i]).af == AF_INET6)
			src = (const void *)(&((tdat[i]).in6));
		else
			src = (const void *)(NULL);
		if (!(inet_ntop((tdat[i]).af, src, ret, (tdat[i]).size))
			|| errno != (tdat[i]).err
			|| strcmp((tdat[i]).str, ret))
			return (err);
		err--;
		i++;
	}
	return (0);
}

int	ut_inet_ntop_memchk(int N)
{
	uint32_t			i;
	union
	{
		struct in_addr	a;
		uint32_t		n;
	}					in;
	char			buff[64];

	i ^= i;
	while (i < (uint32_t)(N))
	{
		in.n = htobe32(i++);
		memset((void *)(buff), '\0', 64);
		inet_ntop(AF_INET, (const void *)(&(in.a)), buff, (socklen_t)(INET_ADDRSTRLEN));
	}
	return (0);
}

int	ut_inet_ntop_timeout(int N)
{
	return(ut_inet_ntop_memchk(N));
}
