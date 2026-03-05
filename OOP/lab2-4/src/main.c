#include "repo_participant.h"

int main(){
    char nume[64] = "Ion";
    char prenume[64] = "Pop";
    int scor[10] = {10, 9, 8, 8, 10, 7, 6, 6, 4, 1};
    Participant participant = new_participant(nume, prenume, scor);
    RepoParticipant repo_participant = new_repo_participant();
    adauga_participant(&repo_participant,participant);
    print_repo_participant(&repo_participant);
    return 0;
}
