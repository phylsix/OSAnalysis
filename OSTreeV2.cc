#include "OSTreeV2.h"

OSTreeV2::OSTreeV2(){
    
    OS_Analysis_Tree = new TTree("OSTree", "Tree for OS Analysis"); 
    //cout<<"Tree has been initialized."<<endl; 
    
    hasExitCode1 = false; 
    hasExitCode2 = false; 
    hasKeyword = false; 
    hasActionOS = false; 
    hasThresholdPerc = false; 
    hasThresholdAbs = false; 
    
    hasExitCode1Extra = false; 
    hasActionWTC = false; 
    hasReasonWTC = false; 
    
    OS_Analysis_Tree->Branch("Workflows", &Workflow);
    OS_Analysis_Tree->Branch("ExitCode1", &ExitCode1);
    OS_Analysis_Tree->Branch("ExitCode1_Occurrence", &ExitCode1_Occurrence);
    
    OS_Analysis_Tree->Branch("ExitCode2", &ExitCode2);
    OS_Analysis_Tree->Branch("ExitCode2_Occurrence", &ExitCode2_Occurrence);
    
    OS_Analysis_Tree->Branch("Keyword", &Keyword);
    OS_Analysis_Tree->Branch("Keyword_Occurrence", &Keyword_Occurrence);
    
    OS_Analysis_Tree->Branch("ActionOS", &ActionOS);
    OS_Analysis_Tree->Branch("ActionOS_Occurrence", &ActionOS_Occurrence);
        
    OS_Analysis_Tree->Branch("ThresholdPerc", &ThresholdPerc);
    OS_Analysis_Tree->Branch("ThresholdPerc_Occurrence", &ThresholdPerc_Occurrence);
        
    OS_Analysis_Tree->Branch("ThresholdAbs", &ThresholdAbs);
    OS_Analysis_Tree->Branch("ThresholdAbs_Occurrence", &ThresholdAbs_Occurrence);
    
    OS_Analysis_Tree->Branch("ActionWTC", &ActionWTC);
    OS_Analysis_Tree->Branch("ActionWTC_Occurrence", &ActionWTC_Occurrence);    
    
    OS_Analysis_Tree->Branch("ReasonWTC", &ReasonWTC);
    OS_Analysis_Tree->Branch("ReasonWTC_Occurrence", &ReasonWTC_Occurrence);
    
    
    
}
 


OSTreeV2::OSTreeV2(std::string TreeName, std::string TreeTitle){
    
    OS_Analysis_Tree = new TTree(TreeName.c_str(), TreeTitle.c_str()); 
    //cout<<"Tree with name "<<TreeName<<" has been initialized."<<endl; 
    
    hasExitCode1 = false; 
    hasExitCode2 = false; 
    hasKeyword = false; 
    hasActionOS = false; 
    hasThresholdPerc = false; 
    hasThresholdAbs = false; 
    
    hasExitCode1Extra = false; 
    hasActionWTC = false; 
    hasReasonWTC = false; 
    
    
    OS_Analysis_Tree->Branch("Workflows", &Workflow);
    OS_Analysis_Tree->Branch("ExitCode1", &ExitCode1);
    OS_Analysis_Tree->Branch("ExitCode1_Occurrence", &ExitCode1_Occurrence);
    
    OS_Analysis_Tree->Branch("ExitCode2", &ExitCode2);
    OS_Analysis_Tree->Branch("ExitCode2_Occurrence", &ExitCode2_Occurrence);
    
    OS_Analysis_Tree->Branch("Keyword", &Keyword);
    OS_Analysis_Tree->Branch("Keyword_Occurrence", &Keyword_Occurrence);
    
    OS_Analysis_Tree->Branch("ActionOS", &ActionOS);
    OS_Analysis_Tree->Branch("ActionOS_Occurrence", &ActionOS_Occurrence);
        
    OS_Analysis_Tree->Branch("ThresholdPerc", &ThresholdPerc);    
    OS_Analysis_Tree->Branch("ThresholdAbs", &ThresholdAbs);
    
    OS_Analysis_Tree->Branch("ExitCode1Extra", &ExitCode1Extra);
    OS_Analysis_Tree->Branch("ExitCode1Extra_Occurrence", &ExitCode1Extra_Occurrence);
    
    OS_Analysis_Tree->Branch("ActionWTC", &ActionWTC);
    OS_Analysis_Tree->Branch("ActionWTC_Occurrence", &ActionWTC_Occurrence);    
    
    OS_Analysis_Tree->Branch("ReasonWTC", &ReasonWTC);
    OS_Analysis_Tree->Branch("ReasonWTC_Occurrence", &ReasonWTC_Occurrence);
     
}


