/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright (C) 2016-2018 TQ Systems GmbH
 * Configuration settings for the TQ Systems TQMa7x SOM
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __TQMA7_CONFIG_H
#define __TQMA7_CONFIG_H

#include <linux/kconfig.h>

#include <asm/arch/imx-regs.h>
#include <asm/imx-common/gpio.h>
#include <linux/sizes.h>
#include "mx7_common.h"

#define CONFIG_DISPLAY_CPUINFO
#if defined(CONFIG_DISPLAY_BOARDINFO)
#undef CONFIG_DISPLAY_BOARDINFO
#endif
#define CONFIG_DISPLAY_BOARDINFO_LATE

#define CONFIG_DBG_MONITOR

/* uncomment for SECURE mode support */
/* #define CONFIG_SECURE_BOOT */

#ifdef CONFIG_SECURE_BOOT
#ifndef CONFIG_CSF_SIZE
#define CONFIG_CSF_SIZE 0x4000
#endif
#endif

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_REVISION_TAG

#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_BOARD_LATE_INIT

#define CONFIG_MXC_GPIO
#define CONFIG_MXC_UART

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_CONS_INDEX		1
#define CONFIG_BAUDRATE			115200

/* I2C Configs */
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_SYS_I2C_SPEED		100000
#define CONFIG_SYS_I2C_MXC_I2C1		/* enable I2C bus 1 */


/* I2C SYSMON (LM75) */
#define CONFIG_DTT_LM75
#define CONFIG_DTT_MAX_TEMP		70
#define CONFIG_DTT_MIN_TEMP		-30
#define CONFIG_DTT_HYSTERESIS	3
#define CONFIG_CMD_DTT

/* I2C EEPROM (M24C64) */
#define CONFIG_SYS_I2C_EEPROM_ADDR			0x50
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN			2
#define CONFIG_SYS_I2C_EEPROM_PAGE_WRITE_BITS		5 /* 32 Bytes */
#define CONFIG_SYS_I2C_EEPROM_PAGE_WRITE_DELAY_MS	20
#define CONFIG_CMD_EEPROM

/* RTC and time support */
#define CONFIG_CMD_DATE
#define CONFIG_RTC_DS1339
#define CONFIG_SYS_I2C_RTC_ADDR 0x68

#define CONFIG_CMD_SF

/* Quad-SPI */
#define CONFIG_FSL_QSPI
#define CONFIG_QSPI_BASE		QSPI1_IPS_BASE_ADDR
#define CONFIG_QSPI_MEMMAP_BASE		QSPI0_ARB_BASE_ADDR

/* Quad-SPI Flash */
#define	CONFIG_SF_DEFAULT_BUS		0
#define	CONFIG_SF_DEFAULT_CS		0
#define	CONFIG_SF_DEFAULT_SPEED		40000000
#define	CONFIG_SF_DEFAULT_MODE		SPI_MODE_0

/* filesystem on flash */
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_UBI
#define CONFIG_RBTREE
#define CONFIG_MTD_UBI_WL_THRESHOLD     4096
#define CONFIG_CMD_UBIFS
#define CONFIG_LZO

/* PMIC */
#define CONFIG_POWER
#define CONFIG_POWER_I2C
#define CONFIG_POWER_PFUZE3000
#define CONFIG_PFUZE3000_PMIC_I2C
#define CONFIG_POWER_PFUZE3000_I2C_ADDR		0x08

/* MMC Configs, other options from mx7_common */
#define CONFIG_SYS_FSL_ESDHC_ADDR	0
#define CONFIG_SUPPORT_EMMC_RPMB

/* USB Configs */
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_MX7
#define CONFIG_USB_STORAGE
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_USB_ETHER_SMSC95XX
#define CONFIG_MXC_USB_PORTSC	(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS	0
#define CONFIG_USB_MAX_CONTROLLER_COUNT	3
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET	/* For OTG port */
#define CONFIG_MX7_USB_HSIC_PORTSC	(PORT_PTS_HSIC | PORT_PTS_PTW)

/* Fuses */
#define CONFIG_MXC_OCOTP
#define CONFIG_CMD_FUSE

#define CONFIG_CMD_EXT2
#define CONFIG_CMD_EXT4
#define CONFIG_CMD_EXT4_WRITE
#define CONFIG_CMD_FAT
#define CONFIG_FAT_WRITE
#define CONFIG_CMD_FS_GENERIC
#define CONFIG_DOS_PARTITION

