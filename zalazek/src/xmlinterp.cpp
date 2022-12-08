#include <xercesc/util/PlatformUtils.hpp>
#include "xmlinterp.hh"
#include <cassert>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace std;

/*!
 * Konstruktor klasy. Tutaj nale¿y zainicjalizowaæ wszystkie
 * dodatkowe pola.
 */
XMLInterp4Config::XMLInterp4Config(Configuration & rConfig): config(rConfig) {}

/*!
 * Metoda wywo³ywana jest bezpoœrednio przed rozpoczêciem
 * przetwarzana dokumentu XML.
 */
void XMLInterp4Config::startDocument() {
  cout << "!!! Rozpoczecie przetwarzania dokumentu XML." << endl;
}

/*!
 * Metoda wywo³ywana jest bezpoœrednio po zakoñczeniu
 * przetwarzana dokumentu XML.
 */
void XMLInterp4Config::endDocument() {
  cout << "!!! Koniec przetwarzania dokumentu XML." << endl;
}

/*!
 * Analizuje atrybuty elementu XML \p "Lib" i odpowiednio je interpretuje.
 * \param[in] rAttrs - atrybuty elementu XML \p "Lib".
 */
void XMLInterp4Config::ProcessLibAttrs(const xercesc::Attributes & rAttrs) {
  if (rAttrs.getLength() != 1) {
    cerr << "Zla ilosc atrybutow dla \"Lib\"" << endl;
    exit(1);
  }

  char * sParamName = xercesc::XMLString::transcode(rAttrs.getQName(0));

  if (strcmp(sParamName, "Name")) {
    cerr << "Zla nazwa atrybutu dla Lib" << endl;
    exit(1);
  }

  XMLSize_t Size = 0;
  char * sLibName = xercesc::XMLString::transcode(rAttrs.getValue(Size));

  cout << "  Nazwa biblioteki: " << sLibName << endl;

  config.AddLibraryName(sLibName);

  xercesc::XMLString::release( & sParamName);
  xercesc::XMLString::release( & sLibName);
}

/*!
 * Analizuje atrybuty. Sprawdza czy ich nazwy s¹ poprawne. Jeœli tak,
 * to pobiera wartoœci atrybutów (w postaci napisów) i przekazuje ...
 * \param[in] rAttrs - atrybuty elementu XML \p "Cube".
 */
