/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 2014 - 2018 SEGGER Microcontroller GmbH             *
*                                                                    *
*           www.segger.com     Support: support@segger.com           *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* conditions are met:                                                *
*                                                                    *
* - Redistributions of source code must retain the above copyright   *
*   notice, this list of conditions and the following disclaimer.    *
*                                                                    *
* - Neither the name of SEGGER Microcontroller GmbH                  *
*   nor the names of its contributors may be used to endorse or      *
*   promote products derived from this software without specific     *
*   prior written permission.                                        *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED.                                                        *
* IN NO EVENT SHALL SEGGER Microcontroller GmbH BE LIABLE FOR        *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main.c
Purpose : Generic application start

*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "app_timer.h"
#include "sdk_common.h"
#include "nrf_drv_clock.h"
#include "nrf_delay.h"
#include "boards.h"
#include "ndn-lite-timer.h"

static ndn_timer_t op;

/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
*/


void on_timer_timeout1(void* timer_context)
{
  (void)timer_context;

  bsp_board_led_off(BSP_BOARD_LED_0);
  ndn_timer_stop(op.abs_timer);
}

void on_timer_timeout2(void* timer_context)
{
  (void)timer_context;

  bsp_board_led_off(BSP_BOARD_LED_1);

}

void on_timer_timeout3(void* timer_context)
{
  (void)timer_context;

  bsp_board_led_on(BSP_BOARD_LED_1);

}

void main(void) {
  bsp_board_init(BSP_INIT_LEDS);
  ndn_timer_init();

  void* timer_context;
  ndn_timer_start(30000, timer_context, on_timer_timeout1);
  ndn_timer_start(20000, timer_context, on_timer_timeout2);
  op.timer_id = 1234;
  op.abs_timer = ndn_timer_start(50000, timer_context, on_timer_timeout3);

  bsp_board_led_on(BSP_BOARD_LED_0);
  bsp_board_led_on(BSP_BOARD_LED_1);

}


/*************************** End of file ****************************/