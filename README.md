# WatchKeeper
WatchKeeper keeps a close watch over owned assets.

# Plan
1. Get T-SIM7000G reporting GPS position over cellular network with MQTT to VPS. Send JSON.
2. Connect spare server PC to VPS.
3. Get server to process if GPS reports are outside of boundary (eg 200m from set location).
4. Server to push email notification from doman already owned.

## Progress Report
- 23 May 2026:
Setup Dell Optiplex 3050 SFF with Ubuntu Server LTS and wired into network. Set static IP address and confirmed maintaining address with SSH connection after reboots.
- 19 May 2026:
Decided to put the Pi and camera aside for now to focus on a lower power GPS logger. Ordered a T-SIM7000G from LilyGo and Adafruit MPU-6050 for testing. Will have the T-SIM report back to my home server (at this stage) via VPS as to not expose my home network. Then planning on sending an email if the device goes outside of a set radius from its home. Working on getting this to a MVP stage for a family member as quickly as I reasonably can.
- 27 April 2026:
Got Pi to stream video over local network using MediaMTX. Setup was far easier than I imagined it was going to be.
![Screenshot of stream from Pi.](/Progress%20Images/web_screenshot.jpeg)

![My Pi is currently atop my PC in the absolute most minimal craddle I could print on my Ender 3. Will work on a better way of mounting the camera and other sensors now I have a P2S.](/Progress%20Images/Pi_on_PC.jpeg)

## Learning Log
20 May 2026:
First introductuon to MQTT, Node-RED and VPS.
