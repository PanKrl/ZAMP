#ifndef  COMMAND4MOVE_HH
#define  COMMAND4MOVE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Move
 *
 * Plik zawiera definicjê klasy Interp4Move która odpowiada za poruszanie obiektem z na dan¹ odleg³oœæ z zadan¹ prêdkoœci¹.
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluje polecenie umozliwiaj¹ce ruch do przodu z zadan¹ prêdkoœci¹.
 * Dodatkowo definiujemy odleg³oœæ do przejechania oraz nazwê.
 */
class Interp4Move: public Interp4Command {
  /*
   *  Tu nale¿y zdefiniowaæ pola, które s¹ niezbêdne
   *  do przechowywania wartoœci parametrów danego polecenia.
   *  Ponie¿ej zdefiniowane jest tylko jedno pole jako przyk³ad.
   */
  double _Speed_mmS;//!< pole przechowuj¹ce prêdkoœæ
  double _Lenght;//!< pole przechowuj¹ce d³ugoœæ drogi
  std::string _Obj_Name;//!< pole przechowuj¹ce nazwê
 public:
  /*!
   * \brief Konstruktor klasy
   */
  Interp4Move();  
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
