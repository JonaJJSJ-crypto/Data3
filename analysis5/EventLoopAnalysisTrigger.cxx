  //////////////////////////////////////////////////////////////////////
// This template analysis code has been built with fragments from the
// classes automatically obtained by the TTree MakeClass() method.
//
// The template shows the structre of a potential analysis code
// where more TTree friends can be added with more physics objects.
//
// The analysis part is based on the RDataFrame analysis example by Stefan Wunch:
// https://github.com/cms-opendata-analyses/HiggsTauTauNanoAODOutreachAnalysis
//
// Done with ROOT version 5.32/00
// from TTree Events/Events
// found on file: myoutput.root
//
//
// Compile me with:
// g++ -std=c++11 -g -O3 -Wall -Wextra -o EventLoopAnalysisTrigg EventLoopAnalysisTrigger.cxx $(root-config --cflags --libs)
/////////////////////////////////////////////////////////////////////

//Include ROOT classes
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include "TLatex.h"
#include "TStopwatch.h"
//Include C++ classes
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;


/*
 * Base path to local filesystem or to EOS containing the datasets
 */
//const std::string samplesBasePath = "root://eospublic.cern.ch//eos/opendata/cms/upload/od-workshop/ws2021/";
const std::string samplesBasePath = "Datos/";


//book example histograms for specific variables
//copy them in the constructor if you add more
const int nhists = 624;

//Histograms for signal region no Filter
TH1F* NF_dataRunB_npv = new TH1F("NF_dataRunB_npv","NF Number of primary vertices",25,5,30);

TH1F* NF_dataRunC_npv  = new TH1F("NF_dataRunC_npv","NF Number of primary vertices",25,5,30);

TH1F* NF_ZLL_npv = new TH1F("NF_ZLL_npv","NF Number of primary vertices",25,5,30);

TH1F* NF_TT_npv = new TH1F("NF_TT_npv","NF Number of primary vertices",25,5,30);

TH1F* NF_W3J_npv = new TH1F("NF_W3J_npv","NF Number of primary vertices",25,5,30);

TH1F* NF_W2J_npv = new TH1F("NF_W2J_npv","NF Number of primary vertices",25,5,30);

TH1F* NF_W1J_npv = new TH1F("NF_W1J_npv","NF Number of primary vertices",25,5,30);

//TH1F* //NF_TTZ_npv = new TH1F("//NF_TTZ_npv","NF Number of primary vertices",25,5,30);

//TH1F* //NF_WW_npv = new TH1F("//NF_WW_npv","NF Number of primary vertices",25,5,30);

//TH1F* //NF_WZ_npv = new TH1F("//NF_WZ_npv","NF Number of primary vertices",25,5,30);

TH1F* NF_LW200_npv = new TH1F("NF_LW200_npv","NF Number of primary vertices",25,5,30);

////TH1F* //NF_LW300_npv = new TH1F("//NF_LW300_npv","NF Number of primary vertices",25,5,30);

//TH1F* NF_LW400_npv = new TH1F("NF_LW400_npv","NF Number of primary vertices",25,5,30);

//TH1F* NF_LW500_npv = new TH1F("NF_LW500_npv","NF Number of primary vertices",25,5,30);

