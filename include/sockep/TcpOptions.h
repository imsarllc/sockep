#pragma once

namespace sockep
{

struct TcpOptions
{
public:
	struct KeepAlive
	{
		bool enabled{false};
		int idleSeconds{10};    // 10 sec default
		int intervalSeconds{5}; // 5 secs
		int keepCount{3};       // 3 probes (15 sec until dead)
	} keepAlive;
};

} // namespace sockep