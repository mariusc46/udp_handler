In order to generate and send a UDP frame with a single CAN message (VALID_ID or INVALID_ID) add the following syntax in main.py and call this file:
udp_single_canframe_valid = udp_gen.generate_udp_singleframe(VALID_ID)
udp_gen.send_one_frame(udp_single_canframe_valid)

In order to generate and send a UDP frame with a multiple CAN messages (VALID_ID or INVALID_ID) add the following syntax in main.py and call this file:
udp_multi_canframe = udp_gen.generate_udp_multiframe(NUMBER_OF_CANFRAMES, VALID_ID)
udp_gen.send_one_frame(udp_multi_canframe)

A simple test sequence is implemented and ready to be called in main.py. Speed and mileage is incremented between each new frame. The following sequence is implemented:
- 15 frames with single can message and valid ID
- 1 frame with single can message and invalid ID
- 1 frame with single can message and crc
- 20 frames with single can message and valid ID
- 1 frame with multiple can messages (10 messages all with valid ID) 

If you want to reset the speed and mileage value use the following code:
udp_gen.mileage = 0
udp_gen.speed = 0

The next function will send valid frames until execution of main.py is stopped.
udp_gen send_cyclic_valid_frames(self):

This project was implemented with the following tools:
- python3
- cmake 3.2
- gcc11
