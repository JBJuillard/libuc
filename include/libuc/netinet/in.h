/*
** in.h
**
** Header file for in subset of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/04 by Juillard Jean-Baptiste
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

#ifndef NETINET_IN_H
# define NETINET_IN_H					1

# include <libuc/inttypes.h>
# include <sys/socket.h>

typedef uint16_t						in_port_t;
typedef uint32_t						in_addr_t;

struct									in_addr
{
	in_addr_t							s_addr;
};

struct									sockaddr_in
{
	sa_family_t							sin_family;		/* AF_INET */
	in_port_t							sin_port;		/* Port number */
	struct in_addr						sin_addr;		/* IP address */
};

struct									in6_addr
{
	uint8_t								s6_addr[16];
};

typedef struct
{
	sa_family_t							sin6_family;	/* AF_INET6 */
	in_port_t							sin6_port;		/* Port number */
	uint32_t							sin6_flowinfo;	/* IPv6 traffic class and flow information */
	struct in6_addr						sin6_addr;		/* IPv6 address */
	uint32_t							sin6_scope_id;	/* Set of interfaces for a scope */
}										sockaddr_in6;

/*
** Define wildcard ipv6 address
**
** ::
*/
extern const struct in6_addr			in6addr_any;
# define IN6ADDR_ANY_INIT				{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}

/*
** Define loopback ipv6 address
**
** ::1
*/
extern const struct in6_addr			in6addr_loopback;
# define IN6ADDR_LOOPBACK_INIT			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}

typedef struct
{
	struct in6_addr						ipv6mr_multiaddr;	/* IPv6 multicast address */
	unsigned int						ipv6mr_interface;	/* Interface index */
}										ipv6_mreq;

enum
{
	IPPROTO_IP = 0,			/* Dummy protocol for TCP */
	IPPROTO_ICMP = 1,		/* Internet Control Message Protocol */
	IPPROTO_IGMP = 2,		/* Internet Group Management Protocol */
	IPPROTO_IPIP = 4,		/* IPIP tunnels (older KA9Q tunnels use 94) */
	IPPROTO_TCP = 6,		/* Transmission Control Protocol */
	IPPROTO_EGP = 8,		/* Exterior Gateway Protocol */
	IPPROTO_PUP = 12,		/* PUP protocol */
	IPPROTO_UDP = 17,		/* User Datagram Protocol */
	IPPROTO_IDP = 22,		/* XNS IDP protocol */
	IPPROTO_TP = 29,		/* SO Transport Protocol Class 4 */
	IPPROTO_DCCP = 33,		/* Datagram Congestion Control Protocol */
	IPPROTO_IPV6 = 41,		/* IPv6 header */
	IPPROTO_RSVP = 46,		/* Reservation Protocol */
	IPPROTO_GRE = 47,		/* General Routing Encapsulation */
	IPPROTO_ESP = 50,		/* encapsulating security payload */
	IPPROTO_AH = 51,		/* authentication header */
	IPPROTO_MTP = 92,		/* Multicast Transport Protocol */
	IPPROTO_BEETPH = 94,	/* IP option pseudo header for BEET */
	IPPROTO_ENCAP = 98,		/* Encapsulation Header */
	IPPROTO_PIM = 103,		/* Protocol Independent Multicast */
	IPPROTO_COMP = 108,		/* Compression Header Protocol */
	IPPROTO_SCTP = 132,		/* Stream Control Transmission Protocol */
	IPPROTO_UDPLITE = 136,	/* UDP-Lite protocol */
	IPPROTO_MPLS = 137,		/* MPLS in IP */
	IPPROTO_RAW = 255,		/* Raw IP packets */
    IPPROTO_MAX
};

# define IPPROTO_IP						IPPROTO_IP
# define IPPROTO_ICMP					IPPROTO_ICMP
# define IPPROTO_IGMP					IPPROTO_IGMP
# define IPPROTO_IPIP					IPPROTO_IPIP
# define IPPROTO_TCP					IPPROTO_TCP
# define IPPROTO_EGP					IPPROTO_EGP
# define IPPROTO_PUP					IPPROTO_PUP
# define IPPROTO_UDP					IPPROTO_UDP
# define IPPROTO_IDP					IPPROTO_IDP
# define IPPROTO_TP						IPPROTO_TP
# define IPPROTO_DCCP					IPPROTO_DCCP
# define IPPROTO_IPV6					IPPROTO_IPV6
# define IPPROTO_RSVP					IPPROTO_RSVP
# define IPPROTO_GRE					IPPROTO_GRE
# define IPPROTO_ESP					IPPROTO_ESP
# define IPPROTO_AH						IPPROTO_AH
# define IPPROTO_MTP					IPPROTO_MTP
# define IPPROTO_BEETPH					IPPROTO_BEETPH
# define IPPROTO_ENCAP					IPPROTO_ENCAP
# define IPPROTO_PIM					IPPROTO_PIM
# define IPPROTO_COMP					IPPROTO_COMP
# define IPPROTO_SCTP					IPPROTO_SCTP
# define IPPROTO_UDPLITE				IPPROTO_UDPLITE
# define IPPROTO_MPLS					IPPROTO_MPLS
# define IPPROTO_RAW					IPPROTO_RAW

