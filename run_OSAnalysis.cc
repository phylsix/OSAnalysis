#include <iostream>
#include <fstream>
#include <sstream>
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
#include <TStyle.h>
#include <TFitResult.h>
#include <TF1.h>

#include "OSTreeV2.h"
#include "OSOverlap.h"
#include "OSPlotter.h"
#include "OSTreeV2.cc"
#include "OSOverlap.cc"
#include "OSPlotter.cc"


void run_OSAnalysis()
{
    
    gStyle->SetOptStat(0); 
    
    bool CreateTrees = false; 
    bool SortTrees = true; 
    bool PlotBranches = true; 
    bool PlotExamples = false; 
    
    
    
    // Read the data in and create TTrees from it
    
    if(CreateTrees){
    
        TFile *f1 = new TFile("OSTrees_Test.root", "Recreate"); 
        
        OSTreeV2 ActiveTree("ActiveTree", "Active List Tree");  
        ActiveTree.AddWorkflows("Lists/Workflows_Active.txt"); 
        ActiveTree.AddExitCode1("Lists/ExitCode1_Active.txt"); 
        ActiveTree.AddKeyword("Lists/Keyword_Active.txt"); 
        ActiveTree.AddActionOS("Lists/Action_Active.txt"); 
        ActiveTree.AddThresholdPerc("Lists/Threshold_Percent_Active.txt"); 
        ActiveTree.AddThresholdAbs("Lists/Threshold_Absolute_Active.txt"); 
        ActiveTree.FillTree(); 
        
        
        OSTreeV2 PassiveTree("PassiveTree", "Passive List Tree");  
        PassiveTree.AddWorkflows("Lists/Workflows_Passive.txt"); // For the passive List there is no real "ExitCode2" there are the two most common ExitCode1 values 
        PassiveTree.AddExitCode1("Lists/ExitCode1_Passive.txt"); 
        PassiveTree.AddExitCode1Extra("Lists/ExitCode1Extra_Passive.txt");
        PassiveTree.AddActionWTC("Lists/Action_Passive.txt"); 
        PassiveTree.AddReasonWTC("Lists/Reasons_Passive.txt"); 
        PassiveTree.FillTree();
        
        f1->Close();
    }
    
    
    
    if(SortTrees){
        // Apply Filters to the Trees and look for Overlap between them. 
        // Different Filter options can be implemented in OSOverlap.cc
        // The Filters can be applied consecutively, before "FillOutputTrees()"
        
        /*OSOverlap Analysis1("OSTrees_Test.root", "ActiveTree", "PassiveTree", "Output_WorkflowIssues_SameExitCode.root"); 
        Analysis1.ApplySameExitCodeFilter(true); 
        Analysis1.ApplyWorkflowIssueFilter(); 
        //Analysis1.ApplySiteIssueFilter(); 
        Analysis1.FillOutputTrees(); 
        */
        
        // OSOverlap Analysis2("OSTrees_Test.root", "ActiveTree", "PassiveTree", "Output_RmExitCode.root"); 
        //Analysis2.ApplySameExitCodeFilter(true); 
        //Analysis2.ApplyWorkflowIssueFilter(); 
        //Analysis2.ApplySiteIssueFilter(); 
        
        
        // Analysis2.RemoveExitCode("73", false); 
        // Analysis2.RemoveExitCode("50660", false);
        // Analysis2.RemoveExitCode("60450", false); 
        // Analysis2.RemoveExitCode("99393", false); 
        // Analysis2.FillOutputTrees();

        // OSOverlap Analysis3 = OSOverlap("OSTrees_Test.root", "ActiveTree", "PassiveTree", "Output_Test.root");
        // Analysis3.FillOutputTrees();
        
        // OSOverlap Analysis4("OSTrees_Test.root", "ActiveTree", "PassiveTree", "Output_workflowIssues.root");
        // Analysis4.ApplyWorkflowIssueFilter();
        // Analysis4.FillOutputTrees();

        OSOverlap Analysis5("OSTrees_Test.root", "ActiveTree", "PassiveTree", "Output_siteIssues.root");
        Analysis5.ApplySiteIssueFilter();
        Analysis5.FillOutputTrees();
    }
    
    
    if(PlotBranches){
        
        if(PlotExamples){
            
            // Examples for the different types of plotting functions 
            OSPlotter Paintbrush_Example("Output_Test.root"); 
            
            // Standard: TreeName, BranchName, Number of minimum Entries: 
            // Examples for the different Plotting Functions: 
            
            // A plain Histogramm of the ExitCode1 distribution for the Active Tree
            Paintbrush_Example.PlotLabelHistogramm("TreeOnBothActive_noFilter", "ExitCode1", 2); 
            
            // A Histogramm that shows the distribution for the differnt Combinations of ExitCode1 and Keyword
            Paintbrush_Example.PlotLabelCombiHistogramm("TreeOnBothActive_noFilter", "ExitCode1", "Keyword", 2);
            
            // A comparison between two trees. The first entry determines the Tree that is used for the x-axis Labels
            // Overloaded versions with more than two Trees to be compared will be implemented in the future. 
            Paintbrush_Example.PlotLabelHistogrammComparison("ActiveTree", "TreeOnBothActive_noFilter", "TreeOnlyActive_noFilter", "ExitCode1", 2); 
            
            // A stack plot. Nice to show the composition of something: 
            Paintbrush_Example.PlotLabelHistogrammStack("ActiveTree", "TreeOnBothActive_noFilter", "TreeOnlyActive_noFilter", "ExitCode1", 2); 
            Paintbrush_Example.PlotLabelHistogrammStackNormalized("ActiveTree", "TreeOnBothActive_noFilter", "TreeOnlyActive_noFilter", "ExitCode1", 2);             
            
            // 2D Histogramms: 
            // For cases where two different Trees are compared to each other. 
            Paintbrush_Example.PlotLabelHistogramm2D("TreeOnBothActive_noFilter", "ExitCode1", 2, "TreeOnBothPassive_noFilter", "ExitCode1", 2, false); 
            // For cases where the correlation between different branches of the same tree is plotted: 
            Paintbrush_Example.PlotLabelHistogramm2D("PassiveTree", "ExitCode1", 2, "ReasonWTC", 2); 
    
        }
    
    
    
        // OSPlotter Paintbrush_Example("Output_Test.root");
        // Paintbrush_Example.PlotLabelHistogrammStack("ActiveTree", "TreeOnlyActive_noFilter", "TreeOnBothActive_noFilter", "ExitCode1", 2); 
        // Paintbrush_Example.PlotLabelHistogrammStackNormalized("ActiveTree", "TreeOnlyActive_noFilter", "TreeOnBothActive_noFilter", "ExitCode1", 2);

        // Paintbrush_Example.PlotLabelHistogrammStack("PassiveTree", "TreeOnlyPassive_noFilter", "TreeOnBothPassive_noFilter", "ExitCode1", 2); 
        // Paintbrush_Example.PlotLabelHistogrammStackNormalized("PassiveTree", "TreeOnlyPassive_noFilter", "TreeOnBothPassive_noFilter", "ExitCode1", 2);


        // OSPlotter Paintbrush_Example("Output_workflowIssues.root");
        // Paintbrush_Example.PlotLabelHistogrammStack("ActiveTree", "TreeOnlyActive_WorkflowIssueFilter", "TreeOnBothActive_WorkflowIssueFilter", "ExitCode1", 2); 
        // Paintbrush_Example.PlotLabelHistogrammStackNormalized("ActiveTree", "TreeOnlyActive_WorkflowIssueFilter", "TreeOnBothActive_WorkflowIssueFilter", "ExitCode1", 2);     

        OSPlotter Paintbrush_Example("Output_siteIssues.root");
        Paintbrush_Example.PlotLabelHistogrammStack("ActiveTree", "TreeOnlyActive_SiteIssueFilter", "TreeOnBothActive_SiteIssueFilter", "ExitCode1", 2); 
        Paintbrush_Example.PlotLabelHistogrammStackNormalized("ActiveTree", "TreeOnlyActive_SiteIssueFilter", "TreeOnBothActive_SiteIssueFilter", "ExitCode1", 2);     

        /*
        OSPlotter Paintbrush_Workflows("Output_WorkflowIssues_SameExitCode.root"); 
        
        Paintbrush_Workflows.PlotLabelHistogrammStack("ActiveTree", "TreeOnlyActive_SameExitCodeFilter_WorkflowIssueFilter", "TreeOnBothActive_SameExitCodeFilter_WorkflowIssueFilter", "ExitCode1", 2); 
        Paintbrush_Workflows.PlotLabelHistogrammStackNormalized("ActiveTree", "TreeOnlyActive_SameExitCodeFilter_WorkflowIssueFilter", "TreeOnBothActive_SameExitCodeFilter_WorkflowIssueFilter", "ExitCode1", 2); 
    
        
        
        OSPlotter Paintbrush_Sites("Output_SiteIssues_SameExitCode.root"); 
        
        Paintbrush_Sites.PlotLabelHistogrammStack("ActiveTree", "TreeOnlyActive_SameExitCodeFilter_SiteIssueFilter", "TreeOnBothActive_SameExitCodeFilter_SiteIssueFilter", "ExitCode1", 2); 
        Paintbrush_Sites.PlotLabelHistogrammStackNormalized("ActiveTree", "TreeOnlyActive_SameExitCodeFilter_SiteIssueFilter", "TreeOnBothActive_SameExitCodeFilter_SiteIssueFilter", "ExitCode1", 2); 
        */
        
        
        
        
        
        
        
        
        
        
        
    } // End of PlotBranches

    
}// End of config