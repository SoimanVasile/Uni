from domeniu.student import Student
from domeniu.disciplina import Disciplina
from domeniu.note import Note

from servicii.service_student import ServiceStudenti
from servicii.service_note import ServiceNote
from servicii.service_disciplina import ServiceDisciplina

from exceptii.EroareUI import EroareUI
from exceptii.EroareRepo import EroareRepo
from exceptii.EroareValidare import EroareValidare


class Consola:

    def __init__(self, service_studenti: ServiceStudenti, service_note: ServiceNote, service_disciplina: ServiceDisciplina):
        self.__service_studenti = service_studenti
        self.__service_note = service_note
        self.__service_disciplina = service_disciplina
        self.__comenzi = {
            "adauga_student": [self.ui_adauga_student, 1, [str]],
            "afiseaza_studenti": [self.ui_afiseaza_student, 0, []],
            "sterge_student": [self.ui_sterge_student, 1, [int]],
            "update_student": [self.ui_update_student, 2, [int, str]],
            "adauga_disciplina": [self.ui_adauga_disciplina, 2, [str, str]],
            "sterge_disciplina": [self.ui_sterge_disciplina, 1, [int]],
            "afiseaza_discipline": [self.ui_afisare_discipline, 0, []],
            "update_disciplina": [self.ui_update_disciplina, 3, [int, str, str]],
            "cauta_student": [self.ui_cauta_student, 1, [int]],
            "cauta_disciplina": [self.ui_cauta_disciplina, 1, [int]],
            "adauga_nota": [self.ui_adauga_nota, 3, [int, int, float]],
            "sterge_nota": [self.ui_sterge_nota, 1, [int]],
            "update_nota": [self.ui_update_nota, 4, [int, int, int, float]],
            "afiseaza_note": [self.ui_afiseaza_nota, 0, []],
            "adauga_student_rand": [self.ui_adauga_student_rand, 0, []],
            "lista_studenti": [self.ui_lista_studenti, 1, [int]],
            "top_studenti": [self.ui_top_studenti, 0, []],
            "undo": [self.ui_undo, 0, []],
        }

    def run(self):
        while True:
            text_comanda = input(">>>>")
            text_comanda = text_comanda.strip()
            if text_comanda == "":
                continue
            if text_comanda == "exit":
                print("Sayonara, User")
                break

            if text_comanda == "help":
                self.ui_help()
                continue

            rezultat = text_comanda.split()
            comanda = rezultat[0]
            parametri_comanda = rezultat[1:]

            if comanda in self.__comenzi:
                try:
                    parametri_comanda = self.verificare_parametru(
                        comanda, parametri_comanda)
                    self.__comenzi[comanda][0](parametri_comanda)
                except EroareUI as eroare_ui:
                    print(f"eroare_ui: {eroare_ui}")

            else:
                print("Nu exista comanda")

    def ui_help(self):
        print(
            "1. adauga_student {nume} - adauga un nou student cu numele {nume}")
        print("2. afiseaza_studenti - afiseaza studentii")
        print(
            "3. sterge_student {id_student} {nume} - sterge studentul cu id_student = {id_student} si nume = {nume}")
        print(
            "4. update_student {id_student} {nume} - actualizeaza studentul cu idul {id_student} schimband numele in {nume}")
        print(
            "5. adauga_disciplina {nume_disciplina} {nume_profesor} - adauga o disciplina noua in repo cu un id unic")
        print("6. afiseaza_discipline - afiseaza disciplinele")
        print(
            "7. sterge_disciplina {id_disciplina} {nume_disciplina} {nume_profesor} - sterge disciplina cu id ul dat")
        print(
            "8. update_disciplina {id_disciplina} {nume_disciplina} {nume_profesor} - actualizeaza disciplina cu {id_disciplina} cu numele introduse")
        print(
            "9. cauta_student {id_student} - afiseaza studentul cu idul respectiv")
        print(
            "10. cauta_disciplina {id_disciplina} - afiseaza disciplina cu idul respectiv")
        print(
            "11. adauga_nota {id_student} {id_disciplina} {nota_student} - adauga o nota la studentul dat la materia respectiva")
        print("12. sterge_nota {id_nota} - sterge o nota din repo")
        print(
            "13. update_nota {id_nota} {id_student} {id_disciplina} {nota_student} - actualizeaza nota cu idul nota dat cu datele inserate")
        print("14. afiseaza_note - afiseaza toate notele")
        print("15. adauga_student_rand - adauga un student nou cu nume random")
        print(
            "16. lista_studenti {id_disciplina} - afiseaza lista studentilor ordonati alfabetic si dupa nota de la disciplina data")
        print("17. top studenti - afiseaza primi 20% din studenti dupa medie")

    def verificare_parametru(self, comanda, parametri_comanda):
        """
        verifica daca parametrii comenzii sunt bune ca numar si tip
        :parem comanda -> comanda
        :parem parametri_comanda -> parametrii comenzii
        :return -
        raise eroare daca numarul de parametrii sunt gresit sau tipul parametrilor sunt gresit
        """
        numarul_parametri_comanda = self.__comenzi[comanda][1]

        if len(parametri_comanda) != numarul_parametri_comanda:
            raise EroareUI("Numar gresit de parametri")

        instantele_comanda = self.__comenzi[comanda][2]

        erori = ""
        for i in range(numarul_parametri_comanda):
            instanta_buna = instantele_comanda[i]
            parametru = parametri_comanda[i]
            try:
                parametru = instanta_buna(parametru)
                parametri_comanda[i] = parametru
            except ValueError:
                erori += f"Parametrul {i+1} nu este de tipul {instanta_buna}"

        if len(erori) != 0:
            raise EroareUI(erori)

        return parametri_comanda

    def ui_adauga_student(self, parametri_comanda):
        '''
        adauga student nou in repository
        :parem parametri_comanda -> parametrii comenzii
        :return -
        '''

        nume_student = parametri_comanda[0]
        id_student = self.__service_studenti.creare_id_student()
        student = Student(id_student, nume_student)
        try:
            self.__service_studenti.adauga_student(student)
        except EroareRepo as e:
            print("EroareRepo>> ", e)
            return

        print(f"Am adaugat cu succes studentul cu id {id_student}")

    def ui_afiseaza_student(self, parametri_comanda):
        '''
        afiseaza studentii memorati
        :parem paremetri_comanda -> parametrii comenzii
        :return lista de stundeti
        '''
        print(self.__service_studenti.afiseaza_studentii())

    def ui_undo(self, parametri_comanda):
        try:
            self.__service_studenti.undo()
        except ValueError as e:
            print(e)

    def ui_sterge_student(self, parametri_comanda):
        '''
        sterge student din student repo
        :parem parametri_comanda -> parametrii comenzii
        :return -
        '''
        id_student = parametri_comanda[0]

        try:
            self.__service_studenti.stergere_student(id_student)
        except EroareRepo as e:
            print("EroareRepo>> ", e)
            return

        print("Am sters cu succes studentul")
        self.__service_note.sterge_nota_dupa_student(id_student)

    def ui_update_student(self, parametri_comanda):
        '''
        update la un student deja existent schimband numele
        :parem parametri_comanda -> parametrii comenzii
        :return -
        '''
        id_student = parametri_comanda[0]
        nume = parametri_comanda[1]
        student = Student(id_student, nume)

        try:
            self.__service_studenti.update_student(student)
        except EroareRepo as e:
            print("EroareRepo>> ", e)
            return

        print("Am actualizat cu succes studentul")

    def ui_adauga_disciplina(self, parametri_comanda):
        '''
        adauga o noua disciplina in repo_disciplina
        :parem parametri_comanda -> parametrii comenzii
        :return -
        '''
        id_disciplina = self.__service_disciplina.creeare_id_disciplina()
        nume_disciplina = parametri_comanda[0]
        nume_profesor = parametri_comanda[1]
        disciplina = Disciplina(id_disciplina, nume_disciplina, nume_profesor)

        try:
            self.__service_disciplina.adauga_disciplina(disciplina)
        except EroareRepo as e:
            print("EroareRepo>> ", e)
            return

        print(f"Am adaugat disciplina cu succes disciplina cu id {
              id_disciplina}")

    def ui_sterge_disciplina(self, parametri_comanda):
        '''
        sterge o disciplina din repo
        :parem parametri_comanda -> parametrii comenzii
        '''
        id_disciplina = parametri_comanda[0]

        try:
            self.__service_disciplina.sterge_disciplina(id_disciplina)
        except EroareRepo as e:
            print("EroareRepo>> ", e)
            return

        print("Am sters cu succes disciplina")
        self.__service_note.sterge_nota_dupa_disciplina(id_disciplina)

    def ui_afisare_discipline(self, parametri_comanda):
        '''
        afiseaza toate disciplinele
        :parem parametrii comanda -> parametrii comenzii
        :return -
        '''
        print(self.__service_disciplina.afiseaza_discipline())

    def ui_update_disciplina(self, parametri_comanda):
        '''
        da update la o disciplina
        :parem parametri_comanda -> parametrii comenzi
        '''
        id_disciplina = parametri_comanda[0]
        nume_disciplina = parametri_comanda[1]
        nume_profesor = parametri_comanda[2]

        disciplina = Disciplina(id_disciplina, nume_disciplina, nume_profesor)
        try:
            self.__service_disciplina.update_disciplina(disciplina)
        except EroareRepo as e:
            print("EroareRepo>> ", e)
            return

        print("Am actualizat cu succes disciplina")

    def ui_cauta_student(self, parametri_comanda):
        '''
        cauta studentul cu idul dat
        :parem parametri_comanda -> parametrii comenzii
        :return -
            printeaza studentul sau raiseEroareRepo
        '''
        id_student = parametri_comanda[0]
        student = self.__service_studenti.cautare_student(id_student)
        if student is None:
            print("Studentul nu exista!")
        else:
            print(f"{student}")

    def ui_cauta_disciplina(self, parametri_comanda):
        '''
        cauta disciplina cu idul data
        :parem parametri_comanda -> parametrii comenzii
        :return -
            printeaza disciplina sau raiseEroareRepo
        '''
        id_disciplina = parametri_comanda[0]

        disciplina = self.__service_disciplina.cautare_disciplina(
            id_disciplina)

        if disciplina is None:
            print("Nu exista disciplina")
        else:
            print(disciplina)

    def ui_adauga_nota(self, paramaetri_comanda):
        '''
        adauga nota in repo
        '''
        id_nota = self.__service_note.creare_id_nota()
        id_student = paramaetri_comanda[0]
        id_disciplina = paramaetri_comanda[1]
        valoare = paramaetri_comanda[2]

        nota = Note(id_nota, id_student, id_disciplina, valoare)

        try:
            self.__service_note.adauga_note(nota)
        except EroareRepo as e:
            print("EroareRepo>> ", e)
            return
        except EroareValidare as e:
            print("EroareValidare>> ", e)
            return

        print(f"Am adaugat nota cu succes cu id {id_nota}")

    def ui_sterge_nota(self, parametri_comanda):
        """
        sterge nota in repo
        """
        id_nota = parametri_comanda[0]

        try:
            self.__service_note.sterge_nota(id_nota)
        except EroareRepo as e:
            print("EroareRepo >>", e)
            return

        print("Am sters cu succes nota")

    def ui_update_nota(self, parametri_comanda):
        """
        actualizeaza o nota in repo
        """
        id_nota = parametri_comanda[0]
        id_student = parametri_comanda[1]
        id_disciplina = parametri_comanda[2]
        nota_student = parametri_comanda[3]

        nota = Note(id_nota, id_student, id_disciplina, nota_student)

        try:
            self.__service_note.update_nota(nota)
        except EroareRepo as e:
            print("EroareRepo >>", e)
            return

        print("Am actualizat cu succes")

    def ui_afiseaza_nota(self, parametri_comanda):
        """
        afiseaza toate notele
        """
        print(self.__service_note.afiseaza_note())

    def ui_adauga_student_rand(self, parametri_comanda):
        """
        adauga un student nou cu nume random
        """
        id_student = self.__service_studenti.creare_id_student()
        nume = self.__service_studenti.creare_nume_rand()

        student = Student(id_student, nume)

        try:
            self.__service_studenti.adauga_student(student)
        except EroareRepo as e:
            print("EroareRepo >>", e)
            return

        print(f"Am adauga cu succes studentu cu id {
              id_student} si nume {nume}")

    def ui_lista_studenti(self, parametri_comanda):
        """
        afiseaza sortat studentii dupa nume si nota
        """
        id_disciplina = parametri_comanda[0]
        print(self.__service_note.lista_studenti_sortata_dupa_disciplina(id_disciplina))

    def ui_top_studenti(self, parametri_comanda):
        """
        afiseaza primit 20 % din studenti cu cea mai mare medie
        """
        rezultat = self.__service_note.top_studenti()
        for student in rezultat:
            print(f"{student[0]} are media {student[1]}")
