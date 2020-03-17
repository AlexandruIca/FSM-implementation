#include <cstddef>
#include <fstream>
#include <iomanip>
#include <set>
#include <string>

#include "dfa.hpp"

auto main() noexcept -> int
{
    fsm::dfa_t autom;
    std::ifstream f{ "dfa.txt" };
    int num_states{ 0 };
    int starting_state{ 0 };
    int num_accepting_states{ 0 };
    std::set<int> accepting_states{};

    f >> num_states;
    f >> starting_state;
    f >> num_accepting_states;

    for(int i = 0; i < num_accepting_states; ++i) {
        int state{ 0 };
        f >> state;
        accepting_states.insert(state);
    }

    for(int state = 0; state < num_states; ++state) {
        // using signed types may lead to undefined behavior
        std::uint64_t state_kind = fsm::none;

        if(state == starting_state) {
            state_kind |= static_cast<std::uint64_t>(fsm::starting);
        }
        if(accepting_states.find(state) != accepting_states.end()) {
            state_kind |= static_cast<std::uint64_t>(fsm::accepting);
        }

        autom.add_state(state, static_cast<fsm::state_kind>(state_kind));
    }

    int num_transitions{ 0 };
    f >> num_transitions;

    for(int transition = 0; transition < num_transitions; ++transition) {
        int from{ 0 };
        char on{ '\0' };
        int to{ 0 };

        f >> from >> on >> to;

        autom.add_transition(from, on, to);
    }

    // Testing the input
    std::vector<std::string> inputs = {
        { "axbacbbzbbaaa", "axccbya", "axbac", "bacy", "bacyaaac" }
    };

    std::cout << std::boolalpha;

    for(auto const& input : inputs) {
        auto input_vector = std::vector<char>{ input.begin(), input.end() };
        std::cout << "Accepting '" << input << "'? "
                  << fsm::accepts(autom, input_vector) << std::endl;
        autom.reset();
    }
}
