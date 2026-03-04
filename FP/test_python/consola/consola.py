from Service.ServiceExperimente import ServiceExperimente
from Eroare.EroareConsola import EroareConsola


class Consola:
    def __init__(self, service_experimente):
        self.__service_experimente = service_experimente
        self.__comenzi = {
            "media_ponderata_la_toti": [self.ui_media_ponderata_la_fiecare_tip, 0, []],
            "ranking_dupa_succes": [self.ui_ranking_dupa_succes, 1, [str]],
        }

    def help(self):
        print("1. media_ponderata_la_toti - afiseaza media ponderata la toate tipurile si daca are mai mare decat cel global afiseaza succes")

    def verificare_parametrii(self, comanda:str, parametrii_comanda:str):
        """
        verifica parametrii comenzii si da de tipul bun
        :comanda - comanda pe care utilizatorul sa l foloseasca
        :parametrii_comanda - parametrii pe care i a inserat
        :return - 1. EroareConsola daca nu are destui parametrii sau nu a introdus date valide
            2. parametrii de instanta buna
        """
        lungimea_parametrii = self.__comenzi[comanda][1]

        if lungimea_parametrii != len(parametrii_comanda):
            raise EroareConsola("Nr invalid de parametri!\n")

        erori = ""

        instante_bune = self.__comenzi[comanda][2]
        for ind in range(lungimea_parametrii):
            parametru = parametrii_comanda[ind]
            instanta_buna = instante_bune[ind]
            try:
                parametrii_comanda[ind] = instanta_buna(parametru)
            except:
                erori += f"Parametru {ind+1} nu este de tipul {instanta_buna}!\n"

        if len(erori) >0:
            raise EroareConsola(erori)

        return parametrii_comanda
    
    def run(self):
        while True:
            input_user = input(">>>")
            input_user.strip()

            if input_user == "exit":
                print("Sayonara!")
                break

            if input_user == "help":
                self.help()
                continue

            if input_user == "":
                continue

            parti = input_user.split()
            comanda = parti [0]
            parametrii_comanda = parti[1:]

            if comanda not in self.__comenzi.keys():
                print("Nu exista comanda")
                continue

            try:
                parametrii_comanda = self.verificare_parametrii(comanda, parametrii_comanda)
            except EroareConsola as e:
                print("EroareConsola >>>",e)
                continue

            self.__comenzi[comanda][0](parametrii_comanda)

    def ui_media_ponderata_la_fiecare_tip(self, parametrii_comanda):
        print(self.__service_experimente.media_ponderata_la_fiecare_tip())

    def ui_ranking_dupa_succes(self, parametrii_comanda):
        tip = parametrii_comanda[0]

        rezultat = self.__service_experimente.ranking_dupa_succes(tip)
        if len(rezultat) == 0:
            print("Nu exista acel tip")
        else:
            for profesor in rezultat:
                print(f"{profesor["profesor"]} ({profesor["media ponderata"]})")
