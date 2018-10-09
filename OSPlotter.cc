#include "OSPlotter.h"
#include <algorithm>



//OSPlotter::OSPLotter() 

OSPlotter::OSPlotter(std::string FileName){
    
    Input_FileName = FileName; 
    Input_File = TFile::Open(Input_FileName.c_str(), "Update"); 
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}




void OSPlotter::PlotLabelHistogramm(std::string TreeName, std::string BranchName, unsigned MinEntries){

    // Get the stuff you need from the File: 
    std::vector<std::string> *Label(0); 
    TBranch *b_Label; 
   
    TTree *OSPlotterTree = (TTree*)Input_File->Get(TreeName.c_str()); 
    OSPlotterTree->SetBranchAddress(BranchName.c_str(), &Label, &b_Label); 
    unsigned NoEntries = OSPlotterTree->GetEntries(); 
    cout<<"Number of Entries: "<<NoEntries<<endl; 
    
    // Optimize the AxisLabels by putting the ones with most Occurrences first: 
    std::vector <std::string> AxisLabel; 
    std::vector <unsigned> Label_Occurrence; 
    bool already_exists; 
    
    
    for(unsigned i0(0); i0 < NoEntries; i0++){
        OSPlotterTree->GetEntry(i0); 
        for(unsigned i1(0); i1 < Label->size(); i1++){
            already_exists = false; 
            for(unsigned i2(0); i2 < AxisLabel.size(); i2++){
                if(Label->at(i1) == AxisLabel[i2]){
                    already_exists = true;  
                    Label_Occurrence[i2]++; 
                }
            }
            
            if(!already_exists){
                AxisLabel.push_back(Label->at(i1));
                Label_Occurrence.push_back(1); 
            }
        }
    }
    
    cout<<"Number of different Labels: "<<AxisLabel.size()<<endl; 
    
         
    std::vector<std::string> AxisLabelSorted = SortAxisLabels(AxisLabel, Label_Occurrence, MinEntries); 
    unsigned NoLabels = AxisLabelSorted.size(); 
    cout<<"Number of different Labels: "<<NoLabels<<" of originally: "<<AxisLabel.size()<<endl; 
    
    
    TH1D *h1_Label = new TH1D(Form("h1_%s_%s", TreeName.c_str(), BranchName.c_str()), Form("%s: %s", TreeName.c_str(), BranchName.c_str()), NoLabels, 0., NoLabels ); 
    
    // Adjust the Labels
    for(unsigned i0(1); i0 <= NoLabels; i0++){
        h1_Label->GetXaxis()->SetBinLabel(i0, AxisLabelSorted[i0-1].c_str());
    }
    
    // Finally fill this thing: 
    for(unsigned i0(0); i0 < NoEntries; i0++){
        OSPlotterTree->GetEntry(i0); 
        for(unsigned i1(0); i1 < Label->size(); i1++){
            h1_Label->Fill(Label->at(i1).c_str(), 1); 
        }
    }
    
    //h1_Label->Draw(); 
    h1_Label->Write(); 
    
    delete OSPlotterTree; 
    
}


void OSPlotter::PlotLabelCombiHistogramm(std::string TreeName, std::string BranchName1, std::string BranchName2, unsigned MinEntries){

    // Get the stuff you need from the File: 
    //std::string *Workflow;             // Not sure I need this yet...
    std::vector<std::string> *Label1(0); 
    TBranch *b_Label1; 
    std::vector<std::string> *Label2(0); 
    TBranch *b_Label2;
    
    
    TTree *OSPlotterTree = (TTree*)Input_File->Get(TreeName.c_str()); 
    OSPlotterTree->SetBranchAddress(BranchName1.c_str(), &Label1, &b_Label1); 
    OSPlotterTree->SetBranchAddress(BranchName2.c_str(), &Label2, &b_Label2); 
    
    unsigned NoEntries = OSPlotterTree->GetEntries(); 
    
    
    // Optimize the AxisLabels by putting the ones with most Occurrences first: 
    std::vector <std::string> AxisLabel; 
    std::vector <unsigned> Label_Occurrence; 
    bool already_exists; 
    
    std::string LabelCombi; 
    
    for(unsigned i0(0); i0 < NoEntries; i0++){
        OSPlotterTree->GetEntry(i0); 
        for(unsigned i1(0); i1 < Label1->size(); i1++){
            LabelCombi = Label1->at(i1)+", "+Label2->at(i1); 
            already_exists = false; 
            for(unsigned i2(0); i2 < AxisLabel.size(); i2++){
                if(LabelCombi == AxisLabel[i2]){
                    already_exists = true;  
                    Label_Occurrence[i2]++; 
                }
            }
            
            if(!already_exists){
                AxisLabel.push_back(LabelCombi);
                Label_Occurrence.push_back(1); 
            }
        }
    }
    
    //cout<<"Number of different Labels: "<<AxisLabel.size()<<endl; 
    
        
    std::vector<std::string> AxisLabelSorted = SortAxisLabels(AxisLabel, Label_Occurrence, MinEntries); 
    unsigned NoLabels = AxisLabelSorted.size(); 
    cout<<"Number of different Labels: "<<NoLabels<<" of originally: "<<AxisLabel.size()<<endl; 
    
   
    TH1D *h1_Label = new TH1D(Form("h1_%s_%s_%s_combi", TreeName.c_str(), BranchName1.c_str(), BranchName2.c_str()), Form("%s: %s + %s", TreeName.c_str(), BranchName1.c_str(), BranchName2.c_str()), NoLabels, 0., NoLabels ); 
    
    // Adjust the Labels
    for(unsigned i0(1); i0 <= NoLabels; i0++){
        h1_Label->GetXaxis()->SetBinLabel(i0+1, AxisLabelSorted[i0-1].c_str());
    }
    
     for(unsigned i0(0); i0 < NoEntries; i0++){
        OSPlotterTree->GetEntry(i0); 
        
        for(unsigned i1(0); i1 < Label1->size(); i1++){
            LabelCombi = Label1->at(i1)+", "+Label2->at(i1);
            h1_Label->Fill(LabelCombi.c_str(), 1); 
        }
    }
    
    //h1_Label->Draw(); 
    h1_Label->Write(); 
    
    delete OSPlotterTree; 
    
}


