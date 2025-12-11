from Repo.RepoExperimente import RepoExperimente
from Validare.ValidareExperiment import ValidareExperiment



class ServiceExperimente:

    def __init__(self, repo_experimente: RepoExperimente, validator_experimente: ValidareExperiment):
        self.__repo_experimente = repo_experimente
        self.__validator_experimente = validator_experimente

    def filtreza_dupa_tip(self, tip: str):
        """
        filtreaza dupa tip
        :parem tip
        :return lista de experimente care au acel tip
        """
        lista_experimente = self.__repo_experimente.get_all()
        rezultat = []
        for experiment in lista_experimente:
            tip_experiment = experiment.get_tip()
            if tip_experiment == tip:
                rezultat.append(experiment)

        return rezultat

    def calculeaza_media_ponderata_dupa_tip(self, tip: str):
        """
        calculeaza media ponderata dupa tip
        :parem tip
        :return media dupa acel tip in float
        """
        lista_experimente = self.filtreza_dupa_tip(tip)

        nr_repetari_total = 0
        nr_succese_total = 0
        for experiment in lista_experimente:
            nr_repetari_total += experiment.get_nr_repetari()
            nr_succese_total += experiment.get_nr_succes()

        return nr_succese_total/nr_repetari_total

    def calculeaza_media_ponderata_global(self):
        """
        calculeaza media ponderata dupa tip
        :parem tip
        :return media dupa acel tip in float
        """
        lista_experimente = self.__repo_experimente.get_all()

        nr_repetari_total = 0
        nr_succese_total = 0
        for experiment in lista_experimente:
            nr_repetari_total += experiment.get_nr_repetari()
            nr_succese_total += experiment.get_nr_succes()

        return nr_succese_total/nr_repetari_total

    def get_toate_tipurile(self):
        """
        returneaza toate tipurile care exista
        :return lista cu tipurile
        """
        lista_experimente = self.__repo_experimente.get_all()
        lista_tipuri = []
        for experiment in lista_experimente:
            tip = experiment.get_tip()
            if tip not in lista_tipuri:
                lista_tipuri.append(tip)

        return lista_tipuri

    def media_ponderata_la_fiecare_tip(self):
        """
        returneaza tipul si media ponderata a fiecarui tip si daca ii mai mare decat global o sa returneze si succes
        :return un string
        """
        lista_tipuri = self.get_toate_tipurile()
        pondere_globala = self.calculeaza_media_ponderata_global()

        rezultat = ""

        for tip in lista_tipuri:
            media_ponderata = self.calculeaza_media_ponderata_dupa_tip(tip)
            if media_ponderata < pondere_globala:
                rezultat += f"{tip}: {media_ponderata}\n"
            else:
                rezultat += f"{tip}: {media_ponderata}, succes\n"

        return rezultat

    def filtreaza_dupa_profesor(self, profesor:str, lista_experimente_dupa_tip):
        lista_experimente = lista_experimente_dupa_tip

        rezultat = []
        for experiment in lista_experimente:
            profesor_experiment = experiment.get_profesor()
            if profesor_experiment == profesor:
                rezultat.append(experiment)

        return rezultat

    def calculeaza_rata_de_succes_la_profesor(self, profesor:str, lista_experimente):
        lista_experimente_profesor = self.filtreaza_dupa_profesor(profesor, lista_experimente)

        nr_repetari_total = 0.0
        nr_succese_total = 0.0
        for experimente in lista_experimente_profesor:
            nr_repetari_total += experimente.get_nr_repetari()
            nr_succese_total += experimente.get_nr_succes()

        return nr_succese_total/nr_repetari_total

    def get_toti_profesorii(self,lista_experimente):
        rezultat = []
        for experimente in lista_experimente:
            profesor_experiment = experimente.get_profesor()
            if profesor_experiment not in rezultat:
                rezultat.append(profesor_experiment)

        return rezultat

    def media_ponderata_la_fiecar_prof(self, tip):
        lista_experimente_tip = self.filtreza_dupa_tip(tip)
        lista_profesori = self.get_toti_profesorii(lista_experimente_tip)

        media_ponderata_la_profi = []

        for profesor in lista_profesori:
            media_ponderata = self.calculeaza_rata_de_succes_la_profesor(profesor, lista_experimente_tip)

            dto = {
                "profesor": profesor,
                "media ponderata": media_ponderata,
            }
            media_ponderata_la_profi.append(dto)

        return media_ponderata_la_profi

    def sorteaza_dupa_medie(self, lista_media_ponderata):
        lista_sortata = lista_media_ponderata
        
        ok = 1
        m = len(lista_media_ponderata)
        while ok == 1:
            ok = 0
            for i in range(1,m):
                if lista_sortata[i-1]["media ponderata"] < lista_sortata[i]["media ponderata"]:
                    lista_sortata[i-1],lista_sortata[i] = lista_sortata[i], lista_sortata[i-1]
                    ok = 1

            m-= 1

        return lista_sortata


    def ranking_dupa_succes(self, tip:str):
        lista_media_ponderata_la_profi = self.media_ponderata_la_fiecar_prof(tip)
        lista_media_ponderata_la_profi = self.sorteaza_dupa_medie(lista_media_ponderata_la_profi)

        return lista_media_ponderata_la_profi
        
