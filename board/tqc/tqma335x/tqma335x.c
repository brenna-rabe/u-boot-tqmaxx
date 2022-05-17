// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2021, TQ-Systems GmbH
 *
 * Copyright (C) 2011, Texas Instruments, Incorporated - http://www.ti.com/
 */

#include <common.h>
#include <cpsw.h>
#include <dm.h>
#include <errno.h>
#include <environment.h>
#include <i2c.h>
#include <miiphy.h>
#include <serial.h>
#include <spl.h>
#include <watchdog.h>
#include <asm/io.h>
#include <asm/emif.h>
#include <asm/gpio.h>
#include <asm/arch/clk_synthesizer.h>
#include <asm/arch/clock.h>
#include <asm/arch/cpu.h>
#include <asm/arch/ddr_defs.h>
#include <asm/arch/hardware.h>
#include <asm/arch/gpio.h>
#include <asm/arch/mem.h>
#include <asm/arch/mmc_host_def.h>
#include <asm/arch/mux.h>
#include <asm/arch/omap.h>
#include <asm/arch/sys_proto.h>
#include <asm/omap_common.h>
#include <asm/omap_sec_common.h>
#include <asm/omap_mmc.h>
#include <power/tps65910.h>

#include "../common/tqc_eeprom.h"
#include "../common/tqc_sdmmc.h"
#include "tqma335x.h"

DECLARE_GLOBAL_DATA_PTR;

static struct module_pin_mux uart0_pin_mux[] = {
	{OFFSET(uart0_rxd), (MODE(0) | PULLUP_EN | RXACTIVE)},	/* UART0_RXD */
	{OFFSET(uart0_txd), (MODE(0) | PULLUDEN)},		/* UART0_TXD */
	{-1},
};

static struct module_pin_mux uart3_pin_mux[] = {
	{OFFSET(spi0_cs1), (MODE(1) | PULLUP_EN | RXACTIVE)},	/* UART3_RXD */
	{OFFSET(ecap0_in_pwm0_out), (MODE(1) | PULLUDEN)},	/* UART3_TXD */
	{-1},
};

static struct module_pin_mux uart4_pin_mux[] = {
	{OFFSET(gpmc_wait0), (MODE(6) | PULLUP_EN | RXACTIVE)},	/* UART4_RXD */
	{OFFSET(gpmc_wpn), (MODE(6) | PULLUDEN)},		/* UART4_TXD */
	{-1},
};

