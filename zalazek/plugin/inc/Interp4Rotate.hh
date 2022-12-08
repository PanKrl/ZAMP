#ifndef  COMMAND4ROTATE_HH
#define  COMMAND4ROTATE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"


/*!
 * \file
 * \brief Definicja klasy Interp4Rotate
 *
 * Plik zawiera definicjê klasy Interp4Rotate ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch obrotowy
 *
 *  Klasa modeluje ...
 */
class Interp4Rotate: public Interp4Command {
  /*
   *  Tu nale¿y zdefiniowaæ pola, które s¹ niezbêdne
   *  do przechowywania wartoœci parametrów danego polecenia.
   *  Ponie¿ej zdefiniowane jest tylko jedno pole jako przyk³ad.
   */
  double  _Angular_Velocity;//!< pole przechowuj¹ce szybkoœæ k¹tow¹ w deg/s
  //double  _Axis; //!<pole przechowuj¹ce numer si obrotu
  double  _Angle; //!< pole przechowuj¹ce k¹t obrotu w deg
  std::string _Axis_Name;//!<pole przechowuj¹ce nazwê osi obrotu
  std::string _Obj_Name;//!<pole przechowuj¹ce nazwê obiektu

 public:
  /*!
   * \brief
   */
  Interp4Rotate();
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
