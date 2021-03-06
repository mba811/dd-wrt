/*
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; version 2 of the License
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 *
 *   based on Ralink SDK3.3
 *   Copyright (C) 2009-2013 John Crispin <blogic@openwrt.org>
 */

#ifndef FE_ETH_H
#define FE_ETH_H

#include <linux/mii.h>
#include <linux/interrupt.h>
#include <linux/netdevice.h>
#include <linux/dma-mapping.h>
#include <linux/phy.h>
#include <linux/inet_lro.h>


enum fe_reg {
	FE_REG_PDMA_GLO_CFG = 0,
	FE_REG_PDMA_RST_CFG,
	FE_REG_DLY_INT_CFG,
	FE_REG_TX_BASE_PTR0,
	FE_REG_TX_MAX_CNT0,
	FE_REG_TX_CTX_IDX0,
	FE_REG_RX_BASE_PTR0,
	FE_REG_RX_MAX_CNT0,
	FE_REG_RX_CALC_IDX0,
	FE_REG_FE_INT_ENABLE,
	FE_REG_FE_INT_STATUS,
	FE_REG_FE_DMA_VID_BASE,
	FE_REG_COUNT
};

#define NUM_DMA_DESC		0x100

#define FE_DELAY_EN_INT		0x80
#define FE_DELAY_MAX_INT	0x04
#define FE_DELAY_MAX_TOUT	0x04
#define FE_DELAY_CHAN		(((FE_DELAY_EN_INT | FE_DELAY_MAX_INT) << 8) | FE_DELAY_MAX_TOUT)
#define FE_DELAY_INIT		((FE_DELAY_CHAN << 16) | FE_DELAY_CHAN)
#define FE_PSE_FQFC_CFG_INIT	0x80504000

/* interrupt bits */
#define FE_CNT_PPE_AF		BIT(31)
#define FE_CNT_GDM_AF		BIT(29)
#define FE_PSE_P2_FC		BIT(26)
#define FE_PSE_BUF_DROP		BIT(24)
#define FE_GDM_OTHER_DROP	BIT(23)
#define FE_PSE_P1_FC		BIT(22)
#define FE_PSE_P0_FC		BIT(21)
#define FE_PSE_FQ_EMPTY		BIT(20)
#define FE_GE1_STA_CHG		BIT(18)
#define FE_TX_COHERENT		BIT(17)
#define FE_RX_COHERENT		BIT(16)
#define FE_TX_DONE_INT3		BIT(11)
#define FE_TX_DONE_INT2		BIT(10)
#define FE_TX_DONE_INT1		BIT(9)
#define FE_TX_DONE_INT0		BIT(8)
#define FE_RX_DONE_INT0		BIT(2)
#define FE_TX_DLY_INT		BIT(1)
#define FE_RX_DLY_INT		BIT(0)

#define RT5350_RX_DLY_INT	BIT(30)
#define RT5350_TX_DLY_INT	BIT(28)

/* registers */
#define FE_FE_OFFSET		0x0000
#define FE_GDMA_OFFSET		0x0020
#define FE_PSE_OFFSET		0x0040
#define FE_GDMA2_OFFSET		0x0060
#define FE_CDMA_OFFSET		0x0080
#define FE_DMA_VID0		0x00a8
#define FE_PDMA_OFFSET		0x0100
#define FE_PPE_OFFSET		0x0200
#define FE_CMTABLE_OFFSET	0x0400
#define FE_POLICYTABLE_OFFSET	0x1000

#define RT5350_PDMA_OFFSET	0x0800
#define RT5350_SDM_OFFSET	0x0c00

#define FE_MDIO_ACCESS		(FE_FE_OFFSET + 0x00)
#define FE_MDIO_CFG		(FE_FE_OFFSET + 0x04)
#define FE_FE_GLO_CFG		(FE_FE_OFFSET + 0x08)
#define FE_FE_RST_GL		(FE_FE_OFFSET + 0x0C)
#define FE_FE_INT_STATUS	(FE_FE_OFFSET + 0x10)
#define FE_FE_INT_ENABLE	(FE_FE_OFFSET + 0x14)
#define FE_MDIO_CFG2		(FE_FE_OFFSET + 0x18)
#define FE_FOC_TS_T		(FE_FE_OFFSET + 0x1C)

