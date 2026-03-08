#ifndef UI_H
#define UI_H

#include "service_participant.h"
typedef struct{
    ServiceParticipant* service_participant;
} UI;

void run();
UI new_ui(ServiceParticipant* service_participant);
void adauga_participant_ui(UI* ui);
void modifica_participant_ui(UI* ui);

#endif
