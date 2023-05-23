// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (c) 2020-2023 TQ-Systems GmbH <u-boot@ew.tq-group.com>,
 * D-82229 Seefeld, Germany.
 * Author: Martin Schmiedel
 */

#include <common.h>
#include <asm/arch/clock.h>
#if defined(CONFIG_IMX8MN)
#include <asm/arch/imx8mn_pins.h>
#elif defined(CONFIG_IMX8MM)
#include <asm/arch/imx8mm_pins.h>
#else
#error
#endif
#include <asm/arch/sys_proto.h>
#include <asm/mach-imx/boot_mode.h>
#include <asm/mach-imx/gpio.h>
#include <asm/mach-imx/iomux-v3.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <errno.h>
#include <fsl_esdhc_imx.h>
#include <mmc.h>
#include <spl.h>
#include <usb.h>
#include <usb/ehci-ci.h>

#include "../common/tqc_bb.h"

DECLARE_GLOBAL_DATA_PTR;

#define USBNC_OFFSET		0x200UL

/*
 * TODO:
 * check if i.MX8MN / i.MX8MM need different settings
 * we use the pull stages although the the errata for i.MX8MM says that the pull
 * stages drift. For SD pull up in the range of 10 ... 100 kOhm is allowed
 */
#define USDHC_CTL_PAD_CTRL	(PAD_CTL_DSE4 | PAD_CTL_HYS | PAD_CTL_FSEL2 | \
				 PAD_CTL_PE | PAD_CTL_PUE)
#define USDHC_DATA_PAD_CTRL	(PAD_CTL_DSE2 | PAD_CTL_HYS | PAD_CTL_FSEL2 | \
				 PAD_CTL_PE | PAD_CTL_PUE)
#define USDHC_GPIO_PAD_CTRL	(PAD_CTL_HYS | PAD_CTL_DSE1)
#define USDHC2_CD_GPIO	IMX_GPIO_NR(2, 12)
#define USDHC2_WP_GPIO	IMX_GPIO_NR(2, 20)
#define USDHC2_PWR_GPIO IMX_GPIO_NR(2, 19)

#ifdef CONFIG_USB
#define OTG_PWR_PAD		IMX_GPIO_NR(1, 12)
#define OTG_GPIO_PAD_CTL	(PAD_CTL_HYS | PAD_CTL_DSE1)
#endif

#ifdef CONFIG_IMX8MN
	static iomux_v3_cfg_t const usdhc2_pads[] = {
		IMX8MN_PAD_SD2_CLK__USDHC2_CLK | MUX_PAD_CTRL(USDHC_CTL_PAD_CTRL),
		IMX8MN_PAD_SD2_CMD__USDHC2_CMD | MUX_PAD_CTRL(USDHC_CTL_PAD_CTRL),
		IMX8MN_PAD_SD2_DATA0__USDHC2_DATA0 | MUX_PAD_CTRL(USDHC_DATA_PAD_CTRL),
		IMX8MN_PAD_SD2_DATA1__USDHC2_DATA1 | MUX_PAD_CTRL(USDHC_DATA_PAD_CTRL),
		IMX8MN_PAD_SD2_DATA2__USDHC2_DATA2 | MUX_PAD_CTRL(USDHC_DATA_PAD_CTRL),
		IMX8MN_PAD_SD2_DATA3__USDHC2_DATA3 | MUX_PAD_CTRL(USDHC_DATA_PAD_CTRL),
		IMX8MN_PAD_SD2_CD_B__GPIO2_IO12 | MUX_PAD_CTRL(USDHC_GPIO_PAD_CTRL),
		IMX8MN_PAD_SD2_WP__GPIO2_IO20 | MUX_PAD_CTRL(USDHC_GPIO_PAD_CTRL),
		IMX8MN_PAD_SD2_RESET_B__GPIO2_IO19 | MUX_PAD_CTRL(USDHC_GPIO_PAD_CTRL),
		IMX8MN_PAD_GPIO1_IO04__USDHC2_VSELECT | MUX_PAD_CTRL(USDHC_GPIO_PAD_CTRL),
	};
	#ifdef CONFIG_USB
	static iomux_v3_cfg_t const usb_otg_pads[] = {
		/* PWR */
		IMX8MN_PAD_GPIO1_IO12__GPIO1_IO12 | MUX_PAD_CTRL(OTG_GPIO_PAD_CTL),
		/* ID */
		IMX8MN_PAD_GPIO1_IO10__USB1_OTG_ID | MUX_PAD_CTRL(OTG_GPIO_PAD_CTL),
	};
	#endif