/*
** IPv4 wildcard address
**
** 0.0.0.0
*/
# define INADDR_ANY						((in_addr_t)(0x00000000))
/*
** IPv4 broadcast address
**
** 255.255.255.255
*/
# define INADDR_BROADCAST				((in_addr_t)(0xffffffff))
/*
** Address indicate an error return
**
** 255.255.255.255
*/
# define INADDR_NONE					((in_addr_t)(0xffffffff))
/*
** Maximum length of the string form for IPv4 address
*/
# define INET_ADDRSTRLEN				16
/*
** Network number for local host loopback
*/
//#define IN_LOOPBACKNET					0X7f
/*
** Address to loopback in software to local host
**
** 127.0.0.1
*/
/*
#ifndef INADDR_LOOPBACK
# define INADDR_LOOPBACK    			((in_addr_t) 0x7f000001)
#endif
*/
/*
** Defines for Multicast INADDR
*/
/*
// 224.0.0.0
#define INADDR_UNSPEC_GROUP				((in_addr_t) 0xe0000000)
// 224.0.0.1
#define INADDR_ALLHOSTS_GROUP			((in_addr_t) 0xe0000001)
// 224.0.0.2
#define INADDR_ALLRTRS_GROUP			((in_addr_t) 0xe0000002)
// 224.0.0.255
#define INADDR_MAX_LOCAL_GROUP			((in_addr_t) 0xe00000ff)
*/

/*
# define IN_CLASSA(a)					((((in_addr_t)(a)) & 0x80000000) == 0)
# define IN_CLASSA_NET					0xff000000
# define IN_CLASSA_NSHIFT				24
# define IN_CLASSA_HOST					(0xffffffff & ~IN_CLASSA_NET)
# define IN_CLASSA_MAX					128

# define IN_CLASSB(a)					((((in_addr_t)(a)) & 0xc0000000) == 0x80000000)
# define IN_CLASSB_NET					0xffff0000
# define IN_CLASSB_NSHIFT				16
# define IN_CLASSB_HOST					(0xffffffff & ~IN_CLASSB_NET)
# define IN_CLASSB_MAX					65536

# define IN_CLASSC(a)					((((in_addr_t)(a)) & 0xe0000000) == 0xc0000000)
# define IN_CLASSC_NET					0xffffff00
# define IN_CLASSC_NSHIFT				8
# define IN_CLASSC_HOST					(0xffffffff & ~IN_CLASSC_NET)

# define IN_CLASSD(a)					((((in_addr_t)(a)) & 0xf0000000) == 0xe0000000)
# define IN_MULTICAST(a)				IN_CLASSD(a)

# define IN_EXPERIMENTAL(a)				((((in_addr_t)(a)) & 0xe0000000) == 0xc0000000)
# define IN_BADCLASS(a)					((((in_addr_t)(a)) & 0xf0000000) == 0xf0000000)
*/

/*
** Length of the string form for IPv6
*/
# define INET6_ADDRSTRLEN				46
/*
** Join a multicast group
**
** define in bits/in.h
*/
//# define IPV6_JOIN_GROUP
/*
** Quit a multicast group
**
** define in bits/in.h
*/
//# define IPV6_LEAVE_GROUP
/*
** Multicast hop limit
**
** define in bits/in.h
*/
//# define IPV6_MULTICAST_HOPS
/*
** Interface to use for outgoing multicast packets
**
** define in bits/in.h
*/
//# define IPV6_MULTICAST_IF
/*
** Multicast packets are delivered back to the local application
**
** define in bits/in.h
*/
//# define IPV6_MULTICAST_LOOP
/*
** Unicast hop limit
**
** define in bits/in.h
*/
//# define IPV6_UNICAST_HOPS
/*
** Restrict AF_INET6 socket to IPv6 communications only
**
** define in bits/in.h
*/
//# define IPV6_V6ONLY

/*
** Unspecified address
*/
# define IN6_IS_ADDR_UNSPECIFIED(a)		({	const struct in6_addr *_a = (const struct in6_addr *)(a);	\
											_a.s6_addr[0] == 0 && _a.s6_addr[1] == 0 &&					\
											_a.s6_addr[2] == 0 && _a.s6_addr[3] == 0 &&					\
											_a.s6_addr[4] == 0 && _a.s6_addr[5] == 0 &&					\
											_a.s6_addr[6] == 0 && _a.s6_addr[7] == 0 &&					\
											_a.s6_addr[8] == 0 && _a.s6_addr[9] == 0 &&					\
											_a.s6_addr[10] == 0 && _a.s6_addr[11] == 0 &&				\
											_a.s6_addr[12] == 0 && _a.s6_addr[13] == 0 &&				\
											_a.s6_addr[14] == 0 && _a.s6_addr[15] == 0 ;				\
										})
