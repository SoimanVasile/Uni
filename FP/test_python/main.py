from domeniu.Experiment import Experiment

from Repo.RepoExperimente import RepoExperimente

from Service.ServiceExperimente import ServiceExperimente

from Validare.ValidareExperiment import ValidareExperiment

from consola.consola import Consola

file_experimente = "experimente.txt"
repo_experimente = RepoExperimente(file_experimente)

validator_experiment = ValidareExperiment()
service_experiment = ServiceExperimente(repo_experimente, validator_experiment)

UI = Consola(service_experiment)

UI.run()
