#ifndef MOVEORIENTATION_H
#define MOVEORIENTATION_H
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
#include <QtTypes>
#else
#include <QtGlobal>
#endif

/**
 * @file
 *
 * @brief The header containing the @ref MoveOrientation
 * @author Felix Fehlauer
 */

/**
 * @enum MoveOrientation
 *
 * @brief The possible directions to move in
 *
 * This is a subset of the @ref Orientation in which a move can potentially take place
 * @var MoveOrientation::Nord
 * north
 * @var MoveOrientation::Ost
 * east
 * @var MoveOrientation::Sued
 * south
 * @var MoveOrientation::West
 * west
 */
enum class MoveOrientation : quint8 { Nord=1, Ost=3, Sued=5, West=7 };

#endif // MOVEORIENTATION_H
