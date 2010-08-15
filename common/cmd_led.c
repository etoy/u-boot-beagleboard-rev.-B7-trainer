/*
 * (C) Copyright 2010
 * Jason Kridner <jkridner@beagleboard.org>
 *
 * Based on cmd_led.c patch from:
 * http://www.mail-archive.com/u-boot@lists.denx.de/msg06873.html
 * (C) Copyright 2008
 * Ulf Samuelsson <ulf.samuelsson@atmel.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * This file provides a shell like 'test' function to return
 * true/false from an integer or string compare of two memory
 * locations or a location and a scalar/literal.
 * A few parts were lifted from bash 'test' command
 */

#include <common.h>
#include <config.h>
#include <command.h>
#include <status_led.h>

int do_led ( cmd_tbl_t *cmdtp, int flag, int argc, char *argv[] )
{
#ifdef CONFIG_BOARD_SPECIFIC_LED
	led_id_t mask;
#endif
	int state;

	/* Validate arguments */
	if ((argc != 3)){
		printf("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

	if (strcmp(argv[2], "off") == 0) {
		state = 0;
	} else if (strcmp(argv[2], "on") == 0) {
		state = 1;
	} else {
		printf ("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

#if defined(STATUS_LED_BIT) && defined(CONFIG_BOARD_SPECIFIC_LED)
	if (strcmp(argv[1], "0") == 0) {
		mask = STATUS_LED_BIT;
		__led_set(mask, state);
	}
	else
#endif
#if defined(STATUS_LED_BIT1) && defined(CONFIG_BOARD_SPECIFIC_LED)
	if (strcmp(argv[1], "1") == 0) {
		mask = STATUS_LED_BIT1;
		__led_set(mask, state);
	}
	else
#endif
#if defined(STATUS_LED_BIT2) && defined(CONFIG_BOARD_SPECIFIC_LED)
	if (strcmp(argv[1], "2") == 0) {
		mask = STATUS_LED_BIT2;
		__led_set(mask, state);
	}
	else
#endif
#if defined(STATUS_LED_BIT3) && defined(CONFIG_BOARD_SPECIFIC_LED)
	if (strcmp(argv[1], "3") == 0) {
		mask = STATUS_LED_BIT3;
		__led_set(mask, state);
	}
	else
#endif
#ifdef STATUS_LED_RED
	if (strcmp(argv[1], "red") == 0) {
		if (state == 0)
			red_LED_off();
		else
			red_LED_on();
	}
	else
#endif
#ifdef STATUS_LED_GREEN
	if (strcmp(argv[1], "green") == 0) {
		if (state == 0)
			green_LED_off();
		else
			green_LED_on();
	}
	else
#endif
#ifdef STATUS_LED_YELLOW
	if (strcmp(argv[1], "yellow") == 0) {
		if (state == 0)
			yellow_LED_off();
		else
			yellow_LED_on();
	}
	else
#endif
#ifdef STATUS_LED_BLUE
	if (strcmp(argv[1], "blue") == 0) {
		if (state == 0)
			blue_LED_off();
		else
			blue_LED_on();
	}
	else
#endif
	if (strcmp(argv[1], "all") == 0) {
		mask = 0
#if defined(STATUS_LED_BIT) && defined(CONFIG_BOARD_SPECIFIC_LED)
			| STATUS_LED_BIT
#endif
#if defined(STATUS_LED_BIT1) && defined(CONFIG_BOARD_SPECIFIC_LED)
			| STATUS_LED_BIT1
#endif
#if defined(STATUS_LED_BIT2) && defined(CONFIG_BOARD_SPECIFIC_LED)
			| STATUS_LED_BIT2
#endif
#if defined(STATUS_LED_BIT3) && defined(CONFIG_BOARD_SPECIFIC_LED)
			| STATUS_LED_BIT3
#endif
			;
#ifdef CONFIG_BOARD_SPECIFIC_LED
		__led_set(mask, state);
#endif
#ifdef STATUS_LED_RED
		if (state == 0)
			red_LED_off();
		else
			red_LED_on();
#endif
#ifdef STATUS_LED_GREEN
		if (state == 0)
			green_LED_off();
		else
			green_LED_on();
#endif
#ifdef STATUS_LED_YELLOW
		if (state == 0)
			yellow_LED_off();
		else
			yellow_LED_on();
#endif
#ifdef STATUS_LED_BLUE
		if (state == 0)
			blue_LED_off();
		else
			blue_LED_on();
#endif
	} else {
		printf ("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

	return 0;
}

U_BOOT_CMD(
	led, 3, 1, do_led,
	"led\t- ["
#if defined(STATUS_LED_BIT) && defined(CONFIG_BOARD_SPECIFIC_LED)
	"0|"
#endif
#if defined(STATUS_LED_BIT1) && defined(CONFIG_BOARD_SPECIFIC_LED)
	"1|"
#endif
#if defined(STATUS_LED_BIT2) && defined(CONFIG_BOARD_SPECIFIC_LED)
	"2|"
#endif
#if defined(STATUS_LED_BIT3) && defined(CONFIG_BOARD_SPECIFIC_LED)
	"3|"
#endif
#ifdef STATUS_LED_GREEN
	"green|"
#endif
#ifdef STATUS_LED_YELLOW
	"yellow|"
#endif
#ifdef STATUS_LED_RED
	"red|"
#endif
#ifdef STATUS_LED_BLUE
	"blue|"
#endif
	"all] [on|off]\n",
	"led [led_name] [on|off] sets or clears led(s)\n"
);

