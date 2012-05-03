/** 
 * Handle QDCs for the position sensitive detector
 */

#ifndef __QDCPROCESSOR_HPP_
#define __QDCPROCESSOR_HPP_

#include <string>
#include <vector>

#include "EventProcessor.h"

class ChanEvent;

class QdcProcessor : public EventProcessor
{
private:
    static const std::string configFile;
    static const int numLocations = 16;
    static const int numQdcs = 8;
	
    float qdcLen[numQdcs]; //< the length of each qdc in pixie samples
    float totLen;          //< calculated length of all qdcs excluding baseline qdc
    int whichQdc;          //< which qdc we are using for position determination
    float posScale;        //< an arbitrary scale for the position parameter to physical units
    float minNormQdc[numLocations]; //< the minimum normalized qdc observed for a location
    float maxNormQdc[numLocations]; //< the maximum normalized qdc observed for a location

    ChanEvent* FindMatchingEdge(ChanEvent *match,
				std::vector<ChanEvent*>::const_iterator begin, 
				std::vector<ChanEvent*>::const_iterator end) const;				
public:
    QdcProcessor(); // no virtual c'tors
    virtual bool Init(DetectorDriver &driver);
    virtual bool Process(RawEvent &event);
    virtual void DeclarePlots(void) const;
};
    
#endif // __QDCPROCESSOR_HPP_