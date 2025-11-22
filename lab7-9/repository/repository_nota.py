from domeniu.note import Note
from domeniu.student import Student
from domeniu.disciplina import Disciplina
from exceptii.EroareRepo import EroareRepo


class RepoNote:
    def __init__(self):
        self.__note = {}

    def adauga_nota(self, nota: Note):
        '''
        adauga o nota nou in repo
        :parem nota -> nota
        :return -
        '''
        id_nota = nota.get_id_nota()

        if id_nota in self.__note.keys():
            raise EroareRepo("Id nota exista deja!\n")

        self.__note[id_nota] = nota

    def sterge_nota(self, id_nota: Note):
        '''
        sterge o nota din repo
        :parem nota -> nota
        :return -
        '''

        if id_nota not in self.__note.keys():
            raise EroareRepo("id nu exista!\n")
            return

        del self.__note[id_nota]

    def update_nota(self, nota: Note):
        '''
        actualizeaza o nota din repo
        :parem nota -> nota
        :return -
        '''

        id_nota = nota.get_id_nota()

        if id_nota not in self.__note.keys():
            raise EroareRepo("id nu exista!\n")

        erori = ""

        self.__note[id_nota] = nota

    def get_all(self):
        '''
        returneaza lista de note
        :return lista de note
        '''
        return list(self.__note.values())

    def cauta_nota(self, id_nota: int):
        """
        cauta nota cu idul dat
        """
        nota = self.__note.get(id_nota)
        return nota

    def creare_id_nota(self):
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

    def __len__(self):
        return len(self.__note)
