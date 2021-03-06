/*
 * Copyright (C) 2012 Tobias Brunner
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

/**
 * @defgroup ipsec_types ipsec_types
 * @{ @ingroup ipsec
 */

#ifndef IPSEC_TYPES_H_
#define IPSEC_TYPES_H_

typedef enum ipsec_mode_t ipsec_mode_t;
typedef enum policy_dir_t policy_dir_t;
typedef enum policy_type_t policy_type_t;
typedef enum policy_priority_t policy_priority_t;
typedef enum ipcomp_transform_t ipcomp_transform_t;
typedef struct ipsec_sa_cfg_t ipsec_sa_cfg_t;
typedef struct lifetime_cfg_t lifetime_cfg_t;
typedef struct mark_t mark_t;

#include <library.h>

/**
 * Mode of an IPsec SA.
 */
enum ipsec_mode_t {
	/** not using any encapsulation */
	MODE_NONE = 0,
	/** transport mode, no inner address */
	MODE_TRANSPORT = 1,
	/** tunnel mode, inner and outer addresses */
	MODE_TUNNEL,
	/** BEET mode, tunnel mode but fixed, bound inner addresses */
	MODE_BEET,
	/** passthrough policy for traffic without an IPsec SA */
	MODE_PASS,
	/** drop policy discarding traffic */
	MODE_DROP
};

/**
 * enum names for ipsec_mode_t.
 */
extern enum_name_t *ipsec_mode_names;

/**
 * Direction of a policy. These are equal to those
 * defined in xfrm.h, but we want to stay implementation
 * neutral here.
 */
enum policy_dir_t {
	/** Policy for inbound traffic */
	POLICY_IN = 0,
	/** Policy for outbound traffic */
	POLICY_OUT = 1,
	/** Policy for forwarded traffic */
	POLICY_FWD = 2,
};

/**
 * enum names for policy_dir_t.
 */
extern enum_name_t *policy_dir_names;

/**
 * Type of a policy.
 */
enum policy_type_t {
	/** Normal IPsec policy */
	POLICY_IPSEC = 1,
	/** Passthrough policy (traffic is ignored by IPsec) */
	POLICY_PASS,
	/** Drop policy (traffic is discarded) */
	POLICY_DROP,
};

/**
 * High-level priority of a policy.
 */
enum policy_priority_t {
	/** Default priority */
	POLICY_PRIORITY_DEFAULT,
	/** Priority for trap policies */
	POLICY_PRIORITY_ROUTED,
	/** Priority for fallback drop policies */
	POLICY_PRIORITY_FALLBACK,
};

/**
 * IPComp transform IDs, as in RFC 4306
 */
enum ipcomp_transform_t {
	IPCOMP_NONE = 0,
	IPCOMP_OUI = 1,
	IPCOMP_DEFLATE = 2,
	IPCOMP_LZS = 3,
	IPCOMP_LZJH = 4,
};

/**
 * enum strings for ipcomp_transform_t.
 */
extern enum_name_t *ipcomp_transform_names;

/**
 * This struct contains details about IPsec SA(s) tied to a policy.
 */
struct ipsec_sa_cfg_t {
	/** mode of SA (tunnel, transport) */
	ipsec_mode_t mode;
	/** unique ID */
	u_int32_t reqid;
	/** details about ESP/AH */
	struct {
		/** TRUE if this protocol is used */
		bool use;
		/** SPI for ESP/AH */
		u_int32_t spi;
	} esp, ah;
	/** details about IPComp */
	struct {
		/** the IPComp transform used */
		u_int16_t transform;
		/** CPI for IPComp */
		u_int16_t cpi;
	} ipcomp;
};

/**
 * A lifetime_cfg_t defines the lifetime limits of an SA.
 *
 * Set any of these values to 0 to ignore.
 */
struct lifetime_cfg_t {
	struct {
		/** Limit before the SA gets invalid. */
		u_int64_t	life;
		/** Limit before the SA gets rekeyed. */
		u_int64_t	rekey;
		/** The range of a random value subtracted from rekey. */
		u_int64_t	jitter;
	} time, bytes, packets;
};

/**
 * A mark_t defines an optional mark in an IPsec SA.
 */
struct mark_t {
	/** Mark value */
	u_int32_t value;
	/** Mark mask */
	u_int32_t mask;
};

/**
 * Special mark value that uses the reqid of the CHILD_SA as mark
 */
#define MARK_REQID (0xFFFFFFFF)

#endif /** IPSEC_TYPES_H_ @}*/
