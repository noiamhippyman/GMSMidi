#define WIN32
#include <vector>
#include "GMS_Ext.hpp"
#include "RtMidi.h"

template <class T>
class PointerManager {
public:
	int add(T item);
	int remove(int id);
	T get(int id);
	int get(T item);
private:
	std::vector<T> m_pointer_list;
};

template <class T>
int PointerManager<T>::add(T ptr) {
	if (m_pointer_list.empty()) {
		m_pointer_list.push_back(ptr);
		return 0;
	}

	const int size = m_pointer_list.size();
	for (int i = 0; i < size; ++i) {
		if (m_pointer_list[i] == nullptr) {
			m_pointer_list[i] = ptr;
			return i;
		}
	}

	m_pointer_list.push_back(ptr);
	return size;
}

template <class T>
int PointerManager<T>::remove(int id) {
	if (m_pointer_list.empty()) {
		return -1;
	}

	const int size = m_pointer_list.size();
	if (id < 0 || id >= size) {
		return -1;
	}

	delete m_pointer_list[id];
	m_pointer_list[id] = nullptr;
	return 0;
}

template <class T>
T PointerManager<T>::get(int id) {
	if (m_pointer_list.empty()) return nullptr;

	const int size = m_pointer_list.size();
	if (id < 0 || id >= size) return nullptr;

	return m_pointer_list[id];
}

template <class T>
int PointerManager<T>::get(T item) {
	if (m_pointer_list.empty()) return -1;

	const int size = m_pointer_list.size();
	for (int i = 0; i < size; ++i) {
		if (m_pointer_list[i] == item) {
			return i;
		}
	}

	return -1;
}

PointerManager<RtMidiIn*> midi_in_ptrs;
PointerManager<RtMidiOut*> midi_out_ptrs;



void midi_in_callback(double deltatime, std::vector< unsigned char > *message, void *userData)
{
	GMLevent e("MIDI");
	RtMidiIn* m = (RtMidiIn*)userData;

	e.add_var("id", midi_in_ptrs.get(m));
	e.add_var("status", (int)message->at(0));
	e.add_var("byte1", (int)message->at(1));
	if (message->size() > 2) {
		e.add_var("byte2", (int)message->at(2));
	}
	e.trigger();

}

GMS_DLL double midi_in_create() {
	return midi_in_ptrs.add(new RtMidiIn());
}

GMS_DLL double midi_in_destroy(double id) {
	return midi_in_ptrs.remove(id);
}

GMS_DLL double midi_in_open_port(double midi_in_id, double port_id) {
	RtMidiIn* midi_in = midi_in_ptrs.get(midi_in_id);
	if (midi_in == nullptr) return -1;
	midi_in->openPort(port_id);
	return 0;
}

GMS_DLL double midi_in_close_port(double midi_in_id) {
	RtMidiIn* midi_in = midi_in_ptrs.get(midi_in_id);
	if (midi_in == nullptr) return -1;
	midi_in->closePort();
	return 0.0;
}

GMS_DLL double midi_in_is_port_open(double midi_in_id) {
	RtMidiIn* midi_in = midi_in_ptrs.get(midi_in_id);
	if (midi_in == nullptr) return -1;
	return midi_in->isPortOpen() ? GMS_TRUE : GMS_FALSE;
}

GMS_DLL double midi_in_get_port_count(double midi_in_id) {
	RtMidiIn* midi_in = midi_in_ptrs.get(midi_in_id);
	if (midi_in == nullptr) return -1;
	return midi_in->getPortCount();
}

GMS_DLL const char* midi_in_get_port_name(double midi_in_id, double port_id) {
	RtMidiIn* midi_in = midi_in_ptrs.get(midi_in_id);
	if (midi_in == nullptr) return "";
	return midi_in->getPortName(port_id).c_str();
}

GMS_DLL double midi_in_start_streaming(double midi_in_id) {
	RtMidiIn* midi_in = midi_in_ptrs.get(midi_in_id);
	if (midi_in == nullptr) return -1;

	midi_in->setCallback(midi_in_callback, midi_in);
	return 0;
}

GMS_DLL double midi_in_stop_streaming(double midi_in_id) {
	RtMidiIn* midi_in = midi_in_ptrs.get(midi_in_id);
	if (midi_in == nullptr) return -1;
	midi_in->cancelCallback();
	return 0;
}

GMS_DLL double midi_out_create() {
	return midi_out_ptrs.add(new RtMidiOut());
}

GMS_DLL double midi_out_destroy(double id) {
	return midi_out_ptrs.remove(id);
}

GMS_DLL double midi_out_open_port(double midi_out_id, double port_id) {
	RtMidiOut* midi_out = midi_out_ptrs.get(midi_out_id);
	if (midi_out == nullptr) return -1;
	midi_out->openPort(port_id);
	return 0;
}

GMS_DLL double midi_out_close_port(double midi_out_id) {
	RtMidiOut* midi_out = midi_out_ptrs.get(midi_out_id);
	if (midi_out == nullptr) return -1;
	midi_out->closePort();
	return 0.0;
}

GMS_DLL double midi_out_is_port_open(double midi_out_id) {
	RtMidiOut* midi_out = midi_out_ptrs.get(midi_out_id);
	if (midi_out == nullptr) return -1;
	return midi_out->isPortOpen() ? GMS_TRUE : GMS_FALSE;
}

GMS_DLL double midi_out_get_port_count(double midi_out_id) {
	RtMidiOut* midi_out = midi_out_ptrs.get(midi_out_id);
	if (midi_out == nullptr) return -1;
	return midi_out->getPortCount();
}

GMS_DLL const char* midi_out_get_port_name(double midi_out_id, double port_id) {
	RtMidiOut* midi_out = midi_out_ptrs.get(midi_out_id);
	if (midi_out == nullptr) return "";
	return midi_out->getPortName(port_id).c_str();
}

GMS_DLL double midi_out_send_message(double midi_out_id, double status, double byte1, double byte2) {
	RtMidiOut* midi_out = midi_out_ptrs.get(midi_out_id);
	if (midi_out == nullptr) return -1;

	std::vector<unsigned char> message;
	message[0] = status;
	message[1] = byte1;
	message[2] = byte2;
	midi_out->sendMessage(&message);

	return 0;
}