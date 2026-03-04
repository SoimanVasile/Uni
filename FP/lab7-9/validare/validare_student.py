from exceptii.EroareValidare import EroareValidare


def verificare_nume_student(nume_student):
    if not isinstance(nume_student, str):
        raise EroareValidare("Nu este sir de caractere!\n")
