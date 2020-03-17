# Structura
In [src/finite\_state\_machine/fsm.hpp](https://github.com/AlexandruIca/LFA_Tema1/blob/master/src/finite_state_machine/fsm.hpp)
am o clasa abstracta `automaton` care reprezinta o interfata si pentru un DFA
si pentru un NFA + o functie `accepts` care verifica daca un automat accepta
un input dat. Un `automaton` trebuie sa implementeze functiile:
* `next` care ia ca parametru un caracter din alfabet si trece in starea/starile
corespunzatoare
* `aborted` care intoarce `true` daca automatul a ajuns la o stare in care
pentru input-ul dat nu se poate duce nicaieri.
* `accepted` care intoarce `true` daca starea curenta este acceptoare/in starile
curente se afla o stare acceptoare.
* `reset` care aduce automatul la starea initiala

In [src/finite\_state\_machine/dfa.hpp](https://github.com/AlexandruIca/LFA_Tema1/blob/master/src/finite_state_machine/dfa.hpp)
am o clasa `dfa` care mosteneste `automaton` si care implementeaza(evident) un
DFA accepter.

In [src/finite\_state\_machine/lambda\_nfa.hpp](https://github.com/AlexandruIca/LFA_Tema1/blob/master/src/finite_state_machine/lambda_nfa.hpp)
am o clasa `lambda_nfa` care mosteneste  la randul ei `automaton`, avand by
default cuvantul lambda reprezentat ca '\0'. In plus mai are functia
`check_lambda` care imi adauga in `m_current_states` starile in care pot sa
ajung doar cu lambda de la o stare data.

In [src/dfa.cpp](https://github.com/AlexandruIca/LFA_Tema1/blob/master/src/dfa.cpp)
si [src/lambda\_nfa.cpp](https://github.com/AlexandruIca/LFA_Tema1/blob/master/src/lambda_nfa.cpp)
sunt testate input-urile date in tema cu ajutorul claselor implementate.

# Rulare
```sh
cmake -Bbuild .
cd build/src/
./dfa
./lambda_nfa
```
