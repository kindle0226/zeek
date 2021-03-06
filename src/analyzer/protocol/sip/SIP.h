#pragma once

#include "events.bif.h"

#include "analyzer/protocol/udp/UDP.h"
#include "sip_pac.h"

namespace zeek::analyzer::sip{

class SIP_Analyzer final : public analyzer::Analyzer {
public:
	explicit SIP_Analyzer(Connection* conn);
	~SIP_Analyzer() override;

	// Overridden from Analyzer

	void Done() override;
	void DeliverPacket(int len, const u_char* data, bool orig,
				   	   uint64_t seq, const IP_Hdr* ip, int caplen) override;

	static analyzer::Analyzer* Instantiate(Connection* conn)
	{ return new SIP_Analyzer(conn); }

protected:
	binpac::SIP::SIP_Conn* interp;
};

} // namespace zeek::analyzer::sip

namespace analyzer::SIP {

using SIP_Analyzer [[deprecated("Remove in v4.1. Use zeek::analyzer::sip::SIP_Analyzer.")]] = zeek::analyzer::sip::SIP_Analyzer;

} // namespace analyzer::SIP