#if defined(CONFIG_TQMA7_512MB)
#define PHYS_SDRAM_SIZE			SZ_512M
#elif defined(CONFIG_TQMA7_1GB)
#define PHYS_SDRAM_SIZE			SZ_1G
#elif defined(CONFIG_TQMA7_2GB)
#define PHYS_SDRAM_SIZE			SZ_2G
#endif

#define CONFIG_FEC_MXC
#define CONFIG_PHYLIB
#define CONFIG_MII
#define CONFIG_CMD_MII
#define CONFIG_FEC_DMA_MINALIGN		64

#define CONFIG_CMD_BMODE
#define CONFIG_CMD_BOOTZ

#if !defined(CONFIG_SYS_BOOTM_LEN) || (CONFIG_SYS_BOOTM_LEN < SZ_16M)
#undef CONFIG_SYS_BOOTM_LEN
#define CONFIG_SYS_BOOTM_LEN		SZ_16M
#endif

#undef CONFIG_BOOTM_NETBSD
#undef CONFIG_BOOTM_PLAN9
#undef CONFIG_BOOTM_RTEMS

#define CONFIG_BOOTDELAY		3
#define CONFIG_ZERO_BOOTDELAY_CHECK

#if defined(CONFIG_LOADADDR) && (CONFIG_LOADADDR < 0x82000000)
#undef CONFIG_LOADADDR
#endif
#define CONFIG_LOADADDR			0x82000000

/* place code in last 8 MiB of RAM */
#if defined(CONFIG_SYS_TEXT_BASE)
#undef CONFIG_SYS_TEXT_BASE
#endif
#if defined(CONFIG_TQMA7_512MB)
#define CONFIG_SYS_TEXT_BASE		0x9f800000
#elif defined(CONFIG_TQMA7_1GB)
#define CONFIG_SYS_TEXT_BASE		0xbf800000
#elif defined(CONFIG_TQMA7_2GB)
#define CONFIG_SYS_TEXT_BASE		0xff800000
#endif

#define CONFIG_ENV_SIZE			(SZ_8K)
/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(32 * SZ_1M)

/*
 * above 128 MiB offset as in ARM related docu for linux suggested
 * DTB is loaded at 128 MiB, so use just 16 MiB more
 */
#define TQMA7_INITRD_ADDRESS		0x89000000

#define TQMA7_MFG_ENV_SETTINGS \
	"mfgtool_args=setenv bootargs console=" CONFIG_CONSOLE_DEV ",115200 "    \
		"rdinit=/linuxrc "                                               \
		"g_mass_storage.stall=0 g_mass_storage.removable=1 "             \
		"g_mass_storage.file=/fat g_mass_storage.ro=1 "                  \
		"g_mass_storage.idVendor=0x066F g_mass_storage.idProduct=0x37FF "\
		"g_mass_storage.iSerialNumber=\"\" "                             \
		"enable_wait_mode=off "                                          \
		"\0"                                                             \
		"initrd_addr="__stringify(TQMA7_INITRD_ADDRESS)"\0"              \
		"initrd_high=0xffffffff\0"                                       \
		"bootcmd_mfg=run mfgtool_args;bootz ${loadaddr} ${initrd_addr} ${fdt_addr};\0" \

#if defined(CONFIG_TQMA7_MMC_BOOT)

#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV		-1
#define TQMA7_UBOOT_OFFSET		SZ_1K
#define TQMA7_UBOOT_SECTOR_START	0x2
#define TQMA7_UBOOT_SECTOR_COUNT	0x7fe

#define CONFIG_ENV_OFFSET		SZ_1M

