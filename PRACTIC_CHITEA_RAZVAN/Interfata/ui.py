import os

from Exceptii.repo_error import RepoError
from Exceptii.valid_error import ValidError


class Consola:

    def __init__(self, service_spectacole):
        '''
        Functie de initiere a unei console de tip Consola
        :param service_spectacole: ServiceSepcatcole - referinta la obiect
        '''
        self.__service_spectacole = service_spectacole
        self.__output = ""
        self.__functionalitati = {
            1: self.__adauga_spectacol,
            2: self.__modifica_spectacol,
            3: self.__genereaza_spectacole,
            4: self.__exporta_fisier
        }
        self.__menu = [
            "1. adauga spectacol",
            "2. modifica spectacol",
            "3. genereaza spectacole",
            "4. exporta spectacole",
            "0. inchideti aplicatia"
        ]

    def __adauga_spectacol(self):
        '''
        Citeste titlul, artistul, durata si genul unui spectacol nou apoi il creaza in service
        :return: str - mesaj confirmare
        :raise ValueError: "Durata trebuie sa fie int!" - daca durata nu e int
        '''
        titlu = input("Titlu: ")
        artsit = input("Artist: ")
        durata = input("Durata: ")
        gen = input("Gen ('Comedie', 'Concert', 'Balet', 'Altele'): ")
        try:
            durata = int(durata)
        except:
            raise ValueError("Durata trebuie sa fie int!")
        return self.__service_spectacole.adauga_spectacol(titlu, artsit, gen, durata)

    def __modifica_spectacol(self):
        '''
        Modifica un spectacol din service cu titlu si artistu existent cu o durata si gen nou daca e cazul
        :return: str - mesaj de confirmare
        :raise ValueError: "Durata trebuie sa fie int!" - daca durata nu e int
        '''
        titlu = input("Titlu existent: ")
        artsit = input("Artist existent: ")
        durata = input("Durata: ")
        gen = input("Gen ('Comedie', 'Concert', 'Balet', 'Altele'): ")
        try:
            durata = int(durata)
        except:
            raise ValueError("Durata trebuie sa fie int!")
        return self.__service_spectacole.modifica_spectacol(titlu, artsit, gen, durata)

    def __genereaza_spectacole(self):
        '''
        Citeste numarul de spectacole ce vor fi generate apoi le genereaza
        :return: str - mesaj de confirmare
        :raises ValueError: "Numarul de generari trebuie sa fie int" - daca numarul nu e int
                            "Numarul de generari trebuie sa fie pozitiv nenul" - daca numarul e <= 0
        '''
        numar_de_generari = input("Numar de spectacole de generat: ")
        try:
            numar_de_generari = int(numar_de_generari)
        except:
            raise ValueError("Numarul de generari trebuie sa fie int")
        if numar_de_generari <= 0:
            raise ValueError("Numarul de generari trebuie sa fie pozitiv nenul")
        return self.__service_spectacole.genereaza_spectacole(numar_de_generari)

    def __exporta_fisier(self):
        '''
        Citeste un nume de fisier, in care va exporta in service toate spectacolele
        :return: str - mesaj de confirmare
        :raise ValueError: "Numele fisierului trebuie sa fie de formatul nume.tip" - daca numele e invalid
        '''
        nume_fisier = input("Nume fisier: ")
        try:
            nume, tip = nume_fisier.split('.')
        except:
            raise ValueError("Numele fisierului trebuie sa fie de formatul nume.tip")
        return self.__service_spectacole.exporta_spectacolele(nume_fisier)

    def run_ui(self):
        '''
        Main Loopul programului, unde se citeste comanda si se apeleaza functiile de afisare
        :return: int = 0 - daca a rulat cu succes
        '''
        os.system("cls")
        self.__afiseaza_spectacolele()
        self.__print_menu()
        while True:
            x = input("Numar buton: ")
            try:
                x = int(x)
            except:
                self.__output = "Comanda invalida"
                os.system("cls")
                self.__print_menu()
                continue
            if x == 0:
                os.system("cls")
                print("Aplicatia a fost inchisa!")
                return 0
            elif 0 < x <= 4:
                try:
                    self.__output = self.__functionalitati[x]()
                except ValueError as ve:
                    self.__output = "ValueError: " + str(ve)
                except ValidError as ve:
                    self.__output = "ValidError: " + str(ve)
                except RepoError as re:
                    self.__output = "RepoError: " + str(re)
                os.system("cls")
                self.__print_menu()
            else:
                self.__output = "Comanda invalida"
                os.system("cls")
                self.__print_menu()

    def __afiseaza_spectacolele(self):
        '''
        Afiseaza la pornire continutul fisierului
        :return: None
        '''
        spectacole = self.__service_spectacole.get_spectacole()
        print("{:<20} {:<20} {:<20} {:<20}".format("Titlu", "Artist", "Gen", "Durata"))
        for spectacol in spectacole:
            print("{:<20} {:<20} {:<20} {:<20}".format(spectacol.get_titlu(), spectacol.get_artist(), spectacol.get_gen(), spectacol.get_durata()))
        print("")

    def __print_menu(self):
        '''
        Afiseaza meniul cu butoanele existente
        :return: None
        '''
        for line in self.__menu:
            print(line)
        if self.__output != "":
            print(f"Output:\n{self.__output}")

