from domeniu.disciplina import Disciplina
from domeniu.note import Note
from domeniu.student import Student

from repository.repositoryStudent import RepoStudent
from repository.repository_disciplina import RepoDisciplina
from repository.repository_nota import RepoNote

from exceptii.EroareRepo import EroareRepo

from validare.validare_nota import ValidareNota


class ServiceNote:
    def __init__(self, repo_disciplina: RepoDisciplina, repo_student: RepoStudent, repo_nota: RepoNote, validare_nota: ValidareNota):
        self.__repo_disciplina = repo_disciplina
        self.__repo_student = repo_student
        self.__repo_nota = repo_nota
        self.__validare_nota = validare_nota

    def adauga_note(self, nota: Note):
        '''
        adauga o nota in repo
        '''
        self.__validare_nota.validare_nota(nota)

        id_student = nota.get_id_student()
        id_disciplina = nota.get_id_disciplina()

        erori = ""
        student = self.__repo_student.cautare_student(id_student)
        if student is None:
            erori += "id student nu exista!\n"

        disciplina = self.__repo_disciplina.cauta_disciplina(id_disciplina)
        if disciplina is None:
            erori += "id student nu exista!\n"

        if len(erori) != 0:
            raise EroareRepo(erori)

        self.__repo_nota.adauga_nota(nota)

    def sterge_nota(self, id_nota: int):
        """
        sterge o nota in repo
        :parem id_nota -> idul notei
        """
        self.__repo_nota.sterge_nota(id_nota)

    def update_nota(self, nota: int):
        """
        actualizeaza o nota din repo
        :parem nota-> nota
        """
        self.__repo_nota.update_nota(nota)

    def creare_id_nota(self):
        return self.__repo_nota.creare_id_nota()
