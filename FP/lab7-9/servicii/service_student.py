from domeniu.student import Student
from repository.repositoryStudent import RepoStudent
import random
import string
# from validare.validare_student import EroareValidare


class ServiceStudenti:
    def __init__(self, repo_student: RepoStudent):
        self.__repo_student = repo_student
        self.__history = []

    def save_state(self):
        state = dict(self.__repo_student.get_all_dict())

        self.__history.append(state)

    def undo(self):
        if not self.__history:
            raise ValueError("Nu am cum sa fac undo!")

        restore_state = self.__history.pop()

        self.__repo_student.restore_state(restore_state)

    def adauga_student(self, student: Student):
        '''
        adauga un student in repo
        :parem student -> Student
        :return -
        '''
        self.save_state()
        self.__repo_student.adaugare_student_repo(student)

    def creare_nume_rand(self, length=None):
        if length is None:
            length = self.generate_length()

        if length == 0:
            return ""

        charset = string.ascii_letters
        return random.choice(charset) + self.creare_nume_rand(length - 1)

    def generate_length(self):
        length = random.randint(1, 15)
        return length

    def afiseaza_studentii(self):
        '''
        returneaza lista de studenti
        :return lista de studenti
        '''
        return (self.__repo_student.get_all_studenti())

    def stergere_student(self, id_student: int):
        '''
        sterge un student din repo
        ;parem student -> Student
        :return -
        '''
        id_student = self.__repo_student.stergere_student(id_student)

        return id_student

    def update_student(self, student: Student):
        '''
        actualizeaza un student din repo
        :parem studen -> Student
        :return -
        '''
        self.__repo_student.update_student(student)

    def creare_id_student(self):
        '''
        returneaza cel mai mic id nefolosit
        return cel mai mic id nefolosit
        '''
        return self.__repo_student.creare_id_student()

    def cautare_student(self, id_student: int):
        '''
        cauta studentul cu idul respectiv
        :parem id_student -> idul studentului
        :return studentul cu idul respectiv
        '''
        id_student = self.__repo_student.cautare_student(id_student)

        return id_student
