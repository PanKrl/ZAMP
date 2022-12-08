#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include <sstream>
#include <memory>

#include "LibInterface.hh"
#include "Scena.hh"
#include "klient.hh"

/*!
 * \file
 * \brief Definicja klasy Set4LibInterfaces.
 *
 * Klasa ma na celu wczytywanie i obs³ugê wtyczek które s¹ u¿ywane do poruszania danym obiektem
 */
class Set4LibInterfaces {
  private:

    map <string, LibInterface*> _Lib_List; //!< Lista komend przechowywane w strukturze map

  Scena * scena; //!< WskaŸnik do obiektu klasy Scena przechowuj¹cej wszystkie obiekty

  public:
    /*!
     * \brief Konstruktor.
     *
     * Konstruktor ma za zadanie za³adawanie wszystkich wtyczek do wybranej struktury
     */
    Set4LibInterfaces(map <string, MobileObj*> & _Object_List);

  /*!
   * \brief Destruktor
   */
  ~Set4LibInterfaces();

  /*!
   * \brief Metoda wczytuje podan¹ biblioteke dynamiczne do struktury
   *
   * \param[in] path - œcie¿ka do biblioteki dynamicznej
   */
  void LoadLibrary(string path);

  /*!
   * \brief Metoda interpretuje ci¹g znaków, i przypisuje parametry z instrukcji dla odpowiedniej komendy
   *
   * \param[in] iStrm - Strumieñ utworzony przez funkcjê ExecPreprocessor
   */
  bool ReadCommands(istringstream & iStrm, int socket);

  bool ExecPreprocessor(const char * NazwaPliku, istringstream & IStrm4Cmds);

  Scena * getScena() {
    return this -> scena;
  }
};

#endif
