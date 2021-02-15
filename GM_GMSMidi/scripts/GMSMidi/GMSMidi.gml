#macro MIDI_MSG_NOTE_OFF 128
#macro MIDI_MSG_NOTE_ON 144
#macro MIDI_MSG_POLY_AFTER 160
#macro MIDI_MSG_CC 176
#macro MIDI_MSG_PC 192
#macro MIDI_MSG_CHANNEL_AFTER 208
#macro MIDI_MSG_PITCH_BEND 224

enum MIDI_MSG_TYPE {
	NOTE_OFF,
	NOTE_ON,
	POLY_AFTER,
	CC,
	PC,
	CHANNEL_AFTER,
	PITCH_BEND
}

function midi_message_get_type(status) {
	if (status >= MIDI_MSG_NOTE_OFF and status < MIDI_MSG_NOTE_OFF + 16) {
		return MIDI_MSG_TYPE.NOTE_OFF;
	} else if (status >= MIDI_MSG_NOTE_ON and status < MIDI_MSG_NOTE_ON + 16) {
		return MIDI_MSG_TYPE.NOTE_ON;
	} else if (status >= MIDI_MSG_POLY_AFTER and status < MIDI_MSG_POLY_AFTER + 16) {
		return MIDI_MSG_TYPE.POLY_AFTER;
	} else if (status >= MIDI_MSG_CC and status < MIDI_MSG_CC + 16) {
		return MIDI_MSG_TYPE.CC;
	} else if (status >= MIDI_MSG_PC and status < MIDI_MSG_PC + 16) {
		return MIDI_MSG_TYPE.PC;
	} else if (status >= MIDI_MSG_CHANNEL_AFTER and status < MIDI_MSG_CHANNEL_AFTER + 16) {
		return MIDI_MSG_TYPE.CHANNEL_AFTER;
	} else if (status >= MIDI_MSG_PITCH_BEND and status < MIDI_MSG_PITCH_BEND + 16) {
		return MIDI_MSG_TYPE.PITCH_BEND;
	}
	
	// invalid status
	return -1;
}

function midi_message_get_channel(status) {
	if (status >= MIDI_MSG_NOTE_OFF and status < MIDI_MSG_NOTE_OFF + 16) {
		
		return status - MIDI_MSG_NOTE_OFF + 1;
		
	} else if (status >= MIDI_MSG_NOTE_ON and status < MIDI_MSG_NOTE_ON + 16) {
		
		return status - MIDI_MSG_NOTE_ON + 1;
		
	} else if (status >= MIDI_MSG_POLY_AFTER and status < MIDI_MSG_POLY_AFTER + 16) {
		
		return status - MIDI_MSG_POLY_AFTER + 1;
		
	} else if (status >= MIDI_MSG_CC and status < MIDI_MSG_CC + 16) {
		
		return status - MIDI_MSG_CC + 1;
		
	} else if (status >= MIDI_MSG_PC and status < MIDI_MSG_PC + 16) {
		
		return status - MIDI_MSG_PC + 1;
		
	} else if (status >= MIDI_MSG_CHANNEL_AFTER and status < MIDI_MSG_CHANNEL_AFTER + 16) {
		
		return status - MIDI_MSG_CHANNEL_AFTER + 1;
		
	} else if (status >= MIDI_MSG_PITCH_BEND and status < MIDI_MSG_PITCH_BEND + 16) {
		
		return status - MIDI_MSG_PITCH_BEND + 1;
		
	}
	
	// invalid status
	return -1;
}