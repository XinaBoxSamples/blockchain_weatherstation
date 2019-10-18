#include<WiFi.h>
#include <Web3.h>
#include <Contract.h>
#include <string.h>
#include <Wire.h>
#include <xCore.h>
#include <xSW01.h>

#define USE_SERIAL Serial

#define ENV_SSID     "SSID"
#define ENV_WIFI_KEY "PSK"
#define MY_ADDRESS "WALLET ADDRESS"
#define CONTRACT_ADDRESS "SMART CONTRACT ADDRESS"
#define INFURA_HOST "ropsten.infura.io"
#define INFURA_PATH "/"

const char PRIVATE_KEY[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                           };


string contractAddr = CONTRACT_ADDRESS;
string addr = MY_ADDRESS;

string infura = INFURA_HOST;
string path = INFURA_PATH;

unsigned long timer;

Web3 web3(&infura, &path);
xSW01 SW01;
float tempC, pressure, humidity;

void eth_send_example();

void setup() {

  USE_SERIAL.begin(115200);

  Wire.begin();
  SW01.begin();

  SW01.poll();

  tempC = SW01.getTempC();
  pressure = SW01.getPressure();
  humidity = SW01.getHumidity();


  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  Serial.println("Temperature:");
  Serial.println(tempC);
  Serial.println("Pressure:");
  Serial.println(pressure);
  Serial.println("Humidity:");
  Serial.println(humidity);

  WiFi.begin(ENV_SSID, ENV_WIFI_KEY);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }

  USE_SERIAL.println("Connected");

  eth_send_temp();
  delay(60000);
  eth_send_press();
  delay(60000);
  eth_send_hum();

  timer = millis();
}

void loop() {
  // put your main code here, to run repeatedly:

  SW01.poll();
  tempC = SW01.getTempC();
  pressure = SW01.getPressure();
  humidity = SW01.getHumidity();

  if (millis() - timer > 600000)
  {
    eth_send_temp();
    delay(60000);
    eth_send_press();
    delay(60000);
    eth_send_hum();
    timer = millis();
  }
}

void eth_send_temp() {

  Contract contract(&web3, &contractAddr);
  contract.SetPrivateKey((uint8_t*)PRIVATE_KEY);
  uint32_t nonceVal = (uint32_t)web3.EthGetTransactionCount(&addr);

  uint32_t gasPriceVal = 141006540;
  uint32_t  gasLimitVal = 3000000;
  string toStr = CONTRACT_ADDRESS;
  string valueStr = "0x00";
  uint8_t dataStr[100];
  memset(dataStr, 0, 100);
  string func = "setTemp(int256)";
  string p = contract.SetupContractData(&func, (int)tempC);
  string result = contract.SendTransaction(nonceVal, gasPriceVal, gasLimitVal, &toStr, &valueStr, &p);

  USE_SERIAL.println(result.c_str());
}

void eth_send_press() {

  Contract contract(&web3, &contractAddr);
  contract.SetPrivateKey((uint8_t*)PRIVATE_KEY);
  uint32_t nonceVal = (uint32_t)web3.EthGetTransactionCount(&addr);

  uint32_t gasPriceVal = 141006540;
  uint32_t  gasLimitVal = 3000000;
  string toStr = CONTRACT_ADDRESS;
  string valueStr = "0x00";
  uint8_t dataStr[100];
  memset(dataStr, 0, 100);
  string func = "setPress(int256)";
  string p = contract.SetupContractData(&func, (int)pressure);
  string result = contract.SendTransaction(nonceVal, gasPriceVal, gasLimitVal, &toStr, &valueStr, &p);

  USE_SERIAL.println(result.c_str());
}

void eth_send_hum() {

  Contract contract(&web3, &contractAddr);
  contract.SetPrivateKey((uint8_t*)PRIVATE_KEY);
  uint32_t nonceVal = (uint32_t)web3.EthGetTransactionCount(&addr);

  uint32_t gasPriceVal = 141006540;
  uint32_t  gasLimitVal = 3000000;
  string toStr = CONTRACT_ADDRESS;
  string valueStr = "0x00";
  uint8_t dataStr[100];
  memset(dataStr, 0, 100);
  string func = "setHum(int256)";
  string p = contract.SetupContractData(&func, (int)humidity);
  string result = contract.SendTransaction(nonceVal, gasPriceVal, gasLimitVal, &toStr, &valueStr, &p);

  USE_SERIAL.println(result.c_str());
}