void OSPlotter::PlotLabelHistogrammComparison(std::string TreeNameXAxis, std::string TreeNameComp1, std::string TreeNameComp2, std::string BranchName, unsigned MinEntries){
    
    std::vector<std::string> *Label(0);
    TBranch *b_Label;
    
    // Get the tree for the axis: 
    TTree *Tree_XAxis = (TTree*)Input_File->Get(TreeNameXAxis.c_str());
    Tree_XAxis->SetBranchAddress(BranchName.c_str(), &Label, &b_Label); 
    
    //unsigned NoEntries = OSPlotterTree->GetEntries(); 
    
    
    std::vector <std::string> AxisLabel; 
    std::vector <unsigned> Label_Occurrence; 
    bool already_exists;
    
    for(unsigned i0(0); i0 < Tree_XAxis->GetEntries(); i0++){
        Tree_XAxis->GetEntry(i0); 
        for(unsigned i1(0); i1 < Label->size(); i1++){
            already_exists = false; 
            for(unsigned i2(0); i2 < AxisLabel.size(); i2++){
                if(Label->at(i1) == AxisLabel[i2]){
                    already_exists = true;  
                    Label_Occurrence[i2]++; 
                }
            }
            
            if(!already_exists){
                AxisLabel.push_back(Label->at(i1));
                Label_Occurrence.push_back(1); 
            }
        }
    }
    
    std::vector<std::string> AxisLabelSorted = SortAxisLabels(AxisLabel, Label_Occurrence, MinEntries); 
    unsigned NoLabels = AxisLabelSorted.size(); 
    cout<<"Number of different Labels: "<<NoLabels<<endl;
    
    
    
    std::vector<std::string> *LabelComp1(0);
    TBranch *b_LabelComp1;
    TTree *Tree_Comp1 = (TTree*)Input_File->Get(TreeNameComp1.c_str()); 
    Tree_Comp1->SetBranchAddress(BranchName.c_str(), &LabelComp1, &b_LabelComp1); 
    
    TH1D *h1_Comp1 = new TH1D(Form("h1_%s_%s_Comp", TreeNameComp1.c_str(), BranchName.c_str()), Form("%s %s", TreeNameComp1.c_str(), BranchName.c_str()), NoLabels, 0., NoLabels);
    h1_Comp1->SetLineColor(kBlue);
    h1_Comp1->SetLineWidth(2);
    //h1_Comp1->SetFillColor(kBlue);
    
    
    std::vector<std::string> *LabelComp2(0);
    TBranch *b_LabelComp2;
    TTree *Tree_Comp2 = (TTree*)Input_File->Get(TreeNameComp2.c_str()); 
    Tree_Comp2->SetBranchAddress(BranchName.c_str(), &LabelComp2, &b_LabelComp2); 
    
    TH1D *h1_Comp2 = new TH1D(Form("h1_%s_%s_Comp", TreeNameComp2.c_str(), BranchName.c_str()), Form("%s %s", TreeNameComp2.c_str(), BranchName.c_str()), NoLabels, 0., NoLabels);
    h1_Comp2->SetLineColor(kRed);
    h1_Comp2->SetLineWidth(2); 
    
    
    
    //Give both histogramms the same Axis
    for(unsigned i0(1); i0 <= NoLabels; i0++){
        h1_Comp1->GetXaxis()->SetBinLabel(i0, AxisLabelSorted[i0-1].c_str());
        h1_Comp2->GetXaxis()->SetBinLabel(i0, AxisLabelSorted[i0-1].c_str());
    }
    
    // Actually fill them
    for(unsigned i0(0); i0 < Tree_Comp1->GetEntries(); i0++){
        Tree_Comp1->GetEntry(i0); 
        for(unsigned i1(0); i1 < LabelComp1->size(); i1++){
            h1_Comp1->Fill(LabelComp1->at(i1).c_str(), 1); 
        }
    }
    for(unsigned i0(0); i0 < Tree_Comp2->GetEntries(); i0++){
        Tree_Comp2->GetEntry(i0); 
        for(unsigned i1(0); i1 < LabelComp2->size(); i1++){
            h1_Comp2->Fill(LabelComp2->at(i1).c_str(), 1); 
        }
    }
     
    
    TCanvas *c_Comparison = new TCanvas(Form("c_%s_%s_%s_Comp", TreeNameComp1.c_str(), TreeNameComp2.c_str(), BranchName.c_str()), Form("c_%s_%s_%s_Comp", TreeNameComp1.c_str(), TreeNameComp2.c_str(), BranchName.c_str()), 800, 500);
    TPad  *pad_Comparison = new TPad(Form("pad_%s_%s_%s_Comp", TreeNameComp1.c_str(), TreeNameComp2.c_str(), BranchName.c_str()), Form("pad_%s_%s_%s_Comp", TreeNameComp1.c_str(), TreeNameComp2.c_str(), BranchName.c_str()), 0., 0., 1., 1.); 
    pad_Comparison->Draw(); 
    pad_Comparison->cd(); 
    
    h1_Comp1->Draw("hist");
    h1_Comp2->Draw("hist same"); 
    
    TLegend *leg_Comparison = new TLegend(0.6, 0.8, 0.9, 0.9); 
    leg_Comparison->AddEntry(h1_Comp1, TreeNameComp1.c_str(), "l");
    leg_Comparison->AddEntry(h1_Comp2, TreeNameComp2.c_str(), "l");
    leg_Comparison->Draw("same"); 
    
    h1_Comp1->Write(); 
    h1_Comp2->Write(); 
    c_Comparison->Write(); 
    
}







