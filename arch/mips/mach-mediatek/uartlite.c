/*
 * Copyright (C) 2017 Gaël PORTAY <gael.portay@savoirfairelinux.com>
 *
 * This file is part of barebox.
 * See file CREDITS for list of people who contributed to this project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */

#include <common.h>
#include <init.h>
#include <board/debug_ll.h>
#include <platform_data/serial-ns16550.h>

static struct NS16550_plat uartlite_plat = {
	.clock = MT7628_UARTLITE_CLK,
	.shift = DEBUG_LL_UART_SHIFT,
};

static int mt7828_uartlite_init(void)
{
	struct device_d *dev;

	dev = add_ns16550_device(DEVICE_ID_DYNAMIC, DEBUG_LL_UART_ADDR, 0xf,
				 IORESOURCE_MEM | IORESOURCE_MEM_8BIT,
				 &uartlite_plat);
	return 0;
}
console_initcall(mt7828_uartlite_init);
