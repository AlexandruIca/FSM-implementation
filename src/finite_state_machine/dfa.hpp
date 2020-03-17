#ifndef DFA_HPP
#define DFA_HPP
#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "fsm.hpp"

namespace fsm {

///
/// \brief Representation of a deterministic finite automaton.
///
template<typename State = int, typename Alphabet = char>
class dfa : public automaton<State, Alphabet>
{
private:
    using transition_t = std::vector<std::pair<Alphabet, State>>;
    std::map<State, transition_t> m_automaton{};
    std::vector<State> m_accepting_states{};
    State m_starting_state{};
    State m_current_state{};
    bool m_aborted{ false };

public:
    dfa() = default;
    dfa(dfa const&) = default;
    dfa(dfa&&) noexcept = default;
    ~dfa() noexcept override = default;

    auto operator=(dfa const&) -> dfa& = default;
    auto operator=(dfa&&) noexcept -> dfa& = default;

    ///
    /// \param kind Is it an accepting/starting state or not?(or both)
    ///
    /// Use like this:
    /// ```cpp
    /// fsm::dfa_t autom;
    /// autom.add_state(0, fsm::starting | fsm::accepting);
    /// autom.add_state(1);
    /// autom.add_state(2, fsm::accepting);
    /// ```
    ///
    auto add_state(State const& state, int kind = state_kind::none) -> void
    {
        if(m_automaton.find(state) != m_automaton.end()) {
            std::cout << "State already in automaton!" << std::endl;
            return;
        }

        m_automaton.emplace(std::make_pair(state, transition_t{}));

        switch(kind) {
        case state_kind::accepting:
            m_accepting_states.push_back(state);
            return;
        case state_kind::starting:
            m_current_state = m_starting_state = state;
            return;
        case state_kind::starting_accepting:
            m_accepting_states.push_back(state);
            m_current_state = m_starting_state = state;
            return;
        default:
            return;
        }
    }

    ///
    /// \warning \p from and \p to must exist in the dfa!
    ///
    auto add_transition(State const& from, Alphabet const& on, State const& to)
        -> void
    {
        bool exists_from = m_automaton.find(from) != m_automaton.end();
        bool exists_to = m_automaton.find(to) != m_automaton.end();

        if(!exists_from || !exists_to) {
            std::cout << "Transition parameters are invalid!" << std::endl;
            return;
        }

        m_automaton[from].emplace_back(on, to);
    }

    auto next(Alphabet const& input) -> void override
    {
        for(auto const& transition : m_automaton[m_current_state]) {
            if(transition.first == input) {
                m_current_state = transition.second;
                return;
            }
        }

        m_aborted = true;
    }

    [[nodiscard]] auto aborted() const noexcept -> bool override
    {
        return m_aborted;
    }

    [[nodiscard]] auto accepted() const noexcept -> bool override
    {
        auto it = std::find(m_accepting_states.begin(),
                            m_accepting_states.end(),
                            m_current_state);

        return it != m_accepting_states.end();
    }

    auto reset() -> void override
    {
        m_current_state = m_starting_state;
        m_aborted = false;
    }

    [[deprecated("Only for testing!")]] inline auto starting_state() const
        noexcept -> State const&
    {
        return m_starting_state;
    }

    [[deprecated("Only for testing!")]] inline auto accepting_states() const
        noexcept -> std::vector<State> const&
    {
        return m_accepting_states;
    }
};

using dfa_t = dfa<>;

} // namespace fsm

#endif // !DFA_HPP
