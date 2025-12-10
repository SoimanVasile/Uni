import random
import string
import os

from exceptii.EroareValidare import EroareValidare
from exceptii.EroareRepo import EroareRepo
from exceptii.EroareValidare import EroareValidare

from validare.validare_nota import ValidareNota

from servicii.service_note import ServiceNote
from servicii.service_disciplina import ServiceDisciplina
from servicii.service_student import ServiceStudenti

from repository.repository_nota import RepoNote
from repository.repository_disciplina import RepoDisciplina
from repository.repositoryStudent import RepoStudent

from domeniu.note import Note
from domeniu.disciplina import Disciplina
from domeniu.student import Student

import unittest
# import sys
# import os
# project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
# sys.path.insert(0, project_root)


class TestStudentRepo(unittest.TestCase):
    """
    Clasa de testare pentru RepoStudent
    """

    def setUp(self):
        """
        Se executa inainte de fiecare test.
        Initializeaza un repo de studenti gol.
        """
        self.file_name = "test_studenti.txt"

        with open(self.file_name, 'w') as f:
            f.write("")
        self.repo = RepoStudent(self.file_name)

    def test_adaugare_student_repo(self):
        """
        Testeaza functia de adaugare student in repo.
        """
        student1 = Student(1, "Ana")
        self.repo.adaugare_student_repo(student1)
        studenti = self.repo.get_all_studenti()
        self.assertEqual(len(studenti), 1,
                         "Lungimea listei de studenti ar trebui sa fie 1.")
        self.assertEqual(studenti[0], student1,
                         "Studentul adaugat nu corespunde.")

        student2 = Student(1, "Mihai")
        with self.assertRaises(EroareRepo):
            self.repo.adaugare_student_repo(student2)

    def test_creare_id_student(self):
        """
        Testeaza functia de creare ID unic pentru student.
        """
        id1 = self.repo.creare_id_student()
        self.assertEqual(id1, 1, "Primul ID creat ar trebui sa fie 1.")

        student1 = Student(id1, "Ana")
        self.repo.adaugare_student_repo(student1)

        id2 = self.repo.creare_id_student()
        self.assertEqual(id2, 2, "Al doilea ID creat ar trebui sa fie 2.")

        student2 = Student(id2, "Bogdan")
        self.repo.adaugare_student_repo(student2)

        id3 = self.repo.creare_id_student()
        self.assertEqual(id3, 3, "Al treilea ID creat ar trebui sa fie 3.")

        id_student2 = student2.get_id_student()
        self.repo.stergere_student(id_student2)
        id4 = self.repo.creare_id_student()
        self.assertEqual(
            id4, 2, "Dupa stergerea ID-ului 2, ar trebui sa fie returnat 2.")

    def test_get_all_studenti(self):
        """
        Testeaza returnarea listei de studenti.
        """
        student1 = Student(1, "Ana")
        student2 = Student(2, "Bogdan")
        self.repo.adaugare_student_repo(student1)
        self.repo.adaugare_student_repo(student2)

        studenti = self.repo.get_all_studenti()
        self.assertEqual(len(studenti), 2,
                         "Lungimea listei ar trebui sa fie 2.")
        self.assertIn(student1, studenti,
                      "Student1 ar trebui sa fie in lista.")
        self.assertIn(student2, studenti,
                      "Student2 ar trebui sa fie in lista.")

    def test_stergere_student(self):
        """
        Testeaza stergerea unui student.
        """
        student1 = Student(1, "Ana")
        self.repo.adaugare_student_repo(student1)
        self.assertEqual(len(self.repo.get_all_studenti()), 1)

        id_student1 = student1.get_id_student()
        self.repo.stergere_student(id_student1)
        self.assertEqual(len(self.repo.get_all_studenti()), 0,
                         "Lista ar trebui sa fie goala dupa stergere.")

        id_student_inexistent = 99
        with self.assertRaises(EroareRepo):
            self.repo.stergere_student(id_student_inexistent)

    def test_update_student(self):
        """
        Testeaza actualizarea unui student.
        """
        student_initial = Student(1, "Ana")
        self.repo.adaugare_student_repo(student_initial)

        student_actualizat = Student(1, "Ana Maria")
        self.repo.update_student(student_actualizat)

        studenti = self.repo.get_all_studenti()
        self.assertEqual(len(studenti), 1)
        self.assertEqual(studenti[0].get_nume(), "Ana Maria",
                         "Numele studentului ar trebui sa fie actualizat.")

        student_inexistent = Student(99, "Nimeni")
        with self.assertRaises(EroareRepo):
            self.repo.update_student(student_inexistent)

    def test_cautare_student(self):
        """
        Testeaza cautarea unui student prin repo
        """
        student_initial = Student(1, "Popa")
        self.repo.adaugare_student_repo(student_initial)
        student_gasit = self.repo.cautare_student(1)

        self.assertEqual(student_gasit, student_initial)

        student_gasit = self.repo.cautare_student(99)

        self.assertEqual(student_gasit, None)

        self.repo.stergere_student(1)
        student_gasit = self.repo.cautare_student(1)
        self.assertEqual(student_gasit, None)

    def tearDown(self):
        # Good for keeping the project folder clean
        if os.path.exists(self.file_name):
            os.remove(self.file_name)