void OSPlotter::PlotLabelHistogrammStack(std::string TreeNameXAxis, std::string TreeNameStack1, std::string TreeNameStack2, std::string BranchName, unsigned MinEntries){

    std::vector<std::string> *Label(0);
    TBranch *b_Label;
    
    // Get the tree for the axis: 
    TTree *Tree_XAxis = (TTree*)Input_File->Get(TreeNameXAxis.c_str());
    Tree_XAxis->SetBranchAddress(BranchName.c_str(), &Label, &b_Label); 
    
    //unsigned NoEntries = OSPlotterTree->GetEntries(); 
    

    std::map<std::string, unsigned int> AxisLabel{};
    for (unsigned i0(0); i0 < Tree_XAxis->GetEntries(); i0++)
    {
        Tree_XAxis->GetEntry(i0); 
        for (const auto& l : *Label)
        {
            if (AxisLabel.find(l) == AxisLabel.end())
            {
                AxisLabel[l] = 1;
            } else
            {
                AxisLabel[l]++;
            }
        }
    }
    
    std::vector<std::string> AxisLabelSorted = SortAxisLabels(AxisLabel, MinEntries); 
    unsigned NoLabels = AxisLabelSorted.size(); 
    cout<<"Number of different Labels: "<<NoLabels<<endl;
    
    
    
    std::vector<std::string> *LabelStack1(0);
    TBranch *b_LabelStack1;
    TTree *Tree_Stack1 = (TTree*)Input_File->Get(TreeNameStack1.c_str()); 
    Tree_Stack1->SetBranchAddress(BranchName.c_str(), &LabelStack1, &b_LabelStack1); 
    
    TH1D *h1_Stack1 = new TH1D(Form("h1_%s_%s_StackComp", TreeNameStack1.c_str(), BranchName.c_str()),
                               Form("%s %s", TreeNameStack1.c_str(), BranchName.c_str()), NoLabels, 0., NoLabels);
    h1_Stack1->SetLineColor(kBlue);
    h1_Stack1->SetFillColor(kBlue);
    
    
    std::vector<std::string> *LabelStack2(0);
    TBranch *b_LabelStack2;
    TTree *Tree_Stack2 = (TTree*)Input_File->Get(TreeNameStack2.c_str()); 
    Tree_Stack2->SetBranchAddress(BranchName.c_str(), &LabelStack2, &b_LabelStack2); 
    
    TH1D *h1_Stack2 = new TH1D(Form("h1_%s_%s_StackComp", TreeNameStack2.c_str(), BranchName.c_str()),
                               Form("%s %s", TreeNameStack2.c_str(), BranchName.c_str()), NoLabels, 0., NoLabels);
    h1_Stack2->SetLineColor(kRed);
    h1_Stack2->SetFillColor(kRed);
    
    THStack *st_Label = new THStack(Form("st_%s_%s_%s_Stack", TreeNameStack1.c_str(), TreeNameStack2.c_str(), BranchName.c_str()),
                                    Form("%s %s %s", TreeNameStack1.c_str(), TreeNameStack2.c_str(), BranchName.c_str())); 
    
    
    //Give both histogramms the same Axis
    for(unsigned i0(1); i0 <= NoLabels; i0++){
        h1_Stack1->GetXaxis()->SetBinLabel(i0, AxisLabelSorted[i0-1].c_str());
        h1_Stack2->GetXaxis()->SetBinLabel(i0, AxisLabelSorted[i0-1].c_str());
    }
    // Actually fill them
    for(unsigned i0(0); i0 < Tree_Stack1->GetEntries(); i0++){
        Tree_Stack1->GetEntry(i0); 
        for(unsigned i1(0); i1 < LabelStack1->size(); i1++){
            if (std::find(AxisLabelSorted.begin(), AxisLabelSorted.end(), LabelStack1->at(i1))==AxisLabelSorted.end()) {continue;}
            h1_Stack1->Fill(LabelStack1->at(i1).c_str(), 1); 
        }
    }
    for(unsigned i0(0); i0 < Tree_Stack2->GetEntries(); i0++){
        Tree_Stack2->GetEntry(i0); 
        for(unsigned i1(0); i1 < LabelStack2->size(); i1++){
            if (std::find(AxisLabelSorted.begin(), AxisLabelSorted.end(), LabelStack2->at(i1))==AxisLabelSorted.end()) {continue;}
            h1_Stack2->Fill(LabelStack2->at(i1).c_str(), 1); 
        }
    }

    st_Label->Add(h1_Stack1);
    st_Label->Add(h1_Stack2);    
    
    TCanvas *c_Stack = new TCanvas(Form("c_%s_%s_%s_Stack", TreeNameStack1.c_str(), TreeNameStack2.c_str(), BranchName.c_str()),
                                   Form("c_%s_%s_%s_Stack", TreeNameStack1.c_str(), TreeNameStack2.c_str(), BranchName.c_str()), 800, 500);
    // TPad  *pad_Stack = new TPad(Form("pad_%s_%s_%s_Stack", TreeNameStack1.c_str(), TreeNameStack2.c_str(), BranchName.c_str()),
    //                             Form("pad_%s_%s_%s_Stack", TreeNameStack1.c_str(), TreeNameStack2.c_str(), BranchName.c_str()), 0., 0., 1., 1.); 
    // pad_Stack->Draw(); 
    // pad_Stack->cd();
    c_Stack->cd();
    
    // st_Label->Draw("hist");
    st_Label->Draw(); 
    
    TLegend *leg_Stack = new TLegend(0.6, 0.8, 0.9, 0.9); 
    leg_Stack->AddEntry(h1_Stack1, TreeNameStack1.c_str(), "l");
    leg_Stack->AddEntry(h1_Stack2, TreeNameStack2.c_str(), "l");
    leg_Stack->Draw("same"); 
    
    
    h1_Stack1->Write(); 
    h1_Stack2->Write(); 
    st_Label->Write(); 
    c_Stack->Write(); 
}


