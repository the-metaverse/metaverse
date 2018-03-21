/**
 * Copyright (c) 2011-2015 metaverse developers (see AUTHORS)
 *
 * This file is part of mvs-node.
 *
 * metaverse is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#ifndef MVS_CHAIN_ATTACHMENT_ASSET_DETAIL_HPP
#define MVS_CHAIN_ATTACHMENT_ASSET_DETAIL_HPP

#include <cstdint>
#include <istream>
#include <vector>
#include <metaverse/bitcoin/chain/point.hpp>
#include <metaverse/bitcoin/chain/script/script.hpp>
#include <metaverse/bitcoin/define.hpp>
#include <metaverse/bitcoin/utility/reader.hpp>
#include <metaverse/bitcoin/utility/writer.hpp>

namespace libbitcoin {
namespace chain {

BC_CONSTEXPR size_t ASSET_DETAIL_SYMBOL_FIX_SIZE = 64;
BC_CONSTEXPR size_t ASSET_DETAIL_MAX_SUPPLY_FIX_SIZE = 8;
BC_CONSTEXPR size_t ASSET_DETAIL_ASSET_TYPE_FIX_SIZE = 4;
BC_CONSTEXPR size_t ASSET_DETAIL_ISSUER_FIX_SIZE = 64;
BC_CONSTEXPR size_t ASSET_DETAIL_ADDRESS_FIX_SIZE = 64;
BC_CONSTEXPR size_t ASSET_DETAIL_DESCRIPTION_FIX_SIZE = 64;

BC_CONSTEXPR size_t ASSET_DETAIL_FIX_SIZE = ASSET_DETAIL_SYMBOL_FIX_SIZE
			+ ASSET_DETAIL_MAX_SUPPLY_FIX_SIZE
			+ ASSET_DETAIL_ASSET_TYPE_FIX_SIZE
			+ ASSET_DETAIL_ISSUER_FIX_SIZE
			+ ASSET_DETAIL_ADDRESS_FIX_SIZE
			+ ASSET_DETAIL_DESCRIPTION_FIX_SIZE;

class BC_API asset_detail
{
public:
	typedef std::vector<asset_detail> list;
	asset_detail();
	asset_detail(std::string symbol, uint64_t maximum_supply,
		uint8_t decimal_number, uint8_t threshold, std::string issuer,
		std::string address, std::string description);
    static asset_detail factory_from_data(const data_chunk& data);
    static asset_detail factory_from_data(std::istream& stream);
    static asset_detail factory_from_data(reader& source);
    static uint64_t satoshi_fixed_size();
    bool from_data(const data_chunk& data);
    bool from_data(std::istream& stream);
    bool from_data(reader& source);
    data_chunk to_data() const;
    void to_data(std::ostream& stream) const;
    void to_data(writer& sink) const;

    std::string to_string() const;

    bool is_valid() const;
    void reset();
    uint64_t serialized_size() const;
	const std::string& get_symbol() const;
	void set_symbol(const std::string& symbol);
	uint64_t get_maximum_supply() const;
	void set_maximum_supply(uint64_t maximum_supply);
	uint8_t get_decimal_number() const;
	void set_decimal_number(uint8_t decimal_number);
	const std::string& get_issuer() const;
	void set_issuer(const std::string& issuer);
	const std::string& get_address() const;
	void set_address(const std::string& address);
	const std::string& get_description() const;
	void set_description(const std::string& description);

    bool is_asset_secondaryissue() const { return secondaryissue_threshold >= 128; }
    void set_asset_secondaryissue() { if (!is_asset_secondaryissue()) { secondaryissue_threshold += 128; } }
    uint8_t get_secondaryissue_threshold() const
    {
        if(secondaryissue_threshold > 128)
            return secondaryissue_threshold - 128;
        else
            return secondaryissue_threshold;
    }
    void set_secondaryissue_threshold(uint8_t share)
    {
        if(secondaryissue_threshold > 128)
            secondaryissue_threshold = share + 128;
        else
            secondaryissue_threshold = share;
    }

private:    
    // NOTICE: ref CAssetDetail in transaction.h
    // asset_detail and CAssetDetail should have the same size and order.
    // uint32_t asset_type in CAssetDetail is divided into four uint8_t parts here.
    std::string symbol;
    uint64_t maximum_supply;
    uint8_t decimal_number;
    uint8_t secondaryissue_threshold;
	uint8_t unused2;
	uint8_t unused3;
    std::string issuer; 
    std::string address;
    std::string description;
};

} // namespace chain
} // namespace libbitcoin

#endif

