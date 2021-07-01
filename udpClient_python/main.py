import udp_class
import time

VALID_ID = 0x21A
INVALID_ID = 0x21C
NUMBER_OF_CANFRAMES = 10

udp_gen = udp_class.UdpGenerator()
udp_gen.init_socket()

def simple_test_seq():
    udp_gen.mileage = 0
    udp_gen.speed = 0

    #send 15 valid frames
    for numberOfFrames in range(0,15):
        #generate a new UDP frame
        udp_single_canframe_valid = udp_gen.generate_udp_singleframe(VALID_ID)
        #send frame to UDP port
        udp_gen.send_one_frame(udp_single_canframe_valid)
        time.sleep(1)
        #increase mileage for each new frame
        udp_gen.mileage += 1
        udp_gen.speed += 1

    #send 1 invalid frame (INVALID ID)
    udp_single_canframe_valid = udp_gen.generate_udp_singleframe(INVALID_ID)
    udp_gen.send_one_frame(udp_single_canframe_valid)
    time.sleep(1)
    udp_gen.mileage += 1

    #send 1 invalid frame (INVALID CRC)
    udp_single_canframe_valid = udp_gen.generate_udp_singleframe(VALID_ID, crc=3)
    udp_gen.send_one_frame(udp_single_canframe_valid)
    time.sleep(1)
    udp_gen.mileage += 1

    #send 20 valid frames
    for numberOfFrames in range(0,20):
        #generate a new UDP frame
        udp_single_canframe_valid = udp_gen.generate_udp_singleframe(VALID_ID)
        #send frame to UDP port
        udp_gen.send_one_frame(udp_single_canframe_valid)
        time.sleep(1)
        #increase mileage for each new frame
        udp_gen.mileage += 1
        udp_gen.speed += 1

    #send 1 UDP with multi CAN frames
    udp_multi_canframe = udp_gen.generate_udp_multiframe(NUMBER_OF_CANFRAMES, VALID_ID)
    udp_gen.send_one_frame(udp_multi_canframe)

    udp_gen.mileage = 0
    print("Simple seq done")

#udp_single_canframe_valid = udp_gen.generate_udp_singleframe(VALID_ID)
#send frame to UDP port
#udp_gen.send_one_frame(udp_single_canframe_valid)

#udp_multi_canframe = udp_gen.generate_udp_multiframe(NUMBER_OF_CANFRAMES, VALID_ID)
#udp_gen.send_one_frame(udp_multi_canframe)

#udp_gen.send_cyclic_valid_frames()

simple_test_seq()
