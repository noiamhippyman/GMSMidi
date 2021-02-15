m = midi_in_create();

midi_in_open_port(m, 0);

midi_in_start_streaming(m);