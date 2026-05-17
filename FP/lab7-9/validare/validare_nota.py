from domeniu.note import Note
from exceptii.EroareValidare import EroareValidare


class ValidareNota:
    def validare_nota(self, nota: Note):

        erori = ""

        id_student = nota.get_id_student()
        id_disciplina = nota.get_id_disciplina()
        valoare = nota.get_nota_student()
        if not isinstance(id_disciplina, int):
            erori += "id disciplina invalid!\n"
        if not isinstance(id_student, int):
            erori += "id student invalid!\n"
        if not isinstance(valoare, float) and not isinstance(valoare, int):
            erori += "nota student tip invalid!\n"
        elif not (valoare >= 0 and valoare <= 10):
            erori += "nota student valoare invalida!\n"

        if len(erori) != 0:
            raise EroareValidare(erori)