class TestStudentService(unittest.TestCase):
    """
    Clasa de testare pentru ServiceStudenti
    """

    def setUp(self):
        """
        Initializeaza un repo si un service inainte de fiecare test.
        """
        self.file_name = "test_studenti.txt"
        with open(self.file_name, 'w') as f:
            f.write("")
        self.repo = RepoStudent(self.file_name)
        self.service = ServiceStudenti(self.repo)

    def test_adauga_student(self):
        """
        Testeaza adaugarea unui student prin service.
        """
        student1 = Student(1, "Ion")
        self.service.adauga_student(student1)

        studenti = self.service.afiseaza_studentii()
        self.assertEqual(len(studenti), 1)
        self.assertEqual(studenti[0].get_nume(), "Ion")

        student2 = Student(1, "Gheorghe")
        with self.assertRaises(EroareRepo):
            self.service.adauga_student(student2)
        studenti = self.service.afiseaza_studentii()
        self.assertEqual(len(studenti), 1,
                         "Nu ar trebui adaugat un student cu ID duplicat.")

    def test_adauga_student_rand(self):
        """
        adauga un student cu nume random
        """
        random.seed(1)
        nume1 = self.service.creare_nume_rand()
        self.assertEqual(nume1, "KZW")

        nume2 = self.service.creare_nume_rand()
        self.assertEqual(nume2, "qh")

        nume3 = self.service.creare_nume_rand()
        self.assertEqual(nume3, "WCEPyYng")

    def test_afiseaza_studentii(self):
        """
        Testeaza afisarea studentilor prin service.
        """
        student1 = Student(1, "Ion")
        student2 = Student(2, "Vasile")
        self.service.adauga_student(student1)
        self.service.adauga_student(student2)

        studenti = self.service.afiseaza_studentii()
        self.assertEqual(len(studenti), 2)
        self.assertIn(student1, studenti)
        self.assertIn(student2, studenti)

    def test_stergere_student(self):
        """
        Testeaza stergerea unui student prin service.
        """
        student1 = Student(1, "Ion")
        self.service.adauga_student(student1)
        self.assertEqual(len(self.service.afiseaza_studentii()), 1)

        id_student1 = student1.get_id_student()
        self.service.stergere_student(id_student1)
        self.assertEqual(len(self.service.afiseaza_studentii()), 0)

        id_student_inexistent = 99
        with self.assertRaises(EroareRepo):
            self.service.stergere_student(id_student_inexistent)

    def test_update_student(self):
        """
        Testeaza actualizarea unui student prin service.
        """
        student_initial = Student(1, "Ion")
        self.service.adauga_student(student_initial)

        student_actualizat = Student(1, "Ionel")
        self.service.update_student(student_actualizat)

        studenti = self.service.afiseaza_studentii()
        self.assertEqual(len(studenti), 1)
        self.assertEqual(studenti[0].get_nume(), "Ionel")

        student_inexistent = Student(99, "Nimeni")
        with self.assertRaises(EroareRepo):
            self.service.update_student(student_inexistent)

    def test_creare_id_student(self):
        """
        Testeaza crearea ID-ului prin service.
        """
        id1 = self.service.creare_id_student()
        self.assertEqual(id1, 1)

        student1 = Student(id1, "Ana")
        self.service.adauga_student(student1)

        id2 = self.service.creare_id_student()
        self.assertEqual(id2, 2)

    def test_cautare_student(self):
        """
        Testeaza cautarea unui student prin service
        """
        student_initial = Student(1, "Lucianes")
        self.repo.adaugare_student_repo(student_initial)

        student_gasit = self.repo.cautare_student(1)
        self.assertEqual(student_gasit, student_initial)

        student_gasit = self.repo.cautare_student(99)
        self.assertEqual(student_gasit, None)

    def tearDown(self):
        if os.path.exists(self.file_name):
            os.remove(self.file_name)

