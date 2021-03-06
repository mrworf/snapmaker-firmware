/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../../../inc/MarlinConfig.h"

#if HAS_FILAMENT_SENSOR

#include "../../gcode.h"
#include "../../../feature/runout.h"

/**
 * M412: Enable / Disable filament runout detection
 */
void GcodeSuite::M412() {
  if (parser.seen("RS"
    #if ENABLED(HOST_ACTION_COMMANDS)
      "H"
    #endif
  )) {
    #if ENABLED(HOST_ACTION_COMMANDS)
      if (parser.seen('H')) runout.host_handling = parser.value_bool();
    #endif
    const bool seenR = parser.seen('R'), seenS = parser.seen('S');
    if (seenR || seenS) runout.reset();
    // if user disable runout checking, clear execption
    if (seenS) {
      if (!parser.value_bool()) {
        if (runout.enabled) {
          SystemStatus.ClearExceptionByFaultFlag(FAULT_FLAG_FILAMENT);
          runout.enabled = false;
        }
      }
      else
        runout.enabled = true;
    }
  }
  else {
    SERIAL_ECHO_START();
    SERIAL_ECHOPGM("Filament runout ");
    serialprintln_onoff(runout.enabled);
  }
}

#endif // HAS_FILAMENT_SENSOR
