import mido
import serial
import sys
import time

def map_to_midi(value, in_min, in_max):
    # Ensure the value is within the input range
    value = max(in_min, min(value, in_max))
    # Map the value to the MIDI range
    return int((value - in_min) * 127 / (in_max - in_min))

if len(sys.argv) != 2:
    print("Usage: python serial_to_midi.py <serial_port>")
    sys.exit(1)

serial_port = sys.argv[1]
baud_rate = 9600
midi_port_name = 'LoopMIDIPort1 1'

mido.set_backend('mido.backends.rtmidi')
print(mido.get_output_names())

try:
    with serial.Serial(serial_port, baud_rate, timeout=1) as ser, mido.open_output(midi_port_name) as outport:
        print(f"Connected to {serial_port} at {baud_rate} baud.")
        while True:
            raw_line = ser.readline()
            try:
                line = raw_line.decode('utf-8').rstrip()
                values = [float(x) for x in line.split('\t')]
                if len(values) == 6:
                    cc_val_ax = map_to_midi(values[0], -2.0, 2.0)
                    cc_val_ay = map_to_midi(values[1], -2.0, 2.0)
                    cc_val_az = map_to_midi(values[2], -2.0, 2.0)
                    cc_val_gx = map_to_midi(values[3], -245.0, 245.0)
                    cc_val_gy = map_to_midi(values[4], -245.0, 245.0)
                    cc_val_gz = map_to_midi(values[5], -245.0, 245.0)

                    outport.send(mido.Message('control_change', control=1, value=cc_val_ax))
                    outport.send(mido.Message('control_change', control=2, value=cc_val_ay))
                    outport.send(mido.Message('control_change', control=3, value=cc_val_az))
                    outport.send(mido.Message('control_change', control=4, value=cc_val_gx))
                    outport.send(mido.Message('control_change', control=5, value=cc_val_gy))
                    outport.send(mido.Message('control_change', control=6, value=cc_val_gz))
            except UnicodeDecodeError:
                print(f"Decode error for line: {raw_line.hex()}")
            except ValueError:
                print("Received non-numeric data")
            except IndexError:
                print("Received incomplete data")
            time.sleep(0.01)
except KeyboardInterrupt:
    print("Exiting due to KeyboardInterrupt")
except Exception as e:
    print(f"An error occurred: {e}")
finally:
    print("Script ended. Ports closed if they were open.")
