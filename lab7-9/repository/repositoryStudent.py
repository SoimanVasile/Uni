from domeniu.student import Student
from exceptii.EroareRepo import EroareRepo


class RepoStudent:

    def __init__(self):
        self.__studenti = {}

    def creare_id_student(self):
        id_existente = list(self.__studenti.keys())
        if len(id_existente) == 0:
            return 1
        id_existente.sort()
        id_prev = id_existente[0]
        for id in id_existente:
            if (id-id_prev > 1):
                return id_prev+1

        return len(id_existente)+1

    def adaugare_student_repo(self, student: Student):
        '''
        functie care adauga un student nou in repository
        :parem student -> student
        :return -
            Raise valueError daca numele studentului nu i bun
        '''

        id_student = student.get_id_student()

        if id_student in self.__studenti:
            raise EroareRepo("Id student exista deja!\n")

        self.__studenti[id_student] = student

        return id_student

    def stergere_student(self, id_student: int):
        '''
        functie care sterge un student din repo
        :parem student -> student
        :return -
        '''

        if id_student not in self.__studenti:
            raise EroareRepo("Id student nu exista!\n")

        del self.__studenti[id_student]

    def update_student(self, student: Student):
        '''
        functie care actualizeaza un student
        :parem student -> student
        :return -
        '''

        id_student = student.get_id_student()

        if id_student not in self.__studenti:
            raise EroareRepo("Id student nu exista!\n")

        self.__studenti[id_student] = student

    def get_all_studenti(self):
        '''
        returneaza lista de studenti
        :return lista de studenti
        '''
        return list(self.__studenti.values())

    def cautare_student(self, id_student: int):
        '''
        returneaza studentul cu idul respectiv
        :parem id_student -> idul studentului
        :return studentul cu idul respectiv
        '''
        return self.__studenti.get(id_student)

    def __len__(self):
        return len(self.__studenti)
