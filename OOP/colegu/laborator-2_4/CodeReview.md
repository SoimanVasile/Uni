# Code Review Template: Lab 5

**Reviewer Name:** [Your Name]  
**Reviewer Group:** [Your Group]  
**Initial C application was created by (Name/Group):** [Colleague's Name / Group]  

---

### 0. Strengths & Positive Aspects
Before diving into areas of improvement, it is important to highlight the strong points of this implementation:

* **Good Foundational Architecture:** The application demonstrates a clear conceptual understanding of layered architecture. The code is logically split into Domain (`domain.c`), Repository (`repo.c`), and Service (`service.c`) layers, which provides a solid foundational structure.
* **Dynamic Memory Resizing:** The Repository successfully implements a dynamic array with automatic capacity resizing (`asigura_capacitate` using `realloc`). This is an excellent feature that prevents crashes due to hardcoded limits.
* **Proactive Memory Deallocation:** The deallocation logic is well thought out. The implementation includes comprehensive destructor functions for all layers (`distruge_materie`, `distruge_repo`, `distruge_service`) and successfully prevents major memory leaks when elements are deleted or updated (e.g., freeing the old `producator` string).
* **Strong Automated Testing:** The inclusion of the `ruleaza_teste()` function is a massive plus. The effective use of `assert` to automatically verify core CRUD functionalities and edge cases (like adding negative quantities) shows a great testing mindset.
* **Clean and Readable Code:** The functions are generally short, focused on a single task, and easy to read. Logic within core functions like `adauga_materie` is straightforward and avoids unnecessary complexity.

---

### 1. Functionality
**List of application functionalities that are missing, are incomplete or buggy:**
* **Bug (Undefined Behavior):** In `main.c`, the application prints the `cantitate` field (a `double`) using the `%d` format specifier. This expects an integer and prints garbage memory values. It must be updated to `%f` or `%.2f`.
* **Compilation Errors (Strict Standards):** Fails to compile under strict `-std=c17` because `strdup` is a POSIX extension. **Fix:** Change the Makefile standard to `-std=gnu17`.
* **Bug (Potential Buffer Overflow):** *(Reviewer Note: Verify if the Repo checks if the array is full before adding a new element. If it doesn't check capacity, it will crash when exceeding the limit).*
* **Unimplemented Functions (Header vs. Source mismatch):** The code declares functions in the header files that are **never implemented** in the `.c` files.
  * In `repo.h`, the function `MateriePrima* cauta(Repo* r, char* nume);` is declared but missing from `repo.c`.
  * In `service.h`, the function `Repo* filtrare(Service* s, char litera, int cantitate_max);` is declared but completely missing from `service.c`. 

### 2. Testing & Coverage
**List of program functions (except UI) that are not covered by tests:**
* **Poor Test Architecture:** Tests are written inside a single massive function in `main.c`. Tests should be modular (e.g., `test_repo()`, `test_service()`) and moved to a dedicated `test.c` file.
* **Incomplete Code Coverage:** The function `copiaza_materie` in the domain module is defined but never called, resulting in dead code and incomplete coverage.

### 3. Specifications
**List of program functions lacking specification:**
* **Complete Lack of Specifications:** None of the functions exposed in the header files (`domain.h`, `repo.h`, `service.h`) are documented. In C, header files serve as the API documentation for the modules. Every exposed function must have a clear comment block describing its purpose, its parameters (`preconditions`), and what it returns (`postconditions`).

### 4. Modularity and Separation
**Is there a clear separation between each module’s specification and its implementation? Please detail…**
* **No, there is a breach of encapsulation (Tight Coupling).** The `Service` accesses the internal fields of the `Repository` directly (e.g., `repo->length`). The Repository must expose getter functions (e.g., `get_length()`).
* **Business Logic Leaking into UI (Major Flaw):** Because the `filtrare` function was never implemented in the Service, the UI takes over. In `main.c`, the `ui_filtrare` function contains a `for` loop that iterates directly through `s->repo->elemente` to find and print the items. Filtering is business logic and MUST belong in the Service. The UI should merely call a Service function that returns a list of filtered elements, and then print that list.
* **Bypassing the Service Layer:** In `main.c` (case 5: sortare), the UI calls `sortare(s->repo, 1, ordine);`. The UI is bypassing the Service layer and passing the Repository directly to the sorting function. Furthermore, the `sortare` function in `service.c` takes a `Repo*` as its first parameter instead of a `Service*`, breaking the standard Service layer pattern.
* **Poor Project Structure:** Header and source files are mixed in the root directory. Standard C architecture requires `.h` files in an `include/` directory and `.c` files in a `src/` directory.

### 5. Layered Architecture
**Is the application correctly layered? Please detail…**
* **No, the application is missing a dedicated presentation layer.** There is no `UI` module. User interaction (`printf`, `scanf`, menus) is improperly mixed inside `main.c`. A dedicated `ui.c` and `ui.h` module must be created.

### 6. Memory Management
**Does the application handle memory correctly (all memory is deallocated, no dangling pointers etc.). Please detail…**
* **No, missing NULL pointer checks.** The application blindly assumes memory allocations always succeed. When calling `malloc` or `strdup` (in `domain.c` and `repo.c`), the returned pointer is never checked against `NULL`. If the system runs out of memory, the program will trigger a Segmentation Fault. Every allocation must be verified before use.

### 7. Code Clarity
**List those functions that are unclear to you (you don’t understand their role or how they work – usually a sign of bad design):**
* **Poor Naming:** Variables are too short and fail to convey intent (using `r`, `s`, or `m` instead of `repo`, `service`, or `materie`). 
* **Magic Numbers:** The code uses `1` for success and `0` for error instead of descriptive enumerations (e.g., `enum ErrorCode`). 
* **Missing Defensive Copies:** If the Repo returns direct pointers to the Service, the Service can accidentally modify internal data. It should return a copy using `copiaza_materie`.

### 8. Action Plan & Estimation
**List the problems present in the reviewed application and indicate the number of man-hours you require for fixing them:**

| Problem | Required Fix | Estimated Time |
| :--- | :--- | :--- |
| **Missing UI Layer** | Create `ui.c`/`ui.h` and move console logic out of `main.c`. | 1.0 hr |
| **Memory Allocation Bugs** | Add `if (ptr == NULL) return NULL;` checks after every `malloc` and `strdup` call. | 0.5 hr |
| **Compiler / Format Bugs** | Change `%d` to `%f`. Change standard to `-std=gnu17`. Add capacity bounds checking to Repo. | 0.5 hr |
| **Missing Implementations** | Write the code for `cauta` in `repo.c` and `filtrare` in `service.c`. | 0.5 hr |
| **Layer Violation (Filtering)** | Remove the `for` loop from `ui_filtrare`. Make the Service return a dynamically allocated array of filtered items for the UI to print. | 1.0 hr |
| **Layer Violation (Sorting)** | Change `sortare` signature to accept `Service* s`. Update UI to call `sortare(s, ...)` without exposing the `repo`. | 0.5 hr |
| **Missing Specs** | Add Doxygen-style documentation (param, return, etc.) to all functions in header files. | 0.5 hr |
| **Test Restructuring** | Extract tests into modular functions in a separate file. | 0.5 hr |
| **Project Structure** | Move files to `include/` and `src/` folders. Update Makefile. | 0.5 hr |
| **Tight Coupling** | Hide Repo internals behind getters. Implement defensive copying. | 1.0 hr |
| **Code Clarity** | Refactor magic numbers to `enum` and rename short variables. | 1.0 hr |
| **Total Estimated Time** | | **~7.5 hrs** |
