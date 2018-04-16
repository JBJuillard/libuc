/*
** ut_memccpy.c
**
** Unit tests for memcpy function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/15 by Juillard Jean-Baptiste
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

#include <libuc/stddef.h>
#include <libuc/string.h>
#include <libuc/errno.h>
#include <stdlib.h>

typedef struct			test_s
{
	const void			*src;
	void				*dst;
	int					c;
	size_t				n;
	void				*ret;
	int					err;
}						test_t;

int	ut_memccpy_interface(int N)
{
	int				err;
	int				i;
	unsigned char	src[128];
	unsigned char	dst[128];
	test_t			tdat[6] = {	{(const void *)(NULL), (void *)(dst), (int)('\n'), 128, NULL, EINVAL},
								{(const void *)(src), NULL, (int)('\n'), 128, NULL, EINVAL},
								{(const void *)(src), (void *)(dst), -1, 128, NULL, EINVAL},
								{(const void *)(src), (void *)(dst), 256, 128, NULL, EINVAL},
								{(const void *)(src), (void *)(dst), (int)('\n'), 0, NULL, EINVAL},
								{(const void *)(src), (void *)(dst), (int)('\n'), 128, (void *)(dst), 0} };

	i ^= i;
	N = N;
	while (i < 127)
	{
		src[i] = (((char)(i % 10)) + '0');
		++i;
	}
	src[127] = '\n';
	err = 0xff;
	i ^= i;
	while (i < 6)
	{
		memset((void *)(dst), 0, 128);
		if (memccpy((tdat[i]).dst, (tdat[i]).src, (tdat[i]).c, (tdat[i]).n) != (tdat[i]).ret
			|| errno != (tdat[i]).err)
			return (err);
		--err;
		++i;
	}
	return (0);
}

int	ut_memccpy_validity(int N)
{
	int				i;
	int				err;
	unsigned char	*src;
	unsigned char	*dst;

	i ^= i;
	err = 0xff;
	if ((src = (unsigned char *)malloc(N * sizeof(char))) == (unsigned char *)(NULL)
		|| (dst = (unsigned char *)malloc(N * sizeof(char))) == (unsigned char *)(NULL))
	{
		if (src)
			free((void *)(src));
		return (err);
	}
	--err;
	srand(N);
	while (i < (N - 1))
		src[i++] = (((unsigned char)(rand() % 0x80)) + '\0');
	src[N - 1] = 0x80;
	memset((void *)(dst), 0, N);
	if (memccpy((void *)(dst), (void *)(src), 0x80, (size_t)(N)) != (void *)(dst)
		|| errno)
	{
		free((void *)(src));
		free((void *)(dst));
		return (err);
	}
	--err;
	if (memcmp((void *)(dst), (void *)(src), (size_t)(N - 1)))
	{
		free((void *)(src));
		free((void *)(dst));
		return (err);
	}
	free((void *)(src));
	free((void *)(dst));
	return (0);
}

int	ut_memccpy_memchk(int N)
{
	return (ut_memccpy_validity(N));
}

int	ut_memccpy_timeout(int N)
{
	return (ut_memccpy_validity(N));
}