class TestDisciplinaRepo(unittest.TestCase):

    def setUp(self):
        self.file_name = "test_discipline.txt"
        with open(self.file_name, 'w') as f:
            f.write("")
        self.repo = RepoDisciplina("test_discipline.txt")

    def test_adaugare_disciplina(self):
        disciplina1 = Disciplina(1, "FP", "Profesor1")
        self.repo.adaugare_disciplina(disciplina1)
        discipline = self.repo.get_all_disciplina()
        self.assertEqual(len(discipline), 1)
        self.assertEqual(discipline[0], disciplina1)

        disciplina2 = Disciplina(1, "ASC", "Profesor2")
        with self.assertRaises(EroareRepo):
            self.repo.adaugare_disciplina(disciplina2)

    def test_creare_id_disciplina(self):
        """
        Testeaza functia de creare ID unic pentru disciplina.
        """
        id1 = self.repo.creare_id_disciplina()
        self.assertEqual(id1, 1, "Primul ID creat ar trebui sa fie 1.")

        disciplina1 = Disciplina(id1, "FP", "Prof1")
        self.repo.adaugare_disciplina(disciplina1)

        id2 = self.repo.creare_id_disciplina()
        self.assertEqual(id2, 2, "Al doilea ID creat ar trebui sa fie 2.")

        self.repo.stergere_disciplina(id1)
        id3 = self.repo.creare_id_disciplina()
        self.assertEqual(
            id3, 1, "Dupa stergerea ID-ului 1, ar trebui sa fie returnat 1.")

    def test_get_all_disciplina(self):
        """
        Testeaza returnarea listei de discipline.
        """
        disciplina1 = Disciplina(1, "FP", "Prof1")
        disciplina2 = Disciplina(2, "ASC", "Prof2")
        self.repo.adaugare_disciplina(disciplina1)
        self.repo.adaugare_disciplina(disciplina2)

        discipline = self.repo.get_all_disciplina()
        self.assertEqual(len(discipline), 2,
                         "Lungimea listei ar trebui sa fie 2.")
        self.assertIn(disciplina1, discipline,
                      "Disciplina1 ar trebui sa fie in lista.")
        self.assertIn(disciplina2, discipline,
                      "Disciplina2 ar trebui sa fie in lista.")

    def test_stergere_disciplina(self):
        """
        Testeaza stergerea unei discipline.
        """
        disciplina1 = Disciplina(1, "FP", "Prof1")
        self.repo.adaugare_disciplina(disciplina1)
        self.assertEqual(len(self.repo.get_all_disciplina()), 1)

        id_disciplina1 = disciplina1.get_id_disciplina()
        self.repo.stergere_disciplina(id_disciplina1)
        self.assertEqual(len(self.repo.get_all_disciplina()),
                         0, "Lista ar trebui sa fie goala dupa stergere.")

        id_disciplina_inexistenta = 99
        with self.assertRaises(EroareRepo):
            self.repo.stergere_disciplina(id_disciplina_inexistenta)

    def test_update_disciplina(self):
        """
        Testeaza actualizarea unei discipline.
        """
        disciplina_initiala = Disciplina(1, "FP", "Prof1")
        self.repo.adaugare_disciplina(disciplina_initiala)

        disciplina_actualizata = Disciplina(
            1, "Fundamentele Programarii", "Profesor1 Updated")
        self.repo.update_disciplina(disciplina_actualizata)

        discipline = self.repo.get_all_disciplina()
        self.assertEqual(len(discipline), 1)
        self.assertEqual(
            discipline[0].get_nume_disciplina(), "Fundamentele Programarii")
        self.assertEqual(
            discipline[0].get_nume_profesor(), "Profesor1 Updated")
        disciplina_inexistenta = Disciplina(99, "Logica", "ProfX")
        with self.assertRaises(EroareRepo):
            self.repo.update_disciplina(disciplina_inexistenta)

    def test_cautare_disciplina(self):
        """
        Testeaza cautarea unei discipline prin repo
        """
        disciplina_initiala = Disciplina(1, "Analiza", "Berinde")
        self.repo.adaugare_disciplina(disciplina_initiala)

        disciplina_gasita = self.repo.cauta_disciplina(1)
        self.assertEqual(disciplina_gasita, disciplina_initiala)

        disciplina_gasita = self.repo.cauta_disciplina(99)
        self.assertEqual(disciplina_gasita, None)

    def tearDown(self):
        if os.path.exists(self.file_name):
            os.remove(self.file_name)


