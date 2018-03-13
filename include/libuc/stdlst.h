/*
** stdlst.h
**
** Header file for stdlst subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2016/12/28 by Juillard Jean-Baptiste
** Updated: 2018/03/12 by Juillard Jean-Baptiste
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
slst_t		*slst_newelm(void);
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
void		slst_purge(slst_t **lst, void (*fdel)(void *, size_t));
void		slst_del(slst_t **lst, void (*fdel)(void *, size_t));
void		slst_deln(slst_t **lst, size_t n, void (*fdel)(void *, size_t));
void		slst_delp(slst_t **lst, slst_t *ptr, void (*fdel)(void *, size_t));
void		slst_delk(	slst_t **lst,
						const void *key,
						const size_t size,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t),
						void (*fdel)(void *, size_t));
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
slst_t		*slst_slctsrt(slst_t **lst,
							int (*fcmp)(const void *, const size_t,
										const void *, const size_t));		// Trie par selection (Selection sort)
slst_t		*slst_slctrsrt(slst_t **lst,
							int (*fcmp)(const void *, const size_t,
										const void *, const size_t));
slst_t		*slst_nsrtsrt(slst_t **lst,
							int (*fcmp)(const void *, const size_t,
										const void *, const size_t));		// Trie par insertion (Insertion sort)
slst_t		*slst_nsrtrsrt(slst_t **lst,
							int (*fcmp)(const void *, const size_t,
										const void *, const size_t));
slst_t		*slst_bbsrt(slst_t **lst,
						int (*fcmp)(const void *, const size_t,
									const void *, const size_t));			// Trie a bulle (Bubble sort)
slst_t		*slst_bbrsrt(slst_t **lst,
							int (*fcmp)(const void *, const size_t,
										const void *, const size_t));
// slst_t		*slst_cmbsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));	// Trie a peigne (Comb sort)
// slst_t		*slst_cmbrsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
slst_t		*slst_mrgsrt(slst_t **lst,
							int (*fcmp)(const void *, const size_t,
										const void *, const size_t));		// Trie fusion (Merge sort)
slst_t		*slst_mrgrsrt(slst_t **lst,
							int (*fcmp)(const void *, const size_t,
										const void *, const size_t));
slst_t		*slst_qcksrt(slst_t **lst,
							int (*fcmp)(const void *, const size_t,
										const void *, const size_t));		// Trie rapide (Quick sort)
slst_t		*slst_qckrsrt(slst_t **lst,
							int (*fcmp)(const void *, const size_t,
										const void *, const size_t));
// slst_t		*slst_intsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));	// Intro sort
// slst_t		*slst_intrsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
// slst_t		*slst_shsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));		// Trie de Shell (Shell sort)
// slst_t		*slst_shrsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
// slst_t		*slst_heapsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));	// Trie par tas (Heap sort)
// slst_t		*slst_heaprsrt(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
slst_t		*slst_random(slst_t **lst, unsigned int seed);					// Melange de Fisher-Yates (Fisher–Yates shuffle)
//slst_t	*slst_rot(slst_t **lst, size_t n);						// Rotation
//slst_t	*slst_rrot(slst_t **lst, size_t n);						// Rotation inverse
lifo_t		*slst2lifo(slst_t **lst);
// sslst_t	*slst2sslst(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
sclst_t		*slst2sclst(slst_t **lst);
fifo_t		*slst2fifo(slst_t **lst);
// scslst_t	*slst2scslst(slst_t **lst, int (*fcmp)(const void *, const size_t, const void *, const size_t));
mslst_t		*slst_map(slst_t **lst);


/*
** Non-ordered simply linked list mapping (mslst_t)
*/
void		mslst_purge(mslst_t **mlst);


/*
** LIFO structure (lifo_t)
*/
lifo_t		*lifo_push(lifo_t **stk, void *key, size_t size);
void		*lifo_pop(lifo_t **stk);
void		lifo_purge(lifo_t **stk, void (*fdel)(void *, size_t));
mlifo_t		*lifo_map(lifo_t **stk);


/*
** LIFO structure mapping (mlifo_t)
*/
mlifo_t		*mlifo_push(mlifo_t **mstk, void **kptr, size_t *sptr);
void		**mlifo_pop(mlifo_t **mstk);
void		mlifo_purge(mlifo_t **mstk);


/*
** Ordered simply linked list (sslst_t)
*/


/*
** Ordered simply linked list mapping (msslst_t)
*/


/*
** Non-ordered simply circular linked list (sclst_t)
*/
sclst_t		*sclst_newelm(void);
void		sclst_delelm(sclst_t *elm, void (*fdel)(void *, size_t));
int			sclst_isempty(sclst_t **lst);
size_t		sclst_len(sclst_t **lst);
sclst_t		*sclst_previous(sclst_t **lst, sclst_t *elm);
sclst_t		*sclst_next(sclst_t **lst, sclst_t *elm);
msclst_t	*sclst_head(sclst_t **lst, size_t n);
msclst_t	*sclst_tail(sclst_t **lst, size_t n);
sclst_t		*sclst_put(sclst_t **lst, void *key, size_t size);
sclst_t		*sclst_put_front(sclst_t **lst, void *key, size_t size);
sclst_t		*sclst_put_back(sclst_t **lst, void *key, size_t size);
sclst_t		*sclst_putn(sclst_t **lst, void *key, size_t size, size_t n);
void		*sclst_get(sclst_t **lst);
void		*sclst_get_front(sclst_t **lst);
void		*sclst_get_back(sclst_t **lst);
void		*sclst_getn(sclst_t **lst, size_t n);
void		sclst_purge(sclst_t **lst, void (*fdel)(void *, size_t));

msclst_t	*sclst_map(sclst_t **lst);

/*
** Non-ordered simply circular linked list mapping (msclst_t)
*/
void		msclst_purge(msclst_t **mlst);


/*
** Ordered simply circular linked list (scslst_t)
*/


/*
** Ordered simply circular linked list mapping (mscslst_t)
*/


/*
** FIFO structure (fifo_t)
*/
fifo_t		*fifo_push(fifo_t **que, void *key, size_t size);
void		*fifo_pop(fifo_t **que);
void		fifo_purge(fifo_t **que, void (*fdel)(void *, size_t));
mfifo_t		*fifo_map(fifo_t **que);


/*
** FIFO structure mapping (mfifo_t)
*/
mfifo_t		*mfifo_push(mfifo_t **mque, void **kptr, size_t *sptr);
void		**mfifo_pop(mfifo_t **mque);
void		mfifo_purge(mfifo_t **mque);


#endif
