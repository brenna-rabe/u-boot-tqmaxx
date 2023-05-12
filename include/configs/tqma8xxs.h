/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (c) 2018-2023 TQ-Systems GmbH <u-boot@ew.tq-group.com>,
 * D-82229 Seefeld, Germany.
 * Author: Markus Niebel
 */

#ifndef __TQMA8XXS_H
#define __TQMA8XXS_H

#include <linux/sizes.h>
#include <asm/arch/imx-regs.h>

#include "imx_env.h"

#ifdef CONFIG_SPL_BUILD
#define CONFIG_PARSE_CONTAINER
#define CONFIG_SPL_MAX_SIZE				(192 * 1024)
#define CONFIG_SYS_MONITOR_LEN				(1024 * 1024)
#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_USE_SECTOR
/* (32K + 2Mb) / sector_size */
#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR		0x1040

/*
 * 0x08081000 - 0x08180FFF is for m4_0 xip image,
 * So 3rd container image may start from 0x8181000
 */
#define CONFIG_SYS_UBOOT_BASE 0x08181000
#define CONFIG_SYS_MMCSD_FS_BOOT_PARTITION		0

#define CONFIG_SPL_LDSCRIPT		"arch/arm/cpu/armv8/u-boot-spl.lds"
/*
 * The memory layout on stack:  DATA section save + gd + early malloc
 * the idea is re-use the early malloc (CONFIG_SYS_MALLOC_F_LEN) with
 * CONFIG_SYS_SPL_MALLOC_START
 */
#define CONFIG_SPL_STACK		0x013fff0
#define CONFIG_SPL_BSS_START_ADDR	0x00130000
#define CONFIG_SPL_BSS_MAX_SIZE		0x1000	/* 4 KB */
#define CONFIG_SYS_SPL_MALLOC_START	0x82200000
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x80000	/* 512 KB */
#define CONFIG_SERIAL_LPUART_BASE	0x5a070000
#define CONFIG_MALLOC_F_ADDR		0x00138000

#define CONFIG_SPL_RAW_IMAGE_ARM_TRUSTED_FIRMWARE

#define CONFIG_SPL_ABORT_ON_RAW_IMAGE

#define CONFIG_OF_EMBED
#endif

#define CONFIG_REMAKE_ELF

#undef CONFIG_CMD_EXPORTENV
#undef CONFIG_CMD_IMPORTENV
#undef CONFIG_CMD_IMLS

#undef CONFIG_BOOTM_NETBSD

#if defined(CONFIG_FEC_MXC)
#define FEC_QUIRK_ENET_MAC
#endif

#if defined(CONFIG_USB)
/* needed for USBOTG1 (chipidea) */
#define CONFIG_MXC_USB_PORTSC		(PORT_PTS_UTMI | PORT_PTS_PTW)
#endif

#define CONFIG_ENV_OVERWRITE

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

#ifdef CONFIG_AHAB_BOOT
#define AHAB_ENV "sec_boot=yes\0"
#else
#define AHAB_ENV "sec_boot=no\0"
#endif

#define CONFIG_MFG_ENV_SETTINGS \
	CONFIG_MFG_ENV_SETTINGS_DEFAULT \
	"initrd_addr=0x83100000\0" \
	"initrd_high=0xffffffffffffffff\0" \
	"emmc_dev=0\0" \
	"sd_dev=1\0" \

