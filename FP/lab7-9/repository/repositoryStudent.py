from domeniu.student import Student
from exceptii.EroareRepo import EroareRepo


class RepoStudent:

    def __init__(self, calea_studenti: str):
        self.__studenti = {}
        self.__calea_studenti = calea_studenti

    def get_all_dict(self):
        return self.__studenti

    def restore_state(self, dict):
        self.__studenti = dict

        self.__salveaza_in_fisier()

    def creare_id_student(self):
        self.__read_studentii_din_fisier()
        id_existente = list(self.__studenti.keys())
        if len(id_existente) == 0:
            return 1
        id_existente.sort()
        id_expected = 1
        for id in id_existente:
            if id_expected != id:
                return id_expected

            id_expected += 1

        self.__salveaza_in_fisier()

        return id_expected

    def adaugare_student_repo(self, student: Student):
        '''
        functie care adauga un student nou in repository
        :parem student -> student
        :return -
            Raise valueError daca numele studentului nu i bun
        '''
        self.__read_studentii_din_fisier()
        id_student = student.get_id_student()

        if id_student in self.__studenti:
            raise EroareRepo("Id student exista deja!\n")

        self.__studenti[id_student] = student

        self.__salveaza_in_fisier()

        return id_student

    def stergere_student(self, id_student: int):
        '''
        functie care sterge un student din repo
        :parem student -> student
        :return -
        '''
        self.__read_studentii_din_fisier()
        if id_student not in self.__studenti:
            raise EroareRepo("Id student nu exista!\n")

        del self.__studenti[id_student]
        self.__salveaza_in_fisier()

    def update_student(self, student: Student):
        '''
        functie care actualizeaza un student
        :parem student -> student
        :return -
        '''
        self.__read_studentii_din_fisier()
        id_student = student.get_id_student()

        if id_student not in self.__studenti:
            raise EroareRepo("Id student nu exista!\n")

        self.__studenti[id_student] = student
        self.__salveaza_in_fisier()

    def get_all_studenti(self):
        '''
        returneaza lista de studenti
        :return lista de studenti
        '''
        self.__read_studentii_din_fisier()
        return list(self.__studenti.values())

    def cautare_student(self, id_student: int):
        '''
        returneaza studentul cu idul respectiv
        :parem id_student -> idul studentului
        :return studentul cu idul respectiv
        '''
        self.__read_studentii_din_fisier()
        return self.__studenti.get(id_student)

    def __read_studentii_din_fisier(self):
        """
        pune studentii in repo
        """
        with open(self.__calea_studenti, "r") as f:
            self.__studenti = {}
            linii = f.readlines()
            for linie in linii:
                linie = linie.strip()
                if linie == '':
                    continue
                parti = linie.split(',')
                id_student = int(parti[0])
                nume = parti[1].strip()
                student = Student(id_student, nume)
                self.__studenti[id_student] = student

    def __salveaza_in_fisier(self):
        with open(self.__calea_studenti, "w") as f:
            for student in self.__studenti.values():
                id_student = student.get_id_student()
                nume = student.get_nume()
                f.write(f"{id_student},{nume}\n")

    def __len__(self):
        return len(self.__studenti)
