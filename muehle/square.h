#ifndef SQUARE_H
#define SQUARE_H
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
#include <QtTypes>
#else
#include <QtGlobal>
#endif

/**
 * @file
 *
 * @brief The header containing the @ref Square
 * @author Felix Fehlauer
 */

/**
 * @enum Square
 *
 * @brief The possible squares of a position
 *
 * This describes the "Quadrat" part of the board positions
 * @var Square::Aussen
 * outside
 * @var Square::Mitte
 * middle
 * @var Square::Innen
 * inside
 */
enum class Square : quint8 { Aussen=1, Mitte=2, Innen=3 };

#endif // SQUARE_H
