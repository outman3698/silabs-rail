/***************************************************************************//**
 * @file hal_common.h
 * @brief This is the header file for common HAL functionality.
 * @copyright Copyright 2015 Silicon Laboratories, Inc. http://www.silabs.com
 ******************************************************************************/

#ifndef _HAL_COMMON_H_
#define _HAL_COMMON_H_

#include "rail_types.h"

void halInit(void);

uint32_t halCommonGetInt32uMillisecondTick(void);
void halCommonDelayMicroseconds(uint16_t us);

void halCommonMemMove(void *dest, const void *src, uint16_t bytes);

/**
 * @brief Returns the elapsed time between two 32 bit values.  
 *   Result may not be valid if the time samples differ by more than 2147483647
 */
#define elapsedTimeInt32u(oldTime, newTime)      \
  ((uint32_t) ((uint32_t)(newTime) - (uint32_t)(oldTime)))

#endif
