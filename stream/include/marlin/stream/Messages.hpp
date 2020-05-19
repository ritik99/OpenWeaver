#ifndef MARLIN_STREAM_MESSAGES_HPP
#define MARLIN_STREAM_MESSAGES_HPP

#include <marlin/core/Buffer.hpp>


namespace marlin {
namespace stream {

template<typename BaseMessageType>
struct DATA {
	BaseMessageType base;

	[[nodiscard]] bool validate(size_t payload_size) const {
		return base.payload_buffer().size() >= 30 + payload_size;
	}

	DATA(size_t payload_size, bool is_fin) : base(30 + payload_size) {
		base.set_payload({0, static_cast<uint8_t>(is_fin)});
	}

	DATA(core::Buffer&& buf) : base(std::move(buf)) {}

	DATA& set_src_conn_id(uint32_t src_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(2, src_conn_id);

		return *this;
	}

	DATA&& set_src_conn_id(uint32_t src_conn_id) && {
		return std::move(set_src_conn_id(src_conn_id));
	}

	uint32_t src_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(6);
	}

	DATA& set_dst_conn_id(uint32_t dst_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(6, dst_conn_id);

		return *this;
	}

	DATA&& set_dst_conn_id(uint32_t dst_conn_id) && {
		return std::move(set_dst_conn_id(dst_conn_id));
	}

	uint32_t dst_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(2);
	}

	DATA& set_stream_id(uint16_t stream_id) & {
		base.payload_buffer().write_uint16_be_unsafe(18, stream_id);

		return *this;
	}

	DATA&& set_stream_id(uint16_t stream_id) && {
		return std::move(set_stream_id(stream_id));
	}

	uint16_t stream_id() const {
		return base.payload_buffer().read_uint16_be_unsafe(18);
	}

	DATA& set_packet_number(uint64_t packet_number) & {
		base.payload_buffer().write_uint64_be_unsafe(10, packet_number);

		return *this;
	}

	DATA&& set_packet_number(uint64_t packet_number) && {
		return std::move(set_packet_number(packet_number));
	}

	uint64_t packet_number() const {
		return base.payload_buffer().read_uint64_be_unsafe(10);
	}

	DATA& set_offset(uint64_t offset) & {
		base.payload_buffer().write_uint64_be_unsafe(20, offset);

		return *this;
	}

	DATA&& set_offset(uint64_t offset) && {
		return std::move(set_offset(offset));
	}

	uint64_t offset() const {
		return base.payload_buffer().read_uint64_be_unsafe(20);
	}

	DATA& set_length(uint16_t length) & {
		base.payload_buffer().write_uint16_be_unsafe(28, length);

		return *this;
	}

	DATA&& set_length(uint16_t length) && {
		return std::move(set_length(length));
	}

	uint16_t length() const {
		return base.payload_buffer().read_uint16_be_unsafe(28);
	}

	DATA& set_payload(uint8_t const* in, size_t size) & {
		base.payload_buffer().write_unsafe(30, in, size);

		return *this;
	}

	DATA&& set_payload(uint8_t const* in, size_t size) && {
		return std::move(set_payload(in, size));
	}

	DATA& set_payload(std::initializer_list<uint8_t> il) & {
		base.payload_buffer().write_unsafe(30, il.begin(), il.size());

		return *this;
	}

	DATA&& set_payload(std::initializer_list<uint8_t> il) && {
		return std::move(set_payload(il));
	}

	core::WeakBuffer payload_buffer() const {
		auto buf = base.payload_buffer();
		buf.cover_unsafe(30);

		return buf;
	}

	uint8_t* payload() {
		return base.payload_buffer().data() + 30;
	}

	bool is_fin_set() const {
		return base.payload_buffer().read_uint8_unsafe(1) == 1;
	}

	core::Buffer finalize() {
		return base.finalize();
	}

	core::Buffer release() {
		auto buf = base.release();
		buf.cover_unsafe(30);

		return std::move(buf);
	}
};

template<typename BaseMessageType>
struct DIAL {
	BaseMessageType base;

	[[nodiscard]] bool validate(size_t payload_size) const {
		return base.payload_buffer().size() >= 10 + payload_size;
	}

	DIAL(size_t payload_size) : base(10 + payload_size) {
		base.set_payload({0, 3});
	}

	DIAL(core::Buffer&& buf) : base(std::move(buf)) {}

	DIAL& set_src_conn_id(uint32_t src_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(2, src_conn_id);

		return *this;
	}

	DIAL&& set_src_conn_id(uint32_t src_conn_id) && {
		return std::move(set_src_conn_id(src_conn_id));
	}

