class Experiment:
    def __init__(self, id_experiment:int, titlu:str, tip: str, profesor:str, nr_repetari: int, nr_succes:int):
        self.__id_experiment = id_experiment
        self.__titlu = titlu
        self.__tip = tip
        self.__profesor = profesor
        self.__nr_repetari = nr_repetari
        self.__nr_succes = nr_succes

    def get_id_experiemnt(self):
        return self.__id_experiment

    def get_titlu(self):
        return self.__titlu

    def get_tip(self):
        return self.__tip

    def get_profesor(self):
        return self.__profesor

    def get_nr_repetari(self):
        return self.__nr_repetari

    def get_nr_succes(self):
        return self.__nr_succes

    def set_id_experiemnt(self, id_experiment_nou:int):
        self.__id_experiment = id_experiment_nou

    def set_titlu(self, titlu_nou:str):
        self.__titlu = titlu_nou

    def set_tip(self, tip_nou: str):
        self.__tip = tip_nou

    def set_profesor(self, profesor_nou: str):
        self.__profesor = profesor_nou

    def set_nr_repetari(self, nr_repetari_nou:int):
        self.__nr_repetari = nr_repetari_nou

    def set_nr_succes(self, nr_succes_nou:int):
        self.__nr_succes = nr_succes_nou

    def __repr__(self):
        return f"id experiemnt = {self.__id_experiment}; titlu = {self.__titlu}; tip = {self.__tip}; profesor = {self.__profesor}; nr repetari = {self.__nr_repetari}; nr succese = {self.__nr_succes}"
