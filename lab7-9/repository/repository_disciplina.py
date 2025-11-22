from domeniu.disciplina import Disciplina
from exceptii.EroareRepo import EroareRepo


class RepoDisciplina:
    def __init__(self):
        self.__disciplina = {}

    def adaugare_disciplina(self, disciplina: Disciplina):
        '''
        functie care adauga o disciplina noua
        :parem disciplina -> disciplina
        :return -
        '''
        id_disciplina = disciplina.get_id_disciplina()

        if id_disciplina in self.__disciplina:
            raise EroareRepo("Id disciplina exista deja!\n")

        self.__disciplina[id_disciplina] = disciplina

        return id_disciplina

    def stergere_disciplina(self, id_disciplina: int):
        '''
        functie care sterge disciplina din repo
        :parem disciplina -> disciplina
        :return -
        '''
        if id_disciplina not in self.__disciplina:
            raise EroareRepo("Id disciplina nu exista!\n")

        del self.__disciplina[id_disciplina]

    def update_disciplina(self, disciplina: Disciplina):
        '''
        actualizeaza o disciplina deja inserata
        :parem disciplina -> disciplina
        :return -
        '''

        id_disciplina = disciplina.get_id_disciplina()

        if id_disciplina not in self.__disciplina:
            raise EroareRepo("Id disciplina nu exista!\n")

        self.__disciplina[id_disciplina] = disciplina

    def cauta_disciplina(self, id_disciplina: int):
        '''
        cauta disciplina cu idul dat
        :parem id_disciplina -> idul disciplinei
        :return disciplina sau None daca nu exista
        '''
        return self.__disciplina.get(id_disciplina)

    def get_all_disciplina(self):
        return list(self.__disciplina.values())

    def creare_id_disciplina(self):
        id_existente = list(self.__disciplina.keys())
        if len(id_existente) == 0:
            return 1
        id_existente.sort()
        id_expected = 1
        for id in id_existente:
            if id_expected != id:
                return id_expected

            id_expected += 1

        return id_expected