#define TQMA7_EXTRA_BOOTDEV_ENV_SETTINGS                                       \
	"uboot_start="__stringify(TQMA7_UBOOT_SECTOR_START)"\0"                \
	"uboot_size="__stringify(TQMA7_UBOOT_SECTOR_COUNT)"\0"                 \
	"mmcdev=-1\0"                                                          \
	"firmwarepart=1\0"                                                     \
	"loadimage=run kernel_name; "                                          \
		"load mmc ${mmcdev}:${firmwarepart} ${loadaddr} ${kernel} \0"  \
	"loadfdt="                                                             \
		"load mmc ${mmcdev}:${firmwarepart} ${fdt_addr} ${fdt_file} \0"\
	"update_uboot=run set_getcmd; "                                        \
		"if ${getcmd} ${uboot}; then "                                 \
			"if itest ${filesize} > 0; then "                      \
				"mmc dev ${mmcdev}; mmc rescan; "              \
				"setexpr blkc ${filesize} + 0x1ff; "           \
				"setexpr blkc ${blkc} / 0x200; "               \
				"if itest ${blkc} <= ${uboot_size}; then "     \
					"mmc write ${loadaddr} ${uboot_start} "\
						"${blkc}; "                    \
				"fi; "                                         \
			"fi; "                                                 \
		"fi; "                                                         \
		"setenv filesize; setenv blkc; setenv getcmd \0"               \
	"update_kernel=run kernel_name; run set_getcmd; "                      \
		"if ${getcmd} ${kernel}; then "                                \
			"if itest ${filesize} > 0; then "                      \
				"mmc dev ${mmcdev}; mmc rescan; "              \
				"echo Write kernel image to mmc ${mmcdev}:${firmwarepart}...; " \
				"save mmc ${mmcdev}:${firmwarepart} ${loadaddr} " \
					"${kernel} ${filesize}; "              \
			"fi; "                                                 \
		"fi; "                                                         \
		"setenv filesize; setenv getcmd \0"                            \
	"update_fdt=run set_getcmd; "                                          \
		"if ${getcmd} ${fdt_file}; then "                              \
			"if itest ${filesize} > 0; then "                      \
				"mmc dev ${mmcdev}; mmc rescan; "              \
				"echo Write fdt image to mmc ${mmcdev}:${firmwarepart}...; " \
				"save mmc ${mmcdev}:${firmwarepart} ${loadaddr} " \
					"${fdt_file} ${filesize}; "            \
			"fi; "                                                 \
		"fi; "                                                         \
		"setenv filesize; setenv getcmd \0"                            \

#define CONFIG_BOOTCOMMAND \
	"run mmcboot; run netboot; run panicboot"

#elif defined(CONFIG_TQMA7_QSPI_BOOT)

#define TQMA7_SPI_FLASH_SECTOR_SIZE	SZ_64K

#define TQMA7_UBOOT_OFFSET		SZ_4K
#define TQMA7_UBOOT_SECTOR_START	0x0
/* max u-boot size: 832kiB */
#define TQMA7_UBOOT_SECTOR_SIZE	TQMA7_SPI_FLASH_SECTOR_SIZE
#define TQMA7_UBOOT_SECTOR_COUNT	13
#define TQMA7_UBOOT_SIZE		(TQMA7_UBOOT_SECTOR_SIZE * \
					 TQMA7_UBOOT_SECTOR_COUNT)

#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_SYS_REDUNDAND_ENVIRONMENT
#define CONFIG_ENV_OFFSET		(TQMA7_UBOOT_SIZE)
#define CONFIG_ENV_SECT_SIZE		TQMA7_SPI_FLASH_SECTOR_SIZE
#define CONFIG_ENV_OFFSET_REDUND	(CONFIG_ENV_OFFSET + \
					 CONFIG_ENV_SECT_SIZE)

#define CONFIG_ENV_SPI_BUS		(CONFIG_SF_DEFAULT_BUS)
#define CONFIG_ENV_SPI_CS		(CONFIG_SF_DEFAULT_CS)
#define CONFIG_ENV_SPI_MAX_HZ		(CONFIG_SF_DEFAULT_SPEED)
#define CONFIG_ENV_SPI_MODE		(CONFIG_SF_DEFAULT_MODE)

#define TQMA7_EXTRA_BOOTDEV_ENV_SETTINGS                                       \
	"mmcblkdev=0\0"                                                        \
	"update_uboot=run set_getcmd; if ${getcmd} ${uboot}; then "            \
		"if itest ${filesize} > 0; then "                              \
			"sf probe 0; "                                         \
			"sf update ${loadaddr} ${uboot_mtdpart} ${filesize}; " \
		"fi; fi; "                                                     \
		"setenv filesize; setenv getcmd \0"                            \
	"update_kernel=run kernel_name; run set_getcmd; "                      \
		"if ${getcmd} ${kernel}; then "                                \
			"if itest ${filesize} > 0; then "                      \
				"sf probe 0; "                                 \
				"sf update ${loadaddr} ${kernel_mtdpart} "     \
					"${filesize};"                         \
		"fi; fi; "                                                     \
		"setenv filesize; setenv getcmd; setenv kernel \0"             \
	"update_fdt=run set_getcmd; if ${getcmd} ${fdt_file}; then "           \
		"if itest ${filesize} > 0; then "                              \
			"sf probe 0; "                                         \
			"sf update ${loadaddr} ${fdt_mtdpart} ${filesize}; "   \
		"fi; fi; "                                                     \
		"setenv filesize; setenv getcmd \0"                            \
	"loadimage=sf probe 0; sf read ${loadaddr} ${kernel_mtdpart}\0"        \
	"loadfdt=sf probe 0; sf read ${fdt_addr} ${fdt_mtdpart}\0"             \

