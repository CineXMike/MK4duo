/**
 * MK4duo Firmware for 3D Printer, Laser and CNC
 *
 * Based on Marlin, Sprinter and grbl
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 * Copyright (C) 2019 Alberto Cotronei @MagoKimbra
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * bltouch.h
 *
 * Copyright (C) 2019 Alberto Cotronei @MagoKimbra
 */

#if ENABLED(BLTOUCH)

#define BLTOUCH_DEPLOY     10
#define BLTOUCH_SW_MODE    60
#define BLTOUCH_STOW       90
#define BLTOUCH_SELFTEST  120
#define BLTOUCH_5V_MODE   140
#define BLTOUCH_OD_MODE   150
#define BLTOUCH_RESET     160

/**
 * The following commands may require different delays.
 *
 * ANTClabs recommends 2000ms for 5V/OD commands. However it is
 * not common for other commands to immediately follow these,
 * and testing has shown that these complete in 500ms reliably.
 *
 * AntClabs recommends 750ms for Deploy/Stow, otherwise you will
 * not catch an alarm state until the following move command.
 */

typedef unsigned char BLTCommand;

class BLTouch {

  public: /** Constructor */

    BLTouch() {};

  public: /** Public Function */

    static void init();
    static bool test();

    static bool deploy();
    static bool stow();
    static bool status();

    FORCE_INLINE static bool set_deployed(const bool dep) { if (dep) return deploy(); else return stow(); }

    FORCE_INLINE static void cmd_reset()    { (void)command(BLTOUCH_RESET);     }
    FORCE_INLINE static void cmd_selftest() { (void)command(BLTOUCH_SELFTEST);  }

    FORCE_INLINE static void cmd_SW_mode()  { (void)command(BLTOUCH_SW_MODE);   }
    FORCE_INLINE static void cmd_5V_mode()  { (void)command(BLTOUCH_5V_MODE);   }
    FORCE_INLINE static void cmd_OD_mode()  { (void)command(BLTOUCH_OD_MODE);   }

    FORCE_INLINE static void cmd_deploy()   { (void)command(BLTOUCH_DEPLOY);    }
    FORCE_INLINE static void cmd_stow()     { (void)command(BLTOUCH_STOW);      }

  private: /** Private Function */

    static void clear();
    static bool command(const BLTCommand cmd);

    FORCE_INLINE static bool cmd_deploy_alarm() { return command(BLTOUCH_DEPLOY); }
    FORCE_INLINE static bool cmd_stow_alarm()   { return command(BLTOUCH_STOW);   }

};

extern BLTouch bltouch;

#endif // ENABLED(BLTOUCH)