void OSPlotter::PlotLabelHistogrammStackNormalized(std::string TreeNameXAxis, std::string TreeNameStack1, std::string TreeNameStack2, std::string BranchName, unsigned MinEntries){

    std::vector<std::string> *Label(0);
    TBranch *b_Label;
    
    // Get the tree for the axis: 
    TTree *Tree_XAxis = (TTree*)Input_File->Get(TreeNameXAxis.c_str());
    Tree_XAxis->SetBranchAddress(BranchName.c_str(), &Label, &b_Label); 
    
    //unsigned NoEntries = OSPlotterTree->GetEntries(); 
    
    
    std::map<std::string, unsigned int> AxisLabel{};
    for (unsigned i0(0); i0 < Tree_XAxis->GetEntries(); i0++)
    {
        Tree_XAxis->GetEntry(i0); 
        for (const auto& l : *Label)
        {
            if (AxisLabel.find(l) == AxisLabel.end())
            {
                AxisLabel[l] = 1;
            } else
            {
                AxisLabel[l]++;
            }
        }
    }
    
    std::vector<std::string> AxisLabelSorted = SortAxisLabels(AxisLabel, MinEntries); 
    unsigned NoLabels = AxisLabelSorted.size(); 
    cout<<"Number of different Labels: "<<NoLabels<<endl;
    
    
    
    std::vector<std::string> *LabelStack1(0);
    TBranch *b_LabelStack1;
    TTree *Tree_Stack1 = (TTree*)Input_File->Get(TreeNameStack1.c_str()); 
    Tree_Stack1->SetBranchAddress(BranchName.c_str(), &LabelStack1, &b_LabelStack1); 
    
    TH1D *h1_Stack1 = new TH1D(Form("h1_%s_%s_StackCompN", TreeNameStack1.c_str(), BranchName.c_str()),
                               Form("%s %s", TreeNameStack1.c_str(), BranchName.c_str()), NoLabels, 0., NoLabels);
    h1_Stack1->SetLineColor(kBlue);
    h1_Stack1->SetFillColor(kBlue);
    
    
    std::vector<std::string> *LabelStack2(0);
    TBranch *b_LabelStack2;
    TTree *Tree_Stack2 = (TTree*)Input_File->Get(TreeNameStack2.c_str()); 
    Tree_Stack2->SetBranchAddress(BranchName.c_str(), &LabelStack2, &b_LabelStack2); 
    
    TH1D *h1_Stack2 = new TH1D(Form("h1_%s_%s_StackCompN", TreeNameStack2.c_str(), BranchName.c_str()),
                               Form("%s %s", TreeNameStack2.c_str(), BranchName.c_str()), NoLabels, 0., NoLabels);
    h1_Stack2->SetLineColor(kRed);
    h1_Stack2->SetFillColor(kRed);
    
    THStack *st_Label = new THStack(Form("st_%s_%s_%s_StackNorm", TreeNameStack1.c_str(), TreeNameStack2.c_str(), BranchName.c_str()),
                                    Form("%s %s %s", TreeNameStack1.c_str(), TreeNameStack2.c_str(), BranchName.c_str())); 
    
    
    //Give both histogramms the same Axis
    for(unsigned i0(1); i0 <= NoLabels; i0++){
        h1_Stack1->GetXaxis()->SetBinLabel(i0, AxisLabelSorted[i0-1].c_str());
        h1_Stack2->GetXaxis()->SetBinLabel(i0, AxisLabelSorted[i0-1].c_str());
    }
    
    // Actually fill them
    for(unsigned i0(0); i0 < Tree_Stack1->GetEntries(); i0++){
        Tree_Stack1->GetEntry(i0); 
        for(unsigned i1(0); i1 < LabelStack1->size(); i1++){
            if (std::find(AxisLabelSorted.begin(), AxisLabelSorted.end(), LabelStack1->at(i1))==AxisLabelSorted.end()) {continue;}
            h1_Stack1->Fill(LabelStack1->at(i1).c_str(), 1); 
        }
    }
    for(unsigned i0(0); i0 < Tree_Stack2->GetEntries(); i0++){
        Tree_Stack2->GetEntry(i0); 
        for(unsigned i1(0); i1 < LabelStack2->size(); i1++){
            if (std::find(AxisLabelSorted.begin(), AxisLabelSorted.end(), LabelStack2->at(i1))==AxisLabelSorted.end()) {continue;}
            h1_Stack2->Fill(LabelStack2->at(i1).c_str(), 1); 
        }
    }
    
    
    // Normalize the entries: 
    float Stack1Content; 
    float Stack2Content; 
    for(unsigned i0(1); i0 <= NoLabels; i0++){
        Stack1Content = h1_Stack1->GetBinContent(i0); 
        Stack2Content = h1_Stack2->GetBinContent(i0); 
            
        if(Stack1Content > 0) h1_Stack1->SetBinContent(i0, Stack1Content/(Stack1Content+Stack2Content)); 
        if(Stack2Content > 0) h1_Stack2->SetBinContent(i0, Stack2Content/(Stack1Content+Stack2Content)); 
    }
    
    
    
    st_Label->Add(h1_Stack1);
    st_Label->Add(h1_Stack2);    
    
    TCanvas *c_Stack = new TCanvas(Form("c_%s_%s_%s_StackNorm", TreeNameStack1.c_str(), TreeNameStack2.c_str(), BranchName.c_str()),
                                   Form("c_%s_%s_%s_StackNorm", TreeNameStack1.c_str(), TreeNameStack2.c_str(), BranchName.c_str()), 800, 500);
    // TPad  *pad_Stack = new TPad(Form("pad_%s_%s_%s_StackNorm", TreeNameStack1.c_str(), TreeNameStack2.c_str(), BranchName.c_str()), Form("pad_%s_%s_%s_StackNorm", TreeNameStack1.c_str(), TreeNameStack2.c_str(), BranchName.c_str()), 0., 0., 1., 1.); 
    // pad_Stack->Draw(); 
    // pad_Stack->cd();
    c_Stack->cd();
    
    st_Label->Draw();  
    
    TLegend *leg_StackNorm = new TLegend(0.6, 0.8, 0.9, 0.9); 
    leg_StackNorm->AddEntry(h1_Stack1, TreeNameStack1.c_str(), "l");
    leg_StackNorm->AddEntry(h1_Stack2, TreeNameStack2.c_str(), "l");
    leg_StackNorm->Draw("same"); 
    
    
    h1_Stack1->Write(); 
    h1_Stack2->Write(); 
    st_Label->Write(); 
    c_Stack->Write(); 
}




