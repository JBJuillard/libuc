/*
** Header file for stdlst subset of Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
** Updated: 02/24/2017 by Juillard Jean-Baptiste
**
** This file is a part of free software; you can redistribute it and/or
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

#ifndef STDLST_H
# define	STDLST_H				1


# include	<stddef.h>

/*
** For Windows and other non-POSIX system
*/
#include	<errno.h>
#ifndef		EOVERFLOW
# define	EOVERFLOW				84
#endif

/*
** Simply linked list
**
**	key		Pointer on key value
**	size	Size of key value
**	next	Pointer on the next element in list
*/
typedef struct		slst_s
{
	void			*key;
	size_t			size;
	struct slst_s	*next;
}					slst_t;

/*
** Simply linked list mapping
**
**	kptr	Pointer on pointer on key value in the original list
**	sptr	Pointer on size of key value in the original list
**	next	Pointer on the next element in the mapped list
*/
typedef struct		mslst_s
{
	void			**kptr;
	size_t			*sptr;
	struct mslst_s	*next;
}					mslst_t;

/*
** Ordered simply linked list and there mapping
*/
typedef slst_t		sslst_t;
typedef mslst_t		msslst_t;

/*
** LIFO structure and there mapping
*/
typedef slst_t		lifo_t;
typedef mslst_t		mlifo_t;

/*
** Non-ordered simply circular linked list and there mapping
*/
typedef slst_t		sclst_t;
typedef mslst_t		msclst_t;

/*
** Ordered simply circular linked list and there mapping
*/
typedef sclst_t		scslst_t;
typedef msclst_t	mscslst_t;

/*
** FIFO structure and there mapping
*/
typedef sclst_t		fifo_t;
typedef msclst_t	mfifo_t;


/*
** Non-ordered simply Linked List function (slst_t)
*/
slst_t		*slst_new(void);
void		slst_delelm(slst_t *elm, void (*fdel)(void *, size_t));
int			slst_isempty(slst_t **lst);
size_t		slst_len(slst_t **lst);
slst_t		*slst_previous(slst_t **lst, slst_t *elm);
slst_t		*slst_next(slst_t **lst, slst_t *elm);
mslst_t		*slst_head(slst_t **lst, size_t n);
mslst_t		*slst_tail(slst_t **lst, size_t n);
slst_t		*slst_put(slst_t **lst, void *key, size_t size);
slst_t		*slst_putn(slst_t **lst, void *key, size_t size, size_t n);
void		*slst_get(slst_t **lst);
void		*slst_getn(slst_t **lst, size_t n);
void		slst_del(slst_t **lst, void (*fdel)(void *, size_t));
void		slst_deln(slst_t **lst, size_t n, void (*fdel)(void *, size_t));
void		slst_delp(slst_t **lst, slst_t *ptr, void (*fdel)(void *, size_t));
void		slst_delk(	slst_t **lst,
						const void *key,
						const size_t size,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t),
						void (*fdel)(void *, size_t));
void		slst_purge(slst_t **lst, void (*fdel)(void *, size_t));
slst_t		*slst_nsrt(slst_t **lst, slst_t *elm);
slst_t		*slst_nsrtn(slst_t **lst, slst_t *elm, size_t n);
slst_t		*slst_nsrtp(slst_t **lst, slst_t *elm, slst_t *ptr);
slst_t		*slst_nsrtk(slst_t **lst, slst_t *elm,
						const void *key,
						const size_t size,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t));
slst_t		*slst_xtrc(slst_t **lst);
slst_t		*slst_xtrcn(slst_t **lst, size_t n);
slst_t		*slst_xtrcp(slst_t **lst, slst_t *ptr);
slst_t		*slst_xtrck(slst_t **lst,
						const void *key,
						const size_t size,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t));
slst_t		*slst_rch(slst_t **lst,
						const void *key,
						const size_t size,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t));
slst_t		*slst_rrch(slst_t **lst,
						const void *key,
						const size_t size,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t));
size_t		slst_xrch(slst_t **lst,
						const void *key,
						const size_t size,
						mslst_t **match,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t));
size_t		slst_rxrch(slst_t **lst,
						const void *key,
						const size_t size,
						mslst_t **match,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t));
