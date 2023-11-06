import mido
import serial
import sys
import time

if len(sys.argv) != 2:
    print("Usage: python serial_to_midi.py <serial_port>")
    sys.exit(1)

serial_port = sys.argv[1]

mido.set_backend('mido.backends.rtmidi')

print(mido.get_output_names())

midi_port_name = 'port_name'

ser = serial.Serial(serial_port, 9600)

try:
    with mido.open_output(midi_port_name) as outport:
        while True:
            if ser.in_waiting:
                line = ser.readline().decode('utf-8').strip()  
                try:
                    avgX, avgY, avgZ = [float(x) for x in line.split('\t')]  
                    cc_val_x = int(63.5 + avgX * 63.5)
                    cc_val_y = int(63.5 + avgY * 63.5)
                    cc_val_z = int(63.5 + avgZ * 63.5)

                    outport.send(mido.Message('control_change', control=1, value=cc_val_x))
                    outport.send(mido.Message('control_change', control=2, value=cc_val_y))
                    outport.send(mido.Message('control_change', control=3, value=cc_val_z))
                except ValueError:
                
                    print("Received non-numeric data")
                time.sleep(0.01)  #Delay to prevent flooding the MIDI port

except KeyboardInterrupt:
    print("MIDI port closed.")
except serial.SerialException as e:
    print(f"Serial error occurred: {e}")
except Exception as e:
    print(f"An error occurred: {e}")
finally:
    ser.close()
