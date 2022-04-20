#pragma once
#include <wlanapi.h>
#include <windows.h>
#include "cJSON.h"
#include "curl/curl.h"
#include <list>

#define GEO_API_BASE_URL "https://www.googleapis.com/geolocation/v1/geolocate?key="
#define GEO_API_KEY "**********************************"
#define GEO_API_REQUEST_URL GEO_API_BASE_URL GEO_API_KEY

namespace whereami {
	class GeolocationRequest {
	public:
	
	private:
		struct MemoryStruct {
			char* memory;
			size_t size;
		};
	};

	class GeolocationWifiPoints
	{
	public:
		int getWifiNetworks();
		char* buildRequestJSON();
	private:
		struct wifiAP {
			char macAddress[44];
			long signalStrength;
		};
		std::list<wifiAP> _wifiAPlist;

	};
}