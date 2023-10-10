// Copyright 2020 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "soc/soc.h"
#include "soc/rtc.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/syscon_reg.h"
#include "esp_attr.h"

#ifdef __cplusplus
extern "C" {
#endif

FORCE_INLINE_ATTR void rtc_cntl_ll_set_wakeup_timer(uint64_t t)
{
    WRITE_PERI_REG(RTC_CNTL_SLP_TIMER0_REG, t & UINT32_MAX);
    WRITE_PERI_REG(RTC_CNTL_SLP_TIMER1_REG, t >> 32);

    SET_PERI_REG_MASK(RTC_CNTL_INT_CLR_REG, RTC_CNTL_MAIN_TIMER_INT_CLR_M);
    SET_PERI_REG_MASK(RTC_CNTL_SLP_TIMER1_REG, RTC_CNTL_MAIN_TIMER_ALARM_EN_M);
}

FORCE_INLINE_ATTR uint32_t rtc_cntl_ll_gpio_get_wakeup_status(void)
{
    return GET_PERI_REG_MASK(RTC_CNTL_GPIO_WAKEUP_REG, RTC_CNTL_GPIO_WAKEUP_STATUS);
}

FORCE_INLINE_ATTR void rtc_cntl_ll_gpio_clear_wakeup_status(void)
{
    REG_SET_BIT(RTC_CNTL_GPIO_WAKEUP_REG, RTC_CNTL_GPIO_WAKEUP_STATUS_CLR);
    REG_CLR_BIT(RTC_CNTL_GPIO_WAKEUP_REG, RTC_CNTL_GPIO_WAKEUP_STATUS_CLR);
}

FORCE_INLINE_ATTR void rtc_cntl_ll_set_cpu_retention_link_addr(uint32_t addr)
{
    REG_SET_FIELD(SYSCON_RETENTION_CTRL_REG, SYSCON_RETENTION_LINK_ADDR, (uint32_t)addr);
}

FORCE_INLINE_ATTR void rtc_cntl_ll_enable_cpu_retention_clock(void)
{
    REG_SET_BIT(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_DIG_CLK8M_EN);
}

FORCE_INLINE_ATTR void rtc_cntl_ll_enable_cpu_retention(void)
{
    /* Enable retention when cpu sleep enable */
    REG_SET_BIT(RTC_CNTL_RETENTION_CTRL_REG, RTC_CNTL_RETENTION_EN);
}

FORCE_INLINE_ATTR void rtc_cntl_ll_disable_cpu_retention(void)
{
    REG_CLR_BIT(RTC_CNTL_RETENTION_CTRL_REG, RTC_CNTL_RETENTION_EN);
}

FORCE_INLINE_ATTR void rtc_cntl_ll_sleep_enable(void)
{
    SET_PERI_REG_MASK(RTC_CNTL_STATE0_REG, RTC_CNTL_SLEEP_EN);
}

FORCE_INLINE_ATTR uint64_t rtc_cntl_ll_get_rtc_time(void)
{
    SET_PERI_REG_MASK(RTC_CNTL_TIME_UPDATE_REG, RTC_CNTL_TIME_UPDATE);
    uint64_t t = READ_PERI_REG(RTC_CNTL_TIME0_REG);
    t |= ((uint64_t) READ_PERI_REG(RTC_CNTL_TIME1_REG)) << 32;
    return t;
}

FORCE_INLINE_ATTR uint64_t rtc_cntl_ll_time_to_count(uint64_t time_in_us)
{
    uint32_t slow_clk_value = REG_READ(RTC_CNTL_STORE1_REG);
    return ((time_in_us * (1 << RTC_CLK_CAL_FRACT)) / slow_clk_value);
}

FORCE_INLINE_ATTR uint32_t rtc_cntl_ll_get_wakeup_cause(void)
{
    return REG_GET_FIELD(RTC_CNTL_SLP_WAKEUP_CAUSE_REG, RTC_CNTL_WAKEUP_CAUSE);
}

#ifdef __cplusplus
}
#endif
