#ifndef MARLIN_SIMULATOR_NETWORK_NETWORKINTERFACE_HPP
#define MARLIN_SIMULATOR_NETWORK_NETWORKINTERFACE_HPP

#include "marlin/net/SocketAddress.hpp"


namespace marlin {
namespace simulator {

class NetworkListener {
	virtual void did_recv(
		net::SocketAddress const& addr,
		net::Buffer&& packet
	) = 0;
	virtual void did_close();
}

template<typename NetworkType>
class NetworkInterface {
private:
	std::unordered_map<uint16_t, NetworkListener*> listeners;
	NetworkType& network;

public:
	net::SocketAddress addr;

	NetworkInterface(
		NetworkType& network,
		net::SocketAddress const& addr
	);

	int bind(NetworkListener& listener, uint16_t port);
	void close(uint16_t port);

	template<typename EventManager>
	int send(EventManager& manager, uint16_t port, SocketAddress const& addr, net::Buffer&& packet);
	void did_recv(uint16_t port, net::SocketAddress const& addr, net::Buffer&& packet);
};


// Impl

template<typename NetworkType>
NetworkInterface<NetworkType>::NetworkInterface(
	NetworkType& network,
	net::SocketAddress const& addr
) : network(network), addr(addr) {}

template<typename NetworkType>
int NetworkInterface<NetworkType>::bind(NetworkListener& listener, uint16_t port) {
	if(listeners.find(port) != listeners.end()) {
		return -1;
	}

	listeners[port] = &listener;

	return 0;
}

template<typename NetworkType>
void NetworkInterface<NetworkType>::close(uint16_t port) {
	if(listeners.find(port) == listeners.end()) {
		return;
	}

	auto* listener = listeners[port];
	listeners.erase(port);
	listener->did_close();
}

template<typename NetworkType>
template<typename EventManager>
int NetworkInterface<NetworkType>::send(
	EventManager& manager,
	SocketAddress const& src_addr,
	SocketAddress const& dst_addr,
	net::Buffer&& packet
) {
	return network.send(manager, src_addr, dst_addr, std::move(packet));
}

template<typename NetworkType>
void NetworkInterface<NetworkType>::did_recv(
	uint16_t port,
	SocketAddress const& addr,
	net::Buffer&& packet
) {
	if(listeners.find(port) == listeners.end()) {
		throw;
	}

	auto* listener = listeners[port];
	listener->did_recv(addr, std::move(packet));
}

} // namespace simulator
} // namespace marlin

#endif // MARLIN_SIMULATOR_NETWORK_NETWORKINTERFACE_HPP
