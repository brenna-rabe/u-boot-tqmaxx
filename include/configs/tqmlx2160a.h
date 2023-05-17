/* SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (c) 2020-2023 TQ-Systems GmbH <u-boot@ew.tq-group.com>,
 * D-82229 Seefeld, Germany.
 * Author: Gregor Herburger
 */

#ifndef __TQMLX2160A_H
#define __TQMLX2160A_H

#include <asm/arch/stream_id_lsch3.h>
#include <asm/arch/config.h>
#include <asm/arch/soc.h>
#include <linux/sizes.h>

#define CONFIG_REMAKE_ELF
#define CONFIG_FSL_LAYERSCAPE
#define CONFIG_GICV3
#define CONFIG_FSL_TZPC_BP147
#define CONFIG_FSL_MEMAC

#define CONFIG_SYS_INIT_SP_ADDR		CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_FLASH_BASE		0x20000000

#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_BOARD_EARLY_INIT_F	1

/* DDR */
#define CONFIG_FSL_DDR_INTERACTIVE	/* Interactive debugging */
#define CONFIG_SYS_FSL_DDR_INTLV_256B	/* force 256 byte interleaving */
#define CONFIG_VERY_BIG_RAM
#define CONFIG_SYS_DDR_SDRAM_BASE		0x80000000UL
#define CONFIG_SYS_FSL_DDR_SDRAM_BASE_PHY	0
#define CONFIG_SYS_DDR_BLOCK2_BASE		0x2080000000ULL
#define CONFIG_SYS_FSL_DDR_MAIN_NUM_CTRLS	2
#define CONFIG_SYS_SDRAM_SIZE			0x200000000UL
#define CONFIG_DDR_SPD
#define CONFIG_DDR_ECC
#define CONFIG_ECC_INIT_VIA_DDRCONTROLLER
#define CONFIG_SYS_SDRAM_BASE		CONFIG_SYS_DDR_SDRAM_BASE
#define CONFIG_MEM_INIT_VALUE		0xdeadbeef
#define CONFIG_SYS_SPD_BUS_NUM		0	/* SPD on I2C bus 0 */
#define CONFIG_DIMM_SLOTS_PER_CTLR	2
#define CONFIG_CHIP_SELECTS_PER_CTRL	4
#define CONFIG_FSL_DDR_BIST	/* enable built-in memory test */
#define CONFIG_SYS_MONITOR_LEN		(936 * 1024)

#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_DDR_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_SDRAM_BASE + (100 * SZ_1M))

/* Miscellaneous configurable options */
#define CONFIG_SYS_LOAD_ADDR		0x90000000
#define CONFIG_LOADADDR			CONFIG_SYS_LOAD_ADDR

/* SMP Definitinos  */
#define CPU_RELEASE_ADDR		secondary_boot_func

/* Generic Timer Definitions */
/*
 * This is not an accurate number. It is used in start.S. The frequency
 * will be udpated later when get_bus_freq(0) is available.
 */

#define COUNTER_FREQUENCY		25000000	/* 25MHz */

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 2048 * 1024)

/* Serial Port */
#define CONFIG_PL01X_SERIAL
#define CONFIG_PL011_CLOCK		(get_bus_freq(0) / 4)
#define CONFIG_SYS_SERIAL0		0x21c0000
#define CONFIG_SYS_SERIAL1		0x21d0000
#define CONFIG_SYS_SERIAL2		0x21e0000
#define CONFIG_SYS_SERIAL3		0x21f0000
/*below might needs to be removed*/
#define CONFIG_PL01x_PORTS		{(void *)CONFIG_SYS_SERIAL0, \
					(void *)CONFIG_SYS_SERIAL1, \
					(void *)CONFIG_SYS_SERIAL2, \
					(void *)CONFIG_SYS_SERIAL3 }
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