#define CONFIG_BOOTCOMMAND                                                     \
	"sf probe; run qspiboot; run netboot; run panicboot"                   \

#else

#error "need to define boot source"

#endif

#define CONFIG_CMD_BOOTAUX /* Boot M4 */

#ifdef CONFIG_CMD_BOOTAUX

#define CONFIG_SYS_AUXCORE_BOOTDATA 0x7F8000 /* Set to TCML address */

#define CONFIG_MXC_RDC /* Enable RDC to isolate the peripherals for A7 and M4 */

#define TQMA7_M4_ENV \
	"m4image=m4.bin\0"                                                     \
	"loadm4image=load mmc ${mmcdev}:${firmwarepart} "                      \
		__stringify(CONFIG_SYS_AUXCORE_BOOTDATA)" ${m4image}\0"        \
	"m4boot=run loadm4image; "                                             \
		"bootaux "__stringify(CONFIG_SYS_AUXCORE_BOOTDATA)"\0"         \
	"m4netboot=tftp ${m4image}; "                                          \
		"bootaux "__stringify(CONFIG_SYS_AUXCORE_BOOTDATA)"\0"
#else
#define TQMA7_M4_ENV
#endif

/* 128 MiB offset as in ARM related docu for linux suggested */
#define TQMA7_FDT_ADDRESS		0x88000000

/* set to a resonable value, changeable by user */
#define TQMA7_CMA_SIZE                 32M

#define TQMA7_MODULE_ENV_SETTINGS \
	"board=tqma7\0"                                                        \
	"uimage=uImage\0"                                                      \
	"zimage=linuximage\0"                                                  \
	"boot_type=bootz\0"                                                    \
	"kernel_name=if test \"${boot_type}\" != bootz; then "                 \
		"setenv kernel ${uimage}; "                                    \
		"else setenv kernel ${zimage}; fi\0"                           \
	"uboot=u-boot.imx\0"                                                   \
	"fdt_addr="__stringify(TQMA7_FDT_ADDRESS)"\0"                          \
	"cma_size="__stringify(TQMA7_CMA_SIZE)"\0"                             \
	"fdt_high=0xffffffff\0"                                                \
	"initrd_high=0xffffffff\0"                                             \
	"rootfsmode=ro\0"                                                      \
	"addcma=setenv bootargs ${bootargs} cma=${cma_size}\0"                 \
	"addtty=setenv bootargs ${bootargs} console=${console},${baudrate} "   \
		"consoleblank=0\0"                                             \
	"mmcpart=2\0"                                                          \
	"mmcblkdev=0\0"                                                        \
	"mmcargs=run addmmc addtty addcma\0"                                   \
	"addmmc=setenv bootargs ${bootargs} "                                  \
		"root=/dev/mmcblk${mmcblkdev}p${mmcpart} ${rootfsmode} "       \
		"rootwait\0"                                                   \
	"mmcboot=echo Booting from mmc ...; "                                  \
		"setenv bootargs; "                                            \
		"run mmcargs; "                                                \
		"if run loadimage; then "                                      \
			"if run loadfdt; then "                                \
				"echo boot device tree kernel ...; "           \
				"${boot_type} ${loadaddr} - ${fdt_addr}; "     \
			"fi; "                                                 \
		"else "                                                        \
			"${boot_type}; "                                       \
		"fi;\0"                                                        \
		"setenv bootargs \0"                                           \
	"qspiboot=echo Booting from qspi ...; "                                \
		"setenv bootargs; "                                            \
		"run qspiargs; "                                               \
		"if run loadimage; then "                                      \
			"if run loadfdt; then "                                \
				"echo boot device tree kernel ...; "           \
				"${boot_type} ${loadaddr} - ${fdt_addr}; "     \
			"fi; "                                                 \
		"else "                                                        \
			"${boot_type}; "                                       \
		"fi;\0"                                                        \
		"setenv bootargs \0"                                           \
	"netdev=eth0\0"                                                        \
	"rootpath=/srv/nfs/tqma7\0"                                            \
	"ipmode=static\0"                                                      \
	"netargs=run addnfs addip addtty addcma\0"                             \
	"addnfs=setenv bootargs ${bootargs} "                                  \
		"root=/dev/nfs rw "                                            \
		"nfsroot=${serverip}:${rootpath},v3,tcp;\0"                    \
	"addip_static=setenv bootargs ${bootargs} "                            \
		"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:"            \
		"${hostname}:${netdev}:off\0"                                  \
	"addip_dynamic=setenv bootargs ${bootargs} ip=dhcp\0"                  \
	"addip=if test \"${ipmode}\" != static; then "                         \
		"run addip_dynamic; else run addip_static; fi\0"               \
	"set_getcmd=if test \"${ipmode}\" != static; then "                    \
		"setenv getcmd dhcp; setenv autoload yes; "                    \
		"else setenv getcmd tftp; setenv autoload no; fi\0"            \
	"netboot=echo Booting from net ...; "                                  \
		"run kernel_name; "                                            \
		"run set_getcmd; "                                             \
		"setenv bootargs; "                                            \
		"run netargs; "                                                \
		"if ${getcmd} ${fdt_addr} ${fdt_file}; then "                  \
			"if ${getcmd} ${loadaddr} ${kernel}; then "            \
				"${boot_type} ${loadaddr} - ${fdt_addr}; "     \
			"fi; "                                                 \
		"fi; "                                                         \
		"echo ... failed\0"                                            \
	"panicboot=echo No boot device !!! reset\0"                            \
	"rootfs_mtddev=5\0"                                                    \
	"addqspi=setenv bootargs ${bootargs} root=ubi0:root ${rootfsmode} "    \
		"rootfstype=ubifs ubi.mtd=${rootfs_mtddev}\0"                  \
	"qspiargs=run addqspi addtty addcma\0"                                 \
	"uboot_mtdpart=U-Boot\0"                                               \
	"fdt_mtdpart=DTB\0"                                                    \
	"kernel_mtdpart=Linux\0"                                               \
	"rootfs_mtdpart=RootFS\0"                                              \

