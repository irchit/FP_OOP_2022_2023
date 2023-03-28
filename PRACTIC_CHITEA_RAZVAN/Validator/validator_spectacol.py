from Exceptii.valid_error import ValidError


class ValidatorSpectacol:

    def __init__(self):
        '''
        Initializeaza un validator de tip ValidatorSpectacol
        '''
        pass

    def valideaza_spectacol(self, spectacol):
        '''
        Functia valideaza un spectacol dupa urmatoarele criterii:
        - titlu si artist: str - nevid
        - durata: unsigned int
        - gen: str - sa fie una dintre urmatoarele: Comedie, Concert, Balet, Altele
        :param spectacol: referinta la un Spectacol
        :return: None
        :raise ValidError: str - contine erorile spectacolului daca exista
        '''
        artist = spectacol.get_artist()
        titlu = spectacol.get_titlu()
        gen = spectacol.get_gen()
        durata = spectacol.get_durata()
        erori = ""

        if titlu == "":
            erori += "Titlu invalid\n"
        if artist == "":
            erori += "Artist invalid\n"
        if durata < 0:
            erori += "Durata invalida\n"
        if gen not in ["Comedie", "Concert", "Balet", "Altele"]:
            erori += "Gen invalid\n"

        if len(erori) != 0:
            raise ValidError(erori)
