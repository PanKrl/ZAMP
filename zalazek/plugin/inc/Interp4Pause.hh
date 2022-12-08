#ifndef  COMMAND4PAUSE_HH
#define  COMMAND4PAUSE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Pause
 *
 * Plik zawiera definicjê klasy Interp4Pause ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluje zatrzymanie w pozycji.
 */
class Interp4Pause: public Interp4Command {

private:
   int _Pause_time;


 public:
  /*!
   * \brief
   */
  Interp4Pause();
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
