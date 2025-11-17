from domeniu.student import Student
from domeniu.disciplina import Disciplina
from domeniu.note import Note

from repository.repositoryStudent import RepoStudent
from repository.repository_disciplina import RepoDisciplina
from repository.repository_nota import RepoNote

from validare.validare_nota import ValidareNota

from servicii.service_student import ServiceStudenti
from servicii.service_disciplina import ServiceDisciplina
from servicii.service_note import ServiceNote

from consola.consola import Consola

repo_student = RepoStudent()
repo_disciplina = RepoDisciplina()
repo_nota = RepoNote()

validare_nota = ValidareNota()

service_studenti = ServiceStudenti(repo_student)
service_discipline = ServiceDisciplina(repo_disciplina)
service_note = ServiceNote(
    repo_disciplina, repo_student, repo_nota, validare_nota)

UI = Consola(service_studenti, service_note, service_discipline)

UI.run()
