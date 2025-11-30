import math
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
        id_nota = nota.get_id_nota()
        nota_cautata = self.__repo_nota.cauta_nota(id_nota)
        if nota_cautata is not None:
            erori += "id nota exista deja!\n"

        student = self.__repo_student.cautare_student(id_student)
        if student is None:
            erori += "id student nu exista!\n"

        disciplina = self.__repo_disciplina.cauta_disciplina(id_disciplina)
        if disciplina is None:
            erori += "id disciplina nu exista!\n"

        if len(erori) != 0:
            raise EroareRepo(erori)

        self.__repo_nota.adauga_nota(nota)

    def sterge_nota(self, id_nota: int):
        """
        sterge o nota in repo
        :parem id_nota -> idul notei
        """
        self.__repo_nota.sterge_nota(id_nota)

    def update_nota(self, nota: Note):
        """
        actualizeaza o nota din repo
        :parem nota-> nota
        """

        self.__repo_nota.update_nota(nota)

    def afiseaza_note(self):
        """
        afiseaza notele
        """
        return self.__repo_nota.get_all()

    def sterge_nota_dupa_student(self, id_student: int):
        """
        sterge notele dupa student
        """
        for nota in self.__repo_nota.get_all():
            id_student_nota = nota.get_id_student()
            id_nota = nota.get_id_nota()
            if id_student_nota == id_student:
                self.__repo_nota.sterge_nota(id_nota)

    def sterge_nota_dupa_disciplina(self, id_disciplina: int):
        """
        sterge notele dupa disiplina
        """
        for nota in self.__repo_nota.get_all():
            id_disciplina_nota = nota.get_id_disciplina()
            id_nota = nota.get_id_nota()
            if id_disciplina_nota == id_disciplina:
                self.__repo_nota.sterge_nota(id_nota)

    def creare_id_nota(self):
        return self.__repo_nota.creare_id_nota()

    def get_toate_note_student_dupa_materie(self, id_student: int, id_disciplina: int):
        """
        da toate notele pe care le are studentul la o materie data
        """
        lista_note = self.__repo_nota.get_all()
        notele_studentului = []
        for nota in lista_note:
            id_disciplina_nota = nota.get_id_disciplina()
            id_student_nota = nota.get_id_student()
            if (id_disciplina == id_disciplina_nota) and (id_student == id_student_nota):
                notele_studentului.append(nota.get_nota_student())

        notele_studentului.sort()
        return notele_studentului

    def media_la_student(self, id_student: int):
        """
        calculeaza media unui student
        """
        lista_disciplina = self.__repo_disciplina.get_all_disciplina()
        cnt = 0
        sum = 0
        for disciplina in lista_disciplina:
            id_disciplina = disciplina.get_id_disciplina()
            lista_nota_din_disciplina = self.get_toate_note_student_dupa_materie(
                id_student, id_disciplina)
            if lista_nota_din_disciplina != []:
                sum += self.media(lista_nota_din_disciplina)
                cnt += 1

        if cnt != 0:
            return sum/cnt
        else:
            return

    def media(self, note: list):
        """
        calculeaza media unei liste
        """
        cnt = 0
        sum = 0
        for nota in note:
            sum += nota
            cnt += 1

        return sum/cnt

    def statistica_note_la_disciplina(self, id_disciplina: Disciplina):
        """
        iau lista de studenti si note si filtrezi notele dupa disciplina
        """
        lista_studenti = self.__repo_student.get_all_studenti()
        rezultat = []

        for student in lista_studenti:
            id_student = student.get_id_student()
            dto = {
                "student": student,
                "nota": self.get_toate_note_student_dupa_materie(id_student, id_disciplina)
            }
            rezultat.append(dto)

        return rezultat

    def lista_studenti_sortata_dupa_disciplina(self, id_disciplina: Disciplina):
        """
        lista de studenti ordonati dupa nume si notele pe care le au la disciplinile date
        """
        lista_studenti = self.statistica_note_la_disciplina(id_disciplina)
        lista_studenti.sort(key=lambda x: (
            x["student"].get_nume(), [n for n in x["nota"]]))

        return lista_studenti

    def lista_de_medie_studenti(self, lista_studenti: list):
        """
        face media la toti studenti
        """
        rezultat = []
        for student in lista_studenti:
            id_student = student.get_id_student()
            media_student = self.media_la_student(id_student)
            if media_student is not None:
                dto = {
                    "media": media_student,
                    "student": student
                }
                rezultat.append(dto)

        return rezultat

    def top_studenti(self):
        """
        top 20% studenti dupa medie
        """
        lista_studenti = self.__repo_student.get_all_studenti()
        lista_studenti_dupa_medie = list(self.lista_de_medie_studenti(
            lista_studenti))

        rezultat = []
        for i in range(len(lista_studenti_dupa_medie)):
            student = lista_studenti_dupa_medie[i]["student"]
            medie = lista_studenti_dupa_medie[i]["media"]
            rezultat.append([student.get_nume(), medie])

        rezultat.sort(key=lambda x: (x[1]), reverse=True)

        rezultat = rezultat[:math.ceil(len(lista_studenti_dupa_medie)/5)]

        return rezultat

    def nr_nota_la_student(self):
        """
        calculeaza nr de note la fiecare student
        """
        lista_sudenti = self.__repo_student.get_all_studenti()
        lista_note = self.__repo_nota.get_all()
        numaru_de_note = []
        for student in lista_sudenti:
            id_student = student.get_id_student()
            nr_de_note = 0
            for nota in lista_note:
                if nota.get_id_student() == id_student:
                    nr_de_note += 1
            dto = {
                "id_student": id_student,
                "nr_de_note": nr_de_note,
            }
            numaru_de_note.append(dto)

        return numaru_de_note

    def top_nr_nota_la_student(self, numaru_de_studenti: int):
        """
        lista cu primii studenti
        """
        lista_nr_note_studenti = self.nr_nota_la_student()
        lista_nr_note_studenti.sort(
            key=lambda x: x["nr_de_note"], reverse=True)
        return lista_nr_note_studenti[:numaru_de_studenti]

    def nr_nota_la_disciplina(self):
        """
        calculeaza nr de note la fiecare student
        """
        lista_disciplina = self.__repo_disciplina.get_all_disciplina()
        lista_note = self.__repo_nota.get_all()
        numaru_de_note = []
        for disciplina in lista_disciplina:
            id_disciplina = disciplina.get_id_disciplina()
            nr_de_note = 0
            for nota in lista_note:
                if nota.get_id_disciplina() == id_disciplina:
                    nr_de_note += 1

            dto = {
                "id_disciplina": id_disciplina,
                "nr_de_note": nr_de_note
            }
            numaru_de_note.append(dto)

        return numaru_de_note

    def top_nr_nota_la_disciplina(self, numaru_de_discipline: int):
        """
        lista cu primii studenti
        """
        lista_nr_note_disciplina = self.nr_nota_la_disciplina()
        lista_nr_note_disciplina.sort(
            key=lambda x: x["nr_de_note"], reverse=True)
        return lista_nr_note_disciplina[: numaru_de_discipline]

    def verifica_daca_student_disciplina_au_legatura(self, id_student: int, id_disciplina: int):
        """
        verifica daca un student are legatura cu disciplina data
        """
        lista_note = self.__repo_nota.get_all()
        for nota in lista_note:
            id_student_nota = nota.get_id_student()
            id_disciplina_nota = nota.get_id_disciplina()
            if (id_student == id_student_nota) and (id_disciplina == id_disciplina_nota):
                return True

        return False

    def top_studenti_disciplina_leg(self, numaru_de_obiecte):
        """
        afiseaza studenti cu cele mai multe legaturi daca au legaturi cu disciplinele care au celel mai multe legaturi
        """
        lista_top_studenti = self.top_nr_nota_la_student(numaru_de_obiecte)
        lista_top_disciplina = self.top_nr_nota_la_disciplina(
            numaru_de_obiecte)

        rezultat = []
        for student in lista_top_studenti:
            id_student = student["id_student"]
            for disciplina in lista_top_disciplina:
                id_disciplina = disciplina["id_disciplina"]
                if self.verifica_daca_student_disciplina_au_legatura(id_student, id_disciplina) == True:
                    student_gasit = self.__repo_student.cautare_student(
                        id_student)
                    disciplina_gasita = self.__repo_disciplina.cauta_disciplina(
                        id_disciplina)
                    rezultat.append([student_gasit, disciplina_gasita])

        return rezultat
