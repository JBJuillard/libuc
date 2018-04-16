/*
** bitsfield.h
**
** Header file for bitsfield subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/31 by Juillard Jean-Baptiste
** Updated: 2018/04/14 by Juillard Jean-Baptiste
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

#ifndef BITSFIELD_H
# define BITSFIELD_H				1

# include <libuc/stdint.h>

/*
** type setbits(type bitfield, type mask);
**
** All bits at 1 in mask are set
*/
# define setbits(b,m)				(b | m)

/*
** type clearbits(type bitfield, type mask);
**
** All bits at 1 in mask are clear
*/
# define clearbits(b,m)				(b & ~(m))

uint8_t		bitswap_8(uint8_t byte);
uint16_t	bitswap_16(uint16_t word);
uint32_t	bitswap_32(uint32_t dword);
uint64_t	bitswap_64(uint64_t qword);

uint8_t		bitsrot_8(uint8_t byte, int pos);
uint16_t	bitsrot_16(uint16_t word, int pos);
uint32_t	bitsrot_32(uint32_t dword, int pos);
uint64_t	bitsrot_64(uint64_t qword, int pos);

#endif
