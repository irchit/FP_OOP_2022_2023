class Spectacol():

    def __init__(self, titlu, artist, gen, durata):
        '''
        Functie de initiere a unui spectacol de tip Spectacol
        :param titlu: str - nevid
        :param artist: str - nevid
        :param gen: str din ["Concert", "Comedie", "Balet", "Altele"]
        :param durata: int pozitiv
        '''
        self.__titlu = titlu
        self.__artist = artist
        self.__gen = gen
        self.__durata = durata

    def get_titlu(self):
        '''
        Get-er pt titlu
        :return: str - titlu spectacolului
        '''
        return self.__titlu

    def get_artist(self):
        '''
        Get-er pt artist
        :return: str - artist spectacolului
        '''
        return self.__artist

    def get_gen(self):
        '''
        Get-er pt gen
        :return: str - genul spectacolului
        '''
        return self.__gen

    def get_durata(self):
        '''
        Get-er pt durata
        :return: int - durata spectacolului
        '''
        return self.__durata

    def set_titlu(self, titlu_nou):
        '''
        Set-er pt titlu, se va modifica titlul unui spectacol
        :param titlu_nou: str - titlul nou al lui
        :return: None
        '''
        self.__titlu = titlu_nou

    def set_artist(self, artist_nou):
        '''
        Set-er pt artist, se va modifica artistul unui spectacol
        :param artist_nou: str - artistul nou al lui
        :return: None
        '''
        self.__artist = artist_nou

    def set_gen(self, gen_nou):
        '''
        Set-er pt gen, se va modifica genul unui spectacol
        :param gen_nou: str - genul nou al lui
        :return:
        '''
        self.__gen = gen_nou

    def set_durata(self, durata_noua):
        '''
        Set-er pt durata, se va modifica durata unui spectacol
        :param durata_noua: int - durata noua al lui
        :return:
        '''
        self.__durata = durata_noua

    def __eq__(self, other):
        '''
        Verifica egalitatea a doua entitati de tip Spectacol
        :param other: referinta la un Spectacol
        :return: True daca au acelasi titlu si artist
                 False altfel
        '''
        return self.__titlu == other.__titlu and self.__artist == other.__artist

    def __str__(self):
        '''
        Parseaza continutul dintr-un Spectacol la string de tip csv
        :return: str - csv cu continutul Spectacolului
        '''
        return f"{self.__artist},{self.__titlu},{self.__durata},{self.__gen}"
