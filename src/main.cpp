#include <iostream>

#include "dfa.hpp"

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

auto main() noexcept -> int
{
    fsm::dfa_t autom;

    autom.add_state(0, fsm::accepting | fsm::starting);
    autom.add_state(1);
    autom.add_state(2);
    autom.add_state(3, fsm::accepting);

    autom.add_transition(0, 'a', 1);
    autom.add_transition(0, 'b', 2);
    autom.add_transition(2, 'a', 3);

    std::vector<char> input;
    std::vector<char> input2{ { 'b', 'a' } };
    std::vector<char> input3{ { 'b', 'b' } };
    std::vector<char> input4{ { 'c', 'x' } };

    std::cout << "Accepting input? " << accepts(autom, input) << std::endl;
    autom.reset();
    std::cout << "Accepting input2? " << accepts(autom, input2) << std::endl;
    autom.reset();
    std::cout << "Accepting input3? " << accepts(autom, input3) << std::endl;
    autom.reset();
    std::cout << "Accepting input4? " << accepts(autom, input4) << std::endl;
    autom.reset();
    std::cout << "Accepting input? " << accepts(autom, input) << std::endl;
    autom.reset();
    std::cout << "Accepting input2? " << accepts(autom, input2) << std::endl;
}
