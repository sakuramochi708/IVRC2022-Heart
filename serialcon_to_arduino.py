# 起動したては０が入る。
# byte でやりとりしているので、254スケールに変換中！（1024スケールのアナログ値）

import serial
import binascii
import time

# Arduino Port Serect
heart_grabber_port = "COM6"  # head shower motor
heart_crank_port = "COM7"    # heart crank motor
sensing_grab_port = "COM8"   # pressure sensor  

# Open heart crank port
heartcrank = serial.Serial(heart_crank_port, 9600, timeout=0.1)
heartcrank.setDTR(False)     # DTRを常にLOWにしてReset防止
heartcrank.close()
heartcrank.open()

# Open sensing grab port
sensing_grab = serial.Serial(sensing_grab_port, 9600, timeout=0.1)
sensing_grab.setDTR(False)
sensing_grab.close()
sensing_grab.open()

# Open heart grabber port
heartgrabber = serial.Serial(heart_grabber_port, 9600, timeout=0.1)
heartgrabber.setDTR(False)
heartgrabber.close()
heartgrabber.open()

# MOTOR CONTROL INFORMATION
# センシングから送られてきた情報をそのまま握られるほうに流す
while True:
    try:
        # receive serial information (0 - 254)
        String_data = sensing_grab.read()
        int_data = int.from_bytes(String_data, 'big')
        print(int_data)

        # send serial com to crank motor
        byte_data = String_data
        heartcrank.write(byte_data)

        # send serial com to grab motor
        byte_data = String_data
        heartgrabber.write(byte_data)

        # flush serial com
        heartcrank.flush()
        heartgrabber.flush()
        sensing_grab.flush()

    except Exception as e:
        msg = 'false'
        print(msg)

# PORT close
heartcrank.close()
sensing_grab.close()
heartgrabber.close()