class TestDisciplinaService(unittest.TestCase):

    def setUp(self):
        self.file_name = "test_discipline.txt"
        with open(self.file_name, 'w') as f:
            f.write("")
        self.repo = RepoDisciplina(self.file_name)
        self.service = ServiceDisciplina(self.repo)

    def test_adauga_disciplina(self):
        disciplina1 = Disciplina(1, "FP", "Profesor1")
        self.service.adauga_disciplina(disciplina1)

        self.assertEqual(len(self.repo.get_all_disciplina()), 1)

        disciplina2 = Disciplina(1, "ASC", "Profesor2")
        # Service-ul prinde exceptia
        with self.assertRaises(EroareRepo):
            self.service.adauga_disciplina(disciplina2)
        self.assertEqual(len(self.repo.get_all_disciplina()),
                         1, "Nu ar trebui adaugata disciplina duplicat.")

    def test_creeare_id_disciplina(self):
        """
        Testeaza crearea ID-ului prin service.
        """
        id1 = self.service.creeare_id_disciplina()
        self.assertEqual(id1, 1)

        disciplina1 = Disciplina(id1, "FP", "Prof1")
        self.service.adauga_disciplina(disciplina1)

        id2 = self.service.creeare_id_disciplina()
        self.assertEqual(id2, 2)

    def test_afiseaza_discipline(self):
        """
        Testeaza "afisarea" disciplinelor prin service.
        """
        disciplina1 = Disciplina(1, "FP", "Prof1")
        disciplina2 = Disciplina(2, "ASC", "Prof2")
        self.service.adauga_disciplina(disciplina1)
        self.service.adauga_disciplina(disciplina2)
        discipline_repo = self.repo.get_all_disciplina()
        self.assertEqual(len(discipline_repo), 2)
        self.assertIn(disciplina1, discipline_repo)
        self.assertIn(disciplina2, discipline_repo)

    def test_sterge_disciplina(self):
        """
        Testeaza stergerea unei discipline prin service.
        """
        disciplina1 = Disciplina(1, "FP", "Prof1")
        self.service.adauga_disciplina(disciplina1)
        self.assertEqual(len(self.repo.get_all_disciplina()), 1)

        id_disciplina1 = disciplina1.get_id_disciplina()
        self.service.sterge_disciplina(id_disciplina1)
        self.assertEqual(len(self.repo.get_all_disciplina()), 0)

        disciplina_inexistenta = Disciplina(99, "Logica", "ProfX")
        with self.assertRaises(EroareRepo):
            self.service.sterge_disciplina(99)
        self.assertEqual(len(self.repo.get_all_disciplina()),
                         0, "Lista ar trebui sa ramana goala.")

    def test_update_disciplina(self):
        """
        Testeaza actualizarea unei discipline prin service.
        """
        disciplina_initiala = Disciplina(1, "FP", "Prof1")
        self.service.adauga_disciplina(disciplina_initiala)

        disciplina_actualizata = Disciplina(
            1, "Fundamentele Programarii", "Profesor1 Updated")
        self.service.update_disciplina(disciplina_actualizata)

        discipline_repo = self.repo.get_all_disciplina()
        self.assertEqual(len(discipline_repo), 1)
        self.assertEqual(
            discipline_repo[0].get_nume_disciplina(), "Fundamentele Programarii")

        disciplina_inexistenta = Disciplina(99, "Logica", "ProfX")
        with self.assertRaises(EroareRepo):
            self.service.update_disciplina(disciplina_inexistenta)

    def test_cautare_disciplina(self):
        """
        Testeaza cautarea unei discipline prin service
        """
        disciplina_initiala = Disciplina(1, "FP", "Istvan")
        self.repo.adaugare_disciplina(disciplina_initiala)

        disciplina_gasita = self.repo.cauta_disciplina(1)
        self.assertEqual(disciplina_gasita, disciplina_initiala)

        disciplina_gasita = self.repo.cauta_disciplina(99)
        self.assertEqual(disciplina_gasita, None)

    def tearDown(self):

        if os.path.exists(self.file_name):
            os.remove(self.file_name)