#elif defined(CONFIG_IMX8MM)
	static iomux_v3_cfg_t const usdhc2_pads[] = {
		IMX8MM_PAD_SD2_CLK_USDHC2_CLK | MUX_PAD_CTRL(USDHC_CTL_PAD_CTRL),
		IMX8MM_PAD_SD2_CMD_USDHC2_CMD | MUX_PAD_CTRL(USDHC_CTL_PAD_CTRL),
		IMX8MM_PAD_SD2_DATA0_USDHC2_DATA0 | MUX_PAD_CTRL(USDHC_DATA_PAD_CTRL),
		IMX8MM_PAD_SD2_DATA1_USDHC2_DATA1 | MUX_PAD_CTRL(USDHC_DATA_PAD_CTRL),
		IMX8MM_PAD_SD2_DATA2_USDHC2_DATA2 | MUX_PAD_CTRL(USDHC_DATA_PAD_CTRL),
		IMX8MM_PAD_SD2_DATA3_USDHC2_DATA3 | MUX_PAD_CTRL(USDHC_DATA_PAD_CTRL),
		IMX8MM_PAD_SD2_CD_B_GPIO2_IO12 | MUX_PAD_CTRL(USDHC_GPIO_PAD_CTRL),
		IMX8MM_PAD_SD2_WP_GPIO2_IO20 | MUX_PAD_CTRL(USDHC_GPIO_PAD_CTRL),
		IMX8MM_PAD_SD2_RESET_B_GPIO2_IO19 | MUX_PAD_CTRL(USDHC_GPIO_PAD_CTRL),
		IMX8MM_PAD_GPIO1_IO04_USDHC2_VSELECT | MUX_PAD_CTRL(USDHC_GPIO_PAD_CTRL),
	};
	#ifdef CONFIG_USB
	static iomux_v3_cfg_t const usb_otg_pads[] = {
		/* PWR */
		IMX8MM_PAD_GPIO1_IO12_GPIO1_IO12 | MUX_PAD_CTRL(OTG_GPIO_PAD_CTL),
		/* ID */
		IMX8MM_PAD_GPIO1_IO10_USB1_OTG_ID | MUX_PAD_CTRL(OTG_GPIO_PAD_CTL),
	};
	#endif
#else
#error
#endif

static struct fsl_esdhc_cfg usdhc2_cfg = {
	.esdhc_base = USDHC2_BASE_ADDR,
	.max_bus_width = 4,
};

int tqc_bb_board_mmc_getcd(struct mmc *mmc)
{
	struct fsl_esdhc_cfg *cfg = (struct fsl_esdhc_cfg *)mmc->priv;
	int ret = 0;

	debug("%s\n", __func__);
	switch (cfg->esdhc_base) {
	case USDHC2_BASE_ADDR:
		ret = !gpio_get_value(USDHC2_CD_GPIO);
		return ret;
	}

	return ret;
}

int tqc_bb_board_mmc_init(bd_t *bis)
{
	int ret;

	debug("%s\n", __func__);
	/*
	 * According to the board_mmc_init() the following map is done:
	 * (U-Boot device node)    (Physical Port)
	 * mmc0                    USDHC3 (REV.0200)
	 * mmc1                    USDHC2
	 */
	init_clk_usdhc(1);
	usdhc2_cfg.sdhc_clk = mxc_get_clock(MXC_ESDHC2_CLK);
	imx_iomux_v3_setup_multiple_pads(usdhc2_pads, ARRAY_SIZE(usdhc2_pads));
	gpio_request(USDHC2_PWR_GPIO, "usdhc2_reset");
	gpio_direction_output(USDHC2_PWR_GPIO, 0);
	udelay(2000);
	gpio_direction_output(USDHC2_PWR_GPIO, 1);
	gpio_request(USDHC2_CD_GPIO, "usdhc2 cd");
	gpio_direction_input(USDHC2_CD_GPIO);

	ret = fsl_esdhc_initialize(bis, &usdhc2_cfg);

	return ret;
}

