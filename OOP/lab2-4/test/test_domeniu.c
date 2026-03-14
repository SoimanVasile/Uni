#include <string.h>
#include <assert.h>

#include "test_domeniu.h"
#include "participant.h"
#include "equal_overloading.h"

void test_creare_participant(){
char nume[64] = "Shannon";
char prenume[64] = "Claude";
int scor[10] = {10, 10, 10, 9, 10, 10, 9, 10, 9, 10};
    Participant participant = new_participant(nume, prenume, scor);
    
    for (size_t i=0; i<strlen(participant.prenume); i++){
        assert(participant.prenume[i] == prenume[i]);
    }

    for (size_t i=0; i<strlen(participant.nume); i++){
        assert(participant.nume[i] == nume[i]);
    }

    for (size_t i=0; i<10; i++){
        assert(participant.scor[i] == scor[i]);
    }

    free_participant(&participant);
}

void test_get_nume(){
char nume[64] = "Shannon";
char prenume[64] = "Claude";
int scor[10] = {10, 10, 10, 9, 10, 10, 9, 10, 9, 10};
    Participant participant = new_participant(nume, prenume, scor);

    char* get_nume_participant = get_nume(&participant);

    for (size_t i=0; i<strlen(get_nume_participant); i++)
        assert(get_nume_participant[i] == nume[i]);
    free_participant(&participant);
}

void test_get_prenume(){
char nume[64] = "Shannon";
char prenume[64] = "Claude";
int scor[10] = {10, 10, 10, 9, 10, 10, 9, 10, 9, 10};
    Participant participant = new_participant(nume, prenume, scor);

    char* get_prenume_participant = get_prenume(&participant);

    for (size_t i=0; i<strlen(get_prenume_participant); i++)
        assert(get_prenume_participant[i] == prenume[i]);
    free_participant(&participant);
}

void test_get_scor(){
char nume[64] = "Shannon";
char prenume[64] = "Claude";
int scor[10] = {10, 10, 10, 9, 10, 10, 9, 10, 9, 10};

    Participant participant = new_participant(nume, prenume, scor);

    int* get_scor_participant = get_scor(&participant);

    assert(equal(get_scor_participant, scor));
    free_participant(&participant);
}

void test_setters() {
    int scor[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Participant participant = new_participant("VechiNume", "VechiPrenume", scor);
    
    // As discussed before, make sure your setters in participant.c use realloc/free+malloc!
    set_nume(&participant, "NouNume");
    assert(equal(get_nume(&participant), "NouNume") == 1);

    assert(equal(get_nume(&participant), "NouNume1") == 0);

    set_prenume(&participant, "NouPrenume");
    assert(equal(get_prenume(&participant), "NouPrenume") == 1);
    assert(equal(get_prenume(&participant), "NouPrenume1") == 0);

    free_participant(&participant);
}