void OSPlotter::PlotLabelHistogramm2D(std::string TreeNameX, std::string BranchNameX, unsigned MinEntriesX, std::string TreeNameY, std::string BranchNameY, unsigned MinEntriesY, bool MergeAxisLabels){

    // X-axis 
    std::string *WorkflowX; 
    TBranch *b_WorkflowX; 
    std::vector<std::string> *LabelX(0);
    TBranch *b_LabelX; 
    
    TTree *OSPlotterTreeX = (TTree*)Input_File->Get(TreeNameX.c_str()); 
    OSPlotterTreeX->SetBranchAddress("Workflows", &WorkflowX, &b_WorkflowX); 
    OSPlotterTreeX->SetBranchAddress(BranchNameX.c_str(), &LabelX, &b_LabelX); 
    unsigned NoEntriesX = OSPlotterTreeX->GetEntries(); 
    //cout<<"Number of Entries: "<<NoEntries<<endl; 
    
    // Optimize the AxisLabels by putting the ones with most Occurrences first: 
    std::vector <std::string> AxisLabelX; 
    std::vector <unsigned> Label_OccurrenceX; 
    bool already_exists; 
    
    for(unsigned i0(0); i0 < NoEntriesX; i0++){
        OSPlotterTreeX->GetEntry(i0); 
        for(unsigned i1(0); i1 < LabelX->size(); i1++){
            already_exists = false; 
            for(unsigned i2(0); i2 < AxisLabelX.size(); i2++){
                if(LabelX->at(i1) == AxisLabelX[i2]){
                    already_exists = true;  
                    Label_OccurrenceX[i2]++; 
                }
            }
            
            if(!already_exists){
                AxisLabelX.push_back(LabelX->at(i1));
                Label_OccurrenceX.push_back(1); 
            }
        }
    }
        
    
    
    
    // Same for the Y-axis
    std::string *WorkflowY; 
    TBranch *b_WorkflowY; 
    std::vector<std::string> *LabelY(0);
    TBranch *b_LabelY; 
    
    TTree *OSPlotterTreeY = (TTree*)Input_File->Get(TreeNameY.c_str()); 
    OSPlotterTreeY->SetBranchAddress("Workflows", &WorkflowY, &b_WorkflowY); 
    OSPlotterTreeY->SetBranchAddress(BranchNameY.c_str(), &LabelY, &b_LabelY); 
    unsigned NoEntriesY = OSPlotterTreeY->GetEntries(); 
    //cout<<"Number of Entries: "<<NoEntries<<endl; 
    
    // Optimize the AxisLabels by putting the ones with most Occurrences first: 
    std::vector <std::string> AxisLabelY; 
    std::vector <unsigned> Label_OccurrenceY; 
    // bool already_exists; 
    
    for(unsigned i0(0); i0 < NoEntriesY; i0++){
        OSPlotterTreeY->GetEntry(i0); 
        for(unsigned i1(0); i1 < LabelY->size(); i1++){
            already_exists = false; 
            for(unsigned i2(0); i2 < AxisLabelY.size(); i2++){
                if(LabelY->at(i1) == AxisLabelY[i2]){
                    already_exists = true;  
                    Label_OccurrenceY[i2]++; 
                }
            }
            
            if(!already_exists){
                AxisLabelY.push_back(LabelY->at(i1));
                Label_OccurrenceY.push_back(1); 
            }
        }
    }
    
    std::vector<std::string> AxisLabelSortedX; 
    std::vector<std::string> AxisLabelSortedY; 
    
    if(MergeAxisLabels){
        AxisLabelSortedX = SortAxisLabels(AxisLabelX, Label_OccurrenceX, AxisLabelY, Label_OccurrenceY, MinEntriesX); 
        unsigned NoLabelsX = AxisLabelSortedX.size(); 
        cout<<"Number of different X Labels: "<<NoLabelsX<<endl; 
        
        AxisLabelSortedY = AxisLabelSortedX; 
        unsigned NoLabelsY = AxisLabelSortedY.size(); 
        cout<<"Number of different Y Labels: "<<NoLabelsY<<endl; 
    }
    else{
        AxisLabelSortedX = SortAxisLabels(AxisLabelX, Label_OccurrenceX, MinEntriesX); 
        unsigned NoLabelsX = AxisLabelSortedX.size(); 
        cout<<"Number of different X Labels: "<<NoLabelsX<<endl; 
        
        AxisLabelSortedY = SortAxisLabels(AxisLabelY, Label_OccurrenceY, MinEntriesY); 
        unsigned NoLabelsY = AxisLabelSortedY.size(); 
        cout<<"Number of different Y Labels: "<<NoLabelsY<<endl; 
    }
    
    
    unsigned NoLabelsX = AxisLabelSortedX.size(); 
    unsigned NoLabelsY = AxisLabelSortedY.size();
    TH2D *h2_Label = new TH2D(Form("%s_%s_%s_%s", TreeNameX.c_str(), BranchNameX.c_str(), TreeNameY.c_str(), BranchNameY.c_str()),
                              Form("%s_%s_%s_%s", TreeNameX.c_str(), BranchNameX.c_str(), TreeNameY.c_str(), BranchNameY.c_str()),
                              NoLabelsX, 0., NoLabelsX, NoLabelsY, 0., NoLabelsY); 
    h2_Label->GetXaxis()->SetTitle(TreeNameX.c_str());
    h2_Label->GetYaxis()->SetTitle(TreeNameY.c_str());
    
    // Adjust the Labels: 
    for(unsigned i0(1); i0 <= NoLabelsX; i0++){
        h2_Label->GetXaxis()->SetBinLabel(i0, AxisLabelSortedX[i0-1].c_str()); 
    }
    for(unsigned i0(1); i0 <= NoLabelsY; i0++){
        h2_Label->GetYaxis()->SetBinLabel(i0, AxisLabelSortedY[i0-1].c_str()); 
    }
    
    
    // Fill the Histogramm: 
    for(unsigned i0(0); i0 < NoEntriesX; i0++){
        OSPlotterTreeX->GetEntry(i0); 
        for(unsigned i1(0); i1 < NoEntriesY; i1++){
            OSPlotterTreeY->GetEntry(i1); 
            if(*WorkflowX == *WorkflowY){
                
                for(unsigned i2(0); i2 < LabelX->size(); i2++){
                    for(unsigned i3(0); i3 < LabelY->size(); i3++){
                        h2_Label->Fill(LabelX->at(i2).c_str(), LabelY->at(i3).c_str(), 1); 
                    }
                }
            }
        }
    }
    
    
    h2_Label->Write(); 
    h2_Label->Draw("colz"); 
    
    delete OSPlotterTreeX; 
    delete OSPlotterTreeY; 
}



