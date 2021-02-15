m = midi_in_create();

midi_in_open_port(m, 0);
show_debug_message(string_replace("Opened: dev","dev",midi_in_get_port_name(m,0)));

midi_in_start_streaming(m);