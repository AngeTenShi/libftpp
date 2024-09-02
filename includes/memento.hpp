#ifndef MEMENTO_HPP
#define MEMENTO_HPP

#include "data_buffer.hpp"

class Memento
{
	public :
	class Snapshot : public DataBuffer
	{
		friend class Memento;
		public :
			Snapshot() = default;
	};
		Memento() = default;
		~Memento() = default;
		virtual void _saveToSnapshot(Snapshot& snapshotToFill) = 0;
		virtual void _loadFromSnapshot(Snapshot& snapshot) = 0;
		void load(const Memento::Snapshot& state);
		Snapshot save();
	private:
		Memento(const Memento& other) = delete;
		Memento& operator=(const Memento& other) = delete;
		Memento::Snapshot _snapshot;
};

#endif
