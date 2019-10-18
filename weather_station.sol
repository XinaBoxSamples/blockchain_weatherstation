pragma solidity ^0.4.18;

contract weather_station {
    int temp;
    int press;
    int hum;
    

    function setTemp(int tempData) public{
        temp = tempData;
    }
    
    function setPress(int pressData) public{
        press = pressData;
    }
    
    function setHum(int humData) public{
        hum = humData;
    }

    function getTemperature() public view returns (int retVal) {
        return temp;
    }

    function getPressure() public view returns (int retVal) {
        return press;
    }
    
    function getHumidity() public view returns (int retVal) {
        return hum;
    }
}