/* Miscellaneous configurable options */
#define CONFIG_SYS_LONGHELP
#define CONFIG_AUTO_COMPLETE

#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR

#if defined(CONFIG_CMD_MEMTEST)
/*
 * config alternate mtest:
 * enable 3/4 of RAM to test
 * U-Boot is relocated to the end of RAM
 * TODO: enable dynamic sizing
 */
#define CONFIG_SYS_ALT_MEMTEST
#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + \
					(PHYS_SDRAM_SIZE) / 4 * 3)
#define CONFIG_SYS_MEMTEST_SCRATCH	CONFIG_SYS_MEMTEST_END
#endif

#define CONFIG_CMDLINE_EDITING
#define CONFIG_STACKSIZE		SZ_128K

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* FLASH and environment organization */
#define CONFIG_SYS_NO_FLASH

#define CONFIG_OF_LIBFDT
#define CONFIG_OF_BOARD_SETUP
#define CONFIG_FIT
#define CONFIG_FIT_VERBOSE

#ifndef CONFIG_SYS_DCACHE_OFF
#define CONFIG_CMD_CACHE
#endif

#define CONFIG_SYS_CONSOLE_IS_IN_ENV


#define CONFIG_IMX_THERMAL

/*
 * All the defines above are for the TQMa7 SoM
 *
 * Now include the baseboard specific configuration
 */
#undef CONFIG_MXC_UART_BASE

#ifdef CONFIG_MBA7
#include "tqma7_mba7.h"
#else
#error "No baseboard for the TQMa7 SOM defined!"
#endif

/* Support at least the sensor on TQMa7 SOM */
#if !defined(CONFIG_DTT_SENSORS)
#define CONFIG_DTT_SENSORS		{ 0 }
#endif

/* fix env settings with manboard specific stuff */
#if defined(CONFIG_DEFAULT_FDT_FILE)
#define TQMA7_FDT_FILE_ENV	"fdt_file=" CONFIG_DEFAULT_FDT_FILE "\0"
#else
#define TQMA7_FDT_FILE_ENV
#endif

#if defined(CONFIG_ARMV7_BOOT_SEC_DEFAULT)
#define TQMA7_BOOTM_BOOT_MODE "sec"
#else
#define TQMA7_BOOTM_BOOT_MODE "nonsec"
#endif

#if defined(MTDPARTS_DEFAULT)
#define TQMA7_MTDPARTS_ENV "mtdparts=" MTDPARTS_DEFAULT "\0"
#else
#define TQMA7_MTDPARTS_ENV
#endif

#define CONFIG_EXTRA_ENV_SETTINGS                                              \
	TQMA7_M4_ENV                                                           \
	TQMA7_MODULE_ENV_SETTINGS                                              \
	TQMA7_EXTRA_BOOTDEV_ENV_SETTINGS                                       \
	TQMA7_FDT_FILE_ENV                                                     \
	"console=" CONFIG_CONSOLE_DEV "\0"                                     \
	"bootm_boot_mode=" TQMA7_BOOTM_BOOT_MODE "\0"                          \
	TQMA7_MTDPARTS_ENV                                                     \
	TQMA7_MFG_ENV_SETTINGS

#endif /* __TQMA7_CONFIG_H */