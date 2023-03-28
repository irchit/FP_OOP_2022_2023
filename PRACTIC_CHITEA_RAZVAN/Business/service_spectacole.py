import random

from Domain.spectacol import Spectacol
from Exceptii.repo_error import RepoError
from Exceptii.valid_error import ValidError


class ServiceSpectacole():

    def __init__(self, repo_spectacole, validator_spectacol):
        '''
        Functie de initiere a unui service de tip ServiceSpectacole
        :param repo_spectacole: RepoSpectacole - referinta la obiect
        :param validator_spectacol: ValidatorSpectacol - referinta la obiect
        '''
        self.__repo_spectacole = repo_spectacole
        self.__validator_spectacole = validator_spectacol

    def adauga_spectacol(self, titlu, artist, gen, durata):
        '''
        Adauga un spectacol nou cu titlul: titlu
                                cu artistul: artist
                                cu durata: durata
                                si cu genul: gen
        in repozitoriu dupa ce a fost validat
        :param titlu: str
        :param artist: str
        :param gen: str
        :param durata: int
        :return: "Spectacolul adaugat cu succes"
        '''
        spectacol = Spectacol(titlu, artist, gen, durata)
        self.__validator_spectacole.valideaza_spectacol(spectacol)
        self.__repo_spectacole.adauga_spectacol(spectacol)
        return "Spectacol adaugat cu succes"

    def modifica_spectacol(self, titlu, artist, gen, durata):
        '''
        Modifica un spectacol cu titlul: titlu si cu artistul: artist
        si cu valorile noi durata: durata si genul: gen
        din repozitoriu dupa ce a fost validat
        :param titlu: str
        :param artist: str
        :param gen: str
        :param durata: int
        :return: "Spectacolul modificat cu succes"
        '''
        spectacol = Spectacol(titlu, artist, gen, durata)
        self.__validator_spectacole.valideaza_spectacol(spectacol)
        self.__repo_spectacole.modifica_spectacol(spectacol)
        return "Spectacol modificat cu succes"

    def genereaza_spectacole(self, numar_de_generari):
        '''
        Genereaza un numar dat de spectacole random
        :param numar_de_generari: int > 0
        :return: "Cele {numar_de_generari} spectacole au fost generate cu succes"
        '''
        genuri = ["Comedie", "Concert", "Balet", "Altele"]
        vocale = ['a', 'e', 'i', 'o', 'u']
        consoane = ['b', 'c', 'd', 'f', 'g', 'h', 'j', 'l', 'm', 'n', 'p', 'r', 's', 't', 'v']
        for i in range(0, numar_de_generari):
            valid = False
            while not valid:
                titlu = ""
                artist = ""
                durata = random.randint(1000, 10000)
                gen = genuri[random.randint(0, 3)]
                lung_titlu = random.randint(9, 12)
                l = lung_titlu
                while lung_titlu > 0:
                    if lung_titlu % 2 == 0:
                        titlu += vocale[random.randint(0, len(vocale) - 1)]
                    else:
                        titlu += consoane[random.randint(0, len(consoane) - 1)]
                    if lung_titlu == l // 2:
                        titlu += " "
                    lung_titlu -= 1
                lung_artist = random.randint(9, 13)
                l = lung_artist
                while lung_artist > 0:
                    if lung_artist % 2 == 0:
                        artist += vocale[random.randint(0, len(vocale) - 1)]
                    else:
                        artist += consoane[random.randint(0, len(consoane) - 1)]
                    if lung_artist == l // 2:
                        artist += " "
                    lung_artist -= 1
                spectacol = Spectacol(titlu, artist, gen, durata)
                try:
                    self.__validator_spectacole.valideaza_spectacol(spectacol)
                    self.__repo_spectacole.adauga_spectacol(spectacol)
                    valid = True
                except ValidError as ve:
                    continue
                except ValueError as ve:
                    continue
                except RepoError as ve:
                    continue
        return f"Cele {numar_de_generari} spectacole au fost generate cu succes"

    def exporta_spectacolele(self, nume_fisier):
        spectacole = self.__repo_spectacole.get_spectacole()
        spectacole.sort(key=(lambda x: (x.get_artist(), x.get_titlu)))
        with open(nume_fisier, "w") as f:
            for spectacol in spectacole:
                f.write(str(spectacol) + "\n")
        return "Fisierul a fost exportat cu succes"

    def get_spectacole(self):
        '''
        Returneaza spectacolele din repo
        :return: list - lista cu spectacolele din repo
        '''
        return self.__repo_spectacole.get_spectacole()

