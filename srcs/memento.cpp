#include "memento.hpp"

void Memento::load(const Memento::Snapshot& state)
{
	_loadFromSnapshot(const_cast<Memento::Snapshot&>(state));
}

Memento::Snapshot Memento::save()
{
	_saveToSnapshot(_snapshot);
	return _snapshot;
}
