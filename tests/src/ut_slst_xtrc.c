/*
** Test for slst_xtrc function of Undefined-C library
**
** Created: 17/01/2017 10:00:00 by Juillard Jean-Baptiste
** Updated: 17/01/2017 10:00:00 by Juillard Jean-Baptiste
*/

#include <stdlib.h>
#include <stdint.h>
#include "stdlst.h"
#include "test.h"

int	ut_slst_xtrc_interface(int N)
{
	slst_t	*ptr;
	slst_t	*tmp;
	int	r;

	N = N;
	ptr = (slst_t *)(NULL);
	r = 0;
	errno = 0;
	if (slst_xtrc((slst_t **)(NULL)) || errno != EINVAL)
		return (0xFF);
	errno = 0;
	if (slst_xtrc(&ptr) || errno)
		return (0xFE);
	if ((ptr = (slst_t *)malloc(sizeof(slst_t))) == (slst_t *)(NULL))
		return (errno);
	ptr->key = (void *)(0xFFFFFFFF);
	ptr->size = SIZE_MAX;
	ptr->next = (slst_t *)(0xFFFFFFFF);
	if (!(tmp = slst_xtrc(&ptr)) || errno)
		return (0xFD);
	free((void *)(tmp));
	return (r);
}

int	ut_slst_xtrc_memchk(int N)
{
	slst_t	*lst;
	slst_t	*ptr;

	if ((lst = _gen_slst(0, N, 1)) == (slst_t *)(NULL))
		return (errno);
	while (lst && N-- >= 0)
	{
		if (!(ptr = slst_xtrc(&lst)) || errno)
		{
			slst_purge(&lst, &_ofree);
			return (errno);
		}
		free(ptr->key);
		free((void *)(ptr));
	}
	return (0);
}

int	ut_slst_xtrc_timeout(int N)
{
	return (ut_slst_xtrc_memchk(N));
}