void OSTreeV2::FillTree(){
    
    std::vector<int> IndexList;
    
    while(Workflows.size() > 0){
        
        Workflow = Workflows[0]; 
        IndexList.push_back(0); 
    
        // Look for multiple entries in the list: 
        for(int i0(1); i0 < Workflows.size(); i0++){
            if(Workflow == Workflows[i0]){
                // Save the multiple entries in the list 
                IndexList.push_back(i0); 
            }
        } //Create a list with the 
        Occurrence = IndexList.size(); 
        
        //cout<<"1"<<endl; 
        
        //cout<<"hasExitCode1: "<<hasExitCode1<<", hasExitCode2: "<<hasExitCode2<<", hasKeyword: "<<hasKeyword<<", hasActionOS: "<<hasActionOS<<", hasThresholdPerc: "<<hasThresholdPerc<<", hasThresholdAbs: "<<hasThresholdAbs<<", hasActionWTC: "<<hasActionWTC<<", hasReasonWTC"<<hasReasonWTC<<endl; 
        
        
        for(int i01(0); i01 < IndexList.size(); i01++){
            
            if(hasExitCode1){
                ExitCode1.push_back(ExitCode1_read[IndexList[i01]]); 
                ExitCode1_Occurrence.push_back(1); 
            }
            if(hasExitCode2){
                ExitCode2.push_back(ExitCode2_read[IndexList[i01]]); 
                ExitCode2_Occurrence.push_back(1); 
            }
            if(hasKeyword){
                Keyword.push_back(Keyword_read[IndexList[i01]]); 
                Keyword_Occurrence.push_back(1); 
            }
            if(hasActionOS){
                ActionOS.push_back(ActionOS_read[IndexList[i01]]); 
                ActionOS_Occurrence.push_back(1); 
            }
            if(hasThresholdPerc){
                ThresholdPerc.push_back(ThresholdPerc_read[IndexList[i01]]); 
            }
            if(hasThresholdAbs){
                ThresholdAbs.push_back(ThresholdAbs_read[IndexList[i01]]); 
            }
            if(hasExitCode1Extra){
                ExitCode1Extra.push_back(ExitCode1Extra_read[IndexList[i01]]); 
                ExitCode1Extra_Occurrence.push_back(1); 
            }
            if(hasActionWTC){
                ActionWTC.push_back(ActionWTC_read[IndexList[i01]]); 
                ActionWTC_Occurrence.push_back(1); 
            }
            if(hasReasonWTC){
                ReasonWTC.push_back(ReasonWTC_read[IndexList[i01]]); 
                ReasonWTC_Occurrence.push_back(1); 
            }
        }
         
        OS_Analysis_Tree->Fill();
     
        for(int i01 = IndexList.size()-1; i01 >= 0 ; i01--){
            
            //cout<<IndexList[i01]<<endl; 
            //cout<<"ExitCode1: "<<ExitCode1_read.size()<<", ExitCode2: "<<ExitCode2_read.size()<<", Keyword: "<<Keyword_read.size()<<", ActionOS: "<<ActionOS_read.size()<<", ThresholdPerc: "<<ThresholdPerc_read.size()<<", ThresholdAbs: "<<ThresholdAbs_read.size()<<", ActionWTC: "<<ActionWTC_read.size()<<", ReasonWTC"<<ReasonWTC_read.size()<<endl;
            
            
            Workflows.erase(Workflows.begin()+IndexList[i01]);
            if(hasExitCode1)    ExitCode1_read.erase(ExitCode1_read.begin()+IndexList[i01]);
            if(hasExitCode2)    ExitCode2_read.erase(ExitCode2_read.begin()+IndexList[i01]);
            if(hasKeyword)      Keyword_read.erase(Keyword_read.begin()+IndexList[i01]);
            if(hasActionOS)     ActionOS_read.erase(ActionOS_read.begin()+IndexList[i01]);
            if(hasThresholdPerc)ThresholdPerc_read.erase(ThresholdPerc_read.begin()+IndexList[i01]);
            if(hasThresholdAbs) ThresholdAbs_read.erase(ThresholdAbs_read.begin()+IndexList[i01]);
            if(hasExitCode1Extra)ExitCode1Extra_read.erase(ExitCode1Extra_read.begin()+IndexList[i01]);
            if(hasActionWTC)    ActionWTC_read.erase(ActionWTC_read.begin()+IndexList[i01]);
            if(hasReasonWTC)    ReasonWTC_read.erase(ReasonWTC_read.begin()+IndexList[i01]);

        }
        
        
        IndexList.clear(); 
        ExitCode1.clear(); 
        ExitCode1_Occurrence.clear();
        ExitCode2.clear(); 
        ExitCode2_Occurrence.clear(); 
        Keyword.clear(); 
        Keyword_Occurrence.clear(); 
        ActionOS.clear(); 
        ActionOS_Occurrence.clear(); 
        ThresholdPerc.clear(); 
        ThresholdAbs.clear(); 
        ExitCode1Extra.clear(); 
        ActionWTC.clear(); 
        ReasonWTC.clear(); 
        
        
    }
    
    OS_Analysis_Tree->Write();
    delete OS_Analysis_Tree; 
    
}