TH1F* NF_dataRunB_nsv = new TH1F("NF_dataRunB_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_dataRunC_nsv  = new TH1F("NF_dataRunC_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_ZLL_nsv = new TH1F("NF_ZLL_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_TT_nsv = new TH1F("NF_TT_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_W3J_nsv = new TH1F("NF_W3J_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_W2J_nsv = new TH1F("NF_W2J_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_W1J_nsv = new TH1F("NF_W1J_nsv","NF Number of secondary vertices",20,0,2000);

//TH1F* //NF_TTZ_nsv = new TH1F("//NF_TTZ_nsv","NF Number of secondary vertices",20,0,2000);

//TH1F* //NF_WW_nsv = new TH1F("//NF_WW_nsv","NF Number of secondary vertices",20,0,2000);

//TH1F* //NF_WZ_nsv = new TH1F("//NF_WZ_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_LW200_nsv = new TH1F("NF_LW200_nsv","NF Number of secondary vertices",20,0,2000);

////TH1F* //NF_LW300_nsv = new TH1F("//NF_LW300_nsv","NF Number of secondary vertices",20,0,2000);

//TH1F* NF_LW400_nsv = new TH1F("NF_LW400_nsv","NF Number of secondary vertices",20,0,2000);

//TH1F* NF_LW500_nsv = new TH1F("NF_LW500_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_dataRunB_svd = new TH1F("NF_dataRunB_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_dataRunC_svd  = new TH1F("NF_dataRunC_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_ZLL_svd = new TH1F("NF_ZLL_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_TT_svd = new TH1F("NF_TT_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_W3J_svd = new TH1F("NF_W3J_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_W2J_svd = new TH1F("NF_W2J_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_W1J_svd = new TH1F("NF_W1J_svd","NF secondary vertex displacement",100,0,1);

//TH1F* //NF_TTZ_svd = new TH1F("//NF_TTZ_svd","NF secondary vertex displacement",100,0,1);

//TH1F* //NF_WW_svd = new TH1F("//NF_WW_svd","NF secondary vertex displacement",100,0,1);

//TH1F* //NF_WZ_svd = new TH1F("//NF_WZ_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_LW200_svd = new TH1F("NF_LW200_svd","NF secondary vertex displacement",100,0,1);

////TH1F* //NF_LW300_svd = new TH1F("//NF_LW300_svd","NF secondary vertex displacement",100,0,1);

//TH1F* NF_LW400_svd = new TH1F("NF_LW400_svd","NF secondary vertex displacement",100,0,1);

//TH1F* NF_LW500_svd = new TH1F("NF_LW500_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_dataRunB_JetMass = new TH1F("NF_dataRunB_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_dataRunC_JetMass  = new TH1F("NF_dataRunC_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_ZLL_JetMass = new TH1F("NF_ZLL_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_TT_JetMass = new TH1F("NF_TT_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_W3J_JetMass = new TH1F("NF_W3J_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_W2J_JetMass = new TH1F("NF_W2J_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_W1J_JetMass = new TH1F("NF_W1J_JetMass","NF Invariant mass from DiJets",100,0,400);

//TH1F* //NF_TTZ_JetMass = new TH1F("//NF_TTZ_JetMass","NF Invariant mass from DiJets",100,0,400);

//TH1F* //NF_WW_JetMass = new TH1F("//NF_WW_JetMass","NF Invariant mass from DiJets",100,0,400);

//TH1F* //NF_WZ_JetMass = new TH1F("//NF_WZ_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_LW200_JetMass = new TH1F("NF_LW200_JetMass","NF Invariant mass from DiJets",100,0,400);

////TH1F* //NF_LW300_JetMass = new TH1F("//NF_LW300_JetMass","NF Invariant mass from DiJets",100,0,400);

//TH1F* NF_LW400_JetMass = new TH1F("NF_LW400_JetMass","NF Invariant mass from DiJets",100,0,400);

//TH1F* NF_LW500_JetMass = new TH1F("NF_LW500_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_dataRunB_LWMass = new TH1F("NF_dataRunB_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_dataRunC_LWMass  = new TH1F("NF_dataRunC_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_ZLL_LWMass = new TH1F("NF_ZLL_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_TT_LWMass = new TH1F("NF_TT_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_W3J_LWMass = new TH1F("NF_W3J_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_W2J_LWMass = new TH1F("NF_W2J_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_W1J_LWMass = new TH1F("NF_W1J_LWMass","NF Invariant mass from LW",100,0,400);

//TH1F* //NF_TTZ_LWMass = new TH1F("//NF_TTZ_LWMass","NF Invariant mass from LW",100,0,400);

//TH1F* //NF_WW_LWMass = new TH1F("//NF_WW_LWMass","NF Invariant mass from LW",100,0,400);

//TH1F* //NF_WZ_LWMass = new TH1F("//NF_WZ_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_LW200_LWMass = new TH1F("NF_LW200_LWMass","NF Invariant mass from LW",100,0,400);

////TH1F* //NF_LW300_LWMass = new TH1F("//NF_LW300_LWMass","NF Invariant mass from LW",100,0,400);

//TH1F* NF_LW400_LWMass = new TH1F("NF_LW400_LWMass","NF Invariant mass from LW",100,0,400);

//TH1F* NF_LW500_LWMass = new TH1F("NF_LW500_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_dataRunB_Elept = new TH1F("NF_dataRunB_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_dataRunC_Elept  = new TH1F("NF_dataRunC_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_ZLL_Elept = new TH1F("NF_ZLL_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_TT_Elept = new TH1F("NF_TT_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_W3J_Elept = new TH1F("NF_W3J_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_W2J_Elept = new TH1F("NF_W2J_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_W1J_Elept = new TH1F("NF_W1J_Elept","NF Electron pt distribution",100,0,200);

//TH1F* //NF_TTZ_Elept = new TH1F("//NF_TTZ_Elept","NF Electron pt distribution",100,0,200);

//TH1F* //NF_WW_Elept = new TH1F("//NF_WW_Elept","NF Electron pt distribution",100,0,200);

//TH1F* //NF_WZ_Elept = new TH1F("//NF_WZ_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_LW200_Elept = new TH1F("NF_LW200_Elept","NF Electron pt distribution",100,0,200);

////TH1F* //NF_LW300_Elept = new TH1F("//NF_LW300_Elept","NF Electron pt distribution",100,0,200);

//TH1F* NF_LW400_Elept = new TH1F("NF_LW400_Elept","NF Electron pt distribution",100,0,200);

//TH1F* NF_LW500_Elept = new TH1F("NF_LW500_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_dataRunB_DieledR = new TH1F("NF_dataRunB_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_dataRunC_DieledR  = new TH1F("NF_dataRunC_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_ZLL_DieledR = new TH1F("NF_ZLL_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_TT_DieledR = new TH1F("NF_TT_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_W3J_DieledR = new TH1F("NF_W3J_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_W2J_DieledR = new TH1F("NF_W2J_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_W1J_DieledR = new TH1F("NF_W1J_DieledR","NF delta R separation between electrons",100,0,8);

//TH1F* //NF_TTZ_DieledR = new TH1F("//NF_TTZ_DieledR","NF delta R separation between electrons",100,0,8);

//TH1F* //NF_WW_DieledR = new TH1F("//NF_WW_DieledR","NF delta R separation between electrons",100,0,8);

//TH1F* //NF_WZ_DieledR = new TH1F("//NF_WZ_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_LW200_DieledR = new TH1F("NF_LW200_DieledR","NF delta R separation between electrons",100,0,8);

////TH1F* //NF_LW300_DieledR = new TH1F("//NF_LW300_DieledR","NF delta R separation between electrons",100,0,8);

//TH1F* NF_LW400_DieledR = new TH1F("NF_LW400_DieledR","NF delta R separation between electrons",100,0,8);

//TH1F* NF_LW500_DieledR = new TH1F("NF_LW500_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_dataRunB_LWdR = new TH1F("NF_dataRunB_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_dataRunC_LWdR  = new TH1F("NF_dataRunC_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_ZLL_LWdR = new TH1F("NF_ZLL_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_TT_LWdR = new TH1F("NF_TT_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_W3J_LWdR = new TH1F("NF_W3J_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_W2J_LWdR = new TH1F("NF_W2J_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_W1J_LWdR = new TH1F("NF_W1J_LWdR","NF delta R separation between electrons and jets",100,0,8);

//TH1F* //NF_TTZ_LWdR = new TH1F("//NF_TTZ_LWdR","NF delta R separation between electrons and jets",100,0,8);

//TH1F* //NF_WW_LWdR = new TH1F("//NF_WW_LWdR","NF delta R separation between electrons and jets",100,0,8);

//TH1F* //NF_WZ_LWdR = new TH1F("//NF_WZ_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_LW200_LWdR = new TH1F("NF_LW200_LWdR","NF delta R separation between electrons and jets",100,0,8);

////TH1F* //NF_LW300_LWdR = new TH1F("//NF_LW300_LWdR","NF delta R separation between electrons and jets",100,0,8);

//TH1F* NF_LW400_LWdR = new TH1F("NF_LW400_LWdR","NF delta R separation between electrons and jets",100,0,8);

//TH1F* NF_LW500_LWdR = new TH1F("NF_LW500_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_dataRunB_DiJetdR = new TH1F("NF_dataRunB_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_dataRunC_DiJetdR  = new TH1F("NF_dataRunC_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_ZLL_DiJetdR = new TH1F("NF_ZLL_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_TT_DiJetdR = new TH1F("NF_TT_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_W3J_DiJetdR = new TH1F("NF_W3J_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_W2J_DiJetdR = new TH1F("NF_W2J_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_W1J_DiJetdR = new TH1F("NF_W1J_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

//TH1F* //NF_TTZ_DiJetdR = new TH1F("//NF_TTZ_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

//TH1F* //NF_WW_DiJetdR = new TH1F("//NF_WW_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

//TH1F* //NF_WZ_DiJetdR = new TH1F("//NF_WZ_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_LW200_DiJetdR = new TH1F("NF_LW200_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

////TH1F* //NF_LW300_DiJetdR = new TH1F("//NF_LW300_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

//TH1F* NF_LW400_DiJetdR = new TH1F("NF_LW400_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

//TH1F* NF_LW500_DiJetdR = new TH1F("NF_LW500_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_dataRunB_BJetPt = new TH1F("NF_dataRunB_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_dataRunC_BJetPt  = new TH1F("NF_dataRunC_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_ZLL_BJetPt = new TH1F("NF_ZLL_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_TT_BJetPt = new TH1F("NF_TT_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_W3J_BJetPt = new TH1F("NF_W3J_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_W2J_BJetPt = new TH1F("NF_W2J_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_W1J_BJetPt = new TH1F("NF_W1J_BJetPt","NF Most energetic Jet pt",100,0,250);

//TH1F* //NF_TTZ_BJetPt = new TH1F("//NF_TTZ_BJetPt","NF Most energetic Jet pt",100,0,250);

//TH1F* //NF_WW_BJetPt = new TH1F("//NF_WW_BJetPt","NF Most energetic Jet pt",100,0,250);

//TH1F* //NF_WZ_BJetPt = new TH1F("//NF_WZ_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_LW200_BJetPt = new TH1F("NF_LW200_BJetPt","NF Most energetic Jet pt",100,0,250);

//TH1F* //NF_LW300_BJetPt = new TH1F("//NF_LW300_BJetPt","NF Most energetic Jet pt",100,0,250);

//TH1F* NF_LW400_BJetPt = new TH1F("NF_LW400_BJetPt","NF Most energetic Jet pt",100,0,250);

//TH1F* NF_LW500_BJetPt = new TH1F("NF_LW500_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_dataRunB_SBJetPt = new TH1F("NF_dataRunB_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_dataRunC_SBJetPt  = new TH1F("NF_dataRunC_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_ZLL_SBJetPt = new TH1F("NF_ZLL_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_TT_SBJetPt = new TH1F("NF_TT_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_W3J_SBJetPt = new TH1F("NF_W3J_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_W2J_SBJetPt = new TH1F("NF_W2J_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_W1J_SBJetPt = new TH1F("NF_W1J_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

//TH1F* //NF_TTZ_SBJetPt = new TH1F("//NF_TTZ_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

//TH1F* //NF_WW_SBJetPt = new TH1F("//NF_WW_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

//TH1F* //NF_WZ_SBJetPt = new TH1F("//NF_WZ_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_LW200_SBJetPt = new TH1F("NF_LW200_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

//TH1F* //NF_LW300_SBJetPt = new TH1F("//NF_LW300_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

//TH1F* NF_LW400_SBJetPt = new TH1F("NF_LW400_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

//TH1F* NF_LW500_SBJetPt = new TH1F("NF_LW500_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_dataRunB_NJet = new TH1F("NF_dataRunB_NJet","NF Number of Jets",20,0,20);

TH1F* NF_dataRunC_NJet  = new TH1F("NF_dataRunC_NJet","NF Number of Jets",20,0,20);

TH1F* NF_ZLL_NJet = new TH1F("NF_ZLL_NJet","NF Number of Jets",20,0,20);

TH1F* NF_TT_NJet = new TH1F("NF_TT_NJet","NF Number of Jets",20,0,20);

TH1F* NF_W3J_NJet = new TH1F("NF_W3J_NJet","NF Number of Jets",20,0,20);

TH1F* NF_W2J_NJet = new TH1F("NF_W2J_NJet","NF Number of Jets",20,0,20);

TH1F* NF_W1J_NJet = new TH1F("NF_W1J_NJet","NF Number of Jets",20,0,20);

//TH1F* //NF_TTZ_NJet = new TH1F("//NF_TTZ_NJet","NF Number of Jets",20,0,20);

//TH1F* //NF_WW_NJet = new TH1F("//NF_WW_NJet","NF Number of Jets",20,0,20);

//TH1F* //NF_WZ_NJet = new TH1F("//NF_WZ_NJet","NF Number of Jets",20,0,20);

TH1F* NF_LW200_NJet = new TH1F("NF_LW200_NJet","NF Number of Jets",20,0,20);

//TH1F* //NF_LW300_NJet = new TH1F("//NF_LW300_NJet","NF Number of Jets",20,0,20);

//TH1F* NF_LW400_NJet = new TH1F("NF_LW400_NJet","NF Number of Jets",20,0,20);

//TH1F* NF_LW500_NJet = new TH1F("NF_LW500_NJet","NF Number of Jets",20,0,20);

TH1F* NF_dataRunB_NEle = new TH1F("NF_dataRunB_NEle","NF Number of electrons",20,0,20);

TH1F* NF_dataRunC_NEle  = new TH1F("NF_dataRunC_NEle","NF Number of electrons",20,0,20);

TH1F* NF_ZLL_NEle = new TH1F("NF_ZLL_NEle","NF Number of electrons",20,0,20);

TH1F* NF_TT_NEle = new TH1F("NF_TT_NEle","NF Number of electrons",20,0,20);

TH1F* NF_W3J_NEle = new TH1F("NF_W3J_NEle","NF Number of electrons",20,0,20);

TH1F* NF_W2J_NEle = new TH1F("NF_W2J_NEle","NF Number of electrons",20,0,20);

TH1F* NF_W1J_NEle = new TH1F("NF_W1J_NEle","NF Number of electrons",20,0,20);

//TH1F* //NF_TTZ_NEle = new TH1F("//NF_TTZ_NEle","NF Number of electrons",20,0,20);

//TH1F* //NF_WW_NEle = new TH1F("//NF_WW_NEle","NF Number of electrons",20,0,20);

//TH1F* //NF_WZ_NEle = new TH1F("//NF_WZ_NEle","NF Number of electrons",20,0,20);

TH1F* NF_LW200_NEle = new TH1F("NF_LW200_NEle","NF Number of electrons",20,0,20);

//TH1F* //NF_LW300_NEle = new TH1F("//NF_LW300_NEle","NF Number of electrons",20,0,20);

//TH1F* NF_LW400_NEle = new TH1F("NF_LW400_NEle","NF Number of electrons",20,0,20);

//TH1F* NF_LW500_NEle = new TH1F("NF_LW500_NEle","NF Number of electrons",20,0,20);

//////////////////////////////////////Trigg filter
TH1F* TF_dataRunB_npv = new TH1F("TF_dataRunB_npv","TF Number of primary vertices",25,5,30);

TH1F* TF_dataRunC_npv  = new TH1F("TF_dataRunC_npv","TF Number of primary vertices",25,5,30);

TH1F* TF_ZLL_npv = new TH1F("TF_ZLL_npv","TF Number of primary vertices",25,5,30);

TH1F* TF_TT_npv = new TH1F("TF_TT_npv","TF Number of primary vertices",25,5,30);

TH1F* TF_W3J_npv = new TH1F("TF_W3J_npv","TF Number of primary vertices",25,5,30);

TH1F* TF_W2J_npv = new TH1F("TF_W2J_npv","TF Number of primary vertices",25,5,30);

TH1F* TF_W1J_npv = new TH1F("TF_W1J_npv","TF Number of primary vertices",25,5,30);

//TH1F* //TF_TTZ_npv = new TH1F("//TF_TTZ_npv","TF Number of primary vertices",25,5,30);

//TH1F* //TF_WW_npv = new TH1F("//TF_WW_npv","TF Number of primary vertices",25,5,30);

//TH1F* //TF_WZ_npv = new TH1F("//TF_WZ_npv","TF Number of primary vertices",25,5,30);

TH1F* TF_LW200_npv = new TH1F("TF_LW200_npv","TF Number of primary vertices",25,5,30);

//TH1F* //TF_LW300_npv = new TH1F("//TF_LW300_npv","TF Number of primary vertices",25,5,30);

//TH1F* TF_LW400_npv = new TH1F("TF_LW400_npv","TF Number of primary vertices",25,5,30);

//TH1F* TF_LW500_npv = new TH1F("TF_LW500_npv","TF Number of primary vertices",25,5,30);

TH1F* TF_dataRunB_nsv = new TH1F("TF_dataRunB_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_dataRunC_nsv  = new TH1F("TF_dataRunC_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_ZLL_nsv = new TH1F("TF_ZLL_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_TT_nsv = new TH1F("TF_TT_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_W3J_nsv = new TH1F("TF_W3J_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_W2J_nsv = new TH1F("TF_W2J_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_W1J_nsv = new TH1F("TF_W1J_nsv","TF Number of secondary vertices",20,0,2000);

//TH1F* //TF_TTZ_nsv = new TH1F("//TF_TTZ_nsv","TF Number of secondary vertices",20,0,2000);

//TH1F* //TF_WW_nsv = new TH1F("//TF_WW_nsv","TF Number of secondary vertices",20,0,2000);

//TH1F* //TF_WZ_nsv = new TH1F("//TF_WZ_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_LW200_nsv = new TH1F("TF_LW200_nsv","TF Number of secondary vertices",20,0,2000);

//TH1F* //TF_LW300_nsv = new TH1F("//TF_LW300_nsv","TF Number of secondary vertices",20,0,2000);

//TH1F* TF_LW400_nsv = new TH1F("TF_LW400_nsv","TF Number of secondary vertices",20,0,2000);

//TH1F* TF_LW500_nsv = new TH1F("TF_LW500_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_dataRunB_svd = new TH1F("TF_dataRunB_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_dataRunC_svd  = new TH1F("TF_dataRunC_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_ZLL_svd = new TH1F("TF_ZLL_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_TT_svd = new TH1F("TF_TT_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_W3J_svd = new TH1F("TF_W3J_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_W2J_svd = new TH1F("TF_W2J_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_W1J_svd = new TH1F("TF_W1J_svd","TF secondary vertex displacement",100,0,1);

//TH1F* //TF_TTZ_svd = new TH1F("//TF_TTZ_svd","TF secondary vertex displacement",100,0,1);

//TH1F* //TF_WW_svd = new TH1F("//TF_WW_svd","TF secondary vertex displacement",100,0,1);

//TH1F* //TF_WZ_svd = new TH1F("//TF_WZ_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_LW200_svd = new TH1F("TF_LW200_svd","TF secondary vertex displacement",100,0,1);

//TH1F* //TF_LW300_svd = new TH1F("//TF_LW300_svd","TF secondary vertex displacement",100,0,1);

//TH1F* TF_LW400_svd = new TH1F("TF_LW400_svd","TF secondary vertex displacement",100,0,1);

//TH1F* TF_LW500_svd = new TH1F("TF_LW500_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_dataRunB_JetMass = new TH1F("TF_dataRunB_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_dataRunC_JetMass  = new TH1F("TF_dataRunC_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_ZLL_JetMass = new TH1F("TF_ZLL_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_TT_JetMass = new TH1F("TF_TT_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_W3J_JetMass = new TH1F("TF_W3J_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_W2J_JetMass = new TH1F("TF_W2J_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_W1J_JetMass = new TH1F("TF_W1J_JetMass","TF Invariant mass from DiJets",100,0,400);

//TH1F* //TF_TTZ_JetMass = new TH1F("//TF_TTZ_JetMass","TF Invariant mass from DiJets",100,0,400);

//TH1F* //TF_WW_JetMass = new TH1F("//TF_WW_JetMass","TF Invariant mass from DiJets",100,0,400);

//TH1F* //TF_WZ_JetMass = new TH1F("//TF_WZ_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_LW200_JetMass = new TH1F("TF_LW200_JetMass","TF Invariant mass from DiJets",100,0,400);

//TH1F* //TF_LW300_JetMass = new TH1F("//TF_LW300_JetMass","TF Invariant mass from DiJets",100,0,400);

//TH1F* TF_LW400_JetMass = new TH1F("TF_LW400_JetMass","TF Invariant mass from DiJets",100,0,400);

//TH1F* TF_LW500_JetMass = new TH1F("TF_LW500_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_dataRunB_LWMass = new TH1F("TF_dataRunB_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_dataRunC_LWMass  = new TH1F("TF_dataRunC_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_ZLL_LWMass = new TH1F("TF_ZLL_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_TT_LWMass = new TH1F("TF_TT_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_W3J_LWMass = new TH1F("TF_W3J_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_W2J_LWMass = new TH1F("TF_W2J_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_W1J_LWMass = new TH1F("TF_W1J_LWMass","TF Invariant mass from LW",100,0,400);

//TH1F* //TF_TTZ_LWMass = new TH1F("//TF_TTZ_LWMass","TF Invariant mass from LW",100,0,400);

//TH1F* //TF_WW_LWMass = new TH1F("//TF_WW_LWMass","TF Invariant mass from LW",100,0,400);

//TH1F* //TF_WZ_LWMass = new TH1F("//TF_WZ_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_LW200_LWMass = new TH1F("TF_LW200_LWMass","TF Invariant mass from LW",100,0,400);

//TH1F* //TF_LW300_LWMass = new TH1F("//TF_LW300_LWMass","TF Invariant mass from LW",100,0,400);

//TH1F* TF_LW400_LWMass = new TH1F("TF_LW400_LWMass","TF Invariant mass from LW",100,0,400);

//TH1F* TF_LW500_LWMass = new TH1F("TF_LW500_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_dataRunB_Elept = new TH1F("TF_dataRunB_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_dataRunC_Elept  = new TH1F("TF_dataRunC_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_ZLL_Elept = new TH1F("TF_ZLL_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_TT_Elept = new TH1F("TF_TT_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_W3J_Elept = new TH1F("TF_W3J_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_W2J_Elept = new TH1F("TF_W2J_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_W1J_Elept = new TH1F("TF_W1J_Elept","TF Electron pt distribution",100,0,200);

//TH1F* //TF_TTZ_Elept = new TH1F("//TF_TTZ_Elept","TF Electron pt distribution",100,0,200);

//TH1F* //TF_WW_Elept = new TH1F("//TF_WW_Elept","TF Electron pt distribution",100,0,200);

//TH1F* //TF_WZ_Elept = new TH1F("//TF_WZ_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_LW200_Elept = new TH1F("TF_LW200_Elept","TF Electron pt distribution",100,0,200);

//TH1F* //TF_LW300_Elept = new TH1F("//TF_LW300_Elept","TF Electron pt distribution",100,0,200);

//TH1F* TF_LW400_Elept = new TH1F("TF_LW400_Elept","TF Electron pt distribution",100,0,200);

//TH1F* TF_LW500_Elept = new TH1F("TF_LW500_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_dataRunB_DieledR = new TH1F("TF_dataRunB_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_dataRunC_DieledR  = new TH1F("TF_dataRunC_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_ZLL_DieledR = new TH1F("TF_ZLL_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_TT_DieledR = new TH1F("TF_TT_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_W3J_DieledR = new TH1F("TF_W3J_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_W2J_DieledR = new TH1F("TF_W2J_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_W1J_DieledR = new TH1F("TF_W1J_DieledR","TF delta R separation between electrons",100,0,8);

//TH1F* //TF_TTZ_DieledR = new TH1F("//TF_TTZ_DieledR","TF delta R separation between electrons",100,0,8);

//TH1F* //TF_WW_DieledR = new TH1F("//TF_WW_DieledR","TF delta R separation between electrons",100,0,8);

//TH1F* //TF_WZ_DieledR = new TH1F("//TF_WZ_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_LW200_DieledR = new TH1F("TF_LW200_DieledR","TF delta R separation between electrons",100,0,8);

//TH1F* //TF_LW300_DieledR = new TH1F("//TF_LW300_DieledR","TF delta R separation between electrons",100,0,8);

//TH1F* TF_LW400_DieledR = new TH1F("TF_LW400_DieledR","TF delta R separation between electrons",100,0,8);

//TH1F* TF_LW500_DieledR = new TH1F("TF_LW500_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_dataRunB_LWdR = new TH1F("TF_dataRunB_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_dataRunC_LWdR  = new TH1F("TF_dataRunC_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_ZLL_LWdR = new TH1F("TF_ZLL_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_TT_LWdR = new TH1F("TF_TT_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_W3J_LWdR = new TH1F("TF_W3J_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_W2J_LWdR = new TH1F("TF_W2J_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_W1J_LWdR = new TH1F("TF_W1J_LWdR","TF delta R separation between electrons and jets",100,0,8);

//TH1F* //TF_TTZ_LWdR = new TH1F("//TF_TTZ_LWdR","TF delta R separation between electrons and jets",100,0,8);

//TH1F* //TF_WW_LWdR = new TH1F("//TF_WW_LWdR","TF delta R separation between electrons and jets",100,0,8);

//TH1F* //TF_WZ_LWdR = new TH1F("//TF_WZ_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_LW200_LWdR = new TH1F("TF_LW200_LWdR","TF delta R separation between electrons and jets",100,0,8);

//TH1F* //TF_LW300_LWdR = new TH1F("//TF_LW300_LWdR","TF delta R separation between electrons and jets",100,0,8);

//TH1F* TF_LW400_LWdR = new TH1F("TF_LW400_LWdR","TF delta R separation between electrons and jets",100,0,8);

//TH1F* TF_LW500_LWdR = new TH1F("TF_LW500_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_dataRunB_DiJetdR = new TH1F("TF_dataRunB_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_dataRunC_DiJetdR  = new TH1F("TF_dataRunC_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_ZLL_DiJetdR = new TH1F("TF_ZLL_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_TT_DiJetdR = new TH1F("TF_TT_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_W3J_DiJetdR = new TH1F("TF_W3J_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_W2J_DiJetdR = new TH1F("TF_W2J_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_W1J_DiJetdR = new TH1F("TF_W1J_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

//TH1F* //TF_TTZ_DiJetdR = new TH1F("//TF_TTZ_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

//TH1F* //TF_WW_DiJetdR = new TH1F("//TF_WW_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

//TH1F* //TF_WZ_DiJetdR = new TH1F("//TF_WZ_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_LW200_DiJetdR = new TH1F("TF_LW200_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

//TH1F* //TF_LW300_DiJetdR = new TH1F("//TF_LW300_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

//TH1F* TF_LW400_DiJetdR = new TH1F("TF_LW400_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

//TH1F* TF_LW500_DiJetdR = new TH1F("TF_LW500_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_dataRunB_BJetPt = new TH1F("TF_dataRunB_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_dataRunC_BJetPt  = new TH1F("TF_dataRunC_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_ZLL_BJetPt = new TH1F("TF_ZLL_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_TT_BJetPt = new TH1F("TF_TT_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_W3J_BJetPt = new TH1F("TF_W3J_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_W2J_BJetPt = new TH1F("TF_W2J_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_W1J_BJetPt = new TH1F("TF_W1J_BJetPt","TF Most energetic Jet pt",100,0,250);

//TH1F* //TF_TTZ_BJetPt = new TH1F("//TF_TTZ_BJetPt","TF Most energetic Jet pt",100,0,250);

//TH1F* //TF_WW_BJetPt = new TH1F("//TF_WW_BJetPt","TF Most energetic Jet pt",100,0,250);

//TH1F* //TF_WZ_BJetPt = new TH1F("//TF_WZ_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_LW200_BJetPt = new TH1F("TF_LW200_BJetPt","TF Most energetic Jet pt",100,0,250);

//TH1F* //TF_LW300_BJetPt = new TH1F("//TF_LW300_BJetPt","TF Most energetic Jet pt",100,0,250);

//TH1F* TF_LW400_BJetPt = new TH1F("TF_LW400_BJetPt","TF Most energetic Jet pt",100,0,250);

//TH1F* TF_LW500_BJetPt = new TH1F("TF_LW500_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_dataRunB_SBJetPt = new TH1F("TF_dataRunB_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_dataRunC_SBJetPt  = new TH1F("TF_dataRunC_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_ZLL_SBJetPt = new TH1F("TF_ZLL_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_TT_SBJetPt = new TH1F("TF_TT_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_W3J_SBJetPt = new TH1F("TF_W3J_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_W2J_SBJetPt = new TH1F("TF_W2J_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_W1J_SBJetPt = new TH1F("TF_W1J_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

//TH1F* //TF_TTZ_SBJetPt = new TH1F("//TF_TTZ_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

//TH1F* //TF_WW_SBJetPt = new TH1F("//TF_WW_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

//TH1F* //TF_WZ_SBJetPt = new TH1F("//TF_WZ_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_LW200_SBJetPt = new TH1F("TF_LW200_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

//TH1F* //TF_LW300_SBJetPt = new TH1F("//TF_LW300_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

//TH1F* TF_LW400_SBJetPt = new TH1F("TF_LW400_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

//TH1F* TF_LW500_SBJetPt = new TH1F("TF_LW500_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_dataRunB_NJet = new TH1F("TF_dataRunB_NJet","TF Number of Jets",20,0,20);

TH1F* TF_dataRunC_NJet  = new TH1F("TF_dataRunC_NJet","TF Number of Jets",20,0,20);

TH1F* TF_ZLL_NJet = new TH1F("TF_ZLL_NJet","TF Number of Jets",20,0,20);

TH1F* TF_TT_NJet = new TH1F("TF_TT_NJet","TF Number of Jets",20,0,20);

TH1F* TF_W3J_NJet = new TH1F("TF_W3J_NJet","TF Number of Jets",20,0,20);

TH1F* TF_W2J_NJet = new TH1F("TF_W2J_NJet","TF Number of Jets",20,0,20);

TH1F* TF_W1J_NJet = new TH1F("TF_W1J_NJet","TF Number of Jets",20,0,20);

//TH1F* //TF_TTZ_NJet = new TH1F("//TF_TTZ_NJet","TF Number of Jets",20,0,20);

//TH1F* //TF_WW_NJet = new TH1F("//TF_WW_NJet","TF Number of Jets",20,0,20);

//TH1F* //TF_WZ_NJet = new TH1F("//TF_WZ_NJet","TF Number of Jets",20,0,20);

TH1F* TF_LW200_NJet = new TH1F("TF_LW200_NJet","TF Number of Jets",20,0,20);

//TH1F* //TF_LW300_NJet = new TH1F("//TF_LW300_NJet","TF Number of Jets",20,0,20);

//TH1F* TF_LW400_NJet = new TH1F("TF_LW400_NJet","TF Number of Jets",20,0,20);

//TH1F* TF_LW500_NJet = new TH1F("TF_LW500_NJet","TF Number of Jets",20,0,20);

TH1F* TF_dataRunB_NEle = new TH1F("TF_dataRunB_NEle","TF Number of electrons",20,0,20);

TH1F* TF_dataRunC_NEle  = new TH1F("TF_dataRunC_NEle","TF Number of electrons",20,0,20);

TH1F* TF_ZLL_NEle = new TH1F("TF_ZLL_NEle","TF Number of electrons",20,0,20);

TH1F* TF_TT_NEle = new TH1F("TF_TT_NEle","TF Number of electrons",20,0,20);

TH1F* TF_W3J_NEle = new TH1F("TF_W3J_NEle","TF Number of electrons",20,0,20);

TH1F* TF_W2J_NEle = new TH1F("TF_W2J_NEle","TF Number of electrons",20,0,20);

TH1F* TF_W1J_NEle = new TH1F("TF_W1J_NEle","TF Number of electrons",20,0,20);

//TH1F* //TF_TTZ_NEle = new TH1F("//TF_TTZ_NEle","TF Number of electrons",20,0,20);

//TH1F* //TF_WW_NEle = new TH1F("//TF_WW_NEle","TF Number of electrons",20,0,20);

//TH1F* //TF_WZ_NEle = new TH1F("//TF_WZ_NEle","TF Number of electrons",20,0,20);

TH1F* TF_LW200_NEle = new TH1F("TF_LW200_NEle","TF Number of electrons",20,0,20);

//TH1F* //TF_LW300_NEle = new TH1F("//TF_LW300_NEle","TF Number of electrons",20,0,20);

//TH1F* TF_LW400_NEle = new TH1F("TF_LW400_NEle","TF Number of electrons",20,0,20);

//TH1F* TF_LW500_NEle = new TH1F("TF_LW500_NEle","NF Number of electrons",20,0,20);

//////////////////////////////////////Trigg object////////////////////////////////////////
TH1F* TO_dataRunB_npv = new TH1F("TO_dataRunB_npv","TO Number of primary vertices",25,5,30);

TH1F* TO_dataRunC_npv  = new TH1F("TO_dataRunC_npv","TO Number of primary vertices",25,5,30);

TH1F* TO_ZLL_npv = new TH1F("TO_ZLL_npv","TO Number of primary vertices",25,5,30);

TH1F* TO_TT_npv = new TH1F("TO_TT_npv","TO Number of primary vertices",25,5,30);

TH1F* TO_W3J_npv = new TH1F("TO_W3J_npv","TO Number of primary vertices",25,5,30);

TH1F* TO_W2J_npv = new TH1F("TO_W2J_npv","TO Number of primary vertices",25,5,30);

TH1F* TO_W1J_npv = new TH1F("TO_W1J_npv","TO Number of primary vertices",25,5,30);

//TH1F* //TO_TTZ_npv = new TH1F("//TO_TTZ_npv","TO Number of primary vertices",25,5,30);

//TH1F* //TO_WW_npv = new TH1F("//TO_WW_npv","TO Number of primary vertices",25,5,30);

//TH1F* TO_WZ_npv = new TH1F("////TO_WZ_npv","TO Number of primary vertices",25,5,30);

TH1F* TO_LW200_npv = new TH1F("TO_LW200_npv","TO Number of primary vertices",25,5,30);

//TH1F* //TO_LW300_npv = new TH1F("//TO_LW300_npv","TO Number of primary vertices",25,5,30);

//TH1F* TO_LW400_npv = new TH1F("TO_LW400_npv","TO Number of primary vertices",25,5,30);

//TH1F* TO_LW500_npv = new TH1F("TO_LW500_npv","TO Number of primary vertices",25,5,30);

TH1F* TO_dataRunB_nsv = new TH1F("TO_dataRunB_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_dataRunC_nsv  = new TH1F("TO_dataRunC_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_ZLL_nsv = new TH1F("TO_ZLL_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_TT_nsv = new TH1F("TO_TT_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_W3J_nsv = new TH1F("TO_W3J_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_W2J_nsv = new TH1F("TO_W2J_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_W1J_nsv = new TH1F("TO_W1J_nsv","TO Number of secondary vertices",20,0,2000);

//TH1F* //TO_TTZ_nsv = new TH1F("//TO_TTZ_nsv","TO Number of secondary vertices",20,0,2000);

//TH1F* //TO_WW_nsv = new TH1F("//TO_WW_nsv","TO Number of secondary vertices",20,0,2000);

//TH1F* TO_WZ_nsv = new TH1F("////TO_WZ_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_LW200_nsv = new TH1F("TO_LW200_nsv","TO Number of secondary vertices",20,0,2000);

//TH1F* //TO_LW300_nsv = new TH1F("//TO_LW300_nsv","TO Number of secondary vertices",20,0,2000);

//TH1F* TO_LW400_nsv = new TH1F("TO_LW400_nsv","TO Number of secondary vertices",20,0,2000);

//TH1F* TO_LW500_nsv = new TH1F("TO_LW500_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_dataRunB_svd = new TH1F("TO_dataRunB_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_dataRunC_svd  = new TH1F("TO_dataRunC_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_ZLL_svd = new TH1F("TO_ZLL_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_TT_svd = new TH1F("TO_TT_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_W3J_svd = new TH1F("TO_W3J_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_W2J_svd = new TH1F("TO_W2J_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_W1J_svd = new TH1F("TO_W1J_svd","TO secondary vertex displacement",100,0,1);

//TH1F* //TO_TTZ_svd = new TH1F("//TO_TTZ_svd","TO secondary vertex displacement",100,0,1);

//TH1F* //TO_WW_svd = new TH1F("//TO_WW_svd","TO secondary vertex displacement",100,0,1);

//TH1F* TO_WZ_svd = new TH1F("////TO_WZ_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_LW200_svd = new TH1F("TO_LW200_svd","TO secondary vertex displacement",100,0,1);

//TH1F* //TO_LW300_svd = new TH1F("//TO_LW300_svd","TO secondary vertex displacement",100,0,1);

//TH1F* TO_LW400_svd = new TH1F("TO_LW400_svd","TO secondary vertex displacement",100,0,1);

//TH1F* TO_LW500_svd = new TH1F("TO_LW500_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_dataRunB_JetMass = new TH1F("TO_dataRunB_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_dataRunC_JetMass  = new TH1F("TO_dataRunC_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_ZLL_JetMass = new TH1F("TO_ZLL_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_TT_JetMass = new TH1F("TO_TT_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_W3J_JetMass = new TH1F("TO_W3J_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_W2J_JetMass = new TH1F("TO_W2J_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_W1J_JetMass = new TH1F("TO_W1J_JetMass","TO Invariant mass from DiJets",100,0,400);

//TH1F* //TO_TTZ_JetMass = new TH1F("//TO_TTZ_JetMass","TO Invariant mass from DiJets",100,0,400);

//TH1F* //TO_WW_JetMass = new TH1F("//TO_WW_JetMass","TO Invariant mass from DiJets",100,0,400);

//TH1F* TO_WZ_JetMass = new TH1F("////TO_WZ_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_LW200_JetMass = new TH1F("TO_LW200_JetMass","TO Invariant mass from DiJets",100,0,400);

//TH1F* //TO_LW300_JetMass = new TH1F("//TO_LW300_JetMass","TO Invariant mass from DiJets",100,0,400);

//TH1F* TO_LW400_JetMass = new TH1F("TO_LW400_JetMass","TO Invariant mass from DiJets",100,0,400);

//TH1F* TO_LW500_JetMass = new TH1F("TO_LW500_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_dataRunB_LWMass = new TH1F("TO_dataRunB_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_dataRunC_LWMass  = new TH1F("TO_dataRunC_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_ZLL_LWMass = new TH1F("TO_ZLL_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_TT_LWMass = new TH1F("TO_TT_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_W3J_LWMass = new TH1F("TO_W3J_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_W2J_LWMass = new TH1F("TO_W2J_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_W1J_LWMass = new TH1F("TO_W1J_LWMass","TO Invariant mass from LW",100,0,400);

//TH1F* //TO_TTZ_LWMass = new TH1F("//TO_TTZ_LWMass","TO Invariant mass from LW",100,0,400);

//TH1F* //TO_WW_LWMass = new TH1F("//TO_WW_LWMass","TO Invariant mass from LW",100,0,400);

//TH1F* TO_WZ_LWMass = new TH1F("////TO_WZ_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_LW200_LWMass = new TH1F("TO_LW200_LWMass","TO Invariant mass from LW",100,0,400);

//TH1F* //TO_LW300_LWMass = new TH1F("//TO_LW300_LWMass","TO Invariant mass from LW",100,0,400);

//TH1F* TO_LW400_LWMass = new TH1F("TO_LW400_LWMass","TO Invariant mass from LW",100,0,400);

//TH1F* TO_LW500_LWMass = new TH1F("TO_LW500_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_dataRunB_Elept = new TH1F("TO_dataRunB_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_dataRunC_Elept  = new TH1F("TO_dataRunC_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_ZLL_Elept = new TH1F("TO_ZLL_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_TT_Elept = new TH1F("TO_TT_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_W3J_Elept = new TH1F("TO_W3J_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_W2J_Elept = new TH1F("TO_W2J_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_W1J_Elept = new TH1F("TO_W1J_Elept","TO Electron pt distribution",100,0,200);

//TH1F* //TO_TTZ_Elept = new TH1F("//TO_TTZ_Elept","TO Electron pt distribution",100,0,200);

//TH1F* //TO_WW_Elept = new TH1F("//TO_WW_Elept","TO Electron pt distribution",100,0,200);

//TH1F* TO_WZ_Elept = new TH1F("////TO_WZ_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_LW200_Elept = new TH1F("TO_LW200_Elept","TO Electron pt distribution",100,0,200);

//TH1F* //TO_LW300_Elept = new TH1F("//TO_LW300_Elept","TO Electron pt distribution",100,0,200);

//TH1F* TO_LW400_Elept = new TH1F("TO_LW400_Elept","TO Electron pt distribution",100,0,200);

//TH1F* TO_LW500_Elept = new TH1F("TO_LW500_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_dataRunB_DieledR = new TH1F("TO_dataRunB_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_dataRunC_DieledR  = new TH1F("TO_dataRunC_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_ZLL_DieledR = new TH1F("TO_ZLL_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_TT_DieledR = new TH1F("TO_TT_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_W3J_DieledR = new TH1F("TO_W3J_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_W2J_DieledR = new TH1F("TO_W2J_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_W1J_DieledR = new TH1F("TO_W1J_DieledR","TO delta R separation between electrons",100,0,8);

//TH1F* //TO_TTZ_DieledR = new TH1F("//TO_TTZ_DieledR","TO delta R separation between electrons",100,0,8);

//TH1F* //TO_WW_DieledR = new TH1F("//TO_WW_DieledR","TO delta R separation between electrons",100,0,8);

//TH1F* TO_WZ_DieledR = new TH1F("////TO_WZ_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_LW200_DieledR = new TH1F("TO_LW200_DieledR","TO delta R separation between electrons",100,0,8);

//TH1F* //TO_LW300_DieledR = new TH1F("//TO_LW300_DieledR","TO delta R separation between electrons",100,0,8);

//TH1F* TO_LW400_DieledR = new TH1F("TO_LW400_DieledR","TO delta R separation between electrons",100,0,8);

//TH1F* TO_LW500_DieledR = new TH1F("TO_LW500_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_dataRunB_LWdR = new TH1F("TO_dataRunB_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_dataRunC_LWdR  = new TH1F("TO_dataRunC_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_ZLL_LWdR = new TH1F("TO_ZLL_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_TT_LWdR = new TH1F("TO_TT_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_W3J_LWdR = new TH1F("TO_W3J_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_W2J_LWdR = new TH1F("TO_W2J_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_W1J_LWdR = new TH1F("TO_W1J_LWdR","TO delta R separation between electrons and jets",100,0,8);

//TH1F* //TO_TTZ_LWdR = new TH1F("//TO_TTZ_LWdR","TO delta R separation between electrons and jets",100,0,8);

//TH1F* //TO_WW_LWdR = new TH1F("//TO_WW_LWdR","TO delta R separation between electrons and jets",100,0,8);

//TH1F* TO_WZ_LWdR = new TH1F("////TO_WZ_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_LW200_LWdR = new TH1F("TO_LW200_LWdR","TO delta R separation between electrons and jets",100,0,8);

//TH1F* //TO_LW300_LWdR = new TH1F("//TO_LW300_LWdR","TO delta R separation between electrons and jets",100,0,8);

//TH1F* TO_LW400_LWdR = new TH1F("TO_LW400_LWdR","TO delta R separation between electrons and jets",100,0,8);

//TH1F* TO_LW500_LWdR = new TH1F("TO_LW500_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_dataRunB_DiJetdR = new TH1F("TO_dataRunB_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_dataRunC_DiJetdR  = new TH1F("TO_dataRunC_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_ZLL_DiJetdR = new TH1F("TO_ZLL_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_TT_DiJetdR = new TH1F("TO_TT_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_W3J_DiJetdR = new TH1F("TO_W3J_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_W2J_DiJetdR = new TH1F("TO_W2J_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_W1J_DiJetdR = new TH1F("TO_W1J_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

//TH1F* //TO_TTZ_DiJetdR = new TH1F("//TO_TTZ_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

//TH1F* //TO_WW_DiJetdR = new TH1F("//TO_WW_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

//TH1F* TO_WZ_DiJetdR = new TH1F("////TO_WZ_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_LW200_DiJetdR = new TH1F("TO_LW200_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

//TH1F* //TO_LW300_DiJetdR = new TH1F("//TO_LW300_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

//TH1F* TO_LW400_DiJetdR = new TH1F("TO_LW400_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

//TH1F* TO_LW500_DiJetdR = new TH1F("TO_LW500_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_dataRunB_BJetPt = new TH1F("TO_dataRunB_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_dataRunC_BJetPt  = new TH1F("TO_dataRunC_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_ZLL_BJetPt = new TH1F("TO_ZLL_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_TT_BJetPt = new TH1F("TO_TT_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_W3J_BJetPt = new TH1F("TO_W3J_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_W2J_BJetPt = new TH1F("TO_W2J_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_W1J_BJetPt = new TH1F("TO_W1J_BJetPt","TO Most energetic Jet pt",100,0,250);

//TH1F* //TO_TTZ_BJetPt = new TH1F("//TO_TTZ_BJetPt","TO Most energetic Jet pt",100,0,250);

//TH1F* //TO_WW_BJetPt = new TH1F("//TO_WW_BJetPt","TO Most energetic Jet pt",100,0,250);

//TH1F* TO_WZ_BJetPt = new TH1F("////TO_WZ_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_LW200_BJetPt = new TH1F("TO_LW200_BJetPt","TO Most energetic Jet pt",100,0,250);

//TH1F* //TO_LW300_BJetPt = new TH1F("//TO_LW300_BJetPt","TO Most energetic Jet pt",100,0,250);

//TH1F* TO_LW400_BJetPt = new TH1F("TO_LW400_BJetPt","TO Most energetic Jet pt",100,0,250);

//TH1F* TO_LW500_BJetPt = new TH1F("TO_LW500_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_dataRunB_SBJetPt = new TH1F("TO_dataRunB_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_dataRunC_SBJetPt  = new TH1F("TO_dataRunC_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_ZLL_SBJetPt = new TH1F("TO_ZLL_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_TT_SBJetPt = new TH1F("TO_TT_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_W3J_SBJetPt = new TH1F("TO_W3J_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_W2J_SBJetPt = new TH1F("TO_W2J_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_W1J_SBJetPt = new TH1F("TO_W1J_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

//TH1F* //TO_TTZ_SBJetPt = new TH1F("//TO_TTZ_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

//TH1F* //TO_WW_SBJetPt = new TH1F("//TO_WW_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

//TH1F* TO_WZ_SBJetPt = new TH1F("////TO_WZ_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_LW200_SBJetPt = new TH1F("TO_LW200_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

//TH1F* //TO_LW300_SBJetPt = new TH1F("//TO_LW300_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

//TH1F* TO_LW400_SBJetPt = new TH1F("TO_LW400_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

//TH1F* TO_LW500_SBJetPt = new TH1F("TO_LW500_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_dataRunB_NJet = new TH1F("TO_dataRunB_NJet","TO Number of Jets",20,0,20);

TH1F* TO_dataRunC_NJet  = new TH1F("TO_dataRunC_NJet","TO Number of Jets",20,0,20);

TH1F* TO_ZLL_NJet = new TH1F("TO_ZLL_NJet","TO Number of Jets",20,0,20);

TH1F* TO_TT_NJet = new TH1F("TO_TT_NJet","TO Number of Jets",20,0,20);

TH1F* TO_W3J_NJet = new TH1F("TO_W3J_NJet","TO Number of Jets",20,0,20);

TH1F* TO_W2J_NJet = new TH1F("TO_W2J_NJet","TO Number of Jets",20,0,20);

TH1F* TO_W1J_NJet = new TH1F("TO_W1J_NJet","TO Number of Jets",20,0,20);

//TH1F* //TO_TTZ_NJet = new TH1F("//TO_TTZ_NJet","TO Number of Jets",20,0,20);

//TH1F* //TO_WW_NJet = new TH1F("//TO_WW_NJet","TO Number of Jets",20,0,20);

//TH1F* TO_WZ_NJet = new TH1F("////TO_WZ_NJet","TO Number of Jets",20,0,20);

TH1F* TO_LW200_NJet = new TH1F("TO_LW200_NJet","TO Number of Jets",20,0,20);

//TH1F* //TO_LW300_NJet = new TH1F("//TO_LW300_NJet","TO Number of Jets",20,0,20);

//TH1F* TO_LW400_NJet = new TH1F("TO_LW400_NJet","TO Number of Jets",20,0,20);

//TH1F* TO_LW500_NJet = new TH1F("TO_LW500_NJet","TO Number of Jets",20,0,20);

TH1F* TO_dataRunB_NEle = new TH1F("TO_dataRunB_NEle","TO Number of electrons",20,0,20);

TH1F* TO_dataRunC_NEle  = new TH1F("TO_dataRunC_NEle","TO Number of electrons",20,0,20);

TH1F* TO_ZLL_NEle = new TH1F("TO_ZLL_NEle","TO Number of electrons",20,0,20);

TH1F* TO_TT_NEle = new TH1F("TO_TT_NEle","TO Number of electrons",20,0,20);

TH1F* TO_W3J_NEle = new TH1F("TO_W3J_NEle","TO Number of electrons",20,0,20);

TH1F* TO_W2J_NEle = new TH1F("TO_W2J_NEle","TO Number of electrons",20,0,20);

TH1F* TO_W1J_NEle = new TH1F("TO_W1J_NEle","TO Number of electrons",20,0,20);

//TH1F* //TO_TTZ_NEle = new TH1F("//TO_TTZ_NEle","TO Number of electrons",20,0,20);

//TH1F* //TO_WW_NEle = new TH1F("//TO_WW_NEle","TO Number of electrons",20,0,20);

//TH1F* TO_WZ_NEle = new TH1F("////TO_WZ_NEle","TO Number of electrons",20,0,20);

TH1F* TO_LW200_NEle = new TH1F("TO_LW200_NEle","TO Number of electrons",20,0,20);

//TH1F* //TO_LW300_NEle = new TH1F("//TO_LW300_NEle","TO Number of electrons",20,0,20);

//TH1F* TO_LW400_NEle = new TH1F("TO_LW400_NEle","TO Number of electrons",20,0,20);

//TH1F* TO_LW500_NEle = new TH1F("TO_LW500_NEle","TO Number of electrons",20,0,20);


//////////////////////////////////////High quality////////////////////////////////////////
TH1F* HQ_dataRunB_npv = new TH1F("HQ_dataRunB_npv","HQ Number of primary vertices",25,5,30);

TH1F* HQ_dataRunC_npv  = new TH1F("HQ_dataRunC_npv","HQ Number of primary vertices",25,5,30);

TH1F* HQ_ZLL_npv = new TH1F("HQ_ZLL_npv","HQ Number of primary vertices",25,5,30);

TH1F* HQ_TT_npv = new TH1F("HQ_TT_npv","HQ Number of primary vertices",25,5,30);

TH1F* HQ_W3J_npv = new TH1F("HQ_W3J_npv","HQ Number of primary vertices",25,5,30);

TH1F* HQ_W2J_npv = new TH1F("HQ_W2J_npv","HQ Number of primary vertices",25,5,30);

TH1F* HQ_W1J_npv = new TH1F("HQ_W1J_npv","HQ Number of primary vertices",25,5,30);

//TH1F* ////HQ_TTZ_npv = new TH1F("////HQ_TTZ_npv","HQ Number of primary vertices",25,5,30);

//TH1F* //HQ_WW_npv = new TH1F("//HQ_WW_npv","HQ Number of primary vertices",25,5,30);

//TH1F* //HQ_WZ_npv = new TH1F("//HQ_WZ_npv","HQ Number of primary vertices",25,5,30);

TH1F* HQ_LW200_npv = new TH1F("HQ_LW200_npv","HQ Number of primary vertices",25,5,30);

//TH1F* //HQ_LW300_npv = new TH1F("//HQ_LW300_npv","HQ Number of primary vertices",25,5,30);

//TH1F* HQ_LW400_npv = new TH1F("HQ_LW400_npv","HQ Number of primary vertices",25,5,30);

//TH1F* HQ_LW500_npv = new TH1F("HQ_LW500_npv","HQ Number of primary vertices",25,5,30);

TH1F* HQ_dataRunB_nsv = new TH1F("HQ_dataRunB_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_dataRunC_nsv  = new TH1F("HQ_dataRunC_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_ZLL_nsv = new TH1F("HQ_ZLL_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_TT_nsv = new TH1F("HQ_TT_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_W3J_nsv = new TH1F("HQ_W3J_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_W2J_nsv = new TH1F("HQ_W2J_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_W1J_nsv = new TH1F("HQ_W1J_nsv","HQ Number of secondary vertices",20,0,2000);

//TH1F* ////HQ_TTZ_nsv = new TH1F("////HQ_TTZ_nsv","HQ Number of secondary vertices",20,0,2000);

//TH1F* //HQ_WW_nsv = new TH1F("//HQ_WW_nsv","HQ Number of secondary vertices",20,0,2000);

//TH1F* //HQ_WZ_nsv = new TH1F("//HQ_WZ_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_LW200_nsv = new TH1F("HQ_LW200_nsv","HQ Number of secondary vertices",20,0,2000);

//TH1F* //HQ_LW300_nsv = new TH1F("//HQ_LW300_nsv","HQ Number of secondary vertices",20,0,2000);

//TH1F* HQ_LW400_nsv = new TH1F("HQ_LW400_nsv","HQ Number of secondary vertices",20,0,2000);

//TH1F* HQ_LW500_nsv = new TH1F("HQ_LW500_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_dataRunB_svd = new TH1F("HQ_dataRunB_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_dataRunC_svd  = new TH1F("HQ_dataRunC_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_ZLL_svd = new TH1F("HQ_ZLL_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_TT_svd = new TH1F("HQ_TT_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_W3J_svd = new TH1F("HQ_W3J_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_W2J_svd = new TH1F("HQ_W2J_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_W1J_svd = new TH1F("HQ_W1J_svd","HQ secondary vertex displacement",100,0,1);

//TH1F* ////HQ_TTZ_svd = new TH1F("////HQ_TTZ_svd","HQ secondary vertex displacement",100,0,1);

//TH1F* //HQ_WW_svd = new TH1F("//HQ_WW_svd","HQ secondary vertex displacement",100,0,1);

//TH1F* //HQ_WZ_svd = new TH1F("//HQ_WZ_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_LW200_svd = new TH1F("HQ_LW200_svd","HQ secondary vertex displacement",100,0,1);

//TH1F* //HQ_LW300_svd = new TH1F("//HQ_LW300_svd","HQ secondary vertex displacement",100,0,1);

//TH1F* HQ_LW400_svd = new TH1F("HQ_LW400_svd","HQ secondary vertex displacement",100,0,1);

//TH1F* HQ_LW500_svd = new TH1F("HQ_LW500_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_dataRunB_JetMass = new TH1F("HQ_dataRunB_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_dataRunC_JetMass  = new TH1F("HQ_dataRunC_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_ZLL_JetMass = new TH1F("HQ_ZLL_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_TT_JetMass = new TH1F("HQ_TT_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_W3J_JetMass = new TH1F("HQ_W3J_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_W2J_JetMass = new TH1F("HQ_W2J_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_W1J_JetMass = new TH1F("HQ_W1J_JetMass","HQ Invariant mass from DiJets",100,0,400);

//TH1F* ////HQ_TTZ_JetMass = new TH1F("////HQ_TTZ_JetMass","HQ Invariant mass from DiJets",100,0,400);

//TH1F* //HQ_WW_JetMass = new TH1F("//HQ_WW_JetMass","HQ Invariant mass from DiJets",100,0,400);

//TH1F* //HQ_WZ_JetMass = new TH1F("//HQ_WZ_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_LW200_JetMass = new TH1F("HQ_LW200_JetMass","HQ Invariant mass from DiJets",100,0,400);

//TH1F* //HQ_LW300_JetMass = new TH1F("//HQ_LW300_JetMass","HQ Invariant mass from DiJets",100,0,400);

//TH1F* HQ_LW400_JetMass = new TH1F("HQ_LW400_JetMass","HQ Invariant mass from DiJets",100,0,400);

//TH1F* HQ_LW500_JetMass = new TH1F("HQ_LW500_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_dataRunB_LWMass = new TH1F("HQ_dataRunB_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_dataRunC_LWMass  = new TH1F("HQ_dataRunC_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_ZLL_LWMass = new TH1F("HQ_ZLL_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_TT_LWMass = new TH1F("HQ_TT_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_W3J_LWMass = new TH1F("HQ_W3J_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_W2J_LWMass = new TH1F("HQ_W2J_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_W1J_LWMass = new TH1F("HQ_W1J_LWMass","HQ Invariant mass from LW",100,0,400);

//TH1F* ////HQ_TTZ_LWMass = new TH1F("////HQ_TTZ_LWMass","HQ Invariant mass from LW",100,0,400);

//TH1F* //HQ_WW_LWMass = new TH1F("//HQ_WW_LWMass","HQ Invariant mass from LW",100,0,400);

//TH1F* //HQ_WZ_LWMass = new TH1F("//HQ_WZ_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_LW200_LWMass = new TH1F("HQ_LW200_LWMass","HQ Invariant mass from LW",100,0,400);

//TH1F* //HQ_LW300_LWMass = new TH1F("//HQ_LW300_LWMass","HQ Invariant mass from LW",100,0,400);

//TH1F* HQ_LW400_LWMass = new TH1F("HQ_LW400_LWMass","HQ Invariant mass from LW",100,0,400);

//TH1F* HQ_LW500_LWMass = new TH1F("HQ_LW500_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_dataRunB_Elept = new TH1F("HQ_dataRunB_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_dataRunC_Elept  = new TH1F("HQ_dataRunC_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_ZLL_Elept = new TH1F("HQ_ZLL_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_TT_Elept = new TH1F("HQ_TT_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_W3J_Elept = new TH1F("HQ_W3J_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_W2J_Elept = new TH1F("HQ_W2J_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_W1J_Elept = new TH1F("HQ_W1J_Elept","HQ Electron pt distribution",100,0,200);

//TH1F* ////HQ_TTZ_Elept = new TH1F("////HQ_TTZ_Elept","HQ Electron pt distribution",100,0,200);

//TH1F* //HQ_WW_Elept = new TH1F("//HQ_WW_Elept","HQ Electron pt distribution",100,0,200);

//TH1F* //HQ_WZ_Elept = new TH1F("//HQ_WZ_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_LW200_Elept = new TH1F("HQ_LW200_Elept","HQ Electron pt distribution",100,0,200);

//TH1F* //HQ_LW300_Elept = new TH1F("//HQ_LW300_Elept","HQ Electron pt distribution",100,0,200);

//TH1F* HQ_LW400_Elept = new TH1F("HQ_LW400_Elept","HQ Electron pt distribution",100,0,200);

//TH1F* HQ_LW500_Elept = new TH1F("HQ_LW500_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_dataRunB_DieledR = new TH1F("HQ_dataRunB_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_dataRunC_DieledR  = new TH1F("HQ_dataRunC_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_ZLL_DieledR = new TH1F("HQ_ZLL_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_TT_DieledR = new TH1F("HQ_TT_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_W3J_DieledR = new TH1F("HQ_W3J_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_W2J_DieledR = new TH1F("HQ_W2J_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_W1J_DieledR = new TH1F("HQ_W1J_DieledR","HQ delta R separation between electrons",100,0,8);

//TH1F* ////HQ_TTZ_DieledR = new TH1F("////HQ_TTZ_DieledR","HQ delta R separation between electrons",100,0,8);

//TH1F* //HQ_WW_DieledR = new TH1F("//HQ_WW_DieledR","HQ delta R separation between electrons",100,0,8);

//TH1F* //HQ_WZ_DieledR = new TH1F("//HQ_WZ_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_LW200_DieledR = new TH1F("HQ_LW200_DieledR","HQ delta R separation between electrons",100,0,8);

//TH1F* //HQ_LW300_DieledR = new TH1F("//HQ_LW300_DieledR","HQ delta R separation between electrons",100,0,8);

//TH1F* HQ_LW400_DieledR = new TH1F("HQ_LW400_DieledR","HQ delta R separation between electrons",100,0,8);

//TH1F* HQ_LW500_DieledR = new TH1F("HQ_LW500_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_dataRunB_LWdR = new TH1F("HQ_dataRunB_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_dataRunC_LWdR  = new TH1F("HQ_dataRunC_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_ZLL_LWdR = new TH1F("HQ_ZLL_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_TT_LWdR = new TH1F("HQ_TT_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_W3J_LWdR = new TH1F("HQ_W3J_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_W2J_LWdR = new TH1F("HQ_W2J_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_W1J_LWdR = new TH1F("HQ_W1J_LWdR","HQ delta R separation between electrons and jets",100,0,8);

//TH1F* ////HQ_TTZ_LWdR = new TH1F("////HQ_TTZ_LWdR","HQ delta R separation between electrons and jets",100,0,8);

//TH1F* //HQ_WW_LWdR = new TH1F("//HQ_WW_LWdR","HQ delta R separation between electrons and jets",100,0,8);

//TH1F* //HQ_WZ_LWdR = new TH1F("//HQ_WZ_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_LW200_LWdR = new TH1F("HQ_LW200_LWdR","HQ delta R separation between electrons and jets",100,0,8);

//TH1F* //HQ_LW300_LWdR = new TH1F("//HQ_LW300_LWdR","HQ delta R separation between electrons and jets",100,0,8);

//TH1F* HQ_LW400_LWdR = new TH1F("HQ_LW400_LWdR","HQ delta R separation between electrons and jets",100,0,8);

//TH1F* HQ_LW500_LWdR = new TH1F("HQ_LW500_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_dataRunB_DiJetdR = new TH1F("HQ_dataRunB_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_dataRunC_DiJetdR  = new TH1F("HQ_dataRunC_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_ZLL_DiJetdR = new TH1F("HQ_ZLL_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_TT_DiJetdR = new TH1F("HQ_TT_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_W3J_DiJetdR = new TH1F("HQ_W3J_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_W2J_DiJetdR = new TH1F("HQ_W2J_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_W1J_DiJetdR = new TH1F("HQ_W1J_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

//TH1F* ////HQ_TTZ_DiJetdR = new TH1F("////HQ_TTZ_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

//TH1F* //HQ_WW_DiJetdR = new TH1F("//HQ_WW_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

//TH1F* //HQ_WZ_DiJetdR = new TH1F("//HQ_WZ_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_LW200_DiJetdR = new TH1F("HQ_LW200_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

//TH1F* //HQ_LW300_DiJetdR = new TH1F("//HQ_LW300_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

//TH1F* HQ_LW400_DiJetdR = new TH1F("HQ_LW400_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

//TH1F* HQ_LW500_DiJetdR = new TH1F("HQ_LW500_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_dataRunB_BJetPt = new TH1F("HQ_dataRunB_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_dataRunC_BJetPt  = new TH1F("HQ_dataRunC_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_ZLL_BJetPt = new TH1F("HQ_ZLL_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_TT_BJetPt = new TH1F("HQ_TT_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_W3J_BJetPt = new TH1F("HQ_W3J_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_W2J_BJetPt = new TH1F("HQ_W2J_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_W1J_BJetPt = new TH1F("HQ_W1J_BJetPt","HQ Most energetic Jet pt",100,0,250);

//TH1F* ////HQ_TTZ_BJetPt = new TH1F("////HQ_TTZ_BJetPt","HQ Most energetic Jet pt",100,0,250);

//TH1F* //HQ_WW_BJetPt = new TH1F("//HQ_WW_BJetPt","HQ Most energetic Jet pt",100,0,250);

//TH1F* //HQ_WZ_BJetPt = new TH1F("//HQ_WZ_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_LW200_BJetPt = new TH1F("HQ_LW200_BJetPt","HQ Most energetic Jet pt",100,0,250);

//TH1F* //HQ_LW300_BJetPt = new TH1F("//HQ_LW300_BJetPt","HQ Most energetic Jet pt",100,0,250);

//TH1F* HQ_LW400_BJetPt = new TH1F("HQ_LW400_BJetPt","HQ Most energetic Jet pt",100,0,250);

//TH1F* HQ_LW500_BJetPt = new TH1F("HQ_LW500_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_dataRunB_SBJetPt = new TH1F("HQ_dataRunB_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_dataRunC_SBJetPt  = new TH1F("HQ_dataRunC_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_ZLL_SBJetPt = new TH1F("HQ_ZLL_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_TT_SBJetPt = new TH1F("HQ_TT_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_W3J_SBJetPt = new TH1F("HQ_W3J_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_W2J_SBJetPt = new TH1F("HQ_W2J_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_W1J_SBJetPt = new TH1F("HQ_W1J_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

//TH1F* ////HQ_TTZ_SBJetPt = new TH1F("////HQ_TTZ_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

//TH1F* //HQ_WW_SBJetPt = new TH1F("//HQ_WW_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

//TH1F* //HQ_WZ_SBJetPt = new TH1F("//HQ_WZ_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_LW200_SBJetPt = new TH1F("HQ_LW200_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

//TH1F* //HQ_LW300_SBJetPt = new TH1F("//HQ_LW300_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

//TH1F* HQ_LW400_SBJetPt = new TH1F("HQ_LW400_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

//TH1F* HQ_LW500_SBJetPt = new TH1F("HQ_LW500_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_dataRunB_NJet = new TH1F("HQ_dataRunB_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_dataRunC_NJet  = new TH1F("HQ_dataRunC_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_ZLL_NJet = new TH1F("HQ_ZLL_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_TT_NJet = new TH1F("HQ_TT_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_W3J_NJet = new TH1F("HQ_W3J_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_W2J_NJet = new TH1F("HQ_W2J_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_W1J_NJet = new TH1F("HQ_W1J_NJet","HQ Number of Jets",20,0,20);

//TH1F* ////HQ_TTZ_NJet = new TH1F("////HQ_TTZ_NJet","HQ Number of Jets",20,0,20);

//TH1F* //HQ_WW_NJet = new TH1F("//HQ_WW_NJet","HQ Number of Jets",20,0,20);

//TH1F* //HQ_WZ_NJet = new TH1F("//HQ_WZ_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_LW200_NJet = new TH1F("HQ_LW200_NJet","HQ Number of Jets",20,0,20);

//TH1F* //HQ_LW300_NJet = new TH1F("//HQ_LW300_NJet","HQ Number of Jets",20,0,20);

//TH1F* HQ_LW400_NJet = new TH1F("HQ_LW400_NJet","HQ Number of Jets",20,0,20);

//TH1F* HQ_LW500_NJet = new TH1F("HQ_LW500_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_dataRunB_NEle = new TH1F("HQ_dataRunB_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_dataRunC_NEle  = new TH1F("HQ_dataRunC_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_ZLL_NEle = new TH1F("HQ_ZLL_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_TT_NEle = new TH1F("HQ_TT_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_W3J_NEle = new TH1F("HQ_W3J_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_W2J_NEle = new TH1F("HQ_W2J_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_W1J_NEle = new TH1F("HQ_W1J_NEle","HQ Number of electrons",20,0,20);

//TH1F* ////HQ_TTZ_NEle = new TH1F("////HQ_TTZ_NEle","HQ Number of electrons",20,0,20);

//TH1F* //HQ_WW_NEle = new TH1F("//HQ_WW_NEle","HQ Number of electrons",20,0,20);

//TH1F* //HQ_WZ_NEle = new TH1F("//HQ_WZ_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_LW200_NEle = new TH1F("HQ_LW200_NEle","HQ Number of electrons",20,0,20);

//TH1F* //HQ_LW300_NEle = new TH1F("//HQ_LW300_NEle","HQ Number of electrons",20,0,20);

//TH1F* HQ_LW400_NEle = new TH1F("HQ_LW400_NEle","HQ Number of electrons",20,0,20);

//TH1F* HQ_LW500_NEle = new TH1F("HQ_LW500_NEle","HQ Number of electrons",20,0,20);

//////////////////////////////////////Signal ////////////////////////////////////////
TH1F* SG_dataRunB_npv = new TH1F("SG_dataRunB_npv","SG Number of primary vertices",25,5,30);

TH1F* SG_dataRunC_npv  = new TH1F("SG_dataRunC_npv","SG Number of primary vertices",25,5,30);

TH1F* SG_ZLL_npv = new TH1F("SG_ZLL_npv","SG Number of primary vertices",25,5,30);

TH1F* SG_TT_npv = new TH1F("SG_TT_npv","SG Number of primary vertices",25,5,30);

TH1F* SG_W3J_npv = new TH1F("SG_W3J_npv","SG Number of primary vertices",25,5,30);

TH1F* SG_W2J_npv = new TH1F("SG_W2J_npv","SG Number of primary vertices",25,5,30);

TH1F* SG_W1J_npv = new TH1F("SG_W1J_npv","SG Number of primary vertices",25,5,30);

//TH1F* SG_TTZ_npv = new TH1F("SG_TTZ_npv","SG Number of primary vertices",25,5,30);

//TH1F* SG_WW_npv = new TH1F("SG_WW_npv","SG Number of primary vertices",25,5,30);

//TH1F* SG_WZ_npv = new TH1F("SG_WZ_npv","SG Number of primary vertices",25,5,30);

TH1F* SG_LW200_npv = new TH1F("SG_LW200_npv","SG Number of primary vertices",25,5,30);

//TH1F* SG_LW300_npv = new TH1F("SG_LW300_npv","SG Number of primary vertices",25,5,30);

//TH1F* SG_LW400_npv = new TH1F("SG_LW400_npv","SG Number of primary vertices",25,5,30);

//TH1F* SG_LW500_npv = new TH1F("SG_LW500_npv","SG Number of primary vertices",25,5,30);

TH1F* SG_dataRunB_nsv = new TH1F("SG_dataRunB_nsv","SG Number of secondary vertices",20,0,2000);

TH1F* SG_dataRunC_nsv  = new TH1F("SG_dataRunC_nsv","SG Number of secondary vertices",20,0,2000);

TH1F* SG_ZLL_nsv = new TH1F("SG_ZLL_nsv","SG Number of secondary vertices",20,0,2000);

TH1F* SG_TT_nsv = new TH1F("SG_TT_nsv","SG Number of secondary vertices",20,0,2000);

TH1F* SG_W3J_nsv = new TH1F("SG_W3J_nsv","SG Number of secondary vertices",20,0,2000);

TH1F* SG_W2J_nsv = new TH1F("SG_W2J_nsv","SG Number of secondary vertices",20,0,2000);

TH1F* SG_W1J_nsv = new TH1F("SG_W1J_nsv","SG Number of secondary vertices",20,0,2000);

//TH1F* SG_TTZ_nsv = new TH1F("SG_TTZ_nsv","SG Number of secondary vertices",20,0,2000);

//TH1F* SG_WW_nsv = new TH1F("SG_WW_nsv","SG Number of secondary vertices",20,0,2000);

//TH1F* SG_WZ_nsv = new TH1F("SG_WZ_nsv","SG Number of secondary vertices",20,0,2000);

TH1F* SG_LW200_nsv = new TH1F("SG_LW200_nsv","SG Number of secondary vertices",20,0,2000);

//TH1F* SG_LW300_nsv = new TH1F("SG_LW300_nsv","SG Number of secondary vertices",20,0,2000);

//TH1F* SG_LW400_nsv = new TH1F("SG_LW400_nsv","SG Number of secondary vertices",20,0,2000);

//TH1F* SG_LW500_nsv = new TH1F("SG_LW500_nsv","SG Number of secondary vertices",20,0,2000);

TH1F* SG_dataRunB_svd = new TH1F("SG_dataRunB_svd","SG secondary vertex displacement",100,0,1);

TH1F* SG_dataRunC_svd  = new TH1F("SG_dataRunC_svd","SG secondary vertex displacement",100,0,1);

TH1F* SG_ZLL_svd = new TH1F("SG_ZLL_svd","SG secondary vertex displacement",100,0,1);

TH1F* SG_TT_svd = new TH1F("SG_TT_svd","SG secondary vertex displacement",100,0,1);

TH1F* SG_W3J_svd = new TH1F("SG_W3J_svd","SG secondary vertex displacement",100,0,1);

TH1F* SG_W2J_svd = new TH1F("SG_W2J_svd","SG secondary vertex displacement",100,0,1);

TH1F* SG_W1J_svd = new TH1F("SG_W1J_svd","SG secondary vertex displacement",100,0,1);

//TH1F* SG_TTZ_svd = new TH1F("SG_TTZ_svd","SG secondary vertex displacement",100,0,1);

//TH1F* SG_WW_svd = new TH1F("SG_WW_svd","SG secondary vertex displacement",100,0,1);

//TH1F* SG_WZ_svd = new TH1F("SG_WZ_svd","SG secondary vertex displacement",100,0,1);

TH1F* SG_LW200_svd = new TH1F("SG_LW200_svd","SG secondary vertex displacement",100,0,1);

//TH1F* SG_LW300_svd = new TH1F("SG_LW300_svd","SG secondary vertex displacement",100,0,1);

//TH1F* SG_LW400_svd = new TH1F("SG_LW400_svd","SG secondary vertex displacement",100,0,1);

//TH1F* SG_LW500_svd = new TH1F("SG_LW500_svd","SG secondary vertex displacement",100,0,1);

TH1F* SG_dataRunB_JetMass = new TH1F("SG_dataRunB_JetMass","SG Invariant mass from DiJets",100,0,400);

TH1F* SG_dataRunC_JetMass  = new TH1F("SG_dataRunC_JetMass","SG Invariant mass from DiJets",100,0,400);

TH1F* SG_ZLL_JetMass = new TH1F("SG_ZLL_JetMass","SG Invariant mass from DiJets",100,0,400);

TH1F* SG_TT_JetMass = new TH1F("SG_TT_JetMass","SG Invariant mass from DiJets",100,0,400);

TH1F* SG_W3J_JetMass = new TH1F("SG_W3J_JetMass","SG Invariant mass from DiJets",100,0,400);

TH1F* SG_W2J_JetMass = new TH1F("SG_W2J_JetMass","SG Invariant mass from DiJets",100,0,400);

TH1F* SG_W1J_JetMass = new TH1F("SG_W1J_JetMass","SG Invariant mass from DiJets",100,0,400);

//TH1F* SG_TTZ_JetMass = new TH1F("SG_TTZ_JetMass","SG Invariant mass from DiJets",100,0,400);

//TH1F* SG_WW_JetMass = new TH1F("SG_WW_JetMass","SG Invariant mass from DiJets",100,0,400);

//TH1F* SG_WZ_JetMass = new TH1F("SG_WZ_JetMass","SG Invariant mass from DiJets",100,0,400);

TH1F* SG_LW200_JetMass = new TH1F("SG_LW200_JetMass","SG Invariant mass from DiJets",100,0,400);

//TH1F* SG_LW300_JetMass = new TH1F("SG_LW300_JetMass","SG Invariant mass from DiJets",100,0,400);

//TH1F* SG_LW400_JetMass = new TH1F("SG_LW400_JetMass","SG Invariant mass from DiJets",100,0,400);

//TH1F* SG_LW500_JetMass = new TH1F("SG_LW500_JetMass","SG Invariant mass from DiJets",100,0,400);

TH1F* SG_dataRunB_LWMass = new TH1F("SG_dataRunB_LWMass","SG Invariant mass from LW",100,0,400);

TH1F* SG_dataRunC_LWMass  = new TH1F("SG_dataRunC_LWMass","SG Invariant mass from LW",100,0,400);

TH1F* SG_ZLL_LWMass = new TH1F("SG_ZLL_LWMass","SG Invariant mass from LW",100,0,400);

TH1F* SG_TT_LWMass = new TH1F("SG_TT_LWMass","SG Invariant mass from LW",100,0,400);

TH1F* SG_W3J_LWMass = new TH1F("SG_W3J_LWMass","SG Invariant mass from LW",100,0,400);

TH1F* SG_W2J_LWMass = new TH1F("SG_W2J_LWMass","SG Invariant mass from LW",100,0,400);

TH1F* SG_W1J_LWMass = new TH1F("SG_W1J_LWMass","SG Invariant mass from LW",100,0,400);

//TH1F* SG_TTZ_LWMass = new TH1F("SG_TTZ_LWMass","SG Invariant mass from LW",100,0,400);

//TH1F* SG_WW_LWMass = new TH1F("SG_WW_LWMass","SG Invariant mass from LW",100,0,400);

//TH1F* SG_WZ_LWMass = new TH1F("SG_WZ_LWMass","SG Invariant mass from LW",100,0,400);

TH1F* SG_LW200_LWMass = new TH1F("SG_LW200_LWMass","SG Invariant mass from LW",100,0,400);

//TH1F* SG_LW300_LWMass = new TH1F("SG_LW300_LWMass","SG Invariant mass from LW",100,0,400);

//TH1F* SG_LW400_LWMass = new TH1F("SG_LW400_LWMass","SG Invariant mass from LW",100,0,400);

//TH1F* SG_LW500_LWMass = new TH1F("SG_LW500_LWMass","SG Invariant mass from LW",100,0,400);

TH1F* SG_dataRunB_Elept = new TH1F("SG_dataRunB_Elept","SG Electron pt distribution",100,0,200);

TH1F* SG_dataRunC_Elept  = new TH1F("SG_dataRunC_Elept","SG Electron pt distribution",100,0,200);

TH1F* SG_ZLL_Elept = new TH1F("SG_ZLL_Elept","SG Electron pt distribution",100,0,200);

TH1F* SG_TT_Elept = new TH1F("SG_TT_Elept","SG Electron pt distribution",100,0,200);

TH1F* SG_W3J_Elept = new TH1F("SG_W3J_Elept","SG Electron pt distribution",100,0,200);

TH1F* SG_W2J_Elept = new TH1F("SG_W2J_Elept","SG Electron pt distribution",100,0,200);

TH1F* SG_W1J_Elept = new TH1F("SG_W1J_Elept","SG Electron pt distribution",100,0,200);

//TH1F* SG_TTZ_Elept = new TH1F("SG_TTZ_Elept","SG Electron pt distribution",100,0,200);

//TH1F* SG_WW_Elept = new TH1F("SG_WW_Elept","SG Electron pt distribution",100,0,200);

//TH1F* SG_WZ_Elept = new TH1F("SG_WZ_Elept","SG Electron pt distribution",100,0,200);

TH1F* SG_LW200_Elept = new TH1F("SG_LW200_Elept","SG Electron pt distribution",100,0,200);

//TH1F* SG_LW300_Elept = new TH1F("SG_LW300_Elept","SG Electron pt distribution",100,0,200);

//TH1F* SG_LW400_Elept = new TH1F("SG_LW400_Elept","SG Electron pt distribution",100,0,200);

//TH1F* SG_LW500_Elept = new TH1F("SG_LW500_Elept","SG Electron pt distribution",100,0,200);

TH1F* SG_dataRunB_DieledR = new TH1F("SG_dataRunB_DieledR","SG delta R separation between electrons",100,0,8);

TH1F* SG_dataRunC_DieledR  = new TH1F("SG_dataRunC_DieledR","SG delta R separation between electrons",100,0,8);

TH1F* SG_ZLL_DieledR = new TH1F("SG_ZLL_DieledR","SG delta R separation between electrons",100,0,8);

TH1F* SG_TT_DieledR = new TH1F("SG_TT_DieledR","SG delta R separation between electrons",100,0,8);

TH1F* SG_W3J_DieledR = new TH1F("SG_W3J_DieledR","SG delta R separation between electrons",100,0,8);

TH1F* SG_W2J_DieledR = new TH1F("SG_W2J_DieledR","SG delta R separation between electrons",100,0,8);

TH1F* SG_W1J_DieledR = new TH1F("SG_W1J_DieledR","SG delta R separation between electrons",100,0,8);

//TH1F* SG_TTZ_DieledR = new TH1F("SG_TTZ_DieledR","SG delta R separation between electrons",100,0,8);

//TH1F* SG_WW_DieledR = new TH1F("SG_WW_DieledR","SG delta R separation between electrons",100,0,8);

//TH1F* SG_WZ_DieledR = new TH1F("SG_WZ_DieledR","SG delta R separation between electrons",100,0,8);

TH1F* SG_LW200_DieledR = new TH1F("SG_LW200_DieledR","SG delta R separation between electrons",100,0,8);

//TH1F* SG_LW300_DieledR = new TH1F("SG_LW300_DieledR","SG delta R separation between electrons",100,0,8);

//TH1F* SG_LW400_DieledR = new TH1F("SG_LW400_DieledR","SG delta R separation between electrons",100,0,8);

//TH1F* SG_LW500_DieledR = new TH1F("SG_LW500_DieledR","SG delta R separation between electrons",100,0,8);

TH1F* SG_dataRunB_LWdR = new TH1F("SG_dataRunB_LWdR","SG delta R separation between electrons and jets",100,0,8);

TH1F* SG_dataRunC_LWdR  = new TH1F("SG_dataRunC_LWdR","SG delta R separation between electrons and jets",100,0,8);

TH1F* SG_ZLL_LWdR = new TH1F("SG_ZLL_LWdR","SG delta R separation between electrons and jets",100,0,8);

TH1F* SG_TT_LWdR = new TH1F("SG_TT_LWdR","SG delta R separation between electrons and jets",100,0,8);

TH1F* SG_W3J_LWdR = new TH1F("SG_W3J_LWdR","SG delta R separation between electrons and jets",100,0,8);

TH1F* SG_W2J_LWdR = new TH1F("SG_W2J_LWdR","SG delta R separation between electrons and jets",100,0,8);

TH1F* SG_W1J_LWdR = new TH1F("SG_W1J_LWdR","SG delta R separation between electrons and jets",100,0,8);

//TH1F* SG_TTZ_LWdR = new TH1F("SG_TTZ_LWdR","SG delta R separation between electrons and jets",100,0,8);

//TH1F* SG_WW_LWdR = new TH1F("SG_WW_LWdR","SG delta R separation between electrons and jets",100,0,8);

//TH1F* SG_WZ_LWdR = new TH1F("SG_WZ_LWdR","SG delta R separation between electrons and jets",100,0,8);

TH1F* SG_LW200_LWdR = new TH1F("SG_LW200_LWdR","SG delta R separation between electrons and jets",100,0,8);

//TH1F* SG_LW300_LWdR = new TH1F("SG_LW300_LWdR","SG delta R separation between electrons and jets",100,0,8);

//TH1F* SG_LW400_LWdR = new TH1F("SG_LW400_LWdR","SG delta R separation between electrons and jets",100,0,8);

//TH1F* SG_LW500_LWdR = new TH1F("SG_LW500_LWdR","SG delta R separation between electrons and jets",100,0,8);

TH1F* SG_dataRunB_DiJetdR = new TH1F("SG_dataRunB_DiJetdR","SG delta R separation between Jet Candidates",100,0,8);

TH1F* SG_dataRunC_DiJetdR  = new TH1F("SG_dataRunC_DiJetdR","SG delta R separation between Jet Candidates",100,0,8);

TH1F* SG_ZLL_DiJetdR = new TH1F("SG_ZLL_DiJetdR","SG delta R separation between Jet Candidates",100,0,8);

TH1F* SG_TT_DiJetdR = new TH1F("SG_TT_DiJetdR","SG delta R separation between Jet Candidates",100,0,8);

TH1F* SG_W3J_DiJetdR = new TH1F("SG_W3J_DiJetdR","SG delta R separation between Jet Candidates",100,0,8);

TH1F* SG_W2J_DiJetdR = new TH1F("SG_W2J_DiJetdR","SG delta R separation between Jet Candidates",100,0,8);

TH1F* SG_W1J_DiJetdR = new TH1F("SG_W1J_DiJetdR","SG delta R separation between Jet Candidates",100,0,8);

//TH1F* SG_TTZ_DiJetdR = new TH1F("SG_TTZ_DiJetdR","SG delta R separation between Jet Candidates",100,0,8);

//TH1F* SG_WW_DiJetdR = new TH1F("SG_WW_DiJetdR","SG delta R separation between Jet Candidates",100,0,8);

//TH1F* SG_WZ_DiJetdR = new TH1F("SG_WZ_DiJetdR","SG delta R separation between Jet Candidates",100,0,8);

TH1F* SG_LW200_DiJetdR = new TH1F("SG_LW200_DiJetdR","SG delta R separation between Jet Candidates",100,0,8);

//TH1F* SG_LW300_DiJetdR = new TH1F("SG_LW300_DiJetdR","SG delta R separation between Jet Candidates",100,0,8);

//TH1F* SG_LW400_DiJetdR = new TH1F("SG_LW400_DiJetdR","SG delta R separation between Jet Candidates",100,0,8);

//TH1F* SG_LW500_DiJetdR = new TH1F("SG_LW500_DiJetdR","SG delta R separation between Jet Candidates",100,0,8);

TH1F* SG_dataRunB_BJetPt = new TH1F("SG_dataRunB_BJetPt","SG Most energetic Jet pt",100,0,250);

TH1F* SG_dataRunC_BJetPt  = new TH1F("SG_dataRunC_BJetPt","SG Most energetic Jet pt",100,0,250);

TH1F* SG_ZLL_BJetPt = new TH1F("SG_ZLL_BJetPt","SG Most energetic Jet pt",100,0,250);

TH1F* SG_TT_BJetPt = new TH1F("SG_TT_BJetPt","SG Most energetic Jet pt",100,0,250);

TH1F* SG_W3J_BJetPt = new TH1F("SG_W3J_BJetPt","SG Most energetic Jet pt",100,0,250);

TH1F* SG_W2J_BJetPt = new TH1F("SG_W2J_BJetPt","SG Most energetic Jet pt",100,0,250);

TH1F* SG_W1J_BJetPt = new TH1F("SG_W1J_BJetPt","SG Most energetic Jet pt",100,0,250);

//TH1F* SG_TTZ_BJetPt = new TH1F("SG_TTZ_BJetPt","SG Most energetic Jet pt",100,0,250);

//TH1F* SG_WW_BJetPt = new TH1F("SG_WW_BJetPt","SG Most energetic Jet pt",100,0,250);

//TH1F* SG_WZ_BJetPt = new TH1F("SG_WZ_BJetPt","SG Most energetic Jet pt",100,0,250);

TH1F* SG_LW200_BJetPt = new TH1F("SG_LW200_BJetPt","SG Most energetic Jet pt",100,0,250);

//TH1F* SG_LW300_BJetPt = new TH1F("SG_LW300_BJetPt","SG Most energetic Jet pt",100,0,250);

//TH1F* SG_LW400_BJetPt = new TH1F("SG_LW400_BJetPt","SG Most energetic Jet pt",100,0,250);

//TH1F* SG_LW500_BJetPt = new TH1F("SG_LW500_BJetPt","SG Most energetic Jet pt",100,0,250);

TH1F* SG_dataRunB_SBJetPt = new TH1F("SG_dataRunB_SBJetPt","Second SG Most energetic Jet pt",100,0,250);

TH1F* SG_dataRunC_SBJetPt  = new TH1F("SG_dataRunC_SBJetPt","Second SG Most energetic Jet pt",100,0,250);

TH1F* SG_ZLL_SBJetPt = new TH1F("SG_ZLL_SBJetPt","Second SG Most energetic Jet pt",100,0,250);

TH1F* SG_TT_SBJetPt = new TH1F("SG_TT_SBJetPt","Second SG Most energetic Jet pt",100,0,250);

TH1F* SG_W3J_SBJetPt = new TH1F("SG_W3J_SBJetPt","Second SG Most energetic Jet pt",100,0,250);

TH1F* SG_W2J_SBJetPt = new TH1F("SG_W2J_SBJetPt","Second SG Most energetic Jet pt",100,0,250);

TH1F* SG_W1J_SBJetPt = new TH1F("SG_W1J_SBJetPt","Second SG Most energetic Jet pt",100,0,250);

//TH1F* SG_TTZ_SBJetPt = new TH1F("SG_TTZ_SBJetPt","Second SG Most energetic Jet pt",100,0,250);

//TH1F* SG_WW_SBJetPt = new TH1F("SG_WW_SBJetPt","Second SG Most energetic Jet pt",100,0,250);

//TH1F* SG_WZ_SBJetPt = new TH1F("SG_WZ_SBJetPt","Second SG Most energetic Jet pt",100,0,250);

TH1F* SG_LW200_SBJetPt = new TH1F("SG_LW200_SBJetPt","Second SG Most energetic Jet pt",100,0,250);

//TH1F* SG_LW300_SBJetPt = new TH1F("SG_LW300_SBJetPt","Second SG Most energetic Jet pt",100,0,250);

//TH1F* SG_LW400_SBJetPt = new TH1F("SG_LW400_SBJetPt","Second SG Most energetic Jet pt",100,0,250);

//TH1F* SG_LW500_SBJetPt = new TH1F("SG_LW500_SBJetPt","Second SG Most energetic Jet pt",100,0,250);

TH1F* SG_dataRunB_NJet = new TH1F("SG_dataRunB_NJet","SG Number of Jets",20,0,20);

TH1F* SG_dataRunC_NJet  = new TH1F("SG_dataRunC_NJet","SG Number of Jets",20,0,20);

TH1F* SG_ZLL_NJet = new TH1F("SG_ZLL_NJet","SG Number of Jets",20,0,20);

TH1F* SG_TT_NJet = new TH1F("SG_TT_NJet","SG Number of Jets",20,0,20);

TH1F* SG_W3J_NJet = new TH1F("SG_W3J_NJet","SG Number of Jets",20,0,20);

TH1F* SG_W2J_NJet = new TH1F("SG_W2J_NJet","SG Number of Jets",20,0,20);

TH1F* SG_W1J_NJet = new TH1F("SG_W1J_NJet","SG Number of Jets",20,0,20);

//TH1F* SG_TTZ_NJet = new TH1F("SG_TTZ_NJet","SG Number of Jets",20,0,20);

//TH1F* SG_WW_NJet = new TH1F("SG_WW_NJet","SG Number of Jets",20,0,20);

//TH1F* SG_WZ_NJet = new TH1F("SG_WZ_NJet","SG Number of Jets",20,0,20);

TH1F* SG_LW200_NJet = new TH1F("SG_LW200_NJet","SG Number of Jets",20,0,20);

//TH1F* SG_LW300_NJet = new TH1F("SG_LW300_NJet","SG Number of Jets",20,0,20);

//TH1F* SG_LW400_NJet = new TH1F("SG_LW400_NJet","SG Number of Jets",20,0,20);

//TH1F* SG_LW500_NJet = new TH1F("SG_LW500_NJet","SG Number of Jets",20,0,20);

TH1F* SG_dataRunB_NEle = new TH1F("SG_dataRunB_NEle","SG Number of electrons",20,0,20);

TH1F* SG_dataRunC_NEle  = new TH1F("SG_dataRunC_NEle","SG Number of electrons",20,0,20);

TH1F* SG_ZLL_NEle = new TH1F("SG_ZLL_NEle","SG Number of electrons",20,0,20);

TH1F* SG_TT_NEle = new TH1F("SG_TT_NEle","SG Number of electrons",20,0,20);

TH1F* SG_W3J_NEle = new TH1F("SG_W3J_NEle","SG Number of electrons",20,0,20);

TH1F* SG_W2J_NEle = new TH1F("SG_W2J_NEle","SG Number of electrons",20,0,20);

TH1F* SG_W1J_NEle = new TH1F("SG_W1J_NEle","SG Number of electrons",20,0,20);

//TH1F* SG_TTZ_NEle = new TH1F("SG_TTZ_NEle","SG Number of electrons",20,0,20);

//TH1F* SG_WW_NEle = new TH1F("SG_WW_NEle","SG Number of electrons",20,0,20);

//TH1F* SG_WZ_NEle = new TH1F("SG_WZ_NEle","SG Number of electrons",20,0,20);

TH1F* SG_LW200_NEle = new TH1F("SG_LW200_NEle","SG Number of electrons",20,0,20);

//TH1F* SG_LW300_NEle = new TH1F("SG_LW300_NEle","SG Number of electrons",20,0,20);

//TH1F* SG_LW400_NEle = new TH1F("SG_LW400_NEle","SG Number of electrons",20,0,20);

//TH1F* SG_LW500_NEle = new TH1F("SG_LW500_NEle","SG Number of electrons",20,0,20);

//Requiered trigger
//string triggerRequest = "HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50";
string triggerRequest[] = {"HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50",
                           "HLT_Photon36_CaloId10_Iso50_Photon22_R9Id85",
                           "HLT_Photon36_R9Id85_Photon22_CaloId10_Iso50",
                           "HLT_Photon36_R9Id85_Photon22_R9Id85"};

// Fixed size dimensions of array or collections stored in the TTree if any.


class EventLoopAnalysisTemplate {
public :

  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  TTree          *tevents;
  TTree          *tvertex;
  TTree          *ttrigger;
  TTree           *tmuons;
  TTree           *ttaus;
  TTree           *tmets;
  TTree           *tjets;
  TTree           *telectrons;
  TTree           *ttrigobjs;

  Int_t           fCurrent; //!current Tree number in a TChain
  TString          labeltag;
  TString         filename;
  Float_t          theweight;

  //array to keep histograms to be written and easily loop over them
  //TH1F            *hists[nhists];
  std::vector<TH1F*> hists;

  // Declaration of example leaf types
  Int_t           run;
  UInt_t          luminosityBlock;
  ULong64_t	   event;
  Int_t           PV_npvs;
  std::map<std::string, int> *triggermap;
  Int_t           numbersecvec;
  vector<float>   *PV_x;
  vector<float>   *PV_y;
  vector<float>   *PV_z;
  vector<float>   *muon_pt;
  vector<float>   *muon_eta;
  vector<float>   *muon_phi;
  vector<float>   *muon_ch;
  vector<float>   *muon_tightid;
  vector<float>   *muon_pfreliso03all;
  vector<float>   *muon_mass;
  vector<float>   *tau_pt;
  vector<float>   *tau_eta;
  vector<float>   *tau_phi;
  vector<float>   *tau_ch;
  vector<float>   *tau_iddecaymode;
  vector<float>   *tau_idisotight;
  vector<float>   *tau_idantieletight;
  vector<float>   *tau_idantimutight;
  vector<float>   *tau_reliso_all;
  vector<float>   *tau_mass;
  vector<float>   *jet_mass;
  vector<float>   *jet_e;
  vector<float>   *jet_pt;
  vector<float>   *corr_jet_pt;
  vector<float>   *jet_pz;
  vector<float>   *jet_px;
  vector<float>   *jet_py;
  vector<float>   *jet_eta;
  vector<float>   *jet_phi;
  vector<float>   *NConstituents;
  vector<float>   *NeutralHF;
  vector<float>   *NeutralEMF;
  vector<float>   *MuonF;
  vector<float>   *ChargedEMF;
  vector<float>   *ChargedHF;
  vector<float>   *ChargedMult;
  vector<float>   *electron_e;
  vector<float>   *electron_pt;
  vector<float>   *electron_pz;
  vector<float>   *electron_px;
  vector<float>   *electron_py;
  vector<float>   *electron_phi;
  vector<float>   *electron_eta;
  vector<float>   *trk_isHQ;
  vector<float>   *trigobj_e;
  vector<float>   *trigobj_pt;
  vector<float>   *trigobj_pz;
  vector<float>   *trigobj_px;
  vector<float>   *trigobj_py;
  vector<float>   *trigobj_eta;
  vector<float>   *trigobj_phi;
  vector<float>   *secvec_posx;
  vector<float>   *secvec_posy;
  vector<float>   *secvec_posz;
  Float_t         met_pt;
  Float_t         met_phi;

  // List of example branches
  TBranch        *b_run;   //!
  TBranch        *b_luminosityBlock;   //!
  TBranch        *b_event;   //!
  TBranch        *b_PV_npvs;   //!
  TBranch        *b_numbersecvec;   //!
  TBranch        *b_PV_x;   //!
  TBranch        *b_PV_y;   //!
  TBranch        *b_PV_z;   //!
  TBranch        *b_triggermap;   //!
  TBranch        *b_muon_pt;   //!
  TBranch        *b_muon_eta;   //!
  TBranch        *b_muon_phi;   //!
  TBranch        *b_muon_ch;   //!
  TBranch        *b_muon_tightid;   //!
  TBranch        *b_muon_pfreliso03all;   //!
  TBranch        *b_muon_mass;   //!
  TBranch        *b_tau_pt;   //!
  TBranch        *b_tau_eta;   //!
  TBranch        *b_tau_phi;   //!
  TBranch        *b_tau_ch;   //!
  TBranch        *b_tau_iddecaymode;   //!
  TBranch        *b_tau_idisotight;   //!
  TBranch        *b_tau_idantieletight;   //!
  TBranch        *b_tau_idantimutight;   //!
  TBranch        *b_tau_reliso_all;   //!
  TBranch        *b_tau_mass;   //!
  TBranch        *b_met_pt;   //!
  TBranch        *b_met_phi;   //!
  TBranch        *b_jet_mass;
  TBranch        *b_jet_e;
  TBranch        *b_jet_pt;
  TBranch        *b_corr_jet_pt;
  TBranch        *b_jet_pz;
  TBranch        *b_jet_px;
  TBranch        *b_jet_py;
  TBranch        *b_jet_phi;
  TBranch        *b_jet_eta;
  TBranch        *b_NConstituents;
  TBranch        *b_NeutralHF;
  TBranch        *b_NeutralEMF;
  TBranch        *b_MuonF;
  TBranch        *b_ChargedEMF;
  TBranch        *b_ChargedHF;
  TBranch        *b_ChargedMult;
  TBranch        *b_electron_e;
  TBranch        *b_electron_pt;
  TBranch        *b_electron_pz;
  TBranch        *b_electron_px;
  TBranch        *b_electron_py;
  TBranch        *b_electron_phi;
  TBranch        *b_electron_eta;
  TBranch        *b_trk_isHQ;
  TBranch        *b_trigobj_e;
  TBranch        *b_trigobj_pt;
  TBranch        *b_trigobj_pz;
  TBranch        *b_trigobj_px;
  TBranch        *b_trigobj_py;
  TBranch        *b_trigobj_eta;
  TBranch        *b_trigobj_phi;
  TBranch        *b_secvec_posx;
  TBranch        *b_secvec_posy;
  TBranch        *b_secvec_posz;

  EventLoopAnalysisTemplate(TString filename, TString labeltag, Float_t theweight);
  virtual ~EventLoopAnalysisTemplate();
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  virtual float deltaR(float eta1, float phi1, float eta2, float phi2);
  void analysis();
  void histograms(string cut);
  bool MinimalSelection();

};



EventLoopAnalysisTemplate::EventLoopAnalysisTemplate(TString thefile, TString thelabel, Float_t sampleweight) : fChain(0)
{
  //Prepare some info for the object:
  filename = thefile;
  labeltag = thelabel;
  theweight = sampleweight;


  //Load histograms for signal region
  hists.push_back(NF_dataRunB_npv);
  hists.push_back(NF_dataRunC_npv);
  hists.push_back(NF_ZLL_npv);
  hists.push_back(NF_TT_npv);
  hists.push_back(NF_W3J_npv);
  hists.push_back(NF_W2J_npv);
  hists.push_back(NF_W1J_npv);
  hists.push_back(NF_LW200_npv);
  hists.push_back(NF_dataRunB_JetMass);
  hists.push_back(NF_dataRunC_JetMass);
  hists.push_back(NF_ZLL_JetMass);
  hists.push_back(NF_TT_JetMass);
  hists.push_back(NF_W3J_JetMass);
  hists.push_back(NF_W2J_JetMass);
  hists.push_back(NF_W1J_JetMass);
  hists.push_back(NF_LW200_JetMass);
  hists.push_back(NF_dataRunB_LWMass);
  hists.push_back(NF_dataRunC_LWMass);
  hists.push_back(NF_ZLL_LWMass);
  hists.push_back(NF_TT_LWMass);
  hists.push_back(NF_W3J_LWMass);
  hists.push_back(NF_W2J_LWMass);
  hists.push_back(NF_W1J_LWMass);
  hists.push_back(NF_LW200_LWMass);
  //hists.push_back(//NF_WW_npv);
  //hists.push_back(//NF_WZ_npv);
  //hists.push_back(//NF_TTZ_npv);
  //hists.push_back(//NF_WW_JetMass);
  //hists.push_back(//NF_WZ_JetMass);
  //hists.push_back(//NF_TTZ_JetMass);
  //hists.push_back(//NF_WW_LWMass);
  //hists.push_back(//NF_WZ_LWMass);
  //hists.push_back(//NF_TTZ_LWMass);
  //hists.push_back(//NF_LW300_LWMass);
  //hists.push_back(NF_LW400_LWMass);
  //hists.push_back(NF_LW500_LWMass);
  //hists.push_back(//NF_LW300_JetMass);
  //hists.push_back(NF_LW400_JetMass);
  //hists.push_back(NF_LW500_JetMass);
  //hists.push_back(//NF_LW300_npv);
  //hists.push_back(NF_LW400_npv);
  //hists.push_back(NF_LW500_npv);
  hists.push_back(NF_dataRunB_nsv);
  hists.push_back(NF_dataRunC_nsv);
  hists.push_back(NF_ZLL_nsv);
  hists.push_back(NF_TT_nsv);
  hists.push_back(NF_W3J_nsv);
  hists.push_back(NF_W2J_nsv);
  hists.push_back(NF_W1J_nsv);
  //hists.push_back(//NF_WW_nsv);
  //hists.push_back(//NF_WZ_nsv);
  //hists.push_back(//NF_TTZ_nsv);
  hists.push_back(NF_LW200_nsv);
  hists.push_back(NF_LW200_nsv);
  //hists.push_back(NF_LW400_nsv);
  //hists.push_back(NF_LW500_nsv);
  hists.push_back(NF_dataRunB_svd);
  hists.push_back(NF_dataRunC_svd);
  hists.push_back(NF_ZLL_svd);
  hists.push_back(NF_TT_svd);
  hists.push_back(NF_W3J_svd);
  hists.push_back(NF_W2J_svd);
  hists.push_back(NF_W1J_svd);
  //hists.push_back(//NF_WW_svd);
  //hists.push_back(//NF_WZ_svd);
  //hists.push_back(//NF_TTZ_svd);
  hists.push_back(NF_LW200_svd);
  hists.push_back(NF_LW200_svd);
  //hists.push_back(NF_LW400_svd);
  //hists.push_back(NF_LW500_svd);
  hists.push_back(NF_dataRunB_Elept);
  hists.push_back(NF_dataRunC_Elept);
  hists.push_back(NF_ZLL_Elept);
  hists.push_back(NF_TT_Elept);
  hists.push_back(NF_W3J_Elept);
  hists.push_back(NF_W2J_Elept);
  hists.push_back(NF_W1J_Elept);
  //hists.push_back(//NF_WW_Elept);
  //hists.push_back(//NF_WZ_Elept);
  //hists.push_back(//NF_TTZ_Elept);
  hists.push_back(NF_LW200_Elept);
  hists.push_back(NF_LW200_Elept);
  //hists.push_back(NF_LW400_svd);
  //hists.push_back(NF_LW500_svd);
  hists.push_back(NF_dataRunB_DieledR);
  hists.push_back(NF_dataRunC_DieledR);
  hists.push_back(NF_ZLL_DieledR);
  hists.push_back(NF_TT_DieledR);
  hists.push_back(NF_W3J_DieledR);
  hists.push_back(NF_W2J_DieledR);
  hists.push_back(NF_W1J_DieledR);
  //hists.push_back(//NF_WW_DieledR);
  //hists.push_back(//NF_WZ_DieledR);
  //hists.push_back(//NF_TTZ_DieledR);
  hists.push_back(NF_LW200_DieledR);
  hists.push_back(NF_LW200_DieledR);
  //hists.push_back(NF_LW400_svd);
  //hists.push_back(NF_LW500_svd);
  hists.push_back(NF_dataRunB_LWdR);
  hists.push_back(NF_dataRunC_LWdR);
  hists.push_back(NF_ZLL_LWdR);
  hists.push_back(NF_TT_LWdR);
  hists.push_back(NF_W3J_LWdR);
  hists.push_back(NF_W2J_LWdR);
  hists.push_back(NF_W1J_LWdR);
  //hists.push_back(//NF_WW_LWdR);
  //hists.push_back(//NF_WZ_LWdR);
  //hists.push_back(//NF_TTZ_LWdR);
  hists.push_back(NF_LW200_LWdR);
  hists.push_back(NF_LW200_LWdR);
  //hists.push_back(NF_LW400_svd);
  //hists.push_back(NF_LW500_svd);
  hists.push_back(NF_dataRunB_DiJetdR);
  hists.push_back(NF_dataRunC_DiJetdR);
  hists.push_back(NF_ZLL_DiJetdR);
  hists.push_back(NF_TT_DiJetdR);
  hists.push_back(NF_W3J_DiJetdR);
  hists.push_back(NF_W2J_DiJetdR);
  hists.push_back(NF_W1J_DiJetdR);
  //hists.push_back(//NF_WW_DiJetdR);
  //hists.push_back(//NF_WZ_DiJetdR);
  //hists.push_back(//NF_TTZ_DiJetdR);
  hists.push_back(NF_LW200_DiJetdR);
  hists.push_back(NF_LW200_DiJetdR);
  //hists.push_back(NF_LW400_svd);
  //hists.push_back(NF_LW500_svd);
  hists.push_back(NF_dataRunB_BJetPt);
  hists.push_back(NF_dataRunC_BJetPt);
  hists.push_back(NF_ZLL_BJetPt);
  hists.push_back(NF_TT_BJetPt);
  hists.push_back(NF_W3J_BJetPt);
  hists.push_back(NF_W2J_BJetPt);
  hists.push_back(NF_W1J_BJetPt);
  //hists.push_back(//NF_WW_BJetPt);
  //hists.push_back(//NF_WZ_BJetPt);
  //hists.push_back(//NF_TTZ_BJetPt);
  hists.push_back(NF_LW200_BJetPt);
  hists.push_back(NF_LW200_BJetPt);
  //hists.push_back(NF_LW400_svd);
  //hists.push_back(NF_LW500_svd);
  hists.push_back(NF_dataRunB_SBJetPt);
  hists.push_back(NF_dataRunC_SBJetPt);
  hists.push_back(NF_ZLL_SBJetPt);
  hists.push_back(NF_TT_SBJetPt);
  hists.push_back(NF_W3J_SBJetPt);
  hists.push_back(NF_W2J_SBJetPt);
  hists.push_back(NF_W1J_SBJetPt);
  //hists.push_back(//NF_WW_SBJetPt);
  //hists.push_back(//NF_WZ_SBJetPt);
  //hists.push_back(//NF_TTZ_SBJetPt);
  hists.push_back(NF_LW200_SBJetPt);
  hists.push_back(NF_LW200_SBJetPt);
  //hists.push_back(NF_LW400_svd);
  //hists.push_back(NF_LW500_svd);
  hists.push_back(NF_dataRunB_NJet);
  hists.push_back(NF_dataRunC_NJet);
  hists.push_back(NF_ZLL_NJet);
  hists.push_back(NF_TT_NJet);
  hists.push_back(NF_W3J_NJet);
  hists.push_back(NF_W2J_NJet);
  hists.push_back(NF_W1J_NJet);
  //hists.push_back(//NF_WW_NJet);
  //hists.push_back(//NF_WZ_NJet);
  //hists.push_back(//NF_TTZ_NJet);
  hists.push_back(NF_LW200_NJet);
  hists.push_back(NF_LW200_NJet);
  //hists.push_back(NF_LW400_svd);
  //hists.push_back(NF_LW500_svd);
  hists.push_back(NF_dataRunB_NEle);
  hists.push_back(NF_dataRunC_NEle);
  hists.push_back(NF_ZLL_NEle);
  hists.push_back(NF_TT_NEle);
  hists.push_back(NF_W3J_NEle);
  hists.push_back(NF_W2J_NEle);
  hists.push_back(NF_W1J_NEle);
  //hists.push_back(//NF_WW_NEle);
  //hists.push_back(//NF_WZ_NEle);
  //hists.push_back(//NF_TTZ_NEle);
  hists.push_back(NF_LW200_NEle);
  hists.push_back(NF_LW200_NEle);
  //hists.push_back(NF_LW400_svd);
  //hists.push_back(NF_LW500_svd);

  hists.push_back(TF_dataRunB_npv);
  hists.push_back(TF_dataRunC_npv);
  hists.push_back(TF_ZLL_npv);
  hists.push_back(TF_TT_npv);
  hists.push_back(TF_W3J_npv);
  hists.push_back(TF_W2J_npv);
  hists.push_back(TF_W1J_npv);
  hists.push_back(TF_LW200_npv);
  hists.push_back(TF_dataRunB_JetMass);
  hists.push_back(TF_dataRunC_JetMass);
  hists.push_back(TF_ZLL_JetMass);
  hists.push_back(TF_TT_JetMass);
  hists.push_back(TF_W3J_JetMass);
  hists.push_back(TF_W2J_JetMass);
  hists.push_back(TF_W1J_JetMass);
  hists.push_back(TF_LW200_JetMass);
  hists.push_back(TF_dataRunB_LWMass);
  hists.push_back(TF_dataRunC_LWMass);
  hists.push_back(TF_ZLL_LWMass);
  hists.push_back(TF_TT_LWMass);
  hists.push_back(TF_W3J_LWMass);
  hists.push_back(TF_W2J_LWMass);
  hists.push_back(TF_W1J_LWMass);
  hists.push_back(TF_LW200_LWMass);
  //hists.push_back(//TF_WW_npv);
  //hists.push_back(//TF_WZ_npv);
  //hists.push_back(//TF_TTZ_npv);
  //hists.push_back(//TF_WW_JetMass);
  //hists.push_back(//TF_WZ_JetMass);
  //hists.push_back(//TF_TTZ_JetMass);
  //hists.push_back(//TF_WW_LWMass);
  //hists.push_back(//TF_WZ_LWMass);
  //hists.push_back(//TF_TTZ_LWMass);
  //hists.push_back(//TF_LW300_LWMass);
  //hists.push_back(TF_LW400_LWMass);
  //hists.push_back(TF_LW500_LWMass);
  //hists.push_back(//TF_LW300_JetMass);
  //hists.push_back(TF_LW400_JetMass);
  //hists.push_back(TF_LW500_JetMass);
  //hists.push_back(//TF_LW300_npv);
  //hists.push_back(TF_LW400_npv);
  //hists.push_back(TF_LW500_npv);
  hists.push_back(TF_dataRunB_nsv);
  hists.push_back(TF_dataRunC_nsv);
  hists.push_back(TF_ZLL_nsv);
  hists.push_back(TF_TT_nsv);
  hists.push_back(TF_W3J_nsv);
  hists.push_back(TF_W2J_nsv);
  hists.push_back(TF_W1J_nsv);
  //hists.push_back(//TF_WW_nsv);
  //hists.push_back(//TF_WZ_nsv);
  //hists.push_back(//TF_TTZ_nsv);
  hists.push_back(TF_LW200_nsv);
  hists.push_back(TF_LW200_nsv);
  //hists.push_back(TF_LW400_nsv);
  //hists.push_back(TF_LW500_nsv);
  hists.push_back(TF_dataRunB_svd);
  hists.push_back(TF_dataRunC_svd);
  hists.push_back(TF_ZLL_svd);
  hists.push_back(TF_TT_svd);
  hists.push_back(TF_W3J_svd);
  hists.push_back(TF_W2J_svd);
  hists.push_back(TF_W1J_svd);
  //hists.push_back(//TF_WW_svd);
  //hists.push_back(//TF_WZ_svd);
  //hists.push_back(//TF_TTZ_svd);
  hists.push_back(TF_LW200_svd);
  hists.push_back(TF_LW200_svd);
  //hists.push_back(TF_LW400_svd);
  //hists.push_back(TF_LW500_svd);
  hists.push_back(TF_dataRunB_Elept);
  hists.push_back(TF_dataRunC_Elept);
  hists.push_back(TF_ZLL_Elept);
  hists.push_back(TF_TT_Elept);
  hists.push_back(TF_W3J_Elept);
  hists.push_back(TF_W2J_Elept);
  hists.push_back(TF_W1J_Elept);
  //hists.push_back(//TF_WW_Elept);
  //hists.push_back(//TF_WZ_Elept);
  //hists.push_back(//TF_TTZ_Elept);
  hists.push_back(TF_LW200_Elept);
  hists.push_back(TF_LW200_Elept);
  //hists.push_back(TF_LW400_svd);
  //hists.push_back(TF_LW500_svd);
  hists.push_back(TF_dataRunB_DieledR);
  hists.push_back(TF_dataRunC_DieledR);
  hists.push_back(TF_ZLL_DieledR);
  hists.push_back(TF_TT_DieledR);
  hists.push_back(TF_W3J_DieledR);
  hists.push_back(TF_W2J_DieledR);
  hists.push_back(TF_W1J_DieledR);
  //hists.push_back(//TF_WW_DieledR);
  //hists.push_back(//TF_WZ_DieledR);
  //hists.push_back(//TF_TTZ_DieledR);
  hists.push_back(TF_LW200_DieledR);
  hists.push_back(TF_LW200_DieledR);
  //hists.push_back(TF_LW400_svd);
  //hists.push_back(TF_LW500_svd);
  hists.push_back(TF_dataRunB_LWdR);
  hists.push_back(TF_dataRunC_LWdR);
  hists.push_back(TF_ZLL_LWdR);
  hists.push_back(TF_TT_LWdR);
  hists.push_back(TF_W3J_LWdR);
  hists.push_back(TF_W2J_LWdR);
  hists.push_back(TF_W1J_LWdR);
  //hists.push_back(//TF_WW_LWdR);
  //hists.push_back(//TF_WZ_LWdR);
  //hists.push_back(//TF_TTZ_LWdR);
  hists.push_back(TF_LW200_LWdR);
  hists.push_back(TF_LW200_LWdR);
  //hists.push_back(TF_LW400_svd);
  //hists.push_back(TF_LW500_svd);
  hists.push_back(TF_dataRunB_DiJetdR);
  hists.push_back(TF_dataRunC_DiJetdR);
  hists.push_back(TF_ZLL_DiJetdR);
  hists.push_back(TF_TT_DiJetdR);
  hists.push_back(TF_W3J_DiJetdR);
  hists.push_back(TF_W2J_DiJetdR);
  hists.push_back(TF_W1J_DiJetdR);
  //hists.push_back(//TF_WW_DiJetdR);
  //hists.push_back(//TF_WZ_DiJetdR);
  //hists.push_back(//TF_TTZ_DiJetdR);
  hists.push_back(TF_LW200_DiJetdR);
  hists.push_back(TF_LW200_DiJetdR);
  //hists.push_back(TF_LW400_svd);
  //hists.push_back(TF_LW500_svd);
  hists.push_back(TF_dataRunB_BJetPt);
  hists.push_back(TF_dataRunC_BJetPt);
  hists.push_back(TF_ZLL_BJetPt);
  hists.push_back(TF_TT_BJetPt);
  hists.push_back(TF_W3J_BJetPt);
  hists.push_back(TF_W2J_BJetPt);
  hists.push_back(TF_W1J_BJetPt);
  //hists.push_back(//TF_WW_BJetPt);
  //hists.push_back(//TF_WZ_BJetPt);
  //hists.push_back(//TF_TTZ_BJetPt);
  hists.push_back(TF_LW200_BJetPt);
  hists.push_back(TF_LW200_BJetPt);
  //hists.push_back(TF_LW400_svd);
  //hists.push_back(TF_LW500_svd);
  hists.push_back(TF_dataRunB_SBJetPt);
  hists.push_back(TF_dataRunC_SBJetPt);
  hists.push_back(TF_ZLL_SBJetPt);
  hists.push_back(TF_TT_SBJetPt);
  hists.push_back(TF_W3J_SBJetPt);
  hists.push_back(TF_W2J_SBJetPt);
  hists.push_back(TF_W1J_SBJetPt);
  //hists.push_back(//TF_WW_SBJetPt);
  //hists.push_back(//TF_WZ_SBJetPt);
  //hists.push_back(//TF_TTZ_SBJetPt);
  hists.push_back(TF_LW200_SBJetPt);
  hists.push_back(TF_LW200_SBJetPt);
  //hists.push_back(TF_LW400_svd);
  //hists.push_back(TF_LW500_svd);
  hists.push_back(TF_dataRunB_NJet);
  hists.push_back(TF_dataRunC_NJet);
  hists.push_back(TF_ZLL_NJet);
  hists.push_back(TF_TT_NJet);
  hists.push_back(TF_W3J_NJet);
  hists.push_back(TF_W2J_NJet);
  hists.push_back(TF_W1J_NJet);
  //hists.push_back(//TF_WW_NJet);
  //hists.push_back(//TF_WZ_NJet);
  //hists.push_back(//TF_TTZ_NJet);
  hists.push_back(TF_LW200_NJet);
  hists.push_back(TF_LW200_NJet);
  //hists.push_back(TF_LW400_svd);
  //hists.push_back(TF_LW500_svd);
  hists.push_back(TF_dataRunB_NEle);
  hists.push_back(TF_dataRunC_NEle);
  hists.push_back(TF_ZLL_NEle);
  hists.push_back(TF_TT_NEle);
  hists.push_back(TF_W3J_NEle);
  hists.push_back(TF_W2J_NEle);
  hists.push_back(TF_W1J_NEle);
  //hists.push_back(//TF_WW_NEle);
  //hists.push_back(//TF_WZ_NEle);
  //hists.push_back(//TF_TTZ_NEle);
  hists.push_back(TF_LW200_NEle);
  hists.push_back(TF_LW200_NEle);
  //hists.push_back(TF_LW400_svd);
  //hists.push_back(TF_LW500_svd);

  hists.push_back(TO_dataRunB_npv);
  hists.push_back(TO_dataRunC_npv);
  hists.push_back(TO_ZLL_npv);
  hists.push_back(TO_TT_npv);
  hists.push_back(TO_W3J_npv);
  hists.push_back(TO_W2J_npv);
  hists.push_back(TO_W1J_npv);
  hists.push_back(TO_LW200_npv);
  hists.push_back(TO_dataRunB_JetMass);
  hists.push_back(TO_dataRunC_JetMass);
  hists.push_back(TO_ZLL_JetMass);
  hists.push_back(TO_TT_JetMass);
  hists.push_back(TO_W3J_JetMass);
  hists.push_back(TO_W2J_JetMass);
  hists.push_back(TO_W1J_JetMass);
  hists.push_back(TO_LW200_JetMass);
  hists.push_back(TO_dataRunB_LWMass);
  hists.push_back(TO_dataRunC_LWMass);
  hists.push_back(TO_ZLL_LWMass);
  hists.push_back(TO_TT_LWMass);
  hists.push_back(TO_W3J_LWMass);
  hists.push_back(TO_W2J_LWMass);
  hists.push_back(TO_W1J_LWMass);
  hists.push_back(TO_LW200_LWMass);
  //hists.push_back(//TO_WW_npv);
  //hists.push_back(////TO_WZ_npv);
  //hists.push_back(//TO_TTZ_npv);
  //hists.push_back(//TO_WW_JetMass);
  //hists.push_back(////TO_WZ_JetMass);
  //hists.push_back(//TO_TTZ_JetMass);
  //hists.push_back(//TO_WW_LWMass);
  //hists.push_back(////TO_WZ_LWMass);
  //hists.push_back(//TO_TTZ_LWMass);
  //hists.push_back(//TO_LW300_LWMass);
  //hists.push_back(TO_LW400_LWMass);
  //hists.push_back(TO_LW500_LWMass);
  //hists.push_back(//TO_LW300_JetMass);
  //hists.push_back(TO_LW400_JetMass);
  //hists.push_back(TO_LW500_JetMass);
  //hists.push_back(//TO_LW300_npv);
  //hists.push_back(TO_LW400_npv);
  //hists.push_back(TO_LW500_npv);
  hists.push_back(TO_dataRunB_nsv);
  hists.push_back(TO_dataRunC_nsv);
  hists.push_back(TO_ZLL_nsv);
  hists.push_back(TO_TT_nsv);
  hists.push_back(TO_W3J_nsv);
  hists.push_back(TO_W2J_nsv);
  hists.push_back(TO_W1J_nsv);
  //hists.push_back(//TO_WW_nsv);
  //hists.push_back(////TO_WZ_nsv);
  //hists.push_back(//TO_TTZ_nsv);
  hists.push_back(TO_LW200_nsv);
  //hists.push_back(TO_LW200_nsv);
  //hists.push_back(TO_LW400_nsv);
  //hists.push_back(TO_LW500_nsv);
  hists.push_back(TO_dataRunB_svd);
  hists.push_back(TO_dataRunC_svd);
  hists.push_back(TO_ZLL_svd);
  hists.push_back(TO_TT_svd);
  hists.push_back(TO_W3J_svd);
  hists.push_back(TO_W2J_svd);
  hists.push_back(TO_W1J_svd);
  //hists.push_back(//TO_WW_svd);
  //hists.push_back(////TO_WZ_svd);
  //hists.push_back(//TO_TTZ_svd);
  hists.push_back(TO_LW200_svd);
  //hists.push_back(TO_LW200_svd);
  //hists.push_back(TO_LW400_svd);
  //hists.push_back(TO_LW500_svd);
  hists.push_back(TO_dataRunB_Elept);
  hists.push_back(TO_dataRunC_Elept);
  hists.push_back(TO_ZLL_Elept);
  hists.push_back(TO_TT_Elept);
  hists.push_back(TO_W3J_Elept);
  hists.push_back(TO_W2J_Elept);
  hists.push_back(TO_W1J_Elept);
  //hists.push_back(//TO_WW_Elept);
  //hists.push_back(////TO_WZ_Elept);
  //hists.push_back(//TO_TTZ_Elept);
  hists.push_back(TO_LW200_Elept);
  //hists.push_back(TO_LW200_Elept);
  //hists.push_back(TO_LW400_svd);
  //hists.push_back(TO_LW500_svd);
  hists.push_back(TO_dataRunB_DieledR);
  hists.push_back(TO_dataRunC_DieledR);
  hists.push_back(TO_ZLL_DieledR);
  hists.push_back(TO_TT_DieledR);
  hists.push_back(TO_W3J_DieledR);
  hists.push_back(TO_W2J_DieledR);
  hists.push_back(TO_W1J_DieledR);
  //hists.push_back(//TO_WW_DieledR);
  //hists.push_back(////TO_WZ_DieledR);
  //hists.push_back(//TO_TTZ_DieledR);
  hists.push_back(TO_LW200_DieledR);
  //hists.push_back(TO_LW200_DieledR);
  //hists.push_back(TO_LW400_svd);
  //hists.push_back(TO_LW500_svd);
  hists.push_back(TO_dataRunB_LWdR);
  hists.push_back(TO_dataRunC_LWdR);
  hists.push_back(TO_ZLL_LWdR);
  hists.push_back(TO_TT_LWdR);
  hists.push_back(TO_W3J_LWdR);
  hists.push_back(TO_W2J_LWdR);
  hists.push_back(TO_W1J_LWdR);
  //hists.push_back(//TO_WW_LWdR);
  //hists.push_back(////TO_WZ_LWdR);
  //hists.push_back(//TO_TTZ_LWdR);
  hists.push_back(TO_LW200_LWdR);
  //hists.push_back(TO_LW200_LWdR);
  //hists.push_back(TO_LW400_svd);
  //hists.push_back(TO_LW500_svd);
  hists.push_back(TO_dataRunB_DiJetdR);
  hists.push_back(TO_dataRunC_DiJetdR);
  hists.push_back(TO_ZLL_DiJetdR);
  hists.push_back(TO_TT_DiJetdR);
  hists.push_back(TO_W3J_DiJetdR);
  hists.push_back(TO_W2J_DiJetdR);
  hists.push_back(TO_W1J_DiJetdR);
  //hists.push_back(//TO_WW_DiJetdR);
  //hists.push_back(////TO_WZ_DiJetdR);
  //hists.push_back(//TO_TTZ_DiJetdR);
  hists.push_back(TO_LW200_DiJetdR);
  //hists.push_back(TO_LW200_DiJetdR);
  //hists.push_back(TO_LW400_svd);
  //hists.push_back(TO_LW500_svd);
  hists.push_back(TO_dataRunB_BJetPt);
  hists.push_back(TO_dataRunC_BJetPt);
  hists.push_back(TO_ZLL_BJetPt);
  hists.push_back(TO_TT_BJetPt);
  hists.push_back(TO_W3J_BJetPt);
  hists.push_back(TO_W2J_BJetPt);
  hists.push_back(TO_W1J_BJetPt);
  //hists.push_back(//TO_WW_BJetPt);
  //hists.push_back(////TO_WZ_BJetPt);
  //hists.push_back(//TO_TTZ_BJetPt);
  hists.push_back(TO_LW200_BJetPt);
  //hists.push_back(TO_LW200_BJetPt);
  //hists.push_back(TO_LW400_svd);
  //hists.push_back(TO_LW500_svd);
  hists.push_back(TO_dataRunB_SBJetPt);
  hists.push_back(TO_dataRunC_SBJetPt);
  hists.push_back(TO_ZLL_SBJetPt);
  hists.push_back(TO_TT_SBJetPt);
  hists.push_back(TO_W3J_SBJetPt);
  hists.push_back(TO_W2J_SBJetPt);
  hists.push_back(TO_W1J_SBJetPt);
  //hists.push_back(//TO_WW_SBJetPt);
  //hists.push_back(////TO_WZ_SBJetPt);
  //hists.push_back(//TO_TTZ_SBJetPt);
  hists.push_back(TO_LW200_SBJetPt);
  //hists.push_back(TO_LW200_SBJetPt);
  //hists.push_back(TO_LW400_svd);
  //hists.push_back(TO_LW500_svd);
  hists.push_back(TO_dataRunB_NJet);
  hists.push_back(TO_dataRunC_NJet);
  hists.push_back(TO_ZLL_NJet);
  hists.push_back(TO_TT_NJet);
  hists.push_back(TO_W3J_NJet);
  hists.push_back(TO_W2J_NJet);
  hists.push_back(TO_W1J_NJet);
  //hists.push_back(//TO_WW_NJet);
  //hists.push_back(////TO_WZ_NJet);
  //hists.push_back(//TO_TTZ_NJet);
  hists.push_back(TO_LW200_NJet);
  //hists.push_back(TO_LW200_NJet);
  //hists.push_back(TO_LW400_svd);
  //hists.push_back(TO_LW500_svd);
  hists.push_back(TO_dataRunB_NEle);
  hists.push_back(TO_dataRunC_NEle);
  hists.push_back(TO_ZLL_NEle);
  hists.push_back(TO_TT_NEle);
  hists.push_back(TO_W3J_NEle);
  hists.push_back(TO_W2J_NEle);
  hists.push_back(TO_W1J_NEle);
  //hists.push_back(//TO_WW_NEle);
  //hists.push_back(////TO_WZ_NEle);
  //hists.push_back(//TO_TTZ_NEle);
  hists.push_back(TO_LW200_NEle);
  //hists.push_back(TO_LW200_NEle);
  //hists.push_back(TO_LW400_svd);
  //hists.push_back(TO_LW500_svd);

  hists.push_back(HQ_dataRunB_npv);
  hists.push_back(HQ_dataRunC_npv);
  hists.push_back(HQ_ZLL_npv);
  hists.push_back(HQ_TT_npv);
  hists.push_back(HQ_W3J_npv);
  hists.push_back(HQ_W2J_npv);
  hists.push_back(HQ_W1J_npv);
  hists.push_back(HQ_LW200_npv);
  hists.push_back(HQ_dataRunB_JetMass);
  hists.push_back(HQ_dataRunC_JetMass);
  hists.push_back(HQ_ZLL_JetMass);
  hists.push_back(HQ_TT_JetMass);
  hists.push_back(HQ_W3J_JetMass);
  hists.push_back(HQ_W2J_JetMass);
  hists.push_back(HQ_W1J_JetMass);
  hists.push_back(HQ_LW200_JetMass);
  hists.push_back(HQ_dataRunB_LWMass);
  hists.push_back(HQ_dataRunC_LWMass);
  hists.push_back(HQ_ZLL_LWMass);
  hists.push_back(HQ_TT_LWMass);
  hists.push_back(HQ_W3J_LWMass);
  hists.push_back(HQ_W2J_LWMass);
  hists.push_back(HQ_W1J_LWMass);
  hists.push_back(HQ_LW200_LWMass);
  //hists.push_back(//HQ_WW_npv);
  //hists.push_back(//HQ_WZ_npv);
  //hists.push_back(////HQ_TTZ_npv);
  //hists.push_back(//HQ_WW_JetMass);
  //hists.push_back(//HQ_WZ_JetMass);
  //hists.push_back(////HQ_TTZ_JetMass);
  //hists.push_back(//HQ_WW_LWMass);
  //hists.push_back(//HQ_WZ_LWMass);
  //hists.push_back(////HQ_TTZ_LWMass);
  //hists.push_back(//HQ_LW300_LWMass);
  //hists.push_back(HQ_LW400_LWMass);
  //hists.push_back(HQ_LW500_LWMass);
  //hists.push_back(//HQ_LW300_JetMass);
  //hists.push_back(HQ_LW400_JetMass);
  //hists.push_back(HQ_LW500_JetMass);
  //hists.push_back(//HQ_LW300_npv);
  //hists.push_back(HQ_LW400_npv);
  //hists.push_back(HQ_LW500_npv);
  hists.push_back(HQ_dataRunB_nsv);
  hists.push_back(HQ_dataRunC_nsv);
  hists.push_back(HQ_ZLL_nsv);
  hists.push_back(HQ_TT_nsv);
  hists.push_back(HQ_W3J_nsv);
  hists.push_back(HQ_W2J_nsv);
  hists.push_back(HQ_W1J_nsv);
  //hists.push_back(//HQ_WW_nsv);
  //hists.push_back(//HQ_WZ_nsv);
  //hists.push_back(////HQ_TTZ_nsv);
  hists.push_back(HQ_LW200_nsv);
  //hists.push_back(HQ_LW200_nsv);
  //hists.push_back(HQ_LW400_nsv);
  //hists.push_back(HQ_LW500_nsv);
  hists.push_back(HQ_dataRunB_svd);
  hists.push_back(HQ_dataRunC_svd);
  hists.push_back(HQ_ZLL_svd);
  hists.push_back(HQ_TT_svd);
  hists.push_back(HQ_W3J_svd);
  hists.push_back(HQ_W2J_svd);
  hists.push_back(HQ_W1J_svd);
  //hists.push_back(//HQ_WW_svd);
  //hists.push_back(//HQ_WZ_svd);
  //hists.push_back(////HQ_TTZ_svd);
  hists.push_back(HQ_LW200_svd);
  //hists.push_back(HQ_LW200_svd);
  //hists.push_back(HQ_LW400_svd);
  //hists.push_back(HQ_LW500_svd);
  hists.push_back(HQ_dataRunB_Elept);
  hists.push_back(HQ_dataRunC_Elept);
  hists.push_back(HQ_ZLL_Elept);
  hists.push_back(HQ_TT_Elept);
  hists.push_back(HQ_W3J_Elept);
  hists.push_back(HQ_W2J_Elept);
  hists.push_back(HQ_W1J_Elept);
  //hists.push_back(//HQ_WW_Elept);
  //hists.push_back(//HQ_WZ_Elept);
  //hists.push_back(////HQ_TTZ_Elept);
  hists.push_back(HQ_LW200_Elept);
  //hists.push_back(HQ_LW200_Elept);
  //hists.push_back(HQ_LW400_svd);
  //hists.push_back(HQ_LW500_svd);
  hists.push_back(HQ_dataRunB_DieledR);
  hists.push_back(HQ_dataRunC_DieledR);
  hists.push_back(HQ_ZLL_DieledR);
  hists.push_back(HQ_TT_DieledR);
  hists.push_back(HQ_W3J_DieledR);
  hists.push_back(HQ_W2J_DieledR);
  hists.push_back(HQ_W1J_DieledR);
  //hists.push_back(//HQ_WW_DieledR);
  //hists.push_back(//HQ_WZ_DieledR);
  //hists.push_back(////HQ_TTZ_DieledR);
  hists.push_back(HQ_LW200_DieledR);
  //hists.push_back(HQ_LW200_DieledR);
  //hists.push_back(HQ_LW400_svd);
  //hists.push_back(HQ_LW500_svd);
  hists.push_back(HQ_dataRunB_LWdR);
  hists.push_back(HQ_dataRunC_LWdR);
  hists.push_back(HQ_ZLL_LWdR);
  hists.push_back(HQ_TT_LWdR);
  hists.push_back(HQ_W3J_LWdR);
  hists.push_back(HQ_W2J_LWdR);
  hists.push_back(HQ_W1J_LWdR);
  //hists.push_back(//HQ_WW_LWdR);
  //hists.push_back(//HQ_WZ_LWdR);
  //hists.push_back(////HQ_TTZ_LWdR);
  hists.push_back(HQ_LW200_LWdR);
  //hists.push_back(HQ_LW200_LWdR);
  //hists.push_back(HQ_LW400_svd);
  //hists.push_back(HQ_LW500_svd);
  hists.push_back(HQ_dataRunB_DiJetdR);
  hists.push_back(HQ_dataRunC_DiJetdR);
  hists.push_back(HQ_ZLL_DiJetdR);
  hists.push_back(HQ_TT_DiJetdR);
  hists.push_back(HQ_W3J_DiJetdR);
  hists.push_back(HQ_W2J_DiJetdR);
  hists.push_back(HQ_W1J_DiJetdR);
  //hists.push_back(//HQ_WW_DiJetdR);
  //hists.push_back(//HQ_WZ_DiJetdR);
  //hists.push_back(////HQ_TTZ_DiJetdR);
  hists.push_back(HQ_LW200_DiJetdR);
  //hists.push_back(HQ_LW200_DiJetdR);
  //hists.push_back(HQ_LW400_svd);
  //hists.push_back(HQ_LW500_svd);
  hists.push_back(HQ_dataRunB_BJetPt);
  hists.push_back(HQ_dataRunC_BJetPt);
  hists.push_back(HQ_ZLL_BJetPt);
  hists.push_back(HQ_TT_BJetPt);
  hists.push_back(HQ_W3J_BJetPt);
  hists.push_back(HQ_W2J_BJetPt);
  hists.push_back(HQ_W1J_BJetPt);
  //hists.push_back(//HQ_WW_BJetPt);
  //hists.push_back(//HQ_WZ_BJetPt);
  //hists.push_back(////HQ_TTZ_BJetPt);
  hists.push_back(HQ_LW200_BJetPt);
  //hists.push_back(HQ_LW200_BJetPt);
  //hists.push_back(HQ_LW400_svd);
  //hists.push_back(HQ_LW500_svd);
  hists.push_back(HQ_dataRunB_SBJetPt);
  hists.push_back(HQ_dataRunC_SBJetPt);
  hists.push_back(HQ_ZLL_SBJetPt);
  hists.push_back(HQ_TT_SBJetPt);
  hists.push_back(HQ_W3J_SBJetPt);
  hists.push_back(HQ_W2J_SBJetPt);
  hists.push_back(HQ_W1J_SBJetPt);
  //hists.push_back(//HQ_WW_SBJetPt);
  //hists.push_back(//HQ_WZ_SBJetPt);
  //hists.push_back(////HQ_TTZ_SBJetPt);
  hists.push_back(HQ_LW200_SBJetPt);
  //hists.push_back(HQ_LW200_SBJetPt);
  //hists.push_back(HQ_LW400_svd);
  //hists.push_back(HQ_LW500_svd);
  hists.push_back(HQ_dataRunB_NJet);
  hists.push_back(HQ_dataRunC_NJet);
  hists.push_back(HQ_ZLL_NJet);
  hists.push_back(HQ_TT_NJet);
  hists.push_back(HQ_W3J_NJet);
  hists.push_back(HQ_W2J_NJet);
  hists.push_back(HQ_W1J_NJet);
  //hists.push_back(//HQ_WW_NJet);
  //hists.push_back(//HQ_WZ_NJet);
  //hists.push_back(////HQ_TTZ_NJet);
  hists.push_back(HQ_LW200_NJet);
  //hists.push_back(HQ_LW200_NJet);
  //hists.push_back(HQ_LW400_svd);
  //hists.push_back(HQ_LW500_svd);
  hists.push_back(HQ_dataRunB_NEle);
  hists.push_back(HQ_dataRunC_NEle);
  hists.push_back(HQ_ZLL_NEle);
  hists.push_back(HQ_TT_NEle);
  hists.push_back(HQ_W3J_NEle);
  hists.push_back(HQ_W2J_NEle);
  hists.push_back(HQ_W1J_NEle);
  //hists.push_back(//HQ_WW_NEle);
  //hists.push_back(//HQ_WZ_NEle);
  //hists.push_back(////HQ_TTZ_NEle);
  hists.push_back(HQ_LW200_NEle);
  //hists.push_back(HQ_LW200_NEle);
  //hists.push_back(HQ_LW400_svd);
  //hists.push_back(HQ_LW500_svd);

  hists.push_back(SG_dataRunB_npv);
  hists.push_back(SG_dataRunC_npv);
  hists.push_back(SG_ZLL_npv);
  hists.push_back(SG_TT_npv);
  hists.push_back(SG_W3J_npv);
  hists.push_back(SG_W2J_npv);
  hists.push_back(SG_W1J_npv);
  hists.push_back(SG_LW200_npv);
  hists.push_back(SG_dataRunB_JetMass);
  hists.push_back(SG_dataRunC_JetMass);
  hists.push_back(SG_ZLL_JetMass);
  hists.push_back(SG_TT_JetMass);
  hists.push_back(SG_W3J_JetMass);
  hists.push_back(SG_W2J_JetMass);
  hists.push_back(SG_W1J_JetMass);
  hists.push_back(SG_LW200_JetMass);
  hists.push_back(SG_dataRunB_LWMass);
  hists.push_back(SG_dataRunC_LWMass);
  hists.push_back(SG_ZLL_LWMass);
  hists.push_back(SG_TT_LWMass);
  hists.push_back(SG_W3J_LWMass);
  hists.push_back(SG_W2J_LWMass);
  hists.push_back(SG_W1J_LWMass);
  hists.push_back(SG_LW200_LWMass);
  //hists.push_back(SG_WW_npv);
  //hists.push_back(SG_WZ_npv);
  //hists.push_back(SG_TTZ_npv);
  //hists.push_back(SG_WW_JetMass);
  //hists.push_back(SG_WZ_JetMass);
  //hists.push_back(SG_TTZ_JetMass);
  //hists.push_back(SG_WW_LWMass);
  //hists.push_back(SG_WZ_LWMass);
  //hists.push_back(SG_TTZ_LWMass);
  //hists.push_back(//HQ_LW300_LWMass);
  //hists.push_back(SG_LW400_LWMass);
  //hists.push_back(SG_LW500_LWMass);
  //hists.push_back(//HQ_LW300_JetMass);
  //hists.push_back(SG_LW400_JetMass);
  //hists.push_back(SG_LW500_JetMass);
  //hists.push_back(//HQ_LW300_npv);
  //hists.push_back(SG_LW400_npv);
  //hists.push_back(SG_LW500_npv);
  hists.push_back(SG_dataRunB_nsv);
  hists.push_back(SG_dataRunC_nsv);
  hists.push_back(SG_ZLL_nsv);
  hists.push_back(SG_TT_nsv);
  hists.push_back(SG_W3J_nsv);
  hists.push_back(SG_W2J_nsv);
  hists.push_back(SG_W1J_nsv);
  //hists.push_back(SG_WW_nsv);
  //hists.push_back(SG_WZ_nsv);
  //hists.push_back(SG_TTZ_nsv);
  hists.push_back(SG_LW200_nsv);
  //hists.push_back(SG_LW200_nsv);
  //hists.push_back(SG_LW400_nsv);
  //hists.push_back(SG_LW500_nsv);
  hists.push_back(SG_dataRunB_svd);
  hists.push_back(SG_dataRunC_svd);
  hists.push_back(SG_ZLL_svd);
  hists.push_back(SG_TT_svd);
  hists.push_back(SG_W3J_svd);
  hists.push_back(SG_W2J_svd);
  hists.push_back(SG_W1J_svd);
  //hists.push_back(SG_WW_svd);
  //hists.push_back(SG_WZ_svd);
  //hists.push_back(SG_TTZ_svd);
  hists.push_back(SG_LW200_svd);
  //hists.push_back(SG_LW200_svd);
  //hists.push_back(SG_LW400_svd);
  //hists.push_back(SG_LW500_svd);
  hists.push_back(SG_dataRunB_Elept);
  hists.push_back(SG_dataRunC_Elept);
  hists.push_back(SG_ZLL_Elept);
  hists.push_back(SG_TT_Elept);
  hists.push_back(SG_W3J_Elept);
  hists.push_back(SG_W2J_Elept);
  hists.push_back(SG_W1J_Elept);
  //hists.push_back(SG_WW_Elept);
  //hists.push_back(SG_WZ_Elept);
  //hists.push_back(SG_TTZ_Elept);
  hists.push_back(SG_LW200_Elept);
  //hists.push_back(SG_LW200_Elept);
  //hists.push_back(SG_LW400_svd);
  //hists.push_back(SG_LW500_svd);
  hists.push_back(SG_dataRunB_DieledR);
  hists.push_back(SG_dataRunC_DieledR);
  hists.push_back(SG_ZLL_DieledR);
  hists.push_back(SG_TT_DieledR);
  hists.push_back(SG_W3J_DieledR);
  hists.push_back(SG_W2J_DieledR);
  hists.push_back(SG_W1J_DieledR);
  //hists.push_back(SG_WW_DieledR);
  //hists.push_back(SG_WZ_DieledR);
  //hists.push_back(SG_TTZ_DieledR);
  hists.push_back(SG_LW200_DieledR);
  //hists.push_back(SG_LW200_DieledR);
  //hists.push_back(SG_LW400_svd);
  //hists.push_back(SG_LW500_svd);
  hists.push_back(SG_dataRunB_LWdR);
  hists.push_back(SG_dataRunC_LWdR);
  hists.push_back(SG_ZLL_LWdR);
  hists.push_back(SG_TT_LWdR);
  hists.push_back(SG_W3J_LWdR);
  hists.push_back(SG_W2J_LWdR);
  hists.push_back(SG_W1J_LWdR);
  //hists.push_back(SG_WW_LWdR);
  //hists.push_back(SG_WZ_LWdR);
  //hists.push_back(SG_TTZ_LWdR);
  hists.push_back(SG_LW200_LWdR);
  //hists.push_back(SG_LW200_LWdR);
  //hists.push_back(SG_LW400_svd);
  //hists.push_back(SG_LW500_svd);
  hists.push_back(SG_dataRunB_DiJetdR);
  hists.push_back(SG_dataRunC_DiJetdR);
  hists.push_back(SG_ZLL_DiJetdR);
  hists.push_back(SG_TT_DiJetdR);
  hists.push_back(SG_W3J_DiJetdR);
  hists.push_back(SG_W2J_DiJetdR);
  hists.push_back(SG_W1J_DiJetdR);
  //hists.push_back(SG_WW_DiJetdR);
  //hists.push_back(SG_WZ_DiJetdR);
  //hists.push_back(SG_TTZ_DiJetdR);
  hists.push_back(SG_LW200_DiJetdR);
  //hists.push_back(SG_LW200_DiJetdR);
  //hists.push_back(SG_LW400_svd);
  //hists.push_back(SG_LW500_svd);
  hists.push_back(SG_dataRunB_BJetPt);
  hists.push_back(SG_dataRunC_BJetPt);
  hists.push_back(SG_ZLL_BJetPt);
  hists.push_back(SG_TT_BJetPt);
  hists.push_back(SG_W3J_BJetPt);
  hists.push_back(SG_W2J_BJetPt);
  hists.push_back(SG_W1J_BJetPt);
  //hists.push_back(SG_WW_BJetPt);
  //hists.push_back(SG_WZ_BJetPt);
  //hists.push_back(SG_TTZ_BJetPt);
  hists.push_back(SG_LW200_BJetPt);
  //hists.push_back(SG_LW200_BJetPt);
  //hists.push_back(SG_LW400_svd);
  //hists.push_back(SG_LW500_svd);
  hists.push_back(SG_dataRunB_SBJetPt);
  hists.push_back(SG_dataRunC_SBJetPt);
  hists.push_back(SG_ZLL_SBJetPt);
  hists.push_back(SG_TT_SBJetPt);
  hists.push_back(SG_W3J_SBJetPt);
  hists.push_back(SG_W2J_SBJetPt);
  hists.push_back(SG_W1J_SBJetPt);
  //hists.push_back(SG_WW_SBJetPt);
  //hists.push_back(SG_WZ_SBJetPt);
  //hists.push_back(SG_TTZ_SBJetPt);
  hists.push_back(SG_LW200_SBJetPt);
  //hists.push_back(SG_LW200_SBJetPt);
  //hists.push_back(SG_LW400_svd);
  //hists.push_back(SG_LW500_svd);
  hists.push_back(SG_dataRunB_NJet);
  hists.push_back(SG_dataRunC_NJet);
  hists.push_back(SG_ZLL_NJet);
  hists.push_back(SG_TT_NJet);
  hists.push_back(SG_W3J_NJet);
  hists.push_back(SG_W2J_NJet);
  hists.push_back(SG_W1J_NJet);
  //hists.push_back(SG_WW_NJet);
  //hists.push_back(SG_WZ_NJet);
  //hists.push_back(SG_TTZ_NJet);
  hists.push_back(SG_LW200_NJet);
  //hists.push_back(SG_LW200_NJet);
  //hists.push_back(SG_LW400_svd);
  //hists.push_back(SG_LW500_svd);
  hists.push_back(SG_dataRunB_NEle);
  hists.push_back(SG_dataRunC_NEle);
  hists.push_back(SG_ZLL_NEle);
  hists.push_back(SG_TT_NEle);
  hists.push_back(SG_W3J_NEle);
  hists.push_back(SG_W2J_NEle);
  hists.push_back(SG_W1J_NEle);
  //hists.push_back(SG_WW_NEle);
  //hists.push_back(SG_WZ_NEle);
  //hists.push_back(SG_TTZ_NEle);
  hists.push_back(SG_LW200_NEle);
  //hists.push_back(SG_LW200_NEle);
  //hists.push_back(SG_LW400_svd);
  //hists.push_back(SG_LW500_svd);


// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   TTree* tree = 0;
   TFile *f = TFile::Open(filename);
   //trigger should go first as it is the more complicated one
   tree = (TTree*)f->Get("mytriggers/Events");
   //Get trees for friendship
   tevents = (TTree*)f->Get("myevents/Events");
   tvertex = (TTree*)f->Get("mypvertex/Events");
   tmuons = (TTree*)f->Get("mymuons/Events");
   ttaus = (TTree*)f->Get("mytaus/Events");
   tmets = (TTree*)f->Get("mymets/Events");
   tjets = (TTree*)f->Get("myjets/Events");
   telectrons = (TTree*)f->Get("myelectrons/Events");
   ttrigobjs = (TTree*)f->Get("mytrigEvent/Events");
   //Make friends so we can have access to friends variables
   //we may not use all of the available information
   //it is just an example
   tree->AddFriend(tevents);
   tree->AddFriend(tvertex);
   tree->AddFriend(tmuons);
   tree->AddFriend(ttaus);
   tree->AddFriend(tmets);
   tree->AddFriend(tjets);
   tree->AddFriend(telectrons);
   tree->AddFriend(ttrigobjs);
   Init(tree);
}

EventLoopAnalysisTemplate::~EventLoopAnalysisTemplate()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t EventLoopAnalysisTemplate::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}



Long64_t EventLoopAnalysisTemplate::LoadTree(Long64_t entry)
{
  //cout<<" Set the environment to read one entry"<<endl;
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }

   return centry;
}


void EventLoopAnalysisTemplate::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   triggermap =0;
   PV_x = 0;
   PV_y = 0;
   PV_z = 0;
   muon_pt = 0;
   muon_eta = 0;
   muon_phi = 0;
   muon_ch = 0;
   muon_tightid = 0;
   muon_pfreliso03all = 0;
   muon_mass = 0;
   tau_pt = 0;
   tau_eta = 0;
   tau_phi = 0;
   tau_ch = 0;
   tau_iddecaymode = 0;
   tau_idisotight = 0;
   tau_idantieletight = 0;
   tau_idantimutight = 0;
   tau_reliso_all = 0;
   tau_mass = 0;
   jet_e = 0;
   jet_pt = 0;
   corr_jet_pt = 0;
   jet_px = 0;
   jet_py = 0;
   jet_pz = 0;
   jet_phi = 0;
   jet_eta = 0;
   NConstituents = 0;
   NeutralHF = 0;
   NeutralEMF = 0;
   MuonF = 0;
   ChargedEMF = 0;
   ChargedHF = 0;
   ChargedMult = 0;
   electron_e = 0;
   electron_pt = 0;
   electron_px = 0;
   electron_py = 0;
   electron_pz = 0;
   electron_phi = 0;
   electron_eta = 0;
   trk_isHQ = 0;
   trigobj_e = 0;
   trigobj_pt = 0;
   trigobj_px = 0;
   trigobj_py = 0;
   trigobj_pz = 0;
   trigobj_eta = 0;
   trigobj_phi = 0;
   secvec_posx = 0;
   secvec_posy = 0;
   secvec_posz = 0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   //Comment out to be able to read map
   //https://root-forum.cern.ch/t/std-map-in-ttree-with-makeclass/14171
   //fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("luminosityBlock", &luminosityBlock, &b_luminosityBlock);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("PV_npvs", &PV_npvs, &b_PV_npvs);
   fChain->SetBranchAddress("numbersecvec", &numbersecvec, &b_numbersecvec);
   fChain->SetBranchAddress("PV_x", &PV_x, &b_PV_x);
   fChain->SetBranchAddress("PV_y", &PV_y, &b_PV_y);
   fChain->SetBranchAddress("PV_z", &PV_z, &b_PV_z);
   fChain->SetBranchAddress("triggermap",&triggermap,&b_triggermap);
   fChain->SetBranchAddress("met_pt", &met_pt, &b_met_pt);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("corr_jet_pt",&corr_jet_pt,&b_corr_jet_pt);
   fChain->SetBranchAddress("jet_pt",&jet_pt,&b_jet_pt);
   fChain->SetBranchAddress("jet_px",&jet_px,&b_jet_px);
   fChain->SetBranchAddress("jet_py",&jet_py,&b_jet_py);
   fChain->SetBranchAddress("jet_pz",&jet_pz,&b_jet_pz);
   fChain->SetBranchAddress("jet_phi",&jet_phi,&b_jet_phi);
   fChain->SetBranchAddress("jet_eta",&jet_eta,&b_jet_eta);
   fChain->SetBranchAddress("jet_e",&jet_e,&b_jet_e);
   fChain->SetBranchAddress("NConstituents",&NConstituents,&b_NConstituents);
   fChain->SetBranchAddress("NeutralHF",&NeutralHF,&b_NeutralHF);
   fChain->SetBranchAddress("NeutralEMF",&NeutralEMF,&b_NeutralEMF);
   fChain->SetBranchAddress("MuonF",&MuonF,&b_MuonF);
   fChain->SetBranchAddress("ChargedEMF",&ChargedEMF,&b_ChargedEMF);
   fChain->SetBranchAddress("ChargedHF",&ChargedHF,&b_ChargedHF);
   fChain->SetBranchAddress("ChargedMult",&ChargedMult,&b_ChargedMult);
   fChain->SetBranchAddress("electron_pt",&electron_pt,&b_electron_pt);
   fChain->SetBranchAddress("electron_px",&electron_px,&b_electron_px);
   fChain->SetBranchAddress("electron_py",&electron_py,&b_electron_py);
   fChain->SetBranchAddress("electron_pz",&electron_pz,&b_electron_pz);
   fChain->SetBranchAddress("electron_phi",&electron_phi,&b_electron_phi);
   fChain->SetBranchAddress("electron_eta",&electron_eta,&b_electron_eta);
   fChain->SetBranchAddress("electron_e",&electron_e,&b_electron_e);
   fChain->SetBranchAddress("trk_isHQ",&trk_isHQ,&b_trk_isHQ);
   fChain->SetBranchAddress("trigobj_px",&trigobj_px,&b_trigobj_px);
   fChain->SetBranchAddress("trigobj_py",&trigobj_py,&b_trigobj_py);
   fChain->SetBranchAddress("trigobj_pz",&trigobj_pz,&b_trigobj_pz);
   fChain->SetBranchAddress("trigobj_phi",&trigobj_phi,&b_trigobj_phi);
   fChain->SetBranchAddress("trigobj_eta",&trigobj_eta,&b_trigobj_eta);
   fChain->SetBranchAddress("trigobj_e",&trigobj_e,&b_trigobj_e);
   fChain->SetBranchAddress("secvec_posx",&secvec_posx,&b_secvec_posx);
   fChain->SetBranchAddress("secvec_posy",&secvec_posy,&b_secvec_posy);
   fChain->SetBranchAddress("secvec_posz",&secvec_posz,&b_secvec_posz);

   Notify();
}


Bool_t EventLoopAnalysisTemplate::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void EventLoopAnalysisTemplate::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

void EventLoopAnalysisTemplate::Loop()
{
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //Just an informative printout
    if(jentry%100000 == 0) {
      cout<<"Processed "<<jentry<<" events out of "<<nentries<<endl;
    }
    //cout<<"Load the current event"<<endl;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;

    analysis();

  }


}


//-----------------------------------------------------------------
void EventLoopAnalysisTemplate::analysis()
{
//-----------------------------------------------------------------

  //cout<<"analysis() execution"<<endl;
  histograms("NF");

  //minimal selection including trigger requirement
  if (!MinimalSelection()) return;
  //counter_ms++;


  //fill histograms for signal region
  histograms("TF");

  /////Identify electron as Trig OBJ
  std::vector<bool> TobjisFound;
  TobjisFound.clear();
  size_t objcount=0;
  for (size_t y=0; y<trigobj_e->size(); y++){
    float saveDR=100;
    //bool saveQ=false;
    for (size_t x=0; x<electron_e->size(); x++){
      float DRet=deltaR(electron_eta->at(x),electron_phi->at(x),trigobj_eta->at(y),trigobj_phi->at(y));
      if(DRet<saveDR){
         saveDR=DRet;
         //saveQ=trk_isHQ;
      }
    }
    if (saveDR<0.1){
      TobjisFound.push_back(true);
      objcount++;
    }
    else TobjisFound.push_back(false);
  }
  if(objcount<2) return;

  histograms("TO");

  //////////JetSelection///////
  vector<bool> JetisHQ;
  JetisHQ.clear();
  size_t Jhqcount=0;
  for(size_t x=0; x<jet_e->size(); x++){
    if(abs(jet_eta->at(x))<2.5){
      if(NConstituents->at(x)>1 && NeutralHF->at(x)<0.9 && MuonF->at(x)<0.8){
        JetisHQ.push_back(true);
        Jhqcount++;
      }
      else JetisHQ.push_back(false);
    }
    else{
      if(NConstituents->at(x)>1 && NeutralHF->at(x)<0.9 && MuonF->at(x)<0.8 &&
          ChargedHF->at(x)>0 && ChargedEMF->at(x)>0 && ChargedMult->at(x)<0.80){
            JetisHQ.push_back(true);
            Jhqcount++;
          }
      else JetisHQ.push_back(false);
    }
  }
  if(Jhqcount<4) return;

  /////Obj selection
  vector<int>  TobjisHQ;
  TobjisHQ.clear();
  size_t hqcount=0;
  for (size_t y=0; y<trigobj_e->size(); y++){
    float saveDR=100;
    int saveQ=0;
    for (size_t x=0; x<electron_e->size(); x++){
      float DRet=deltaR(electron_eta->at(x),electron_phi->at(x),trigobj_eta->at(y),trigobj_phi->at(y));
      if(DRet<saveDR){
         saveDR=DRet;
         saveQ=trk_isHQ->at(x);
      }
    }
    if (saveDR<0.1){
      TobjisHQ.push_back(saveQ);
      if(saveQ==1) hqcount++;
    }
    else {
      TobjisHQ.push_back(saveQ);
    }
  }
  if(hqcount<2) return;

  histograms("HQ");


}//------analysis()

/*
 * Perform a selection on the minimal requirements of an event
 */
//-----------------------------------------------------------------
bool EventLoopAnalysisTemplate::MinimalSelection()
{
//-----------------------------------------------------------------

 //cout<<"Applying minimal selection"<<endl;
  bool isTrigger = false;

  //Check trigger and acceptance bit
  for(size_t x=0; x<4; x++){
    for (map<string, int>::iterator it=triggermap->begin();it!=triggermap->end();it++){
      if(it->first.find(triggerRequest[x])!=string::npos &&
         it->second!=0){
  	 //cout<<it->first<<"  "<<it->second<<endl;
        isTrigger = true;
      }
    }
  }

  return isTrigger;

}//------MinimalSelection

///////////////////////Histograms////////////////////////
void EventLoopAnalysisTemplate::histograms(string cut) {
  Int_t histsize = sizeof(hists)/sizeof(hists[0]);
  for (Int_t j=0;j<hists.size();++j){
    TString histname = TString(hists.at(j)->GetName());
    TString thecut = histname(0,histname.First("_"));
    histname = histname(histname.First("_")+1,histname.Sizeof());
    TString thelabel = histname(0,histname.First("_"));
    TString thevar = histname(histname.First("_")+1,histname.Sizeof());

    if (thecut == cut && thelabel == labeltag){

      //primary vertices
      //cout<<"npv\n";
      if(thevar == "npv"){
	       hists.at(j)->Fill(PV_npvs,theweight);
      }

      /*//secondary Vertices
      //cout<<"nsv\n";
      if(thevar == "nsv"){
	       hists.at(j)->Fill(numbersecvec,theweight);
      }

      //NF secondary vertex displacements
      //cout<<"svd\n";
      if(thevar == "svd"){
        float dx,dy,dz,disp;
        for (size_t i = 0; i < secvec_posx->size(); i++) {
          dx=PV_x->at(0)-secvec_posx->at(i);
          dy=PV_y->at(0)-secvec_posy->at(i);
          dz=PV_z->at(0)-secvec_posz->at(i);
          disp=sqrt( dx*dx + dy*dy + dz*dz );
          hists.at(j)->Fill(disp,theweight);
        }
      }*/
      //JetMass
      //cout<<"JetMass\n";
      if(thevar == "JetMass"){
        ////////Jet Inv Mass ///////////////////
        float px,py,pz,e,m;
        //correctedJetMass
        //float corr_pt;
        for(size_t i=0; i < jet_e->size(); i++){
          for(size_t k=i+1; k < jet_e->size(); k++){
            px=0,py=0,pz=0,e=0,m=0;
            if(i!=k){
              px=cos(jet_phi->at(i))*corr_jet_pt->at(i) + cos(jet_phi->at(k))*corr_jet_pt->at(k);
              py=sin(jet_phi->at(i))*corr_jet_pt->at(i) + sin(jet_phi->at(k))*corr_jet_pt->at(k);
              float corr1=corr_jet_pt->at(i)/jet_pt->at(i);
              float corr2=corr_jet_pt->at(k)/jet_pt->at(k);
              pz=jet_pz->at(i)*corr1+jet_pz->at(k)*corr2;
              e=jet_e->at(i)*corr1+jet_e->at(k)*corr2;
              m=sqrt( e*e - px*px - py*py - pz*pz );

              hists.at(j)->Fill(m,theweight);
            }
          }
        }
      }
      //cout<<"LWMass\n";
      if(thevar == "LWMass"){
        ////////Jet Inv Mass ///////////////////
        float px,py,pz,e,m;
        //correctedJetMass
        //float corr_pt;
        for(size_t i=0; i < jet_e->size(); i++){
          for(size_t k=i+1; k < jet_e->size(); k++){
            for(size_t l=0; l < electron_e->size(); l++){
              px=0,py=0,pz=0,e=0,m=0;
              if(i!=k){
                px=cos(jet_phi->at(i))*corr_jet_pt->at(i) + cos(jet_phi->at(k))*corr_jet_pt->at(k) + electron_px->at(l);
                py=sin(jet_phi->at(i))*corr_jet_pt->at(i) + sin(jet_phi->at(k))*corr_jet_pt->at(k) + electron_py->at(l);
                float corr1=corr_jet_pt->at(i)/jet_pt->at(i);
                float corr2=corr_jet_pt->at(k)/jet_pt->at(k);
                pz=jet_pz->at(i)*corr1+jet_pz->at(k)*corr2+electron_pz->at(l);
                e=jet_e->at(i)*corr1+jet_e->at(k)*corr2+electron_e->at(l);
                m=sqrt( e*e - px*px - py*py - pz*pz );

                hists.at(j)->Fill(m,theweight);
              }
            }
          }
        }
      }
      //cout<<"Elept\n";
      if(thevar == "Elept"){
        for(size_t l=0; l < electron_e->size(); l++){
          hists.at(j)->Fill(electron_pt->at(l),theweight);
        }
      }
      //cout<<"DieledR\n";
      if(thevar == "DieledR"){
        for(size_t l=0; l < electron_e->size(); l++){
          for(size_t k=l+1; k < electron_e->size(); k++){
            float dieledR= deltaR(electron_eta->at(l),electron_phi->at(l),electron_eta->at(k),electron_phi->at(k));
            hists.at(j)->Fill(dieledR,theweight);
          }
        }
      }
      //cout<<"LWdR\n";
      if(thevar == "LWdR"){
        for(size_t l=0; l < electron_e->size(); l++){
          for(size_t k=0; k < jet_e->size(); k++){
            float LWdR= deltaR(electron_eta->at(l),electron_phi->at(l),jet_eta->at(k),jet_phi->at(k));
            hists.at(j)->Fill(LWdR,theweight);
          }
        }
      }
      //cout<<"DiJetdR\n";
      if(thevar == "DiJetdR"){
        for(size_t l=0; l < jet_e->size(); l++){
          for(size_t k=l+1; k < jet_e->size(); k++){
            float DiJetdR= deltaR(jet_eta->at(l),jet_phi->at(l),jet_eta->at(k),jet_phi->at(k));
            hists.at(j)->Fill(DiJetdR,theweight);
          }
        }
      }
      sort(corr_jet_pt->begin(),corr_jet_pt->begin());
      //cout<<"BJetPt\n";
      if(thevar == "BJetPt"){

        if(corr_jet_pt->size()>0) hists.at(j)->Fill(corr_jet_pt->at(0),theweight);

      }
      //cout<<"SBJetPT\n";
      if(thevar == "SBJetPt"){
        if(corr_jet_pt->size()>1)hists.at(j)->Fill(corr_jet_pt->at(1),theweight);
      }
      //cout<<"NJet\n";
      if(thevar == "NJet"){
        hists.at(j)->Fill(jet_e->size(),theweight);
      }
      //cout<<"NEle\n";
      if(thevar == "NEle"){
        hists.at(j)->Fill(electron_e->size(),theweight);
      }
    }
  }
}////////////////////////histograms/////////////////

///////////////deltaR
float EventLoopAnalysisTemplate::deltaR(float eta1, float phi1, float eta2, float phi2) {
  float deta = eta1 - eta2;
  float dphi = std::abs(phi1 - phi2);
  if (dphi > 3.14159)
    dphi -= (2 * 3.14159);
  return sqrt(deta * deta + dphi * dphi);
}//------deltaR




//-----------------------------------------------------------------
int main()
{
//-----------------------------------------------------------------

  gROOT->ProcessLine("#include<map>");

  /*
 * Compute event weights to be used for the respective datasets
 *
 * The event weight reweights the full dataset so that the sum of the weights
 * is equal to the expected number of events in data. The expectation is given by
 * multiplying the integrated luminosity of the data with the cross-section of
 * the process in the datasets divided by the number of simulated events.
 */
  //const float integratedLuminosity = 4.412 * 1000.0; // Run2012B only
  //const float integratedLuminosity = 7.055 * 1000.0; // Run2012C only
  const float integratedLuminosity = 11.467 * 1000.0; // Run2012B+C

  const float W1J_w =  6381.2 / 29784800.0 * integratedLuminosity;
  const float W2J_w =  2039.8 / 30693853.0 * integratedLuminosity;
  const float W3J_w =  612.5 / 15241144.0 * integratedLuminosity;
  const float TT_w = 225.2 / 6423106.0 * integratedLuminosity;
  const float ZLL_w = 3503.7 / 30458871.0 * integratedLuminosity;
  const float LW200_w = 0.0059 / 150000 * integratedLuminosity;
  //const float LW300_w = 0.00096 / 150000 * integratedLuminosity;
  //const float LW400_w = 0.00023 / 150000 * integratedLuminosity;
  //const float LW500_w = 0.00006 / 150000 * integratedLuminosity;
  //const float WW_w = 5.824 / 1933120 * integratedLuminosity;
  //const float WZ_w = 2.207 / 3215990 * integratedLuminosity;
  //const float TTZ_w = 0.175 / 787495 * integratedLuminosity;
  const float dataRunB_w = 1.0;
  const float dataRunC_w = 1.0;


  map<string, pair<string,float> > sampleNames;
  //sampleNames.insert(make_pair("WWJetsTo2L2Nu",make_pair("WW",WW_w)));
  //sampleNames.insert(make_pair("WZJetsTo2L2Q",make_pair("WZ",WZ_w)));
  //sampleNames.insert(make_pair("ttbarZ",make_pair("TTZ",TTZ_w)));
  sampleNames.insert(make_pair("W1JetsToLNu",make_pair("W1J",W1J_w)));
  sampleNames.insert(make_pair("W2JetsToLNu",make_pair("W2J",W2J_w)));
  sampleNames.insert(make_pair("W3JetsToLNu",make_pair("W3J",W3J_w)));
  sampleNames.insert(make_pair("TTbar",make_pair("TT",TT_w)));
  sampleNames.insert(make_pair("DYJetsToLL",make_pair("ZLL",ZLL_w)));
  sampleNames.insert(make_pair("LWSM200DnR",make_pair("LW200",LW200_w)));
  //sampleNames.insert(make_pair("LWSM300DnR",make_pair("LW300",LW300_w)));
  //sampleNames.insert(make_pair("LWSM400DnR",make_pair("LW400",LW400_w)));
  //sampleNames.insert(make_pair("LWSM500DnR",make_pair("LW500",LW500_w)));
  sampleNames.insert(make_pair("Run2012B_DoublePhoton",make_pair("dataRunB",dataRunB_w)));
  sampleNames.insert(make_pair("Run2012C_DoublePhoton",make_pair("dataRunC",dataRunC_w)));




  //loop over sample files with names  defined above
  for(map< string,pair<string,float> >::iterator it=sampleNames.begin();
      it!=sampleNames.end();it++){

    TString samplename = it->first;
    TString thelabel = it->second.first;
    Float_t sampleweight = it->second.second;

    TStopwatch time;
    time.Start();
    cout << ">>> Processing sample " << samplename <<" with label "<<thelabel<<" and weight "<<sampleweight<<":" <<endl;


    TString filename = samplesBasePath+samplename+".root";

    cout<<"Build the analysis object with file "<<filename<<endl;
    EventLoopAnalysisTemplate mytemplate(filename,thelabel,sampleweight);

    cout<<"Run the event loop"<<endl;
    mytemplate.Loop();
    time.Stop();
    time.Print();
  }

  TFile* hfile = new TFile("TriggerFilter/histogramsTrigg.root","RECREATE");

  //Save signal region histos
  NF_dataRunB_npv->Write();
  NF_dataRunC_npv->Write();
  NF_ZLL_npv->Write();
  NF_TT_npv->Write();
  NF_W3J_npv->Write();
  NF_W2J_npv->Write();
  NF_W1J_npv->Write();
  //NF_WW_npv->Write();
  //NF_WZ_npv->Write();
  //NF_TTZ_npv->Write();
  NF_LW200_npv->Write();
  //NF_LW300_npv->Write();
  //NF_LW400_npv->Write();
  //NF_LW500_npv->Write();
  NF_dataRunB_JetMass->Write();
  NF_dataRunC_JetMass->Write();
  NF_ZLL_JetMass->Write();
  NF_TT_JetMass->Write();
  NF_W3J_JetMass->Write();
  NF_W2J_JetMass->Write();
  NF_W1J_JetMass->Write();
  //NF_WW_JetMass->Write();
  //NF_WZ_JetMass->Write();
  //NF_TTZ_JetMass->Write();
  NF_LW200_JetMass->Write();
  //NF_LW300_JetMass->Write();
  //NF_LW400_JetMass->Write();
  //NF_LW500_JetMass->Write();
  NF_dataRunB_LWMass->Write();
  NF_dataRunC_LWMass->Write();
  NF_ZLL_LWMass->Write();
  NF_TT_LWMass->Write();
  NF_W3J_LWMass->Write();
  NF_W2J_LWMass->Write();
  NF_W1J_LWMass->Write();
  //NF_WW_LWMass->Write();
  //NF_WZ_LWMass->Write();
  //NF_TTZ_LWMass->Write();
  NF_LW200_LWMass->Write();
  //NF_LW300_LWMass->Write();
  //NF_LW400_LWMass->Write();
  //NF_LW500_LWMass->Write();
  NF_dataRunB_nsv->Write();
  NF_dataRunC_nsv->Write();
  NF_ZLL_nsv->Write();
  NF_TT_nsv->Write();
  NF_W3J_nsv->Write();
  NF_W2J_nsv->Write();
  NF_W1J_nsv->Write();
  //NF_WW_nsv->Write();
  //NF_WZ_nsv->Write();
  //NF_TTZ_nsv->Write();
  NF_LW200_nsv->Write();
  //NF_LW300_nsv->Write();
  //NF_LW400_nsv->Write();
  //NF_LW500_nsv->Write();
  NF_dataRunB_svd->Write();
  NF_dataRunC_svd->Write();
  NF_ZLL_svd->Write();
  NF_TT_svd->Write();
  NF_W3J_svd->Write();
  NF_W2J_svd->Write();
  NF_W1J_svd->Write();
  //NF_WW_svd->Write();
  //NF_WZ_svd->Write();
  //NF_TTZ_svd->Write();
  NF_LW200_svd->Write();
  //NF_LW300_svd->Write();
  //NF_LW400_svd->Write();
  //NF_LW500_svd->Write();
  NF_dataRunB_Elept->Write();
  NF_dataRunC_Elept->Write();
  NF_ZLL_Elept->Write();
  NF_TT_Elept->Write();
  NF_W3J_Elept->Write();
  NF_W2J_Elept->Write();
  NF_W1J_Elept->Write();
  //NF_WW_Elept->Write();
  //NF_WZ_Elept->Write();
  //NF_TTZ_Elept->Write();
  NF_LW200_Elept->Write();
  //NF_LW300_Elept->Write();
  //NF_LW400_Elept->Write();
  //NF_LW500_Elept->Write();
  NF_dataRunB_DieledR->Write();
  NF_dataRunC_DieledR->Write();
  NF_ZLL_DieledR->Write();
  NF_TT_DieledR->Write();
  NF_W3J_DieledR->Write();
  NF_W2J_DieledR->Write();
  NF_W1J_DieledR->Write();
  //NF_WW_DieledR->Write();
  //NF_WZ_DieledR->Write();
  //NF_TTZ_DieledR->Write();
  NF_LW200_DieledR->Write();
  //NF_LW300_DieledR->Write();
  //NF_LW400_DieledR->Write();
  //NF_LW500_DieledR->Write();
  NF_dataRunB_LWdR->Write();
  NF_dataRunC_LWdR->Write();
  NF_ZLL_LWdR->Write();
  NF_TT_LWdR->Write();
  NF_W3J_LWdR->Write();
  NF_W2J_LWdR->Write();
  NF_W1J_LWdR->Write();
  //NF_WW_LWdR->Write();
  //NF_WZ_LWdR->Write();
  //NF_TTZ_LWdR->Write();
  NF_LW200_LWdR->Write();
  //NF_LW300_LWdR->Write();
  //NF_LW400_LWdR->Write();
  //NF_LW500_LWdR->Write();
  NF_dataRunB_DiJetdR->Write();
  NF_dataRunC_DiJetdR->Write();
  NF_ZLL_DiJetdR->Write();
  NF_TT_DiJetdR->Write();
  NF_W3J_DiJetdR->Write();
  NF_W2J_DiJetdR->Write();
  NF_W1J_DiJetdR->Write();
  //NF_WW_DiJetdR->Write();
  //NF_WZ_DiJetdR->Write();
  //NF_TTZ_DiJetdR->Write();
  NF_LW200_DiJetdR->Write();
  //NF_LW300_DiJetdR->Write();
  //NF_LW400_DiJetdR->Write();
  //NF_LW500_DiJetdR->Write();
  NF_dataRunB_BJetPt->Write();
  NF_dataRunC_BJetPt->Write();
  NF_ZLL_BJetPt->Write();
  NF_TT_BJetPt->Write();
  NF_W3J_BJetPt->Write();
  NF_W2J_BJetPt->Write();
  NF_W1J_BJetPt->Write();
  //NF_WW_BJetPt->Write();
  //NF_WZ_BJetPt->Write();
  //NF_TTZ_BJetPt->Write();
  NF_LW200_BJetPt->Write();
  //NF_LW300_BJetPt->Write();
  //NF_LW400_BJetPt->Write();
  //NF_LW500_BJetPt->Write();
  NF_dataRunB_SBJetPt->Write();
  NF_dataRunC_SBJetPt->Write();
  NF_ZLL_SBJetPt->Write();
  NF_TT_SBJetPt->Write();
  NF_W3J_SBJetPt->Write();
  NF_W2J_SBJetPt->Write();
  NF_W1J_SBJetPt->Write();
  //NF_WW_SBJetPt->Write();
  //NF_WZ_SBJetPt->Write();
  //NF_TTZ_SBJetPt->Write();
  NF_LW200_SBJetPt->Write();
  //NF_LW300_SBJetPt->Write();
  //NF_LW400_SBJetPt->Write();
  //NF_LW500_SBJetPt->Write();
  NF_dataRunB_NJet->Write();
  NF_dataRunC_NJet->Write();
  NF_ZLL_NJet->Write();
  NF_TT_NJet->Write();
  NF_W3J_NJet->Write();
  NF_W2J_NJet->Write();
  NF_W1J_NJet->Write();
  //NF_WW_NJet->Write();
  //NF_WZ_NJet->Write();
  //NF_TTZ_NJet->Write();
  NF_LW200_NJet->Write();
  //NF_LW300_NJet->Write();
  //NF_LW400_NJet->Write();
  //NF_LW500_NJet->Write();
  NF_dataRunB_NEle->Write();
  NF_dataRunC_NEle->Write();
  NF_ZLL_NEle->Write();
  NF_TT_NEle->Write();
  NF_W3J_NEle->Write();
  NF_W2J_NEle->Write();
  NF_W1J_NEle->Write();
  //NF_WW_NEle->Write();
  //NF_WZ_NEle->Write();
  //NF_TTZ_NEle->Write();
  NF_LW200_NEle->Write();
  //NF_LW300_NEle->Write();
  //NF_LW400_NEle->Write();
  //NF_LW500_NEle->Write();

  TF_dataRunB_npv->Write();
  TF_dataRunC_npv->Write();
  TF_ZLL_npv->Write();
  TF_TT_npv->Write();
  TF_W3J_npv->Write();
  TF_W2J_npv->Write();
  TF_W1J_npv->Write();
  //TF_WW_npv->Write();
  //TF_WZ_npv->Write();
  //TF_TTZ_npv->Write();
  TF_LW200_npv->Write();
  //TF_LW300_npv->Write();
  //TF_LW400_npv->Write();
  //TF_LW500_npv->Write();
  TF_dataRunB_JetMass->Write();
  TF_dataRunC_JetMass->Write();
  TF_ZLL_JetMass->Write();
  TF_TT_JetMass->Write();
  TF_W3J_JetMass->Write();
  TF_W2J_JetMass->Write();
  TF_W1J_JetMass->Write();
  //TF_WW_JetMass->Write();
  //TF_WZ_JetMass->Write();
  //TF_TTZ_JetMass->Write();
  TF_LW200_JetMass->Write();
  //TF_LW300_JetMass->Write();
  //TF_LW400_JetMass->Write();
  //TF_LW500_JetMass->Write();
  TF_dataRunB_LWMass->Write();
  TF_dataRunC_LWMass->Write();
  TF_ZLL_LWMass->Write();
  TF_TT_LWMass->Write();
  TF_W3J_LWMass->Write();
  TF_W2J_LWMass->Write();
  TF_W1J_LWMass->Write();
  //TF_WW_LWMass->Write();
  //TF_WZ_LWMass->Write();
  //TF_TTZ_LWMass->Write();
  TF_LW200_LWMass->Write();
  //TF_LW300_LWMass->Write();
  //TF_LW400_LWMass->Write();
  //TF_LW500_LWMass->Write();
  TF_dataRunB_nsv->Write();
  TF_dataRunC_nsv->Write();
  TF_ZLL_nsv->Write();
  TF_TT_nsv->Write();
  TF_W3J_nsv->Write();
  TF_W2J_nsv->Write();
  TF_W1J_nsv->Write();
  //TF_WW_nsv->Write();
  //TF_WZ_nsv->Write();
  //TF_TTZ_nsv->Write();
  TF_LW200_nsv->Write();
  //TF_LW300_nsv->Write();
  //TF_LW400_nsv->Write();
  //TF_LW500_nsv->Write();
  TF_dataRunB_svd->Write();
  TF_dataRunC_svd->Write();
  TF_ZLL_svd->Write();
  TF_TT_svd->Write();
  TF_W3J_svd->Write();
  TF_W2J_svd->Write();
  TF_W1J_svd->Write();
  //TF_WW_svd->Write();
  //TF_WZ_svd->Write();
  //TF_TTZ_svd->Write();
  TF_LW200_svd->Write();
  //TF_LW300_svd->Write();
  //TF_LW400_svd->Write();
  //TF_LW500_svd->Write();
  TF_dataRunB_Elept->Write();
  TF_dataRunC_Elept->Write();
  TF_ZLL_Elept->Write();
  TF_TT_Elept->Write();
  TF_W3J_Elept->Write();
  TF_W2J_Elept->Write();
  TF_W1J_Elept->Write();
  //TF_WW_Elept->Write();
  //TF_WZ_Elept->Write();
  //TF_TTZ_Elept->Write();
  TF_LW200_Elept->Write();
  //TF_LW300_Elept->Write();
  //TF_LW400_Elept->Write();
  //TF_LW500_Elept->Write();
  TF_dataRunB_DieledR->Write();
  TF_dataRunC_DieledR->Write();
  TF_ZLL_DieledR->Write();
  TF_TT_DieledR->Write();
  TF_W3J_DieledR->Write();
  TF_W2J_DieledR->Write();
  TF_W1J_DieledR->Write();
  //TF_WW_DieledR->Write();
  //TF_WZ_DieledR->Write();
  //TF_TTZ_DieledR->Write();
  TF_LW200_DieledR->Write();
  //TF_LW300_DieledR->Write();
  //TF_LW400_DieledR->Write();
  //TF_LW500_DieledR->Write();
  TF_dataRunB_LWdR->Write();
  TF_dataRunC_LWdR->Write();
  TF_ZLL_LWdR->Write();
  TF_TT_LWdR->Write();
  TF_W3J_LWdR->Write();
  TF_W2J_LWdR->Write();
  TF_W1J_LWdR->Write();
  //TF_WW_LWdR->Write();
  //TF_WZ_LWdR->Write();
  //TF_TTZ_LWdR->Write();
  TF_LW200_LWdR->Write();
  //TF_LW300_LWdR->Write();
  //TF_LW400_LWdR->Write();
  //TF_LW500_LWdR->Write();
  TF_dataRunB_DiJetdR->Write();
  TF_dataRunC_DiJetdR->Write();
  TF_ZLL_DiJetdR->Write();
  TF_TT_DiJetdR->Write();
  TF_W3J_DiJetdR->Write();
  TF_W2J_DiJetdR->Write();
  TF_W1J_DiJetdR->Write();
  //TF_WW_DiJetdR->Write();
  //TF_WZ_DiJetdR->Write();
  //TF_TTZ_DiJetdR->Write();
  TF_LW200_DiJetdR->Write();
  //TF_LW300_DiJetdR->Write();
  //TF_LW400_DiJetdR->Write();
  //TF_LW500_DiJetdR->Write();
  TF_dataRunB_BJetPt->Write();
  TF_dataRunC_BJetPt->Write();
  TF_ZLL_BJetPt->Write();
  TF_TT_BJetPt->Write();
  TF_W3J_BJetPt->Write();
  TF_W2J_BJetPt->Write();
  TF_W1J_BJetPt->Write();
  //TF_WW_BJetPt->Write();
  //TF_WZ_BJetPt->Write();
  //TF_TTZ_BJetPt->Write();
  TF_LW200_BJetPt->Write();
  //TF_LW300_BJetPt->Write();
  //TF_LW400_BJetPt->Write();
  //TF_LW500_BJetPt->Write();
  TF_dataRunB_SBJetPt->Write();
  TF_dataRunC_SBJetPt->Write();
  TF_ZLL_SBJetPt->Write();
  TF_TT_SBJetPt->Write();
  TF_W3J_SBJetPt->Write();
  TF_W2J_SBJetPt->Write();
  TF_W1J_SBJetPt->Write();
  //TF_WW_SBJetPt->Write();
  //TF_WZ_SBJetPt->Write();
  //TF_TTZ_SBJetPt->Write();
  TF_LW200_SBJetPt->Write();
  //TF_LW300_SBJetPt->Write();
  //TF_LW400_SBJetPt->Write();
  //TF_LW500_SBJetPt->Write();
  TF_dataRunB_NJet->Write();
  TF_dataRunC_NJet->Write();
  TF_ZLL_NJet->Write();
  TF_TT_NJet->Write();
  TF_W3J_NJet->Write();
  TF_W2J_NJet->Write();
  TF_W1J_NJet->Write();
  //TF_WW_NJet->Write();
  //TF_WZ_NJet->Write();
  //TF_TTZ_NJet->Write();
  TF_LW200_NJet->Write();
  //TF_LW300_NJet->Write();
  //TF_LW400_NJet->Write();
  //TF_LW500_NJet->Write();
  TF_dataRunB_NEle->Write();
  TF_dataRunC_NEle->Write();
  TF_ZLL_NEle->Write();
  TF_TT_NEle->Write();
  TF_W3J_NEle->Write();
  TF_W2J_NEle->Write();
  TF_W1J_NEle->Write();
  //TF_WW_NEle->Write();
  //TF_WZ_NEle->Write();
  //TF_TTZ_NEle->Write();
  TF_LW200_NEle->Write();
  //TF_LW300_NEle->Write();
  //TF_LW400_NEle->Write();
  //TF_LW500_NEle->Write();

  TO_dataRunB_npv->Write();
  TO_dataRunC_npv->Write();
  TO_ZLL_npv->Write();
  TO_TT_npv->Write();
  TO_W3J_npv->Write();
  TO_W2J_npv->Write();
  TO_W1J_npv->Write();
  //TO_WW_npv->Write();
  ////TO_WZ_npv->Write();
  //TO_TTZ_npv->Write();
  TO_LW200_npv->Write();
  //TO_LW300_npv->Write();
  //TO_LW400_npv->Write();
  //TO_LW500_npv->Write();
  TO_dataRunB_JetMass->Write();
  TO_dataRunC_JetMass->Write();
  TO_ZLL_JetMass->Write();
  TO_TT_JetMass->Write();
  TO_W3J_JetMass->Write();
  TO_W2J_JetMass->Write();
  TO_W1J_JetMass->Write();
  //TO_WW_JetMass->Write();
  ////TO_WZ_JetMass->Write();
  //TO_TTZ_JetMass->Write();
  TO_LW200_JetMass->Write();
  //TO_LW300_JetMass->Write();
  //TO_LW400_JetMass->Write();
  //TO_LW500_JetMass->Write();
  TO_dataRunB_LWMass->Write();
  TO_dataRunC_LWMass->Write();
  TO_ZLL_LWMass->Write();
  TO_TT_LWMass->Write();
  TO_W3J_LWMass->Write();
  TO_W2J_LWMass->Write();
  TO_W1J_LWMass->Write();
  //TO_WW_LWMass->Write();
  ////TO_WZ_LWMass->Write();
  //TO_TTZ_LWMass->Write();
  TO_LW200_LWMass->Write();
  //TO_LW300_LWMass->Write();
  //TO_LW400_LWMass->Write();
  //TO_LW500_LWMass->Write();
  TO_dataRunB_nsv->Write();
  TO_dataRunC_nsv->Write();
  TO_ZLL_nsv->Write();
  TO_TT_nsv->Write();
  TO_W3J_nsv->Write();
  TO_W2J_nsv->Write();
  TO_W1J_nsv->Write();
  //TO_WW_nsv->Write();
  ////TO_WZ_nsv->Write();
  //TO_TTZ_nsv->Write();
  TO_LW200_nsv->Write();
  //TO_LW300_nsv->Write();
  //TO_LW400_nsv->Write();
  //TO_LW500_nsv->Write();
  TO_dataRunB_svd->Write();
  TO_dataRunC_svd->Write();
  TO_ZLL_svd->Write();
  TO_TT_svd->Write();
  TO_W3J_svd->Write();
  TO_W2J_svd->Write();
  TO_W1J_svd->Write();
  //TO_WW_svd->Write();
  ////TO_WZ_svd->Write();
  //TO_TTZ_svd->Write();
  TO_LW200_svd->Write();
  //TO_LW300_svd->Write();
  //TO_LW400_svd->Write();
  //TO_LW500_svd->Write();
  TO_dataRunB_Elept->Write();
  TO_dataRunC_Elept->Write();
  TO_ZLL_Elept->Write();
  TO_TT_Elept->Write();
  TO_W3J_Elept->Write();
  TO_W2J_Elept->Write();
  TO_W1J_Elept->Write();
  //TO_WW_Elept->Write();
  ////TO_WZ_Elept->Write();
  //TO_TTZ_Elept->Write();
  TO_LW200_Elept->Write();
  //TO_LW300_Elept->Write();
  //TO_LW400_Elept->Write();
  //TO_LW500_Elept->Write();
  TO_dataRunB_DieledR->Write();
  TO_dataRunC_DieledR->Write();
  TO_ZLL_DieledR->Write();
  TO_TT_DieledR->Write();
  TO_W3J_DieledR->Write();
  TO_W2J_DieledR->Write();
  TO_W1J_DieledR->Write();
  //TO_WW_DieledR->Write();
  ////TO_WZ_DieledR->Write();
  //TO_TTZ_DieledR->Write();
  TO_LW200_DieledR->Write();
  //TO_LW300_DieledR->Write();
  //TO_LW400_DieledR->Write();
  //TO_LW500_DieledR->Write();
  TO_dataRunB_LWdR->Write();
  TO_dataRunC_LWdR->Write();
  TO_ZLL_LWdR->Write();
  TO_TT_LWdR->Write();
  TO_W3J_LWdR->Write();
  TO_W2J_LWdR->Write();
  TO_W1J_LWdR->Write();
  //TO_WW_LWdR->Write();
  ////TO_WZ_LWdR->Write();
  //TO_TTZ_LWdR->Write();
  TO_LW200_LWdR->Write();
  //TO_LW300_LWdR->Write();
  //TO_LW400_LWdR->Write();
  //TO_LW500_LWdR->Write();
  TO_dataRunB_DiJetdR->Write();
  TO_dataRunC_DiJetdR->Write();
  TO_ZLL_DiJetdR->Write();
  TO_TT_DiJetdR->Write();
  TO_W3J_DiJetdR->Write();
  TO_W2J_DiJetdR->Write();
  TO_W1J_DiJetdR->Write();
  //TO_WW_DiJetdR->Write();
  ////TO_WZ_DiJetdR->Write();
  //TO_TTZ_DiJetdR->Write();
  TO_LW200_DiJetdR->Write();
  //TO_LW300_DiJetdR->Write();
  //TO_LW400_DiJetdR->Write();
  //TO_LW500_DiJetdR->Write();
  TO_dataRunB_BJetPt->Write();
  TO_dataRunC_BJetPt->Write();
  TO_ZLL_BJetPt->Write();
  TO_TT_BJetPt->Write();
  TO_W3J_BJetPt->Write();
  TO_W2J_BJetPt->Write();
  TO_W1J_BJetPt->Write();
  //TO_WW_BJetPt->Write();
  ////TO_WZ_BJetPt->Write();
  //TO_TTZ_BJetPt->Write();
  TO_LW200_BJetPt->Write();
  //TO_LW300_BJetPt->Write();
  //TO_LW400_BJetPt->Write();
  //TO_LW500_BJetPt->Write();
  TO_dataRunB_SBJetPt->Write();
  TO_dataRunC_SBJetPt->Write();
  TO_ZLL_SBJetPt->Write();
  TO_TT_SBJetPt->Write();
  TO_W3J_SBJetPt->Write();
  TO_W2J_SBJetPt->Write();
  TO_W1J_SBJetPt->Write();
  //TO_WW_SBJetPt->Write();
  ////TO_WZ_SBJetPt->Write();
  //TO_TTZ_SBJetPt->Write();
  TO_LW200_SBJetPt->Write();
  //TO_LW300_SBJetPt->Write();
  //TO_LW400_SBJetPt->Write();
  //TO_LW500_SBJetPt->Write();
  TO_dataRunB_NJet->Write();
  TO_dataRunC_NJet->Write();
  TO_ZLL_NJet->Write();
  TO_TT_NJet->Write();
  TO_W3J_NJet->Write();
  TO_W2J_NJet->Write();
  TO_W1J_NJet->Write();
  //TO_WW_NJet->Write();
  ////TO_WZ_NJet->Write();
  //TO_TTZ_NJet->Write();
  TO_LW200_NJet->Write();
  //TO_LW300_NJet->Write();
  //TO_LW400_NJet->Write();
  //TO_LW500_NJet->Write();
  TO_dataRunB_NEle->Write();
  TO_dataRunC_NEle->Write();
  TO_ZLL_NEle->Write();
  TO_TT_NEle->Write();
  TO_W3J_NEle->Write();
  TO_W2J_NEle->Write();
  TO_W1J_NEle->Write();
  //TO_WW_NEle->Write();
  ////TO_WZ_NEle->Write();
  //TO_TTZ_NEle->Write();
  TO_LW200_NEle->Write();
  //TO_LW300_NEle->Write();
  //TO_LW400_NEle->Write();
  //TO_LW500_NEle->Write();

  HQ_dataRunB_npv->Write();
  HQ_dataRunC_npv->Write();
  HQ_ZLL_npv->Write();
  HQ_TT_npv->Write();
  HQ_W3J_npv->Write();
  HQ_W2J_npv->Write();
  HQ_W1J_npv->Write();
  //HQ_WW_npv->Write();
  //HQ_WZ_npv->Write();
  ////HQ_TTZ_npv->Write();
  HQ_LW200_npv->Write();
  //HQ_LW300_npv->Write();
  //HQ_LW400_npv->Write();
  //HQ_LW500_npv->Write();
  HQ_dataRunB_JetMass->Write();
  HQ_dataRunC_JetMass->Write();
  HQ_ZLL_JetMass->Write();
  HQ_TT_JetMass->Write();
  HQ_W3J_JetMass->Write();
  HQ_W2J_JetMass->Write();
  HQ_W1J_JetMass->Write();
  //HQ_WW_JetMass->Write();
  //HQ_WZ_JetMass->Write();
  ////HQ_TTZ_JetMass->Write();
  HQ_LW200_JetMass->Write();
  //HQ_LW300_JetMass->Write();
  //HQ_LW400_JetMass->Write();
  //HQ_LW500_JetMass->Write();
  HQ_dataRunB_LWMass->Write();
  HQ_dataRunC_LWMass->Write();
  HQ_ZLL_LWMass->Write();
  HQ_TT_LWMass->Write();
  HQ_W3J_LWMass->Write();
  HQ_W2J_LWMass->Write();
  HQ_W1J_LWMass->Write();
  //HQ_WW_LWMass->Write();
  //HQ_WZ_LWMass->Write();
  ////HQ_TTZ_LWMass->Write();
  HQ_LW200_LWMass->Write();
  //HQ_LW300_LWMass->Write();
  //HQ_LW400_LWMass->Write();
  //HQ_LW500_LWMass->Write();
  HQ_dataRunB_nsv->Write();
  HQ_dataRunC_nsv->Write();
  HQ_ZLL_nsv->Write();
  HQ_TT_nsv->Write();
  HQ_W3J_nsv->Write();
  HQ_W2J_nsv->Write();
  HQ_W1J_nsv->Write();
  //HQ_WW_nsv->Write();
  //HQ_WZ_nsv->Write();
  ////HQ_TTZ_nsv->Write();
  HQ_LW200_nsv->Write();
  //HQ_LW300_nsv->Write();
  //HQ_LW400_nsv->Write();
  //HQ_LW500_nsv->Write();
  HQ_dataRunB_svd->Write();
  HQ_dataRunC_svd->Write();
  HQ_ZLL_svd->Write();
  HQ_TT_svd->Write();
  HQ_W3J_svd->Write();
  HQ_W2J_svd->Write();
  HQ_W1J_svd->Write();
  //HQ_WW_svd->Write();
  //HQ_WZ_svd->Write();
  ////HQ_TTZ_svd->Write();
  HQ_LW200_svd->Write();
  //HQ_LW300_svd->Write();
  //HQ_LW400_svd->Write();
  //HQ_LW500_svd->Write();
  HQ_dataRunB_Elept->Write();
  HQ_dataRunC_Elept->Write();
  HQ_ZLL_Elept->Write();
  HQ_TT_Elept->Write();
  HQ_W3J_Elept->Write();
  HQ_W2J_Elept->Write();
  HQ_W1J_Elept->Write();
  //HQ_WW_Elept->Write();
  //HQ_WZ_Elept->Write();
  ////HQ_TTZ_Elept->Write();
  HQ_LW200_Elept->Write();
  //HQ_LW300_Elept->Write();
  //HQ_LW400_Elept->Write();
  //HQ_LW500_Elept->Write();
  HQ_dataRunB_DieledR->Write();
  HQ_dataRunC_DieledR->Write();
  HQ_ZLL_DieledR->Write();
  HQ_TT_DieledR->Write();
  HQ_W3J_DieledR->Write();
  HQ_W2J_DieledR->Write();
  HQ_W1J_DieledR->Write();
  //HQ_WW_DieledR->Write();
  //HQ_WZ_DieledR->Write();
  ////HQ_TTZ_DieledR->Write();
  HQ_LW200_DieledR->Write();
  //HQ_LW300_DieledR->Write();
  //HQ_LW400_DieledR->Write();
  //HQ_LW500_DieledR->Write();
  HQ_dataRunB_LWdR->Write();
  HQ_dataRunC_LWdR->Write();
  HQ_ZLL_LWdR->Write();
  HQ_TT_LWdR->Write();
  HQ_W3J_LWdR->Write();
  HQ_W2J_LWdR->Write();
  HQ_W1J_LWdR->Write();
  //HQ_WW_LWdR->Write();
  //HQ_WZ_LWdR->Write();
  ////HQ_TTZ_LWdR->Write();
  HQ_LW200_LWdR->Write();
  //HQ_LW300_LWdR->Write();
  //HQ_LW400_LWdR->Write();
  //HQ_LW500_LWdR->Write();
  HQ_dataRunB_DiJetdR->Write();
  HQ_dataRunC_DiJetdR->Write();
  HQ_ZLL_DiJetdR->Write();
  HQ_TT_DiJetdR->Write();
  HQ_W3J_DiJetdR->Write();
  HQ_W2J_DiJetdR->Write();
  HQ_W1J_DiJetdR->Write();
  //HQ_WW_DiJetdR->Write();
  //HQ_WZ_DiJetdR->Write();
  ////HQ_TTZ_DiJetdR->Write();
  HQ_LW200_DiJetdR->Write();
  //HQ_LW300_DiJetdR->Write();
  //HQ_LW400_DiJetdR->Write();
  //HQ_LW500_DiJetdR->Write();
  HQ_dataRunB_BJetPt->Write();
  HQ_dataRunC_BJetPt->Write();
  HQ_ZLL_BJetPt->Write();
  HQ_TT_BJetPt->Write();
  HQ_W3J_BJetPt->Write();
  HQ_W2J_BJetPt->Write();
  HQ_W1J_BJetPt->Write();
  //HQ_WW_BJetPt->Write();
  //HQ_WZ_BJetPt->Write();
  ////HQ_TTZ_BJetPt->Write();
  HQ_LW200_BJetPt->Write();
  //HQ_LW300_BJetPt->Write();
  //HQ_LW400_BJetPt->Write();
  //HQ_LW500_BJetPt->Write();
  HQ_dataRunB_SBJetPt->Write();
  HQ_dataRunC_SBJetPt->Write();
  HQ_ZLL_SBJetPt->Write();
  HQ_TT_SBJetPt->Write();
  HQ_W3J_SBJetPt->Write();
  HQ_W2J_SBJetPt->Write();
  HQ_W1J_SBJetPt->Write();
  //HQ_WW_SBJetPt->Write();
  //HQ_WZ_SBJetPt->Write();
  ////HQ_TTZ_SBJetPt->Write();
  HQ_LW200_SBJetPt->Write();
  //HQ_LW300_SBJetPt->Write();
  //HQ_LW400_SBJetPt->Write();
  //HQ_LW500_SBJetPt->Write();
  HQ_dataRunB_NJet->Write();
  HQ_dataRunC_NJet->Write();
  HQ_ZLL_NJet->Write();
  HQ_TT_NJet->Write();
  HQ_W3J_NJet->Write();
  HQ_W2J_NJet->Write();
  HQ_W1J_NJet->Write();
  //HQ_WW_NJet->Write();
  //HQ_WZ_NJet->Write();
  ////HQ_TTZ_NJet->Write();
  HQ_LW200_NJet->Write();
  //HQ_LW300_NJet->Write();
  //HQ_LW400_NJet->Write();
  //HQ_LW500_NJet->Write();
  HQ_dataRunB_NEle->Write();
  HQ_dataRunC_NEle->Write();
  HQ_ZLL_NEle->Write();
  HQ_TT_NEle->Write();
  HQ_W3J_NEle->Write();
  HQ_W2J_NEle->Write();
  HQ_W1J_NEle->Write();
  //HQ_WW_NEle->Write();
  //HQ_WZ_NEle->Write();
  ////HQ_TTZ_NEle->Write();
  HQ_LW200_NEle->Write();
  //HQ_LW300_NEle->Write();
  //HQ_LW400_NEle->Write();
  //HQ_LW500_NEle->Write();

  SG_dataRunB_npv->Write();
  SG_dataRunC_npv->Write();
  SG_ZLL_npv->Write();
  SG_TT_npv->Write();
  SG_W3J_npv->Write();
  SG_W2J_npv->Write();
  SG_W1J_npv->Write();
  //SG_WW_npv->Write();
  //SG_WZ_npv->Write();
  //SG_TTZ_npv->Write();
  SG_LW200_npv->Write();
  //SG_LW300_npv->Write();
  //SG_LW400_npv->Write();
  //SG_LW500_npv->Write();
  SG_dataRunB_JetMass->Write();
  SG_dataRunC_JetMass->Write();
  SG_ZLL_JetMass->Write();
  SG_TT_JetMass->Write();
  SG_W3J_JetMass->Write();
  SG_W2J_JetMass->Write();
  SG_W1J_JetMass->Write();
  //SG_WW_JetMass->Write();
  //SG_WZ_JetMass->Write();
  //SG_TTZ_JetMass->Write();
  SG_LW200_JetMass->Write();
  //SG_LW300_JetMass->Write();
  //SG_LW400_JetMass->Write();
  //SG_LW500_JetMass->Write();
  SG_dataRunB_LWMass->Write();
  SG_dataRunC_LWMass->Write();
  SG_ZLL_LWMass->Write();
  SG_TT_LWMass->Write();
  SG_W3J_LWMass->Write();
  SG_W2J_LWMass->Write();
  SG_W1J_LWMass->Write();
  //SG_WW_LWMass->Write();
  //SG_WZ_LWMass->Write();
  //SG_TTZ_LWMass->Write();
  SG_LW200_LWMass->Write();
  //SG_LW300_LWMass->Write();
  //SG_LW400_LWMass->Write();
  //SG_LW500_LWMass->Write();
  SG_dataRunB_nsv->Write();
  SG_dataRunC_nsv->Write();
  SG_ZLL_nsv->Write();
  SG_TT_nsv->Write();
  SG_W3J_nsv->Write();
  SG_W2J_nsv->Write();
  SG_W1J_nsv->Write();
  //SG_WW_nsv->Write();
  //SG_WZ_nsv->Write();
  //SG_TTZ_nsv->Write();
  SG_LW200_nsv->Write();
  //SG_LW300_nsv->Write();
  //SG_LW400_nsv->Write();
  //SG_LW500_nsv->Write();
  SG_dataRunB_svd->Write();
  SG_dataRunC_svd->Write();
  SG_ZLL_svd->Write();
  SG_TT_svd->Write();
  SG_W3J_svd->Write();
  SG_W2J_svd->Write();
  SG_W1J_svd->Write();
  //SG_WW_svd->Write();
  //SG_WZ_svd->Write();
  //SG_TTZ_svd->Write();
  SG_LW200_svd->Write();
  //SG_LW300_svd->Write();
  //SG_LW400_svd->Write();
  //SG_LW500_svd->Write();
  SG_dataRunB_Elept->Write();
  SG_dataRunC_Elept->Write();
  SG_ZLL_Elept->Write();
  SG_TT_Elept->Write();
  SG_W3J_Elept->Write();
  SG_W2J_Elept->Write();
  SG_W1J_Elept->Write();
  //SG_WW_Elept->Write();
  //SG_WZ_Elept->Write();
  //SG_TTZ_Elept->Write();
  SG_LW200_Elept->Write();
  //SG_LW300_Elept->Write();
  //SG_LW400_Elept->Write();
  //SG_LW500_Elept->Write();
  SG_dataRunB_DieledR->Write();
  SG_dataRunC_DieledR->Write();
  SG_ZLL_DieledR->Write();
  SG_TT_DieledR->Write();
  SG_W3J_DieledR->Write();
  SG_W2J_DieledR->Write();
  SG_W1J_DieledR->Write();
  //SG_WW_DieledR->Write();
  //SG_WZ_DieledR->Write();
  //SG_TTZ_DieledR->Write();
  SG_LW200_DieledR->Write();
  //SG_LW300_DieledR->Write();
  //SG_LW400_DieledR->Write();
  //SG_LW500_DieledR->Write();
  SG_dataRunB_LWdR->Write();
  SG_dataRunC_LWdR->Write();
  SG_ZLL_LWdR->Write();
  SG_TT_LWdR->Write();
  SG_W3J_LWdR->Write();
  SG_W2J_LWdR->Write();
  SG_W1J_LWdR->Write();
  //SG_WW_LWdR->Write();
  //SG_WZ_LWdR->Write();
  //SG_TTZ_LWdR->Write();
  SG_LW200_LWdR->Write();
  //SG_LW300_LWdR->Write();
  //SG_LW400_LWdR->Write();
  //SG_LW500_LWdR->Write();
  SG_dataRunB_DiJetdR->Write();
  SG_dataRunC_DiJetdR->Write();
  SG_ZLL_DiJetdR->Write();
  SG_TT_DiJetdR->Write();
  SG_W3J_DiJetdR->Write();
  SG_W2J_DiJetdR->Write();
  SG_W1J_DiJetdR->Write();
  //SG_WW_DiJetdR->Write();
  //SG_WZ_DiJetdR->Write();
  //SG_TTZ_DiJetdR->Write();
  SG_LW200_DiJetdR->Write();
  //SG_LW300_DiJetdR->Write();
  //SG_LW400_DiJetdR->Write();
  //SG_LW500_DiJetdR->Write();
  SG_dataRunB_BJetPt->Write();
  SG_dataRunC_BJetPt->Write();
  SG_ZLL_BJetPt->Write();
  SG_TT_BJetPt->Write();
  SG_W3J_BJetPt->Write();
  SG_W2J_BJetPt->Write();
  SG_W1J_BJetPt->Write();
  //SG_WW_BJetPt->Write();
  //SG_WZ_BJetPt->Write();
  //SG_TTZ_BJetPt->Write();
  SG_LW200_BJetPt->Write();
  //SG_LW300_BJetPt->Write();
  //SG_LW400_BJetPt->Write();
  //SG_LW500_BJetPt->Write();
  SG_dataRunB_SBJetPt->Write();
  SG_dataRunC_SBJetPt->Write();
  SG_ZLL_SBJetPt->Write();
  SG_TT_SBJetPt->Write();
  SG_W3J_SBJetPt->Write();
  SG_W2J_SBJetPt->Write();
  SG_W1J_SBJetPt->Write();
  //SG_WW_SBJetPt->Write();
  //SG_WZ_SBJetPt->Write();
  //SG_TTZ_SBJetPt->Write();
  SG_LW200_SBJetPt->Write();
  //SG_LW300_SBJetPt->Write();
  //SG_LW400_SBJetPt->Write();
  //SG_LW500_SBJetPt->Write();
  SG_dataRunB_NJet->Write();
  SG_dataRunC_NJet->Write();
  SG_ZLL_NJet->Write();
  SG_TT_NJet->Write();
  SG_W3J_NJet->Write();
  SG_W2J_NJet->Write();
  SG_W1J_NJet->Write();
  //SG_WW_NJet->Write();
  //SG_WZ_NJet->Write();
  //SG_TTZ_NJet->Write();
  SG_LW200_NJet->Write();
  //SG_LW300_NJet->Write();
  //SG_LW400_NJet->Write();
  //SG_LW500_NJet->Write();
  SG_dataRunB_NEle->Write();
  SG_dataRunC_NEle->Write();
  SG_ZLL_NEle->Write();
  SG_TT_NEle->Write();
  SG_W3J_NEle->Write();
  SG_W2J_NEle->Write();
  SG_W1J_NEle->Write();
  //SG_WW_NEle->Write();
  //SG_WZ_NEle->Write();
  //SG_TTZ_NEle->Write();
  SG_LW200_NEle->Write();
  //SG_LW300_NEle->Write();
  //SG_LW400_NEle->Write();
  //SG_LW500_NEle->Write();

  hfile->Close();


  return 0;

}
