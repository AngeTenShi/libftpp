#ifndef STATE_MACHINE_HPP
# define STATE_MACHINE_HPP

#include <map>
#include <functional>

template <typename TState>
class StateMachine {
	private:
		TState _state;
		std::map<const TState, std::function<void()>> _states;
		std::map<const TState, std::vector<std::pair<TState, std::function<void()>>>> _transitions; // for each state a vector of transitions
	public:
		StateMachine() : _state(static_cast<TState>(0)) {}
		~StateMachine() {}
		void addState(const TState &state)
		{
			_states[state] = [](void) {};
		}
		void addTransition(const TState& startState, const TState& finalState, const std::function<void()>& lambda)
		{
			if (_states.find(startState) == _states.end() || _states.find(finalState) == _states.end())
				throw std::invalid_argument("State not found");
			_transitions[startState].push_back(std::make_pair(finalState, lambda));
		}
		void addAction(const TState& state, const std::function<void()>& lambda)
		{
			if (_states.find(state) == _states.end())
				throw std::invalid_argument("State not found");
			_states[state] = lambda;
		}
		void transitionTo(const TState &state)
		{
			if (state == _state)
				update();
			if (_transitions.find(_state) == _transitions.end())
			{
				throw std::invalid_argument("State not found");
			}
			for (auto &transition : _transitions[_state])
			{
				if (transition.first == state)
				{
					transition.second();
					_state = state;
					return;
				}
			}
			_state = state;
			throw std::invalid_argument("State not found");
		}
		void update()
		{
			if (_states.find(_state) != _states.end())
				_states[_state]();
		}
};

#endif
