# mBot-Sweeper

An autonomous cleaning robot built using an **mBot** platform, enhanced with **ultrasonic obstacle detection**, **line following**, and an **IR-based kill switch** for controlled stopping. This project was part of a university engineering module, developed by a team of 7.

---
## High level design

The PDF in this repo is a scaled up version of our protoype where the our group discusses and presents calculations for a market-ready product

## Overview

The mBot-Sweeper simulates a basic smart vacuum cleaner. It moves in a randomized cleaning pattern, avoids obstacles using an ultrasonic sensor, follows lines, and stops operation immediately when triggered by an IR detection system.

The system was designed with:

- **Obstacle avoidance**
- **Line sensing**
- **IR safety stop**
- **Randomized turns for area coverage**

---

## Hardware Components

- mBot chassis with DC motors and onboard controller
- **Ultrasonic sensor** (PORT 4) – for obstacle detection
- **Line follower sensor** (PORT 2) – to detect floor markings
- **IR receiver circuit** (custom soldered, on A2)
- **Secondary analog sensor** (A3) – for miscellaneous sensing / debugging
- **Buzzer** – alerts when certain sensor values are triggered

---

## Features

| Feature                | Description                                                              |
|------------------------|---------------------------------------------------------------------------|
| Random Cleaning     | Bot moves forward with periodic random left/right turns                  |
| Obstacle Avoidance  | Stops and redirects when ultrasonic sensor detects an object (<10 cm)    |
| Line Detection      | Uses line follower to reverse and turn when crossing boundary lines      |
| IR Stop Mechanism   | Immediately halts operation when IR signal is detected (<170 threshold)  |
| Buzzer Alert        | Activates tone when analog signal > 20                                   |

---

## Core Logic 

- Main loop checks for:
  - IR override (`killBot()`)
  - Obstacle proximity (`ultraSensor`)
  - Line detection (`lineFinder`)
- Random turns and backtracking implemented using `random()` and `millis()`
- Interrupt-safe design ensures robot halts instantly under certain conditions

---

## System Behavior

```text
If IR received (A2 < 170):       → Immediately stop all motors
If Ultrasonic < 10 cm:          → Stop, turn randomly, continue
If Line Detected:               → Backtrack and turn
Else:                           → Move forward and buzz if A3 > 20
