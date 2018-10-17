// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2011 Antony Pavlov <antonynpavlov@gmail.com>
 */

/**
 * @file
 * @brief Clocksource based on MIPS CP0 timer
 */

#include <init.h>
#include <of.h>
#include <linux/clk.h>
#include <clock.h>
#include <io.h>
#include <asm/mipsregs.h>

static uint64_t c0_hpt_read(void)
{
	return read_c0_count();
}

static struct clocksource cs = {
	.read	= c0_hpt_read,
	.mask	= CLOCKSOURCE_MASK(32),
};

static int clocksource_init(void)
{
	unsigned int mips_hpt_frequency = CONFIG_CSRC_R4K_HPT_FREQUENCY/2;
	struct device_node *np;
	struct clk *clk;

	if (IS_ENABLED(CONFIG_OFTREE)) {
		np = of_get_cpu_node(0, NULL);
		if (np) {
			clk = of_clk_get(np, 0);
			if (!IS_ERR(clk)) {
				mips_hpt_frequency = clk_get_rate(clk) / 2;
			}
		}
	}

	clocks_calc_mult_shift(&cs.mult, &cs.shift,
		mips_hpt_frequency, NSEC_PER_SEC, 10);

	return init_clock(&cs);
}
postcore_initcall(clocksource_init);