/* MC firmware */
#define CONFIG_SYS_LS_MC_DPC_MAX_LENGTH		0x20000
#define CONFIG_SYS_LS_MC_DRAM_DPC_OFFSET	0x00F00000
#define CONFIG_SYS_LS_MC_DPL_MAX_LENGTH		0x20000
#define CONFIG_SYS_LS_MC_DRAM_DPL_OFFSET	0x00F20000
#define CONFIG_SYS_LS_MC_BOOT_TIMEOUT_MS	5000

/* Define phy_reset function to boot the MC based on mcinitcmd.
 * This happens late enough to properly fixup u-boot env MAC addresses.
 */
#define CONFIG_RESET_PHY_R

/*
 * Carve out a DDR region which will not be used by u-boot/Linux
 *
 * It will be used by MC and Debug Server. The MC region must be
 * 512MB aligned, so the min size to hide is 512MB.
 */
#ifdef CONFIG_FSL_MC_ENET
#define CONFIG_SYS_LS_MC_DRAM_BLOCK_MIN_SIZE	(256UL * 1024 * 1024)
#endif

#define CONFIG_VID

/* RTC */
#define RTC
#define CONFIG_SYS_RTC_BUS_NUM		0x0
#define CONFIG_SYS_I2C_RTC_ADDR		0x51

#define SYSCTRL_I2C_BUS_NUM		0x0
#define SYSCTRL_I2C_ADDR		0x11

#define I2C_XFI1_BUS			0x8
#define I2C_XFI1_RETIMER_ADDR		0x19
#define I2C_XFI2_BUS			0x9
#define I2C_XFI2_RETIMER_ADDR		0x1B

#define I2C_QSFP_BUS			0xA
#define I2C_QSFP_RETIMER1_ADDR		0x21
#define I2C_QSFP_RETIMER2_ADDR		0x20

#define CONFIG_SYS_I2C_EEPROM_ADDR	0x57
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN	1

/* PCI */
#ifdef CONFIG_PCI
#define CONFIG_SYS_PCI_64BIT
#define CONFIG_PCI_SCAN_SHOW
#endif

/* MMC */
#ifdef CONFIG_MMC
#define CONFIG_SYS_FSL_MMC_HAS_CAPBLT_VS33
#endif

/* SATA */
#ifdef CONFIG_SCSI
#define CONFIG_SCSI_AHCI_PLAT
#define CONFIG_SYS_SATA1		AHCI_BASE_ADDR1
#define CONFIG_SYS_SATA2		AHCI_BASE_ADDR2
#define CONFIG_SYS_SCSI_MAX_SCSI_ID	1
#define CONFIG_SYS_SCSI_MAX_LUN		1
#define CONFIG_SYS_SCSI_MAX_DEVICE	(CONFIG_SYS_SCSI_MAX_SCSI_ID * \
					CONFIG_SYS_SCSI_MAX_LUN)
#endif

/* USB */
#ifdef CONFIG_USB
#define CONFIG_HAS_FSL_XHCI_USB
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#endif

/* FlexSPI */
#ifdef CONFIG_NXP_FSPI
#define NXP_FSPI_FLASH_SIZE		SZ_128M
#define NXP_FSPI_FLASH_NUM		1
#endif

#ifndef __ASSEMBLY__
unsigned long get_board_sys_clk(void);
unsigned long get_board_ddr_clk(void);
#endif

#define CONFIG_SYS_CLK_FREQ		get_board_sys_clk()
#define CONFIG_DDR_CLK_FREQ		get_board_ddr_clk()
#define COUNTER_FREQUENCY_REAL		(CONFIG_SYS_CLK_FREQ / 4)

#define CONFIG_HWCONFIG
#define HWCONFIG_BUFFER_SIZE		128
#define CONFIG_MTD_DEVICE
#define CONFIG_CMD_MTDPARTS
#define MTDIDS_DEFAULT \
		"nor0=nor0\0"

