#ifndef MOBILEOBJ_HH
#define MOBILEOBJ_HH

#include <string>
#include <sstream>

#include "Vector3D.hh"


/*!
 * \file
 * \brief Zawiera definicjê klasy MobileObj
 *
 * Plik zawiera definicjê klasy MobileObj.
 * Definicja to mo¿e byæ rozszerzona i zmienione mog¹
 * byæ nazwy pól. Obowi¹zkowe s¹ jedynie nazwy metod.
 */

/*!
 * Nazwy pól klasy s¹ jedynie propozycj¹ i mog¹ byæ zmienione
 * Nazwy metod s¹ obowi¹zuj¹ce.
 */
class MobileObj {
  /*!
   * \brief K¹t \e yaw reprezentuje rotacjê zgodnie z ruchem wskazówek zegara
   *        wokó³ osi \e OZ.
   *
   * K¹t \e yaw reprezentuje rotacjê zgodnie z ruchem wskazówek zegara
   * wokó³ osi \e OZ. Wartoœæ k¹ta wyra¿ona jest w stopniach.
   */
  double _Ang_Yaw_deg = 0;

  /*!
   * \brief K¹t \e pitch reprezentuje rotacjê zgodnie z ruchem wskazówek zegara
   *        wokó³ osi \e OY.
   *
   * K¹t \e pitch reprezentuje rotacjê zgodnie z ruchem wskazówek zegara
   * wokó³ osi \e OY. Wartoœæ k¹ta wyra¿ona jest w stopniach.
   */
  double _Ang_Pitch_deg = 0;

  /*!
   * \brief K¹t \e roll reprezentuje rotacjê zgodnie z ruchem wskazówek zegara
   *        wokó³ osi \e OX.
   *
   * K¹t \e roll reprezentuje rotacjê zgodnie z ruchem wskazówek zegara
   * wokó³ osi \e OX. Wartoœæ k¹ta wyra¿ona jest w stopniach.
   */
  double _Ang_Roll_deg = 0;

  /*!
   * \brief Wspó³rzêdne aktualnej pozycji obiektu.
   *
   * Wspó³rzêdne aktualnej pozycji obiektu. Przyjmuje siê,
   * ¿e wspó³rzêdne wyra¿one s¹ w metrach.
   */
  Vector3D _Position_m;

  /*!
   * \brief Nazwa obiektu, która go indentyfikuje.
   *
   * Nazwa obiektu, która go indentyfikuje. Z tego wzglêdu musi
   * musi to byæ nazwa unikalna wœród wszystkich obiektów na scenie.
   */
  string _Name;

  Vector3D _Scale;

  Vector3D _Shift;

  int color[3];

  public:
    /*!
     * \brief Zwraca informacjê o stanie obiektu
     *
     * \return ciag znaków zawieraj¹cy informacje o obiekcie.
     */
    string ActualPosition() {
      char buffer[100];
      int len = sprintf(buffer, " Name=%s RotXYZ_deg=(%f,%f,%f)\n", this -> _Name.c_str(), this -> _Ang_Yaw_deg, this -> _Ang_Pitch_deg, this -> _Ang_Roll_deg);
      string result(buffer, len);

      return result;
    }

  /*!
   * \brief Zwraca informacjê o stanie obiektu
   *
   * \return ciag znaków zawieraj¹cy informacje o obiekcie.
   */
  string returnParameters() {
    char buffer[200];
    int length = sprintf(buffer, "Name=%s RGB=(%d,%d,%d) Scale=(%f,%f,%f) Shift=(%f,%f,%f) RotXYZ_deg=(%f,%f,%f) Trans_m=(%f,%f,%f)\n",
      this -> _Name.c_str(), this -> color[0], this -> color[1], this -> color[2], this -> _Scale[0], this -> _Scale[1], this -> _Scale[2],
      this -> _Shift[0], this -> _Shift[1], this -> _Shift[2], this -> _Ang_Roll_deg, this -> _Ang_Pitch_deg, this -> _Ang_Yaw_deg, this -> _Position_m[0], this -> _Position_m[1], this -> _Position_m[2]);
    string result(buffer, length);
    string message = result;
    // Ta instrukcja to tylko uproszczony przyk³ad
    // cout << objectPointer->movingState;
    return message; // Tu musi zostaæ wywo³anie odpowiedniej                  // metody/funkcji geruj¹cej polecenia dla serwera
  }
  /*!
   * \brief Udostêpia wartoœæ k¹ta \e roll.
   *
   * Udostêpia wartoœæ k¹ta \e roll. Jest ona wyra¿ona w stopniach.
   */
  double GetAng_Roll_deg() const {
    return _Ang_Roll_deg;
  }
  /*!
   * \brief Udostêpia wartoœæ k¹ta \e pitch.
   *
   * Udostêpia wartoœæ k¹ta \e pitch. Jest ona wyra¿ona w stopniach.
   */
  double GetAng_Pitch_deg() const {
    return _Ang_Pitch_deg;
  }
  /*!
   * \brief Udostêpia wartoœæ k¹ta \e yaw.
   *
   * Udostêpia wartoœæ k¹ta \e yaw. Jest ona wyra¿ona w stopniach.
   */
  double GetAng_Yaw_deg() const {
    return _Ang_Yaw_deg;
  }

