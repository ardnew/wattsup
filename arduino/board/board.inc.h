/*******************************************************************************
 * file: board.inc.h
 * proj: wattsup
 * desc: Preprocessor directives that include the target board.
 * copy: MIT License (c) 2022 andrew@ardnew.com
 *                                     ---
 * This file is manually created and maintained based on the targets supported
 * by this project.
 *
 * This file's sole purpose is to isolate the preprocessor logic that #include's
 * the correct header file(s) containing target pinout/wiring definitions.
 *
 * Aside from the files included below, all other source files must never use
 * target-specific code or make any decision based on compilation target.
 *
 * Instead, this file should be included before attempting to access any target-
 * specific pinout/wiring definitions.
 *
 * This file must NOT contain C/C++ source code or preprocessor definitions.
 ******************************************************************************/
#ifndef board_inc_h
#define board_inc_h

#if defined(ARDUINO_NRF52840_LED_GLASSES)
#include "adafruit/nrf52/ledglasses_nrf52840.h"
#endif

#endif // board_inc_h
