#ifndef __ESP_FUNCTIONS_H__
#define __ESP_FUNCTIONS_H__


//-------------------------------------------------------------------------------
#define ESP_AP_CONFIG_FILE						"/apConfig"
#define ESP_AP_SSID_MAX_LEN						32
#define ESP_AP_KEY_MAX_LEN						32

//-------------------------------------------------------------------------------
#include <stdint.h>
#include <ESP8266WebServer.h>

//-------------------------------------------------------------------------------
namespace esp {
	/**
	 * read ssid and key for AP from spi fs
	 * @param {char*} ssid
	 * @param {char*} key
	 * @return {uint8_t} result ( 1 - success, 0 - error )
	 */
	uint8_t readAPconfig(char *ssid, char *key);
	/**
	 * save ssid and key for AP from spi fs
	 * @param {char*} ssid
	 * @param {char*} key
	 * @return {uint8_t} result ( 1 - success, 0 - error )
	 */
	uint8_t saveAPconfig(const char *ssid, const char *key);
	/**
	 * checking acces from web
	 * @param {char*} user
	 * @param {char*} password
	 * @param {char*} realm
	 * @param {char*} failMess
	 * @return {uint8_t} result ( 1 - success, 0 - error )
	 */
	uint8_t checkWebAuth(ESP8266WebServer *webServer, const char *user, const char *password, const char *realm, const char *failMess);
}

//-------------------------------------------------------------------------------

#endif /* __ESP_FUNCTIONS_H__ */
