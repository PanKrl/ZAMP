#ifndef  COMMAND4ROTATE_HH
#define  COMMAND4ROTATE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Set
 *
 * Plik zawiera definicjê klasy Interp4Set ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluje ustawienie wybranego obiektu w zadanym miejscu na scenie.
 */
class Interp4Set: public Interp4Command {

private:

  double  _Wsp_x;
  double  _Wsp_y;
  double  _Kat_Ox;
  double  _Kat_Oy;
  double  _Kat_Oz;
  std::string _Obj_Name;


 public:
  /*!
   * \brief
   */
  Interp4Set();
  /*!
   * \brief Wyœwietla postaæ bie¿¹cego polecenia (nazwê oraz wartoœci parametrów)
   */
  virtual void PrintCmd() const;
  /*!
   * \brief Wyœwietla sk³adniê polecenia
   */
  virtual void PrintSyntax() const;
  /*!
   * \brief Wyœwietla nazwê polecenia
   */
  virtual const char* GetCmdName() const;
  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizacjê
   */
  virtual bool ExecCmd( MobileObj  *pMobObj, GuardedSocket *pAccessCtrl) const;
  /*!
   * \brief Czyta wartoœci parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief Wyœwietla wartoœci wczytanych parametrów
   */
  virtual void PrintParams() {}
  /*!
   * \brief
   *
   *  Ta metoda nie musi byæ zdefiniowna w klasie bazowej.
   */
  static Interp4Command* CreateCmd();
 };

#endif
