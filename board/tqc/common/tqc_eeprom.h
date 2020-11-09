/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2014 - 2020 TQ Systems GmbH
 * Markus Niebel <Markus.Niebel@tq-group.com>
 */

#ifndef __TQC_EEPROM_H__
#define __TQC_EEPROM_H__

int tqc_read_eeprom_buf(unsigned int bus, unsigned int i2c_addr,
			unsigned int alen, unsigned int addr,
			size_t bsize, uchar *buf);

#if !defined(CONFIG_SPL_BUILD)

/*
 * static EEPROM layout
 */
#define TQC_EE_HRCW_BYTES		0x20
#define TQC_EE_MAC_BYTES		6
#define TQC_EE_RSV1_BYTES		10
#define TQC_EE_SERIAL_BYTES		8
#define TQC_EE_RSV2_BYTES		8
#define TQC_EE_BDID_BYTES		0x40

struct __attribute__ ((__packed__)) tqc_eeprom_data {
	u8 hrcw_primary[TQC_EE_HRCW_BYTES];
	u8 mac[TQC_EE_MAC_BYTES];		/* 0x20 ... 0x25 */
	u8 rsv1[TQC_EE_RSV1_BYTES];
	u8 serial[TQC_EE_SERIAL_BYTES];		/* 0x30 ... 0x37 */
	u8 rsv2[TQC_EE_RSV2_BYTES];
	u8 id[TQC_EE_BDID_BYTES];		/* 0x40 ... 0x7f */
};

int tqc_parse_eeprom_mac(struct tqc_eeprom_data * const eeprom, char *buf,
			 size_t len);

int tqc_parse_eeprom_serial(struct tqc_eeprom_data * const eeprom, char *buf,
			    size_t len);
int tqc_parse_eeprom_id(struct tqc_eeprom_data * const eeprom, char *buf,
			size_t len);
int tqc_show_eeprom(struct tqc_eeprom_data *const eeprom, const char *id);
int tqc_read_eeprom_at(unsigned int bus, unsigned int i2c_addr,
		       unsigned int alen, unsigned int addr,
		       struct tqc_eeprom_data *eeprom);
int tqc_board_handle_eeprom_data(const char *board_name,
				 struct tqc_eeprom_data * const eeprom);

#if defined(CONFIG_SYS_I2C_EEPROM_ADDR_LEN)
int tqc_read_eeprom(unsigned int bus, unsigned int addr,
		    struct tqc_eeprom_data *eeprom);
#endif /* CONFIG_SYS_I2C_EEPROM_ADDR_LEN */

#endif /* CONFIG_SPL_BUILD */

#endif
