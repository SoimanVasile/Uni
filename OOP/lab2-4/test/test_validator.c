#include "validator.h"
#include <assert.h>

#include "errors.h"

void test_validator() {
    int scor_valid[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    int scor_invalid1[10] = {-1, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    int scor_invalid2[10] = {11, 5, 5, 5, 5, 5, 5, 5, 5, 5};

    assert(verifica_participant("yaho", "kirky", scor_valid) == SUCCES);
    assert(verifica_participant("yaho", "kirky", scor_invalid1) == ERR_INVALID_SCOR);
    assert(verifica_participant("yaho", "kirky", scor_invalid2) == ERR_INVALID_SCOR);
}