/*
 * In case of boot from SD1 (e-MMC) or SD2 (SD-Card) we must correct the boot
 * device settings, since the i.MX8MM CPU code will return BOOT_DEVICE_MMC1
 * for SD1 and SD2 which is wrong for our board. Restore sane default with
 * our own mapping, BOOT_DEVICE_MMC1/2 is used in spl_mmc to query the index
 * of the MMC device.
 */
void board_boot_order(u32 *spl_boot_list)
{
	enum boot_device boot_device_spl = get_boot_device();

	switch (boot_device_spl) {
	case SD3_BOOT:
	case MMC3_BOOT:
		puts("boot order USDHC3 -> MMC1\n");
		spl_boot_list[0] = BOOT_DEVICE_MMC1;
		break;
	case SD1_BOOT:
	case MMC1_BOOT:
		puts("boot order USDHC1 -> MMC1\n");
		spl_boot_list[0] = BOOT_DEVICE_MMC1;
		break;
	case SD2_BOOT:
	case MMC2_BOOT:
		puts("boot order USDHC2 -> MMC2\n");
		spl_boot_list[0] = BOOT_DEVICE_MMC2;
		break;
	default:
		spl_boot_list[0] = spl_boot_device();
	}
}

void tqc_bb_spl_board_init(void)
{
	debug("%s\n", __func__);
}

void tqc_bb_board_init_f(ulong dummy)
{
	debug("%s\n", __func__);
}

#if defined(CONFIG_USB)

int board_ehci_hcd_init(int port)
{
	pr_debug("%s(idx %d)\n", __func__, port);

	if (port == 0) {
		u32 *usbnc_usb_ctrl2 = (u32 *)(ulong)(USB_BASE_ADDR +
						      (0x10000ul * (ulong)port) +
						      USBNC_OFFSET + 4ul);
		imx_iomux_v3_setup_multiple_pads(usb_otg_pads,
						 ARRAY_SIZE(usb_otg_pads));

		pr_debug("USB0/OTG: DIG_ID_SEL %p\n", usbnc_usb_ctrl2);
		/* Set DIG_ID_SEL to muxable PIN for ID detect */
		setbits_le32(usbnc_usb_ctrl2, BIT(20));

		gpio_request(OTG_PWR_PAD, "otg_pwr");
		gpio_direction_output(OTG_PWR_PAD, 0);
	};

	return 0;
}

int board_ehci_power(int port, int on)
{
	pr_debug("%s(idx %d, %s)\n", __func__, port, (on) ? "ON" : "OFF");

	if (port == 0) {
		gpio_direction_output(OTG_PWR_PAD, (on) ? 1 : 0);
	};

	return 0;
}

int board_usb_init(int index, enum usb_init_type init)
{
	int ret;

	pr_debug("%s(idx %d)\n", __func__, index);
	ret = imx8m_usb_power(index, true);

	return ret;
}

int board_usb_cleanup(int index, enum usb_init_type init)
{
	int ret;

	pr_debug("%s(idx %d)\n", __func__, index);
	ret = imx8m_usb_power(index, false);

	return ret;
}

#endif

int spl_board_boot_device(enum boot_device boot_dev_spl)
{
	pr_debug("%s\n", __func__);
	switch (boot_dev_spl) {
	case SD2_BOOT:
	case MMC2_BOOT:
		return BOOT_DEVICE_MMC1;
	case SD3_BOOT:
	case MMC3_BOOT:
		return BOOT_DEVICE_MMC2;
	case QSPI_BOOT:
		return BOOT_DEVICE_NOR;
	case NAND_BOOT:
		return BOOT_DEVICE_NAND;
	case USB_BOOT:
		return BOOT_DEVICE_BOARD;
	default:
		return BOOT_DEVICE_NONE;
	}
}
