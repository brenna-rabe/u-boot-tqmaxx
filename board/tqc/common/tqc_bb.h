/*
 * Copyright (C) 2013, 2014, 2016 TQ Systems
 * Author: Markus Niebel <markus.niebel@tq-group.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __TQC_BB__
#define __TQC_BB__

#include <common.h>

int tqc_bb_board_mmc_getwp(struct mmc *mmc);
int tqc_bb_board_mmc_getcd(struct mmc *mmc);
int tqc_bb_board_mmc_init(bd_t *bis);

int tqc_bb_board_early_init_f(void);
int tqc_bb_board_init(void);
int tqc_bb_board_late_init(void);
int tqc_bb_checkboard(void);

const char *tqc_bb_get_boardname(void);

/*
 * Device Tree Support
 */
#if defined(CONFIG_OF_BOARD_SETUP) && defined(CONFIG_OF_LIBFDT)
void tqc_bb_ft_board_setup(void *blob, bd_t *bd);
#endif /* defined(CONFIG_OF_BOARD_SETUP) && defined(CONFIG_OF_LIBFDT) */

#endif