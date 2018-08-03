#include "../src/BitsAndBytes.h"

enum class TestBits
{
    BitA = 0,
    BitB,
    BitC,
    BitD = 8
};

BOOST_AUTO_TEST_CASE(BitsNormal)
{
    uint32_t bitfield = 0;

    Utilities::setBit(bitfield, 0);
    BOOST_CHECK_EQUAL(bitfield, 1);

    Utilities::setBit(bitfield, 1u);
    BOOST_CHECK_EQUAL(bitfield, 3u);

    Utilities::clearBit(bitfield, 1);
    BOOST_CHECK_EQUAL(bitfield, 1);

    Utilities::clearBit(bitfield, 0u);
    BOOST_CHECK_EQUAL(bitfield, 0u);

    Utilities::toggleBit(bitfield, 3);
    BOOST_CHECK_EQUAL(bitfield, 8);

    Utilities::toggleBit(bitfield, 3u);
    BOOST_CHECK_EQUAL(bitfield, 0u);

    // Bits not set
    BOOST_CHECK(!Utilities::checkBit(bitfield, 1u));
    BOOST_CHECK(!Utilities::checkBit(bitfield, 2u));

    // Turn on bits 3 & 8
    Utilities::updateBit(bitfield, 3u, true);
    Utilities::updateBit(bitfield, 8u, true);

    // Bits set
    BOOST_CHECK(Utilities::checkBit(bitfield, 3u));
    BOOST_CHECK(Utilities::checkBit(bitfield, 8u));
}

BOOST_AUTO_TEST_CASE(BitsEnum)
{
    uint32_t bitfield = 0;

    Utilities::setBit(bitfield, TestBits::BitA);
    BOOST_CHECK_EQUAL(bitfield, 1);

    Utilities::setBit(bitfield, TestBits::BitB);
    BOOST_CHECK_EQUAL(bitfield, 3);

    Utilities::clearBit(bitfield, TestBits::BitB);
    BOOST_CHECK_EQUAL(bitfield, 1);

    Utilities::clearBit(bitfield, TestBits::BitA);
    BOOST_CHECK_EQUAL(bitfield, 0);

    Utilities::toggleBit(bitfield, TestBits::BitC);
    BOOST_CHECK_EQUAL(bitfield, 4);

    Utilities::toggleBit(bitfield, TestBits::BitD);
    BOOST_CHECK_EQUAL(bitfield, 260);

    // Bits not set
    BOOST_CHECK(!Utilities::checkBit(bitfield, TestBits::BitA));
    BOOST_CHECK(!Utilities::checkBit(bitfield, TestBits::BitB));

    // Bits set
    BOOST_CHECK(Utilities::checkBit(bitfield, TestBits::BitC));
    BOOST_CHECK(Utilities::checkBit(bitfield, TestBits::BitD));

    // Turn off bits C & D and update bit A state to be set
    Utilities::updateBit(bitfield, TestBits::BitC, false);
    Utilities::updateBit(bitfield, TestBits::BitD, false);
    Utilities::updateBit(bitfield, TestBits::BitA, true);
    BOOST_CHECK_EQUAL(bitfield, 1);
}