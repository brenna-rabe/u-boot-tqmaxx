// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright 2020-2021 TQ-Systems GmbH
 */

#include <common.h>
#include <fsl_ddr_sdram.h>
#include <fsl_ddr_dimm_params.h>

DECLARE_GLOBAL_DATA_PTR;

int fsl_initdram(void)
{
	gd->ram_size = tfa_get_dram_size();

	if (!gd->ram_size)
		gd->ram_size = fsl_ddr_sdram_size();

	return 0;
}