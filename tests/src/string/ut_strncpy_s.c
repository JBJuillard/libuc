/*
** ut_strncpy_s.c
**
** Unit tests for strncpy_s function of Undefined-C library
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

# define __STDC_WANT_LIB_EXT1__ 		1

#include <libuc/stddef.h>
#include <libuc/string.h>
#include <libuc/errno.h>
#include <stdlib.h>

typedef struct			test_s
{
	const void			*src;
	rsize_t				smax;
	void				*dst;
	rsize_t				size;
	errno_t				ret;
	int					err;
}						test_t;

int	ut_strncpy_s_interface(int N)
{
	int				err;
	int				i;
	unsigned char	src[128];
	unsigned char	dst[128];
	test_t			tdat[6] = {	{(const void *)(NULL), 128, (void *)(dst), 128, (errno_t)(EINVAL), EINVAL},
								{(const void *)(src), 0, (void *)(dst), 128, (errno_t)(EINVAL), EINVAL},
								{(const void *)(src), 127, (void *)(dst), 128, (errno_t)(EINVAL), EINVAL},
								{(const void *)(src), 128, NULL, 128, (errno_t)(EINVAL), EINVAL},
								{(const void *)(src), 128, (void *)(dst), 0, (errno_t)(EINVAL), EINVAL},
								{(const void *)(src), 128, (void *)(dst), 127, (errno_t)(0), 0} };

	i ^= i;
	N = N;
	while (i < 127)
	{
		src[i] = (((char)(i % 10)) + '0');
		++i;
	}
	src[127] = '\0';
	err = 0xff;
	i ^= i;
	while (i < 6)
	{
		memset((void *)(dst), 0, 128);
		if (strncpy_s((tdat[i]).dst, (tdat[i]).smax, (tdat[i]).src, (tdat[i]).size) != (tdat[i]).ret
			|| errno != (tdat[i]).err)
			return (err);
		--err;
		++i;
	}
	return (0);
}

int	ut_strncpy_s_validity(int N)
{
	size_t			i;
	int				err;
	unsigned char	*src;
	unsigned char	*dst;

	i ^= i;
	err = 0xff;
	if ((src = (unsigned char *)malloc((N + 1) * sizeof(char))) == (unsigned char *)(NULL)
		|| (dst = (unsigned char *)malloc((N + 1) * sizeof(char))) == (unsigned char *)(NULL))
	{
		if (src)
			free((void *)(src));
		return (err);
	}
	--err;
	srand(N);
	while (i < (size_t)(N))
		src[i++] = (((unsigned char)(rand() % 26)) + 'a');
	src[N] = '\0';
	memset((void *)(dst), 0, N);
	if (strncpy_s((void *)(dst), (rsize_t)(N + 1), (void *)(src), (rsize_t)(N)) != (errno_t)(0)
		|| errno)
	{
		free((void *)(src));
		free((void *)(dst));
		return (err);
	}
	--err;
	if (memcmp((void *)(dst), (void *)(src), (size_t)(N)))
	{
		free((void *)(src));
		free((void *)(dst));
		return (err);
	}
	free((void *)(src));
	free((void *)(dst));
	return (0);
}

int	ut_strncpy_s_memchk(int N)
{
	return (ut_strncpy_s_validity(N));
}

int	ut_strncpy_s_timeout(int N)
{
	return (ut_strncpy_s_validity(N));
}