void XMLInterp4Config::ProcessCubeAttrs(const xercesc::Attributes & rAttrs) {
  if (rAttrs.getLength() < 1) {
    cerr << "Zla ilosc atrybutow dla \"Cube\"" << endl;
    exit(1);
  }

  /*
   *  Tutaj pobierane sa nazwy pierwszego i drugiego atrybuty.
   *  Sprawdzamy, czy na pewno jest to Name i Value.
   */

  char * sName_Name = xercesc::XMLString::transcode(rAttrs.getQName(0));
  char * sName_Shift = xercesc::XMLString::transcode(rAttrs.getQName(1));
  char * sName_Scale = xercesc::XMLString::transcode(rAttrs.getQName(2));
  char * sName_RotXYZ = xercesc::XMLString::transcode(rAttrs.getQName(3));
  char * sName_Trans = xercesc::XMLString::transcode(rAttrs.getQName(4));
  char * sName_RGB = xercesc::XMLString::transcode(rAttrs.getQName(5));

  XMLSize_t Index = 0;
  char * sValue_Name = xercesc::XMLString::transcode(rAttrs.getValue(Index));
  char * sValue_Shift = xercesc::XMLString::transcode(rAttrs.getValue(1));
  char * sValue_Scale = xercesc::XMLString::transcode(rAttrs.getValue(2));
  char * sValue_RotXYZ = xercesc::XMLString::transcode(rAttrs.getValue(3));
  char * sValue_Trans = xercesc::XMLString::transcode(rAttrs.getValue(4));
  char * sValue_RGB = xercesc::XMLString::transcode(rAttrs.getValue(5));

  //-----------------------------------------------------------------------------
  // Wyœwietlenie nazw atrybutów i ich "wartoœci"
  //Shift="0 -0.5 0" SizeXYZ="0.5 0.2 0.2" RotXYZ="10 20 0" Trans_m="0.2 0.3 0" RGB="0 128 255"
  cout << " Atrybuty:" << endl <<
    "     " << sName_Name << " = \"" << sValue_Name << "\"" << endl <<
    "     " << sName_Shift << " = \"" << sValue_Shift << "\"" << endl <<
    "     " << sName_Scale << " = \"" << sValue_Scale << "\"" << endl <<
    "     " << sName_RotXYZ << " = \"" << sValue_RotXYZ << "\"" << endl <<
    "     " << sName_Trans << " = \"" << sValue_Trans << "\"" << endl <<
    "     " << sName_RGB << " = \"" << sValue_RGB << "\"" << endl <<
    endl;
  //-----------------------------------------------------------------------------
  // Przyk³ad czytania wartoœci parametrów
  // Ten przyk³ad jest zrobiony "na piechotê" wykorzystuj¹c osobne zmienne.
  // Skala powinna byæ wektorem. Czytanie powinno byæ rezlizowane z wykorzysaniem
  // wektorów, np.
  //
  //
  // istringstream IStrm;
  // IStrm.str(sValue_Scale);
  // Vector3D  Scale;
  //
  // IStrm >> Scale;
  //
  istringstream IStrm, IStrm1, IStrm2, IStrm3;

  IStrm.str(sValue_Scale);
  IStrm1.str(sValue_Shift);
  IStrm2.str(sValue_Trans);
  IStrm3.str(sValue_RotXYZ);
  Vector3D Scale, Shift, Trans, RotXYZ;

  IStrm >> Scale[0] >> Scale[1] >> Scale[2];
  IStrm1 >> Shift[0] >> Shift[1] >> Shift[2];
  IStrm2 >> Trans[0] >> Trans[1] >> Trans[2];
  IStrm3 >> RotXYZ[0] >> RotXYZ[1] >> RotXYZ[2];

  if (IStrm.fail()) {
    cerr << " Blad!!!" << endl;
  } else {
    cout << " Czytanie wartosci OK!!!" << endl;
    cout << "     " << Scale[0] << "  " << Scale[1] << "  " << Scale[2] << endl;
  }

  //this->config.AddMobileObj(sValue_Name,Scale,sValue_RGB);
  this -> config.AddMobileObj(sValue_Name, Scale, sValue_RGB, Shift, RotXYZ, Trans);

  xercesc::XMLString::release( & sName_Name);
  xercesc::XMLString::release( & sName_Shift);
  xercesc::XMLString::release( & sName_Scale);
  xercesc::XMLString::release( & sValue_RotXYZ);
  xercesc::XMLString::release( & sValue_Trans);
  xercesc::XMLString::release( & sValue_RGB);
}

/*!
 * Wykonuje operacje zwi¹zane z wyst¹pieniem danego elementu XML.
 * W przypadku elementu \p "Action" bêdzie to utworzenie obiektu
 * reprezentuj¹cego odpowiedni¹ dzia³anie robota.
 * W przypadku elementu \p "Parameter" bêdzie to zapisanie parametrów
 * zwi¹zanych z danym dzia³aniem.
 * \param[in] rElemName - nazwa elementu XML.
 * \param[in] rAttrs - atrybuty napotkanego elementu XML.
 */
void XMLInterp4Config::WhenStartElement(const std::string & rElemName,
  const xercesc::Attributes & rAttrs) {
  if (rElemName == "Lib") {
    ProcessLibAttrs(rAttrs);
    return;
  }

  if (rElemName == "Cube") {
    ProcessCubeAttrs(rAttrs);
    return;
  }
}

/*!
 * Metoda jest wywo³ywana po napotkaniu nowego elementu XML, np.
 * gdy zostanie napotkany element:
   \verbatim
     <Action Name="Rotate">
   \endverbatim
 *  to poprzez parametr \e xscElemName jest dostêp do nazwy elementu
 *  tzn. \p Action,
 *  \param[in] pURI - (Uniform Resource Identifier) je¿eli nie jest on wyspecyfikowany
 *                    poprzez u¿ycie atrybutów \p xmlns (o ile jego u¿ycie jest przewidziane w gramatyce,
 *                    w tym przyk³adzie nie jest to przewidziane), to bêdzie to napis pusty.
 *  \param[in] pLocalName -  umo¿liwia dostêp do nazwy elementu XML.
 *                 W podanym przyk³adzie nazw¹ elementu XML jest "Action".
 *  \param[in] pQName - pe³na kwalifikowana nazwa. To ma znaczenie, gdy u¿yta jest przestrzeñ nazwa.
 *                      Wówczas poprzez ten parametr mo¿na otrzymaæ nazwê elementu wraz z prefiksem
 *                      przestrzeni nazwa. Jeœli przestrzeñ nazw nie jest u¿yta (taka jak w tym
 *                      przyk³adzie), to \p pQName i \p pLocalName dostaczaj¹ identyczne napisy.
 *  \param[in] rAttrs -  lista atrybutów danego symbolu XML.
 *                 W przyk³adzie pokazanym powy¿ej listê atrybutów
 *                 bêd¹ stanowi³y napisy:
 */
