/**
 * @file
 * @brief Low-Level Debug NS16550 Driver implementation
 *
 * FileName: drivers/serial/serial_ns16550.c
 *
 * NS16550 support
 * Modified from u-boot drivers/serial.c and drivers/ns16550.c
 * originally from linux source (arch/ppc/boot/ns16550.c)
 * modified to use CFG_ISA_MEM and new defines
 */
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <common.h>
#include <driver.h>
#include <init.h>
#include <malloc.h>
#include <linux/clk.h>

#include <debug_ll.h>
#include <platform_data/serial-ns16550.h>

struct ll_ns16550_priv {
	struct console_device cdev;
	struct NS16550_plat plat;
	struct clk *clk;
};

static inline struct ll_ns16550_priv *to_ll_ns16550_priv(
						    struct console_device *cdev)
{
	return container_of(cdev, struct ll_ns16550_priv, cdev);
}


/**
 * @brief Set the baudrate for the uart port
 *
 * @param[in] cdev  console device
 * @param[in] baud_rate baud rate to set
 *
 * @return  0-implied to support the baudrate
 */
static int ll_ns16550_setbaudrate(struct console_device *cdev, int baud_rate)
{
	return 0;
}

/*********** Exposed Functions **********************************/

/**
 * @brief Put a character to the serial port
 *
 * @param[in] cdev pointer to console device
 * @param[in] c character to put
 */
static void ll_ns16550_putc(struct console_device *cdev, char c)
{
	putc_ll(c);
}

/**
 * @brief Retrieve a character from serial port
 *
 * @param[in] cdev pointer to console device
 *
 * @return return the character read
 */
static int ll_ns16550_getc(struct console_device *cdev)
{
	return getc_ll();
}

/**
 * @brief Test if character is available
 *
 * @param[in] cdev pointer to console device
 *
 * @return  - status based on data availability
 */
static int ll_ns16550_tstc(struct console_device *cdev)
{
	return tstc_ll();
}

static void ll_ns16550_probe_dt(struct device_d *dev,
				struct ll_ns16550_priv *priv)
{
	struct device_node *np = dev->device_node;

	if (!IS_ENABLED(CONFIG_OFDEVICE))
		return;

	of_property_read_u32(np, "clock-frequency", &priv->plat.clock);
	of_property_read_u32(np, "reg-shift", &priv->plat.shift);
}

/**
 * @brief Probe entry point -called on the first match for device
 *
 * @param[in] dev matched device
 *
 * @return EINVAL if platform_data is not populated,
 *	   ENOMEM if calloc failed
 *	   else return result of console_register
 */
static int ll_ns16550_probe(struct device_d *dev)
{
	struct ll_ns16550_priv *priv;
	struct console_device *cdev;
	struct NS16550_plat *plat = (struct NS16550_plat *)dev->platform_data;
	int ret;

	priv = xzalloc(sizeof(*priv));
	if (plat)
		priv->plat = *plat;
	else
		ll_ns16550_probe_dt(dev, priv);

	if (!priv->plat.clock) {
		priv->clk = clk_get(dev, NULL);
		if (IS_ERR(priv->clk)) {
			ret = PTR_ERR(priv->clk);
			dev_err(dev, "failed to get clk (%d)\n", ret);
			goto err;
		}
		clk_enable(priv->clk);
		priv->plat.clock = clk_get_rate(priv->clk);
	}

	if (priv->plat.clock == 0) {
		dev_err(dev, "no valid clockrate\n");
		ret = -EINVAL;
		goto err;
	}

	cdev = &priv->cdev;
	cdev->dev = dev;
	cdev->tstc = ll_ns16550_tstc;
	cdev->putc = ll_ns16550_putc;
	cdev->getc = ll_ns16550_getc;
	cdev->setbrg = ll_ns16550_setbaudrate;
	cdev->linux_console_name = "ttyS";

	return console_register(cdev);

err:
	free(priv);

	return ret;
}

static struct of_device_id ll_ns16550_serial_dt_ids[] = {
	{
		.compatible = "ll-ns16550a",
	},
};

/**
 * @brief Driver registration structure
 */
static struct driver_d ll_ns16550_serial_driver = {
	.name = "ll_ns16550_serial",
	.probe = ll_ns16550_probe,
	.of_compatible = DRV_OF_COMPAT(ll_ns16550_serial_dt_ids),
};
console_platform_driver(ll_ns16550_serial_driver);
