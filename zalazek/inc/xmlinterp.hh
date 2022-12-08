#ifndef XMLINTERP4ACTIONS_HH
#define XMLINTERP4ACTIONS_HH

#include <string>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/Locator.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

#include "Configuration.hh"


/*!
 * \brief Implementuje reakcje na napotkane elementu opisu akcji
 *
 * Klasa zawiera zestaw metod, które wywo³ywane s¹ w trakcie czytania i analizy
 * pliku XML.
 */
class XMLInterp4Config: public xercesc::DefaultHandler {
  public: Configuration & config;
  /*!
   * \brief Inicjalizuje obiekt i kojarzy go z list¹ poleceñ robota
   */
  XMLInterp4Config(Configuration & rConfig);

  /*!
   * \brief Wywo³ywana jest na pocz¹tku dokumentu
   */
  virtual void startDocument() override;
  /*!
   * \brief Wywo³ywana jest na koñcu dokumentu
   */
  virtual void endDocument() override;

  /*!
   * \brief Wywo³ywana jest po napotkaniu nowego elementu XML
   */
  virtual void startElement(
    const XMLCh *
      const pURI,
        const XMLCh *
          const pLocalName,
            const XMLCh *
              const pQNname,
                const xercesc::Attributes & rAttrs
  ) override;

  /*!
   * \brief Wywo³ywana jest po dojœciu do koñca elementu XML
   */
  virtual void endElement(
    const XMLCh *
      const pURI,
        const XMLCh *
          const pLocalName,
            const XMLCh *
              const pQNname
  ) override;
  /*!
   * \brief Wywo³ywana jest gdy napotkany zostanie b³¹d fatalny
   */
  void fatalError(const xercesc::SAXParseException & );
  /*!
   * \brief Wywo³ywana jest gdy napotkany zostanie b³¹d
   */
  void error(const xercesc::SAXParseException & );
  /*!
   * \brief Wywo³ywana jest gdy parser sygnalizuje ostrze¿enie
   */
  void warning(const xercesc::SAXParseException & );

  /*!
   * \brief Wykonuje operacje zwi¹zane z danym elementem XML
   */
  void WhenStartElement(const std::string & rElemName,
    const xercesc::Attributes & rAttrs);
  /*!
   * \brief Analizuje atrybuty i  odpwiednio je interpretuje
   */
  void ProcessLibAttrs(const xercesc::Attributes & rAttrs);
  /*!
   * \brief Analizuje atrybuty i odpwiednio je interpretuje
   */
  void ProcessCubeAttrs(const xercesc::Attributes & rAttrs);
  private:

};

bool ReadFile(const char * filename, Configuration & config);
#endif