/*
** Loopback address
*/
# define IN6_IS_ADDR_LOOPBACK(a)		({	const struct in6_addr *_a = (const struct in6_addr *)(a);	\
											_a.s6_addr[0] == 0 && _a.s6_addr[1] == 0 &&					\
											_a.s6_addr[2] == 0 && _a.s6_addr[3] == 0 &&					\
											_a.s6_addr[4] == 0 && _a.s6_addr[5] == 0 &&					\
											_a.s6_addr[6] == 0 && _a.s6_addr[7] == 0 &&					\
											_a.s6_addr[8] == 0 && _a.s6_addr[9] == 0 &&					\
											_a.s6_addr[10] == 0 && _a.s6_addr[11] == 0 &&				\
											_a.s6_addr[12] == 0 && _a.s6_addr[13] == 0 &&				\
											_a.s6_addr[14] == 0 && _a.s6_addr[15] == 1 ;				\
										})
/*
** Multicast address
*/
# define IN6_IS_ADDR_MULTICAST(a)		({	const struct in6_addr *_a = (const struct in6_addr *)(a);	\
											_a.s6_addr[0] == 0xff ;										\
										})
/*
** Unicast link-local address
*/
# define IN6_IS_ADDR_LINKLOCAL(a)		({	const struct in6_addr *_a = (const struct in6_addr *)(a);			\
											(_a.s6_addr[0] & 0xff) == 0xfe && (_a.s6_addr[1] & 0xc0) == 0x80  ;	\
										})
/*
** Unicast site-local address
*/
# define IN6_IS_ADDR_SITELOCAL(a)		({	const struct in6_addr *_a = (const struct in6_addr *)(a);			\
											(_a.s6_addr[0] & 0xff) == 0xfe && (_a.s6_addr[1] & 0xc0) == 0xc0  ;	\
										})
/*
** IPv4 mapped address
*/
# define IN6_IS_ADDR_V4MAPPED(a)		({	const struct in6_addr *_a = (const struct in6_addr *)(a);	\
											_a.s6_addr[0] == 0 && _a.s6_addr[1] == 0  &&				\
											_a.s6_addr[2] == 0 && _a.s6_addr[3] == 0  &&				\
											_a.s6_addr[4] == 0 && _a.s6_addr[5] == 0  &&				\
											_a.s6_addr[6] == 0 && _a.s6_addr[7] == 0  &&				\
											_a.s6_addr[8] == 0 && _a.s6_addr[9] == 0  &&				\
											_a.s6_addr[10] == 0xff && _a.s6_addr[11] == 0xff ;			\
										})
/*
** IPv4-compatible address
*/
# define IN6_IS_ADDR_V4COMPAT(a)		({	const struct in6_addr *_a = (const struct in6_addr *)(a);	\
											_a.s6_addr[0] == 0 && _a.s6_addr[1] == 0  &&				\
											_a.s6_addr[2] == 0 && _a.s6_addr[3] == 0  &&				\
											_a.s6_addr[4] == 0 && _a.s6_addr[5] == 0  &&				\
											_a.s6_addr[6] == 0 && _a.s6_addr[7] == 0  &&				\
											_a.s6_addr[8] == 0 && _a.s6_addr[9] == 0  &&				\
											_a.s6_addr[10] == 0 && _a.s6_addr[11] == 0 &&				\
											(_a.s6_addr[12] || _a.s6_addr[13]							\
												|| _a.s6_addr[14] || _a.s6_addr[15] > 1);				\
										})
/*
** Multicast node-local address
*/
# define IN6_IS_ADDR_MC_NODELOCAL(a)	(IN6_IS_ADDR_MULTICAST(a)						\
										&& ((((const uint8_t *) (a))[1] & 0xf) == 0x1))
/*
** Multicast link-local address
*/
# define IN6_IS_ADDR_MC_LINKLOCAL(a)	(IN6_IS_ADDR_MULTICAST(a)						\
										&& ((((const uint8_t *) (a))[1] & 0xf) == 0x2))
/*
** Multicast site-local address
*/
# define IN6_IS_ADDR_MC_SITELOCAL(a)	(IN6_IS_ADDR_MULTICAST(a)						\
										&& ((((const uint8_t *) (a))[1] & 0xf) == 0x5))
/*
** Multicast organization-local address
*/
# define IN6_IS_ADDR_MC_ORGLOCAL(a)		(IN6_IS_ADDR_MULTICAST(a)						\
										&& ((((const uint8_t *) (a))[1] & 0xf) == 0x8))
/*
** Multicast global address
*/
# define IN6_IS_ADDR_MC_GLOBAL(a)		(IN6_IS_ADDR_MULTICAST(a)						\
										&& ((((const uint8_t *) (a))[1] & 0xf) == 0xe))


#endif
