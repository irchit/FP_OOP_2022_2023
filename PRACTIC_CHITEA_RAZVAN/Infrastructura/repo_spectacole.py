from Exceptii.repo_error import RepoError


class RepoSpectacole():

    def __init__(self):
        '''
        Functie ce initializeaza un repozitoru de tip RepoSpectacole
        '''
        self._spectacole = []

    def adauga_spectacol(self, spectacol):
        '''
        Functia adauga un spectacol nou in repo
        :param spectacol: referinta la Specatcolul de adaugat
        :return: None
        '''
        self._spectacole.append(spectacol)

    def sterge_spectacol(self, titlu, artist):
        '''
        Functia sterge un spectacol din repo
        :param titlu: str
        :param artist: str
        :return: None
        :raise RepoError: "Spectacol inexistent" - daca spectacolul nu exista
        '''
        index = 0
        for spectacol in self._spectacole:
            if spectacol.get_titlu() == titlu and spectacol.get_artist() == artist:
                self._spectacole.pop(index)
                return
            index += 1
        raise RepoError("Spectacol inexistent")

    def modifica_spectacol(self, spectacol_modificat):
        '''
        Functia modifica un spectacol din repo
        :param spectacol_modificat: referinta la spectacolul cu care trebuie modificat cel
        existent
        :return: None
        :raise RepoError: "Spectacol inexistent" - daca spectacolul nu exista
        '''
        index = 0
        for spectacol in self._spectacole:
            if spectacol.get_titlu() == spectacol_modificat.get_titlu() \
                    and spectacol.get_artist() == spectacol_modificat.get_artist():
                self._spectacole[index] = spectacol_modificat
                return
            index += 1
        raise RepoError("Spectacol inexistent")

    def get_spectacole(self):
        '''
        Returneaza toate spectacolele
        :return: list - lista cu spectacole
        '''
        return self._spectacole[:]

    def __len__(self):
        '''
        Returneaza lungimea listei din repo
        :return: int - lungimea listei de spectacole
        '''
        return len(self._spectacole)

    def cauta_spectacol(self, titlu, artist):
        '''
        Cauta un spectacol dupa titlu si artist
        :param titlu: str
        :param artist: str
        :return: Spectacol - spectacolul cautat
        :raise RepoError: "Spectacol inexistent" - daca spectacolul nu exista
        '''
        index = 0
        for spectacol in self._spectacole:
            if spectacol.get_titlu() == titlu and spectacol.get_artist() == artist:
                return self._spectacole[index]
            index += 1
        raise RepoError("Spectacol inexistent")


