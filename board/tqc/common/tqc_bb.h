/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (C) 2013, 2014, 2016 - 2022 TQ-Systems
 * Author: Markus Niebel <markus.niebel@tq-group.com>
 */

#ifndef __TQC_BB__
#define __TQC_BB__

#include <common.h>

struct mmc;

int tqc_bb_board_mmc_getwp(struct mmc *mmc);
int tqc_bb_board_mmc_getcd(struct mmc *mmc);
int tqc_bb_board_mmc_init(bd_t *bis);

void tqc_bb_board_init_f(ulong dummy);
int tqc_bb_board_early_init_f(void);
int tqc_bb_board_init(void);
int tqc_bb_board_late_init(void);
int tqc_bb_checkboard(void);
void tqc_bb_board_quiesce_devices(void);

const char *tqc_bb_get_boardname(void);

#if defined(CONFIG_SPL_BUILD)
void tqc_bb_spl_board_init(void);
#endif

/*
 * Device Tree Support
 */
#if defined(CONFIG_OF_BOARD_SETUP) && defined(CONFIG_OF_LIBFDT)
int tqc_bb_ft_board_setup(void *blob, bd_t *bd);
struct node_info;
/**
 * modify SPI NOR specific data in the FDT before booting the OS.
 *
 * @param blob		FDT blob to update
 * @param path		path to spi controller for the SPI NOR device
 * @param nodes		list of compatibles to scan
 * @param node_count	path to spi controller for the SPI NOR device
 *
 * Test if optional SPI NOR is present and enable / disable it in device tree
 * If present, use U-Boot standard env variables to add partition info to the
 * SPI NOR device node. This is needed by kernel to use UBIFS in MTD partition
 * as rootfs.
 *
 * If compiled without SPI NOR support no changes are applied to device tree
 */
void tqc_ft_spi_setup(void *blob, const char *path,
		      const struct node_info *nodes,
		      size_t node_count);
#endif /* defined(CONFIG_OF_BOARD_SETUP) && defined(CONFIG_OF_LIBFDT) */

#if defined(CONFIG_TQC_RTC) && (CONFIG_DM_I2C)

#define TQC_PCF85063_CLKOUT_OFF 0x07

int tqc_pcf85063_adjust_capacity(int bus, int address, int quartz_load);
int tqc_pcf85063_set_clkout(int bus, int address, uint8_t clkout);
int tqc_pcf85063_set_offset(int bus, int address, bool mode, int offset);
#endif /* CONFIG_TQC_RTC */

#endif