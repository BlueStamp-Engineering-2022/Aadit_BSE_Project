// This #include statement was automatically added by the Particle IDE.
#include "dht.h"

//#include "DHT.h"
#define DHTPIN          D4
#define DHTTYPE         DHT11
#define DELAY           2500

DHT dht(DHTPIN, DHTTYPE);

int temperature = 0;
int humidity = 0;

// Returns temperature
int getTemperature(String args){
    return ((int)dht.readTemperature() * 9 / 5) + 32;
}

// Returns humidity
int getHumidity(String args){
    return (int)dht.readHumidity();
}

// Turn on/off LEDs
int controlled(String args){
    int pos = args.indexOf(',');
    
    if(-1 == pos){
        return -1;
    }
    
    String strPin = args.substring(0, pos);
    String strValue = args.substring(pos + 1);
    
    Serial.println();
    Serial.print("Pin: ");
    Serial.print(strPin);
    Serial.print(" ");
    Serial.print("Value: ");
    Serial.print(strValue);
    Serial.println();
    
    int pin = D2;
    int value = HIGH;
    
    if(strPin.equalsIgnoreCase("D2")){
        pin = D2;
    }
    else if(strPin.equalsIgnoreCase("D6")){
        pin = D6;
    }
    else{
        return -2;
    }
    
    if(strValue.equalsIgnoreCase("HIGH")){
        value = HIGH;
    }
    else if(strValue.equalsIgnoreCase("LOW")){
        value = LOW;
    }
    else{
        return -3;
    }
    
    digitalWrite(pin, value);
    
    return 1;
}

void setup() {
    Serial.begin(115200);
    dht.begin();
    
    pinMode(D2, OUTPUT);
    pinMode(D6, OUTPUT);
    
    // Particle Functions
    Spark.function("gettmp", getTemperature);
    Spark.function("gethmd", getHumidity);
    Spark.function("ctrlled", controlled);
    
}

void loop() {
    // Get temperature and humidity
    temperature = ((int)dht.readTemperature() * 9 / 5) + 32;
    humidity = (int)dht.readHumidity();
    Particle.publish ("Temperature: ", String(temperature) + "°F");
    Particle.publish ("Humidity: ", String(humidity) + "%");
   /* for (int i = 0; i < 5; i++) {
        digitalWrite(D2, HIGH);
        digitalWrite(D6, LOW);
        delay (250);
    
        digitalWrite(D2, LOW);
        digitalWrite(D6, HIGH);
        delay (250);
    }
    /*
    
    /*
    Serial.println();
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println();
    */
    delay(DELAY);
}
