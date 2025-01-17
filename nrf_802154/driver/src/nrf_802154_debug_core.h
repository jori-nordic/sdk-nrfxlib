/*
 * Copyright (c) 2019 - 2022, Nordic Semiconductor ASA
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 * @brief Module that contains debug helpers for the 802.15.4 radio driver for the nRF SoC devices.
 *
 */

#ifndef NRF_802154_DEBUG_CORE_H_
#define NRF_802154_DEBUG_CORE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PIN_DBG_TIMESLOT_ACTIVE       3
#define PIN_DBG_TIMESLOT_EXTEND_REQ   4
#define PIN_DBG_TIMESLOT_SESSION_IDLE 16
#define PIN_DBG_TIMESLOT_RADIO_IRQ    28
#define PIN_DBG_TIMESLOT_FAILED       29
#define PIN_DBG_TIMESLOT_BLOCKED      30
#define PIN_DBG_RAAL_CRITICAL_SECTION 15

#define PIN_DBG_RTC0_EVT_REM          31

#if ENABLE_DEBUG_GPIO

#define NRF_802154_DEBUG_CORE_PINS_USED ((1 << PIN_DBG_TIMESLOT_ACTIVE) |       \
                                         (1 << PIN_DBG_TIMESLOT_EXTEND_REQ) |   \
                                         (1 << PIN_DBG_TIMESLOT_SESSION_IDLE) | \
                                         (1 << PIN_DBG_TIMESLOT_RADIO_IRQ) |    \
                                         (1 << PIN_DBG_TIMESLOT_FAILED) |       \
                                         (1 << PIN_DBG_TIMESLOT_BLOCKED) |      \
                                         (1 << PIN_DBG_RAAL_CRITICAL_SECTION))

#else // ENABLE_DEBUG_GPIO

#define NRF_802154_DEBUG_CORE_PINS_USED 0

#endif

#if ENABLE_DEBUG_GPIO

#define nrf_802154_pin_set(pin) NRF_P0->OUTSET = (1UL << (pin))
#define nrf_802154_pin_clr(pin) NRF_P0->OUTCLR = (1UL << (pin))
#define nrf_802154_pin_tgl(pin)                  \
    do                                           \
    {                                            \
        volatile uint32_t ps = NRF_P0->OUT;      \
                                                 \
        NRF_P0->OUTSET = (~ps & (1UL << (pin))); \
        NRF_P0->OUTCLR = (ps & (1UL << (pin)));  \
    }                                            \
    while (0);

#else // ENABLE_DEBUG_GPIO

#define nrf_802154_pin_set(pin)
#define nrf_802154_pin_clr(pin)
#define nrf_802154_pin_tgl(pin)

#endif // ENABLE_DEBUG_GPIO

#ifdef __cplusplus
}
#endif

#endif /* NRF_802154_DEBUG_CORE_H_ */
