#ifndef OSPLOTTER_H
#define OSPLOTTER_H



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <TTree.h>
#include <vector>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TFitResult.h>
#include <TF1.h>


class OSPlotter
{
private:     
    std::string Input_FileName; 
    TFile *Input_File; 
    
    //std::vector<std::string> GlobalXAxisLabels;      
    //std::vector<std::string> GlobalYAxisLabels; 
    
    
public: 
    
    OSPlotter(); 
    OSPlotter(std::string FileName);
    
    // Classic 1D Histogramm with X axis sorted by occurrence of the Label(combinations). Not suitable for Thresholds, only std::strings. 
    void PlotLabelHistogramm(std::string TreeName, std::string BranchName, unsigned MinEntries);
    void PlotLabelCombiHistogramm(std::string TreeName, std::string BranchName1, std::string BranchName2, unsigned MinEntries);
    
    // Compare Different 
    void PlotLabelHistogrammComparison(std::string TreeNameXAxis, std::string TreeNameComp1, std::string TreeNameComp2, std::string BranchName, unsigned MinEntries); 
    void PlotLabelHistogrammComparison(std::string TreeNameXAxis, std::string TreeNameComp1, std::string TreeNameComp2, std::string TreeNameComp3, std::string BranchName, unsigned MinEntries);
    
    // Create Stacks of Histogramms e.g. composition of Active or Passive Tree. 
    void PlotLabelHistogrammStack(std::string TreeNameXAxis, std::string TreeNameStack1, std::string TreeNameStack2, std::string BranchName, unsigned MinEntries); 
    void PlotLabelHistogrammStackNormalized(std::string TreeNameXAxis, std::string TreeNameStack1, std::string TreeNameStack2, std::string BranchName, unsigned MinEntries); 
    void PlotLabelHistogrammStack(std::string TreeNameXAxis, std::string TreeNameStack1, std::string TreeNameStack2, std::string TreeNameStack3, std::string BranchName, unsigned MinEntries); 
    
    
    // 2D Histogramms
    void PlotLabelHistogramm2D(std::string TreeNameX, std::string BranchNameX, unsigned MinEntriesX, std::string TreeNameY, std::string BranchNameY, unsigned MinEntriesY, bool MergeAxisLabels); 
    void PlotLabelHistogramm2D(std::string TreeName, std::string BranchNameX, unsigned MinEntriesX, std::string BranchNameY, unsigned MinEntriesY); 
    
    std::vector<std::string> SortAxisLabels(std::vector<std::string> AxisLabelOrg, std::vector<unsigned> Label_OccurrenceOrg);
    std::vector<std::string> SortAxisLabels(std::vector<std::string> AxisLabelOrg, std::vector<unsigned> Label_OccurrenceOrg, unsigned MinimumOccurrence);
    std::vector<std::string> SortAxisLabels(std::vector<std::string> AxisLabelOrg1, std::vector<unsigned> Label_OccurrenceOrg1, std::vector<std::string> AxisLabelOrg2, std::vector<unsigned> Label_OccurrenceOrg2, unsigned MinimumOccurrence);
    std::vector<std::string> SortAxisLabels(const std::map<std::string, unsigned int>& AxisLabelOrig, unsigned MinimumOccurrence);

}; 


#endif





