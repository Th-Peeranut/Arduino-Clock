# Description
Features
1. Show current date & time
2. Can set alarm clock (up to 3 clocks at the same time)
3. Countdown Timer
4. Count Up Timer

Limitations
- available only device is online (by Wi-Fi)

## Tools
- Hardware
  - KidBright32 v1.3
- Software
  - Arduino IDE v1.8.19
  - Blynk (mobile app)

## Libraries used
1. Alarm Clock - [TimeAlarms.h](https://github.com/PaulStoffregen/TimeAlarms)
2. Countdown & Count up Timer - [Countimer.h](https://github.com/Th-Peeranut/Countimer) 
3. Blynk App & Notify - [Blynk.h](https://docs.blynk.io/en/legacy-platform/legacy-articles/what-do-i-need-to-blynk)

# User Interface
![tab1](https://user-images.githubusercontent.com/86977897/176155731-aca4c05c-e14f-4a42-9a9c-764c5c6d9855.jpg)
![tab2](https://user-images.githubusercontent.com/86977897/176156294-ced5ef13-8eb9-4f56-b7ce-e955448ece4b.jpg)

# Installation
`$ git clone https://github.com/Embedded-Design-System-Laboratory/RTC-LED-Clock.git`<br/>

## Don't Forget to fill data
1. /main
    - ssid
    - password
2. /blynk.h
    - BLYNK_AUTH_TOKEN