static struct module_pin_mux mmc0_pin_mux[] = {
	{OFFSET(mmc0_dat3), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_DAT3 */
	{OFFSET(mmc0_dat2), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_DAT2 */
	{OFFSET(mmc0_dat1), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_DAT1 */
	{OFFSET(mmc0_dat0), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_DAT0 */
	{OFFSET(mmc0_clk), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_CLK */
	{OFFSET(mmc0_cmd), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_CMD */
	{OFFSET(mcasp0_aclkr), (MODE(4) | RXACTIVE)},		/* MMC0_WP */
	{OFFSET(spi0_cs1), (MODE(7) | RXACTIVE | PULLUP_EN)},	/* GPIO0_6 */
	{-1},
};

static struct module_pin_mux i2c0_pin_mux[] = {
	{OFFSET(i2c0_sda), (MODE(0) | RXACTIVE |
			PULLUDEN | SLEWCTRL)}, /* I2C_DATA */
	{OFFSET(i2c0_scl), (MODE(0) | RXACTIVE |
			PULLUDEN | SLEWCTRL)}, /* I2C_SCLK */
	{-1},
};

void enable_uart0_pin_mux(void)
{
	configure_module_pin_mux(uart0_pin_mux);
}

void enable_uart3_pin_mux(void)
{
	configure_module_pin_mux(uart3_pin_mux);
}

void enable_uart4_pin_mux(void)
{
	configure_module_pin_mux(uart4_pin_mux);
}

void enable_i2c0_pin_mux(void)
{
	configure_module_pin_mux(i2c0_pin_mux);
}

void enable_board_pin_mux(void)
{
	configure_module_pin_mux(mmc0_pin_mux);
	configure_module_pin_mux(i2c0_pin_mux);
	configure_module_pin_mux(uart4_pin_mux);
}

#ifdef CONFIG_ENV_IS_IN_MMC
int mmc_get_env_dev(void)
{
	switch (gd->arch.omap_boot_device) {
	case BOOT_DEVICE_MMC1:
		return 0;
	case BOOT_DEVICE_MMC2:
		return 1;
	default:
		return -ENODEV;
	}
}
#endif

#ifdef CONFIG_SPL_BUILD
static struct ctrl_dev *cdev = (struct ctrl_dev *)CTRL_DEVICE_BASE;

#ifdef CONFIG_TQMA335X_512MB
  #define DDR_CMD0_IOCTRL		DDR3L_512MB_IOCTRL_VALUE
  #define DATA_PHY_RD_DQS_SLAVE_RATIO	DDR3L_512MB_RD_DQS
  #define DATA_PHY_FIFO_WE_SLAVE_RATIO	DDR3L_512MB_PHY_FIFO_WE
  #define DATA_PHY_WR_DQS_SLAVE_RATIO	DDR3L_512MB_WR_DQS
  #define DATA_PHY_WR_DATA_SLAVE_RATIO	DDR3L_512MB_PHY_WR_DATA
  #define CMD_PHY_CTRL_SLAVE_RATIO	DDR3L_512MB_RATIO
  #define CMD_PHY_INVERT_CLKOUT		DDR3L_512MB_INVERT_CLKOUT
  #define ALLOPP_DDR3_SDRAM_CONFIG	DDR3L_512MB_EMIF_SDCFG
  #define ALLOPP_DDR3_REF_CTRL		DDR3L_512MB_EMIF_SDREF
  #define ALLOPP_DDR3_ZQ_CONFIG		DDR3L_512MB_ZQ_CFG
  #define ALLOPP_DDR3_SDRAM_TIMING1	DDR3L_512MB_EMIF_TIM1
  #define ALLOPP_DDR3_SDRAM_TIMING2	DDR3L_512MB_EMIF_TIM2
  #define ALLOPP_DDR3_SDRAM_TIMING3	DDR3L_512MB_EMIF_TIM3
  #define EMIF_DDR_PHY_CTRL_1_REG	DDR3L_512MB_EMIF_READ_LATENCY
#else
  #define DDR_CMD0_IOCTRL		DDR3L_256MB_IOCTRL_VALUE
  #define DATA_PHY_RD_DQS_SLAVE_RATIO	DDR3L_256MB_RD_DQS
  #define DATA_PHY_FIFO_WE_SLAVE_RATIO	DDR3L_256MB_PHY_FIFO_WE
  #define DATA_PHY_WR_DQS_SLAVE_RATIO	DDR3L_256MB_WR_DQS
  #define DATA_PHY_WR_DATA_SLAVE_RATIO	DDR3L_256MB_PHY_WR_DATA
  #define CMD_PHY_CTRL_SLAVE_RATIO	DDR3L_256MB_RATIO
  #define CMD_PHY_INVERT_CLKOUT		DDR3L_256MB_INVERT_CLKOUT
  #define ALLOPP_DDR3_SDRAM_CONFIG	DDR3L_256MB_EMIF_SDCFG
  #define ALLOPP_DDR3_REF_CTRL		DDR3L_256MB_EMIF_SDREF
  #define ALLOPP_DDR3_ZQ_CONFIG		DDR3L_256MB_ZQ_CFG
  #define ALLOPP_DDR3_SDRAM_TIMING1	DDR3L_256MB_EMIF_TIM1
  #define ALLOPP_DDR3_SDRAM_TIMING2	DDR3L_256MB_EMIF_TIM2
  #define ALLOPP_DDR3_SDRAM_TIMING3	DDR3L_256MB_EMIF_TIM3
  #define EMIF_DDR_PHY_CTRL_1_REG	DDR3L_256MB_EMIF_READ_LATENCY
#endif

static const struct ddr_data ddr3_data = {
	.datardsratio0 = DATA_PHY_RD_DQS_SLAVE_RATIO,
	.datawdsratio0 = DATA_PHY_WR_DQS_SLAVE_RATIO,
	.datafwsratio0 = DATA_PHY_FIFO_WE_SLAVE_RATIO,
	.datawrsratio0 = DATA_PHY_WR_DATA_SLAVE_RATIO,
};

static const struct cmd_control ddr3_cmd_ctrl_data = {
	.cmd0csratio = CMD_PHY_CTRL_SLAVE_RATIO,
	.cmd0iclkout = CMD_PHY_INVERT_CLKOUT,

	.cmd1csratio = CMD_PHY_CTRL_SLAVE_RATIO,
	.cmd1iclkout = CMD_PHY_INVERT_CLKOUT,

	.cmd2csratio = CMD_PHY_CTRL_SLAVE_RATIO,
	.cmd2iclkout = CMD_PHY_INVERT_CLKOUT,
};

static struct emif_regs ddr3_emif_reg_data = {
	.sdram_config = ALLOPP_DDR3_SDRAM_CONFIG,
	.ref_ctrl = ALLOPP_DDR3_REF_CTRL,
	.sdram_tim1 = ALLOPP_DDR3_SDRAM_TIMING1,
	.sdram_tim2 = ALLOPP_DDR3_SDRAM_TIMING2,
	.sdram_tim3 = ALLOPP_DDR3_SDRAM_TIMING3,
	.zq_config = ALLOPP_DDR3_ZQ_CONFIG,
	.emif_ddr_phy_ctlr_1 = EMIF_DDR_PHY_CTRL_1_REG,
};

const struct ctrl_ioregs ioregs = {
	.cm0ioctl		= DDR_CMD0_IOCTRL,
	.cm1ioctl		= DDR_CMD0_IOCTRL,
	.cm2ioctl		= DDR_CMD0_IOCTRL,
	.dt0ioctl		= DDR_CMD0_IOCTRL,
	.dt1ioctl		= DDR_CMD0_IOCTRL,
};

#ifdef CONFIG_SPL_OS_BOOT
int spl_start_uboot(void)
{
#ifdef CONFIG_SPL_SERIAL_SUPPORT
	/* break into full u-boot on 'c' */
	if (serial_tstc() && serial_getc() == 'c')
		return 1;
#endif

	return 0;
}
#endif

const struct dpll_params *get_dpll_ddr_params(void)
{
	int ind = get_sys_clk_index();

	return &dpll_ddr3_400MHz[ind];
}

const struct dpll_params *get_dpll_mpu_params(void)
{
	int ind = get_sys_clk_index();
	int freq = am335x_get_efuse_mpu_max_freq(cdev);

	switch (freq) {
	case MPUPLL_M_1000:
		return &dpll_mpu_opp[ind][5];
	case MPUPLL_M_800:
		return &dpll_mpu_opp[ind][4];
	case MPUPLL_M_720:
		return &dpll_mpu_opp[ind][3];
	case MPUPLL_M_600:
		return &dpll_mpu_opp[ind][2];
	case MPUPLL_M_500:
		return &dpll_mpu_opp100;
	case MPUPLL_M_300:
		return &dpll_mpu_opp[ind][0];
	}

	return &dpll_mpu_opp[ind][0];
}

static void scale_vcores_generic(int freq)
{
	int sil_rev, mpu_vdd;

	/*
	 * The GP EVM, IDK and EVM SK use a TPS65910 PMIC.  For all
	 * MPU frequencies we support we use a CORE voltage of
	 * 1.10V.  For MPU voltage we need to switch based on
	 * the frequency we are running at.
	 */
#ifndef CONFIG_DM_I2C
	if (i2c_probe(TPS65910_CTRL_I2C_ADDR))
		return;
#else
	if (power_tps65910_init(0))
		return;
#endif
	/*
	 * Depending on MPU clock and PG we will need a different
	 * VDD to drive at that speed.
	 */
	sil_rev = readl(&cdev->deviceid) >> 28;
	mpu_vdd = am335x_get_tps65910_mpu_vdd(sil_rev, freq);

	/* Tell the TPS65910 to use i2c */
	tps65910_set_i2c_control();

	/* First update MPU voltage. */
	if (tps65910_voltage_update(MPU, mpu_vdd))
		return;

	/* Second, update the CORE voltage. */
	if (tps65910_voltage_update(CORE, TPS65910_OP_REG_SEL_1_1_0))
		return;
}

void gpi2c_init(void)
{
	/* When needed to be invoked prior to BSS initialization */
	static bool first_time = true;

	if (first_time) {
		enable_i2c0_pin_mux();
#ifndef CONFIG_DM_I2C
		i2c_init(CONFIG_SYS_OMAP24_I2C_SPEED,
			 CONFIG_SYS_OMAP24_I2C_SLAVE);
#endif
		first_time = false;
	}
}

void scale_vcores(void)
{
	int freq;

	gpi2c_init();
	freq = am335x_get_efuse_mpu_max_freq(cdev);

	scale_vcores_generic(freq);
}

void sdram_init(void)
{
	config_ddr(400, &ioregs, &ddr3_data, &ddr3_cmd_ctrl_data,
		   &ddr3_emif_reg_data, 0);
}
#endif

/*
 * Basic board specific setup.  Pinmux has been handled already.
 */
int board_init(void)
{
	save_omap_boot_params();
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;

	return 0;
}

#if defined(CONFIG_BOARD_LATE_INIT) && !defined(CONFIG_SPL_BUILD)
int board_late_init(void)
{
	int ret;
	/* must hold largest field of eeprom data */
	char safe_string[0x41];
	struct tqc_eeprom_data eedat;
	u32 mac;
	u8 addr[6];

	ret = tqc_read_eeprom_buf(CONFIG_SYS_EEPROM_BUS_NUM, CONFIG_SYS_I2C_EEPROM_ADDR,
				  CONFIG_SYS_I2C_EEPROM_ADDR_LEN, 0,  sizeof(eedat),
				  (void *)&eedat);
	if (!ret) {
		/* ID */
		tqc_parse_eeprom_id(&eedat, safe_string, ARRAY_SIZE(safe_string));
		if (strncmp(safe_string, "TQM", 3) == 0)
			env_set("boardtype", safe_string);
		if (tqc_parse_eeprom_serial(&eedat, safe_string, ARRAY_SIZE(safe_string)) == 0)
			env_set("serial#", safe_string);
		else
			env_set("serial#", "???");

		if (tqc_parse_eeprom_mac(&eedat, safe_string, ARRAY_SIZE(safe_string)) == 0) {
			env_set("ethaddr", safe_string);

			eth_parse_enetaddr(safe_string, addr);
			mac = addr[3] << 16 | addr[4] << 8 | addr[5];
			mac++;
			mac &= 0xFFFFFF;

			addr[3] = (uint8_t)(mac >> 16);
			addr[4] = (uint8_t)(mac >>  8);
			addr[5] = (uint8_t)(mac >>  0);
			eth_env_set_enetaddr("eth1addr", addr);
		}

		tqc_show_eeprom(&eedat, "TQM");
	} else {
		printf("EEPROM: err %d\n", ret);
	}

	board_late_mmc_env_init();

	return 0;
}
#endif

#if !CONFIG_IS_ENABLED(OF_CONTROL)
static const struct omap_hsmmc_plat am335x_mmc1_platdata = {
	.base_addr = (struct hsmmc *)OMAP_HSMMC2_BASE,
	.cfg.host_caps = MMC_MODE_HS_52MHz | MMC_MODE_HS | MMC_MODE_8BIT,
	.cfg.f_min = 400000,
	.cfg.f_max = 52000000,
	.cfg.voltages = MMC_VDD_32_33 | MMC_VDD_33_34 | MMC_VDD_165_195,
	.cfg.b_max = CONFIG_SYS_MMC_MAX_BLK_COUNT,
};

U_BOOT_DEVICE(am335x_mmc1) = {
	.name = "omap_hsmmc",
	.platdata = &am335x_mmc1_platdata,
};
#endif
