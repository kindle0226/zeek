// See the file  in the main distribution directory for copyright.

#include "IMAP.h"
#include "plugin/Plugin.h"
#include "analyzer/Component.h"

namespace zeek::plugin::detail::Zeek_IMAP {

class Plugin : public zeek::plugin::Plugin {
public:
	zeek::plugin::Configuration Configure() override
		{
		AddComponent(new zeek::analyzer::Component("IMAP", zeek::analyzer::imap::IMAP_Analyzer::Instantiate));

		zeek::plugin::Configuration config;
		config.name = "Zeek::IMAP";
		config.description = "IMAP analyzer (StartTLS only)";
		return config;
		}
} plugin;

} // namespace zeek::plugin::detail::Zeek_IMAP
