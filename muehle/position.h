#ifndef POSITION_H
#define POSITION_H

/**
 * @file
 *
 * @brief The header containing the @ref position constants
 *
 * It also includes definitions to be able to use enums in QHash in older Qt versions.
 * @author Felix Fehlauer
 */

/**
 * @namespace position
 * @brief Shorthand definitions for all valid position pairs
 */
namespace position {

const QPair NW_Q1 = {Orientation::Nordwest, Square::Aussen};
const QPair N_Q1 = {Orientation::Nord, Square::Aussen};
const QPair NO_Q1 = {Orientation::Nordost, Square::Aussen};
const QPair NW_Q2 = {Orientation::Nordwest, Square::Mitte};
const QPair N_Q2 = {Orientation::Nord, Square::Mitte};
const QPair NO_Q2 = {Orientation::Nordost, Square::Mitte};
const QPair NW_Q3 = {Orientation::Nordwest, Square::Innen};
const QPair N_Q3 = {Orientation::Nord, Square::Innen};
const QPair NO_Q3 = {Orientation::Nordost, Square::Innen};
const QPair W_Q1 = {Orientation::West, Square::Aussen};
const QPair W_Q2 = {Orientation::West, Square::Mitte};
const QPair W_Q3 = {Orientation::West, Square::Innen};
const QPair O_Q3 = {Orientation::Ost, Square::Innen};
const QPair O_Q2 = {Orientation::Ost, Square::Mitte};
const QPair O_Q1 = {Orientation::Ost, Square::Aussen};
const QPair SW_Q3 = {Orientation::Suedwest, Square::Innen};
const QPair S_Q3 = {Orientation::Sued, Square::Innen};
const QPair SO_Q3 = {Orientation::Suedost, Square::Innen};
const QPair SW_Q2 = {Orientation::Suedwest, Square::Mitte};
const QPair S_Q2 = {Orientation::Sued, Square::Mitte};
const QPair SO_Q2 = {Orientation::Suedost, Square::Mitte};
const QPair SW_Q1 = {Orientation::Suedwest, Square::Aussen};
const QPair S_Q1 = {Orientation::Sued, Square::Aussen};
const QPair SO_Q1 = {Orientation::Suedost, Square::Aussen};

}

#if QT_VERSION < QT_VERSION_CHECK(6, 5, 0)
QT_BEGIN_NAMESPACE

#if QT_VERSION < QT_VERSION_CHECK(6, 2, 0)
// like std::to_underlying
template <typename Enum>
constexpr std::underlying_type_t<Enum> qToUnderlying(Enum e) noexcept
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}
#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
namespace QHashPrivate {

Q_DECL_CONST_FUNCTION constexpr size_t hash(size_t key, size_t seed) noexcept
{
    key ^= seed;
    if constexpr (sizeof(size_t) == 4) {
        key ^= key >> 16;
        key *= UINT32_C(0x45d9f3b);
        key ^= key >> 16;
        key *= UINT32_C(0x45d9f3b);
        key ^= key >> 16;
        return key;
    } else {
        quint64 key64 = key;
        key64 ^= key64 >> 32;
        key64 *= UINT64_C(0xd6e8feb86659fd93);
        key64 ^= key64 >> 32;
        key64 *= UINT64_C(0xd6e8feb86659fd93);
        key64 ^= key64 >> 32;
        return size_t(key64);
    }
}
}
#endif

template <class Enum, std::enable_if_t<std::is_enum_v<Enum>, bool> = true>
Q_DECL_CONST_FUNCTION constexpr inline size_t qHash(Enum e, size_t seed = 0) noexcept
{ return QHashPrivate::hash(qToUnderlying(e), seed); }

QT_END_NAMESPACE
#endif

#endif // POSITION_H
