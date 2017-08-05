// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2017 Gaël PORTAY <gael.portay@savoirfairelinux.com>
 */

#include <common.h>
#include <init.h>
#include <debug_ll.h>

static int console_ll_tstc(struct console_device *cdev)
{
	return tstc_ll();
}

static void console_ll_putc(struct console_device *cdev, char c)
{
	putc_ll(c);
}

static int console_ll_puts(struct console_device *cdev, const char *s)
{
	puts_ll(s);
	return 0;
}

static int console_ll_getc(struct console_device *cdev)
{
	return getc_ll();
}

static struct console_device console_ll = {
	.tstc = console_ll_tstc,
	.putc = console_ll_putc,
	.puts = console_ll_puts,
	.getc = console_ll_getc,
	.devname = "console_ns16550_ll",
	.devid = 0,
	.baudrate = CONFIG_BAUDRATE,
	.linux_console_name = "ttyS",
};

static int mt7828_console_ll_init(void)
{
	pr_info("low-level console\n");

	return console_register(&console_ll);
}
console_initcall(mt7828_console_ll_init);
