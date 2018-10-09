OSAnalysis: 
===========

This code works with ROOT 5.34/36. 
Adjustments will have to be made to make it work with ROOT 6. 

-------------------------------------------------------
Set all parameters, filters, etc in run_OSAnalysis.cc . 
-------------------------------------------------------


------------------------------------------------
Create Trees from the input lists with OSTreeV2: 
------------------------------------------------

Every Branch needs its own input list. At the moment each of the branches has their own Function to read in the data. 
Eventually this should be done by something like: AddBranch(Name, Type, InputList). 

All trees have the following branches, even though some might not be filled depending on the list type: 

Workflow                (both lists)
ExitCode1               (both lists)
ExitCode1_Occurrence    (both lists)
ExitCode2               (only Active)
ExitCode2_Occurrence    (only Active)
Keyword                 (only Active)
Keyword_Occurrence      (only Active)
ActionOS                (only Active)
ActionOS_Occurrrence    (only Active)
ThresholdPerc           (only Active)
ThresholdAbs            (only Active)
ExitCode1Extra          (only Passive, second most often ExitCode)
ExitCode1Extra_Occurrence (only Passive)
ActionWTC               (only Passive)
ActionWTC_Occurrence    (only Passive)
ReasonWTC               (only Passive)
ReasonWTC_Occurrrence   (only Passive)


Workflows on the active list can contain several entries for ExitCode, Keyword, etc. 
The ones on the passive list should only contain one, since they are only reported once. 



-------------------------------------------------------------
Sort Entries into new Trees and Apply Filters with OSOverlap: 
-------------------------------------------------------------

This Class creates new Trees out of the Active and Passive ones: 

OnBothActive
OnBothPassive
OnlyActive
OnlyPassive
SortedOutActive         (not saved in output if 0 Entries)
SortedOutPassive        (not saved in output if 0 Entries)


The original trees are copied to the new output file to make plotting easier. 
Each workflow on the active and Passive trees gets a tag: 
"OnBoth", "OnlyOnActive"/"OnlyOnPassive", "SortedOut"


These tags can change, depending on the filters run on the trees. 
The filters should be constructed in a way that they can be applied consecutively if desired. 
The names of the filters are appended to the tree names in the output file. 

After all filters have been applied, run FillOutputTrees(). 
Then the lists containing the tags are used to sort the entries into the new trees. 




-----------------------------------------------
Create Plots from the Trees using OSPlotter
-----------------------------------------------

Examples for the different Plotting functions are listed in run_OSAnalysis.cc . 
