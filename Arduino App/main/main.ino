
#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <WiFi.h>

/*-------------------------------------------------------------------------------
 ERRORS
 -------------------------------------------------------------------------------*/

const char* Err_BeginSocket = "WIFI_BEGIN_SOCKET";

/*-------------------------------------------------------------------------------
 RESULT
 -------------------------------------------------------------------------------*/

extern const char* ERR_OK;
extern const char* ERR_FAILED;
extern const char* ERR_SYSTEM;
extern const char* NULL_STR;
extern const char* g_result_context;
extern const char* g_result_code;

bool RESULT_OK();
bool RESULT(const char* context, const char* code);

/*-------------------------------------------------------------------------------
 NetworkServer
 -------------------------------------------------------------------------------*/
#define WIFI_PORT 45454

#pragma once
class NetworkServer
{
public:
	NetworkServer(void);
	~NetworkServer(void);
	bool initHost();
	bool connect();
	void printAddress();
	void printNetAddress();
	bool readCommand();
private:
	WiFiUDP udp;
};




/**
 * Port wifi utilisé pour les transactions avec les applications clientes
 */
NetworkServer net;

/**
 * Equipment Item structure
*/
#define ITEM_TYPE_SWITCHER 2 // intensite
#define ITEM_TYPE_LED     3 // LED
#define ITEM_TYPE_HEATER  ITEM_TYPE_SWITCHER // CHAUFFAGE
#define ITEM_TYPE_SHUTTER ITEM_TYPE_SWITCHER // VOLET roulant

typedef struct _item{
	int id; // identificateur
	char type; // Type d'item
	char room_num; // Numéro de pièce
	char used_pins[8]; // Broches arduino utilisées
}item;

typedef struct _item_switcher{
	unsigned int intensity;
}item_switcher;

typedef struct _item_led{
	unsigned char r,g,b;
}item_led;

/**
 * Client request structure
*/
typedef struct _client_req{
	int target_id;
	int cmd;
	char n_val;
	int* val;
}client_req;

void setup()
{
	//init serial
	Serial.begin(9600);
	Serial.println("hello world");

	//init network server
	if(net.connect()){
		net.printAddress();
		net.initHost();
	}
	
	Serial.println("READY");
}

void loop()
{
	net.readCommand();
	delay(1000);
  /* add main program code here */
}

/*-------------------------------------------------------------------------------
 RESULT
 -------------------------------------------------------------------------------*/

const char* ERR_OK = "ERR_OK";
const char* ERR_FAILED = "ERR_FAILED";
const char* ERR_SYSTEM = "ERR_SYSTEM";
const char* NULL_STR = "";
const char* g_result_context;
const char* g_result_code;

bool RESULT_OK(){
	g_result_context=ERR_OK;
	g_result_code=NULL_STR;
	return true;
}

bool RESULT(const char* context, const char* code){
	g_result_context=context;
	g_result_code=code;
	if(strcmp(context,"ERR_OK") == 0)
		return true;
	Serial.print("context: ");
	Serial.print(context);
	Serial.print(", ");
	Serial.println(code);
	return false;
}


/*-------------------------------------------------------------------------------
 NetworkServer
 -------------------------------------------------------------------------------*/

NetworkServer::NetworkServer(void)
{
}


NetworkServer::~NetworkServer(void)
{
}


bool NetworkServer::connect(){
	Serial.println("Connect to network...");

	char ssid[] = "AceTeaM";     //  your network SSID (name) 
	char pass[] = "emyleplusbeaudesbebes";  // your network password
	int status = WL_IDLE_STATUS;

	// check for the presence of the shield:
	if (WiFi.status() == WL_NO_SHIELD) {
		Serial.println("WiFi shield not present"); 
		// don't continue:
		while(true);
	}

	// attempt to connect to Wifi network:
	while ( status != WL_CONNECTED) { 
		Serial.print("Attempting to connect to WPA SSID: ");
		Serial.println(ssid);
		// Connect to WPA/WPA2 network:    
		status = WiFi.begin(ssid, pass);

		// wait 10 seconds for connection:
		delay(10000);
	}
   
	// you're connected now, so print out the data:
	Serial.println("You're connected to the network");

	return true;
}

// initialise l'interface serveur
bool NetworkServer::initHost(){
	Serial.println("Init Host...");
	if(!udp.begin(WIFI_PORT))
		return RESULT(ERR_FAILED,Err_BeginSocket);
	return RESULT_OK();
}

// lit une commande 
bool NetworkServer::readCommand(){
	char buf[UDP_TX_PACKET_MAX_SIZE];
	int length=0;
	Serial.print("Read Cmd...");
	length = udp.parsePacket();
	if(length){
	    Serial.print(length);
	    Serial.println(" bytes");
		udp.read(buf,length);
		Serial.println(buf);
		
		// send a reply, to the IP address and port that sent us the packet we received
		/*udp.beginPacket(udp.remoteIP(), udp.remotePort());
		udp.write(buf);
		udp.endPacket();*/
	}
	else Serial.println("None");
	return RESULT_OK();
}

void NetworkServer::printAddress() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address : ");
  Serial.println(ip);
  
  // print your MAC address:
  byte mac[6];  
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
 
}

void NetworkServer::printNetAddress() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);    
  Serial.print("MAC address: ");
  Serial.print(bssid[5],HEX);
  Serial.print(":");
  Serial.print(bssid[4],HEX);
  Serial.print(":");
  Serial.print(bssid[3],HEX);
  Serial.print(":");
  Serial.print(bssid[2],HEX);
  Serial.print(":");
  Serial.print(bssid[1],HEX);
  Serial.print(":");
  Serial.println(bssid[0],HEX);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption,HEX);
  Serial.println();
}