#define MTDPARTS_DEFAULT						       \
	"mtdparts=nor0:"                                                       \
	"1M@0k(RCW-PBL),"                                                      \
	"2M@1M(U-Boot),"                                                       \
	"1M@5M(U-Boot-Env),"						       \
	"2M@8M(DDR-PHY),"						       \
	"3M@10M(DPAA2-MC),"                                                    \
	"1M@13M(DPAA2-DPL),"						       \
	"1M@14M(DPAA2-DPC),"						       \
	"112M@16M(RootFS)\0"

#define CONFIG_SYS_MMC_ENV_DEV          0
#define CONFIG_ENV_SIZE			SZ_128K
#define CONFIG_ENV_SECT_SIZE		SZ_128K
#define CONFIG_ENV_OFFSET		(5 * SZ_1M)
#define CONFIG_ENV_ADDR			(CONFIG_SYS_FLASH_BASE + \
					 CONFIG_ENV_OFFSET)

/* Allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE		512	/* Console I/O Buffer Size */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE /* Boot args buffer */
#define CONFIG_CMDLINE_EDITING		1
#define CONFIG_SYS_MAXARGS		64	/* max command args */

#define CONFIG_SYS_BOOTM_LEN   (64 << 20)      /* Increase max gunzip size */

#define MAX_UBOOT_SIZE 0x300000
#define MMC_UBOOT_OFFSET 0x800 /* Blocks */

/* Initial environment variables */
#define XSPI_MC_INIT_CMD			\
	"env exists secureboot && "		\
	"esbc_validate 0x20700000 && "		\
	"esbc_validate 0x20740000 ;"		\
	"fsl_mc start mc 0x20a00000 0x20e00000\0"

#define SD_MC_INIT_CMD				\
	"load mmc ${mmcdev_sdhc}:${bootpart} 0x80a00000 ${mc_file};"\
	"load mmc ${mmcdev_sdhc}:${bootpart} 0x80e00000 ${dpc_file};"\
	"fsl_mc start mc 0x80a00000 0x80e00000\0"

#define SD2_MC_INIT_CMD				\
	"load mmc ${mmcdev_emmc}:${bootpart} 0x80a00000 ${mc_file};"\
	"load mmc ${mmcdev_emmc}:${bootpart} 0x80e00000 ${dpc_file};"\
	"fsl_mc start mc 0x80a00000 0x80e00000\0"

