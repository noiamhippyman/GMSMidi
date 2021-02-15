# GMSMidi
 MIDI extension for Gamemaker Studio 2.3+ using RtMidi library.

RtMidi docs: https://www.music.mcgill.ca/~gary/rtmidi/index.html

 Check out the RtMidi docs. Everything is wrapped to match the original api with the exception of the two streaming functions.

 The basic setup is as follows:
 - Create a RtMidiIn instance with *midi_in_create*. This returns the ID.
 - Use *midi_in_get_port_count* and *midi_in_get_port_name* to look at all the available devices.
 - Open a port with an available port using *midi_in_open_port*. Devices are zero indexed.
 - Start streaming midi message data to async social event with *midi_in_start_streaming*.
 - Stop streaming midi message data with *midi_in_stop_streaming*.
 - Close the port with *midi_in_close_port*. If you need to check if it's opened use *midi_in_is_port_open*.
 - Delete the RtMidiIn instance with *midi_in_destroy*.

The GameMaker project has an example on how to handle the midi message data received. I haven't tested the midi_out functions. Feel free to mess with them but I only really expect to use the midi_in functions anyways.