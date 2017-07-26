// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2017 Gaël PORTAY <gael.portay@savoirfairelinux.com>
 */

#include <common.h>
#include <init.h>

static int mt7628_mach_init(void)
{
	pr_info("Mediatek MT7628\n");

	return 0;
}
postcore_initcall(mt7628_mach_init);
