#ifndef ORIENTATION_H
#define ORIENTATION_H
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
#include <QtTypes>
#else
#include <QtGlobal>
#endif

/**
 * @file
 *
 * @brief The header containing the @ref Orientation
 * @author Felix Fehlauer
 */

/**
 * @enum Orientation
 *
 * @brief The possible orientations of a position
 *
 * This describes the "Himmelsrichtung" part of the board positions
 * @var Orientation::Nord
 * north
 * @var Orientation::Nordost
 * northeast
 * @var Orientation::Ost
 * east
 * @var Orientation::Suedost
 * southeast
 * @var Orientation::Sued
 * south
 * @var Orientation::Suedwest
 * southwest
 * @var Orientation::West
 * west
 * @var Orientation::Nordwest
 * northwest
 */
enum class Orientation : quint8 { Nord=1, Nordost=2, Ost=3, Suedost=4, Sued=5, Suedwest=6, West=7, Nordwest=8 };

#endif // ORIENTATION_H
