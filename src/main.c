/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include "gp9002a.h"
//#include "lvgl.h"

void main(void)
{
        gp9002a_init();

        gp9002a_draw_pixel(30, 2);
        gp9002a_draw_pixel(31, 2);
        gp9002a_draw_pixel(30, 3);
        gp9002a_draw_pixel(31, 3);
        gp9002a_draw_pixel(30, 4);
        gp9002a_draw_pixel(31, 4);
        gp9002a_draw_pixel(30, 5);
        gp9002a_draw_pixel(31, 5);
        gp9002a_draw_pixel(28, 2);
        gp9002a_draw_pixel(29, 2);
        gp9002a_draw_pixel(28, 3);
        gp9002a_draw_pixel(29, 3);
        gp9002a_draw_pixel(32, 2);
        gp9002a_draw_pixel(33, 2);
        gp9002a_draw_pixel(32, 3);
        gp9002a_draw_pixel(33, 3);
        gp9002a_draw_pixel(126, 2);
        gp9002a_draw_pixel(127, 2);
        gp9002a_draw_pixel(126, 3);
        gp9002a_draw_pixel(127, 3);
        gp9002a_draw_pixel(126, 60);
        gp9002a_draw_pixel(127, 61);
        gp9002a_draw_pixel(126, 60);
        gp9002a_draw_pixel(127, 61);

        for (;;){

                // lv_task_handler();
            k_msleep(100);

        }
}