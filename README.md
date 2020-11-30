# Control System Of A Robot In Different Modes
<div style="text-align:center"><img src="https://i.ibb.co/sb1QYrQ/image0.png" /></div>

> This a first year student project
---

### Table of Contents

- [Description](#description)
- [Specifications](#specifications)
- [The Hardware](#the-hardware)
- [System Architecture](#system-architecture)
- [Software Architecture](#software-architecture)
- [Project Files](#project-files)
- [Author Info](#author-info)

---

## Description

The goal of this project is to control a Robot based on two-dimension coordinates of a given space (room, etc.).

All the commands will be made with the use of a remote control.

---

## Specifications

- **Operating modes :** 

    The robot control system must operate in 4 different modes, as follows :

    - *Mode 1 :* Real-time control
    - *Mode 2 :* Control through a path given in INPUT
    - *Mode 3 :* Entering a path to store it in memory
    - *Mode 4 :* Control through a path already stored in memory

- **User interface :** 

    The user interfaces the system from :
        
    1. A remote control to do everything
    2. An LCD display for guidance
    3. A "buzzer alarm" for accompanying sound effects (pressing the keys on the remote control, obstacle detection)
    4. "LEDs" for signaling related to different operations

---

## The Hardware

- 1 x Robot chassis
- 1 x Remote control
- 1 x Infrared sensor
- 4 x LEDs
- 1 x Buzzer alarm
- 1 x Ultrasonic sensor
- 1 x LCD display
- 1 x DC Motor Driver : H Bridge Board L9110
- 1 x Arduino Uno board
- 1 x Battery
- Breadboard
- Routing cables

---

## System Architecture

### Abstract view

<div style="text-align:center"><img src="https://i.ibb.co/3YCshYK/image2.png" /></div>

### Routing view

<div style="text-align:center"><img src="https://i.ibb.co/B6Bycbt/image8.png" /></div>

---

## Software Architecture

- ***Preliminary program :***

<div style="text-align:center"><img src="https://i.ibb.co/KD7NxCV/image7.png" /></div>

- ***Mode 1 :***

<div style="text-align:center"><img src="https://i.ibb.co/GpkLdwF/image3.png" /></div>

- ***Mode 2 :***

<div style="text-align:center"><img src="https://i.ibb.co/YR529Jy/image4.png" /></div>

- ***Mode 3 :***

<div style="text-align:center"><img src="https://i.ibb.co/qCZm9Sg/image5.png" /></div>

- ***Mode 4 :***

<div style="text-align:center"><img src="https://i.ibb.co/D4v3ZRR/image6.png" /></div>

---

## Project Files

The project contains one single file :

1. [Arduino_Code.ino](src/Arduino_Code.ino) : contains the code to be run on the Arduino card

---

## Author Info

- Email - oussama.oulkaid@gmail.com
- LinkedIn - [Oussama Oulkaid](https://www.linkedin.com/in/oulkaid)
