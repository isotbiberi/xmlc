#include <iostream>
#include <iomanip>
// Compile with something like (Makefile excerpt):
// g++ -g -O0 -Wall -I/usr/local/xerces/include/ $(^) -L/usr/local/xerces/lib/ -lxerces-c

#include <fstream>
#include <sstream>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>



#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>

using namespace std;
using namespace xercesc;
using namespace std;
using namespace xercesc_3_1;
int main(int argc, char* args[])
{
    
// This is where our data will go after it's pulled out of the XML file
map<string,pair<string,string> > myData;
vector<pair<string,string> > imageLine;

try {
        XMLPlatformUtils::Initialize();
    } catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Error during initialization! :\n" << message << "\n";
        XMLString::release(&message);
        return 1;
    }

    XercesDOMParser* parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoNamespaces(true); // optional

    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

    const char * xmlFile = "ObservationPlan.xml";

    try {
        parser->parse(xmlFile);
    } catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return -1;
    } catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
        cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return -1;
    } catch (...) {
        cout << "Unexpected Exception \n";
        return -1;
    }

    cout << xmlFile << ": parse OK" << endl;


   try

{
	      // no need to free this pointer - owned by the parent parser object
	      DOMDocument* xmlDoc = parser->getDocument();
	 
	      // Get the top-level element: NAme is "root". No attributes for "root"
	       
	      DOMElement* elementRoot = xmlDoc->getDocumentElement();
	      if( !elementRoot ) throw(std::runtime_error( "empty XML document" ));
	 
	      // Parse XML file for tags of interest: "ApplicationSettings"
	      // Look one level nested within "root". (child of root)
	

              DOMNodeIterator * walker;
              walker = xmlDoc->createNodeIterator(elementRoot,DOMNodeFilter::SHOW_ELEMENT,NULL,true); 

             // Some declarations
DOMNode * current_node = NULL;
string thisNodeName;
string parentNodeName;
bool wordParts[7] = {false,false,false,false,false,false,false};
string wordText = "";
pair<string,string> wordTypeValue;
    
//vector<pair<string,string> > imageLine;

for (current_node = walker->nextNode(); current_node != 0; current_node = walker->nextNode()) 
   {
    
    thisNodeName = XMLString::transcode(current_node->getNodeName());
    parentNodeName = XMLString::transcode(current_node->getParentNode()->getNodeName());
    //std::cout<<"this node name "<<thisNodeName<<" parent node name " <<parentNodeName<<std::endl;
    
   if(parentNodeName == "ImageLine" ) 

   {
    
   	//std::cout<<"imageline icindeyim"<<std::endl;

   	if(thisNodeName == "ImageLineID") {
        wordParts[0] = true;
        //std::cout<<"wordparts[0] true oldu"<<std::endl;

        wordText = XMLString::transcode(current_node->getFirstChild()->getNodeValue());
        imageLine.push_back(std::make_pair("ImageLineID",wordText));
    	} 
          else if(thisNodeName == "Time") {
        wordParts[1] = true;
        //std::cout<<"wordparts[1] true oldu"<<std::endl;
 
       wordTypeValue.first =  XMLString::transcode(current_node->getFirstChild()->getNodeValue());
       imageLine.push_back(std::make_pair("Time",wordTypeValue.first));
	
       } else if(thisNodeName == "ExposureTime") {
        wordParts[2] = true;

        wordTypeValue.second =  XMLString::transcode(current_node->getFirstChild()->getNodeValue());
        imageLine.push_back(std::make_pair("ExposureTime",wordTypeValue.second));
 
 	}
   
     else if(thisNodeName == "FrameNumber") {
        wordParts[3] = true;
    	 imageLine.push_back(std::make_pair("FrameNumber", XMLString::transcode(current_node->getFirstChild()->getNodeValue())));

        }
	else if(thisNodeName == "Gain") {
        wordParts[4] = true;
    	imageLine.push_back(std::make_pair("Gain", XMLString::transcode(current_node->getFirstChild()->getNodeValue())));

        }
	else if(thisNodeName == "Focus") {
        wordParts[5] = true;
        imageLine.push_back(std::make_pair("Focus", XMLString::transcode(current_node->getFirstChild()->getNodeValue())));

    	}
	else if(thisNodeName == "Binning") {
        wordParts[6] = true;
        imageLine.push_back(std::make_pair("Binning", XMLString::transcode(current_node->getFirstChild()->getNodeValue())));

       }



    



if(wordParts[6]&&wordParts[5] && wordParts[4] && wordParts[3]&&wordParts[2] && wordParts[1] && wordParts[0]) {
   //std::cout<<"word parts hepsi true oldu"<<std::endl; 
   myData[wordText] = wordTypeValue;
   wordParts[0] = false;
   wordParts[1] = false;
   wordParts[2] = false;
   wordParts[3] = false;
   wordParts[4] = false;
   wordParts[5] = false;
   wordParts[6] = false;



}
/*
else {
    std::cout<<"word parts hepsi true OLMADI"<<std::endl;

    // Not in a word
    wordParts[0] = false;
    wordParts[1] = false;
    wordParts[2] = false;
}
*/
}
   }//end of for loop

}

	   catch( xercesc::XMLException& e )
	   {
	      char* message = xercesc::XMLString::transcode( e.getMessage() );
	      ostringstream errBuf;
	      errBuf << "Error parsing file: " << message << flush;
	      XMLString::release( &message );
	   }






for(int i = 0; i < imageLine.size(); i++)
{
     cout << imageLine[i].first << ", " << imageLine[i].second << endl<<endl;
}



    delete parser;
    return 0;
}


