from crccheck.crc import Crc8Autosar

import socket
import time

UDP_IP = "127.0.0.1"
UDP_PORT = 4000
CYCLETIME = 1

class UdpGenerator:
    sock = any
    mileage = 0
    speed = 22

    def init_socket(self):
        print("UDP target IP: %s" % UDP_IP)
        print("UDP target port: %s" % UDP_PORT)
        self.sock = socket.socket(socket.AF_INET, 
                     socket.SOCK_DGRAM) # UDP                     

    def generate_can_message(self, mileage, speed, id=None, length=None, crc=None):
        NBO = "big"
        result = (id or 0x21A).to_bytes(2, NBO)
        # print("result \n", result)
        result += (length or 8).to_bytes(1, NBO)
        # print("result \n", result)
        result += mileage.to_bytes(3, NBO)
        # print("mileage ", mileage.to_bytes(3, NBO))
        result += speed.to_bytes(3, NBO)
        # print("result \n", result)
        # print("Computed crc is ", Crc8Autosar.calc(result))
        result += (crc or Crc8Autosar.calc(result)).to_bytes(1, NBO)
        # print("Generated CAN message is", result)
        return result
    
    def generate_udp_singleframe(self, can_id, crc=None):
        return self.generate_can_message(mileage = self.mileage, speed = self.speed, id = can_id, crc=crc)

    def generate_udp_multiframe(self, numberOfCanFrames, can_id):
        udp_multiframe = bytearray()
        for index in range(0, numberOfCanFrames):
            can_frame = self.generate_can_message(mileage = self.mileage, speed = self.speed, id = can_id)
            udp_multiframe += can_frame
            self.mileage +=1
        return udp_multiframe
            
    def send_one_frame(self, udp_package):
        self.sock.sendto(udp_package, (UDP_IP, UDP_PORT))
        print("UDP frame sent", udp_package)

    def send_cyclic_valid_frames(self):
        while(True):
            self.mileage += 1
            udp_package = self.generate_udp_singleframe(0x21A)            
            time.sleep(CYCLETIME)
            self.sock.sendto(udp_package, (UDP_IP, UDP_PORT))
            print("UDP frame sent", udp_package)
