# Documentație Proiect: Gestiune Academică

---

## 1. Obiectivul Aplicației

Crearea unei aplicații de tip consolă (sau cu interfață simplă) pentru gestionarea academică a studenților, disciplinelor și notelor la o facultate. Aplicația va permite operații administrative (CRUD), funcții de căutare și generarea de rapoarte statistice.

---

## 2. Modele de Date (Entități)

Aplicația va utiliza trei modele principale de date.

### 2.1. Student
Stochează informații despre un singur student.
* **`IDStudent`** (Tip: `string` sau `int`, Cheie Unică)
    * *Descriere:* Un identificator unic pentru fiecare student (ex: "S101" sau 101).
* **`Nume`** (Tip: `string`)
    * *Descriere:* Numele complet al studentului (ex: "Popescu Ion").

### 2.2. Disciplina
Stochează informații despre o singură materie.
* **`idDisciplină`** (Tip: `string` sau `int`, Cheie Unică)
    * *Descriere:* Un identificator unic pentru fiecare disciplină (ex: "D01" sau 501).
* **`Nume`** (Tip: `string`)
    * *Descriere:* Numele complet al disciplinei (ex: "Programare Orientată Obiect").
* **`Profesor`** (Tip: `string`)
    * *Descriere:* Numele profesorului titular (ex: "Ionescu Ana").

### 2.3. Nota (Entitate de Legătură)
Aceasta este o entitate esențială care conectează un Student cu o Disciplină și îi atribuie o valoare. Rezolvă relația de tip **Many-to-Many** (un student poate avea multe note la multe discipline, iar o disciplină poate fi urmată de mulți studenți).



* **`IDStudent`** (Tip: `string` sau `int`, Cheie Externă)
    * *Descriere:* Referință la `IDStudent` din entitatea **Student**.
* **`idDisciplină`** (Tip: `string` sau `int`, Cheie Externă)
    * *Descriere:* Referință la `idDisciplină` din entitatea **Disciplina**.
* **`ValoareNota`** (Tip: `int` sau `float`)
    * *Descriere:* Nota efectivă obținută (ex: 10, 9.5, 5).

---

## 3. Cerințe Funcționale

### 3.1. Gestiune Studenți (CRUD)
* **Adăugare:** Permite adăugarea unui nou student (ID, Nume).
* **Modificare:** Permite modificarea numelui unui student pe baza ID-ului.
* **Ștergere:** Permite ștergerea unui student pe baza ID-ului.
* **Listare:** Afișează toți studenții înregistrați.

### 3.2. Gestiune Discipline (CRUD)
* **Adăugare:** Permite adăugarea unei noi discipline (ID, Nume, Profesor).
* **Modificare:** Permite modificarea numelui sau profesorului unei discipline pe baza ID-ului.
* **Ștergere:** Permite ștergerea unei discipline pe baza ID-ului.
* **Listare:** Afișează toate disciplinele înregistrate.

### 3.3. Căutare
* **Căutare Student:** Permite găsirea unui student după ID sau Nume (parțial sau exact).
* **Căutare Disciplină:** Permite găsirea unei discipline după ID, Nume sau Profesor.

### 3.4. Gestiune Note
* **Asignare Notă:** Permite adăugarea unei noi înregistrări `Nota` (legarea unui `IDStudent` de un `idDisciplină` cu o `ValoareNota`).

### 3.5. Statistici și Rapoarte
* **Raport 1 (Note la disciplină):** Afișează o listă de studenți și notele lor la o disciplină dată (selectată de utilizator).
    * Opțiune de sortare **alfabetică** (după numele studentului).
    * Opțiune de sortare **după notă** (descrescător).
* **Raport 2 (Top Performers):** Afișează primii 20% din studenți, ordonați după media notelor lor la *toate* disciplinele.

---

## 4. Planificare Iterații (3 Săptămâni)

Acesta este un plan de dezvoltare (sprint plan) pentru implementarea cerințelor.

### Săptămâna 1: Fundația și CRUD
* **Obiectiv:** Crearea structurii de bază a proiectului și implementarea operațiilor CRUD pentru entitățile de bază.
* **Task-uri:**
    1.  **Setare Proiect:** Crearea structurii de foldere (ex: Modele, Repository, Service, UI).
    2.  **Modele:** Definirea claselor `Student` și `Disciplina`.
    3.  **Repository:** Implementarea `StudentRepository` și `DisciplinaRepository` (inițial pot fi în memorie, cu liste).
    4.  **Service:** Crearea `StudentService` și `DisciplinaService` care conțin logica de validare.
    5.  **UI (Consolă):** Crearea meniurilor pentru:
        * Adăugare / Modificare / Ștergere / Listare Studenți.
        * Adăugare / Modificare / Ștergere / Listare Discipline.

### Săptămâna 2: Logica de Bază și Căutări
* **Obiectiv:** Implementarea funcționalităților de căutare și a logicii centrale de business (asignarea notelor).
* **Task-uri:**
    1.  **Model:** Definirea clasei `Nota`.
    2.  **Repository:** Implementarea `NotaRepository`.
    3.  **Service:** Crearea `NotaService` cu funcția `asignareNota(IDStudent, idDisciplina, valoare)`.
        * *Notă:* Acest service va trebui să colaboreze cu `StudentRepository` și `DisciplinaRepository` pentru a valida existența ID-urilor.
    4.  **UI (Consolă):** Adăugarea meniului pentru "Asignare Notă".
    5.  **Implementare Căutare:**
        * Adăugarea în `StudentService` a funcției `searchStudent(...)`.
        * Adăugarea în `DisciplinaService` a funcției `searchDisciplina(...)`.
    6.  **UI (Consolă):** Adăugarea meniurilor pentru "Căutare Student" și "Căutare Disciplină".

### Săptămâna 3: Statistici și Finalizare
* **Obiectiv:** Implementarea rapoartelor complexe și finalizarea aplicației.
* **Task-uri:**
    1.  **Logică Rapoarte:** Crearea unui nou `ReportService` (sau extinderea `NotaService`).
    2.  **Implementare Raport 1:** Crearea funcției `getRaportDisciplina(idDisciplina, criteriuSortare)`.
        * Aceasta va prelua date din `NotaRepository` și `StudentRepository`.
    3.  **Implementare Raport 2:** Crearea funcției `getTopStudenti()`.
        * Aceasta va fi cea mai complexă: trebuie să itereze prin *toți* studenții, să calculeze media pentru *fiecare*, să-i sorteze și să extragă primii 20%.
    4.  **UI (Consolă):** Adăugarea meniurilor pentru "Afișare Raport 1" și "Afișare Raport 2".
    5.  **Testare și Refactorizare:** Asigurarea că toate funcționalitățile merg împreună și că nu există erori (ex: ce se întâmplă dacă ștergi un student care are note?).
