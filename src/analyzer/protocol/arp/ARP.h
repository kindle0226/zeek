// See the file "COPYING" in the main distribution directory for copyright.

#pragma once

#include "zeek-config.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/if_arp.h>
#ifdef HAVE_NET_ETHERNET_H
#include <net/ethernet.h>
#elif defined(HAVE_SYS_ETHERNET_H)
#include <sys/ethernet.h>
#elif defined(HAVE_NETINET_IF_ETHER_H)
#include <netinet/if_ether.h>
#elif defined(HAVE_NET_ETHERTYPES_H)
#include <net/ethertypes.h>
#endif

#ifndef arp_pkthdr
#define arp_pkthdr arphdr
#endif

#include "NetVar.h"

ZEEK_FORWARD_DECLARE_NAMESPACED(Packet, zeek);

extern "C" {
#include <pcap.h>
}

namespace zeek::analyzer::arp {

class ARP_Analyzer : public Obj {
public:
	ARP_Analyzer();
	~ARP_Analyzer() override;

	void NextPacket(double t, const Packet* pkt);

	void Describe(ODesc* d) const override;
	void RREvent(EventHandlerPtr e, const u_char* src, const u_char* dst,
	             const char* spa, const char* sha,
	             const char* tpa, const char* tha);

protected:

	[[deprecated("Remove in v4.1.  Use ToAddrVal().")]]
	AddrVal* ConstructAddrVal(const void* addr);
	[[deprecated("Remove in v4.1.  Use ToEthAddrStr().")]]
	StringVal* EthAddrToStr(const u_char* addr);

	AddrValPtr ToAddrVal(const void* addr);
	StringValPtr ToEthAddrStr(const u_char* addr);
	void BadARP(const struct arp_pkthdr* hdr, const char* string);
	void Corrupted(const char* string);
};

} // namespace zeek::analyzer::arp

namespace analyzer::arp {

using ARP_Analyzer [[deprecated("Remove in v4.1. Use zeek::analyzer::arp::ARP_Analyzer.")]] = zeek::analyzer::arp::ARP_Analyzer;

} // namespace analyzer::arp
