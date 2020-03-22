#ifndef MARLIN_PUBSUB_WITNESS_CHAINWITNESSER_HPP
#define MARLIN_PUBSUB_WITNESS_CHAINWITNESSER_HPP

#include <stdint.h>
#include <cstring>


namespace marlin {
namespace pubsub {

template<typename HeaderType>
struct ChainWitnesser {
	using KeyType = uint8_t const*;
	KeyType secret_key;

	constexpr uint64_t witness_size(
		HeaderType prev_witness_header
	) {
		return prev_witness_header.witness_size == 0 ? 2 + 32 : (prev_witness_header.witness_size + 32);
	}

	int witness(
		HeaderType prev_witness_header,
		net::Buffer& out,
		uint64_t offset = 0
	) {
		if(prev_witness_header.witness_size == 0) {
			out.write_uint16_be(offset, 32);
			offset += 2;
		}
		out.write(offset, prev_witness_header.witness_data, prev_witness_header.witness_size);
		crypto_scalarmult_base((uint8_t*)out.data()+offset+prev_witness_header.witness_size, secret_key);
		return 0;
	}

	uint64_t parse_length(net::Buffer& in, uint64_t offset = 0) {
		return in.read_uint16_be(offset) + 2;
	}
};

} // namespace pubsub
} // namespace marlin

#endif // MARLIN_PUBSUB_WITNESS_CHAINWITNESSER_HPP
