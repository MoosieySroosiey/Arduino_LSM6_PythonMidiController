# Arduino_LSM6_PythonMidiController

Arduino IMU to MIDI Converter

This project provides a way to convert Inertial Measurement Unit (IMU) sensor data from an Arduino into MIDI signals that can be used in digital audio workstations (DAWs), musical instruments, or any software that accepts MIDI input.
Features

    Converts real-time accelerometer data from an LSM6 IMU sensor to MIDI control change messages.
    Averages the IMU data to provide smooth MIDI control.
    Easily configurable for different MIDI controllers and mappings.
    Provides a virtual MIDI port for easy integration with software.

Prerequisites

Before you begin, ensure you have met the following requirements:

    An Arduino board with an LSM6 IMU sensor connected.
    The Arduino IDE installed on your computer for uploading the sketch to the Arduino board.
    Python 3 installed on your computer for running the MIDI conversion script.
    mido, python-rtmidi, and pyserial Python libraries installed for MIDI and serial communication.

Installation Guide
Arduino Setup

    Connect your LSM6 IMU sensor to your Arduino board.
    Open the provided Arduino sketch in the Arduino IDE.
    Upload the sketch to your Arduino board.

Python Environment Setup

    Install Python 3 if you haven't already. You can download it from the official Python website.

    Install the required Python libraries by running the following commands in your terminal:

bash

pip install mido python-rtmidi pyserial

Running the MIDI Converter Script

    Connect the Arduino to your computer via USB.

    Open a terminal or command prompt window.

    Navigate to the directory where the Python script is located.

    Run the Python script with the correct serial port:

bash

python serial_to_midi.py COM3  # Replace COM3 with your actual port

Virtual MIDI Port Setup

For Windows users, you may need to install a virtual MIDI port software like loopMIDI.

For macOS and Linux users, the system's built-in virtual MIDI ports can be used.
Usage

Once you have the Arduino and the Python script running, open your DAW or MIDI software and look for the virtual MIDI port named "VirtualMIDI" or the name you have specified. Use this MIDI port as an input source for controlling your software.