class TestNoteRepo (unittest.TestCase):

    def setUp(self):
        self.file_name = "test_note.txt"
        with open(self.file_name, 'w') as f:
            f.write("")
        self.repo_note = RepoNote(self.file_name)

    def test_adauga_nota(self):
        """
        Testeaza adaugarea unei note prin repo
        """
        nota = Note(1, 1, 1, 10)
        self.repo_note.adauga_nota(nota)

        self.assertEqual(len(self.repo_note), 1)

        nota = Note(2, 1, 1, 9.5)
        self.repo_note.adauga_nota(nota)

        self.assertEqual(len(self.repo_note), 2)

        nota = Note(3, 1, 2, 8.75)
        self.repo_note.adauga_nota(nota)

        self.assertEqual(len(self.repo_note), 3)

        nota_gresita = Note(1, 10, 10, 9.54)
        with self.assertRaises(EroareRepo):
            self.repo_note.adauga_nota(nota_gresita)

    def test_stergere_nota(self):
        """
        Testeaza stergerea unei note prin repo
        """
        nota = Note(1, 1, 1, 10)
        self.repo_note.adauga_nota(nota)

        nota2 = Note(2, 1, 1, 9.5)
        self.repo_note.adauga_nota(nota2)

        self.repo_note.sterge_nota(1)
        self.assertEqual(len(self.repo_note), 1)

        nota_inexistenta = (99, 99, 5.4)
        with self.assertRaises(EroareRepo):
            self.repo_note.sterge_nota(nota_inexistenta)

    def test_update_nota(self):
        """
        Testeaza actualizarea unei  note prin repo
        """
        nota = Note(1, 1, 1, 9.45)
        self.repo_note.adauga_nota(nota)

        nota_actualizata = Note(1, 2, 1, 9.45)
        self.repo_note.update_nota(nota_actualizata)

        nota_gresita = Note(10, 10, 10, 10)
        with self.assertRaises(EroareRepo):
            self.repo_note.update_nota(nota_gresita)

    def tearDown(self):

        if os.path.exists(self.file_name):
            os.remove(self.file_name)


