#ifndef INTERP4COMMAND_HH
#define INTERP4COMMAND_HH

#include <iostream>

#include "MobileObj.hh"
#include "GuardedSocket.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Command
 *
 * Plik zawiera definicjê klasy Interp4Command ...
 */

/*!
 * \brief Modeluje abstrakcyjne polecenie dla robota mobilnego
 *
 *  Klasa modeluje ...
 */
class Interp4Command {
  public:
    /*!bObj, int Socket ) const = 0;
     * \brief Destruktor wirtualny ze wzgledu na klasy pochodne
     *
     *
     */
    virtual~Interp4Command() {}
  /*!
   * \brief Wyœwietla postaæ bie¿¹cego polecenia (nazwê oraz wartoœci parametrów).
   */
  virtual void PrintCmd() const = 0;
  /*!
   * \brief Wyœwietla sk³adniê polecenia.
   */
  virtual void PrintSyntax() const = 0;
  /*!
   * \brief Wyœwietla nazwê polecenia.
   */
  virtual
  const char * GetCmdName() const = 0;
  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizacjê.
   */
  virtual bool ExecCmd(MobileObj * pMobObj, GuardedSocket * pAccCtrl) const = 0;
  //virtual bool ExecCmd( MobileObj *pMobObj, int Socket ) const = 0;
  /*!
   * \brief Czyta wartoœci parametrów danego polecenia.
   */
  virtual bool ReadParams(istream & Strm_CmdsList) = 0;
};

#endif