#define	FE_GDMA1_FWD_CFG	(FE_GDMA_OFFSET + 0x00)
#define FE_GDMA1_SCH_CFG	(FE_GDMA_OFFSET + 0x04)
#define FE_GDMA1_SHPR_CFG	(FE_GDMA_OFFSET + 0x08)
#define FE_GDMA1_MAC_ADRL	(FE_GDMA_OFFSET + 0x0C)
#define FE_GDMA1_MAC_ADRH	(FE_GDMA_OFFSET + 0x10)

#define	FE_GDMA2_FWD_CFG	(FE_GDMA2_OFFSET + 0x00)
#define FE_GDMA2_SCH_CFG	(FE_GDMA2_OFFSET + 0x04)
#define FE_GDMA2_SHPR_CFG	(FE_GDMA2_OFFSET + 0x08)
#define FE_GDMA2_MAC_ADRL	(FE_GDMA2_OFFSET + 0x0C)
#define FE_GDMA2_MAC_ADRH	(FE_GDMA2_OFFSET + 0x10)

#define FE_PSE_FQ_CFG		(FE_PSE_OFFSET + 0x00)
#define FE_CDMA_FC_CFG		(FE_PSE_OFFSET + 0x04)
#define FE_GDMA1_FC_CFG		(FE_PSE_OFFSET + 0x08)
#define FE_GDMA2_FC_CFG		(FE_PSE_OFFSET + 0x0C)

#define FE_CDMA_CSG_CFG		(FE_CDMA_OFFSET + 0x00)
#define FE_CDMA_SCH_CFG		(FE_CDMA_OFFSET + 0x04)

#define MT7620A_GDMA_OFFSET		0x0600
#define	MT7620A_GDMA1_FWD_CFG		(MT7620A_GDMA_OFFSET + 0x00)
#define MT7620A_FE_GDMA1_SCH_CFG	(MT7620A_GDMA_OFFSET + 0x04)
#define MT7620A_FE_GDMA1_SHPR_CFG	(MT7620A_GDMA_OFFSET + 0x08)
#define MT7620A_FE_GDMA1_MAC_ADRL	(MT7620A_GDMA_OFFSET + 0x0C)
#define MT7620A_FE_GDMA1_MAC_ADRH	(MT7620A_GDMA_OFFSET + 0x10)

#define RT5350_TX_BASE_PTR0	(RT5350_PDMA_OFFSET + 0x00)
#define RT5350_TX_MAX_CNT0	(RT5350_PDMA_OFFSET + 0x04)
#define RT5350_TX_CTX_IDX0	(RT5350_PDMA_OFFSET + 0x08)
#define RT5350_TX_DTX_IDX0	(RT5350_PDMA_OFFSET + 0x0C)
#define RT5350_TX_BASE_PTR1	(RT5350_PDMA_OFFSET + 0x10)
#define RT5350_TX_MAX_CNT1	(RT5350_PDMA_OFFSET + 0x14)
#define RT5350_TX_CTX_IDX1	(RT5350_PDMA_OFFSET + 0x18)
#define RT5350_TX_DTX_IDX1	(RT5350_PDMA_OFFSET + 0x1C)
#define RT5350_TX_BASE_PTR2	(RT5350_PDMA_OFFSET + 0x20)
#define RT5350_TX_MAX_CNT2	(RT5350_PDMA_OFFSET + 0x24)
#define RT5350_TX_CTX_IDX2	(RT5350_PDMA_OFFSET + 0x28)
#define RT5350_TX_DTX_IDX2	(RT5350_PDMA_OFFSET + 0x2C)
#define RT5350_TX_BASE_PTR3	(RT5350_PDMA_OFFSET + 0x30)
#define RT5350_TX_MAX_CNT3	(RT5350_PDMA_OFFSET + 0x34)
#define RT5350_TX_CTX_IDX3	(RT5350_PDMA_OFFSET + 0x38)
#define RT5350_TX_DTX_IDX3	(RT5350_PDMA_OFFSET + 0x3C)
#define RT5350_RX_BASE_PTR0	(RT5350_PDMA_OFFSET + 0x100)
#define RT5350_RX_MAX_CNT0	(RT5350_PDMA_OFFSET + 0x104)
#define RT5350_RX_CALC_IDX0	(RT5350_PDMA_OFFSET + 0x108)
#define RT5350_RX_DRX_IDX0	(RT5350_PDMA_OFFSET + 0x10C)
#define RT5350_RX_BASE_PTR1	(RT5350_PDMA_OFFSET + 0x110)
#define RT5350_RX_MAX_CNT1	(RT5350_PDMA_OFFSET + 0x114)
#define RT5350_RX_CALC_IDX1	(RT5350_PDMA_OFFSET + 0x118)
#define RT5350_RX_DRX_IDX1	(RT5350_PDMA_OFFSET + 0x11C)
#define RT5350_PDMA_GLO_CFG	(RT5350_PDMA_OFFSET + 0x204)
#define RT5350_PDMA_RST_CFG	(RT5350_PDMA_OFFSET + 0x208)
#define RT5350_DLY_INT_CFG	(RT5350_PDMA_OFFSET + 0x20c)
#define RT5350_FE_INT_STATUS	(RT5350_PDMA_OFFSET + 0x220)
#define RT5350_FE_INT_ENABLE	(RT5350_PDMA_OFFSET + 0x228)
#define RT5350_PDMA_SCH_CFG	(RT5350_PDMA_OFFSET + 0x280)