#define EXTRA_ENV_SETTINGS			\
	"hwconfig=fsl_ddr:bank_intlv=auto\0"	\
	"ramdisk_addr=0x800000\0"		\
	"ramdisk_size=0x2000000\0"		\
	"kernel_start=0x1000000\0"		\
	"kernelheader_start=0x7C0000\0"		\
	"scriptaddr=0x80000000\0"		\
	"scripthdraddr=0x80080000\0"		\
	"kernel_addr_r=0x81000000\0"		\
	"fdt_addr_r=0x90000000\0"		\
	"consoledev=ttyAMA0\0"			\
	"bootpart=1\0"				\
	"mc_file=mc.itb\0"			\
	"dpc_file=dpc-warn.dtb\0"		\
	"dpl_file=dpl-min.dtb\0"		\
	"mmcdev_sdhc=0\0"			\
	"mmcdev_emmc=1\0"			\
	"kernel=Image\0"			\
	"fdt_file=" __stringify(CONFIG_DEFAULT_DEVICE_TREE) ".dtb\0"	       \
	"earlycon=pl011,mmio32,0x21c0000\0"				       \
	"rootfsmode=ro\0"                                                      \
	"addtty=setenv bootargs ${bootargs} console=${consoledev},${baudrate}n8\0"\
	"addearlycon=setenv bootargs ${bootargs} earlycon=${earlycon}\0"       \
	"mmcargs=run addmmc addtty addearlycon\0"                              \
	"mmcblkdev=0\0"                                                        \
	"mmcrootpart=2\0"                                                      \
	"addmmc=setenv bootargs ${bootargs} "                                  \
		"root=/dev/mmcblk${mmcblkdev}p${mmcrootpart} ${rootfsmode} "   \
		"rootwait\0"                                                   \
	"uboot=fip_uboot.bin\0"						       \
	"uboot_spi_offset=0x100000\0"					       \
	"pbl_mmc_offset=8\0"						       \
	"ubirootfspart=RootFS\0"					       \
	"ubirootfsvol=root\0"						       \
	"uboot_mmc_offset=" __stringify(MMC_UBOOT_OFFSET) "\0"                 \
	"uboot_max_size=" __stringify(MAX_UBOOT_SIZE) "\0"                     \
	"pbl_spi_offset=0x0\0"						       \
	"pbl_spi=bl2_flexspi_nor.pbl\0"					       \
	"pbl_sdmmc=bl2_auto.pbl\0"					       \
	"update_uboot_spi=run set_getcmd; if ${get_cmd} ${uboot}; then "       \
		"if itest ${filesize} > 0; then "                              \
			"echo Write u-boot image to sf address ${uboot_spi_offset};"\
			"sf probe;"					       \
			"sf update ${fileaddr} ${uboot_spi_offset} ${filesize};"\
		"fi; fi; "                                                     \
		"setenv filesize;\0"					       \
	"update_pbl_spi=run set_getcmd; if ${get_cmd} ${pbl_spi}; then "       \
		"if itest ${filesize} > 0; then "                              \
			"echo Write rcw-pbl image to address ${pbl_spi_offset};"\
			"sf probe;"					       \
			"sf update ${fileaddr} ${pbl_spi_offset} ${filesize};"\
		"fi; fi; "                                                     \
		"setenv filesize;\0"					       \
	"update_pbl_mmc=run set_getcmd; if ${get_cmd} ${pbl_sdmmc}; then "       \
		"if itest ${filesize} > 0; then "                              \
			"mmc dev ${mmcdev_emmc}; mmc rescan; "	               \
			"setexpr blkc ${filesize} + 0x1ff; "                   \
			"setexpr blkc ${blkc} / 0x200; "		       \
			"if itest ${filesize} <= ${uboot_max_size}; then "     \
				"mmc write ${fileaddr} ${pbl_mmc_offset} ${blkc}; "\
			"fi; "                                         \
		"fi; fi; "                                                     \
		"setenv filesize;\0"					       \
	"update_uboot_mmc=run set_getcmd; if ${get_cmd} ${uboot}; then "       \
		"if itest ${filesize} > 0; then "                              \
			"mmc dev ${mmcdev_emmc}; mmc rescan; "		       \
			"setexpr blkc ${filesize} + 0x1ff; "		       \
			"setexpr blkc ${blkc} / 0x200; "		       \
			"if itest ${filesize} <= ${uboot_max_size}; then "     \
				"mmc write ${fileaddr} ${uboot_mmc_offset} ${blkc}; "\
			"fi; "						       \
		"fi; fi; "                                                     \
		"setenv filesize;\0"					       \
	"update_pbl_sd=run set_getcmd; if ${get_cmd} ${pbl_mmc}; then "        \
		"if itest ${filesize} > 0; then "                              \
			"mmc dev ${mmcdev_sdhc}; mmc rescan; "	               \
			"setexpr blkc ${filesize} + 0x1ff; "                   \
			"setexpr blkc ${blkc} / 0x200; "		       \
			"if itest ${filesize} <= ${uboot_max_size}; then "     \
				"mmc write ${fileaddr} ${pbl_mmc_offset} ${blkc}; "\
			"fi; "						       \
		"fi; fi; "                                                     \
		"setenv filesize;\0"					       \
	"update_uboot_sd=run set_getcmd; if ${get_cmd} ${uboot}; then "        \
		"if itest ${filesize} > 0; then "                              \
			"mmc dev ${mmcdev_sdhc}; mmc rescan; "		       \
			"setexpr blkc ${filesize} + 0x1ff; "		       \
			"setexpr blkc ${blkc} / 0x200; "		       \
			"if itest ${filesize} <= ${uboot_max_size}; then "     \
				"mmc write ${fileaddr} ${uboot_mmc_offset} ${blkc}; " \
			"fi; "                                                 \
		"fi; fi; "                                                     \
		"setenv filesize;\0"					       \
	"set_getcmd=if test \"${ip_dyn}\" = yes; then "                        \
			"setenv get_cmd dhcp; "                                \
		"else "                                                        \
			"setenv get_cmd tftp; "                                \
		"fi; \0"                                                       \
	"spiargs=run addspi addtty addearlycon\0"                              \
	"addspi=setenv bootargs ${bootargs} root=ubi0_0 rw "		       \
		"rootfstype=ubifs ubi.mtd=7\0"                                 \
	BOOTENV								       \
	"mcmemsize=0x70000000\0"					       \
	XSPI_MC_INIT_CMD						       \
	"scan_dev_for_boot_part="					       \
		"part list ${devtype} ${devnum} devplist; "	\
		"env exists devplist || setenv devplist 1; "	\
		"for distro_bootpart in ${devplist}; do "	\
			"if fstype ${devtype} "			\
				"${devnum}:${distro_bootpart} "	\
				"bootfstype; then "		\
				"run scan_dev_for_boot; "	\
			"fi; "					\
		"done\0"					\
	"boot_a_script="					\
		"load ${devtype} ${devnum}:${distro_bootpart} "	\
			"${scriptaddr} ${prefix}${script}; "	\
		"env exists secureboot && load ${devtype} "	\
			"${devnum}:${distro_bootpart} "		\
			"${scripthdraddr} ${prefix}${boot_script_hdr} "	\
			"&& esbc_validate ${scripthdraddr};"	\
		"source ${scriptaddr}\0"

