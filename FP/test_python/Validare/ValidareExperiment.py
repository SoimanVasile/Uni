from domeniu.Experiment import Experiment
from Eroare.EroareValidare import EroareValidare


class ValidareExperiment:

    def verificare_experiment(self, experiment: Experiment):
        id_experiment = experiment.get_id_experiemnt()
        nr_repetari = experiment.get_nr_repetari()
        nr_succese = experiment.get_nr_succes()

        erori = ""

        if id_experiment <= 0:
            erori = "Id invalid!\n"

        if nr_repetari <0:
            erori = "Nr repetari negativ!\n"

        if nr_succese <0:
            erori = "Nr succese negativ!\n"

        if nr_succese > nr_repetari:
            erori = "Nr succese mai mare decat nr de incercari!\n"

        if len(erori) > 0:
            raise EroareValidare(erori)
