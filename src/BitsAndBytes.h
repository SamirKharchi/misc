#ifndef BITSANDBYTES_H_
#define BITSANDBYTES_H_

#include <type_traits>

namespace Misc
{
    /************************************************************************/
    /* Bit manipulation                                                     */
    /************************************************************************/
    template < typename T >
    inline void assertBit()
    {
        static_assert(std::is_integral<T>::value, "T must be of integral type.");
    }
    //! Sets the desired bit in data
    template < typename T >
    inline void setBit(T& data, unsigned bit)
    {
        assertBit<T>();
        // OR
        data |= 1UL << bit;
    }

    //! Clears the desired bit in data
    template < typename T >
    inline void clearBit(T& data, unsigned bit)
    {
        assertBit<T>();
        // bit string inversion then AND
        data &= ~(1UL << bit);
    }

    //! Sets or clears the desired bit in data depending on given boolean
    template < typename T >
    inline void updateBit(T& data, unsigned bit, bool state)
    {
        assertBit<T>();
        state ? setBit(data, bit) : clearBit(data, bit);
    }

    //! Toggles the desired bit in data
    template < typename T >
    inline void toggleBit(T& data, unsigned bit)
    {
        assertBit<T>();
        // XOR
        data ^= 1UL << bit;
    }

    template < typename T >
    inline bool checkBit(const T& data, unsigned bit)
    {
        assertBit<T>();
        // right shift + bitwise AND
        return (data >> bit) & 1U;
    }

    /************************************************************************/
    /* Bit manipulation - Enum class specific version                       */
    /************************************************************************/
    //! Removes template from overload resolution if bit parameter type is not an enum
    template < typename T >
    using IsEnum = typename std::enable_if_t<std::is_enum<T>::value>;

    //! Sets the desired bit in data
    template < typename T, typename U, typename = IsEnum<U> >
    inline void setBit(T& data, U bit)
    {
        assertBit<T>();
        // OR
        data |= 1UL << underlying(bit);
    }
    
    //! Clears the desired bit in data
    template < typename T, typename U, typename = IsEnum<U> >
    inline void clearBit(T& data, U bit)
    {
        assertBit<T>();
        // bit string inversion then AND
        data &= ~(1UL << underlying(bit));
    }
    
    //! Sets or clears the desired bit in data depending on given boolean
    template < typename T, typename U, typename = IsEnum<U> >
    inline void updateBit(T& data, U bit, bool state)
    {
        assertBit<T>();
        state ? setBit(data, bit) : clearBit(data, bit);
    }

    //! Toggles the desired bit in data
    template < typename T, typename U, typename = IsEnum<U> >
    inline void toggleBit(T& data, U bit)
    {
        assertBit<T>();
        // XOR
        data ^= 1UL << underlying(bit);
    }

    //! That will return the value of the desired bit
    template < typename T, typename U, typename = IsEnum<U> >
    inline bool checkBit(const T& data, U bit)
    {
        assertBit<T>();
        // right shift + bitwise AND
        return (data >> underlying(bit)) & 1U;
    }
}

#endif // BITSANDBYTES_H_
