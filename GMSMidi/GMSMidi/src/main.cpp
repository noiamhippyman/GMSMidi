#define WIN32
#include <vector>
#include "GMS_Ext.hpp"
#include "RtMidi.h"

template <class T>
class PointerManager {
public:
	int add(T item);
	int remove(int id);
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

PointerManager<RtMidiIn*> midi_in_ptrs;
PointerManager<RtMidiOut*> midi_out_ptrs;

GMS_DLL double midi_in_create() {
	return midi_in_ptrs.add(new RtMidiIn());
}

GMS_DLL double midi_in_destroy(double id) {
	return midi_in_ptrs.remove(id);
}

GMS_DLL double midi_out_create() {
	return midi_out_ptrs.add(new RtMidiOut());
}

GMS_DLL double midi_out_destroy(double id) {
	return midi_out_ptrs.remove(id);
}

