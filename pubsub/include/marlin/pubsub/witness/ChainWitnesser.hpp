#ifndef MARLIN_PUBSUB_WITNESS_CHAINWITNESSER_HPP
#define MARLIN_PUBSUB_WITNESS_CHAINWITNESSER_HPP

#include <stdint.h>
#include <marlin/core/Buffer.hpp>


namespace marlin {
namespace pubsub {

struct ChainWitnesser {
	using KeyType = uint8_t const*;
	KeyType secret_key;

	ChainWitnesser(KeyType secret_key) : secret_key(secret_key) {}

	template<typename HeaderType>
	constexpr uint64_t witness_size(
		HeaderType prev_witness_header
	) {
		return prev_witness_header.witness_size == 0 ? 2 + 32 : (prev_witness_header.witness_size + 32);
	}

	template<typename HeaderType>
	int witness(
		HeaderType prev_witness_header,
		core::Buffer& out,
		uint64_t offset = 0
	) {
		if(prev_witness_header.witness_size == 0) {
			// FIXME: should probably add _unsafe to function
			out.write_uint16_be_unsafe(offset, 32);
			offset += 2;
		}
		// FIXME: should probably add _unsafe to function
		out.write_unsafe(offset, prev_witness_header.witness_data, prev_witness_header.witness_size);
		crypto_scalarmult_base(out.data()+offset+prev_witness_header.witness_size, secret_key);
		return 0;
	}

	std::optional<uint64_t> parse_size(core::Buffer& in, uint64_t offset = 0) {
		auto res = in.read_uint16_be(offset);
		return res.has_value() ? res.value() + 2 : res;
	}
};

} // namespace pubsub
} // namespace marlin

#endif // MARLIN_PUBSUB_WITNESS_CHAINWITNESSER_HPP
