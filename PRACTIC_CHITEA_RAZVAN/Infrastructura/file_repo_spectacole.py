from Domain.spectacol import Spectacol
from Infrastructura.repo_spectacole import RepoSpectacole


class FileRepoSpectacole(RepoSpectacole):

    def __init__(self, cale_fisier):
        '''
        Functie de initiere a unui file_repo de tip FileRepoSpectacole care is a RepoSpectacole
        :param cale_fisier: str
        '''
        RepoSpectacole.__init__(self)
        self.__cale_fisier = cale_fisier

    def __citeste_continut_fisier(self):
        '''
        Citeste toate spectacolele din fisierul cu calea salvata in self.__cale_fisier
        :return: None
        '''
        self._spectacole = []
        with open(self.__cale_fisier, "r") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    params = line.split(",")
                    artist = params[0]
                    titlu = params[1]
                    durata = int(params[2])
                    gen = params[3]
                    spectacol = Spectacol(titlu, artist, gen, durata)
                    self._spectacole.append(spectacol)

    def __scrie_continut_fisier(self):
        '''
        Screi toate spectacolele din repo in fisierul cu calea salvata in self.__cale_fisier
        :return: None
        '''
        with open(self.__cale_fisier, "w") as f:
            for spectacol in self._spectacole:
                f.write(str(spectacol) + "\n")

    def adauga_spectacol(self, spectacol):
        '''
        Adauga un spectacol nou in repo si in fisier
        :param spectacol: Spectacol - spectacolul de adaugat
        :return: None
        '''
        self.__citeste_continut_fisier()
        RepoSpectacole.adauga_spectacol(self, spectacol)
        self.__scrie_continut_fisier()

    def sterge_spectacol(self, titlu, artist):
        '''
        Sterge un spectacol cu titlul si artistul dat din repo si din fisier
        :param titlu: str
        :param artist: str
        :return: None
        '''
        self.__citeste_continut_fisier()
        RepoSpectacole.sterge_spectacol(self, titlu, artist)
        self.__scrie_continut_fisier()

    def modifica_spectacol(self, spectacol_modificat):
        '''
        Modifica un spectacol cu spectacolul nou dat din repo si din fisier
        :param spectacol_modificat: Spectacol - spectacol modificat cu titlu si artist existent
        :return: None
        '''
        self.__citeste_continut_fisier()
        RepoSpectacole.modifica_spectacol(self, spectacol_modificat)
        self.__scrie_continut_fisier()

    def cauta_spectacol(self, titlu, artist):
        '''
        Cauta un spectacol dupa titlu si artist in fisier
        :param titlu: str
        :param artist: str
        :return: Spectacol - spectacolul cautat
        '''
        self.__citeste_continut_fisier()
        return RepoSpectacole.cauta_spectacol(self, titlu, artist)

    def get_spectacole(self):
        '''
        Returneaza toate spectacolele din fisier
        :return: list - lista cu spectacoelle din fisier
        '''
        self.__citeste_continut_fisier()
        return RepoSpectacole.get_spectacole(self)

    def __len__(self):
        '''
        Returneaza numarul specatcolelor din fisier
        :return: int - numarul de spectacole
        '''
        self.__citeste_continut_fisier()
        return RepoSpectacole.__len__(self)


