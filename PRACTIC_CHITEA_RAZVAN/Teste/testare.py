from Business.service_spectacole import ServiceSpectacole
from Domain.spectacol import Spectacol
from Exceptii.repo_error import RepoError
from Exceptii.valid_error import ValidError
from Infrastructura.file_repo_spectacole import FileRepoSpectacole
from Validator.validator_spectacol import ValidatorSpectacol


class Testare():

    def __init__(self):
        pass

    def run_teste(self):
        self.__validator = ValidatorSpectacol()
        self.__repo = FileRepoSpectacole("Teste/teste.in")
        print(self.__teste_domain())
        print(self.__teste_validator())
        print(self.__teste_repo())
        print(self.__teste_service())

    def __teste_domain(self):
        self.__spectacol_bun = Spectacol("Lebada neagra", "Maria Georgiana", "Balet", 2500)
        assert self.__spectacol_bun.get_titlu() == "Lebada neagra"
        assert self.__spectacol_bun.get_artist() == "Maria Georgiana"
        assert self.__spectacol_bun.get_gen() == "Balet"
        assert self.__spectacol_bun.get_durata() == 2500

        spectacol = Spectacol("Lebada neagra", "Maria Georgiana", "Balet", 2500)
        assert self.__spectacol_bun == spectacol

        spectacol.set_titlu("StandUpNow")
        spectacol.set_artist("Micutzu")
        spectacol.set_gen("Altele")
        spectacol.set_durata(2000)
        assert spectacol.get_titlu() == "StandUpNow"
        assert spectacol.get_artist() == "Micutzu"
        assert spectacol.get_gen() == "Altele"
        assert spectacol.get_durata() == 2000

        assert self.__spectacol_bun != spectacol
        assert str(spectacol) == "Micutzu,StandUpNow,2000,Altele"

        return "Teste domain ok!"

    def __teste_validator(self):
        self.__validator.valideaza_spectacol(self.__spectacol_bun)
        spectacol_gresit = Spectacol("", "", "StandUp", -1000)
        try:
            self.__validator.valideaza_spectacol(spectacol_gresit)
            assert False
        except ValidError as ve:
            assert str(ve) == "Titlu invalid\nArtist invalid\nDurata invalida\nGen invalid\n"

        return "Teste validator ok!"

    def __teste_repo(self):
        with open("Teste/teste.in", "w") as f:
            pass

        assert len(self.__repo) == 0
        assert self.__repo.get_spectacole() == []

        self.__repo.adauga_spectacol(self.__spectacol_bun)
        assert len(self.__repo) == 1

        self.__repo.sterge_spectacol(self.__spectacol_bun.get_titlu(), self.__spectacol_bun.get_artist())
        assert len(self.__repo) == 0

        try:
            self.__repo.sterge_spectacol("Cantecul pisicilor", "Nelson Mondialu")
            assert False
        except RepoError as re:
            assert str(re) == "Spectacol inexistent"

        self.__repo.adauga_spectacol(self.__spectacol_bun)
        spectacol_modificat = Spectacol("Lebada neagra", "Maria Georgiana", "Altele", 10000)
        self.__repo.modifica_spectacol(spectacol_modificat)
        assert self.__repo.cauta_spectacol("Lebada neagra", "Maria Georgiana").get_gen() == "Altele"
        assert self.__repo.cauta_spectacol("Lebada neagra", "Maria Georgiana").get_durata() == 10000

        try:
            spectacol_inexistent = Spectacol("Miau", "Hau", "Comedie", 500)
            self.__repo.modifica_spectacol(spectacol_inexistent)
            assert False
        except RepoError as re:
            assert str(re) == "Spectacol inexistent"

        event = self.__repo.cauta_spectacol("Lebada neagra", "Maria Georgiana")
        assert event == self.__spectacol_bun

        try:
            spectacol_inexistent = self.__repo.cauta_spectacol("Miau", "Miau")
            assert False
        except RepoError as re:
            assert str(re) == "Spectacol inexistent"

        return "Teste repo ok!"

    def __teste_service(self):
        with open("Teste/teste.in", "w") as f:
            pass
        repo = FileRepoSpectacole("Teste/teste.in")
        service = ServiceSpectacole(repo, self.__validator)

        spectacol_valid = Spectacol("Boom", "Cabral", "Altele", 5000)
        spectacol_invalid = Spectacol("", "", "Emisiune", -100)

        assert service.adauga_spectacol("Boom", "Cabral", "Altele", 5000) == "Spectacol adaugat cu succes"
        try:
            service.adauga_spectacol("", "", "Emisiune", -100)
            assert False
        except ValidError as ve:
            assert str(ve) == "Titlu invalid\nArtist invalid\nDurata invalida\nGen invalid\n"

        assert service.modifica_spectacol("Boom", "Cabral", "Comedie", 10000) == "Spectacol modificat cu succes"
        try:
            service.modifica_spectacol("Parol", "Petru", "Altele", 10000)
            assert False
        except RepoError as ve:
            assert str(ve) == "Spectacol inexistent"
        try:
            service.modifica_spectacol("Boom", "Cabral", "Jocuri", -10000)
            assert False
        except ValidError as ve:
            assert str(ve) == "Durata invalida\nGen invalid\n"

        assert service.genereaza_spectacole(10) == "Cele 10 spectacole au fost generate cu succes"
        assert len(service.get_spectacole()) == 11

        assert service.exporta_spectacolele("Teste/export.out") == "Fisierul a fost exportat cu succes"

        try:
            open("Teste/export.out", "x")
            assert False
        except:
            assert True

        return "Teste service ok!"


