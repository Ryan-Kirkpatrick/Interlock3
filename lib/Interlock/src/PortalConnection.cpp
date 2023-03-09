#include "PortalConnection.hpp"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

std::optional<std::string> PortalConnection::obtainHashOfAuthedCards(WiFiClient &wifiClient) {
    std::optional<std::string> result;
    
    // Obtain http payload, returning nothing if there is an error
    const char *url = ""; // TODO
    auto httpResult = httpGET(wifiClient, url);
    if (!httpResult.has_value()) {
        return result;
    }

    // Decode JSON
    auto decodeResult = decodeHashOfAuthedCards(httpResult.value());
    if (decodeResult.has_value()) {
        result = decodeResult.value();
    }
    return result;

}

std::optional<CachedRFIDCards> PortalConnection::getAllAuthedCards(WiFiClient &wifiClient) {
    std::optional<CachedRFIDCards> result;
    
    // Obtain http payload, returning nothing if there is an error
    const char *url = ""; // TODO
    auto httpResult = httpGET(wifiClient, url);
    if (!httpResult.has_value()) {
        return result;
    }

    // Decode JSON
    auto decodeResult = decodeAllAuthedCards(httpResult.value());
    if (decodeResult.has_value()) {
        result = decodeResult.value();
    }
    return result;

}

std::optional<bool> PortalConnection::checkCardAuth(WiFiClient &wifiClient, RFIDCard card) {
    std::optional<bool> result;
    
    // Obtain http payload, returning nothing if there is an error
    const char *url = ""; // TODO
    auto httpResult = httpGET(wifiClient, url);
    if (!httpResult.has_value()) {
        return result;
    }

    // Decode JSON
    auto decodeResult = decodeCardAuth(httpResult.value());
    if (decodeResult.has_value()) {
        result = decodeResult.value();
    }
    return result;

}

std::optional<std::string> PortalConnection::decodeHashOfAuthedCards(String payload) {
    std::optional<std::string> result;
    
    StaticJsonDocument<128> jsonDoc;
    if (deserializeJson(jsonDoc, payload)) {
        // Error deserializing json
        return result;
    }

    // Catch other JSON errors
    if ((jsonDoc.overflowed()) || (!jsonDoc.containsKey("success")) || (!jsonDoc.containsKey("hashOfTags"))) {
        return result;
    }

    // Check if request to portal was successful
    if (!jsonDoc["success"].as<bool>()) {
        return result;
    }

    // Success!
    result = jsonDoc["success"].as<std::string>();
    return result;
}

std::optional<CachedRFIDCards> PortalConnection::decodeAllAuthedCards(String payload) {
    std::optional<CachedRFIDCards> result;
    
    StaticJsonDocument<3072> jsonDoc;
    if (deserializeJson(jsonDoc, payload)) {
        // Error deserializing json
        return result;
    }
    // Catch other json errors
    if ((jsonDoc.overflowed()) || (!jsonDoc.containsKey("authorised_tags")) || (!jsonDoc.containsKey("authorised_tags_hash"))) {
        return result;
    }

    // Obtain the results, so long as everything fits into the cache
    if(jsonDoc["authorised_tags"].size() <= Core::CACHE_SIZE) {
        JsonArray cards = jsonDoc["authorised_tags"];
        result.value().numberOfCards = copyArray(cards, result.value().cards);
        result.value().hashOfCards = jsonDoc["authorised_tags_hash"].as<std::string>();
    }
    return result;
}

std::optional<bool> PortalConnection::decodeCardAuth(String payload) {
    std::optional<bool> result;
    
    StaticJsonDocument<264> jsonDoc;
    if (deserializeJson(jsonDoc, payload)) {
        // Error deserializing json
        return result;
    }

    // Catch other JSON errors
    if ((jsonDoc.overflowed()) || (!jsonDoc.containsKey("access"))) {
        return result;
    }

    // Success!
    result = jsonDoc["access"].as<bool>();
    return result;
}

std::optional<String> PortalConnection::httpGET(WiFiClient &wifiCLient, const char *url) {
    std::optional<String> result;
    
    HTTPClient http;
    if (http.begin(wifiCLient, url)) {
        if (http.GET() == HTTP_CODE_OK) { // Errors yield negative results
            result = (http.getString());
        }
    }
    return result;
}
