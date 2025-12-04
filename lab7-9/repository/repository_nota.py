from domeniu.note import Note
from domeniu.student import Student
from domeniu.disciplina import Disciplina
from exceptii.EroareRepo import EroareRepo


class RepoNote:
    def __init__(self, calea_note: str):
        self.__note = {}
        self.__calea_note = calea_note

    def adauga_nota(self, nota: Note):
        '''
        adauga o nota nou in repo
        :parem nota -> nota
        :return -
        '''
        self.__read_nota_din_fisier()
        id_nota = nota.get_id_nota()

        if id_nota in self.__note.keys():
            raise EroareRepo("Id nota exista deja!\n")

        self.__note[id_nota] = nota
        self.__salveaza_nota_in_fisier()

    def sterge_nota(self, id_nota: Note):
        '''
        sterge o nota din repo
        :parem nota -> nota
        :return -
        '''
        self.__read_nota_din_fisier()
        if id_nota not in self.__note.keys():
            raise EroareRepo("id nu exista!\n")
            return

        del self.__note[id_nota]
        self.__salveaza_nota_in_fisier()

    def update_nota(self, nota: Note):
        '''
        actualizeaza o nota din repo
        :parem nota -> nota
        :return -
        '''
        self.__read_nota_din_fisier()
        id_nota = nota.get_id_nota()

        if id_nota not in self.__note.keys():
            raise EroareRepo("id nu exista!\n")

        self.__note[id_nota] = nota
        self.__salveaza_nota_in_fisier()

    def get_all(self):
        '''
        returneaza lista de note
        :return lista de note
        '''
        self.__read_nota_din_fisier()
        return list(self.__note.values())

    def cauta_nota(self, id_nota: int):
        """
        cauta nota cu idul dat
        """
        self.__read_nota_din_fisier()
        nota = self.__note.get(id_nota)
        return nota

    def creare_id_nota(self):
        self.__read_nota_din_fisier()
        id_existente = list(self.__note.keys())
        if len(id_existente) == 0:
            return 1
        id_existente.sort()
        id_expected = 1
        for id in id_existente:
            if id_expected != id:
                return id_expected

            id_expected += 1

        return id_expected
        self.__salveaza_nota_in_fisier()

    def __len__(self):
        return len(self.__note)

    def __read_nota_din_fisier(self):
        """
        citeste din fisier disciplinele
        """
        with open(self.__calea_note, "r") as f:
            self.__note = {}
            linii = f.readlines()
            for linie in linii:
                linie = linie.strip()
                if linie == '':
                    continue
                parti = linie.split(',')
                id_nota = int(parti[0])
                id_student = int(parti[1])
                id_disciplina = int(parti[2])
                nota_student = float(parti[3])
                nota = Note(id_nota, id_student, id_disciplina, nota_student)
                self.__note[id_nota] = nota

    def __salveaza_nota_in_fisier(self):
        """
        salveaza disciplinele in fisier
        """
        with open(self.__calea_note, "w") as f:
            for nota in self.__note.values():
                id_nota = nota.get_id_nota()
                id_disciplina = nota.get_id_disciplina()
                id_student = nota.get_id_student()
                nota_student = nota.get_nota_student()
                f.write(f"{id_nota},{id_student},{
                        id_disciplina},{nota_student}\n")
