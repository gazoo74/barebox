/*
 * Copyright (C) 2018 Gaël PORTAY <gael.portay@savoirfairelinux.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <common.h>
#include <io.h>
#include <init.h>
#include <restart.h>

/* System Control */
#define MT7628_SYSCTL_BASE	0xb0000000

/* Reset Control Register */
#define SYSCTL_RSTCTL_REG	0x034

/* Whole System Reset Control */
#define RSTCTL_SYS_RST_BIT	BIT(0)

static void __noreturn mt7628_restart_soc(struct restart_handler *rst)
{
	__raw_writel(RSTCTL_SYS_RST_BIT, MT7628_SYSCTL_BASE + SYSCTL_RSTCTL_REG);

	hang();
	/*NOTREACHED*/
}

static int restart_register_feature(void)
{
	restart_handler_register_fn(mt7628_restart_soc);

	return 0;
}
coredevice_initcall(restart_register_feature);
