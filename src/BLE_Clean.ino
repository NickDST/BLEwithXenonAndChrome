
// Variables for keeping state
typedef struct {
  uint8_t light;
  uint8_t light2;
} led_level_t;

// Static level tracking
static led_level_t m_led_level;

int led1 = A3;
int led2 = D7;
int num = 1;

bool lightStatus = false;

const char* serviceUuid = "4677062c-ad02-4034-9abf-98581772427c"; //service
const char* light         = "dc13b36a-3499-46b0-ac11-5ac0173c4cc5"; //red char
const char* light2       =  "26f260de-0b93-4352-baa3-56b8be1e606a"; //green char 

//Static function for handling Bluetooth Low Energy callbacks
static void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer, void* context) {
  // Sets the global level
  if( context == light ) {
    m_led_level.light = data[0];
}

  if( context == light2 ) {
    m_led_level.light2 = data[0];
}

}

void setup() {

// RGB.control(true);
// RGB.control(m_led_level.green);

pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);

  // Set the RGB BLE service
BleUuid rgbService(serviceUuid);

BleCharacteristic redCharacteristic("lightValue", BleCharacteristicProperty::WRITE_WO_RSP, light, serviceUuid, onDataReceived, (void*)light);
BleCharacteristic blueCharacteristic("lightValue", BleCharacteristicProperty::WRITE_WO_RSP, light2, serviceUuid, onDataReceived, (void*)light2);


 // Add the characteristics
 BLE.addCharacteristic(redCharacteristic);
 BLE.addCharacteristic(blueCharacteristic);

 // Advertising data
 BleAdvertisingData advData;

 // Add the RGB LED service
 advData.appendServiceUUID(rgbService);

 // Start advertising!
 BLE.advertise(&advData);

}

void loop() {


if(m_led_level.light){
            digitalWrite(led1, HIGH);
            Particle.variable("light1", "On");
} else {
           digitalWrite(led1, LOW);
           Particle.variable("light1", "Off");
}


if(m_led_level.light2){
            digitalWrite(led2, HIGH);
            Particle.variable("light2", "On");
} else {
           digitalWrite(led2, LOW);
           Particle.variable("light2", "Off");
}


delay(500);
}