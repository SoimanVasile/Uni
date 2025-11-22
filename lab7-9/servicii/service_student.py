from domeniu.student import Student
from repository.repositoryStudent import RepoStudent
import random
import string
# from validare.validare_student import EroareValidare


class ServiceStudenti:
    def __init__(self, repo_student: RepoStudent):
        self.__repo_student = repo_student

    def adauga_student(self, student: Student):
        '''
        adauga un student in repo
        :parem student -> Student
        :return -
        '''
        self.__repo_student.adaugare_student_repo(student)

    def creare_nume_rand(self):
        length = self.generate_length()
        charset = string.ascii_letters
        name = ""

        for _ in range(length):
            random_char = random.choice(charset)
            name += random_char

        return name

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
