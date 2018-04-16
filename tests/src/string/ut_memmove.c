/*
** ut_memmove.c
**
** Unit tests for memmove function of Undefined-C library
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
	size_t				size;
	void				*ret;
	int					err;
}						test_t;

int	ut_memmove_interface(int N)
{
	int				err;
	int				i;
	unsigned char	src[128];
	test_t			tdat[4] = {	{(const void *)(NULL), (void *)(src + 64), 64, NULL, EINVAL},
								{(const void *)(src), NULL, 64, NULL, EINVAL},
								{(const void *)(src), (void *)(src + 64), 0, NULL, EINVAL},
								{(const void *)(src), (void *)(src + 64), 64, (void *)(src + 64), 0} };

	i ^= i;
	N = N;
	while (i < 128)
	{
		src[i] = (((char)(i % 10)) + '0');
		++i;
	}
	err = 0xff;
	i ^= i;
	while (i < 4)
	{
		if (memmove((tdat[i]).dst, (tdat[i]).src, (tdat[i]).size) != (tdat[i]).ret
			|| errno != (tdat[i]).err)
			return (err);
		--err;
		++i;
	}
	return (0);
}

int	ut_memmove_validity(int N)
{
	int				i;
	int				err;
	unsigned char	*src;
	unsigned char	*dst;

	i ^= i;
	err = 0xff;
	if ((src = (unsigned char *)malloc(N * sizeof(char))) == (unsigned char *)(NULL))
		return (err);
	--err;
	srand(N);
	while (i < N)
		src[i++] = (((unsigned char)(rand() % 256)) + '\0');
	dst = src + (N / 2);
	if (memmove((void *)(dst), (void *)(src), (size_t)(N / 2)) != (void *)(dst)
		|| errno)
	{
		free((void *)(src));
		return (err);
	}
	--err;
	if (memcmp((void *)(dst), (void *)(src), (size_t)(N / 2)))
	{
		free((void *)(src));
		return (err);
	}
	free((void *)(src));
	return (0);
}

int	ut_memmove_memchk(int N)
{
	return (ut_memmove_validity(N));
}

int	ut_memmove_timeout(int N)
{
	return (ut_memmove_validity(N));
}
