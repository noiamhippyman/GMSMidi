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

PointerManager<RtMidiIn*> midi_in_ptrs;
PointerManager<RtMidiOut*> midi_out_ptrs;

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

GMS_DLL const char* midi_in_get_port_name(double midi_in_id) {
	RtMidiIn* midi_in = midi_in_ptrs.get(midi_in_id);
	if (midi_in == nullptr) return "";
	return midi_in->getPortName().c_str();
}

GMS_DLL double midi_out_create() {
	return midi_out_ptrs.add(new RtMidiOut());
}

GMS_DLL double midi_out_destroy(double id) {
	return midi_out_ptrs.remove(id);
}

