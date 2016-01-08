#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 177); // Change the IP according to your local network

const byte SelectSlave_SD = 5; // For Ferduino Mega
//const byte SelectSlave_SD = 4; // For ethernet shield
const byte SelectSlave_ETH = 53;
const byte SelectSlave_RFM = 69;

EthernetServer server(80);

void setup()
{
	pinMode(SelectSlave_SD, OUTPUT);
	pinMode(SelectSlave_RFM, OUTPUT);
	digitalWrite(SelectSlave_SD, HIGH);
	digitalWrite(SelectSlave_RFM, HIGH);
// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial)
	{
		; // wait for serial port to connect. Needed for Leonardo only
	}
	// start the Ethernet connection and the server:
	Ethernet.begin(mac, ip, SelectSlave_ETH);
	server.begin();
	Serial.print("server is at ");
	Serial.println(Ethernet.localIP());
}


void loop()
{
	// listen for incoming clients
	EthernetClient client = server.available();
	if (client)
	{
		uint8_t remoteIP[4];
		client.getRemoteIP(remoteIP);
		Serial.print("New client: ");
		Serial.print(remoteIP[0]);
		Serial.print(".");
		Serial.print(remoteIP[1]);
		Serial.print(".");
		Serial.print(remoteIP[2]);
		Serial.print(".");
		Serial.println(remoteIP[3]);

		// an http request ends with a blank line
		boolean currentLineIsBlank = true;
		while (client.connected())
		{
			if (client.available())
			{
				char c = client.read();
				Serial.write(c);
				// if you've gotten to the end of the line (received a newline
				// character) and the line is blank, the http request has ended,
				// so you can send a reply
				if (c == '\n' && currentLineIsBlank)
				{
					// send a standard http response header
					client.println("HTTP/1.1 200 OK");
					client.println("Content-Type: text/html");
					client.println("Connection: close");  // the connection will be closed after completion of the response
					client.println("Refresh: 5");  // refresh the page automatically every 5 sec
					client.println();
					client.println("<!DOCTYPE HTML>");
					client.println("<html>");
					// output the value of each analog input pin
					for (int analogChannel = 0; analogChannel < 6; analogChannel++)
					{
						int sensorReading = analogRead(analogChannel);
						client.print("analog input ");
						client.print(analogChannel);
						client.print(" is ");
						client.print(sensorReading);
						client.println("<br />");
					}
					client.println("</html>");
					break;
				}
				if (c == '\n')
				{
					// you're starting a new line
					currentLineIsBlank = true;
				}
				else if (c != '\r')
				{
					// you've gotten a character on the current line
					currentLineIsBlank = false;
				}
			}
		}
		// give the web browser time to receive the data
		delay(1);
		// close the connection:
		client.stop();
		Serial.println("client disonnected");
	}
}
