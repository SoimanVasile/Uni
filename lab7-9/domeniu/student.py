class Student:

    def __init__(self, id_student: int, nume: str):
        self.__id_student = id_student
        self.__nume = nume

    def get_id_student(self):
        return self.__id_student

    def get_nume(self):
        return self.__nume

    def set_nume(self, nume: str):
        self.__nume = nume

    def __repr__(self):
        return f"[id_student: {self.__id_student}, nume_student: {self.__nume}]"
