#pragma once


#include <string>
#include <map>
#include <vector>

#include "GuardedSocket.hh"
#include "MobileObj.hh"


/*!
 * \file
 * \brief Definicja klasy Scene.
 *
 * Plik zawiera definicjê klasy Scene, przechowuj¹cej listê obiektów mobilnych w postaci struktury map.
 */

class Scena: public GuardedSocket {
  private:
    /*!
     * \brief Mapa wskaŸników na obiekty klasy MobileObj
     */
    map <string,
  MobileObj*> _Object_List;
  public:
    /*!
     * \brief Konstruktor klasy
     */
    Scena();
  /*!
   * \brief Konstruktor klasy
   */
  Scena(map < string, MobileObj * > & List);
  /*!
   * \brief Destruktor klasy
   */
  ~Scena() {
    _Object_List.clear();
  };
  /*!
   * \brief Wyszukuje i zwraca wskaŸnik na obiekt o nazwie podanej w parametrze
   *
   * \param[in] sName - nazwa obiektu mobilnego do wyszukania na scenie
   * \return Zwraca wskaŸnik na znaleziony obiekt lub nullptr, gdy obiekt nie zostanie znaleziony
   */
  MobileObj * FindMobileObj(string sName);

  /*!
   * \brief Dodaje obiekt o padanej nazwie do listy obiektów
   *
   * \param[in] sName - nazwa obiektu mobilnego do dodania do sceny
   */
  void AddMobileObj(string sName);
  /*!
   * \brief zwraca  na liste obiektów
   *
   *
   * \return Pole _Object_List klasy Scena
   */
  map <string,
  MobileObj*> getObjList() {
    return this -> _Object_List;
  }
  vector <MobileObj*> getObjects();

};
