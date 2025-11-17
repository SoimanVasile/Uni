class Note:

    def __init__(self, id_nota: int, id_student: int, id_disciplina: int, nota_student: float):
        self.__id_nota = id_nota
        self.__id_student = id_student
        self.__id_disciplina = id_disciplina
        self.__nota_student = nota_student

    def get_id_nota(self):
        return self.__id_nota

    def get_id_student(self):
        return self.__id_student

    def get_nota_student(self):
        return self.__nota_student

    def get_id_disciplina(self):
        return self.__id_disciplina

    def set_nota_student(self, nota_student: float):
        self.__nota_student = nota_student

    def __repr__(self):
        return f"{self.__id_nota}: {self.__id_student}, {self.__id_disciplina}, {self.__nota_student}"
