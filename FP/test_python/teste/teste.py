from domeniu.Experiment import Experiment

from Repo.RepoExperimente import RepoExperimente

from Service.ServiceExperimente import ServiceExperimente

from Validare.ValidareExperiment import ValidareExperiment

from consola.consola import Consola

import os
import unittest

class TestServiceExperimente(unittest.TestCase):

    def setUp(self):
        self.file_name = "test_experimente.txt"

        with open(self.file_name, 'w') as f:
            f.write("")

        repo_experiment = RepoExperimente(self.file_name)

        validator_experiemnt = ValidareExperiment()

        self.service_experimente = ServiceExperimente(repo_experiment, validator_experiemnt)
    
    def tearDown(self):
        if os.path.exists(self.file_name):
            os.remove(self.file_name)
