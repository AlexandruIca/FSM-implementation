#ifndef FINITE_STATE_MACHINE
#define FINITE_STATE_MACHINE
#pragma once

#include <vector>

///
/// \brief Namespace that contains all relevant code for representing finite
///        state machines.
///
namespace fsm {

enum state_kind
{
    none = 0,
    starting = 1,
    accepting = 2,
    starting_accepting = 3
};

///
/// \brief Abstract representation of a finite state machine.
///
/// \tparam State What represents a state(we'll use int).
/// \tparam Alphabet What represents the alphabet(we'll use char).
///
template<typename State, typename Alphabet>
class automaton
{
public:
    automaton() noexcept = default;
    automaton(automaton const&) noexcept = default;
    automaton(automaton&&) noexcept = default;
    virtual ~automaton() noexcept = default;

    auto operator=(automaton const&) noexcept -> automaton& = default;
    auto operator=(automaton&&) noexcept -> automaton& = default;

    ///
    /// \brief Process next input of \ref Alphabet.
    ///
    virtual auto next(Alphabet const& input) -> void = 0;
    ///
    /// \returns true If an unknown input was given to \ref automaton::next.
    ///
    [[nodiscard]] virtual auto aborted() const noexcept -> bool = 0;
    ///
    /// \returns true If the current state that we are at is an accepting state.
    ///
    [[nodiscard]] virtual auto accepted() const noexcept -> bool = 0;
    ///
    /// \brief Get back to the initial state for new input.
    ///
    virtual auto reset() -> void = 0;
};

template<typename State, typename Alphabet>
[[nodiscard]] auto accepts(fsm::automaton<State, Alphabet>& autom,
                           std::vector<Alphabet> const& input) -> bool
{
    if(input.empty()) {
        return autom.accepted();
    }

    for(Alphabet const& tok : input) {
        autom.next(tok);

        if(autom.aborted()) {
            return false;
        }
    }

    return autom.accepted();
}

} // namespace fsm

#endif // !FINITE_STATE_MACHINE
