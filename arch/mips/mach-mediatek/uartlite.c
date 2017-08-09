// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2017 Gaël PORTAY <gael.portay@savoirfairelinux.com>
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
