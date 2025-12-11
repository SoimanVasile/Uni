from domeniu.Experiment import Experiment


class RepoExperimente:
    def __init__(self, file_name: str):
        self.__experimente = {}
        self.__file_name = file_name

    def __read_from_fisier(self):
        with open(self.__file_name, 'r') as f:
            self.__experimente = {}
            linii = f.readlines()
            for linie in linii:
                linie.strip()
                if linie != "":
                    parti = linie.split(',')
                    id_experiment =int( parti[0])
                    titlu = parti[1]
                    tip = parti[2]
                    profesor = parti[3]
                    nr_repetari = float(parti[4])
                    nr_succese = float(parti[5])
                    experiment = Experiment(id_experiment, titlu, tip, profesor, nr_repetari, nr_succese)
                    self.__experimente[id_experiment] = experiment


    def __save_in_file(self):
        with open(self.__file_name, 'w') as f:
            for experiment in self.__experimente.values():
                id_experiment = experiment.get_id_experiment()
                titlu = experiment.get_titlu()
                tip = experiment.get_tip()
                profesor = experiment.get_profesor()
                nr_repetari = experiment.get_nr_repeterari()
                nr_succese = experiment.get_nr_succes()
                f.write(f"{id_experiment},{titlu},{tip},{profesor},{nr_repetari},{nr_succese}")

    def get_all(self):
        """
        returneaza toate experimentele
        :return lista cu experimentele existente
        """
        self.__read_from_fisier()
        return list(self.__experimente.values())
