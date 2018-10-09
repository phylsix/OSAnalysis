#ifndef OSOVERLAP_H
#define OSOVERLAP_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <TTree.h>
#include <vector>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>


class OSOverlap 
{
private: 
    
    TFile *InputFile_Active; 
    TFile *InputFile_Passive; 
    TFile *OutputFile; 
    
    TTree *InputTree_Active; 
    TTree *InputTree_Passive; 
 
    
    unsigned Entries_Active; 
    unsigned Entries_Passive; 
    std::vector<unsigned> Counterpart; 
    std::vector<std::string> Sort_Active;          // 1: On both lists, 2: Only on Active, 3: Sorted out by filter
    std::vector<std::string> Sort_Passive;         // 1: On both lists, 2: Only on Passive, 3: Sorted out by filter; 
    
    std::string *Workflow_Active; 
    std::vector<std::string> *ExitCode1_Active;                     // Entry in the Tree
    std::vector<std::string> *ExitCode2_Active;                     // Entry in the Tree
    std::vector<std::string> *Keyword_Active;                        // Entry in the Tree
    std::vector<std::string> *ActionOS_Active;                       // Entry in the Tree
    std::vector<float> *ThresholdPerc_Active;                  // Entry in the Tree
    std::vector<int> *ThresholdAbs_Active;                     // Entry in the Tree
    std::vector<std::string> *ExitCode1Extra_Active;                // Entry in the Tree
    std::vector<std::string> *ActionWTC_Active;                     // Entry in the Tree
    std::vector<std::string> *ReasonWTC_Active;                     // Entry in the Tree
    
    TBranch *b_Workflow_Active; 
    TBranch *b_ExitCode1_Active;                     // Entry in the Tree
    TBranch *b_ExitCode2_Active;                     // Entry in the Tree
    TBranch *b_Keyword_Active;                        // Entry in the Tree
    TBranch *b_ActionOS_Active;                       // Entry in the Tree
    TBranch *b_ThresholdPerc_Active;                  // Entry in the Tree
    TBranch *b_ThresholdAbs_Active;                     // Entry in the Tree
    TBranch *b_ExitCode1Extra_Active;                // Entry in the Tree
    TBranch *b_ActionWTC_Active;                     // Entry in the Tree
    TBranch *b_ReasonWTC_Active;                     // Entry in the Tree
        
    
    std::string *Workflow_Passive; 
    std::vector<std::string> *ExitCode1_Passive;                     // Entry in the Tree
    std::vector<std::string> *ExitCode2_Passive;                     // Entry in the Tree
    std::vector<std::string> *Keyword_Passive;                        // Entry in the Tree
    std::vector<std::string> *ActionOS_Passive;                       // Entry in the Tree
    std::vector<float> *ThresholdPerc_Passive;                  // Entry in the Tree
    std::vector<int> *ThresholdAbs_Passive;                     // Entry in the Tree
    std::vector<std::string> *ExitCode1Extra_Passive;                // Entry in the Tree
    std::vector<std::string> *ActionWTC_Passive;                     // Entry in the Tree
    std::vector<std::string> *ReasonWTC_Passive;                     // Entry in the Tree
    
    TBranch *b_Workflow_Passive; 
    TBranch *b_ExitCode1_Passive;                     // Entry in the Tree
    TBranch *b_ExitCode2_Passive;                     // Entry in the Tree
    TBranch *b_Keyword_Passive;                        // Entry in the Tree
    TBranch *b_ActionOS_Passive;                       // Entry in the Tree
    TBranch *b_ThresholdPerc_Passive;                  // Entry in the Tree
    TBranch *b_ThresholdAbs_Passive;                     // Entry in the Tree
    TBranch *b_ExitCode1Extra_Passive;                // Entry in the Tree
    TBranch *b_ActionWTC_Passive;                     // Entry in the Tree
    TBranch *b_ReasonWTC_Passive;                     // Entry in the Tree
    
    
    // Output stuff: 
    TTree *OutputTree_OnBothActive; 
    TTree *OutputTree_OnBothPassive; 
    TTree *OutputTree_OnlyActive; 
    TTree *OutputTree_OnlyPassive; 
    TTree *OutputTree_SortedOutActive; 
    TTree *OutputTree_SortedOutPassive; 
    
    std::string Workflow_Sorted; 
    std::vector<std::string> ExitCode1_Sorted;                     // Entry in the Tree
    std::vector<std::string> ExitCode2_Sorted;                     // Entry in the Tree
    std::vector<std::string> Keyword_Sorted;                        // Entry in the Tree
    std::vector<std::string> ActionOS_Sorted;                       // Entry in the Tree
    std::vector<float> ThresholdPerc_Sorted;                  // Entry in the Tree
    std::vector<int> ThresholdAbs_Sorted;                     // Entry in the Tree
    std::vector<std::string> ExitCode1Extra_Sorted;                // Entry in the Tree
    std::vector<std::string> ActionWTC_Sorted;                     // Entry in the Tree
    std::vector<std::string> ReasonWTC_Sorted;                     // Entry in the Tree
    
    
    
    std::string FilterName;
    
    
    
    
    
    
    
public:     
    
    // Both in the same Input File
    OSOverlap(std::string Input, std::string Active_TreeName, std::string Passive_TreeName, std::string OutputName);
    // ~OSOverlap();
    // In different Input Files
    // OSOverlap(std::string Active_Input, std::string Active_TreeName, std::string Passive_Input, std::string Passive_TreeName); 

    void ApplySameExitCodeFilter(bool withExitCode1Extra); 
    void ApplyWorkflowIssueFilter(); 
    void ApplySiteIssueFilter(); 
    
    // Only keep Workflows with this ExitCode (can only be used once because next iteration would overwrite the labels): 
    void ApplyExitCodeFilter(std::string ExitCode1_Input, bool withExitCode1Extra);
    void ApplyExitCodeFilter(std::string ExitCode1_Input1, std::string ExitCode1_Input2, bool withExitCode1Extra);
    void FilterMultipleEntries();
    // Remove Workflows with this ExitCode: 
    void RemoveExitCode(std::string ExitCode1_Input, bool withExitCode1Extra); 
    
    // Threshold Filters: 
    void SetThresholdPercMin(float MinFailed); 
    void SetThresholdPercMin(float MinFailed, std::string ExitCode1_Input); 
    void SetThresholdPercMin(float MinFailed, std::string ExitCode1_Input1, std::string ExitCode1_Input2); 
    void FillOutputTrees();
}; 

#endif

