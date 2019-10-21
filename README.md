# blockchain_weatherstation
## Quick Instructions

1. Create your metamask wallet
2. Create your account at [infura](https://infura.io/)
3. Select ropsten test net.
4. Copy your keys
5. Upload blockchain_weatherstation code to XinaBox CW02
6. Deploy Solidity code [weather_station](https://github.com/XinaBoxSamples/blockchain_weatherstation/blob/master/weather_station.sol) to your Ethereum account. Select Injected Web3 environment.
7. Update Arduino code [blockchain_weatherstation](https://github.com/XinaBoxSamples/blockchain_weatherstation/blob/master/blockchain_weatherstation.ino) with your keys and addresses
8. Download and install these libraries to Arduino IDE.: [xCore](https://github.com/xinabox/arduino-CORE), [xSW01](https://github.com/xinabox/arduino-SW01) and [arduino-web3](https://github.com/xinabox/web3-arduino)
9. CW02 will now trasmit SW01 data to your blockchain with 10 minutes of interval.

Detailed document: [Google doc link]()