#define FE_PDMA_GLO_CFG		(FE_PDMA_OFFSET + 0x00)
#define FE_PDMA_RST_CFG		(FE_PDMA_OFFSET + 0x04)
#define FE_PDMA_SCH_CFG		(FE_PDMA_OFFSET + 0x08)
#define FE_DLY_INT_CFG		(FE_PDMA_OFFSET + 0x0C)
#define FE_TX_BASE_PTR0		(FE_PDMA_OFFSET + 0x10)
#define FE_TX_MAX_CNT0		(FE_PDMA_OFFSET + 0x14)
#define FE_TX_CTX_IDX0		(FE_PDMA_OFFSET + 0x18)
#define FE_TX_DTX_IDX0		(FE_PDMA_OFFSET + 0x1C)
#define FE_TX_BASE_PTR1		(FE_PDMA_OFFSET + 0x20)
#define FE_TX_MAX_CNT1		(FE_PDMA_OFFSET + 0x24)
#define FE_TX_CTX_IDX1		(FE_PDMA_OFFSET + 0x28)
#define FE_TX_DTX_IDX1		(FE_PDMA_OFFSET + 0x2C)
#define FE_RX_BASE_PTR0		(FE_PDMA_OFFSET + 0x30)
#define FE_RX_MAX_CNT0		(FE_PDMA_OFFSET + 0x34)
#define FE_RX_CALC_IDX0		(FE_PDMA_OFFSET + 0x38)
#define FE_RX_DRX_IDX0		(FE_PDMA_OFFSET + 0x3C)
#define FE_TX_BASE_PTR2		(FE_PDMA_OFFSET + 0x40)
#define FE_TX_MAX_CNT2		(FE_PDMA_OFFSET + 0x44)
#define FE_TX_CTX_IDX2		(FE_PDMA_OFFSET + 0x48)
#define FE_TX_DTX_IDX2		(FE_PDMA_OFFSET + 0x4C)
#define FE_TX_BASE_PTR3		(FE_PDMA_OFFSET + 0x50)
#define FE_TX_MAX_CNT3		(FE_PDMA_OFFSET + 0x54)
#define FE_TX_CTX_IDX3		(FE_PDMA_OFFSET + 0x58)
#define FE_TX_DTX_IDX3		(FE_PDMA_OFFSET + 0x5C)
#define FE_RX_BASE_PTR1		(FE_PDMA_OFFSET + 0x60)
#define FE_RX_MAX_CNT1		(FE_PDMA_OFFSET + 0x64)
#define FE_RX_CALC_IDX1		(FE_PDMA_OFFSET + 0x68)
#define FE_RX_DRX_IDX1		(FE_PDMA_OFFSET + 0x6C)

#define RT5350_SDM_CFG		(RT5350_SDM_OFFSET + 0x00)  //Switch DMA configuration
#define RT5350_SDM_RRING	(RT5350_SDM_OFFSET + 0x04)  //Switch DMA Rx Ring
#define RT5350_SDM_TRING	(RT5350_SDM_OFFSET + 0x08)  //Switch DMA Tx Ring
#define RT5350_SDM_MAC_ADRL	(RT5350_SDM_OFFSET + 0x0C)  //Switch MAC address LSB
#define RT5350_SDM_MAC_ADRH	(RT5350_SDM_OFFSET + 0x10)  //Switch MAC Address MSB
#define RT5350_SDM_TPCNT	(RT5350_SDM_OFFSET + 0x100) //Switch DMA Tx packet count
#define RT5350_SDM_TBCNT	(RT5350_SDM_OFFSET + 0x104) //Switch DMA Tx byte count
#define RT5350_SDM_RPCNT	(RT5350_SDM_OFFSET + 0x108) //Switch DMA rx packet count
#define RT5350_SDM_RBCNT	(RT5350_SDM_OFFSET + 0x10C) //Switch DMA rx byte count
#define RT5350_SDM_CS_ERR	(RT5350_SDM_OFFSET + 0x110) //Switch DMA rx checksum error count