  /*!
   * \brief Zmienia wartoœæ k¹ta \e roll.
   *
   * Zmienia wartoœæ k¹ta \e roll.
   * \param[in] Ang_Roll_deg - nowa wartoœæ k¹ta \e roll wyra¿ona w stopniach.
   */
  void SetAng_Roll_deg(double Ang_Roll_deg) {
    _Ang_Roll_deg = Ang_Roll_deg;
  }
  /*!
   * \brief Zmienia wartoœæ k¹ta \e pitch.
   *
   * Zmienia wartoœæ k¹ta \e pitch.
   * \param[in] Ang_Pitch_deg - nowa wartoœæ k¹ta \e pitch wyra¿ona w stopniach.
   */
  void SetAng_Pitch_deg(double Ang_Pitch_deg) {
    _Ang_Pitch_deg = Ang_Pitch_deg;
  }
  /*!
   * \brief Zmienia wartoœæ k¹ta \e yaw.
   *
   * Zmienia wartoœæ k¹ta \e yaw.
   * \param[in] Ang_Yaw_deg - nowa wartoœæ k¹ta \e yaw wyra¿ona w stopniach.
   */
  void SetAng_Yaw_deg(double Ang_Yaw_deg) {
    _Ang_Yaw_deg = Ang_Yaw_deg;
  }

  /*!
   * \brief Udostêpnia wspó³rzêdne po³o¿enia obiektu w trybie tylko do odczytu.
   *
   * Udostêpnia wspó³rzêdne punktu, który definiuje po³o¿enia obiektu
   * w trybie tylko do odczytu.
   * Domyœlnie przyjmuje siê, ¿e jest to geometryczny œrodek bry³y.
   */
  const Vector3D & GetPositoin_m() const {
    return _Position_m;
  }
  /*!
   * \brief Udostêpnia wspó³rzêdne po³o¿enia obiektu w trybie modyfikacji.
   *
   * Udostêpnia wspó³rzêdne punktu, który definiuje po³o¿enia obiektu
   * w trybie modyfikacji.
   * Domyœlnie przyjmuje siê, ¿e jest to geometryczny œrodek bry³y.
   */
  Vector3D & UsePosition_m() {
    return _Position_m;
  }
  /*!
   * \brief Zmienia wspó³rzêdne po³o¿enia obiektu.
   *
   * Zmienia wspó³rzêdne punktu, który definiuje po³o¿enia obiektu.
   * Domyœlnie przyjmuje siê, ¿e jest to geometryczny œrodek bry³y.
   * \param[in] rPos_m - wspó³rzêdne nowgo po³o¿enia. Przyjmuje siê,
   *                     ¿e s¹ one wyra¿one w metrach.
   */
  void SetPosition_m(const Vector3D & rPos_m) {
    _Position_m = rPos_m;
  }

  /*!
   * \brief Zmienia nazwê obiektu.
   *
   *  Zmienia nazwê obiektu.
   *  \param[in] sName - nowa nazwa obiektu.
   */
  void SetName(const char * sName) {
    _Name = sName;
  }
  /*!
   * \brief Udostêpnia nazwê obiektu.
   *
   * Udostêpnia nazwê obiektu w trybie tylko do odczytu.
   */
  const string & GetName() const {
    return _Name;
  }

  /*!
   * \brief Zmienia wielkoœæ obiektu
   *
   * \param[in] Scale - wektor3D z wartoœciami skali XYZ
   */
  void SetScale(const Vector3D & Scale) {
    _Scale = Scale;
  }

  /*!
   * \brief Zmienia kolor obiektu.
   *
   * \param[in] RGB - kolor w postaci RGB
   */
  void setColor(const string RGB) {
    istringstream IStrm;
    IStrm.str(RGB);
    IStrm >> this -> color[0] >> this -> color[1] >> this -> color[2];
  }

  void setShift(const Vector3D & Shift) {
    _Shift = Shift;
  }
};

#endif