#define XSPI_NOR_BOOTCOMMAND					\
	"run distro_bootcmd;run xspi_bootcmd; "
#define SD_BOOTCOMMAND						\
	"run distro_bootcmd;run sd_bootcmd;"
#define SD2_BOOTCOMMAND						\
	"run distro_bootcmd;run emmc_bootcmd;"

/* Initial environment variables */
#define CONFIG_EXTRA_ENV_SETTINGS		\
	EXTRA_ENV_SETTINGS			\
	"xspi_bootcmd=echo Trying load from flexspi..;"		\
		"setenv bootargs; "				\
		"run spiargs; "					\
		"sf probe 0:0; "				\
		"ubi part ${ubirootfspart}; "			\
		"ubifsmount ubi0:${ubirootfsvol}; "		\
		"ubifsload ${kernel_addr_r} /boot/${kernel}; "	\
		"ubifsload ${fdt_addr_r} /boot/${fdt_file}; "	\
		"ubifsumount; ubi detach ;"			\
		"fsl_mc lazyapply DPL 0x20d00000; "     	\
		"booti ${kernel_addr_r} - ${fdt_addr_r}\0"	\
	"sdmmc_bootcmd=setenv bootargs; run mmcargs;"		\
		"load mmc ${mmcblkdev}:${mmcrootpart} ${kernel_addr_r} /boot/${kernel};" \
		"load mmc ${mmcblkdev}:${mmcrootpart} ${fdt_addr_r} /boot/${fdt_file};" \
		"load mmc ${mmcblkdev}:${bootpart} 0x80d00000 ${dpl_file};" \
		"fsl_mc lazyappply DPL 0x80d00000;"	        \
		"booti ${kernel_addr_r} - ${fdt_addr_r};"	\
		"setenv mmcdev_root\0"                          \
	"sd_bootcmd=echo Trying load from sd card..;"		\
		"setenv mmcblkdev ${mmcdev_sdhc}; "		\
		"run sdmmc_bootcmd\0"                           \
	"emmc_bootcmd=echo Trying load from emmc..;"		\
		"setenv mmcblkdev ${mmcdev_emmc}; "		\
		"run sdmmc_bootcmd\0"                           \

#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 0) \
	func(MMC, mmc, 1)

#include <config_distro_bootcmd.h>

#endif /* __TQMLX2160A_H */
