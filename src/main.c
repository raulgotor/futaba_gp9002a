/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   100
#define SLEEP_TIME_MS_one   1

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <stdio.h>
#include <string.h>

#define SPIBB_NODE      DT_NODELABEL(arduino_spi)
#define GPIOA_NODE      DT_NODELABEL(gpioa)

#define CD_PIN          (9)
#define DISPLAY_MODE 0x14
#define DISPLAY_OR_1_2 0x10
#define MONOCHROME 0x10
#define DISPLAY_1_ON 0x01
#define DISPLAY_2_ON 0x02
#define LOWER_ADDR_START_1 0x0A
#define UPPER_ADDR_START_1 0x0B
#define LOWER_ADDR_START_2 0x0C
#define UPPER_ADDR_START_2 0x0D
#define CLEAR 0x06
#define HELD 0x05
#define NO_HELD 0x04
#define WRITE_DATA 0x08


const struct device *const dev = DEVICE_DT_GET(SPIBB_NODE);
const struct device *const gpioa = DEVICE_DT_GET(GPIOA_NODE);

struct spi_cs_control cs_ctrl = (struct spi_cs_control){
        .gpio = GPIO_DT_SPEC_GET(SPIBB_NODE, cs_gpios),
        .delay = 0u,
};

struct spi_config spi_cfg = {
        .frequency = 500000U,
        .operation = SPI_WORD_SET(8) | SPI_TRANSFER_LSB | SPI_OP_MODE_MASTER,

        .cs = &cs_ctrl,

};

int write(uint8_t const * const p_data, size_t const size, bool is_cmd)
{
        int ret;
        int cmd = is_cmd ? 1 : 0;

        struct spi_buf bufs[] = {
                {
                        .buf = p_data,
                        .len = size
                },
        };

        struct spi_buf_set tx = {
                .buffers =  bufs,
                .count = 1
        };

        ret = gpio_pin_set(gpioa, CD_PIN, cmd);
        if (0 == ret) {
                ret = spi_write(dev, &spi_cfg, &tx);
        }
        k_msleep(SLEEP_TIME_MS_one);

        return ret;
}

int write_cmd(uint8_t const * const p_data, size_t const size)
{
        return write(p_data, size, true);
}

int write_data(uint8_t const * const p_data, size_t const size)
{
        return write(p_data, size, false);
}

int write_one_byte_cmd(uint8_t byte)
{
        return write_cmd(&byte, 1);
}

int write_one_byte_data(uint8_t byte)
{
        return write_data(&byte, 1);
}

void init(void)
{
        write_one_byte_cmd(DISPLAY_MODE);
        write_one_byte_data(MONOCHROME);

        write_one_byte_cmd(LOWER_ADDR_START_1);
        write_one_byte_data(0x00);

        write_one_byte_cmd(UPPER_ADDR_START_1);
        write_one_byte_data(0x00);

        write_one_byte_cmd(LOWER_ADDR_START_2);
        write_one_byte_data(0x00);

        write_one_byte_cmd(UPPER_ADDR_START_2);
        write_one_byte_data(0x04);

        write_one_byte_cmd(DISPLAY_OR_1_2);
        write_one_byte_cmd(CLEAR);
        write_one_byte_cmd(DISPLAY_1_ON);
        write_one_byte_cmd(HELD);

}

void draw_pixel(uint8_t const x, uint8_t const y)
{
        uint16_t address = x * 8 + (63 - y) / 8;
        uint8_t const bit = 0x01 << (y % 8);

        write_one_byte_cmd(0xE);
        write_one_byte_data(address);

        write_one_byte_cmd(0xF);
        write_one_byte_data(address >> 8);

        write_one_byte_cmd(WRITE_DATA);
        write_one_byte_data(bit);
}

void main(void)
{
	if (!gpio_is_ready_dt(&led)) {
		return;
	}

        if (!gpio_is_ready_dt(&gpioa)) {
                return;
        }

        gpio_pin_configure(gpioa, CD_PIN, GPIO_OUTPUT);

        init();

        int i = 0;
	while (1) {
                i++;
		k_msleep(100);
                draw_pixel(i, i);
        }
}