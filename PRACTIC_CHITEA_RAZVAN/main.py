from Business.service_spectacole import ServiceSpectacole
from Infrastructura.file_repo_spectacole import FileRepoSpectacole
from Interfata.ui import Consola
from Teste.testare import Testare
from Validator.validator_spectacol import ValidatorSpectacol

if __name__ == "__main__":
    testare = Testare()
    testare.run_teste()

    cale_fisier = "spectacole.in"
    validator_spectacol = ValidatorSpectacol()
    repo_spectacole = FileRepoSpectacole(cale_fisier)
    service_spectacole = ServiceSpectacole(repo_spectacole, validator_spectacol)
    consola = Consola(service_spectacole)
    consola.run_ui()

