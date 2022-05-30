In order to run the test suite:

1. Adjust the build flags for [env:test] in platformio.ini 
2. Start an MQTT broker 
3. Run test.py, ensuring the details there match the flags set in platformio.ini (broker address, mqtt topics, etc)
4. Run `pio test --environment test`