/*
 * Te metode nalezy odpowiednio zdekomponowac!!!
 */
void XMLInterp4Config::startElement(const XMLCh *
  const pURI,
    const XMLCh *
      const pLocalName,
        const XMLCh *
          const pQName,
            const xercesc::Attributes & rAttrs) {
  char * sElemName = xercesc::XMLString::transcode(pLocalName);
  cout << "+++ Poczatek elementu: " << sElemName << endl;

  WhenStartElement(sElemName, rAttrs);

  xercesc::XMLString::release( & sElemName);
}

/*!
 * Metoda zostaje wywo³ana w momencie zakoñczenia danego elementu
 * XML, np. je¿eli w pliku jest wpis:
   \verbatim
     <Lib Name="Rotate">
     </Lib>
   \endverbatim
 * to metoda ta zostanie wywo³ana po napotkaniu znacznika:
 * \verbatim</Lib>\endverbatim
 * Je¿eli element XML ma formê skrócon¹, tzn.
   \verbatim
     <Parametr Name="Rotate"/>
   \endverbatim
 * to wówczas wywo³ana metoda wywo³ana zostanie w momencie
 * napotkania sekwencji "/>"
 *  \param[in] pURI - (Uniform Resource Identifier) je¿eli nie jest on wyspecyfikowany
 *                    poprzez u¿ycie atrybutów \p xmlns (o ile jego u¿ycie jest przewidziane w gramatyce,
 *                    w tym przyk³adzie nie jest to przewidziane), to bêdzie to napis pusty.
 *  \param[in] pLocalName -  umo¿liwia dostêp do nazwy elementu XML.
 *                 W podanym przyk³adzie nazw¹ elementu XML jest "Lib".
 *  \param[in] pQName - pe³na kwalifikowana nazwa. To ma znaczenie, gdy u¿yta jest przestrzeñ nazwa.
 *                      Wówczas poprzez ten parametr mo¿na otrzymaæ nazwê elementu wraz z prefiksem
 *                      przestrzeni nazwa. Jeœli przestrzeñ nazw nie jest u¿yta (taka jak w tym
 *                      przyk³adzie), to \p pQName i \p pLocalName dostaczaj¹ identyczne napisy.
 *
 */
void XMLInterp4Config::endElement(const XMLCh *
  const pURI,
    const XMLCh *
      const pLocalName,
        const XMLCh *
          const pQName) {
  char * sURI = xercesc::XMLString::transcode(pURI);
  char * sElemName = xercesc::XMLString::transcode(pLocalName);
  char * sQName = xercesc::XMLString::transcode(pQName);
  cout << "   URI: " << sURI << endl;
  cout << " QName: " << sQName << endl;
  cout << "----- Koniec elementu: " << sElemName << endl;

  xercesc::XMLString::release( & sElemName);
}

/*!
 * Metoda wywo³ywana jest, gdy napotkany zostanie b³¹d fatalny,
 * np.
  \verbatim
    <Action Name="Rotate">
    </Parametr>
  \endverbatim
 * \param[in] rException - zawiera informacje dotycz¹ce b³êdu w dokumencie,
 *                         linii, kolumny itp.
 */
void XMLInterp4Config::fatalError(const xercesc::SAXParseException & rException) {
  char * sMessage = xercesc::XMLString::transcode(rException.getMessage());
  char * sSystemId = xercesc::XMLString::transcode(rException.getSystemId());

  cerr << "Blad fatalny! " << endl <<
    "    Plik:  " << sSystemId << endl <<
    "   Linia: " << rException.getLineNumber() << endl <<
    " Kolumna: " << rException.getColumnNumber() << endl <<
    " Informacja: " << sMessage <<
    endl;

  xercesc::XMLString::release( & sMessage);
  xercesc::XMLString::release( & sSystemId);
}

/*!
 * Metoda jest wywo³ywana, gdy napotkany zostanie b³¹d, który nie
 * jest traktowany jako fatalny. W ten sposób traktowane s¹ b³êdy
 * wystêpuj¹ce w opisie gramatyki dokumentu.
 * \param[in] rException - zawiera informacje dotycz¹ce b³êdu. Informacje
 *                     te to opis b³êdu oraz numer linii, w której
 *                     wyst¹pi³ b³¹d.
 */