/* Initial environment variables */
#define TQMA8XXS_MODULE_ENV_SETTINGS		\
	CONFIG_MFG_ENV_SETTINGS \
	AHAB_ENV \
	"script=boot.scr\0" \
	"image=Image\0" \
	"fdt_addr=0x83000000\0"			\
	"cntr_addr=0x98000000\0"			\
	"cntr_file=os_cntr_signed.bin\0" \
	"boot_fdt=try\0" \
	"mmcdev=" __stringify(CONFIG_SYS_MMC_ENV_DEV) "\0" \
	"mmcpart=" __stringify(CONFIG_SYS_MMC_IMG_LOAD_PART) "\0" \
	"mmcpath=/\0" \
	"mmcautodetect=yes\0" \
	"loadbootscript=mmc dev ${mmcdev}; mmc rescan;" \
		"load mmc ${mmcdev}:${mmcpart} ${loadaddr} " \
		"${mmcpath}${script};\0" \
	"bootscript=echo Running bootscript from mmc ...; " \
		"source\0" \
	"loadimage=mmc dev ${mmcdev}; mmc rescan;" \
		"load mmc ${mmcdev}:${mmcpart} ${loadaddr} " \
			"${mmcpath}${image}\0" \
	"loadfdt=mmc dev ${mmcdev}; mmc rescan;" \
		"load mmc ${mmcdev}:${mmcpart} ${fdt_addr} " \
			"${mmcpath}${fdt_file}\0" \
	"loadcntr=mmc dev ${mmcdev}; mmc rescan;" \
		"load mmc ${mmcdev}:${mmcpart} ${cntr_addr} " \
			"${mmcpath}${cntr_file}\0" \
	"auth_os=auth_cntr ${cntr_addr}\0" \
	"boot_os=booti ${loadaddr} - ${fdt_addr};\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"setenv bootargs; " \
		"run mmcargs; " \
		"run loadimage; " \
		"run loadfdt; " \
		"if test ${sec_boot} = yes; then " \
			"if run auth_os; then " \
				"run boot_os; " \
			"else " \
				"echo ERR: failed to authenticate; " \
			"fi; " \
		"else " \
			"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
				"if run loadfdt; then " \
					"run boot_os; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"else " \
				"echo wait for boot; " \
			"fi;" \
		"fi;\0" \
	"netboot=echo Booting from net ...; " \
		"setenv bootargs; " \
		"run netargs;  " \
		"run set_getcmd; " \
		"if test ${sec_boot} = yes; then " \
			"${get_cmd} ${cntr_addr} ${cntr_file}; " \
			"if run auth_os; then " \
				"run boot_os; " \
			"else " \
				"echo ERR: failed to authenticate; " \
			"fi; " \
		"else " \
			"${get_cmd} ${loadaddr} ${image}; " \
			"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
				"if ${get_cmd} ${fdt_addr} ${fdt_file}; then " \
					"run boot_os; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"else " \
				"booti; " \
			"fi;" \
		"fi;\0" \
	"update_kernel_mmc=run set_getcmd; "                                   \
		"if ${get_cmd} ${image}; then "                                \
			"if itest ${filesize} > 0; then "                      \
				"echo Write to mmc ${mmcdev}:${mmcpart}...; "  \
				"mmc dev ${mmcdev}; mmc rescan;" \
				"save mmc ${mmcdev}:${mmcpart} ${loadaddr} "   \
					"${mmcpath}${image} ${filesize}; "     \
			"fi; "                                                 \
		"fi; "                                                         \
		"setenv filesize; setenv get_cmd \0"                           \
	"update_fdt_mmc=run set_getcmd; "                                      \
		"if ${get_cmd} ${fdt_file}; then "                             \
			"if itest ${filesize} > 0; then "                      \
				"echo Write to mmc ${mmcdev}:${mmcpart}...; "  \
				"mmc dev ${mmcdev}; mmc rescan;" \
				"save mmc ${mmcdev}:${mmcpart} ${loadaddr} "   \
					"${mmcpath}${fdt_file} ${filesize}; "  \
			"fi; "                                                 \
		"fi; "                                                         \
		"setenv filesize; setenv get_cmd \0"                           \
	"uboot_mmc_start=0x40\0"                                               \
	"uboot_mmc_size=0xfc0\0"                                               \
	"uboot_fspi_start=0x0\0"                                               \
	"uboot_fspi_size=0x400000\0"                                           \
	"uboot=bootstream.bin\0"                                               \
	"update_uboot_mmc=run set_getcmd; if ${get_cmd} ${uboot}; then "       \
		"if itest ${filesize} > 0; then "                              \
			"echo Write u-boot image to mmc ${mmcdev} ...; "       \
			"mmc dev ${mmcdev}; mmc rescan; "                      \
			"setexpr blkc ${filesize} + 0x1ff; "                   \
			"setexpr blkc ${blkc} / 0x200; "                       \
			"if itest ${blkc} <= ${uboot_mmc_size}; then "         \
				"mmc write ${loadaddr} ${uboot_mmc_start} "    \
					"${blkc}; "                            \
			"fi; "                                                 \
		"fi; fi; "                                                     \
		"setenv filesize; setenv blkc \0"                              \
	"set_getcmd=if test \"${ip_dyn}\" = yes; then "                        \
			"setenv get_cmd dhcp; "                                \
		"else "                                                        \
			"setenv get_cmd tftp; "                                \
		"fi; \0"                                                       \
	"rootfsmode=ro\0"                                                      \
	"addtty=setenv bootargs ${bootargs} console=${console},${baudrate}"    \
		" earlycon\0"                                                  \
	"mmcargs=run addmmc addtty\0"                                          \
	"mmcrootpart=2\0"                                                      \
	"addmmc=setenv bootargs ${bootargs} "                                  \
		"root=/dev/mmcblk${mmcblkdev}p${mmcrootpart} ${rootfsmode} "   \
		"rootwait\0"                                                   \
	"netargs=run addnfs addip addtty\0"                                    \
	"addnfs=setenv bootargs ${bootargs} "                                  \
		"root=/dev/nfs rw "                                            \
		"nfsroot=${serverip}:${rootpath},v3,tcp;\0"                    \
	"netdev=eth0\0"                                                        \
	"rootpath=/srv/nfs\0"                                                  \
	"ipmode=static\0"                                                      \
	"addip_static=setenv bootargs ${bootargs} "                            \
		"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:"            \
		"${hostname}:${netdev}:off\0"                                  \
	"addip_dynamic=setenv bootargs ${bootargs} ip=dhcp\0"                  \
	"addip=if test \"${ipmode}\" != static; then "                         \
		"run addip_dynamic; else run addip_static; fi\0"

