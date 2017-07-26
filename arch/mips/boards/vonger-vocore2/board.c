// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2017 Gaël PORTAY <gael.portay@savoirfairelinux.com>
 */

#include <common.h>
#include <init.h>

static int vocore2_board_init(void)
{
	barebox_set_model("Vonger VoCore 2");
	barebox_set_hostname("vocore2");

	return 0;
}
postcore_initcall(vocore2_board_init);