class TestNoteService (unittest.TestCase):

    def setUp(self):
        self.file_student = "test_studenti.txt"
        self.file_discipline = "test_discipline.txt"
        self.file_note = "test_note.txt"
        with open(self.file_student, 'w') as f: f.write("")
        with open(self.file_discipline, 'w') as f: f.write("")
        with open(self.file_note, 'w') as f: f.write("")

        self.repo_note = RepoNote("test_note.txt")
        self.repo_disciplina = RepoDisciplina("test_discipline.txt")
        self.repo_student = RepoStudent("test_studenti.txt")
        self.validare_nota = ValidareNota()
        self.service_note = ServiceNote(
            self.repo_disciplina, self.repo_student, self.repo_note, self.validare_nota)

    def test_adaugare_note(self):
        """
        Testeaza adaugarea unei note prin service
        """
        student = Student(1, "Mircea")
        self.repo_student.adaugare_student_repo(student)

        disciplina = Disciplina(10, "Algebra", "%2")
        self.repo_disciplina.adaugare_disciplina(disciplina)

        nota = Note(1, 1, 10, 5.45)
        self.service_note.adauga_note(nota)

        self.assertEqual(len(self.repo_note), 1)

    def test_validare_nota(self):
        """
        Testeaza validator nota prin service
        """
        nota = Note(1, 1, 1, 10)
        self.validare_nota.validare_nota(nota)

        nota_gresita = Note(1, 1, 1, -10)
        with self.assertRaises(EroareValidare):
            self.validare_nota.validare_nota(nota_gresita)

        nota_gresita = Note(1, "10", 10, 20)
        with self.assertRaises(EroareValidare):
            self.validare_nota.validare_nota(nota_gresita)

    def test_sterge_nota(self):
        """
        Testeaza stergerea unei note prin service
        """
        nota = Note(1, 1, 1, 10)
        self.repo_note.adauga_nota(nota)
        nota2 = Note(2, 2, 3, 9.4)
        self.repo_note.adauga_nota(nota2)

        self.service_note.sterge_nota(1)

        self.assertEqual(len(self.repo_note), 1)

    def test_update_nota(self):
        """
        Testeaza actualizarea unei note prin service
        """
        nota = Note(1, 1, 1, 5.64)
        self.repo_note.adauga_nota(nota)

        nota_actualizata = Note(1, 1, 1, 6.23)
        self.service_note.update_nota(nota_actualizata)

        self.assertEqual(len(self.repo_note), 1)

        note = self.repo_note.get_all()
        self.assertLess(abs(note[0].get_nota_student()-6.23), 0.000001)

    def tearDown(self):

        if os.path.exists(self.file_student):
            os.remove(self.file_student)

        if os.path.exists(self.file_discipline):
            os.remove(self.file_discipline)

        if os.path.exists(self.file_note):
            os.remove(self.file_note)