#if !defined(CONFIG_BOOTCOMMAND)
#define CONFIG_BOOTCOMMAND \
	   "mmc dev ${mmcdev}; if mmc rescan; then " \
		   "if run loadbootscript; then " \
			   "run bootscript; " \
		   "else " \
			   "if test ${sec_boot} = yes; then " \
				   "if run loadcntr; then " \
					   "run mmcboot; " \
				   "else run netboot; " \
				   "fi; " \
			    "else " \
				   "if run loadimage; then " \
					   "run mmcboot; " \
				   "else run netboot; " \
				   "fi; " \
			 "fi; " \
		   "fi; " \
	   "else run boot_os; fi"
#endif

/* Link Definitions */
#define CONFIG_LOADADDR			0x80280000

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR

#define CONFIG_SYS_INIT_SP_ADDR		0x80200000

/*
 * USDHC1 is for eMMC, USDHC2 is for SD on CPU board - we use DM and
 * determine it based on current boot device
 */
#define CONFIG_SYS_MMC_ENV_DEV		-1	/* invalid */
#define CONFIG_SYS_MMC_ENV_PART		0	/* user area */

#define CONFIG_SYS_MMC_IMG_LOAD_PART	1

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		SZ_64M

#define CONFIG_SYS_SDRAM_BASE		0x80000000
/* #define CONFIG_NR_DRAM_BANKS		1 */
#define PHYS_SDRAM_1			0x80000000
#if defined(CONFIG_TQMA8XXS_RAM_2048MB)
#define PHYS_SDRAM_1_SIZE			SZ_2G /* 2GB LPDDR4 */
#elif defined(CONFIG_TQMA8XXS_RAM_1024MB)
#define PHYS_SDRAM_1_SIZE			SZ_1G /* 1GB LPDDR4 */
#else
#error
#endif
/* needed for loop in CPU code */
#define PHYS_SDRAM_2			0x800000000
#define PHYS_SDRAM_2_SIZE		0x0000000	/* not placed */

#if defined(CONFIG_CMD_MEMTEST)
/*
 * Use alternative / extended memtest,
 * start at CONFIG_LOADADDR and use 3/4 of RAM
 * U-Boot is loaded to 0x80200000 (offset 8 MiB)
 * and relocated at end of configured RAM
 */
#if defined(CONFIG_SYS_ALT_MEMTEST)
#define CONFIG_SYS_MEMTEST_START	(CONFIG_LOADADDR)
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + \
					((PHYS_SDRAM_1_SIZE / 4) * 3))
#define CONFIG_SYS_MEMTEST_SCRATCH	CONFIG_SYS_MEMTEST_END

#endif /* CONFIG_SYS_ALT_MEMTEST */

#endif /* CONFIG_CMD_MEMTEST */

/* Serial */
#define CONFIG_BAUDRATE			115200

/* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE		2048
#define CONFIG_SYS_MAXARGS		64
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)

/* Generic Timer Definitions */
#define COUNTER_FREQUENCY		8000000	/* 8MHz */

/* MT35XU512ABA1G12 has only one Die, so QSPI0 B won't work */
#ifdef CONFIG_FSL_FSPI
#define FSL_FSPI_FLASH_SIZE		SZ_64M
#define FSL_FSPI_FLASH_NUM		1

#define CONFIG_SYS_FSL_FSPI_AHB
#endif

#if defined(CONFIG_TQMA8XXS_BB_MB_SMARC_2)
#include "tqma8xxs-mb-smarc-2.h"
#else
#error
#endif

#include "tqma8-shared-env.h"

#define CONFIG_EXTRA_ENV_SETTINGS		\
	TQMA8_SHARED_ENV_SETTINGS		\
	TQMA8XXS_MODULE_ENV_SETTINGS		\
	BB_ENV_SETTINGS

#ifndef CONFIG_SPL_BUILD
#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 0) \
	func(USB, usb, 0)
#include <config_distro_bootcmd.h>
#endif

#endif /* __TQMA8XXS_H */
