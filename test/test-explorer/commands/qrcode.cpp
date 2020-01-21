/**
 * Copyright (c) 2019-2020 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(stub)
BOOST_AUTO_TEST_SUITE(qrcode__invoke)

#if defined WITH_QRENCODE && defined WITH_PNG
BOOST_AUTO_TEST_CASE(qrcode__invoke__always__failure_error)
{
    BX_DECLARE_COMMAND(qrcode);
    command.set_module_size_option(0);
    command.set_png_option(true);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__size_one__success)
{
    BX_DECLARE_COMMAND(qrcode);

    static const uint8_t qr_png_data[]
    {
        0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00,
        0x0d, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00,
        0x00, 0x1d, 0x01, 0x03, 0x00, 0x00, 0x00, 0x6c, 0x5d, 0xf5, 0x4c,
        0x00, 0x00, 0x00, 0x06, 0x50, 0x4c, 0x54, 0x45, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0xa5, 0xd9, 0x9f, 0xdd, 0x00, 0x00, 0x00, 0x02,
        0x74, 0x52, 0x4e, 0x53, 0xff, 0xff, 0xc8, 0xb5, 0xdf, 0xc7, 0x00,
        0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0xea, 0x65, 0x16, 0xa4, 0x00, 0x00,
        0x00, 0x9a, 0x49, 0x44, 0x41, 0x54, 0x08, 0x99, 0x63, 0x60, 0xdc,
        0xcc, 0xc3, 0xce, 0x50, 0x7b, 0xc4, 0xf7, 0x3b, 0x83, 0xab, 0x60,
        0xad, 0x38, 0x83, 0x6b, 0xc7, 0x59, 0x20, 0x71, 0xf7, 0xae, 0x38,
        0x43, 0xed, 0xee, 0xde, 0xef, 0x0c, 0x8c, 0xa1, 0x21, 0xec, 0x0c,
        0xff, 0x05, 0xed, 0xff, 0x33, 0x08, 0xf8, 0x54, 0xde, 0x67, 0x38,
        0xee, 0x73, 0x70, 0x3a, 0x83, 0xe4, 0xee, 0xcb, 0xe1, 0x0c, 0x8f,
        0xdf, 0x9b, 0xff, 0x67, 0xb0, 0x2c, 0x57, 0x59, 0xce, 0xf0, 0x3c,
        0xd9, 0x64, 0x3b, 0x43, 0xcb, 0xd1, 0x99, 0xe9, 0x0c, 0xc9, 0x81,
        0x7c, 0xe9, 0x0c, 0x29, 0x67, 0x4b, 0xaf, 0x33, 0xec, 0x5e, 0x2b,
        0xba, 0x9d, 0x21, 0xa1, 0xfa, 0x9a, 0x39, 0xc3, 0xfc, 0xf5, 0xeb,
        0xec, 0x19, 0x2a, 0xae, 0x19, 0x98, 0x33, 0xfc, 0x4f, 0x0a, 0x2f,
        0x67, 0x60, 0x64, 0x3d, 0x1a, 0xce, 0x50, 0x6b, 0xb0, 0x3d, 0x9d,
        0xc1, 0xd5, 0xb7, 0x00, 0x68, 0xd1, 0x59, 0x39, 0x75, 0x06, 0x57,
        0xeb, 0x6d, 0x40, 0x31, 0xbf, 0xbe, 0xf7, 0x0c, 0x8c, 0x65, 0x8a,
        0xcb, 0x01, 0x45, 0x5a, 0x35, 0x29, 0x97, 0x41, 0x52, 0x77, 0x00,
        0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
    };
    static const auto qr_png_data_length = sizeof(qr_png_data) / sizeof(uint8_t);

    command.set_module_size_option(1);
    command.set_png_option(true);
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    BX_REQUIRE_OKAY(command.invoke(output, error));

    istream_reader in(output);
    const auto data = in.read_data_to_eof();
    BOOST_REQUIRE_EQUAL(data.size(), qr_png_data_length);
    BOOST_REQUIRE(std::memcmp(qr_png_data, data.data(), qr_png_data_length) == 0);
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__optional_args__success)
{
    BX_DECLARE_COMMAND(qrcode);

    const uint8_t qr_png_data[]
    {
        0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00,
        0x0d, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00,
        0x00, 0x27, 0x01, 0x03, 0x00, 0x00, 0x00, 0xb6, 0x6d, 0xc3, 0x76,
        0x00, 0x00, 0x00, 0x06, 0x50, 0x4c, 0x54, 0x45, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0xa5, 0xd9, 0x9f, 0xdd, 0x00, 0x00, 0x00, 0x02,
        0x74, 0x52, 0x4e, 0x53, 0xff, 0xff, 0xc8, 0xb5, 0xdf, 0xc7, 0x00,
        0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x0b, 0x1f,
        0x00, 0x00, 0x0b, 0x1f, 0x01, 0xdb, 0xed, 0x13, 0x6f, 0x00, 0x00,
        0x00, 0xb2, 0x49, 0x44, 0x41, 0x54, 0x08, 0x99, 0x63, 0xf8, 0x0f,
        0x02, 0x0c, 0xb8, 0xc8, 0x1f, 0xbc, 0x33, 0x12, 0xec, 0x19, 0x7e,
        0xbf, 0x53, 0xca, 0xdf, 0xcf, 0xf0, 0x4b, 0xa3, 0xfb, 0x05, 0x90,
        0xd4, 0x71, 0xcb, 0x00, 0x92, 0x7a, 0xef, 0x80, 0xec, 0xdf, 0x6f,
        0xef, 0x00, 0xc5, 0x7f, 0x70, 0xad, 0x5a, 0x60, 0xcf, 0xf0, 0xff,
        0x47, 0x27, 0x48, 0x7d, 0x53, 0xf2, 0xb9, 0xff, 0x0c, 0xff, 0xac,
        0xd2, 0x78, 0x80, 0xe2, 0x67, 0xef, 0xcd, 0xda, 0xcf, 0xf0, 0x5f,
        0xbe, 0x72, 0xff, 0x7f, 0x86, 0x9f, 0xa7, 0x77, 0xaa, 0x02, 0xd5,
        0x58, 0x4b, 0x2e, 0xdd, 0xcf, 0xf0, 0x47, 0x4d, 0xe7, 0x34, 0xd0,
        0x4c, 0xa9, 0x8e, 0x62, 0x20, 0xa9, 0x96, 0xbd, 0x6e, 0x3f, 0xc3,
        0xdf, 0xbb, 0x19, 0x6b, 0x81, 0xa6, 0x31, 0xdf, 0xdb, 0x08, 0x94,
        0xfd, 0x5b, 0x5b, 0xf8, 0x9f, 0xe1, 0xf7, 0xb1, 0x8d, 0x8d, 0x40,
        0xbd, 0xbf, 0x85, 0x76, 0x03, 0xcd, 0xe1, 0xd0, 0xd3, 0x02, 0xca,
        0xbe, 0x6c, 0xdd, 0x6d, 0xcf, 0xf0, 0x4b, 0x2b, 0xbb, 0x01, 0x64,
        0x7b, 0xc6, 0x47, 0x20, 0x5b, 0xf3, 0xee, 0x26, 0xa0, 0xf8, 0xab,
        0x92, 0xf2, 0x7a, 0x86, 0x1f, 0xdc, 0x1b, 0x79, 0xed, 0x71, 0xfa,
        0x02, 0x4c, 0x02, 0x00, 0xa7, 0x42, 0x8c, 0x5f, 0x6a, 0x80, 0x62,
        0xf2, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42,
        0x60, 0x82
    };
    static const auto qr_png_data_length = sizeof(qr_png_data) / sizeof(uint8_t);

    command.set_module_size_option(1);
    command.set_scheme_option("");
    command.set_png_option(true);
    command.set_insensitive_option(false);
    command.set_version_option(0);
    command.set_density_option(73);
    command.set_margin_size_option(5);
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    BX_REQUIRE_OKAY(command.invoke(output, error));

    istream_reader in(output);
    const auto data = in.read_data_to_eof();
    BOOST_REQUIRE_EQUAL(data.size(), qr_png_data_length);
    BOOST_REQUIRE(std::memcmp(qr_png_data, data.data(), qr_png_data_length) == 0);
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__qr_encode__success)
{
    BX_DECLARE_COMMAND(qrcode);

    const uint8_t raw_qr_data[]
    {
        0x03, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0xc1, 0xc1, 0xc1,
        0xc1, 0xc1, 0xc1, 0xc1, 0xc0, 0x84, 0x03, 0x02, 0x02, 0x03, 0x03,
        0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0xc0, 0xc1, 0xc1, 0xc1,
        0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1,
        0xc0, 0x84, 0x02, 0x03, 0x03, 0x03, 0x02, 0x03, 0x03, 0x03, 0x02,
        0x03, 0x03, 0x02, 0xc0, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1,
        0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc0, 0x85, 0x03, 0x03,
        0x02, 0x03, 0x03, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0xc0,
        0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc1, 0xc0, 0xc1, 0xc1,
        0xc1, 0xc0, 0xc1, 0xc0, 0x84, 0x03, 0x03, 0x03, 0x02, 0x03, 0x03,
        0x03, 0x02, 0x02, 0x03, 0x03, 0x02, 0xc0, 0xc1, 0xc0, 0xc1, 0xc1,
        0xc1, 0xc0, 0xc1, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc0,
        0x84, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03,
        0x02, 0x02, 0xc0, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc1,
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0xc0, 0x84, 0x03, 0x02, 0x02,
        0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0xc0, 0xc1,
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1,
        0xc1, 0xc1, 0xc0, 0x91, 0x90, 0x91, 0x90, 0x91, 0x90, 0x91, 0x90,
        0x91, 0x90, 0x91, 0x90, 0x91, 0xc0, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1,
        0xc1, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x85,
        0x03, 0x03, 0x02, 0x03, 0x03, 0x03, 0x02, 0x03, 0x03, 0x02, 0x02,
        0x02, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x85, 0x85,
        0x85, 0x84, 0x85, 0x85, 0x91, 0x85, 0x85, 0x02, 0x03, 0x03, 0x02,
        0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x85, 0x85, 0x84,
        0x84, 0x84, 0x85, 0x84, 0x84, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02,
        0x90, 0x02, 0x03, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03, 0x02,
        0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03, 0x02,
        0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0x91, 0x02, 0x02, 0x03,
        0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x03,
        0x03, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02,
        0x03, 0x03, 0x03, 0x90, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02,
        0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02,
        0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x02, 0x03, 0x91,
        0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x03,
        0x02, 0x03, 0x03, 0x02, 0x03, 0x03, 0x02, 0x03, 0x02, 0x03, 0x03,
        0x02, 0x02, 0x02, 0x03, 0x03, 0x02, 0x90, 0x02, 0x03, 0x02, 0x02,
        0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x02,
        0x03, 0x03, 0x02, 0x03, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03,
        0x03, 0x02, 0x91, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x03,
        0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03, 0x02, 0x03, 0x02,
        0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x90, 0x02,
        0x03, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0x02, 0x03, 0x03, 0x03,
        0x03, 0x02, 0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03,
        0x02, 0x02, 0x03, 0x03, 0x02, 0x91, 0x03, 0x02, 0x02, 0x03, 0x03,
        0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x03,
        0x02, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02,
        0x03, 0x90, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x03, 0x02,
        0x03, 0x03, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x03, 0x02,
        0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x91, 0x03, 0x03,
        0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02,
        0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0x02, 0x03,
        0x03, 0x02, 0x02, 0x02, 0x90, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02,
        0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03,
        0x03, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x03,
        0x91, 0x03, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x03, 0x03,
        0x03, 0x02, 0x02, 0xa1, 0xa1, 0xa1, 0xa1, 0xa1, 0x03, 0x02, 0x02,
        0x03, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x81, 0x02,
        0x02, 0x03, 0x03, 0x03, 0x02, 0x03, 0x03, 0x02, 0x03, 0x02, 0xa1,
        0xa0, 0xa0, 0xa0, 0xa1, 0x02, 0x02, 0x02, 0x03, 0xc1, 0xc1, 0xc1,
        0xc1, 0xc1, 0xc1, 0xc1, 0xc0, 0x85, 0x03, 0x03, 0x03, 0x03, 0x02,
        0x03, 0x02, 0x02, 0x02, 0x03, 0x03, 0xa1, 0xa0, 0xa1, 0xa0, 0xa1,
        0x02, 0x03, 0x02, 0x03, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1,
        0xc0, 0x85, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x03,
        0x02, 0x02, 0xa1, 0xa0, 0xa0, 0xa0, 0xa1, 0x02, 0x02, 0x03, 0x03,
        0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc0, 0x85, 0x02, 0x03,
        0x03, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02, 0xa1, 0xa1,
        0xa1, 0xa1, 0xa1, 0x03, 0x03, 0x02, 0x03, 0xc1, 0xc0, 0xc1, 0xc1,
        0xc1, 0xc0, 0xc1, 0xc0, 0x84, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03,
        0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03,
        0x02, 0x03, 0x03, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc0,
        0x85, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02,
        0x02, 0x03, 0x02, 0x02, 0x03, 0x03, 0x02, 0x03, 0x02, 0x03, 0xc1,
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0xc0, 0x85, 0x02, 0x03, 0x03,
        0x02, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02,
        0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1,
        0xc1, 0xc1, 0xc0, 0x85, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x03,
        0x03, 0x03, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0x02,
        0x03, 0x03
    };
    static const auto raw_qr_data_length = sizeof(raw_qr_data) / sizeof(uint8_t);

    command.set_module_size_option(1);
    command.set_png_option(false);
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    BX_REQUIRE_OKAY(command.invoke(output, error));

    istream_reader in(output);
    const auto data = in.read_data_to_eof();
    BOOST_REQUIRE_EQUAL(data.size(), raw_qr_data_length);
    BOOST_REQUIRE(std::memcmp(raw_qr_data, data.data(), raw_qr_data_length) == 0);
}

#else
BOOST_AUTO_TEST_CASE(qrcode__invoke__always__failure_error)
{
    BX_DECLARE_COMMAND(qrcode);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_QRCODE_REQUIRES_QRENCODE "\n");
}
#endif

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