int			slst_cmp(slst_t **lst1,
						slst_t **ptr1,
						slst_t **lst2,
						slst_t **ptr2,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t));
int			slst_rcmp(slst_t **lst1,
						slst_t **ptr1,
						slst_t **lst2,
						slst_t **ptr2,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t));
size_t		slst_diff(slst_t **lst1,
						mslst_t **diff1,
						slst_t **lst2,
						mslst_t **diff2,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t));
size_t		slst_rdiff(slst_t **lst1,
						mslst_t **diff1,
						slst_t **lst2,
						mslst_t **diff2,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t));
slst_t		*slst_cpy(slst_t **lst, void *(*fcpy)(const void *, size_t));
slst_t		*slst_rcpy(slst_t **lst, void *(*fcpy)(const void *, size_t));
slst_t		*slst_rev(slst_t **lst);
slst_t		*slst_cat(slst_t **lst1, slst_t **lst2);
slst_t		*slst_cut(slst_t **lst);
slst_t		*slst_cutn(slst_t **lst, size_t n);
slst_t		*slst_cutp(slst_t **lst, slst_t *ptr);
slst_t		*slst_cutk(slst_t **lst,
						const void *key,
						const size_t size,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t));

int			slst_apply(slst_t **lst, int (*func)(void **, size_t *));
size_t		slst_keyslen(slst_t **lst);
void		*slst_keysdup(slst_t **lst, size_t *size);

// slst_t		*slst_stupidsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
// slst_t		*slst_stupidrsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
slst_t		*slst_bubblesrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
slst_t		*slst_bubblersrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
// slst_t		*slst_shellsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
// slst_t		*slst_shellrsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
// slst_t		*slst_introsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
// slst_t		*slst_introrsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
// slst_t		*slst_mergesrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
// slst_t		*slst_mergersrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
// slst_t		*slst_heapsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
// slst_t		*slst_heaprsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));

lifo_t		*slst2lifo(slst_t **lst);
// sslst_t	*slst2sslst(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
sclst_t		*slst2sclst(slst_t **lst);
fifo_t		*slst2fifo(slst_t **lst);
// scslst_t	*slst2scslst(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
mslst_t		*slst_map(slst_t **lst);


/*
** Non-ordered simply linked list mapping (mslst_t)
*/


/*
** Ordered simply linked list (sslst_t)
*/


/*
** Ordered simply linked list mapping (msslst_t)
*/


/*
** LIFO structure (lifo_t)
*/
lifo_t		*lifo_new(void);
lifo_t		*lifo_push(lifo_t **stk, void *key, size_t size);
void		*lifo_pop(lifo_t **stk);
void		lifo_purge(lifo_t **stk, void (*f)(void *, size_t));
//mlifo_t	*lifo_map(lifo_t **stk);


/*
** LIFO structure mapping (mlifo_t)
*/
// mlifo_t		*mlifo_new(void);
// mlifo_t		*mlifo_push(mlifo_t **mstk, void **kptr, size_t *sptr);
// void		*mlifo_pop(mlifo_t **mstk);
// void		mlifo_purge(mlifo_t **mstk);


/*
** Non-ordered simply circular linked list (sclst_t)
*/


/*
** Non-ordered simply circular linked list mapping (msclst_t)
*/


/*
** Ordered simply circular linked list (scslst_t)
*/


/*
** Ordered simply circular linked list mapping (mscslst_t)
*/


/*
** FIFO structure (fifo_t)
*/
//fifo_t	*fifo_new(void);
//fifo_t	*fifo_push(fifo_t **queue, void *key, size_t size);
//void		*fifo_pop(fifo_t **queue);
//void		fifo_purge(fifo_t **queue, void (*f)(void *, size_t));
//mfifo_t	*fifo_map(fifo_t **queue);


/*
** FIFO structure mapping (mfifo_t)
*/
//mfifo_t	*mfifo_new(void);
//mfifo_t	*mfifo_push(mfifo_t **mqueue, void **kptr, size_t *sptr);
//void		*mfifo_pop(mfifo_t **mqueue);
//void		mfifo_purge(mfifo_t **mqueue);


#endif
