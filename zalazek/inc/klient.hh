#ifndef KLIENT_HH
#define KLIENT_HH

#include <thread>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>

#include "GuardedSocket.hh"
#include "Port.hh"
#include "Scena.hh"


using namespace std;



/*!
 * \brief Wysy³a napis do poprzez gniazdo sieciowe.
 *
 * Wysy³a napis do poprzez gniazdo sieciowe.
 * \param[in] Sk2Server - deskryptor gniazda sieciowego, poprzez które
 *                        ma zostaæ wys³any napis w sensie jêzyka C.
 * \param[in] sMesg - zawiera napis, który ma zostaæ wys³any poprzez
 *                    gniazdo sieciowe.
 */
int Send(int Sk2Server,
  const char * sMesg);

/*!
 * \brief Modeluje nadajnik poleceñ odzwierciedlaj¹cych aktualny stan sceny.
 *
 * Modeluje nadajnik poleceñ odzwierciedlaj¹cych aktualny stan sceny.
 * W tym celu monitoruje zmiany na scenie, a gdy je wykryje przesy³a
 * informacje o aktualnej pozycji wszystkich obiektów.
 */
class Sender {
  /*!
   * \brief Wartoœæ tego pola decyduje o kontynuacji wykonywania w¹tku.
   *
   * Wartoœæ tego pola decyduje o kontynuacji wykonywania w¹tku.
   * W przypadku wartoœci \p true, pêtla w¹tku bêdzie wykonywana.
   * Natomiast wartoœæ \p false powoduje przerwanie pêtli.
   */
  volatile bool _ContinueLooping = true;
  /*!
   * \brief Deskryptor gniazda sieciowego, poprzez które wysy³ane s¹ polecenia.
   */
  int _Socket = 0;
  /*!
   * \brief WskaŸnik na scenê, które stan jest przesy³any w postaci
   *        poleceñ do serwera graficzneg.
   */
  Scena * _pScn = nullptr;

  std::thread klient_thread;

  public:
    /*!
     * \brief Inicjalizuje obiekt deskryptorem gniazda i wskaŸnikiem
     *        na scenê, na zmianê stanu które bêdzie ten obiekt reagowa³.
     */
    Sender(int Socket, Scena * pScn);

  ~Sender() {
    this -> CancelCountinueLooping();
    this -> klient_thread.join();
    close(_Socket);
  }

  /*!
   * \brief Sprawdza, czy pêtla w¹tku mo¿e byæ wykonywana.
   *
   * Sprawdza, czy pêtla w¹tku mo¿e byæ wykonywana.
   * \retval true - pêtla w¹tku mo¿e byæ nadal wykonywana.
   * \retval false - w przypadku przeciwnym.
   */
  bool ShouldCountinueLooping() const {
    return _ContinueLooping;
  }
  /*!
   * \brief Powoduje przerwanie dzia³ania pêtli w¹tku.
   *
   * Powoduje przerwanie dzia³ania pêtli w¹tku.
   * \warning Reakcja na tê operacjê nie bêdize natychmiastowa.
   */
  void CancelCountinueLooping() {
    _ContinueLooping = false;
  }

  /*!
   * \brief Ta metoda jest de facto treœci¹ w¹tku komunikacyjnego
   *
   * Przegl¹da scenê i tworzy odpowiednie polecenia, a nastêpnie
   * wysy³a je do serwera.
   * \param[in] Socket - deskryptor gniazda sieciowego, poprzez które
   *                     wysy³ane s¹ polecenia.
   */
  void Watching_and_Sending() {
    while (ShouldCountinueLooping()) {
      if (!_pScn -> IsChanged()) {
        usleep(10000);
        continue;
      }
      _pScn -> LockAccess();

      //------- Przegl¹danie tej kolekcji to uproszczony przyk³ad

      //Send(_Socket,"Clear\n"); // To jest konieczne, aby usun¹æ wczeœniejsze obiekty.
      //cout << "Clear\n";
      std::map < std::string, MobileObj * > MobileObjects = _pScn -> getObjList();
      std::vector < MobileObj * > objects_list;
      std::map < std::string, MobileObj * > ::iterator Iter;

      for (Iter = MobileObjects.begin(); Iter != MobileObjects.end(); Iter++) {
        objects_list.push_back(Iter -> second);
      }

      for (MobileObj * object_ptr: objects_list) {
        //MobileObj* object = object_ptr;

        std::string message = "UpdateObj ";
        message += object_ptr -> returnParameters();
        //std::cout<<"lul"<<message<<"XDDDD"<<std::endl;
        // Ta instrukcja to tylko uproszczony przyk³ad
        // cout << objectPointer->movingState;
        Send(_Socket, message.c_str()); // Tu musi zostaæ wywo³anie odpowiedniej
        // metody/funkcji geruj¹cej polecenia dla serwera.
      }
      //Send(_Socket,"Display\n"); // To jest konieczne, aby zobaczyæ zmiany
      //cout << "Display\n";

      _pScn -> CancelChange();
      _pScn -> UnlockAccess();
    }
  }
};

/*!
 * \brief Funkcja jest treœci¹ w¹tku komunikacyjnego
 *
 * Funkcja jest treœci¹ w¹tku komunikacyjnego.
 * \param[in] rSender - odpowiada za œledenie zmian na scenie
 *                      i przesy³anie do serwera graficznego
 *                      aktualnego stanu sceny, gdy uleg³ on zmianie.
 */
void Fun_CommunicationThread(Sender * pSender);

/*!
 * Otwiera po³¹czenie sieciowe
 * \param[out]  rSocket - deskryptor gniazda, poprzez które mo¿e byæ
 *                        realizowana komunikacja sieciowa.
 */
bool OpenConnection(int & rSocket);

void close(int socket, Sender & clientSender, thread t);


#endif