	uint32_t src_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(6);
	}

	DIAL& set_dst_conn_id(uint32_t dst_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(6, dst_conn_id);

		return *this;
	}

	DIAL&& set_dst_conn_id(uint32_t dst_conn_id) && {
		return std::move(set_dst_conn_id(dst_conn_id));
	}

	uint32_t dst_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(2);
	}

	DIAL& set_payload(uint8_t const* in, size_t size) & {
		base.payload_buffer().write_unsafe(10, in, size);

		return *this;
	}

	DIAL&& set_payload(uint8_t const* in, size_t size) && {
		return std::move(set_payload(in, size));
	}

	DIAL& set_payload(std::initializer_list<uint8_t> il) & {
		base.payload_buffer().write_unsafe(10, il.begin(), il.size());

		return *this;
	}

	DIAL&& set_payload(std::initializer_list<uint8_t> il) && {
		return std::move(set_payload(il));
	}

	uint8_t* payload() {
		return base.payload_buffer().data() + 10;
	}

	core::Buffer finalize() {
		return base.finalize();
	}

	core::Buffer release() {
		return base.release();
	}
};

template<typename BaseMessageType>
struct DIALCONF {
	BaseMessageType base;

	[[nodiscard]] bool validate(size_t payload_size) const {
		return base.payload_buffer().size() >= 10 + payload_size;
	}

	DIALCONF(size_t payload_size) : base(10 + payload_size) {
		base.set_payload({0, 4});
	}

	DIALCONF(core::Buffer&& buf) : base(std::move(buf)) {}

	DIALCONF& set_src_conn_id(uint32_t src_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(2, src_conn_id);

		return *this;
	}

	DIALCONF&& set_src_conn_id(uint32_t src_conn_id) && {
		return std::move(set_src_conn_id(src_conn_id));
	}

	uint32_t src_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(6);
	}

	DIALCONF& set_dst_conn_id(uint32_t dst_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(6, dst_conn_id);

		return *this;
	}

	DIALCONF&& set_dst_conn_id(uint32_t dst_conn_id) && {
		return std::move(set_dst_conn_id(dst_conn_id));
	}

	uint32_t dst_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(2);
	}

	DIALCONF& set_payload(uint8_t const* in, size_t size) & {
		base.payload_buffer().write_unsafe(10, in, size);

		return *this;
	}

	DIALCONF&& set_payload(uint8_t const* in, size_t size) && {
		return std::move(set_payload(in, size));
	}

	DIALCONF& set_payload(std::initializer_list<uint8_t> il) & {
		base.payload_buffer().write_unsafe(10, il.begin(), il.size());

		return *this;
	}

	DIALCONF&& set_payload(std::initializer_list<uint8_t> il) && {
		return std::move(set_payload(il));
	}

	uint8_t* payload() {
		return base.payload_buffer().data() + 10;
	}

	core::Buffer finalize() {
		return base.finalize();
	}

	core::Buffer release() {
		return base.release();
	}
};

template<typename BaseMessageType>
struct CONF {
	BaseMessageType base;

	[[nodiscard]] bool validate() const {
		return base.payload_buffer().size() >= 10;
	}

	CONF() : base(10) {
		base.set_payload({0, 5});
	}

	CONF(core::Buffer&& buf) : base(std::move(buf)) {}

	CONF& set_src_conn_id(uint32_t src_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(2, src_conn_id);

		return *this;
	}

	CONF&& set_src_conn_id(uint32_t src_conn_id) && {
		return std::move(set_src_conn_id(src_conn_id));
	}

	uint32_t src_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(6);
	}

	CONF& set_dst_conn_id(uint32_t dst_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(6, dst_conn_id);

		return *this;
	}

	CONF&& set_dst_conn_id(uint32_t dst_conn_id) && {
		return std::move(set_dst_conn_id(dst_conn_id));
	}

	uint32_t dst_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(2);
	}

	core::Buffer finalize() {
		return base.finalize();
	}

	core::Buffer release() {
		return base.release();
	}
};

template<typename BaseMessageType>
struct RST {
	BaseMessageType base;

	[[nodiscard]] bool validate() const {
		return base.payload_buffer().size() >= 10;
	}

	RST() : base(10) {
		base.set_payload({0, 6});
	}

	RST(core::Buffer&& buf) : base(std::move(buf)) {}

	RST& set_src_conn_id(uint32_t src_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(2, src_conn_id);

		return *this;
	}

	RST&& set_src_conn_id(uint32_t src_conn_id) && {
		return std::move(set_src_conn_id(src_conn_id));
	}

	uint32_t src_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(6);
	}

	RST& set_dst_conn_id(uint32_t dst_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(6, dst_conn_id);

		return *this;
	}

	RST&& set_dst_conn_id(uint32_t dst_conn_id) && {
		return std::move(set_dst_conn_id(dst_conn_id));
	}

	uint32_t dst_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(2);
	}

	core::Buffer finalize() {
		return base.finalize();
	}

	core::Buffer release() {
		return base.release();
	}
};

template<typename BaseMessageType>
struct SKIPSTREAM {
	BaseMessageType base;

	[[nodiscard]] bool validate() const {
		return base.payload_buffer().size() >= 20;
	}

	SKIPSTREAM() : base(20) {
		base.set_payload({0, 7});
	}

	SKIPSTREAM(core::Buffer&& buf) : base(std::move(buf)) {}

	SKIPSTREAM& set_src_conn_id(uint32_t src_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(2, src_conn_id);

		return *this;
	}

	SKIPSTREAM&& set_src_conn_id(uint32_t src_conn_id) && {
		return std::move(set_src_conn_id(src_conn_id));
	}

