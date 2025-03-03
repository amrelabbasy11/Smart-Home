# Smart Home Project

## Overview
This Smart Home project is designed to control and monitor various appliances and features within a home environment. The project focuses on three rooms, with functionalities such as:
- **TV Control**
- **Air Conditioner (AC) Control**
  
![image](https://github.com/user-attachments/assets/a712dbab-9048-4116-8369-ddca80999fed)

# This is the view when we run : 

![image](https://github.com/user-attachments/assets/40a060b4-4bbf-44b6-903b-f688bd95d100)
1. Select Mode.
2. Write Password.
3. Choose The desired room.
4. Choose the action that you want.
   
## Technical Details
- **Microcontroller:** AVR (ATmega32)
- **Communication Protocols:** SPI (Serial Peripheral Interface)
- **Memory Management:** EEPROM (Electrically Erasable Programmable Read-Only Memory)
- **Input Devices:** Keypad
- **Output Devices:** LEDs, LCD Display
- **Sensors:** Temperature sensor (LM35)

## Features
- **Room Modes:**
  - Admin Mode
  - Guest Mode
  - Block Mode
- **Real-Time Control:**
  - Users can interact with the system through the keypad.
  - LCD displays the current mode and status of appliances.
- **Temperature Monitoring:**
  - The LM35 sensor detects room temperature, which can be used to trigger AC control.
- **Data Storage:**
  - EEPROM stores critical data, ensuring persistence across power cycles.

## Collaboration and Validation
- This project was discussed and validated by:
  - **Teaching assistants at ITI** (Information Technology Institute)
  - **Engineers at Valeo Company**
- It was part of the projects I implemented at **IEEE**.

## How to Run the Project
1. **Hardware Setup:** Connect the ATmega32 MCU, keypad, LCD, LEDs, and sensors as shown in the Proteus simulation.
2. **Code Compilation:** Use AVR Studio or any compatible IDE to compile the embedded C code.
3. **Simulation:** Open the Proteus file and run the simulation to test the functionality.
4. **Flashing the Code:** Burn the hex file into the ATmega32 microcontroller.

## Future Enhancements
- Integrate Bluetooth or Wi-Fi modules for remote control.
- Add voice command functionality.
- Implement a mobile app interface.



