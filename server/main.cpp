#include <memory>
#include <cstdint>
#include <iostream>
#include <string.h>
#include <evhttp.h>
#include "json.hpp"

using json = nlohmann::json;
json teamUpList = json::parse("[]");

void OnReq(evhttp_request *req, void *)
{
	auto *OutBuf = evhttp_request_get_output_buffer(req);

	struct evkeyvalq headers;
	const char *action;
	evhttp_parse_query (evhttp_request_get_uri (req), &headers);
	action = evhttp_find_header (&headers, "action");

	if (OutBuf){
		if(action != nullptr && strcmp(action, "get") == 0){
			evbuffer_add_printf(OutBuf, teamUpList.dump().c_str());

		}else if(action != nullptr && strcmp(action, "add") == 0){
			const char *username = evhttp_find_header (&headers, "username");
			const char *restaurant = evhttp_find_header (&headers, "restaurant");
			if(username != nullptr && restaurant != nullptr){
				json temp = {
					{"restaurant", atoi(restaurant)},
					{"name", username}
				};
				teamUpList.push_back(temp);
				evbuffer_add_printf(OutBuf, "Added!");
			}else{
				evbuffer_add_printf(OutBuf, "Missing Parameter(s).");
			}
		}else{
			evbuffer_add_printf(OutBuf, "Hello World!");
		}
		evhttp_send_reply(req, HTTP_OK, "", OutBuf);
	}
};
int main()
{
	if (!event_init())
	{
		std::cerr << "Failed to init libevent." << std::endl;
		return -1;
	}
	char const SrvAddress[] = "127.0.0.1";
	std::uint16_t SrvPort = 8080;
	std::unique_ptr<evhttp, decltype(&evhttp_free)> Server(evhttp_start(SrvAddress, SrvPort), &evhttp_free);
	if (!Server)
	{
		std::cerr << "Failed to init http server." << std::endl;
		return -1;
	}

	evhttp_set_gencb(Server.get(), OnReq, nullptr);
	if (event_dispatch() == -1)
	{
		std::cerr << "Failed to run messahe loop." << std::endl;
		return -1;
	}
	return 0;
}