	uint32_t src_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(6);
	}

	SKIPSTREAM& set_dst_conn_id(uint32_t dst_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(6, dst_conn_id);

		return *this;
	}

	SKIPSTREAM&& set_dst_conn_id(uint32_t dst_conn_id) && {
		return std::move(set_dst_conn_id(dst_conn_id));
	}

	uint32_t dst_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(2);
	}

	SKIPSTREAM& set_stream_id(uint16_t stream_id) & {
		base.payload_buffer().write_uint16_be_unsafe(10, stream_id);

		return *this;
	}

	SKIPSTREAM&& set_stream_id(uint16_t stream_id) && {
		return std::move(set_stream_id(stream_id));
	}

	uint16_t stream_id() const {
		return base.payload_buffer().read_uint16_be_unsafe(10);
	}

	SKIPSTREAM& set_offset(uint64_t offset) & {
		base.payload_buffer().write_uint64_be_unsafe(12, offset);

		return *this;
	}

	SKIPSTREAM&& set_offset(uint64_t offset) && {
		return std::move(set_offset(offset));
	}

	uint64_t offset() const {
		return base.payload_buffer().read_uint64_be_unsafe(12);
	}

	core::Buffer finalize() {
		return base.finalize();
	}

	core::Buffer release() {
		return base.release();
	}
};

template<typename BaseMessageType>
struct FLUSHSTREAM {
	BaseMessageType base;

	[[nodiscard]] bool validate() const {
		return base.payload_buffer().size() >= 20;
	}

	FLUSHSTREAM() : base(20) {
		base.set_payload({0, 8});
	}

	FLUSHSTREAM(core::Buffer&& buf) : base(std::move(buf)) {}

	FLUSHSTREAM& set_src_conn_id(uint32_t src_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(2, src_conn_id);

		return *this;
	}

	FLUSHSTREAM&& set_src_conn_id(uint32_t src_conn_id) && {
		return std::move(set_src_conn_id(src_conn_id));
	}

	uint32_t src_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(6);
	}

	FLUSHSTREAM& set_dst_conn_id(uint32_t dst_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(6, dst_conn_id);

		return *this;
	}

	FLUSHSTREAM&& set_dst_conn_id(uint32_t dst_conn_id) && {
		return std::move(set_dst_conn_id(dst_conn_id));
	}

	uint32_t dst_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(2);
	}

	FLUSHSTREAM& set_stream_id(uint16_t stream_id) & {
		base.payload_buffer().write_uint16_be_unsafe(10, stream_id);

		return *this;
	}

	FLUSHSTREAM&& set_stream_id(uint16_t stream_id) && {
		return std::move(set_stream_id(stream_id));
	}

	uint16_t stream_id() const {
		return base.payload_buffer().read_uint16_be_unsafe(10);
	}

	FLUSHSTREAM& set_offset(uint64_t offset) & {
		base.payload_buffer().write_uint64_be_unsafe(12, offset);

		return *this;
	}

	FLUSHSTREAM&& set_offset(uint64_t offset) && {
		return std::move(set_offset(offset));
	}

	uint64_t offset() const {
		return base.payload_buffer().read_uint64_be_unsafe(12);
	}

	core::Buffer finalize() {
		return base.finalize();
	}

	core::Buffer release() {
		return base.release();
	}
};

template<typename BaseMessageType>
struct FLUSHCONF {
	BaseMessageType base;

	[[nodiscard]] bool validate() const {
		return base.payload_buffer().size() >= 12;
	}

	FLUSHCONF() : base(12) {
		base.set_payload({0, 9});
	}

	FLUSHCONF(core::Buffer&& buf) : base(std::move(buf)) {}

	FLUSHCONF& set_src_conn_id(uint32_t src_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(2, src_conn_id);

		return *this;
	}

	FLUSHCONF&& set_src_conn_id(uint32_t src_conn_id) && {
		return std::move(set_src_conn_id(src_conn_id));
	}

	uint32_t src_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(6);
	}

	FLUSHCONF& set_dst_conn_id(uint32_t dst_conn_id) & {
		base.payload_buffer().write_uint32_be_unsafe(6, dst_conn_id);

		return *this;
	}

	FLUSHCONF&& set_dst_conn_id(uint32_t dst_conn_id) && {
		return std::move(set_dst_conn_id(dst_conn_id));
	}

	uint32_t dst_conn_id() const {
		return base.payload_buffer().read_uint32_be_unsafe(2);
	}

	FLUSHCONF& set_stream_id(uint16_t stream_id) & {
		base.payload_buffer().write_uint16_be_unsafe(10, stream_id);

		return *this;
	}

	FLUSHCONF&& set_stream_id(uint16_t stream_id) && {
		return std::move(set_stream_id(stream_id));
	}

	uint16_t stream_id() const {
		return base.payload_buffer().read_uint16_be_unsafe(10);
	}

	core::Buffer finalize() {
		return base.finalize();
	}

	core::Buffer release() {
		return base.release();
	}
};

} // namespace stream
} // namespace marlin

#endif // MARLIN_STREAM_MESSAGES_HPP
