if (async_load[? "event" ] == "MIDI") {
	
	// this is the ID of the instance you created with midi_in_create.
	// so you can know which midi device this came from
	var mid = async_load[? "id" ];
	
	
	
	// MIDI MESSAGE DATA
	var status = async_load[? "status" ];
	var byte1 = async_load[? "byte1" ];
	var byte2 = async_load[? "byte2" ];
	
	var msg_type = midi_message_get_type(status);
	var channel = midi_message_get_channel(status);
	
	switch (msg_type) {
		case MIDI_MSG_TYPE.NOTE_OFF:
			var str = "NOTE OFF|\tChannel: $c\tNote: $n\tVelocity: $v";
			str = string_replace(str,"$c",string(channel));
			str = string_replace(str,"$n",string(byte1));
			str = string_replace(str,"$v",string(byte2));
			show_debug_message(str);
			break;
		case MIDI_MSG_TYPE.NOTE_ON:
			var str = "NOTE ON|\tChannel: $c\tNote: $n\tVelocity: $v";
			str = string_replace(str,"$c",string(channel));
			str = string_replace(str,"$n",string(byte1));
			str = string_replace(str,"$v",string(byte2));
			show_debug_message(str);
			break;
		case MIDI_MSG_TYPE.POLY_AFTER:
			var str = "POLYPHONIC AFTERTOUCH|\tChannel: $c\tNote: $n\tPressure: $v";
			str = string_replace(str,"$c",string(channel));
			str = string_replace(str,"$n",string(byte1));
			str = string_replace(str,"$v",string(byte2));
			show_debug_message(str);
			break;
		case MIDI_MSG_TYPE.CC:
			var str = "CONTROL CHANGE|\tChannel: $c\tCC: $n\tValue: $v";
			str = string_replace(str,"$c",string(channel));
			str = string_replace(str,"$n",string(byte1));
			str = string_replace(str,"$v",string(byte2));
			show_debug_message(str);
			break;
		case MIDI_MSG_TYPE.PC:
			var str = "PROGRAM CHANGE|\tChannel: $c\tProgram: $n";
			str = string_replace(str,"$c",string(channel));
			str = string_replace(str,"$n",string(byte1));
			show_debug_message(str);
			break;
		case MIDI_MSG_TYPE.CHANNEL_AFTER:
			var str = "CHANNEL AFTERTOUCH|\tChannel: $c\tPressure: $n";
			str = string_replace(str,"$c",string(channel));
			str = string_replace(str,"$n",string(byte1));
			show_debug_message(str);
			break;
		case MIDI_MSG_TYPE.PITCH_BEND:
			var str = "PITCH BEND CHANGE|\tChannel: $c\tLSB: $n\tMSB: $v";
			str = string_replace(str,"$c",string(channel));
			str = string_replace(str,"$n",string(byte1));
			str = string_replace(str,"$v",string(byte2));
			show_debug_message(str);
			break;
		default:
			show_debug_message(string_replace("UNRECOGNIZED MIDI MESSAGE STATUS: $s","$s",status));
			break;
	}
}