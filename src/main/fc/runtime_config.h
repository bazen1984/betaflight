/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "common/utils.h"

// FIXME some of these are flight modes, some of these are general status indicators
typedef enum {
    ARMED                       = (1 << 0),
    WAS_EVER_ARMED              = (1 << 1),
    WAS_ARMED_WITH_PREARM       = (1 << 2)
} armingFlag_e;

extern uint8_t armingFlags;

#define DISABLE_ARMING_FLAG(mask) (armingFlags &= ~(mask))
#define ENABLE_ARMING_FLAG(mask) (armingFlags |= (mask))
#define ARMING_FLAG(mask) (armingFlags & (mask))

    ARMING_DISABLED_GPS             = (1 << 18),
    ARMING_DISABLED_RESC            = (1 << 19),
    ARMING_DISABLED_RPMFILTER       = (1 << 20),
    ARMING_DISABLED_REBOOT_REQUIRED = (1 << 21),
    ARMING_DISABLED_DSHOT_BITBANG   = (1 << 22),
    ARMING_DISABLED_ACC_CALIBRATION = (1 << 23),
    ARMING_DISABLED_MOTOR_PROTOCOL  = (1 << 24),
    ARMING_DISABLED_ARM_SWITCH      = (1 << 25), // Needs to be the last element, since it's always activated if one of the others is active when arming
} armingDisableFlags_e;

#define ARMING_DISABLE_FLAGS_COUNT (LOG2(ARMING_DISABLED_ARM_SWITCH) + 1)

extern const char *armingDisableFlagNames[ARMING_DISABLE_FLAGS_COUNT];

void setArmingDisabled(armingDisableFlags_e flag);
void unsetArmingDisabled(armingDisableFlags_e flag);
bool isArmingDisabled(void);
armingDisableFlags_e getArmingDisableFlags(void);

typedef enum {
    ANGLE_MODE      = (1 << 0),
    HORIZON_MODE    = (1 << 1),
    MAG_MODE        = (1 << 2),
//    BARO_MODE       = (1 << 3),
//    GPS_HOME_MODE   = (1 << 4),
//    GPS_HOLD_MODE   = (1 << 5),
    HEADFREE_MODE   = (1 << 6),
//    UNUSED_MODE     = (1 << 7), // old autotune
    PASSTHRU_MODE   = (1 << 8),
//    RANGEFINDER_MODE= (1 << 9),
    FAILSAFE_MODE   = (1 << 10),
    GPS_RESCUE_MODE = (1 << 11)
} flightModeFlags_e;

extern uint16_t flightModeFlags;

#define DISABLE_FLIGHT_MODE(mask) disableFlightMode(mask)
#define ENABLE_FLIGHT_MODE(mask) enableFlightMode(mask)
#define FLIGHT_MODE(mask) (flightModeFlags & (mask))

// macro to initialize map from boxId_e to log2(flightModeFlags). Keep it in sync with flightModeFlags_e enum.
// [BOXARM] is left unpopulated
#define BOXID_TO_FLIGHT_MODE_MAP_INITIALIZER {           \
   [BOXANGLE]       = LOG2(ANGLE_MODE),                  \
   [BOXHORIZON]     = LOG2(HORIZON_MODE),                \
   [BOXMAG]         = LOG2(MAG_MODE),                    \
   [BOXHEADFREE]    = LOG2(HEADFREE_MODE),               \
   [BOXPASSTHRU]    = LOG2(PASSTHRU_MODE),               \
   [BOXFAILSAFE]    = LOG2(FAILSAFE_MODE),               \
   [BOXGPSRESCUE]   = LOG2(GPS_RESCUE_MODE),             \
}                                                        \
/**/

typedef enum {
    GPS_FIX_HOME   = (1 << 0),
    GPS_FIX        = (1 << 1),
} stateFlags_t;

#define DISABLE_STATE(mask) (stateFlags &= ~(mask))
#define ENABLE_STATE(mask) (stateFlags |= (mask))
#define STATE(mask) (stateFlags & (mask))

extern uint8_t stateFlags;

uint16_t enableFlightMode(flightModeFlags_e mask);
uint16_t disableFlightMode(flightModeFlags_e mask);

bool sensors(uint32_t mask);
void sensorsSet(uint32_t mask);
void sensorsClear(uint32_t mask);
uint32_t sensorsMask(void);

void mwDisarm(void);