void OSPlotter::PlotLabelHistogramm2D(std::string TreeName, std::string BranchNameX, unsigned MinEntriesX, std::string BranchNameY, unsigned MinEntriesY){

    // X-axis  
    std::vector<std::string> *LabelX(0);
    TBranch *b_LabelX; 
    std::vector<std::string> *LabelY(0);
    TBranch *b_LabelY; 
    
    TTree *OSPlotterTree = (TTree*)Input_File->Get(TreeName.c_str()); 
    OSPlotterTree->SetBranchAddress(BranchNameX.c_str(), &LabelX, &b_LabelX); 
    OSPlotterTree->SetBranchAddress(BranchNameY.c_str(), &LabelY, &b_LabelY); 
    unsigned NoEntries = OSPlotterTree->GetEntries(); 
    //cout<<"Number of Entries: "<<NoEntries<<endl; 
    
    // Optimize the AxisLabels by putting the ones with most Occurrences first: 
    std::vector <std::string> AxisLabelX; 
    std::vector <unsigned> Label_OccurrenceX; 
    bool already_exists; 
    
    for(unsigned i0(0); i0 < NoEntries; i0++){
        OSPlotterTree->GetEntry(i0); 
        for(unsigned i1(0); i1 < LabelX->size(); i1++){
            already_exists = false; 
            for(unsigned i2(0); i2 < AxisLabelX.size(); i2++){
                if(LabelX->at(i1) == AxisLabelX[i2]){
                    already_exists = true;  
                    Label_OccurrenceX[i2]++; 
                }
            }
            
            if(!already_exists){
                AxisLabelX.push_back(LabelX->at(i1));
                Label_OccurrenceX.push_back(1); 
            }
        }
    }
        
    std::vector<std::string> AxisLabelSortedX = SortAxisLabels(AxisLabelX, Label_OccurrenceX, MinEntriesX); 
    unsigned NoLabelsX = AxisLabelSortedX.size(); 
    cout<<"Number of different X Labels: "<<NoLabelsX<<endl; 
    
    
    // Optimize the AxisLabels by putting the ones with most Occurrences first: 
    std::vector <std::string> AxisLabelY; 
    std::vector <unsigned> Label_OccurrenceY; 
    
    for(unsigned i0(0); i0 < NoEntries; i0++){
        OSPlotterTree->GetEntry(i0); 
        for(unsigned i1(0); i1 < LabelY->size(); i1++){
            already_exists = false; 
            for(unsigned i2(0); i2 < AxisLabelY.size(); i2++){
                if(LabelY->at(i1) == AxisLabelY[i2]){
                    already_exists = true;  
                    Label_OccurrenceY[i2]++; 
                }
            }
            
            if(!already_exists){
                AxisLabelY.push_back(LabelY->at(i1));
                Label_OccurrenceY.push_back(1); 
            }
        }
    }
    
    std::vector<std::string> AxisLabelSortedY = SortAxisLabels(AxisLabelY, Label_OccurrenceY, MinEntriesY); 
    unsigned NoLabelsY = AxisLabelSortedY.size(); 
    cout<<"Number of different Y Labels: "<<NoLabelsY<<endl; 
    
    
    
    
    TH2D *h2_Label = new TH2D(Form("h2_%s_%s_%s", TreeName.c_str(), BranchNameX.c_str(), BranchNameY.c_str()), Form("%s: %s - %s", TreeName.c_str(), BranchNameX.c_str(), BranchNameY.c_str()), NoLabelsX, 0., NoLabelsX, NoLabelsY, 0., NoLabelsY); 
    // Adjust the Labels: 
    for(unsigned i0(1); i0 <= NoLabelsX; i0++){
        h2_Label->GetXaxis()->SetBinLabel(i0, AxisLabelSortedX[i0-1].c_str()); 
    }
    for(unsigned i0(1); i0 <= NoLabelsY; i0++){
        h2_Label->GetYaxis()->SetBinLabel(i0, AxisLabelSortedY[i0-1].c_str()); 
    }
    
    
    // Fill the Histogramm: 
    for(unsigned i0(0); i0 < NoEntries; i0++){
        OSPlotterTree->GetEntry(i0); 
        for(unsigned i1(0); i1 < LabelX->size(); i1++){
            h2_Label->Fill(LabelX->at(i1).c_str(), LabelY->at(i1).c_str(), 1); 
        }
    }
    
    h2_Label->Draw("colz"); 
    h2_Label->Write(); 
    delete OSPlotterTree;
}







