from repository.repository_disciplina import RepoDisciplina
from domeniu.disciplina import Disciplina


class ServiceDisciplina:

    def __init__(self, repo_disciplina: RepoDisciplina):
        self.__repo_disciplina = repo_disciplina

    def adauga_disciplina(self, disciplina: Disciplina):
        '''
        adauga o noua disciplina in repo_disciplina
        :parem disciplina -> disciplina
        :return -
        '''
        return self.__repo_disciplina.adaugare_disciplina(disciplina)

    def sterge_disciplina(self, id_disciplina: int):
        '''
        sterge o disciplina din repo
        :parem disciplina -> disciplina
        :return -
        '''
        self.__repo_disciplina.stergere_disciplina(id_disciplina)

    def update_disciplina(self, disciplina: Disciplina):
        '''
        actualizeaza o disciplina din repo
        :param disciplina -> Disciplina
        :return -
        '''
        self.__repo_disciplina.update_disciplina(disciplina)

    def afiseaza_discipline(self):
        '''
        afiseaza toate disciplinele
        :return -
        '''
        return self.__repo_disciplina.get_all_disciplina()

    def creeare_id_disciplina(self):
        '''
        returneaza cel mai mic id nefolosit
        :return cel mai mic id nefolosit
        '''
        return self.__repo_disciplina.creare_id_disciplina()

    def cautare_disciplina(self, id_disciplina):
        '''
        cauta disciplina cu idul dat
        :parem id_student -> idul studentului
        :return disciplina sau None daca nu exista
        '''
        return self.__repo_disciplina.cauta_disciplina(id_disciplina)
