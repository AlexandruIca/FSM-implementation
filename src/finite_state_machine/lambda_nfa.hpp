#ifndef LAMBDA_NFA_HPP
#define LAMBDA_NFA_HPP
#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

#include "fsm.hpp"

namespace fsm {

///
/// \brief Representation of a non-deterministic finite automaton that can
///        consume the empty word.
///
template<typename State = int, typename Alphabet = char, Alphabet Lambda = '\0'>
class lambda_nfa final : public automaton<State, Alphabet>
{
public:
    static constexpr Alphabet lambda = Lambda;

private:
    using transition_t = std::vector<std::pair<Alphabet, State>>;
    std::map<State, transition_t> m_automaton{};
    std::vector<State> m_accepting_states{};
    std::vector<State> m_current_states{};
    State m_starting_state{};
    bool m_aborted{ false };

    auto check_lambda(std::set<State>& to_check, State const& state) -> void
    {
        std::vector<State> with_lambda{ { state } };
        std::size_t index{ 0 };

        do {
            for(auto const& transition : m_automaton[with_lambda[index++]]) {
                if(transition.first == lambda) {
                    with_lambda.push_back(transition.second);
                }
            }
        } while(index < with_lambda.size());

        for(State const& s : with_lambda) {
            to_check.insert(s);
        }
    }

public:
    lambda_nfa() = default;
    lambda_nfa(lambda_nfa const&) = default;
    lambda_nfa(lambda_nfa&&) noexcept = default;
    ~lambda_nfa() noexcept override = default;

    auto operator=(lambda_nfa const&) -> lambda_nfa& = default;
    auto operator=(lambda_nfa&&) noexcept -> lambda_nfa& = default;

    ///
    /// \param kind Is it an accepting/starting state or not?(or both)
    ///
    /// Use like this:
    /// ```cpp
    /// fsm::lambda_nfa_t autom;
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
            m_starting_state = state;
            m_current_states.push_back(m_starting_state);
            return;
        case state_kind::starting_accepting:
            m_accepting_states.push_back(state);
            m_starting_state = state;
            m_current_states.push_back(m_starting_state);
            return;
        default:
            return;
        }
    }

    ///
    /// \warning \p from and \p to must exist in the nfa!
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
        std::set<State> to_check{};
        for(auto const& current_state : m_current_states) {
            for(auto const& transition : m_automaton[current_state]) {
                if(transition.first == input) {
                    to_check.insert(transition.second);
                    this->check_lambda(to_check, transition.second);
                }
            }
        }

        if(to_check.empty()) {
            m_aborted = true;
            return;
        }

        m_current_states.clear();
        m_current_states.assign(to_check.begin(), to_check.end());
    }

    [[nodiscard]] auto aborted() const noexcept -> bool override
    {
        return m_aborted;
    }

    [[nodiscard]] auto accepted() const noexcept -> bool override
    {
        for(auto const& state : m_current_states) {
            auto it = std::find(
                m_accepting_states.begin(), m_accepting_states.end(), state);
            if(it != m_accepting_states.end()) {
                return true;
            }
        }

        return false;
    }

    auto reset() -> void override
    {
        m_current_states.clear();
        m_current_states.push_back(m_starting_state);
        m_aborted = false;
    }
};

using lambda_nfa_t = lambda_nfa<>;

} // namespace fsm

#endif // !LAMBDA_NFA_HPP