std::vector<std::string> OSPlotter::SortAxisLabels(std::vector<std::string> AxisLabelOrg, std::vector<unsigned> Label_OccurrenceOrg){
    
    std::vector<std::string> AxisLabelCopy = AxisLabelOrg; 
    std::vector<unsigned> Label_OccurrenceCopy = Label_OccurrenceOrg; 
    std::vector<std::string> NewAxisLabel; 
    
    //unsigned Occurrences = 0; 
    unsigned Index = 0; 
    while(AxisLabelCopy.size() > 0){
        Index = 0; 
        for(unsigned i1(0); i1 < AxisLabelCopy.size(); i1++){
            if(Label_OccurrenceCopy[i1] > Label_OccurrenceCopy[Index]){
                Index = i1; 
            }
        }
        NewAxisLabel.push_back(AxisLabelCopy[Index]);
        AxisLabelCopy.erase(AxisLabelCopy.begin()+Index); 
        Label_OccurrenceCopy.erase(Label_OccurrenceCopy.begin()+Index); 
    }
    
    return NewAxisLabel; 
    
}


std::vector<std::string> OSPlotter::SortAxisLabels(std::vector<std::string> AxisLabelOrg, std::vector<unsigned> Label_OccurrenceOrg, unsigned MinimumOccurrence){
    
    std::vector<std::string> AxisLabelCopy = AxisLabelOrg; 
    std::vector<unsigned> Label_OccurrenceCopy = Label_OccurrenceOrg; 
    std::vector<std::string> NewAxisLabel; 
    
    //unsigned Occurrences = 0; 
    unsigned Index = 0; 
    while(AxisLabelCopy.size() > 0){
        Index = 0; 
        for(unsigned i1(0); i1 < AxisLabelCopy.size(); i1++){
            if(Label_OccurrenceCopy[i1] > Label_OccurrenceCopy[Index]){
                Index = i1; 
            }
        }
        // Sorts out the more obscure combinations. 
        if(Label_OccurrenceCopy[Index] >= MinimumOccurrence)
            NewAxisLabel.push_back(AxisLabelCopy[Index]);
        
        AxisLabelCopy.erase(AxisLabelCopy.begin()+Index); 
        Label_OccurrenceCopy.erase(Label_OccurrenceCopy.begin()+Index); 
    }
    
    return NewAxisLabel; 
    
}

