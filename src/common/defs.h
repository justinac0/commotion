#ifndef DEFS_H
#define DEFS_H

#include <raylib.h>

// WINDOW CONSTANTS
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (480)
#define HALF_SCREEN_WIDTH (SCREEN_WIDTH / 2)
#define HALF_SCREEN_HEIGHT (SCREEN_HEIGHT / 2)

// MISC CONSTANTS
#define METER_SCALE_PX (1)

// TYPES
typedef double real;

// PHYSICAL CONSTANTS
#define G ((real) 6.67430E-11)
#define EARTH_MASS ((real) 5.972E24)
#define EARTH_RADIUS ((real) 6371E3)
#define MOON_MASS ((real) 7.35E22)
#define MOON_RADIUS ((real) 1737.5E3)
#define LUNAR_DISTANCE ((real) 385000E3)

#endif // DEFS_H