void XMLInterp4Config::error(const xercesc::SAXParseException & rException) {
  cerr << "Blad ..." << endl;

  /*
   * Tutaj nale¿y wstawiæ odpowiedni kod. Tekst wyœwietlany powy¿ej
   * jest tylko "atrap¹".
   */
}

/*!
 * Metoda wywo³ana jest w przypadku b³êdów, które nie s¹ fatalne
 * i mog¹ byæ traktowane jako ostrze¿enia.
 * \param[in] rException - zawiera informacje dotycz¹ce b³êdu w dokumencie,
 *                         linii, kolumny itp.
 */
void XMLInterp4Config::warning(const xercesc::SAXParseException & rException) {
  cerr << "Ostrzezenie ..." << endl;

  /*
   * Tutaj nale¿y wstawiæ odpowiedni kod. Tekst wyœwietlany powy¿ej
   * jest tylko "atrap¹".
   */
}

/*!
 * Czyta z pliku opis poleceñ i dodaje je do listy komend,
 * które robot musi wykonaæ.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceñ.
 * \param CmdList - (\b we.) zarz¹dca listy poleceñ dla robota.
 * \retval true - jeœli wczytanie zosta³o zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
/*!
 * Czyta z pliku opis poleceñ i dodaje je do listy komend,
 * które robot musi wykonaæ.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceñ.
 * \param CmdList - (\b we.) zarz¹dca listy poleceñ dla robota.
 * \retval true - jeœli wczytanie zosta³o zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ReadFile(const char * filename, Configuration & config) {
  try {
    xercesc::XMLPlatformUtils::Initialize();
  } catch (const xercesc::XMLException & exception) {
    char * message = xercesc::XMLString::transcode(exception.getMessage());
    std::cerr << "Error during initialization! :\n";
    std::cerr << "Exception message is: \n" << message << "\n";
    xercesc::XMLString::release( & message);
    return false;
  }

  xercesc::SAX2XMLReader * parser = xercesc::XMLReaderFactory::createXMLReader();

  parser -> setFeature(xercesc::XMLUni::fgSAX2CoreNameSpaces, true);
  parser -> setFeature(xercesc::XMLUni::fgSAX2CoreValidation, true);
  parser -> setFeature(xercesc::XMLUni::fgXercesDynamic, false);
  parser -> setFeature(xercesc::XMLUni::fgXercesSchema, true);
  parser -> setFeature(xercesc::XMLUni::fgXercesSchemaFullChecking, true);
  parser -> setFeature(xercesc::XMLUni::fgXercesValidationErrorAsFatal, true);

  xercesc::DefaultHandler * handler = new XMLInterp4Config(config);
  parser -> setContentHandler(handler);
  parser -> setErrorHandler(handler);

  try {
    bool status = parser -> loadGrammar("config/config.xsd", xercesc::Grammar::SchemaGrammarType, true);

    if (false == status) {
      std::cerr << "Plik grammar/actions.xsd, ktory zawiera opis gramatyki, nie moze zostac wczytany." << std::endl;
      return false;
    }

    parser -> setFeature(xercesc::XMLUni::fgXercesUseCachedGrammarInParse, true);
    parser -> parse(filename);
  } catch (const xercesc::XMLException & exception) {
    char * message = xercesc::XMLString::transcode(exception.getMessage());
    std::cerr << "Informacja o wyjatku: \n" << "   " << message << "\n";
    xercesc::XMLString::release( & message);
    return false;
  } catch (const xercesc::SAXParseException & exception) {
    char * message = xercesc::XMLString::transcode(exception.getMessage());
    char * file = xercesc::XMLString::transcode(exception.getSystemId());

    std::cerr << "Blad! " << std::endl <<
      "    Plik:  " << file << std::endl <<
      "   Linia: " << exception.getLineNumber() << std::endl <<
      " Kolumna: " << exception.getColumnNumber() << std::endl <<
      " Informacja: " << message <<
      std::endl;

    xercesc::XMLString::release( & message);
    xercesc::XMLString::release( & file);
    return false;
  } catch (...) {
    std::cout << "Zgloszony zostal nieoczekiwany wyjatek!\n";
    return false;
  }

  delete parser;
  delete handler;
  return true;
}
