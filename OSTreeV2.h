#ifndef OSTREEV2_H
#define OSTREEV2_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <TTree.h>
#include <vector>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

//#pragma link C++ class std::vector<std::vector<int> >+; 
//#pragma link C++ class std::vector<std::vector<float> >+; 
//#pragma link C++ class std::vector<std::vector<std::string> >+;
//#pragma link C++ class vector<vector<int> >+;



class OSTreeV2
{
private: 
    TTree *OS_Analysis_Tree; 
    // Stuff for the es: 
    std::string line;                            // general tool to read the lists line-by-line
    
    // Workflows
    std::vector<std::string> Workflows;         // for reading in the lists
    std::string Workflow;                        // Entry in the Tree
    int    Occurrence;                      // How many times was this reported
    
    // std::string version (The code is used as a label, not a number. )
    bool hasExitCode1; 
    std::vector<std::string> ExitCode1_read;    // For reading in the lists
    std::vector<std::string> ExitCode1;                     // Entry in the Tree
    std::vector<int> ExitCode1_Occurrence;
    
    bool hasExitCode2; 
    std::vector<std::string> ExitCode2_read;    // For reading in the lists
    std::vector<std::string> ExitCode2;                     // Entry in the Tree
    std::vector<int> ExitCode2_Occurrence;
    
    bool hasKeyword; 
    std::vector<std::string> Keyword_read;    // For reading in the lists
    std::vector<std::string> Keyword;                     // Entry in the Tree
    std::vector<int> Keyword_Occurrence;
    
    bool hasActionOS; 
    std::vector<std::string> ActionOS_read;    // For reading in the lists
    std::vector<std::string> ActionOS;                     // Entry in the Tree
    std::vector<int> ActionOS_Occurrence;
    
    bool hasThresholdPerc; 
    std::vector<float> ThresholdPerc_read;    // For reading in the lists
    std::vector<float> ThresholdPerc;
    std::vector<int> ThresholdPerc_Occurrence;
    
    bool hasThresholdAbs; 
    std::vector<int> ThresholdAbs_read;    // For reading in the lists
    std::vector<int> ThresholdAbs;                     // Entry in the Tree
    std::vector<int> ThresholdAbs_Occurrence;
    
    bool hasExitCode1Extra; 
    std::vector<std::string> ExitCode1Extra_read;    // For reading in the lists
    std::vector<std::string> ExitCode1Extra;                     // Entry in the Tree
    std::vector<int> ExitCode1Extra_Occurrence;
    
    bool hasActionWTC; 
    std::vector<std::string> ActionWTC_read;    // For reading in the lists
    std::vector<std::string> ActionWTC;                     // Entry in the Tree
    std::vector<int> ActionWTC_Occurrence;
    
    bool hasReasonWTC; 
    std::vector<std::string> ReasonWTC_read;    // For reading in the lists
    std::vector<std::string> ReasonWTC;                     // Entry in the Tree
    std::vector<int> ReasonWTC_Occurrence;
    
    
    
    
public: 
    
    OSTreeV2(); 
    OSTreeV2(std::string TreeName, std::string TreeTitle);
    
    void AddWorkflows(std::string WorkflowsListName);
    void AddExitCode1(std::string ExitCode1ListName); 
    void AddExitCode2(std::string ExitCode2ListName); 
    void AddKeyword(std::string KeywordListName); 
    void AddActionOS(std::string ActionListName); 
    void AddThresholdPerc(std::string ThresholdPercListName);
    void AddThresholdAbs(std::string ThresholdAbsListName); 
    
    void AddExitCode1Extra(std::string ExitCode1ExtraName); 
    void AddActionWTC(std::string ActionListName); 
    void AddReasonWTC(std::string ReasonListName);
    
    
    void InitializeBranches(); 
    void FillTree(); 
    
    
}; 


#endif


















