class Disciplina:

    def __init__(self, id_disciplina: int, nume_disciplina: str, nume_profesor: str):
        self.__id_disciplina = id_disciplina
        self.__nume_disciplina = nume_disciplina
        self.__nume_profesor = nume_profesor

    def get_id_disciplina(self):
        return self.__id_disciplina

    def get_nume_disciplina(self):
        return self.__nume_disciplina

    def get_nume_profesor(self):
        return self.__nume_profesor

    def set_nume_disciplina(self, nume_disciplina: str):
        self.__nume_disciplina = nume_disciplina

    def set_nume_profesor(self, nume_profesor: str):
        self.__nume_profesor = nume_profesor

    def __repr__(self):
        return f"{self.__id_disciplina}: {self.__nume_disciplina}, {self.__nume_profesor}"

    def __eq__(self, other):
        if not isinstance(other, Disciplina):
            return False

        return self.__id_disciplina == other.__id_disciplina and self.__nume_profesor == other.__nume_profesor and self.__nume_disciplina == other.__nume_disciplina
