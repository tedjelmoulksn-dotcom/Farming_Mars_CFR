# Farming Mars — Competition Robotics

Arduino mobile-robot project for the 2024 French Robotics Cup. A differential-drive chassis with MD25/EMG30 motor control, ultrasonic sensing, a servo gripper and a solar-panel arm executes a predefined competition route.

![Project illustration](assets/2024_table-1200x552.png)

## Repository guide

| Location | Contents |
|---|---|
| [arduino/](arduino/) | Match sketches, drivetrain and gripper experiments |
| [documentation/](documentation/) | Team report, presentation and component-selection note |
| [assets/](assets/) | Playing field, wiring and hardware photographs |
| [archive/](archive/) | Earlier integration and gripper variants |
| [third_party/](third_party/) | Original Adeept arm-kit examples, tools and documentation |

## Getting started

Choose the sketch for the target subsystem and open it in the Arduino IDE. Check board selection, I²C addresses, motor mode and master/slave serial connections against the report before uploading.

## Project context

Eight-student team project at Sup Galilée. Tedj worked in the drivetrain subgroup. Competition motion is primarily time-based; encoder-reading experiments are present but do not establish closed-loop route navigation. Adeept files retain their original attribution.
