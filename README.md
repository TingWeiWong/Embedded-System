# Automatic Firearm 

<p align="center">
  <img src="https://github.com/TingWeiWong/Embedded-System/blob/master/Cardboard-Gun.jpg">
</p> 

## Motivation

Inspired by the "Edna mode" scene in the movie "The Incredibles", we developed an automatic system that 
alarms owner of trespassers and attacks accordingly.

## Components

1. DC Motor
2. Cardboard Gun
3. Grove PIR Sensor
4. Buzzer 
5. STM32IOT Node I
6. STM32IOT Node II

## Structure

<p align="center">
  <img src="https://github.com/TingWeiWong/Embedded-System/blob/master/block-diagram.png" width="100%" height="100%">
</p> 

### DC Motor
* STM32 GPIO library with digital output
* Use relay to turn on/off motor


Motor Control Callback Function
```cpp
void on_data_written(const GattWriteCallbackParams *params) {
	if ((params->handle == _led_service->getValueHandle()) && (params->len == 1)) {
		_actuated_led = *(params->data);
		// \control = *(params->data);
		relay = *(params->data);
		while (control == 1) {
			for (int i = 0; i < 20; i++) {
				relay = i % 2;
				if (relay == 1) {
					wait(1);
				}
				else {
					wait(0.075);
				}
			}
			control = 0;
			relay = 1;
		}
		cout << "relay = " << relay << endl;
		// cout << "*params->data = " << *(params->data) << endl;
		// cout << "params->data = " << (params->data) << endl;
		// cout << "params->len = " << (params->len) << endl;
		cout << "actuated led = " << _actuated_led << endl;


	}
```
### Cardboard Gun

### Grove PIR Sensor
* Digital Input at D5 pin 
* Detects motion change within 6 meters and 120º angle
* Outputs 1 if motion detected 0 otherwise

### Buzzer
* Digital Output at D12 pin
* 3V power supply required
* Rings when digital output is high 

Function for Sensor and Buzzer 
```cpp

DigitalOut buzzer(D12);

InterruptIn motion(D5);


int motion_detected = 0;
 
void irq_handler(void)
{
    motion_detected = 1;
}
```



### STM32IOT Node I 

Main Function for Motor Control
```cpp


int main()
{
    relay = 1;
    BLE &ble = BLE::Instance();
    ble.onEventsToProcess(schedule_ble_events);

    std::cout << "After on Events" << endl;

    LEDDemo demo(ble, event_queue);

    std::cout << "After demo " << endl;
    std::cout << "BLE = " << (&ble) << endl;
    // std::cout << "BLE data = " << ble.data << endl;
    // printf("%d", ble);
    demo.start();


    return 0;
}
```


### STM32IOT Node II
Main Function for Buzzer Sensor Integration
```cpp
int main()
{
    int cnt = 0;
    motion.rise(&irq_handler);  
    while(1) {
        if(motion_detected) {
            cnt++;
            motion_detected = 0;
            printf("Hello! I've detected %d times since reset\n", cnt);
            for (int i = 0; i < 11; i++) {
                buzzer = i % 2;
                cout << "Buzzer = " << buzzer << endl;
                wait(1);
            }
        }
    }
}
```

## Difficulties

### Software
<p align="center">
  <img src="https://github.com/TingWeiWong/Embedded-System/blob/master/finite_state.png" width="100%" height="100%">
</p> 

* Unable to break from active mode to detect mode after writing value to STM32
* First attempt : Use finite state machine to transfer between two states
* Solution : We separate the code into two STM32s 

### Hardware

<p align="center">
  <img src="https://github.com/TingWeiWong/Embedded-System/blob/master/hardware.png" width="100%" height="100%">
</p> 

* Sensor too sensitive
* Solution : Unplug after first siren

## Result

1. Demo Video

[![Demo1](https://github.com/TingWeiWong/Embedded-System/blob/master/youtube.png)](https://www.youtube.com/watch?v=p7qkj2737BU&feature=youtu.be)

## Reference

1. [arm MBED](https://os.mbed.com/docs/mbed-os/v5.14/apis/index.html)

2. [stackoverflow](https://stackoverflow.com/)

3. [amr mcl](https://www.youtube.com/user/MCIsection)
