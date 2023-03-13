#include "HTTPInterface.hpp"
#include "Core.hpp"


HTTPInterface::HTTPInterface(PortalConnection &portal, Logger &logger) : 
portal{portal}, 
httpServer{ESP8266WebServer(80)},
logger{logger} {
    httpServer.on("/", [this](){httpRoot();});
    httpServer.on("/bump", [this](){httpBump();});
    httpServer.on("/activate", [this](){httpActivate();});
    httpServer.on("/reboot", [this](){httpReboot();});
    httpServer.on("/logs", [this](){httpLogs();});
    httpServer.on("/log", [this](){httpLogs();});
    httpServer.begin();
}

std::optional<std::unique_ptr<AbstractState>> HTTPInterface::loop() {
    httpServer.handleClient();
    if (nextState.has_value()) {
        auto result = std::move(nextState.value());
        nextState.reset();
        return std::move(result);
    }
    return {};
}

void HTTPInterface::httpRoot() {
    // Don't mess with the ASCII art >:(
    PGM_P rootHTML = PSTR("<html>"
        "<head>"
            "<title>" DEVICE_NAME "</title>"
        "</head>"
        "<h1>" DEVICE_NAME "</h1>"
        "<h2>" 
            "<p>"
            "You're probably here because something is sad :'(" 
            "</p><p>"
            "For logs go to <a href=\"./logs\">https://x.x.x.x/logs</a>" 
            "</p><p>"
                "Logs are no longer live but will show previous logging events."
            "</p>"
        "</h2>"
        "<pre>"
"          _____                    _____                    _____                    _____                    _____          \n"
"         /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\         \n"
"        /::\\____\\                /::\\    \\                /::\\    \\                /::\\____\\                /::\\    \\        \n"
"       /:::/    /               /::::\\    \\              /::::\\    \\              /::::|   |               /::::\\    \\       \n"
"      /:::/    /               /::::::\\    \\            /::::::\\    \\            /:::::|   |              /::::::\\    \\      \n"
"     /:::/    /               /:::/\\:::\\    \\          /:::/\\:::\\    \\          /::::::|   |             /:::/\\:::\\    \\     \n"
"    /:::/____/               /:::/__\\:::\\    \\        /:::/__\\:::\\    \\        /:::/|::|   |            /:::/__\\:::\\    \\    \n"
"   /::::\\    \\               \\:::\\   \\:::\\    \\      /::::\\   \\:::\\    \\      /:::/ |::|   |           /::::\\   \\:::\\    \\   \n"
"  /::::::\\    \\   _____    ___\\:::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\    /:::/  |::|   | _____    /::::::\\   \\:::\\    \\  \n"
" /:::/\\:::\\    \\ /\\    \\  /\\   \\:::\\   \\:::\\    \\  /:::/\\:::\\   \\:::\\ ___\\  /:::/   |::|   |/\\    \\  /:::/\\:::\\   \\:::\\    \\ \n"
"/:::/  \\:::\\    /::\\____\\/::\\   \\:::\\   \\:::\\____\\/:::/__\\:::\\   \\:::|    |/:: /    |::|   /::\\____\\/:::/__\\:::\\   \\:::\\____\\\n"
"\\::/    \\:::\\  /:::/    /\\:::\\   \\:::\\   \\::/    /\\:::\\   \\:::\\  /:::|____|\\::/    /|::|  /:::/    /\\:::\\   \\:::\\   \\::/    /\n"
" \\/____/ \\:::\\/:::/    /  \\:::\\   \\:::\\   \\/____/  \\:::\\   \\:::\\/:::/    /  \\/____/ |::| /:::/    /  \\:::\\   \\:::\\   \\/____/ \n"
"          \\::::::/    /    \\:::\\   \\:::\\    \\       \\:::\\   \\::::::/    /           |::|/:::/    /    \\:::\\   \\:::\\    \\     \n"
"           \\::::/    /      \\:::\\   \\:::\\____\\       \\:::\\   \\::::/    /            |::::::/    /      \\:::\\   \\:::\\____\\    \n"
"           /:::/    /        \\:::\\  /:::/    /        \\:::\\  /:::/    /             |:::::/    /        \\:::\\   \\::/    /    \n"
"          /:::/    /          \\:::\\/:::/    /          \\:::\\/:::/    /              |::::/    /          \\:::\\   \\/____/     \n"
"         /:::/    /            \\::::::/    /            \\::::::/    /               /:::/    /            \\:::\\    \\         \n"
"        /:::/    /              \\::::/    /              \\::::/    /               /:::/    /              \\:::\\____\\        \n"
"        \\::/    /                \\::/    /                \\::/____/                \\::/    /                \\::/    /        \n"
"         \\/____/                  \\/____/                  ~~                       \\/____/                  \\/____/         \n"
                                                                                                                             
    "</pre>"
    "</html>"
    );
    httpServer.send(200, "text/html", rootHTML);
}

void HTTPInterface::httpReboot() {
    ESP.reset();
}

void HTTPInterface::httpBump() {
    // TODO
}

void HTTPInterface::httpActivate() {
    // TODO
}

void HTTPInterface::httpLogs() {
    httpServer.send(200, "text/plain", logger.getLogs());
}