// Functions for adding the different Branches: 
void OSTreeV2::AddWorkflows(std::string WorkflowsListName){
    
    std::ifstream WorkflowsList(WorkflowsListName.c_str());
        
    while(std::getline(WorkflowsList, line)){
        Workflows.push_back(line); 
    }
    cout<<"Workflows: "<<Workflows.size()<<endl; 
}

void OSTreeV2::AddExitCode1(std::string ExitCode1ListName){

    hasExitCode1 = true; 
    std::ifstream ExitCode1List(ExitCode1ListName.c_str());
    
    while(std::getline(ExitCode1List, line)){
        ExitCode1_read.push_back(line); 
    }
    cout<<"ExitCode1: "<<ExitCode1_read.size()<<endl; 
}

void OSTreeV2::AddExitCode2(std::string ExitCode2ListName){

    hasExitCode2 = true; 
    std::ifstream ExitCode2List(ExitCode2ListName.c_str());
    
    while(std::getline(ExitCode2List, line)){
        ExitCode2_read.push_back(line); 
    }
    cout<<"ExitCode2: "<<ExitCode2_read.size()<<endl; 
}    

    
void OSTreeV2::AddKeyword(std::string KeywordListName){

    hasKeyword = true; 
    std::ifstream KeywordList(KeywordListName.c_str());
    
    while(std::getline(KeywordList, line)){
        Keyword_read.push_back(line); 
    }
    cout<<"Keyword: "<<Keyword_read.size()<<endl; 
}    
    
void OSTreeV2::AddActionOS(std::string ActionOSListName){

    hasActionOS = true; 
    std::ifstream ActionOSList(ActionOSListName.c_str());
    
    while(std::getline(ActionOSList, line)){
        ActionOS_read.push_back(line); 
    }
    cout<<"ActionOS: "<<ActionOS_read.size()<<endl; 
}       


void OSTreeV2::AddThresholdPerc(std::string ThresholdPercListName){
    
    hasThresholdPerc = true; 
    float Percent; 
    std::ifstream ThresholdPercList(ThresholdPercListName.c_str()); 

    while(std::getline(ThresholdPercList, line)){
        if(ThresholdPercList >> Percent) 
            ThresholdPerc_read.push_back(Percent); 
    }
    cout<<"Threshold Percent: "<<ThresholdPerc_read.size()<<endl; 
}

void OSTreeV2::AddThresholdAbs(std::string ThresholdAbsListName){
    
    hasThresholdAbs = true; 
    int Absolute; 
    std::ifstream ThresholdAbsList(ThresholdAbsListName.c_str()); 

    while(std::getline(ThresholdAbsList, line)){
        if(ThresholdAbsList >> Absolute) 
            ThresholdAbs_read.push_back(Absolute); 
    }
    cout<<"Threshold Absolute: "<<ThresholdAbs_read.size()<<endl; 
    /*for(int i(0); i < ThresholdAbs_read.size(); i++){
        cout<<ThresholdAbs_read[i]<<endl; 
        
    }*/
}



void OSTreeV2::AddExitCode1Extra(std::string ExitCode1ExtraListName){

    hasExitCode1Extra = true; 
    std::ifstream ExitCode1ExtraList(ExitCode1ExtraListName.c_str());
    
    while(std::getline(ExitCode1ExtraList, line)){
        ExitCode1Extra_read.push_back(line); 
    }
    cout<<"ExitCode1Extra: "<<ExitCode1Extra_read.size()<<endl; 
}  


void OSTreeV2::AddActionWTC(std::string ActionWTCListName){

    hasActionWTC = true; 
    std::ifstream ActionWTCList(ActionWTCListName.c_str());
    
    while(std::getline(ActionWTCList, line)){
        ActionWTC_read.push_back(line); 
    }
    cout<<"ActionWTC: "<<ActionWTC_read.size()<<endl; 
}  

void OSTreeV2::AddReasonWTC(std::string ReasonWTCListName){

    hasReasonWTC = true; 
    std::ifstream ReasonWTCList(ReasonWTCListName.c_str());
    
    while(std::getline(ReasonWTCList, line)){
        ReasonWTC_read.push_back(line); 
    }
    cout<<"ReasonWTC: "<<ReasonWTC_read.size()<<endl; 
}  






#if defined(__ROOTCLING__)
#pragma link C++ class OSTreeV2;
#endif
    
    
    
    

