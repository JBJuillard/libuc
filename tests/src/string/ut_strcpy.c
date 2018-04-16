/*
** ut_strcpy.c
**
** Unit tests for strcpy function of Undefined-C library
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
	void				*ret;
	int					err;
}						test_t;

int	ut_strcpy_interface(int N)
{
	int				err;
	int				i;
	unsigned char	src[128];
	unsigned char	dst[128];
	test_t			tdat[3] = {	{(const void *)(NULL), (void *)(dst), NULL, EINVAL},
								{(const void *)(src), NULL, NULL, EINVAL},
								{(const void *)(src), (void *)(dst), (void *)(dst), 0} };

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
	while (i < 3)
	{
		memset((void *)(dst), 0, 128);
		if (strcpy((tdat[i]).dst, (tdat[i]).src) != (tdat[i]).ret
			|| errno != (tdat[i]).err)
			return (err);
		--err;
		++i;
	}
	return (0);
}

int	ut_strcpy_validity(int N)
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
		src[i++] = (((unsigned char)(rand() % 26)) + 'a');
	src[(N - 1)] = '\0';
	memset((void *)(dst), 0, N);
	if (strcpy((void *)(dst), (void *)(src)) != (void *)(dst)
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

int	ut_strcpy_memchk(int N)
{
	return (ut_strcpy_validity(N));
}

int	ut_strcpy_timeout(int N)
{
	return (ut_strcpy_validity(N));
}
