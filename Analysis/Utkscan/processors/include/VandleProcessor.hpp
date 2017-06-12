/** \file VandleProcessor.hpp
 * \brief A class to handle VANDLE bars
 *
 *Processes information from the VANDLE Bars, allows for
 *beta-gamma-neutron correlations. The prototype for this
 *code was written by M. Madurga.
 *
 * Currently, the code is set to recognize two types of starts: LeRIBSS style
 * and the new Double Beta starts (SiPMT implementation). I have currently
 * coded things to be mutually exclusive. If there are Double Beta Starts then
 * the code will not analyze the LeRIBSS style starts. This is to alleviate a
 * potential confusion when it comes to the histogramming. This problem will be
 * resolved at a later date. -SVP 12/17/2014
 *
 *\author S. V. Paulauskas
 *\date 26 July 2010
 */
#ifndef __VANDLEPROCESSOR_HPP_
#define __VANDLEPROCESSOR_HPP_

#include "BarDetector.hpp"
#include "EventProcessor.hpp"
#include "HighResTimingData.hpp"

#include "TFile.h"
#include "TTree.h"
#include "TVector.h"

/// Class to process VANDLE related events
class VandleProcessor : public EventProcessor {
public:
    /** Default Constructor */
    VandleProcessor();
    /** Default Destructor */
    ~VandleProcessor() {
      TFile_ornl16->Write();
      TFile_ornl16->Close();
    };
    /** Declare the plots used in the analysis */
    virtual void DeclarePlots(void);

    /** Constructor taking a list of detector types as an argument
     * \param [in] typeList : the list of bar types that are in the analysis
     * \param [in] res : The resolution of the DAMM histograms
     * \param [in] offset : The offset of the DAMM histograms
     * \param [in] numStarts : number of starts we have to process */
    VandleProcessor(const std::vector<std::string> &typeList,
                    const double &res, const double &offset,
                    const unsigned int &numStarts);

    /** Preprocess the VANDLE data
     * \param [in] event : the event to preprocess
     * \return true if successful */
    virtual bool PreProcess(RawEvent &event);

    /** Process the event for VANDLE stuff
    * \param [in] event : the event to process
    * \return Returns true if the processing was successful */
    virtual bool Process(RawEvent &event);

    /** \brief Correct the time of flight based on the geometry of the setup
     * \param [in] TOF : The time of flight to correct
     * \param [in] corRadius : the corrected radius for the flight path
     * \param [in] z0 : perpendicular distance from the source to bar
     * \return True if the retrieval was successful. */
    virtual double CorrectTOF(const double &TOF, const double &corRadius,
                              const double &z0) {
        return((z0/corRadius)*TOF);
    }

    /** \return the map of the build VANDLE bars */
    BarMap GetBars(void) {return(bars_);}
    /** \return true if we requested small bars in the xml */
    bool GetHasSmall(void) {return(hasSmall_);}
    /** \return true if we requested medium bars in the xml  */
    bool GetHasMed(void) {return(hasMed_);}
    /** \return true if we requsted large bars in the xml */
    bool GetHasBig(void) {return(hasBig_);}


    /** \root TTree */
    TFile* TFile_ornl16;
    TTree* TTree_ornl16;

    unsigned int evtNumber=0;
    double vandle_QDC=0;
    double vandle_TOF=0;
    double vandle_lSnR=0;
    double vandle_rSnR=0;
    double vandle_lAmp=0;
    double vandle_rAmp=0;
    double vandle_lMaxAmpPos=0;
    double vandle_rMaxAmpPos=0;
    double vandle_lAveBaseline=0;
    double vandle_rAveBaseline=0;
    unsigned int vandle_barNum=0;
    double vandle_TAvg=0;
    double vandle_Corrected_TAvg=0;
    double vandle_TDiff=0;
    double vandle_Corrected_TDiff=0;
    std::vector<unsigned int> vandle_ltrace;
    std::vector<unsigned int> vandle_rtrace;

    double beta_QDC=0;
    double beta_lSnR=0;
    double beta_rSnR=0;
    double beta_lAmp=0;
    double beta_rAmp=0;
    double beta_lMaxAmpPos=0;
    double beta_rMaxAmpPos=0;
    double beta_lAveBaseline=0;
    double beta_rAveBaseline=0;
    unsigned int beta_barNum=0;
    double beta_TAvg=0;
    double beta_Corrected_TAvg=0;
    double beta_TDiff=0;
    double beta_Corrected_TDiff=0;
    std::vector<unsigned int> beta_ltrace;
    std::vector<unsigned int> beta_rtrace;


protected:
    BarMap bars_;//!< A map to hold all the bars
    TimingMap starts_;//!< A map to to hold all the starts
    BarMap barStarts_;//!< A map that holds all of the bar starts
    DetectorSummary *geSummary_;//!< The Detector Summary for Ge Events

    bool hasDecay_; //!< True if there was a correlated beta decay
    double decayTime_; //!< the time of the decay

    double plotMult_;//!< The resolution multiplier for DAMM histograms
    double plotOffset_;//!< The offset multiplier for DAMM histograms

    bool hasSmall_; //!< True if small bars were requested in the Config
    bool hasBig_; //!< True if big bars were requested in the Config
    bool hasMed_; //!< True if medium bars were requested in the Config

    double qdcComp_;

    unsigned int numStarts_; //!< The number of starts set in the Config File
private:
    /** Analyze the data for scenarios with Bar Starts; e.g. Double Beta
     * detectors */
    void AnalyzeBarStarts(void);
    /** Analyze the data for scenarios with Single sided Starts; e.g. LeRIBSS
     * beta scintillators. */
    void AnalyzeStarts(void);
    /** Clear the maps in anticipation for the next event */
    void ClearMaps(void);
    /** Fill up the basic histograms */
    void FillVandleOnlyHists();

    /** \return Returns the appropriate offset based off the VANDLE bar type
     * \param [in] type : The type of bar that we are dealing with */
    std::pair<unsigned int ,unsigned int >ReturnOffset(const std::string &type);
};
#endif
