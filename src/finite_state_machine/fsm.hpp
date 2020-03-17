#ifndef FINITE_STATE_MACHINE
#define FINITE_STATE_MACHINE
#pragma once

///
/// \brief Namespace that contains all relevant code for representing finite
///        state machines.
///
namespace fsm {

enum state_kind
{
    none = 0,
    starting = 1,
    accepting = starting << 1,
    starting_accepting = starting | accepting
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
    virtual ~automaton() noexcept = default;

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

} // namespace fsm

#endif // !FINITE_STATE_MACHINE
