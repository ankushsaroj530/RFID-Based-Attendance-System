# 📡 RFID-Based Attendance System using Arduino

## Introduction

This project demonstrates an **RFID-Based Attendance Management System** using the **Arduino UNO** and **RC522 RFID module**. The system automates attendance tracking by identifying students through RFID cards and maintaining digital records in Microsoft Excel.

When a registered RFID card is scanned, the system verifies the UID, increments the attendance count, calculates attendance percentage, displays the details on an LCD screen, and logs the data into Excel in real-time using serial communication (PLX-DAQ).

If an unregistered card is scanned, the system identifies it as an unknown card and prevents unauthorized attendance logging.

---

## Components Required

- Arduino UNO  
- RFID RC522 Module  
- RFID Tags / Cards  
- 16x2 LCD Display (I2C)  
- Jumper Wires  
- Breadboard  
- USB Cable  
- PC/Laptop (for Excel logging using PLX-DAQ)

---

## Connections

### RFID RC522 → Arduino UNO

| RFID RC522 Pin | Arduino UNO Pin |
|----------------|-----------------|
| SDA (SS)       | 10              |
| SCK            | 13              |
| MOSI           | 11              |
| MISO           | 12              |
| RST            | 9               |
| VCC            | 3.3V            |
| GND            | GND             |



### LCD (I2C) → Arduino UNO

| LCD I2C Pin | Arduino UNO Pin |
|-------------|------------------|
| VCC         | 5V               |
| GND         | GND              |
| SDA         | A4               |
| SCL         | A5               |

> I2C Address used in code: `0x27`

---
![Project Image](WhatsApp Image 2026-03-13 at 20.10.52 (1).jpeg)
## Working Principle

1. The RFID reader continuously scans for nearby RFID cards.
2. When a card is detected, the system reads its unique UID.
3. The UID is compared with pre-stored authorized student UIDs.
4. If a match is found:
   - Attendance count is incremented.
   - Attendance percentage is calculated.
   - Student details are displayed on the LCD.
   - Data is sent to Microsoft Excel via serial communication.
5. If no match is found:
   - The system displays **"Unknown Card"**.
   - UID is printed on the Serial Monitor for debugging.

---

## Installation & Setup

1. Install the required Arduino libraries:
   - `SPI.h`
   - `MFRC522.h`
   - `Wire.h`
   - `LiquidCrystal_I2C.h`
   - `TimeLib.h`

2. Connect the hardware components as per the connection table above.

3. Upload the Arduino code to the board.

4. Open PLX-DAQ in Microsoft Excel.

5. Start the Serial Monitor at **9600 baud rate**.

6. Scan an RFID card to begin attendance logging.

---

## How It Works

- Each student has a unique RFID UID stored in the system.
- Attendance is stored in an integer array.
- Attendance percentage is calculated using:

  ```
  percentage = (presentClasses * 100.0) / totalClasses;
  ```

- Date and time are generated using `TimeLib`.
- Data is formatted and transmitted to Excel using serial commands:

  ```
  LABEL,Name,Roll,Semester,Date,Time,Classes Attended,Attendance %
  ```

- The LCD displays:
  - Student Name
  - Roll Number
  - Semester
  - Attendance Percentage
  - Date

---

## Applications

- Educational institutions for automated student attendance  
- Office employee check-in systems  
- Event access control systems  
- Secure RFID-based identity logging  
