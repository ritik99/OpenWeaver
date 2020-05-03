#ifndef MARLIN_STREAM_MESSAGES_HPP
#define MARLIN_STREAM_MESSAGES_HPP

#include <marlin/core/Buffer.hpp>


namespace marlin {
namespace stream {

struct DIAL : public core::Buffer {
public:
	DIAL(
		uint32_t src_conn_id,
		uint32_t dst_conn_id,
		uint8_t const* payload,
		size_t payload_size
	) : core::Buffer({0, 3}, 10 + payload_size) {
		this->write_uint32_be_unsafe(2, src_conn_id);
		this->write_uint32_be_unsafe(6, dst_conn_id);
		this->write_unsafe(10, payload, payload_size);
	}

	[[nodiscard]] bool validate(size_t payload_size) const {
		return this->size() >= 10 + payload_size;
	}

	uint32_t src_conn_id() const {
		return this->read_uint32_be_unsafe(6);
	}

	uint32_t dst_conn_id() const {
		return this->read_uint32_be_unsafe(6);
	}

	uint8_t* payload() {
		return this->data() + 10;
	}
};

} // namespace stream
} // namespace marlin

#endif // MARLIN_STREAM_MESSAGES_HPP