#define RT5350_SDM_ICS_EN	BIT(16)
#define RT5350_SDM_TCS_EN	BIT(17)
#define RT5350_SDM_UCS_EN	BIT(18)


/* MDIO_CFG register bits */
#define FE_MDIO_CFG_AUTO_POLL_EN	BIT(29)
#define FE_MDIO_CFG_GP1_BP_EN		BIT(16)
#define FE_MDIO_CFG_GP1_FRC_EN		BIT(15)
#define FE_MDIO_CFG_GP1_SPEED_10	(0 << 13)
#define FE_MDIO_CFG_GP1_SPEED_100	(1 << 13)
#define FE_MDIO_CFG_GP1_SPEED_1000	(2 << 13)
#define FE_MDIO_CFG_GP1_DUPLEX		BIT(12)
#define FE_MDIO_CFG_GP1_FC_TX		BIT(11)
#define FE_MDIO_CFG_GP1_FC_RX		BIT(10)
#define FE_MDIO_CFG_GP1_LNK_DWN		BIT(9)
#define FE_MDIO_CFG_GP1_AN_FAIL		BIT(8)
#define FE_MDIO_CFG_MDC_CLK_DIV_1	(0 << 6)
#define FE_MDIO_CFG_MDC_CLK_DIV_2	(1 << 6)
#define FE_MDIO_CFG_MDC_CLK_DIV_4	(2 << 6)
#define FE_MDIO_CFG_MDC_CLK_DIV_8	(3 << 6)
#define FE_MDIO_CFG_TURBO_MII_FREQ	BIT(5)
#define FE_MDIO_CFG_TURBO_MII_MODE	BIT(4)
#define FE_MDIO_CFG_RX_CLK_SKEW_0	(0 << 2)
#define FE_MDIO_CFG_RX_CLK_SKEW_200	(1 << 2)
#define FE_MDIO_CFG_RX_CLK_SKEW_400	(2 << 2)
#define FE_MDIO_CFG_RX_CLK_SKEW_INV	(3 << 2)
#define FE_MDIO_CFG_TX_CLK_SKEW_0	0
#define FE_MDIO_CFG_TX_CLK_SKEW_200	1
#define FE_MDIO_CFG_TX_CLK_SKEW_400	2
#define FE_MDIO_CFG_TX_CLK_SKEW_INV	3

/* uni-cast port */
#define FE_GDM1_ICS_EN		BIT(22)
#define FE_GDM1_TCS_EN		BIT(21)
#define FE_GDM1_UCS_EN		BIT(20)
#define FE_GDM1_JMB_EN		BIT(19)
#define FE_GDM1_STRPCRC		BIT(16)
#define FE_GDM1_UFRC_P_CPU	(0 << 12)
#define FE_GDM1_UFRC_P_GDMA1	(1 << 12)
#define FE_GDM1_UFRC_P_PPE	(6 << 12)

/* checksums */
#define FE_ICS_GEN_EN		BIT(2)
#define FE_UCS_GEN_EN		BIT(1)
#define FE_TCS_GEN_EN		BIT(0)

/* dma ring */
#define FE_PST_DRX_IDX0		BIT(16)
#define FE_PST_DTX_IDX3		BIT(3)
#define FE_PST_DTX_IDX2		BIT(2)
#define FE_PST_DTX_IDX1		BIT(1)
#define FE_PST_DTX_IDX0		BIT(0)

#define FE_TX_WB_DDONE		BIT(6)
#define FE_RX_DMA_BUSY		BIT(3)
#define FE_TX_DMA_BUSY		BIT(1)
#define FE_RX_DMA_EN		BIT(2)
#define FE_TX_DMA_EN		BIT(0)

#define FE_PDMA_SIZE_4DWORDS	(0 << 4)
#define FE_PDMA_SIZE_8DWORDS	(1 << 4)
#define FE_PDMA_SIZE_16DWORDS	(2 << 4)

#define FE_US_CYC_CNT_MASK	0xff
#define FE_US_CYC_CNT_SHIFT	0x8
#define FE_US_CYC_CNT_DIVISOR	1000000

