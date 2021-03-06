/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */


#include "contiki.h"
#include <stdio.h>
#include "sys/ctimer.h"
#include "sys/etimer.h"

PROCESS(test_timers, "Test timers");
AUTOSTART_PROCESSES(&test_timers);

static struct ctimer ct;
static int ctimer_period_counter = 0;

static void print_seconds_gone(void *ptr){
	ctimer_period_counter += 10;
	printf("%d seconds are gone\n", *(int*)ptr);
	ctimer_set(&ct, 10 * CLOCK_SECOND, print_seconds_gone, &ctimer_period_counter);
}

PROCESS_THREAD(test_timers, ev, data){
	static struct etimer et;
	static int sec_counter = 0;

	PROCESS_BEGIN();
	etimer_set(&et, 3*CLOCK_SECOND);
	ctimer_set(&ct, 10 * CLOCK_SECOND, print_seconds_gone, &ctimer_period_counter);

	while(1){
		PROCESS_YIELD();
		if (ev == PROCESS_EVENT_TIMER){
			if(etimer_expired(&et)){
				sec_counter += 1;
				printf("%d seconds are elapsed\n", sec_counter*3); etimer_restart(&et);
			}
		}
	}
	PROCESS_END();
}
