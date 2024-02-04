#include "XMLReader.h"
#include <expat.h>
#include "queue"

struct CXMLReader::SImplementation {
    std::shared_ptr< CDataSource > DDataSource;
    XML_Parser DXMLParser;
    std::queue<SXMLEntity> DEntityQueue;
}

void StartElementHandler(const std::string &name, const std::vector<std::string> &attrs) {
    SXMLEntity TempEntity;
    TempEntity.DNameData = name;
    TempEntity.DType = SXMLEntity::EType::StartElement;
    for(size_t Index = 0, Index < attrs.size(); Index += 2) { //to add values in as pairs
        TempEntity.SetAttribute(attrs[Index], attrs[Index + 1]);
    }
    DEntityQueue.push(TempEntity);
}
void EndElementHandler(const std::string &name) {
    
}

void CharacterDataHandler(const std::string &cdata) {

}

static void StartElementHandlerCallback(void *context, const XML_Char *name, const XML_Char **atts) {
    SImplementation *ReaderObject = static_cast<SImplementation *>(context);
    std::vector<std::string> Attributes;
    auto AttrPtr = atts;
    while(*AttrPtr) {
        Attributes.push_back(*AttrPtr);
        AttrPtr++;
    }
    ReaderObject -> StartElementHandler(name, Attributes);
}


static void EndElementHandlerCallback(void *context, const XML_Char *name) {
    SImplementation *ReaderObject = static_cast<SImplementation *>(context);
    ReaderObject->EndElementHandler(name);
}

static void CharacterDataHandlerCallback (void *context, const XML_Char *s, int len) {
    SImplementation *ReaderObject = static_cast<SImplementation*>(context);
    ReaderObject -> CharacterDataHandler(std::string(s, len));
}

SImplementation(std::shared_ptr< CDataSource > src) {
    DDataSource = src; 
    DXMLParser = XML_ParserCreate(NULL);
    XML_SetStartElementHandler(DXMLParser, StartElementHandlerCallback);
    XML_SetEndElementHandler(DXMLParser, EndElementHandlerCallback);
    XML_SetCharacterDataHandler(DXMLParser, CharacterDataHandlerCallback);
    XML_SetUserData(DXMLParser, this);
}

bool End() const {

}

bool ReadEntity(SXMLEntity &entity, bool skipcdata) {
    //read from source, pass to parser, return the entity
    std::vector<char>DataBuffer;
    while(DEntityQueue.empty()) {
        if (DDataSource ->Read(DataBuffer, 512)) {
            XML_Parse(DXMLParser, DataBuffer.data(), DataBuffer.size(), DataBuffer.size() < 512) {

            }
        }
        else {
            XML_Parse(DXMLParser, Databuffer.data(), 0, true);
        }
    }
    if(DEntityQueue.empty()) {
        return false;
    }
    entity = DEntityQueue.front();
    DEntityQueue.pop();
    return true;

};