std::vector<std::string>
OSPlotter::SortAxisLabels(const std::map<std::string, unsigned int>& AxisLabelOrig, unsigned MinimumOccurrence)
{

    std::vector<std::pair<std::string, unsigned int>> AxisLabel{};
    for (const auto& l : AxisLabelOrig) {AxisLabel.emplace_back(l);}
    std::sort(AxisLabel.begin(), AxisLabel.end(),
            [](std::pair<std::string, unsigned int>& lhs, std::pair<std::string, unsigned int>& rhs){return lhs.second>rhs.second;});

    std::vector<std::string> LabelSorted{};
    for (const auto& l : AxisLabel)
    {
        if (l.second<MinimumOccurrence) {continue;}
        LabelSorted.emplace_back(l.first);
    }
    return LabelSorted;
}

std::vector<std::string> OSPlotter::SortAxisLabels(std::vector<std::string> AxisLabelOrg1, std::vector<unsigned> Label_OccurrenceOrg1, std::vector<std::string> AxisLabelOrg2, std::vector<unsigned> Label_OccurrenceOrg2, unsigned MinimumOccurrence){
    
    // If all Labels from two different trees are supposed to be used. 
    
    std::vector<std::string> AxisLabelCopy1 = AxisLabelOrg1; 
    std::vector<unsigned> Label_OccurrenceCopy1 = Label_OccurrenceOrg1; 
    
    std::vector<std::string> AxisLabelCopy2 = AxisLabelOrg2; 
    std::vector<unsigned> Label_OccurrenceCopy2 = Label_OccurrenceOrg2; 
    
    
    // Merge both Label Vectors; 
    bool already_exists = false; 
    
    for(unsigned i0(0); i0 < AxisLabelCopy2.size(); i0++){
        for(unsigned i1(0); i1 < AxisLabelCopy1.size(); i1++){
            if(AxisLabelCopy2[i0] == AxisLabelCopy1[i1]){
                Label_OccurrenceCopy1[i1] += Label_OccurrenceCopy2[i0];
                already_exists = true; 
                break; 
            }
        }
        if(!already_exists){
            AxisLabelCopy1.push_back(AxisLabelCopy2[i0]); 
            Label_OccurrenceCopy1.push_back(Label_OccurrenceCopy2[i0]); 
        }
    }
    
    
    
    std::vector<std::string> NewAxisLabel; 
    
    //unsigned Occurrences = 0; 
    unsigned Index = 0; 
    while(AxisLabelCopy1.size() > 0){
        Index = 0; 
        for(unsigned i1(0); i1 < AxisLabelCopy1.size(); i1++){
            if(Label_OccurrenceCopy1[i1] > Label_OccurrenceCopy1[Index]){
                Index = i1; 
            }
        }
        // Sorts out the more obscure combinations. 
        if(Label_OccurrenceCopy1[Index] >= MinimumOccurrence)
            NewAxisLabel.push_back(AxisLabelCopy1[Index]);
        
        AxisLabelCopy1.erase(AxisLabelCopy1.begin()+Index); 
        Label_OccurrenceCopy1.erase(Label_OccurrenceCopy1.begin()+Index); 
    }
    
    
    return NewAxisLabel; 
    
}









#if defined(__ROOTCLING__)
#pragma link C++ class OSPLotter;
#endif

































