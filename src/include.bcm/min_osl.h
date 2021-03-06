/*
 * HND Minimal OS Abstraction Layer.
 *
 * Copyright 2007, Broadcom Corporation
 * All Rights Reserved.
 * 
 * THIS SOFTWARE IS OFFERED "AS IS", AND BROADCOM GRANTS NO WARRANTIES OF ANY
 * KIND, EXPRESS OR IMPLIED, BY STATUTE, COMMUNICATION OR OTHERWISE. BROADCOM
 * SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A SPECIFIC PURPOSE OR NONINFRINGEMENT CONCERNING THIS SOFTWARE.
 *
 * $Id$
 */

#ifndef _min_osl_h_
#define _min_osl_h_

#include <typedefs.h>
#include <sbconfig.h>
#include <mipsinc.h>
#include <bcmstdlib.h>

/* Cache support */
extern void caches_on(void);
extern void blast_dcache(void);
extern void blast_icache(void);

/* assert & debugging */
#if defined(BCMDBG)
extern void assfail(char *exp, char *file, int line);
#define ASSERT(exp) \
	do { if (!(exp)) assfail(#exp, __FILE__, __LINE__); } while (0)
#else
#define	ASSERT(exp)		do {} while (0)
#endif

/* PCMCIA attribute space access macros */
#define	OSL_PCMCIA_READ_ATTR(osh, offset, buf, size) \
	ASSERT(0)
#define	OSL_PCMCIA_WRITE_ATTR(osh, offset, buf, size) \
	ASSERT(0)

/* PCI configuration space access macros */
#define	OSL_PCI_READ_CONFIG(loc, offset, size) \
	(offset == 8 ? 0 : 0xffffffff)
#define	OSL_PCI_WRITE_CONFIG(loc, offset, size, val) \
	do {} while (0)

/* PCI device bus # and slot # */
#define OSL_PCI_BUS(osh)	(0)
#define OSL_PCI_SLOT(osh)	(0)

/* register access macros */
#define wreg32(r, v)		(*(volatile uint32*)(r) = (uint32)(v))
#define rreg32(r)		(*(volatile uint32*)(r))
#define wreg16(r, v)		(*(volatile uint16*)(r) = (uint16)(v))
#define rreg16(r)		(*(volatile uint16*)(r))
#define wreg8(r, v)		(*(volatile uint8*)(r) = (uint8)(v))
#define rreg8(r)		(*(volatile uint8*)(r))
#define R_REG(osh, r) ({ \
	__typeof(*(r)) __osl_v; \
	switch (sizeof(*(r))) { \
	case sizeof(uint8):	__osl_v = rreg8((r)); break; \
	case sizeof(uint16):	__osl_v = rreg16((r)); break; \
	case sizeof(uint32):	__osl_v = rreg32((r)); break; \
	} \
	__osl_v; \
})
#define W_REG(osh, r, v) do { \
	switch (sizeof(*(r))) { \
	case sizeof(uint8):	wreg8((r), (v)); break; \
	case sizeof(uint16):	wreg16((r), (v)); break; \
	case sizeof(uint32):	wreg32((r), (v)); break; \
	} \
} while (0)
#define	AND_REG(osh, r, v)		W_REG(osh, (r), R_REG(osh, r) & (v))
#define	OR_REG(osh, r, v)		W_REG(osh, (r), R_REG(osh, r) | (v))

/* general purpose memory allocation */
#define	MALLOC(osh, size)	malloc(size)
#define	MFREE(osh, addr, size)	free(addr)
#define	MALLOCED(osh)		0
#define	MALLOC_FAILED(osh)	0
#define	MALLOC_DUMP(osh, b)
extern int free(void *ptr);
extern void *malloc(uint size);

/* uncached virtual address */
#define	OSL_UNCACHED(va)	((void*)KSEG1ADDR((ulong)(va)))

/* host/bus architecture-specific address byte swap */
#define BUS_SWAP32(v)		(v)

/* microsecond delay */
#define	OSL_DELAY(usec)		udelay(usec)
extern void udelay(uint32 usec);

/* map/unmap physical to virtual I/O */
#define	REG_MAP(pa, size)	((void*)KSEG1ADDR((ulong)(pa)))
#define	REG_UNMAP(va)		do {} while (0)

/* dereference an address that may cause a bus exception */
#define	BUSPROBE(val, addr)	(uint32 *)(addr) = (val)

/* Misc stubs */
#define osl_attach(pdev)	((osl_t*)pdev)
#define osl_detach(osh)

#define PKTFREESETCB(osh, _tx_fn, _tx_ctx)

extern void *osl_init(void);
#define OSL_ERROR(bcmerror)	osl_error(bcmerror)
extern int osl_error(int);

/* the largest reasonable packet buffer driver uses for ethernet MTU in bytes */
#define	PKTBUFSZ			(MAXPKTBUFSZ - LBUFSZ)

/* packet primitives */
#define PKTGET(osh, len, send)		((void *)NULL)
#define PKTFREE(osh, p, send)
#define	PKTDATA(osh, lb)		((void *)NULL)
#define	PKTLEN(osh, lb)			0
#define	PKTHEADROOM(osh, lb)		0
#define	PKTTAILROOM(osh, lb)		0
#define	PKTNEXT(osh, lb)		((void *)NULL)
#define	PKTSETNEXT(osh, lb, x)
#define	PKTSETLEN(osh, lb, len)
#define	PKTPUSH(osh, lb, bytes)
#define	PKTPULL(osh, lb, bytes)
#define PKTDUP(osh, p)
#define	PKTTAG(lb)			((void *)NULL)
#define	PKTLINK(lb)			((void *)NULL)
#define	PKTSETLINK(lb, x)
#define	PKTPRIO(lb)			0
#define	PKTSETPRIO(lb, x)
#define PKTSHARED(lb)			1
#define PKTALLOCED(osh)			0
#define PKTLIST_DUMP(osh, buf)
#define PKTFRMNATIVE(osh, lb)		((void *)NULL)
#define PKTTONATIVE(osh, p)		((struct lbuf *)NULL)

#endif	/* _min_osl_h_ */