class TestStatisticiNoi(unittest.TestCase):
    def setUp(self):
        self.file_student = "test_studenti.txt"
        self.file_discipline = "test_discipline.txt"
        self.file_note = "test_note.txt"
        with open(self.file_student, 'w') as f: f.write("")
        with open(self.file_discipline, 'w') as f: f.write("")
        with open(self.file_note, 'w') as f: f.write("")
        self.repo_student = RepoStudent(self.file_student)
        self.repo_disciplina = RepoDisciplina(self.file_discipline)
        self.repo_nota = RepoNote(self.file_note)
        self.validare_nota = ValidareNota()

        self.service = ServiceNote(
            self.repo_disciplina,
            self.repo_student,
            self.repo_nota,
            self.validare_nota
        )
        # 10 studenti
        nume_studenti = [
            "Popescu Ion",      # ID 1
            "Albu Ana",         # ID 2
            "Popescu Ion",      # ID 3 (Același nume ca ID 1)
            "Barbu Matei",      # ID 4
            "Costea George",    # ID 5
            "Zaharia Maria",    # ID 6
            "Albu Ana",         # ID 7 (Același nume ca ID 2)
            "Dinu Cornel",      # ID 8
            "Enache Elena",     # ID 9
            "Faur Dan"          # ID 10
        ]

        for i in range(len(nume_studenti)):
            s = Student(i + 1, nume_studenti[i])
            self.repo_student.adaugare_student_repo(s)

        # 1 Disciplină
        disciplina = Disciplina(100, "Informatica", "Prof. X")
        self.repo_disciplina.adaugare_disciplina(disciplina)

    def test_lista_studenti_sortata_dupa_disciplina(self):
        """
        Testează sortarea pentru 10 studenți.
        Criteriu sortare: 1. Nume (Alfabetic), 2. Notă (Crescător)
        """

        # Asignăm note studenților la disciplina 100
        # Format: (id_student, nota)
        note_asignate = [
            (1, 8.50),  # Popescu Ion (8.50)
            (2, 9.00),  # Albu Ana (9.00)
            # Popescu Ion (7.00) -> Trebuie să apară ÎNAINTEA lui ID 1 (7.00 < 8.50)
            (3, 7.00),
            (4, 10.00),  # Barbu Matei
            (5, 5.00),  # Costea George
            (6, 9.50),  # Zaharia Maria
            # Albu Ana (6.00) -> Trebuie să apară ÎNAINTEA lui ID 2 (6.00 < 9.00)
            (7, 6.00),
            (8, 4.50),  # Dinu Cornel
            (9, 8.00),  # Enache Elena
            (10, 7.50)  # Faur Dan
        ]

        # Adăugăm notele în repo
        id_nota_start = 1000
        for id_student, valoare_nota in note_asignate:
            nota = Note(id_nota_start, id_student, 100, valoare_nota)
            self.repo_nota.adauga_nota(nota)
            id_nota_start += 1

        # Apelăm funcția de sortare
        rezultat = self.service.lista_studenti_sortata_dupa_disciplina(100)

        # Verificăm că avem 10 rezultate
        self.assertEqual(len(rezultat), 10)

        # Construim ordinea așteptată manual pentru verificare
        # Ordine: Nume ASC, apoi Nota ASC

        # 1. Albu Ana (ID 7, Nota 6.00)
        self.assertEqual(rezultat[0]["student"].get_nume(), "Albu Ana")
        self.assertEqual(rezultat[0]["nota"], [6.00])

        # 2. Albu Ana (ID 2, Nota 9.00)
        self.assertEqual(rezultat[1]["student"].get_nume(), "Albu Ana")
        self.assertEqual(rezultat[1]["nota"], [9.00])

        # 3. Barbu Matei (ID 4, Nota 10.00)
        self.assertEqual(rezultat[2]["student"].get_nume(), "Barbu Matei")

        # 4. Costea George (ID 5, Nota 5.00)
        self.assertEqual(rezultat[3]["student"].get_nume(), "Costea George")

        # 5. Dinu Cornel (ID 8, Nota 4.50)
        self.assertEqual(rezultat[4]["student"].get_nume(), "Dinu Cornel")

        # 6. Enache Elena (ID 9, Nota 8.00)
        self.assertEqual(rezultat[5]["student"].get_nume(), "Enache Elena")

        # 7. Faur Dan (ID 10, Nota 7.50)
        self.assertEqual(rezultat[6]["student"].get_nume(), "Faur Dan")

        # 8. Popescu Ion (ID 3, Nota 7.00) - Nota mai mică primul
        self.assertEqual(rezultat[7]["student"].get_nume(), "Popescu Ion")
        self.assertEqual(rezultat[7]["nota"], [7.00])

        # 9. Popescu Ion (ID 1, Nota 8.50)
        self.assertEqual(rezultat[8]["student"].get_nume(), "Popescu Ion")
        self.assertEqual(rezultat[8]["nota"], [8.50])

        # 10. Zaharia Maria (ID 6, Nota 9.50)
        self.assertEqual(rezultat[9]["student"].get_nume(), "Zaharia Maria")

    def test_top_studenti(self):
        """
        testeaza functia top_studenti din service
        """
        note_asignate = [
            (1, 8.5),
            (1, 9.0),
            (2, 5.6),
            (2, 10.0),
            (2, 10.0),
            (3, 8.34),
            (4, 9.12),
            (4, 9.87),
            (5, 9.80),
            (5, 9.05),
            (6, 10.0),
        ]

        id_nota_start = 1000
        for id_student, valoare_nota in note_asignate:
            nota = Note(id_nota_start, id_student, 100, valoare_nota)
            self.repo_nota.adauga_nota(nota)
            id_nota_start += 1

        rezultat = self.service.top_studenti()

        self.assertEqual(len(rezultat), 2)

        self.assertEqual(rezultat[1][0], "Barbu Matei")
        self.assertEqual(rezultat[0][0], "Zaharia Maria")

    def test_top_nr_nota_la_student(self):
        """
        testeaza topu studenti dupa note
        """
        nr_studenti = 3
        note_asignate = [
            (1, 5.0),
            (1, 5.0),
            (2, 4.0),
            (2, 4.0),
            (2, 4.0),
            (6, 6.0),
            (6, 6.0),
            (6, 6.0),
            (6, 6.0),
            (7, 6.0),
        ]
        id_nota_start = 1000
        for id_student, valoarea_nota in note_asignate:
            nota = Note(id_nota_start, id_student, 100, valoarea_nota)
            self.repo_nota.adauga_nota(nota)
            id_nota_start += 1

        lista_studenti = self.service.top_nr_nota_la_student(nr_studenti)

        student_prev = lista_studenti[0]["nr_de_note"]
        for student in lista_studenti:
            if (student["nr_de_note"] > student_prev):
                assert False
            student_prev = student["nr_de_note"]

    def test_top_nr_nota_la_disciplina(self):
        """
        testeaza topu discipline dupa nota
        """
        nr_discipline = 3
        discipline = [
            Disciplina(101, "FP", "Istvan"),
            Disciplina(102, "ASC", "Sotropa"),
            Disciplina(103, "Algebra", "%2"),
        ]
        for disciplina in discipline:
            self.repo_disciplina.adaugare_disciplina(disciplina)

        note_asignate = [
            (1, 100, 5.0),
            (1, 100, 5.0),
            (1, 100, 5.0),
            (4, 101, 6.0),
            (5, 102, 7.0),
            (6, 103, 8.0),
            (4, 101, 6.0),
        ]
        id_nota_start = 1000
        for id_student, id_disciplina, valoare_nota in note_asignate:
            nota = Note(id_nota_start, id_student, id_disciplina, valoare_nota)
            self.repo_nota.adauga_nota(nota)
            id_nota_start += 1

        numaru_de_disciplina = 7
        lista_nr_note_disciplina = self.service.top_nr_nota_la_disciplina(
            numaru_de_disciplina)

        disciplina_prev = lista_nr_note_disciplina[0]["nr_de_note"]
        for disciplina in lista_nr_note_disciplina:
            if disciplina["nr_de_note"] > disciplina_prev:
                assert False

            disciciplina_prev = disciplina["nr_de_note"]

    def test_top_studenti_disciplina_leg(self):
        """
        testeaza daca returneaza lista de studenti si discipline care au leg
        """
        disciplina1 = Disciplina(101, "FP", "Istvan")
        self.repo_disciplina.adaugare_disciplina(disciplina1)

        note_asignate = [
            (1, 100, 6.0),
            (2, 101, 6.0),
            (3, 101, 6.0),
            (1, 101, 6.0),
            (1, 100, 6.0),
            (1, 101, 6.0),
            (2, 101, 6.0),
        ]
        id_nota_start = 1000
        for id_student, id_disciplina, valoare_nota in note_asignate:
            nota = Note(id_nota_start, id_student, id_disciplina, valoare_nota)
            self.repo_nota.adauga_nota(nota)
            id_nota_start += 1
        nr_obiecte = 3
        lista_student_disciplina_leg = self.service.top_studenti_disciplina_leg(
            3)

        


    def tearDown(self):

        if os.path.exists(self.file_student):
            os.remove(self.file_student)

        if os.path.exists(self.file_discipline):
            os.remove(self.file_discipline)

        if os.path.exists(self.file_note):
            os.remove(self.file_note)


if __name__ == '__main__':
    unittest.main()