#define RX_DMA_PLEN0(_x)	(((_x) >> 16) & 0x3fff)
#define RX_DMA_LSO		BIT(30)
#define RX_DMA_DONE		BIT(31)
#define RX_DMA_L4VALID		BIT(30)

struct fe_rx_dma {
	unsigned int rxd1;
	unsigned int rxd2;
	unsigned int rxd3;
	unsigned int rxd4;
} __packed __aligned(4);

#define TX_DMA_PLEN0_MASK	((0x3fff) << 16)
#define TX_DMA_PLEN0(_x)	(((_x) & 0x3fff) << 16)
#define TX_DMA_PLEN1(_x)	((_x) & 0x3fff)
#define TX_DMA_LS1		BIT(14)
#define TX_DMA_LSO		BIT(30)
#define TX_DMA_DONE		BIT(31)
#define TX_DMA_QN(_x)		((_x) << 16)
#define TX_DMA_PN(_x)		((_x) << 24)
#define TX_DMA_QN_MASK		TX_DMA_QN(0x7)
#define TX_DMA_PN_MASK		TX_DMA_PN(0x7)
#define TX_DMA_CHKSUM		(0x7 << 29)

struct fe_tx_dma {
	unsigned int txd1;
	unsigned int txd2;
	unsigned int txd3;
	unsigned int txd4;
} __packed __aligned(4);

struct fe_priv;

struct fe_phy {
	struct phy_device	*phy[8];
	struct device_node	*phy_node[8];
	const __be32		*phy_fixed[8];
	int			duplex[8];
	int			speed[8];
	int			tx_fc[8];
	int			rx_fc[8];
	spinlock_t		lock;

	int (*connect)(struct fe_priv *priv);
	void (*disconnect)(struct fe_priv *priv);
	void (*start)(struct fe_priv *priv);
	void (*stop)(struct fe_priv *priv);
};

struct fe_soc_data
{
	unsigned char mac[6];
	const u32 *reg_table;

	void (*init_data)(struct fe_soc_data *data);
	void (*reset_fe)(void);
	void (*set_mac)(struct fe_priv *priv, unsigned char *mac);
	void (*fwd_config)(struct fe_priv *priv);
	void (*tx_dma)(struct fe_priv *priv, int idx, struct sk_buff *skb);
	void (*rx_dma)(struct fe_priv *priv, int idx, int len);
	int (*switch_init)(struct fe_priv *priv);
	int (*switch_config)(struct fe_priv *priv);
	void (*port_init)(struct fe_priv *priv, struct device_node *port);
	int (*has_carrier)(struct fe_priv *priv);
	int (*mdio_init)(struct fe_priv *priv);
	void (*mdio_cleanup)(struct fe_priv *priv);
	int (*mdio_write)(struct mii_bus *bus, int phy_addr, int phy_reg, u16 val);
	int (*mdio_read)(struct mii_bus *bus, int phy_addr, int phy_reg);
	void (*mdio_adjust_link)(struct fe_priv *priv, int port);
	int (*get_skb_header)(struct sk_buff *skb, void **iphdr, void **tcph, u64 *hdr_flags, void *priv);

	void *swpriv;
	u32 pdma_glo_cfg;
	u32 rx_dly_int;
	u32 tx_dly_int;
	u32 checksum_bit;
	u32 tso;

	int min_pkt_len;
};

struct fe_priv
{
	spinlock_t			page_lock;

	struct fe_soc_data		*soc;
	struct net_device		*netdev;
	struct device			*device;
	unsigned long			sysclk;

	struct fe_rx_dma		*rx_dma;
        struct napi_struct		rx_napi;
	struct sk_buff			*rx_skb[NUM_DMA_DESC];
	dma_addr_t			rx_phys;

	struct fe_tx_dma		*tx_dma;
	struct tasklet_struct		tx_tasklet;
	struct sk_buff			*tx_skb[NUM_DMA_DESC];
	dma_addr_t			tx_phys;
	unsigned int			tx_free_idx;

	struct fe_phy			*phy;
	struct mii_bus			*mii_bus;
	int				mii_irq[PHY_MAX_ADDR];

	int				link[8];

	struct net_lro_mgr		lro_mgr;
	struct net_lro_desc		lro_arr[8];
};

extern const struct of_device_id of_fe_match[];

void fe_w32(u32 val, unsigned reg);
u32 fe_r32(unsigned reg);

#endif /* FE_ETH_H */
