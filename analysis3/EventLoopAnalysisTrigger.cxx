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

TH1F* NF_TTZ_npv = new TH1F("NF_TTZ_npv","NF Number of primary vertices",25,5,30);

TH1F* NF_WW_npv = new TH1F("NF_WW_npv","NF Number of primary vertices",25,5,30);

TH1F* NF_WZ_npv = new TH1F("NF_WZ_npv","NF Number of primary vertices",25,5,30);

TH1F* NF_LW200_npv = new TH1F("NF_LW200_npv","NF Number of primary vertices",25,5,30);

TH1F* NF_LW300_npv = new TH1F("NF_LW300_npv","NF Number of primary vertices",25,5,30);

//TH1F* NF_LW400_npv = new TH1F("NF_LW400_npv","NF Number of primary vertices",25,5,30);

//TH1F* NF_LW500_npv = new TH1F("NF_LW500_npv","NF Number of primary vertices",25,5,30);

TH1F* NF_dataRunB_nsv = new TH1F("NF_dataRunB_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_dataRunC_nsv  = new TH1F("NF_dataRunC_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_ZLL_nsv = new TH1F("NF_ZLL_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_TT_nsv = new TH1F("NF_TT_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_W3J_nsv = new TH1F("NF_W3J_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_W2J_nsv = new TH1F("NF_W2J_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_W1J_nsv = new TH1F("NF_W1J_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_TTZ_nsv = new TH1F("NF_TTZ_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_WW_nsv = new TH1F("NF_WW_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_WZ_nsv = new TH1F("NF_WZ_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_LW200_nsv = new TH1F("NF_LW200_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_LW300_nsv = new TH1F("NF_LW300_nsv","NF Number of secondary vertices",20,0,2000);

//TH1F* NF_LW400_nsv = new TH1F("NF_LW400_nsv","NF Number of secondary vertices",20,0,2000);

//TH1F* NF_LW500_nsv = new TH1F("NF_LW500_nsv","NF Number of secondary vertices",20,0,2000);

TH1F* NF_dataRunB_svd = new TH1F("NF_dataRunB_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_dataRunC_svd  = new TH1F("NF_dataRunC_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_ZLL_svd = new TH1F("NF_ZLL_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_TT_svd = new TH1F("NF_TT_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_W3J_svd = new TH1F("NF_W3J_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_W2J_svd = new TH1F("NF_W2J_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_W1J_svd = new TH1F("NF_W1J_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_TTZ_svd = new TH1F("NF_TTZ_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_WW_svd = new TH1F("NF_WW_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_WZ_svd = new TH1F("NF_WZ_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_LW200_svd = new TH1F("NF_LW200_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_LW300_svd = new TH1F("NF_LW300_svd","NF secondary vertex displacement",100,0,1);

//TH1F* NF_LW400_svd = new TH1F("NF_LW400_svd","NF secondary vertex displacement",100,0,1);

//TH1F* NF_LW500_svd = new TH1F("NF_LW500_svd","NF secondary vertex displacement",100,0,1);

TH1F* NF_dataRunB_JetMass = new TH1F("NF_dataRunB_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_dataRunC_JetMass  = new TH1F("NF_dataRunC_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_ZLL_JetMass = new TH1F("NF_ZLL_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_TT_JetMass = new TH1F("NF_TT_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_W3J_JetMass = new TH1F("NF_W3J_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_W2J_JetMass = new TH1F("NF_W2J_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_W1J_JetMass = new TH1F("NF_W1J_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_TTZ_JetMass = new TH1F("NF_TTZ_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_WW_JetMass = new TH1F("NF_WW_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_WZ_JetMass = new TH1F("NF_WZ_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_LW200_JetMass = new TH1F("NF_LW200_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_LW300_JetMass = new TH1F("NF_LW300_JetMass","NF Invariant mass from DiJets",100,0,400);

//TH1F* NF_LW400_JetMass = new TH1F("NF_LW400_JetMass","NF Invariant mass from DiJets",100,0,400);

//TH1F* NF_LW500_JetMass = new TH1F("NF_LW500_JetMass","NF Invariant mass from DiJets",100,0,400);

TH1F* NF_dataRunB_LWMass = new TH1F("NF_dataRunB_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_dataRunC_LWMass  = new TH1F("NF_dataRunC_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_ZLL_LWMass = new TH1F("NF_ZLL_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_TT_LWMass = new TH1F("NF_TT_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_W3J_LWMass = new TH1F("NF_W3J_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_W2J_LWMass = new TH1F("NF_W2J_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_W1J_LWMass = new TH1F("NF_W1J_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_TTZ_LWMass = new TH1F("NF_TTZ_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_WW_LWMass = new TH1F("NF_WW_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_WZ_LWMass = new TH1F("NF_WZ_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_LW200_LWMass = new TH1F("NF_LW200_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_LW300_LWMass = new TH1F("NF_LW300_LWMass","NF Invariant mass from LW",100,0,400);

//TH1F* NF_LW400_LWMass = new TH1F("NF_LW400_LWMass","NF Invariant mass from LW",100,0,400);

//TH1F* NF_LW500_LWMass = new TH1F("NF_LW500_LWMass","NF Invariant mass from LW",100,0,400);

TH1F* NF_dataRunB_Elept = new TH1F("NF_dataRunB_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_dataRunC_Elept  = new TH1F("NF_dataRunC_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_ZLL_Elept = new TH1F("NF_ZLL_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_TT_Elept = new TH1F("NF_TT_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_W3J_Elept = new TH1F("NF_W3J_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_W2J_Elept = new TH1F("NF_W2J_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_W1J_Elept = new TH1F("NF_W1J_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_TTZ_Elept = new TH1F("NF_TTZ_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_WW_Elept = new TH1F("NF_WW_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_WZ_Elept = new TH1F("NF_WZ_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_LW200_Elept = new TH1F("NF_LW200_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_LW300_Elept = new TH1F("NF_LW300_Elept","NF Electron pt distribution",100,0,200);

//TH1F* NF_LW400_Elept = new TH1F("NF_LW400_Elept","NF Electron pt distribution",100,0,200);

//TH1F* NF_LW500_Elept = new TH1F("NF_LW500_Elept","NF Electron pt distribution",100,0,200);

TH1F* NF_dataRunB_DieledR = new TH1F("NF_dataRunB_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_dataRunC_DieledR  = new TH1F("NF_dataRunC_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_ZLL_DieledR = new TH1F("NF_ZLL_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_TT_DieledR = new TH1F("NF_TT_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_W3J_DieledR = new TH1F("NF_W3J_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_W2J_DieledR = new TH1F("NF_W2J_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_W1J_DieledR = new TH1F("NF_W1J_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_TTZ_DieledR = new TH1F("NF_TTZ_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_WW_DieledR = new TH1F("NF_WW_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_WZ_DieledR = new TH1F("NF_WZ_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_LW200_DieledR = new TH1F("NF_LW200_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_LW300_DieledR = new TH1F("NF_LW300_DieledR","NF delta R separation between electrons",100,0,8);

//TH1F* NF_LW400_DieledR = new TH1F("NF_LW400_DieledR","NF delta R separation between electrons",100,0,8);

//TH1F* NF_LW500_DieledR = new TH1F("NF_LW500_DieledR","NF delta R separation between electrons",100,0,8);

TH1F* NF_dataRunB_LWdR = new TH1F("NF_dataRunB_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_dataRunC_LWdR  = new TH1F("NF_dataRunC_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_ZLL_LWdR = new TH1F("NF_ZLL_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_TT_LWdR = new TH1F("NF_TT_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_W3J_LWdR = new TH1F("NF_W3J_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_W2J_LWdR = new TH1F("NF_W2J_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_W1J_LWdR = new TH1F("NF_W1J_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_TTZ_LWdR = new TH1F("NF_TTZ_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_WW_LWdR = new TH1F("NF_WW_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_WZ_LWdR = new TH1F("NF_WZ_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_LW200_LWdR = new TH1F("NF_LW200_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_LW300_LWdR = new TH1F("NF_LW300_LWdR","NF delta R separation between electrons and jets",100,0,8);

//TH1F* NF_LW400_LWdR = new TH1F("NF_LW400_LWdR","NF delta R separation between electrons and jets",100,0,8);

//TH1F* NF_LW500_LWdR = new TH1F("NF_LW500_LWdR","NF delta R separation between electrons and jets",100,0,8);

TH1F* NF_dataRunB_DiJetdR = new TH1F("NF_dataRunB_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_dataRunC_DiJetdR  = new TH1F("NF_dataRunC_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_ZLL_DiJetdR = new TH1F("NF_ZLL_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_TT_DiJetdR = new TH1F("NF_TT_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_W3J_DiJetdR = new TH1F("NF_W3J_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_W2J_DiJetdR = new TH1F("NF_W2J_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_W1J_DiJetdR = new TH1F("NF_W1J_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_TTZ_DiJetdR = new TH1F("NF_TTZ_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_WW_DiJetdR = new TH1F("NF_WW_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_WZ_DiJetdR = new TH1F("NF_WZ_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_LW200_DiJetdR = new TH1F("NF_LW200_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_LW300_DiJetdR = new TH1F("NF_LW300_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

//TH1F* NF_LW400_DiJetdR = new TH1F("NF_LW400_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

//TH1F* NF_LW500_DiJetdR = new TH1F("NF_LW500_DiJetdR","NF delta R separation between Jet Candidates",100,0,8);

TH1F* NF_dataRunB_BJetPt = new TH1F("NF_dataRunB_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_dataRunC_BJetPt  = new TH1F("NF_dataRunC_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_ZLL_BJetPt = new TH1F("NF_ZLL_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_TT_BJetPt = new TH1F("NF_TT_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_W3J_BJetPt = new TH1F("NF_W3J_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_W2J_BJetPt = new TH1F("NF_W2J_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_W1J_BJetPt = new TH1F("NF_W1J_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_TTZ_BJetPt = new TH1F("NF_TTZ_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_WW_BJetPt = new TH1F("NF_WW_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_WZ_BJetPt = new TH1F("NF_WZ_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_LW200_BJetPt = new TH1F("NF_LW200_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_LW300_BJetPt = new TH1F("NF_LW300_BJetPt","NF Most energetic Jet pt",100,0,250);

//TH1F* NF_LW400_BJetPt = new TH1F("NF_LW400_BJetPt","NF Most energetic Jet pt",100,0,250);

//TH1F* NF_LW500_BJetPt = new TH1F("NF_LW500_BJetPt","NF Most energetic Jet pt",100,0,250);

TH1F* NF_dataRunB_SBJetPt = new TH1F("NF_dataRunB_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_dataRunC_SBJetPt  = new TH1F("NF_dataRunC_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_ZLL_SBJetPt = new TH1F("NF_ZLL_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_TT_SBJetPt = new TH1F("NF_TT_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_W3J_SBJetPt = new TH1F("NF_W3J_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_W2J_SBJetPt = new TH1F("NF_W2J_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_W1J_SBJetPt = new TH1F("NF_W1J_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_TTZ_SBJetPt = new TH1F("NF_TTZ_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_WW_SBJetPt = new TH1F("NF_WW_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_WZ_SBJetPt = new TH1F("NF_WZ_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_LW200_SBJetPt = new TH1F("NF_LW200_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_LW300_SBJetPt = new TH1F("NF_LW300_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

//TH1F* NF_LW400_SBJetPt = new TH1F("NF_LW400_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

//TH1F* NF_LW500_SBJetPt = new TH1F("NF_LW500_SBJetPt","Second NF Most energetic Jet pt",100,0,250);

TH1F* NF_dataRunB_NJet = new TH1F("NF_dataRunB_NJet","NF Number of Jets",20,0,20);

TH1F* NF_dataRunC_NJet  = new TH1F("NF_dataRunC_NJet","NF Number of Jets",20,0,20);

TH1F* NF_ZLL_NJet = new TH1F("NF_ZLL_NJet","NF Number of Jets",20,0,20);

TH1F* NF_TT_NJet = new TH1F("NF_TT_NJet","NF Number of Jets",20,0,20);

TH1F* NF_W3J_NJet = new TH1F("NF_W3J_NJet","NF Number of Jets",20,0,20);

TH1F* NF_W2J_NJet = new TH1F("NF_W2J_NJet","NF Number of Jets",20,0,20);

TH1F* NF_W1J_NJet = new TH1F("NF_W1J_NJet","NF Number of Jets",20,0,20);

TH1F* NF_TTZ_NJet = new TH1F("NF_TTZ_NJet","NF Number of Jets",20,0,20);

TH1F* NF_WW_NJet = new TH1F("NF_WW_NJet","NF Number of Jets",20,0,20);

TH1F* NF_WZ_NJet = new TH1F("NF_WZ_NJet","NF Number of Jets",20,0,20);

TH1F* NF_LW200_NJet = new TH1F("NF_LW200_NJet","NF Number of Jets",20,0,20);

TH1F* NF_LW300_NJet = new TH1F("NF_LW300_NJet","NF Number of Jets",20,0,20);

//TH1F* NF_LW400_NJet = new TH1F("NF_LW400_NJet","NF Number of Jets",20,0,20);

//TH1F* NF_LW500_NJet = new TH1F("NF_LW500_NJet","NF Number of Jets",20,0,20);

TH1F* NF_dataRunB_NEle = new TH1F("NF_dataRunB_NEle","NF Number of electrons",20,0,20);

TH1F* NF_dataRunC_NEle  = new TH1F("NF_dataRunC_NEle","NF Number of electrons",20,0,20);

TH1F* NF_ZLL_NEle = new TH1F("NF_ZLL_NEle","NF Number of electrons",20,0,20);

TH1F* NF_TT_NEle = new TH1F("NF_TT_NEle","NF Number of electrons",20,0,20);

TH1F* NF_W3J_NEle = new TH1F("NF_W3J_NEle","NF Number of electrons",20,0,20);

TH1F* NF_W2J_NEle = new TH1F("NF_W2J_NEle","NF Number of electrons",20,0,20);

TH1F* NF_W1J_NEle = new TH1F("NF_W1J_NEle","NF Number of electrons",20,0,20);

TH1F* NF_TTZ_NEle = new TH1F("NF_TTZ_NEle","NF Number of electrons",20,0,20);

TH1F* NF_WW_NEle = new TH1F("NF_WW_NEle","NF Number of electrons",20,0,20);

TH1F* NF_WZ_NEle = new TH1F("NF_WZ_NEle","NF Number of electrons",20,0,20);

TH1F* NF_LW200_NEle = new TH1F("NF_LW200_NEle","NF Number of electrons",20,0,20);

TH1F* NF_LW300_NEle = new TH1F("NF_LW300_NEle","NF Number of electrons",20,0,20);

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

TH1F* TF_TTZ_npv = new TH1F("TF_TTZ_npv","TF Number of primary vertices",25,5,30);

TH1F* TF_WW_npv = new TH1F("TF_WW_npv","TF Number of primary vertices",25,5,30);

TH1F* TF_WZ_npv = new TH1F("TF_WZ_npv","TF Number of primary vertices",25,5,30);

TH1F* TF_LW200_npv = new TH1F("TF_LW200_npv","TF Number of primary vertices",25,5,30);

TH1F* TF_LW300_npv = new TH1F("TF_LW300_npv","TF Number of primary vertices",25,5,30);

//TH1F* TF_LW400_npv = new TH1F("TF_LW400_npv","TF Number of primary vertices",25,5,30);

//TH1F* TF_LW500_npv = new TH1F("TF_LW500_npv","TF Number of primary vertices",25,5,30);

TH1F* TF_dataRunB_nsv = new TH1F("TF_dataRunB_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_dataRunC_nsv  = new TH1F("TF_dataRunC_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_ZLL_nsv = new TH1F("TF_ZLL_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_TT_nsv = new TH1F("TF_TT_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_W3J_nsv = new TH1F("TF_W3J_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_W2J_nsv = new TH1F("TF_W2J_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_W1J_nsv = new TH1F("TF_W1J_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_TTZ_nsv = new TH1F("TF_TTZ_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_WW_nsv = new TH1F("TF_WW_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_WZ_nsv = new TH1F("TF_WZ_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_LW200_nsv = new TH1F("TF_LW200_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_LW300_nsv = new TH1F("TF_LW300_nsv","TF Number of secondary vertices",20,0,2000);

//TH1F* TF_LW400_nsv = new TH1F("TF_LW400_nsv","TF Number of secondary vertices",20,0,2000);

//TH1F* TF_LW500_nsv = new TH1F("TF_LW500_nsv","TF Number of secondary vertices",20,0,2000);

TH1F* TF_dataRunB_svd = new TH1F("TF_dataRunB_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_dataRunC_svd  = new TH1F("TF_dataRunC_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_ZLL_svd = new TH1F("TF_ZLL_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_TT_svd = new TH1F("TF_TT_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_W3J_svd = new TH1F("TF_W3J_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_W2J_svd = new TH1F("TF_W2J_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_W1J_svd = new TH1F("TF_W1J_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_TTZ_svd = new TH1F("TF_TTZ_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_WW_svd = new TH1F("TF_WW_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_WZ_svd = new TH1F("TF_WZ_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_LW200_svd = new TH1F("TF_LW200_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_LW300_svd = new TH1F("TF_LW300_svd","TF secondary vertex displacement",100,0,1);

//TH1F* TF_LW400_svd = new TH1F("TF_LW400_svd","TF secondary vertex displacement",100,0,1);

//TH1F* TF_LW500_svd = new TH1F("TF_LW500_svd","TF secondary vertex displacement",100,0,1);

TH1F* TF_dataRunB_JetMass = new TH1F("TF_dataRunB_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_dataRunC_JetMass  = new TH1F("TF_dataRunC_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_ZLL_JetMass = new TH1F("TF_ZLL_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_TT_JetMass = new TH1F("TF_TT_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_W3J_JetMass = new TH1F("TF_W3J_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_W2J_JetMass = new TH1F("TF_W2J_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_W1J_JetMass = new TH1F("TF_W1J_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_TTZ_JetMass = new TH1F("TF_TTZ_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_WW_JetMass = new TH1F("TF_WW_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_WZ_JetMass = new TH1F("TF_WZ_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_LW200_JetMass = new TH1F("TF_LW200_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_LW300_JetMass = new TH1F("TF_LW300_JetMass","TF Invariant mass from DiJets",100,0,400);

//TH1F* TF_LW400_JetMass = new TH1F("TF_LW400_JetMass","TF Invariant mass from DiJets",100,0,400);

//TH1F* TF_LW500_JetMass = new TH1F("TF_LW500_JetMass","TF Invariant mass from DiJets",100,0,400);

TH1F* TF_dataRunB_LWMass = new TH1F("TF_dataRunB_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_dataRunC_LWMass  = new TH1F("TF_dataRunC_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_ZLL_LWMass = new TH1F("TF_ZLL_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_TT_LWMass = new TH1F("TF_TT_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_W3J_LWMass = new TH1F("TF_W3J_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_W2J_LWMass = new TH1F("TF_W2J_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_W1J_LWMass = new TH1F("TF_W1J_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_TTZ_LWMass = new TH1F("TF_TTZ_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_WW_LWMass = new TH1F("TF_WW_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_WZ_LWMass = new TH1F("TF_WZ_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_LW200_LWMass = new TH1F("TF_LW200_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_LW300_LWMass = new TH1F("TF_LW300_LWMass","TF Invariant mass from LW",100,0,400);

//TH1F* TF_LW400_LWMass = new TH1F("TF_LW400_LWMass","TF Invariant mass from LW",100,0,400);

//TH1F* TF_LW500_LWMass = new TH1F("TF_LW500_LWMass","TF Invariant mass from LW",100,0,400);

TH1F* TF_dataRunB_Elept = new TH1F("TF_dataRunB_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_dataRunC_Elept  = new TH1F("TF_dataRunC_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_ZLL_Elept = new TH1F("TF_ZLL_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_TT_Elept = new TH1F("TF_TT_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_W3J_Elept = new TH1F("TF_W3J_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_W2J_Elept = new TH1F("TF_W2J_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_W1J_Elept = new TH1F("TF_W1J_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_TTZ_Elept = new TH1F("TF_TTZ_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_WW_Elept = new TH1F("TF_WW_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_WZ_Elept = new TH1F("TF_WZ_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_LW200_Elept = new TH1F("TF_LW200_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_LW300_Elept = new TH1F("TF_LW300_Elept","TF Electron pt distribution",100,0,200);

//TH1F* TF_LW400_Elept = new TH1F("TF_LW400_Elept","TF Electron pt distribution",100,0,200);

//TH1F* TF_LW500_Elept = new TH1F("TF_LW500_Elept","TF Electron pt distribution",100,0,200);

TH1F* TF_dataRunB_DieledR = new TH1F("TF_dataRunB_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_dataRunC_DieledR  = new TH1F("TF_dataRunC_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_ZLL_DieledR = new TH1F("TF_ZLL_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_TT_DieledR = new TH1F("TF_TT_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_W3J_DieledR = new TH1F("TF_W3J_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_W2J_DieledR = new TH1F("TF_W2J_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_W1J_DieledR = new TH1F("TF_W1J_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_TTZ_DieledR = new TH1F("TF_TTZ_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_WW_DieledR = new TH1F("TF_WW_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_WZ_DieledR = new TH1F("TF_WZ_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_LW200_DieledR = new TH1F("TF_LW200_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_LW300_DieledR = new TH1F("TF_LW300_DieledR","TF delta R separation between electrons",100,0,8);

//TH1F* TF_LW400_DieledR = new TH1F("TF_LW400_DieledR","TF delta R separation between electrons",100,0,8);

//TH1F* TF_LW500_DieledR = new TH1F("TF_LW500_DieledR","TF delta R separation between electrons",100,0,8);

TH1F* TF_dataRunB_LWdR = new TH1F("TF_dataRunB_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_dataRunC_LWdR  = new TH1F("TF_dataRunC_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_ZLL_LWdR = new TH1F("TF_ZLL_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_TT_LWdR = new TH1F("TF_TT_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_W3J_LWdR = new TH1F("TF_W3J_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_W2J_LWdR = new TH1F("TF_W2J_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_W1J_LWdR = new TH1F("TF_W1J_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_TTZ_LWdR = new TH1F("TF_TTZ_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_WW_LWdR = new TH1F("TF_WW_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_WZ_LWdR = new TH1F("TF_WZ_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_LW200_LWdR = new TH1F("TF_LW200_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_LW300_LWdR = new TH1F("TF_LW300_LWdR","TF delta R separation between electrons and jets",100,0,8);

//TH1F* TF_LW400_LWdR = new TH1F("TF_LW400_LWdR","TF delta R separation between electrons and jets",100,0,8);

//TH1F* TF_LW500_LWdR = new TH1F("TF_LW500_LWdR","TF delta R separation between electrons and jets",100,0,8);

TH1F* TF_dataRunB_DiJetdR = new TH1F("TF_dataRunB_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_dataRunC_DiJetdR  = new TH1F("TF_dataRunC_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_ZLL_DiJetdR = new TH1F("TF_ZLL_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_TT_DiJetdR = new TH1F("TF_TT_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_W3J_DiJetdR = new TH1F("TF_W3J_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_W2J_DiJetdR = new TH1F("TF_W2J_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_W1J_DiJetdR = new TH1F("TF_W1J_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_TTZ_DiJetdR = new TH1F("TF_TTZ_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_WW_DiJetdR = new TH1F("TF_WW_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_WZ_DiJetdR = new TH1F("TF_WZ_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_LW200_DiJetdR = new TH1F("TF_LW200_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_LW300_DiJetdR = new TH1F("TF_LW300_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

//TH1F* TF_LW400_DiJetdR = new TH1F("TF_LW400_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

//TH1F* TF_LW500_DiJetdR = new TH1F("TF_LW500_DiJetdR","TF delta R separation between Jet Candidates",100,0,8);

TH1F* TF_dataRunB_BJetPt = new TH1F("TF_dataRunB_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_dataRunC_BJetPt  = new TH1F("TF_dataRunC_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_ZLL_BJetPt = new TH1F("TF_ZLL_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_TT_BJetPt = new TH1F("TF_TT_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_W3J_BJetPt = new TH1F("TF_W3J_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_W2J_BJetPt = new TH1F("TF_W2J_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_W1J_BJetPt = new TH1F("TF_W1J_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_TTZ_BJetPt = new TH1F("TF_TTZ_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_WW_BJetPt = new TH1F("TF_WW_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_WZ_BJetPt = new TH1F("TF_WZ_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_LW200_BJetPt = new TH1F("TF_LW200_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_LW300_BJetPt = new TH1F("TF_LW300_BJetPt","TF Most energetic Jet pt",100,0,250);

//TH1F* TF_LW400_BJetPt = new TH1F("TF_LW400_BJetPt","TF Most energetic Jet pt",100,0,250);

//TH1F* TF_LW500_BJetPt = new TH1F("TF_LW500_BJetPt","TF Most energetic Jet pt",100,0,250);

TH1F* TF_dataRunB_SBJetPt = new TH1F("TF_dataRunB_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_dataRunC_SBJetPt  = new TH1F("TF_dataRunC_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_ZLL_SBJetPt = new TH1F("TF_ZLL_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_TT_SBJetPt = new TH1F("TF_TT_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_W3J_SBJetPt = new TH1F("TF_W3J_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_W2J_SBJetPt = new TH1F("TF_W2J_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_W1J_SBJetPt = new TH1F("TF_W1J_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_TTZ_SBJetPt = new TH1F("TF_TTZ_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_WW_SBJetPt = new TH1F("TF_WW_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_WZ_SBJetPt = new TH1F("TF_WZ_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_LW200_SBJetPt = new TH1F("TF_LW200_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_LW300_SBJetPt = new TH1F("TF_LW300_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

//TH1F* TF_LW400_SBJetPt = new TH1F("TF_LW400_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

//TH1F* TF_LW500_SBJetPt = new TH1F("TF_LW500_SBJetPt","Second TF Most energetic Jet pt",100,0,250);

TH1F* TF_dataRunB_NJet = new TH1F("TF_dataRunB_NJet","TF Number of Jets",20,0,20);

TH1F* TF_dataRunC_NJet  = new TH1F("TF_dataRunC_NJet","TF Number of Jets",20,0,20);

TH1F* TF_ZLL_NJet = new TH1F("TF_ZLL_NJet","TF Number of Jets",20,0,20);

TH1F* TF_TT_NJet = new TH1F("TF_TT_NJet","TF Number of Jets",20,0,20);

TH1F* TF_W3J_NJet = new TH1F("TF_W3J_NJet","TF Number of Jets",20,0,20);

TH1F* TF_W2J_NJet = new TH1F("TF_W2J_NJet","TF Number of Jets",20,0,20);

TH1F* TF_W1J_NJet = new TH1F("TF_W1J_NJet","TF Number of Jets",20,0,20);

TH1F* TF_TTZ_NJet = new TH1F("TF_TTZ_NJet","TF Number of Jets",20,0,20);

TH1F* TF_WW_NJet = new TH1F("TF_WW_NJet","TF Number of Jets",20,0,20);

TH1F* TF_WZ_NJet = new TH1F("TF_WZ_NJet","TF Number of Jets",20,0,20);

TH1F* TF_LW200_NJet = new TH1F("TF_LW200_NJet","TF Number of Jets",20,0,20);

TH1F* TF_LW300_NJet = new TH1F("TF_LW300_NJet","TF Number of Jets",20,0,20);

//TH1F* TF_LW400_NJet = new TH1F("TF_LW400_NJet","TF Number of Jets",20,0,20);

//TH1F* TF_LW500_NJet = new TH1F("TF_LW500_NJet","TF Number of Jets",20,0,20);

TH1F* TF_dataRunB_NEle = new TH1F("TF_dataRunB_NEle","TF Number of electrons",20,0,20);

TH1F* TF_dataRunC_NEle  = new TH1F("TF_dataRunC_NEle","TF Number of electrons",20,0,20);

TH1F* TF_ZLL_NEle = new TH1F("TF_ZLL_NEle","TF Number of electrons",20,0,20);

TH1F* TF_TT_NEle = new TH1F("TF_TT_NEle","TF Number of electrons",20,0,20);

TH1F* TF_W3J_NEle = new TH1F("TF_W3J_NEle","TF Number of electrons",20,0,20);

TH1F* TF_W2J_NEle = new TH1F("TF_W2J_NEle","TF Number of electrons",20,0,20);

TH1F* TF_W1J_NEle = new TH1F("TF_W1J_NEle","TF Number of electrons",20,0,20);

TH1F* TF_TTZ_NEle = new TH1F("TF_TTZ_NEle","TF Number of electrons",20,0,20);

TH1F* TF_WW_NEle = new TH1F("TF_WW_NEle","TF Number of electrons",20,0,20);

TH1F* TF_WZ_NEle = new TH1F("TF_WZ_NEle","TF Number of electrons",20,0,20);

TH1F* TF_LW200_NEle = new TH1F("TF_LW200_NEle","TF Number of electrons",20,0,20);

TH1F* TF_LW300_NEle = new TH1F("TF_LW300_NEle","TF Number of electrons",20,0,20);

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

TH1F* TO_TTZ_npv = new TH1F("TO_TTZ_npv","TO Number of primary vertices",25,5,30);

TH1F* TO_WW_npv = new TH1F("TO_WW_npv","TO Number of primary vertices",25,5,30);

TH1F* TO_WZ_npv = new TH1F("TO_WZ_npv","TO Number of primary vertices",25,5,30);

TH1F* TO_LW200_npv = new TH1F("TO_LW200_npv","TO Number of primary vertices",25,5,30);

TH1F* TO_LW300_npv = new TH1F("TO_LW300_npv","TO Number of primary vertices",25,5,30);

//TH1F* TO_LW400_npv = new TH1F("TO_LW400_npv","TO Number of primary vertices",25,5,30);

//TH1F* TO_LW500_npv = new TH1F("TO_LW500_npv","TO Number of primary vertices",25,5,30);

TH1F* TO_dataRunB_nsv = new TH1F("TO_dataRunB_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_dataRunC_nsv  = new TH1F("TO_dataRunC_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_ZLL_nsv = new TH1F("TO_ZLL_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_TT_nsv = new TH1F("TO_TT_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_W3J_nsv = new TH1F("TO_W3J_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_W2J_nsv = new TH1F("TO_W2J_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_W1J_nsv = new TH1F("TO_W1J_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_TTZ_nsv = new TH1F("TO_TTZ_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_WW_nsv = new TH1F("TO_WW_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_WZ_nsv = new TH1F("TO_WZ_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_LW200_nsv = new TH1F("TO_LW200_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_LW300_nsv = new TH1F("TO_LW300_nsv","TO Number of secondary vertices",20,0,2000);

//TH1F* TO_LW400_nsv = new TH1F("TO_LW400_nsv","TO Number of secondary vertices",20,0,2000);

//TH1F* TO_LW500_nsv = new TH1F("TO_LW500_nsv","TO Number of secondary vertices",20,0,2000);

TH1F* TO_dataRunB_svd = new TH1F("TO_dataRunB_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_dataRunC_svd  = new TH1F("TO_dataRunC_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_ZLL_svd = new TH1F("TO_ZLL_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_TT_svd = new TH1F("TO_TT_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_W3J_svd = new TH1F("TO_W3J_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_W2J_svd = new TH1F("TO_W2J_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_W1J_svd = new TH1F("TO_W1J_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_TTZ_svd = new TH1F("TO_TTZ_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_WW_svd = new TH1F("TO_WW_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_WZ_svd = new TH1F("TO_WZ_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_LW200_svd = new TH1F("TO_LW200_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_LW300_svd = new TH1F("TO_LW300_svd","TO secondary vertex displacement",100,0,1);

//TH1F* TO_LW400_svd = new TH1F("TO_LW400_svd","TO secondary vertex displacement",100,0,1);

//TH1F* TO_LW500_svd = new TH1F("TO_LW500_svd","TO secondary vertex displacement",100,0,1);

TH1F* TO_dataRunB_JetMass = new TH1F("TO_dataRunB_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_dataRunC_JetMass  = new TH1F("TO_dataRunC_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_ZLL_JetMass = new TH1F("TO_ZLL_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_TT_JetMass = new TH1F("TO_TT_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_W3J_JetMass = new TH1F("TO_W3J_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_W2J_JetMass = new TH1F("TO_W2J_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_W1J_JetMass = new TH1F("TO_W1J_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_TTZ_JetMass = new TH1F("TO_TTZ_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_WW_JetMass = new TH1F("TO_WW_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_WZ_JetMass = new TH1F("TO_WZ_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_LW200_JetMass = new TH1F("TO_LW200_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_LW300_JetMass = new TH1F("TO_LW300_JetMass","TO Invariant mass from DiJets",100,0,400);

//TH1F* TO_LW400_JetMass = new TH1F("TO_LW400_JetMass","TO Invariant mass from DiJets",100,0,400);

//TH1F* TO_LW500_JetMass = new TH1F("TO_LW500_JetMass","TO Invariant mass from DiJets",100,0,400);

TH1F* TO_dataRunB_LWMass = new TH1F("TO_dataRunB_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_dataRunC_LWMass  = new TH1F("TO_dataRunC_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_ZLL_LWMass = new TH1F("TO_ZLL_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_TT_LWMass = new TH1F("TO_TT_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_W3J_LWMass = new TH1F("TO_W3J_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_W2J_LWMass = new TH1F("TO_W2J_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_W1J_LWMass = new TH1F("TO_W1J_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_TTZ_LWMass = new TH1F("TO_TTZ_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_WW_LWMass = new TH1F("TO_WW_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_WZ_LWMass = new TH1F("TO_WZ_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_LW200_LWMass = new TH1F("TO_LW200_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_LW300_LWMass = new TH1F("TO_LW300_LWMass","TO Invariant mass from LW",100,0,400);

//TH1F* TO_LW400_LWMass = new TH1F("TO_LW400_LWMass","TO Invariant mass from LW",100,0,400);

//TH1F* TO_LW500_LWMass = new TH1F("TO_LW500_LWMass","TO Invariant mass from LW",100,0,400);

TH1F* TO_dataRunB_Elept = new TH1F("TO_dataRunB_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_dataRunC_Elept  = new TH1F("TO_dataRunC_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_ZLL_Elept = new TH1F("TO_ZLL_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_TT_Elept = new TH1F("TO_TT_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_W3J_Elept = new TH1F("TO_W3J_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_W2J_Elept = new TH1F("TO_W2J_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_W1J_Elept = new TH1F("TO_W1J_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_TTZ_Elept = new TH1F("TO_TTZ_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_WW_Elept = new TH1F("TO_WW_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_WZ_Elept = new TH1F("TO_WZ_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_LW200_Elept = new TH1F("TO_LW200_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_LW300_Elept = new TH1F("TO_LW300_Elept","TO Electron pt distribution",100,0,200);

//TH1F* TO_LW400_Elept = new TH1F("TO_LW400_Elept","TO Electron pt distribution",100,0,200);

//TH1F* TO_LW500_Elept = new TH1F("TO_LW500_Elept","TO Electron pt distribution",100,0,200);

TH1F* TO_dataRunB_DieledR = new TH1F("TO_dataRunB_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_dataRunC_DieledR  = new TH1F("TO_dataRunC_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_ZLL_DieledR = new TH1F("TO_ZLL_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_TT_DieledR = new TH1F("TO_TT_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_W3J_DieledR = new TH1F("TO_W3J_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_W2J_DieledR = new TH1F("TO_W2J_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_W1J_DieledR = new TH1F("TO_W1J_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_TTZ_DieledR = new TH1F("TO_TTZ_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_WW_DieledR = new TH1F("TO_WW_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_WZ_DieledR = new TH1F("TO_WZ_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_LW200_DieledR = new TH1F("TO_LW200_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_LW300_DieledR = new TH1F("TO_LW300_DieledR","TO delta R separation between electrons",100,0,8);

//TH1F* TO_LW400_DieledR = new TH1F("TO_LW400_DieledR","TO delta R separation between electrons",100,0,8);

//TH1F* TO_LW500_DieledR = new TH1F("TO_LW500_DieledR","TO delta R separation between electrons",100,0,8);

TH1F* TO_dataRunB_LWdR = new TH1F("TO_dataRunB_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_dataRunC_LWdR  = new TH1F("TO_dataRunC_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_ZLL_LWdR = new TH1F("TO_ZLL_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_TT_LWdR = new TH1F("TO_TT_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_W3J_LWdR = new TH1F("TO_W3J_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_W2J_LWdR = new TH1F("TO_W2J_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_W1J_LWdR = new TH1F("TO_W1J_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_TTZ_LWdR = new TH1F("TO_TTZ_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_WW_LWdR = new TH1F("TO_WW_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_WZ_LWdR = new TH1F("TO_WZ_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_LW200_LWdR = new TH1F("TO_LW200_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_LW300_LWdR = new TH1F("TO_LW300_LWdR","TO delta R separation between electrons and jets",100,0,8);

//TH1F* TO_LW400_LWdR = new TH1F("TO_LW400_LWdR","TO delta R separation between electrons and jets",100,0,8);

//TH1F* TO_LW500_LWdR = new TH1F("TO_LW500_LWdR","TO delta R separation between electrons and jets",100,0,8);

TH1F* TO_dataRunB_DiJetdR = new TH1F("TO_dataRunB_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_dataRunC_DiJetdR  = new TH1F("TO_dataRunC_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_ZLL_DiJetdR = new TH1F("TO_ZLL_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_TT_DiJetdR = new TH1F("TO_TT_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_W3J_DiJetdR = new TH1F("TO_W3J_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_W2J_DiJetdR = new TH1F("TO_W2J_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_W1J_DiJetdR = new TH1F("TO_W1J_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_TTZ_DiJetdR = new TH1F("TO_TTZ_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_WW_DiJetdR = new TH1F("TO_WW_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_WZ_DiJetdR = new TH1F("TO_WZ_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_LW200_DiJetdR = new TH1F("TO_LW200_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_LW300_DiJetdR = new TH1F("TO_LW300_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

//TH1F* TO_LW400_DiJetdR = new TH1F("TO_LW400_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

//TH1F* TO_LW500_DiJetdR = new TH1F("TO_LW500_DiJetdR","TO delta R separation between Jet Candidates",100,0,8);

TH1F* TO_dataRunB_BJetPt = new TH1F("TO_dataRunB_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_dataRunC_BJetPt  = new TH1F("TO_dataRunC_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_ZLL_BJetPt = new TH1F("TO_ZLL_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_TT_BJetPt = new TH1F("TO_TT_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_W3J_BJetPt = new TH1F("TO_W3J_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_W2J_BJetPt = new TH1F("TO_W2J_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_W1J_BJetPt = new TH1F("TO_W1J_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_TTZ_BJetPt = new TH1F("TO_TTZ_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_WW_BJetPt = new TH1F("TO_WW_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_WZ_BJetPt = new TH1F("TO_WZ_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_LW200_BJetPt = new TH1F("TO_LW200_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_LW300_BJetPt = new TH1F("TO_LW300_BJetPt","TO Most energetic Jet pt",100,0,250);

//TH1F* TO_LW400_BJetPt = new TH1F("TO_LW400_BJetPt","TO Most energetic Jet pt",100,0,250);

//TH1F* TO_LW500_BJetPt = new TH1F("TO_LW500_BJetPt","TO Most energetic Jet pt",100,0,250);

TH1F* TO_dataRunB_SBJetPt = new TH1F("TO_dataRunB_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_dataRunC_SBJetPt  = new TH1F("TO_dataRunC_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_ZLL_SBJetPt = new TH1F("TO_ZLL_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_TT_SBJetPt = new TH1F("TO_TT_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_W3J_SBJetPt = new TH1F("TO_W3J_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_W2J_SBJetPt = new TH1F("TO_W2J_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_W1J_SBJetPt = new TH1F("TO_W1J_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_TTZ_SBJetPt = new TH1F("TO_TTZ_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_WW_SBJetPt = new TH1F("TO_WW_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_WZ_SBJetPt = new TH1F("TO_WZ_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_LW200_SBJetPt = new TH1F("TO_LW200_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_LW300_SBJetPt = new TH1F("TO_LW300_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

//TH1F* TO_LW400_SBJetPt = new TH1F("TO_LW400_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

//TH1F* TO_LW500_SBJetPt = new TH1F("TO_LW500_SBJetPt","Second TO Most energetic Jet pt",100,0,250);

TH1F* TO_dataRunB_NJet = new TH1F("TO_dataRunB_NJet","TO Number of Jets",20,0,20);

TH1F* TO_dataRunC_NJet  = new TH1F("TO_dataRunC_NJet","TO Number of Jets",20,0,20);

TH1F* TO_ZLL_NJet = new TH1F("TO_ZLL_NJet","TO Number of Jets",20,0,20);

TH1F* TO_TT_NJet = new TH1F("TO_TT_NJet","TO Number of Jets",20,0,20);

TH1F* TO_W3J_NJet = new TH1F("TO_W3J_NJet","TO Number of Jets",20,0,20);

TH1F* TO_W2J_NJet = new TH1F("TO_W2J_NJet","TO Number of Jets",20,0,20);

TH1F* TO_W1J_NJet = new TH1F("TO_W1J_NJet","TO Number of Jets",20,0,20);

TH1F* TO_TTZ_NJet = new TH1F("TO_TTZ_NJet","TO Number of Jets",20,0,20);

TH1F* TO_WW_NJet = new TH1F("TO_WW_NJet","TO Number of Jets",20,0,20);

TH1F* TO_WZ_NJet = new TH1F("TO_WZ_NJet","TO Number of Jets",20,0,20);

TH1F* TO_LW200_NJet = new TH1F("TO_LW200_NJet","TO Number of Jets",20,0,20);

TH1F* TO_LW300_NJet = new TH1F("TO_LW300_NJet","TO Number of Jets",20,0,20);

//TH1F* TO_LW400_NJet = new TH1F("TO_LW400_NJet","TO Number of Jets",20,0,20);

//TH1F* TO_LW500_NJet = new TH1F("TO_LW500_NJet","TO Number of Jets",20,0,20);

TH1F* TO_dataRunB_NEle = new TH1F("TO_dataRunB_NEle","TO Number of electrons",20,0,20);

TH1F* TO_dataRunC_NEle  = new TH1F("TO_dataRunC_NEle","TO Number of electrons",20,0,20);

TH1F* TO_ZLL_NEle = new TH1F("TO_ZLL_NEle","TO Number of electrons",20,0,20);

TH1F* TO_TT_NEle = new TH1F("TO_TT_NEle","TO Number of electrons",20,0,20);

TH1F* TO_W3J_NEle = new TH1F("TO_W3J_NEle","TO Number of electrons",20,0,20);

TH1F* TO_W2J_NEle = new TH1F("TO_W2J_NEle","TO Number of electrons",20,0,20);

TH1F* TO_W1J_NEle = new TH1F("TO_W1J_NEle","TO Number of electrons",20,0,20);

TH1F* TO_TTZ_NEle = new TH1F("TO_TTZ_NEle","TO Number of electrons",20,0,20);

TH1F* TO_WW_NEle = new TH1F("TO_WW_NEle","TO Number of electrons",20,0,20);

TH1F* TO_WZ_NEle = new TH1F("TO_WZ_NEle","TO Number of electrons",20,0,20);

TH1F* TO_LW200_NEle = new TH1F("TO_LW200_NEle","TO Number of electrons",20,0,20);

TH1F* TO_LW300_NEle = new TH1F("TO_LW300_NEle","TO Number of electrons",20,0,20);

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

TH1F* HQ_TTZ_npv = new TH1F("HQ_TTZ_npv","HQ Number of primary vertices",25,5,30);

TH1F* HQ_WW_npv = new TH1F("HQ_WW_npv","HQ Number of primary vertices",25,5,30);

TH1F* HQ_WZ_npv = new TH1F("HQ_WZ_npv","HQ Number of primary vertices",25,5,30);

TH1F* HQ_LW200_npv = new TH1F("HQ_LW200_npv","HQ Number of primary vertices",25,5,30);

TH1F* HQ_LW300_npv = new TH1F("HQ_LW300_npv","HQ Number of primary vertices",25,5,30);

//TH1F* HQ_LW400_npv = new TH1F("HQ_LW400_npv","HQ Number of primary vertices",25,5,30);

//TH1F* HQ_LW500_npv = new TH1F("HQ_LW500_npv","HQ Number of primary vertices",25,5,30);

TH1F* HQ_dataRunB_nsv = new TH1F("HQ_dataRunB_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_dataRunC_nsv  = new TH1F("HQ_dataRunC_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_ZLL_nsv = new TH1F("HQ_ZLL_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_TT_nsv = new TH1F("HQ_TT_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_W3J_nsv = new TH1F("HQ_W3J_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_W2J_nsv = new TH1F("HQ_W2J_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_W1J_nsv = new TH1F("HQ_W1J_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_TTZ_nsv = new TH1F("HQ_TTZ_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_WW_nsv = new TH1F("HQ_WW_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_WZ_nsv = new TH1F("HQ_WZ_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_LW200_nsv = new TH1F("HQ_LW200_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_LW300_nsv = new TH1F("HQ_LW300_nsv","HQ Number of secondary vertices",20,0,2000);

//TH1F* HQ_LW400_nsv = new TH1F("HQ_LW400_nsv","HQ Number of secondary vertices",20,0,2000);

//TH1F* HQ_LW500_nsv = new TH1F("HQ_LW500_nsv","HQ Number of secondary vertices",20,0,2000);

TH1F* HQ_dataRunB_svd = new TH1F("HQ_dataRunB_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_dataRunC_svd  = new TH1F("HQ_dataRunC_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_ZLL_svd = new TH1F("HQ_ZLL_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_TT_svd = new TH1F("HQ_TT_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_W3J_svd = new TH1F("HQ_W3J_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_W2J_svd = new TH1F("HQ_W2J_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_W1J_svd = new TH1F("HQ_W1J_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_TTZ_svd = new TH1F("HQ_TTZ_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_WW_svd = new TH1F("HQ_WW_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_WZ_svd = new TH1F("HQ_WZ_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_LW200_svd = new TH1F("HQ_LW200_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_LW300_svd = new TH1F("HQ_LW300_svd","HQ secondary vertex displacement",100,0,1);

//TH1F* HQ_LW400_svd = new TH1F("HQ_LW400_svd","HQ secondary vertex displacement",100,0,1);

//TH1F* HQ_LW500_svd = new TH1F("HQ_LW500_svd","HQ secondary vertex displacement",100,0,1);

TH1F* HQ_dataRunB_JetMass = new TH1F("HQ_dataRunB_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_dataRunC_JetMass  = new TH1F("HQ_dataRunC_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_ZLL_JetMass = new TH1F("HQ_ZLL_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_TT_JetMass = new TH1F("HQ_TT_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_W3J_JetMass = new TH1F("HQ_W3J_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_W2J_JetMass = new TH1F("HQ_W2J_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_W1J_JetMass = new TH1F("HQ_W1J_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_TTZ_JetMass = new TH1F("HQ_TTZ_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_WW_JetMass = new TH1F("HQ_WW_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_WZ_JetMass = new TH1F("HQ_WZ_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_LW200_JetMass = new TH1F("HQ_LW200_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_LW300_JetMass = new TH1F("HQ_LW300_JetMass","HQ Invariant mass from DiJets",100,0,400);

//TH1F* HQ_LW400_JetMass = new TH1F("HQ_LW400_JetMass","HQ Invariant mass from DiJets",100,0,400);

//TH1F* HQ_LW500_JetMass = new TH1F("HQ_LW500_JetMass","HQ Invariant mass from DiJets",100,0,400);

TH1F* HQ_dataRunB_LWMass = new TH1F("HQ_dataRunB_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_dataRunC_LWMass  = new TH1F("HQ_dataRunC_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_ZLL_LWMass = new TH1F("HQ_ZLL_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_TT_LWMass = new TH1F("HQ_TT_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_W3J_LWMass = new TH1F("HQ_W3J_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_W2J_LWMass = new TH1F("HQ_W2J_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_W1J_LWMass = new TH1F("HQ_W1J_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_TTZ_LWMass = new TH1F("HQ_TTZ_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_WW_LWMass = new TH1F("HQ_WW_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_WZ_LWMass = new TH1F("HQ_WZ_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_LW200_LWMass = new TH1F("HQ_LW200_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_LW300_LWMass = new TH1F("HQ_LW300_LWMass","HQ Invariant mass from LW",100,0,400);

//TH1F* HQ_LW400_LWMass = new TH1F("HQ_LW400_LWMass","HQ Invariant mass from LW",100,0,400);

//TH1F* HQ_LW500_LWMass = new TH1F("HQ_LW500_LWMass","HQ Invariant mass from LW",100,0,400);

TH1F* HQ_dataRunB_Elept = new TH1F("HQ_dataRunB_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_dataRunC_Elept  = new TH1F("HQ_dataRunC_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_ZLL_Elept = new TH1F("HQ_ZLL_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_TT_Elept = new TH1F("HQ_TT_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_W3J_Elept = new TH1F("HQ_W3J_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_W2J_Elept = new TH1F("HQ_W2J_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_W1J_Elept = new TH1F("HQ_W1J_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_TTZ_Elept = new TH1F("HQ_TTZ_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_WW_Elept = new TH1F("HQ_WW_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_WZ_Elept = new TH1F("HQ_WZ_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_LW200_Elept = new TH1F("HQ_LW200_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_LW300_Elept = new TH1F("HQ_LW300_Elept","HQ Electron pt distribution",100,0,200);

//TH1F* HQ_LW400_Elept = new TH1F("HQ_LW400_Elept","HQ Electron pt distribution",100,0,200);

//TH1F* HQ_LW500_Elept = new TH1F("HQ_LW500_Elept","HQ Electron pt distribution",100,0,200);

TH1F* HQ_dataRunB_DieledR = new TH1F("HQ_dataRunB_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_dataRunC_DieledR  = new TH1F("HQ_dataRunC_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_ZLL_DieledR = new TH1F("HQ_ZLL_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_TT_DieledR = new TH1F("HQ_TT_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_W3J_DieledR = new TH1F("HQ_W3J_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_W2J_DieledR = new TH1F("HQ_W2J_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_W1J_DieledR = new TH1F("HQ_W1J_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_TTZ_DieledR = new TH1F("HQ_TTZ_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_WW_DieledR = new TH1F("HQ_WW_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_WZ_DieledR = new TH1F("HQ_WZ_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_LW200_DieledR = new TH1F("HQ_LW200_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_LW300_DieledR = new TH1F("HQ_LW300_DieledR","HQ delta R separation between electrons",100,0,8);

//TH1F* HQ_LW400_DieledR = new TH1F("HQ_LW400_DieledR","HQ delta R separation between electrons",100,0,8);

//TH1F* HQ_LW500_DieledR = new TH1F("HQ_LW500_DieledR","HQ delta R separation between electrons",100,0,8);

TH1F* HQ_dataRunB_LWdR = new TH1F("HQ_dataRunB_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_dataRunC_LWdR  = new TH1F("HQ_dataRunC_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_ZLL_LWdR = new TH1F("HQ_ZLL_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_TT_LWdR = new TH1F("HQ_TT_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_W3J_LWdR = new TH1F("HQ_W3J_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_W2J_LWdR = new TH1F("HQ_W2J_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_W1J_LWdR = new TH1F("HQ_W1J_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_TTZ_LWdR = new TH1F("HQ_TTZ_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_WW_LWdR = new TH1F("HQ_WW_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_WZ_LWdR = new TH1F("HQ_WZ_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_LW200_LWdR = new TH1F("HQ_LW200_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_LW300_LWdR = new TH1F("HQ_LW300_LWdR","HQ delta R separation between electrons and jets",100,0,8);

//TH1F* HQ_LW400_LWdR = new TH1F("HQ_LW400_LWdR","HQ delta R separation between electrons and jets",100,0,8);

//TH1F* HQ_LW500_LWdR = new TH1F("HQ_LW500_LWdR","HQ delta R separation between electrons and jets",100,0,8);

TH1F* HQ_dataRunB_DiJetdR = new TH1F("HQ_dataRunB_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_dataRunC_DiJetdR  = new TH1F("HQ_dataRunC_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_ZLL_DiJetdR = new TH1F("HQ_ZLL_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_TT_DiJetdR = new TH1F("HQ_TT_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_W3J_DiJetdR = new TH1F("HQ_W3J_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_W2J_DiJetdR = new TH1F("HQ_W2J_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_W1J_DiJetdR = new TH1F("HQ_W1J_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_TTZ_DiJetdR = new TH1F("HQ_TTZ_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_WW_DiJetdR = new TH1F("HQ_WW_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_WZ_DiJetdR = new TH1F("HQ_WZ_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_LW200_DiJetdR = new TH1F("HQ_LW200_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_LW300_DiJetdR = new TH1F("HQ_LW300_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

//TH1F* HQ_LW400_DiJetdR = new TH1F("HQ_LW400_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

//TH1F* HQ_LW500_DiJetdR = new TH1F("HQ_LW500_DiJetdR","HQ delta R separation between Jet Candidates",100,0,8);

TH1F* HQ_dataRunB_BJetPt = new TH1F("HQ_dataRunB_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_dataRunC_BJetPt  = new TH1F("HQ_dataRunC_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_ZLL_BJetPt = new TH1F("HQ_ZLL_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_TT_BJetPt = new TH1F("HQ_TT_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_W3J_BJetPt = new TH1F("HQ_W3J_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_W2J_BJetPt = new TH1F("HQ_W2J_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_W1J_BJetPt = new TH1F("HQ_W1J_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_TTZ_BJetPt = new TH1F("HQ_TTZ_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_WW_BJetPt = new TH1F("HQ_WW_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_WZ_BJetPt = new TH1F("HQ_WZ_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_LW200_BJetPt = new TH1F("HQ_LW200_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_LW300_BJetPt = new TH1F("HQ_LW300_BJetPt","HQ Most energetic Jet pt",100,0,250);

//TH1F* HQ_LW400_BJetPt = new TH1F("HQ_LW400_BJetPt","HQ Most energetic Jet pt",100,0,250);

//TH1F* HQ_LW500_BJetPt = new TH1F("HQ_LW500_BJetPt","HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_dataRunB_SBJetPt = new TH1F("HQ_dataRunB_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_dataRunC_SBJetPt  = new TH1F("HQ_dataRunC_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_ZLL_SBJetPt = new TH1F("HQ_ZLL_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_TT_SBJetPt = new TH1F("HQ_TT_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_W3J_SBJetPt = new TH1F("HQ_W3J_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_W2J_SBJetPt = new TH1F("HQ_W2J_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_W1J_SBJetPt = new TH1F("HQ_W1J_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_TTZ_SBJetPt = new TH1F("HQ_TTZ_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_WW_SBJetPt = new TH1F("HQ_WW_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_WZ_SBJetPt = new TH1F("HQ_WZ_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_LW200_SBJetPt = new TH1F("HQ_LW200_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_LW300_SBJetPt = new TH1F("HQ_LW300_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

//TH1F* HQ_LW400_SBJetPt = new TH1F("HQ_LW400_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

//TH1F* HQ_LW500_SBJetPt = new TH1F("HQ_LW500_SBJetPt","Second HQ Most energetic Jet pt",100,0,250);

TH1F* HQ_dataRunB_NJet = new TH1F("HQ_dataRunB_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_dataRunC_NJet  = new TH1F("HQ_dataRunC_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_ZLL_NJet = new TH1F("HQ_ZLL_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_TT_NJet = new TH1F("HQ_TT_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_W3J_NJet = new TH1F("HQ_W3J_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_W2J_NJet = new TH1F("HQ_W2J_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_W1J_NJet = new TH1F("HQ_W1J_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_TTZ_NJet = new TH1F("HQ_TTZ_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_WW_NJet = new TH1F("HQ_WW_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_WZ_NJet = new TH1F("HQ_WZ_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_LW200_NJet = new TH1F("HQ_LW200_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_LW300_NJet = new TH1F("HQ_LW300_NJet","HQ Number of Jets",20,0,20);

//TH1F* HQ_LW400_NJet = new TH1F("HQ_LW400_NJet","HQ Number of Jets",20,0,20);

//TH1F* HQ_LW500_NJet = new TH1F("HQ_LW500_NJet","HQ Number of Jets",20,0,20);

TH1F* HQ_dataRunB_NEle = new TH1F("HQ_dataRunB_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_dataRunC_NEle  = new TH1F("HQ_dataRunC_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_ZLL_NEle = new TH1F("HQ_ZLL_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_TT_NEle = new TH1F("HQ_TT_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_W3J_NEle = new TH1F("HQ_W3J_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_W2J_NEle = new TH1F("HQ_W2J_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_W1J_NEle = new TH1F("HQ_W1J_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_TTZ_NEle = new TH1F("HQ_TTZ_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_WW_NEle = new TH1F("HQ_WW_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_WZ_NEle = new TH1F("HQ_WZ_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_LW200_NEle = new TH1F("HQ_LW200_NEle","HQ Number of electrons",20,0,20);

TH1F* HQ_LW300_NEle = new TH1F("HQ_LW300_NEle","HQ Number of electrons",20,0,20);

//TH1F* HQ_LW400_NEle = new TH1F("HQ_LW400_NEle","HQ Number of electrons",20,0,20);

//TH1F* HQ_LW500_NEle = new TH1F("HQ_LW500_NEle","HQ Number of electrons",20,0,20);

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
  TH1F            *hists[nhists];

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
  hists[0] = NF_dataRunB_npv;
  hists[1] = NF_dataRunC_npv;
  hists[2] = NF_ZLL_npv;
  hists[3] = NF_TT_npv;
  hists[4] = NF_W3J_npv;
  hists[5] = NF_W2J_npv;
  hists[6] = NF_W1J_npv;
  hists[21] = NF_LW200_npv;
  hists[7] = NF_dataRunB_JetMass;
  hists[8] = NF_dataRunC_JetMass;
  hists[9] = NF_ZLL_JetMass;
  hists[10] = NF_TT_JetMass;
  hists[11] = NF_W3J_JetMass;
  hists[12] = NF_W2J_JetMass;
  hists[13] = NF_W1J_JetMass;
  hists[22] = NF_LW200_JetMass;
  hists[14] = NF_dataRunB_LWMass;
  hists[15] = NF_dataRunC_LWMass;
  hists[16] = NF_ZLL_LWMass;
  hists[17] = NF_TT_LWMass;
  hists[18] = NF_W3J_LWMass;
  hists[19] = NF_W2J_LWMass;
  hists[20] = NF_W1J_LWMass;
  hists[23] = NF_LW200_LWMass;
  hists[24] = NF_WW_npv;
  hists[25] = NF_WZ_npv;
  hists[26] = NF_TTZ_npv;
  hists[27] = NF_WW_JetMass;
  hists[28] = NF_WZ_JetMass;
  hists[29] = NF_TTZ_JetMass;
  hists[30] = NF_WW_LWMass;
  hists[31] = NF_WZ_LWMass;
  hists[32] = NF_TTZ_LWMass;
  hists[33] = NF_LW300_LWMass;
  //hists[34] = NF_LW400_LWMass;
  //hists[35] = NF_LW500_LWMass;
  hists[34] = NF_LW300_JetMass;
  //hists[37] = NF_LW400_JetMass;
  //hists[38] = NF_LW500_JetMass;
  hists[35] = NF_LW300_npv;
  //hists[40] = NF_LW400_npv;
  //hists[41] = NF_LW500_npv;
  hists[36] = NF_dataRunB_nsv;
  hists[37] = NF_dataRunC_nsv;
  hists[38] = NF_ZLL_nsv;
  hists[39] = NF_TT_nsv;
  hists[40] = NF_W3J_nsv;
  hists[41] = NF_W2J_nsv;
  hists[42] = NF_W1J_nsv;
  hists[43] = NF_WW_nsv;
  hists[44] = NF_WZ_nsv;
  hists[45] = NF_TTZ_nsv;
  hists[46] = NF_LW200_nsv;
  hists[47] = NF_LW200_nsv;
  //hists[40] = NF_LW400_nsv;
  //hists[41] = NF_LW500_nsv;
  hists[48] = NF_dataRunB_svd;
  hists[49] = NF_dataRunC_svd;
  hists[50] = NF_ZLL_svd;
  hists[51] = NF_TT_svd;
  hists[52] = NF_W3J_svd;
  hists[53] = NF_W2J_svd;
  hists[54] = NF_W1J_svd;
  hists[55] = NF_WW_svd;
  hists[56] = NF_WZ_svd;
  hists[57] = NF_TTZ_svd;
  hists[58] = NF_LW200_svd;
  hists[59] = NF_LW200_svd;
  //hists[40] = NF_LW400_svd;
  //hists[41] = NF_LW500_svd;
  hists[60] = NF_dataRunB_Elept;
  hists[61] = NF_dataRunC_Elept;
  hists[62] = NF_ZLL_Elept;
  hists[63] = NF_TT_Elept;
  hists[64] = NF_W3J_Elept;
  hists[65] = NF_W2J_Elept;
  hists[66] = NF_W1J_Elept;
  hists[67] = NF_WW_Elept;
  hists[68] = NF_WZ_Elept;
  hists[69] = NF_TTZ_Elept;
  hists[70] = NF_LW200_Elept;
  hists[71] = NF_LW200_Elept;
  //hists[40] = NF_LW400_svd;
  //hists[41] = NF_LW500_svd;
  hists[72] = NF_dataRunB_DieledR;
  hists[73] = NF_dataRunC_DieledR;
  hists[74] = NF_ZLL_DieledR;
  hists[75] = NF_TT_DieledR;
  hists[76] = NF_W3J_DieledR;
  hists[77] = NF_W2J_DieledR;
  hists[78] = NF_W1J_DieledR;
  hists[79] = NF_WW_DieledR;
  hists[80] = NF_WZ_DieledR;
  hists[81] = NF_TTZ_DieledR;
  hists[82] = NF_LW200_DieledR;
  hists[83] = NF_LW200_DieledR;
  //hists[40] = NF_LW400_svd;
  //hists[41] = NF_LW500_svd;
  hists[84] = NF_dataRunB_LWdR;
  hists[85] = NF_dataRunC_LWdR;
  hists[86] = NF_ZLL_LWdR;
  hists[87] = NF_TT_LWdR;
  hists[88] = NF_W3J_LWdR;
  hists[89] = NF_W2J_LWdR;
  hists[90] = NF_W1J_LWdR;
  hists[91] = NF_WW_LWdR;
  hists[92] = NF_WZ_LWdR;
  hists[93] = NF_TTZ_LWdR;
  hists[94] = NF_LW200_LWdR;
  hists[95] = NF_LW200_LWdR;
  //hists[40] = NF_LW400_svd;
  //hists[41] = NF_LW500_svd;
  hists[96] = NF_dataRunB_DiJetdR;
  hists[97] = NF_dataRunC_DiJetdR;
  hists[98] = NF_ZLL_DiJetdR;
  hists[99] = NF_TT_DiJetdR;
  hists[100] = NF_W3J_DiJetdR;
  hists[101] = NF_W2J_DiJetdR;
  hists[102] = NF_W1J_DiJetdR;
  hists[103] = NF_WW_DiJetdR;
  hists[104] = NF_WZ_DiJetdR;
  hists[105] = NF_TTZ_DiJetdR;
  hists[106] = NF_LW200_DiJetdR;
  hists[107] = NF_LW200_DiJetdR;
  //hists[40] = NF_LW400_svd;
  //hists[41] = NF_LW500_svd;
  hists[108] = NF_dataRunB_BJetPt;
  hists[109] = NF_dataRunC_BJetPt;
  hists[110] = NF_ZLL_BJetPt;
  hists[111] = NF_TT_BJetPt;
  hists[112] = NF_W3J_BJetPt;
  hists[113] = NF_W2J_BJetPt;
  hists[114] = NF_W1J_BJetPt;
  hists[115] = NF_WW_BJetPt;
  hists[116] = NF_WZ_BJetPt;
  hists[117] = NF_TTZ_BJetPt;
  hists[118] = NF_LW200_BJetPt;
  hists[119] = NF_LW200_BJetPt;
  //hists[40] = NF_LW400_svd;
  //hists[41] = NF_LW500_svd;
  hists[120] = NF_dataRunB_SBJetPt;
  hists[121] = NF_dataRunC_SBJetPt;
  hists[122] = NF_ZLL_SBJetPt;
  hists[123] = NF_TT_SBJetPt;
  hists[124] = NF_W3J_SBJetPt;
  hists[125] = NF_W2J_SBJetPt;
  hists[126] = NF_W1J_SBJetPt;
  hists[127] = NF_WW_SBJetPt;
  hists[128] = NF_WZ_SBJetPt;
  hists[129] = NF_TTZ_SBJetPt;
  hists[130] = NF_LW200_SBJetPt;
  hists[131] = NF_LW200_SBJetPt;
  //hists[40] = NF_LW400_svd;
  //hists[41] = NF_LW500_svd;
  hists[132] = NF_dataRunB_NJet;
  hists[133] = NF_dataRunC_NJet;
  hists[134] = NF_ZLL_NJet;
  hists[135] = NF_TT_NJet;
  hists[136] = NF_W3J_NJet;
  hists[137] = NF_W2J_NJet;
  hists[138] = NF_W1J_NJet;
  hists[139] = NF_WW_NJet;
  hists[140] = NF_WZ_NJet;
  hists[141] = NF_TTZ_NJet;
  hists[142] = NF_LW200_NJet;
  hists[143] = NF_LW200_NJet;
  //hists[40] = NF_LW400_svd;
  //hists[41] = NF_LW500_svd;
  hists[144] = NF_dataRunB_NEle;
  hists[145] = NF_dataRunC_NEle;
  hists[146] = NF_ZLL_NEle;
  hists[147] = NF_TT_NEle;
  hists[148] = NF_W3J_NEle;
  hists[149] = NF_W2J_NEle;
  hists[150] = NF_W1J_NEle;
  hists[151] = NF_WW_NEle;
  hists[152] = NF_WZ_NEle;
  hists[153] = NF_TTZ_NEle;
  hists[154] = NF_LW200_NEle;
  hists[155] = NF_LW200_NEle;
  //hists[40] = NF_LW400_svd;
  //hists[41] = NF_LW500_svd;

  hists[156] = TF_dataRunB_npv;
  hists[157] = TF_dataRunC_npv;
  hists[158] = TF_ZLL_npv;
  hists[159] = TF_TT_npv;
  hists[160] = TF_W3J_npv;
  hists[161] = TF_W2J_npv;
  hists[162] = TF_W1J_npv;
  hists[163] = TF_LW200_npv;
  hists[164] = TF_dataRunB_JetMass;
  hists[165] = TF_dataRunC_JetMass;
  hists[166] = TF_ZLL_JetMass;
  hists[167] = TF_TT_JetMass;
  hists[168] = TF_W3J_JetMass;
  hists[169] = TF_W2J_JetMass;
  hists[170] = TF_W1J_JetMass;
  hists[171] = TF_LW200_JetMass;
  hists[172] = TF_dataRunB_LWMass;
  hists[173] = TF_dataRunC_LWMass;
  hists[174] = TF_ZLL_LWMass;
  hists[175] = TF_TT_LWMass;
  hists[176] = TF_W3J_LWMass;
  hists[177] = TF_W2J_LWMass;
  hists[178] = TF_W1J_LWMass;
  hists[179] = TF_LW200_LWMass;
  hists[180] = TF_WW_npv;
  hists[181] = TF_WZ_npv;
  hists[182] = TF_TTZ_npv;
  hists[183] = TF_WW_JetMass;
  hists[184] = TF_WZ_JetMass;
  hists[185] = TF_TTZ_JetMass;
  hists[186] = TF_WW_LWMass;
  hists[187] = TF_WZ_LWMass;
  hists[188] = TF_TTZ_LWMass;
  hists[189] = TF_LW300_LWMass;
  //hists[34] = TF_LW400_LWMass;
  //hists[35] = TF_LW500_LWMass;
  hists[190] = TF_LW300_JetMass;
  //hists[37] = TF_LW400_JetMass;
  //hists[38] = TF_LW500_JetMass;
  hists[191] = TF_LW300_npv;
  //hists[40] = TF_LW400_npv;
  //hists[41] = TF_LW500_npv;
  hists[192] = TF_dataRunB_nsv;
  hists[193] = TF_dataRunC_nsv;
  hists[194] = TF_ZLL_nsv;
  hists[195] = TF_TT_nsv;
  hists[196] = TF_W3J_nsv;
  hists[197] = TF_W2J_nsv;
  hists[198] = TF_W1J_nsv;
  hists[199] = TF_WW_nsv;
  hists[200] = TF_WZ_nsv;
  hists[201] = TF_TTZ_nsv;
  hists[202] = TF_LW200_nsv;
  hists[203] = TF_LW200_nsv;
  //hists[40] = TF_LW400_nsv;
  //hists[41] = TF_LW500_nsv;
  hists[204] = TF_dataRunB_svd;
  hists[205] = TF_dataRunC_svd;
  hists[206] = TF_ZLL_svd;
  hists[207] = TF_TT_svd;
  hists[208] = TF_W3J_svd;
  hists[209] = TF_W2J_svd;
  hists[210] = TF_W1J_svd;
  hists[211] = TF_WW_svd;
  hists[212] = TF_WZ_svd;
  hists[213] = TF_TTZ_svd;
  hists[214] = TF_LW200_svd;
  hists[215] = TF_LW200_svd;
  //hists[40] = TF_LW400_svd;
  //hists[41] = TF_LW500_svd;
  hists[216] = TF_dataRunB_Elept;
  hists[217] = TF_dataRunC_Elept;
  hists[218] = TF_ZLL_Elept;
  hists[219] = TF_TT_Elept;
  hists[220] = TF_W3J_Elept;
  hists[221] = TF_W2J_Elept;
  hists[222] = TF_W1J_Elept;
  hists[223] = TF_WW_Elept;
  hists[224] = TF_WZ_Elept;
  hists[225] = TF_TTZ_Elept;
  hists[226] = TF_LW200_Elept;
  hists[227] = TF_LW200_Elept;
  //hists[40] = TF_LW400_svd;
  //hists[41] = TF_LW500_svd;
  hists[228] = TF_dataRunB_DieledR;
  hists[229] = TF_dataRunC_DieledR;
  hists[230] = TF_ZLL_DieledR;
  hists[231] = TF_TT_DieledR;
  hists[232] = TF_W3J_DieledR;
  hists[233] = TF_W2J_DieledR;
  hists[234] = TF_W1J_DieledR;
  hists[235] = TF_WW_DieledR;
  hists[236] = TF_WZ_DieledR;
  hists[237] = TF_TTZ_DieledR;
  hists[238] = TF_LW200_DieledR;
  hists[239] = TF_LW200_DieledR;
  //hists[40] = TF_LW400_svd;
  //hists[41] = TF_LW500_svd;
  hists[240] = TF_dataRunB_LWdR;
  hists[241] = TF_dataRunC_LWdR;
  hists[242] = TF_ZLL_LWdR;
  hists[243] = TF_TT_LWdR;
  hists[244] = TF_W3J_LWdR;
  hists[245] = TF_W2J_LWdR;
  hists[246] = TF_W1J_LWdR;
  hists[247] = TF_WW_LWdR;
  hists[248] = TF_WZ_LWdR;
  hists[249] = TF_TTZ_LWdR;
  hists[250] = TF_LW200_LWdR;
  hists[251] = TF_LW200_LWdR;
  //hists[40] = TF_LW400_svd;
  //hists[41] = TF_LW500_svd;
  hists[252] = TF_dataRunB_DiJetdR;
  hists[253] = TF_dataRunC_DiJetdR;
  hists[254] = TF_ZLL_DiJetdR;
  hists[255] = TF_TT_DiJetdR;
  hists[256] = TF_W3J_DiJetdR;
  hists[257] = TF_W2J_DiJetdR;
  hists[258] = TF_W1J_DiJetdR;
  hists[259] = TF_WW_DiJetdR;
  hists[260] = TF_WZ_DiJetdR;
  hists[261] = TF_TTZ_DiJetdR;
  hists[262] = TF_LW200_DiJetdR;
  hists[263] = TF_LW200_DiJetdR;
  //hists[40] = TF_LW400_svd;
  //hists[41] = TF_LW500_svd;
  hists[264] = TF_dataRunB_BJetPt;
  hists[265] = TF_dataRunC_BJetPt;
  hists[266] = TF_ZLL_BJetPt;
  hists[267] = TF_TT_BJetPt;
  hists[268] = TF_W3J_BJetPt;
  hists[269] = TF_W2J_BJetPt;
  hists[270] = TF_W1J_BJetPt;
  hists[271] = TF_WW_BJetPt;
  hists[272] = TF_WZ_BJetPt;
  hists[273] = TF_TTZ_BJetPt;
  hists[274] = TF_LW200_BJetPt;
  hists[275] = TF_LW200_BJetPt;
  //hists[40] = TF_LW400_svd;
  //hists[41] = TF_LW500_svd;
  hists[276] = TF_dataRunB_SBJetPt;
  hists[277] = TF_dataRunC_SBJetPt;
  hists[278] = TF_ZLL_SBJetPt;
  hists[279] = TF_TT_SBJetPt;
  hists[280] = TF_W3J_SBJetPt;
  hists[281] = TF_W2J_SBJetPt;
  hists[282] = TF_W1J_SBJetPt;
  hists[283] = TF_WW_SBJetPt;
  hists[284] = TF_WZ_SBJetPt;
  hists[285] = TF_TTZ_SBJetPt;
  hists[286] = TF_LW200_SBJetPt;
  hists[287] = TF_LW200_SBJetPt;
  //hists[40] = TF_LW400_svd;
  //hists[41] = TF_LW500_svd;
  hists[288] = TF_dataRunB_NJet;
  hists[289] = TF_dataRunC_NJet;
  hists[290] = TF_ZLL_NJet;
  hists[291] = TF_TT_NJet;
  hists[292] = TF_W3J_NJet;
  hists[293] = TF_W2J_NJet;
  hists[294] = TF_W1J_NJet;
  hists[295] = TF_WW_NJet;
  hists[296] = TF_WZ_NJet;
  hists[297] = TF_TTZ_NJet;
  hists[298] = TF_LW200_NJet;
  hists[299] = TF_LW200_NJet;
  //hists[40] = TF_LW400_svd;
  //hists[41] = TF_LW500_svd;
  hists[300] = TF_dataRunB_NEle;
  hists[301] = TF_dataRunC_NEle;
  hists[302] = TF_ZLL_NEle;
  hists[303] = TF_TT_NEle;
  hists[304] = TF_W3J_NEle;
  hists[305] = TF_W2J_NEle;
  hists[306] = TF_W1J_NEle;
  hists[307] = TF_WW_NEle;
  hists[308] = TF_WZ_NEle;
  hists[309] = TF_TTZ_NEle;
  hists[310] = TF_LW200_NEle;
  hists[311] = TF_LW200_NEle;
  //hists[40] = TF_LW400_svd;
  //hists[41] = TF_LW500_svd;

  hists[312] = TO_dataRunB_npv;
  hists[313] = TO_dataRunC_npv;
  hists[314] = TO_ZLL_npv;
  hists[315] = TO_TT_npv;
  hists[316] = TO_W3J_npv;
  hists[317] = TO_W2J_npv;
  hists[318] = TO_W1J_npv;
  hists[319] = TO_LW200_npv;
  hists[320] = TO_dataRunB_JetMass;
  hists[321] = TO_dataRunC_JetMass;
  hists[322] = TO_ZLL_JetMass;
  hists[323] = TO_TT_JetMass;
  hists[324] = TO_W3J_JetMass;
  hists[325] = TO_W2J_JetMass;
  hists[326] = TO_W1J_JetMass;
  hists[327] = TO_LW200_JetMass;
  hists[328] = TO_dataRunB_LWMass;
  hists[329] = TO_dataRunC_LWMass;
  hists[330] = TO_ZLL_LWMass;
  hists[331] = TO_TT_LWMass;
  hists[332] = TO_W3J_LWMass;
  hists[333] = TO_W2J_LWMass;
  hists[334] = TO_W1J_LWMass;
  hists[335] = TO_LW200_LWMass;
  hists[336] = TO_WW_npv;
  hists[337] = TO_WZ_npv;
  hists[338] = TO_TTZ_npv;
  hists[339] = TO_WW_JetMass;
  hists[340] = TO_WZ_JetMass;
  hists[341] = TO_TTZ_JetMass;
  hists[342] = TO_WW_LWMass;
  hists[343] = TO_WZ_LWMass;
  hists[344] = TO_TTZ_LWMass;
  hists[345] = TO_LW300_LWMass;
  //hists[34] = TO_LW400_LWMass;
  //hists[35] = TO_LW500_LWMass;
  hists[346] = TO_LW300_JetMass;
  //hists[37] = TO_LW400_JetMass;
  //hists[38] = TO_LW500_JetMass;
  hists[347] = TO_LW300_npv;
  //hists[40] = TO_LW400_npv;
  //hists[41] = TO_LW500_npv;
  hists[348] = TO_dataRunB_nsv;
  hists[349] = TO_dataRunC_nsv;
  hists[350] = TO_ZLL_nsv;
  hists[351] = TO_TT_nsv;
  hists[352] = TO_W3J_nsv;
  hists[353] = TO_W2J_nsv;
  hists[354] = TO_W1J_nsv;
  hists[355] = TO_WW_nsv;
  hists[356] = TO_WZ_nsv;
  hists[357] = TO_TTZ_nsv;
  hists[358] = TO_LW200_nsv;
  hists[359] = TO_LW200_nsv;
  //hists[40] = TO_LW400_nsv;
  //hists[41] = TO_LW500_nsv;
  hists[360] = TO_dataRunB_svd;
  hists[361] = TO_dataRunC_svd;
  hists[362] = TO_ZLL_svd;
  hists[363] = TO_TT_svd;
  hists[364] = TO_W3J_svd;
  hists[365] = TO_W2J_svd;
  hists[366] = TO_W1J_svd;
  hists[367] = TO_WW_svd;
  hists[368] = TO_WZ_svd;
  hists[369] = TO_TTZ_svd;
  hists[370] = TO_LW200_svd;
  hists[371] = TO_LW200_svd;
  //hists[40] = TO_LW400_svd;
  //hists[41] = TO_LW500_svd;
  hists[372] = TO_dataRunB_Elept;
  hists[373] = TO_dataRunC_Elept;
  hists[374] = TO_ZLL_Elept;
  hists[375] = TO_TT_Elept;
  hists[376] = TO_W3J_Elept;
  hists[377] = TO_W2J_Elept;
  hists[378] = TO_W1J_Elept;
  hists[379] = TO_WW_Elept;
  hists[380] = TO_WZ_Elept;
  hists[381] = TO_TTZ_Elept;
  hists[382] = TO_LW200_Elept;
  hists[383] = TO_LW200_Elept;
  //hists[40] = TO_LW400_svd;
  //hists[41] = TO_LW500_svd;
  hists[384] = TO_dataRunB_DieledR;
  hists[385] = TO_dataRunC_DieledR;
  hists[386] = TO_ZLL_DieledR;
  hists[387] = TO_TT_DieledR;
  hists[388] = TO_W3J_DieledR;
  hists[389] = TO_W2J_DieledR;
  hists[390] = TO_W1J_DieledR;
  hists[391] = TO_WW_DieledR;
  hists[392] = TO_WZ_DieledR;
  hists[393] = TO_TTZ_DieledR;
  hists[394] = TO_LW200_DieledR;
  hists[395] = TO_LW200_DieledR;
  //hists[40] = TO_LW400_svd;
  //hists[41] = TO_LW500_svd;
  hists[396] = TO_dataRunB_LWdR;
  hists[397] = TO_dataRunC_LWdR;
  hists[398] = TO_ZLL_LWdR;
  hists[399] = TO_TT_LWdR;
  hists[400] = TO_W3J_LWdR;
  hists[401] = TO_W2J_LWdR;
  hists[402] = TO_W1J_LWdR;
  hists[403] = TO_WW_LWdR;
  hists[404] = TO_WZ_LWdR;
  hists[405] = TO_TTZ_LWdR;
  hists[406] = TO_LW200_LWdR;
  hists[407] = TO_LW200_LWdR;
  //hists[40] = TO_LW400_svd;
  //hists[41] = TO_LW500_svd;
  hists[408] = TO_dataRunB_DiJetdR;
  hists[409] = TO_dataRunC_DiJetdR;
  hists[410] = TO_ZLL_DiJetdR;
  hists[411] = TO_TT_DiJetdR;
  hists[412] = TO_W3J_DiJetdR;
  hists[413] = TO_W2J_DiJetdR;
  hists[414] = TO_W1J_DiJetdR;
  hists[415] = TO_WW_DiJetdR;
  hists[416] = TO_WZ_DiJetdR;
  hists[417] = TO_TTZ_DiJetdR;
  hists[418] = TO_LW200_DiJetdR;
  hists[419] = TO_LW200_DiJetdR;
  //hists[40] = TO_LW400_svd;
  //hists[41] = TO_LW500_svd;
  hists[420] = TO_dataRunB_BJetPt;
  hists[421] = TO_dataRunC_BJetPt;
  hists[422] = TO_ZLL_BJetPt;
  hists[423] = TO_TT_BJetPt;
  hists[424] = TO_W3J_BJetPt;
  hists[425] = TO_W2J_BJetPt;
  hists[426] = TO_W1J_BJetPt;
  hists[427] = TO_WW_BJetPt;
  hists[428] = TO_WZ_BJetPt;
  hists[429] = TO_TTZ_BJetPt;
  hists[430] = TO_LW200_BJetPt;
  hists[431] = TO_LW200_BJetPt;
  //hists[40] = TO_LW400_svd;
  //hists[41] = TO_LW500_svd;
  hists[432] = TO_dataRunB_SBJetPt;
  hists[433] = TO_dataRunC_SBJetPt;
  hists[434] = TO_ZLL_SBJetPt;
  hists[435] = TO_TT_SBJetPt;
  hists[436] = TO_W3J_SBJetPt;
  hists[437] = TO_W2J_SBJetPt;
  hists[438] = TO_W1J_SBJetPt;
  hists[439] = TO_WW_SBJetPt;
  hists[440] = TO_WZ_SBJetPt;
  hists[441] = TO_TTZ_SBJetPt;
  hists[442] = TO_LW200_SBJetPt;
  hists[443] = TO_LW200_SBJetPt;
  //hists[40] = TO_LW400_svd;
  //hists[41] = TO_LW500_svd;
  hists[444] = TO_dataRunB_NJet;
  hists[445] = TO_dataRunC_NJet;
  hists[446] = TO_ZLL_NJet;
  hists[447] = TO_TT_NJet;
  hists[448] = TO_W3J_NJet;
  hists[449] = TO_W2J_NJet;
  hists[450] = TO_W1J_NJet;
  hists[451] = TO_WW_NJet;
  hists[452] = TO_WZ_NJet;
  hists[453] = TO_TTZ_NJet;
  hists[454] = TO_LW200_NJet;
  hists[455] = TO_LW200_NJet;
  //hists[40] = TO_LW400_svd;
  //hists[41] = TO_LW500_svd;
  hists[456] = TO_dataRunB_NEle;
  hists[457] = TO_dataRunC_NEle;
  hists[458] = TO_ZLL_NEle;
  hists[459] = TO_TT_NEle;
  hists[460] = TO_W3J_NEle;
  hists[461] = TO_W2J_NEle;
  hists[462] = TO_W1J_NEle;
  hists[463] = TO_WW_NEle;
  hists[464] = TO_WZ_NEle;
  hists[465] = TO_TTZ_NEle;
  hists[466] = TO_LW200_NEle;
  hists[467] = TO_LW200_NEle;
  //hists[40] = TO_LW400_svd;
  //hists[41] = TO_LW500_svd;

  hists[468] = HQ_dataRunB_npv;
  hists[469] = HQ_dataRunC_npv;
  hists[470] = HQ_ZLL_npv;
  hists[471] = HQ_TT_npv;
  hists[472] = HQ_W3J_npv;
  hists[473] = HQ_W2J_npv;
  hists[474] = HQ_W1J_npv;
  hists[475] = HQ_LW200_npv;
  hists[476] = HQ_dataRunB_JetMass;
  hists[477] = HQ_dataRunC_JetMass;
  hists[478] = HQ_ZLL_JetMass;
  hists[479] = HQ_TT_JetMass;
  hists[480] = HQ_W3J_JetMass;
  hists[481] = HQ_W2J_JetMass;
  hists[482] = HQ_W1J_JetMass;
  hists[483] = HQ_LW200_JetMass;
  hists[484] = HQ_dataRunB_LWMass;
  hists[485] = HQ_dataRunC_LWMass;
  hists[486] = HQ_ZLL_LWMass;
  hists[487] = HQ_TT_LWMass;
  hists[488] = HQ_W3J_LWMass;
  hists[489] = HQ_W2J_LWMass;
  hists[490] = HQ_W1J_LWMass;
  hists[491] = HQ_LW200_LWMass;
  hists[492] = HQ_WW_npv;
  hists[493] = HQ_WZ_npv;
  hists[494] = HQ_TTZ_npv;
  hists[495] = HQ_WW_JetMass;
  hists[496] = HQ_WZ_JetMass;
  hists[497] = HQ_TTZ_JetMass;
  hists[498] = HQ_WW_LWMass;
  hists[499] = HQ_WZ_LWMass;
  hists[500] = HQ_TTZ_LWMass;
  hists[501] = HQ_LW300_LWMass;
  //hists[34] = HQ_LW400_LWMass;
  //hists[35] = HQ_LW500_LWMass;
  hists[502] = HQ_LW300_JetMass;
  //hists[37] = HQ_LW400_JetMass;
  //hists[38] = HQ_LW500_JetMass;
  hists[503] = HQ_LW300_npv;
  //hists[40] = HQ_LW400_npv;
  //hists[41] = HQ_LW500_npv;
  hists[504] = HQ_dataRunB_nsv;
  hists[505] = HQ_dataRunC_nsv;
  hists[506] = HQ_ZLL_nsv;
  hists[507] = HQ_TT_nsv;
  hists[508] = HQ_W3J_nsv;
  hists[509] = HQ_W2J_nsv;
  hists[510] = HQ_W1J_nsv;
  hists[511] = HQ_WW_nsv;
  hists[512] = HQ_WZ_nsv;
  hists[513] = HQ_TTZ_nsv;
  hists[514] = HQ_LW200_nsv;
  hists[515] = HQ_LW200_nsv;
  //hists[40] = HQ_LW400_nsv;
  //hists[41] = HQ_LW500_nsv;
  hists[516] = HQ_dataRunB_svd;
  hists[517] = HQ_dataRunC_svd;
  hists[518] = HQ_ZLL_svd;
  hists[519] = HQ_TT_svd;
  hists[520] = HQ_W3J_svd;
  hists[521] = HQ_W2J_svd;
  hists[522] = HQ_W1J_svd;
  hists[523] = HQ_WW_svd;
  hists[524] = HQ_WZ_svd;
  hists[525] = HQ_TTZ_svd;
  hists[526] = HQ_LW200_svd;
  hists[527] = HQ_LW200_svd;
  //hists[40] = HQ_LW400_svd;
  //hists[41] = HQ_LW500_svd;
  hists[528] = HQ_dataRunB_Elept;
  hists[529] = HQ_dataRunC_Elept;
  hists[530] = HQ_ZLL_Elept;
  hists[531] = HQ_TT_Elept;
  hists[532] = HQ_W3J_Elept;
  hists[533] = HQ_W2J_Elept;
  hists[534] = HQ_W1J_Elept;
  hists[535] = HQ_WW_Elept;
  hists[536] = HQ_WZ_Elept;
  hists[537] = HQ_TTZ_Elept;
  hists[538] = HQ_LW200_Elept;
  hists[539] = HQ_LW200_Elept;
  //hists[40] = HQ_LW400_svd;
  //hists[41] = HQ_LW500_svd;
  hists[540] = HQ_dataRunB_DieledR;
  hists[541] = HQ_dataRunC_DieledR;
  hists[542] = HQ_ZLL_DieledR;
  hists[543] = HQ_TT_DieledR;
  hists[544] = HQ_W3J_DieledR;
  hists[545] = HQ_W2J_DieledR;
  hists[546] = HQ_W1J_DieledR;
  hists[547] = HQ_WW_DieledR;
  hists[548] = HQ_WZ_DieledR;
  hists[549] = HQ_TTZ_DieledR;
  hists[550] = HQ_LW200_DieledR;
  hists[551] = HQ_LW200_DieledR;
  //hists[40] = HQ_LW400_svd;
  //hists[41] = HQ_LW500_svd;
  hists[552] = HQ_dataRunB_LWdR;
  hists[553] = HQ_dataRunC_LWdR;
  hists[554] = HQ_ZLL_LWdR;
  hists[555] = HQ_TT_LWdR;
  hists[556] = HQ_W3J_LWdR;
  hists[557] = HQ_W2J_LWdR;
  hists[558] = HQ_W1J_LWdR;
  hists[559] = HQ_WW_LWdR;
  hists[560] = HQ_WZ_LWdR;
  hists[561] = HQ_TTZ_LWdR;
  hists[562] = HQ_LW200_LWdR;
  hists[563] = HQ_LW200_LWdR;
  //hists[40] = HQ_LW400_svd;
  //hists[41] = HQ_LW500_svd;
  hists[564] = HQ_dataRunB_DiJetdR;
  hists[565] = HQ_dataRunC_DiJetdR;
  hists[566] = HQ_ZLL_DiJetdR;
  hists[567] = HQ_TT_DiJetdR;
  hists[568] = HQ_W3J_DiJetdR;
  hists[569] = HQ_W2J_DiJetdR;
  hists[570] = HQ_W1J_DiJetdR;
  hists[571] = HQ_WW_DiJetdR;
  hists[572] = HQ_WZ_DiJetdR;
  hists[573] = HQ_TTZ_DiJetdR;
  hists[574] = HQ_LW200_DiJetdR;
  hists[575] = HQ_LW200_DiJetdR;
  //hists[40] = HQ_LW400_svd;
  //hists[41] = HQ_LW500_svd;
  hists[576] = HQ_dataRunB_BJetPt;
  hists[577] = HQ_dataRunC_BJetPt;
  hists[578] = HQ_ZLL_BJetPt;
  hists[579] = HQ_TT_BJetPt;
  hists[580] = HQ_W3J_BJetPt;
  hists[581] = HQ_W2J_BJetPt;
  hists[582] = HQ_W1J_BJetPt;
  hists[583] = HQ_WW_BJetPt;
  hists[584] = HQ_WZ_BJetPt;
  hists[585] = HQ_TTZ_BJetPt;
  hists[586] = HQ_LW200_BJetPt;
  hists[587] = HQ_LW200_BJetPt;
  //hists[40] = HQ_LW400_svd;
  //hists[41] = HQ_LW500_svd;
  hists[588] = HQ_dataRunB_SBJetPt;
  hists[589] = HQ_dataRunC_SBJetPt;
  hists[590] = HQ_ZLL_SBJetPt;
  hists[591] = HQ_TT_SBJetPt;
  hists[592] = HQ_W3J_SBJetPt;
  hists[593] = HQ_W2J_SBJetPt;
  hists[594] = HQ_W1J_SBJetPt;
  hists[595] = HQ_WW_SBJetPt;
  hists[596] = HQ_WZ_SBJetPt;
  hists[597] = HQ_TTZ_SBJetPt;
  hists[598] = HQ_LW200_SBJetPt;
  hists[599] = HQ_LW200_SBJetPt;
  //hists[40] = HQ_LW400_svd;
  //hists[41] = HQ_LW500_svd;
  hists[600] = HQ_dataRunB_NJet;
  hists[601] = HQ_dataRunC_NJet;
  hists[602] = HQ_ZLL_NJet;
  hists[603] = HQ_TT_NJet;
  hists[604] = HQ_W3J_NJet;
  hists[605] = HQ_W2J_NJet;
  hists[606] = HQ_W1J_NJet;
  hists[607] = HQ_WW_NJet;
  hists[608] = HQ_WZ_NJet;
  hists[609] = HQ_TTZ_NJet;
  hists[610] = HQ_LW200_NJet;
  hists[611] = HQ_LW200_NJet;
  //hists[40] = HQ_LW400_svd;
  //hists[41] = HQ_LW500_svd;
  hists[612] = HQ_dataRunB_NEle;
  hists[613] = HQ_dataRunC_NEle;
  hists[614] = HQ_ZLL_NEle;
  hists[615] = HQ_TT_NEle;
  hists[616] = HQ_W3J_NEle;
  hists[617] = HQ_W2J_NEle;
  hists[618] = HQ_W1J_NEle;
  hists[619] = HQ_WW_NEle;
  hists[620] = HQ_WZ_NEle;
  hists[621] = HQ_TTZ_NEle;
  hists[622] = HQ_LW200_NEle;
  hists[623] = HQ_LW200_NEle;
  //hists[40] = HQ_LW400_svd;
  //hists[41] = HQ_LW500_svd;


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
  for (Int_t j=0;j<histsize;++j){
    TString histname = TString(hists[j]->GetName());
    TString thecut = histname(0,histname.First("_"));
    histname = histname(histname.First("_")+1,histname.Sizeof());
    TString thelabel = histname(0,histname.First("_"));
    TString thevar = histname(histname.First("_")+1,histname.Sizeof());

    if (thecut == cut && thelabel == labeltag){

      //primary vertices
      //cout<<"npv\n";
      if(thevar == "npv"){
	       hists[j]->Fill(PV_npvs,theweight);
      }

      /*//secondary Vertices
      //cout<<"nsv\n";
      if(thevar == "nsv"){
	       hists[j]->Fill(numbersecvec,theweight);
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
          hists[j]->Fill(disp,theweight);
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

              hists[j]->Fill(m,theweight);
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

                hists[j]->Fill(m,theweight);
              }
            }
          }
        }
      }
      //cout<<"Elept\n";
      if(thevar == "Elept"){
        for(size_t l=0; l < electron_e->size(); l++){
          hists[j]->Fill(electron_pt->at(l),theweight);
        }
      }
      //cout<<"DieledR\n";
      if(thevar == "DieledR"){
        for(size_t l=0; l < electron_e->size(); l++){
          for(size_t k=l+1; k < electron_e->size(); k++){
            float dieledR= deltaR(electron_eta->at(l),electron_phi->at(l),electron_eta->at(k),electron_phi->at(k));
            hists[j]->Fill(dieledR,theweight);
          }
        }
      }
      //cout<<"LWdR\n";
      if(thevar == "LWdR"){
        for(size_t l=0; l < electron_e->size(); l++){
          for(size_t k=0; k < jet_e->size(); k++){
            float LWdR= deltaR(electron_eta->at(l),electron_phi->at(l),jet_eta->at(k),jet_phi->at(k));
            hists[j]->Fill(LWdR,theweight);
          }
        }
      }
      //cout<<"DiJetdR\n";
      if(thevar == "DiJetdR"){
        for(size_t l=0; l < jet_e->size(); l++){
          for(size_t k=l+1; k < jet_e->size(); k++){
            float DiJetdR= deltaR(jet_eta->at(l),jet_phi->at(l),jet_eta->at(k),jet_phi->at(k));
            hists[j]->Fill(DiJetdR,theweight);
          }
        }
      }
      sort(corr_jet_pt->begin(),corr_jet_pt->begin());
      //cout<<"BJetPt\n";
      if(thevar == "BJetPt"){

        if(corr_jet_pt->size()>0) hists[j]->Fill(corr_jet_pt->at(0),theweight);

      }
      //cout<<"SBJetPT\n";
      if(thevar == "SBJetPt"){
        if(corr_jet_pt->size()>1)hists[j]->Fill(corr_jet_pt->at(1),theweight);
      }
      //cout<<"NJet\n";
      if(thevar == "NJet"){
        hists[j]->Fill(jet_e->size(),theweight);
      }
      //cout<<"NEle\n";
      if(thevar == "NEle"){
        hists[j]->Fill(electron_e->size(),theweight);
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
  const float LW300_w = 0.00096 / 150000 * integratedLuminosity;
  //const float LW400_w = 0.00023 / 150000 * integratedLuminosity;
  //const float LW500_w = 0.00006 / 150000 * integratedLuminosity;
  const float WW_w = 5.824 / 1933120 * integratedLuminosity;
  const float WZ_w = 2.207 / 3215990 * integratedLuminosity;
  const float TTZ_w = 0.175 / 787495 * integratedLuminosity;
  const float dataRunB_w = 1.0;
  const float dataRunC_w = 1.0;


  map<string, pair<string,float> > sampleNames;
  sampleNames.insert(make_pair("WWJetsTo2L2Nu",make_pair("WW",WW_w)));
  sampleNames.insert(make_pair("WZJetsTo2L2Q",make_pair("WZ",WZ_w)));
  sampleNames.insert(make_pair("ttbarZ",make_pair("TTZ",TTZ_w)));
  sampleNames.insert(make_pair("W1JetsToLNu",make_pair("W1J",W1J_w)));
  sampleNames.insert(make_pair("W2JetsToLNu",make_pair("W2J",W2J_w)));
  sampleNames.insert(make_pair("W3JetsToLNu",make_pair("W3J",W3J_w)));
  sampleNames.insert(make_pair("TTbar",make_pair("TT",TT_w)));
  sampleNames.insert(make_pair("DYJetsToLL",make_pair("ZLL",ZLL_w)));
  sampleNames.insert(make_pair("LWSM200DnR",make_pair("LW200",LW200_w)));
  sampleNames.insert(make_pair("LWSM300DnR",make_pair("LW300",LW300_w)));
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
  NF_WW_npv->Write();
  NF_WZ_npv->Write();
  NF_TTZ_npv->Write();
  NF_LW200_npv->Write();
  NF_LW300_npv->Write();
  //NF_LW400_npv->Write();
  //NF_LW500_npv->Write();
  NF_dataRunB_JetMass->Write();
  NF_dataRunC_JetMass->Write();
  NF_ZLL_JetMass->Write();
  NF_TT_JetMass->Write();
  NF_W3J_JetMass->Write();
  NF_W2J_JetMass->Write();
  NF_W1J_JetMass->Write();
  NF_WW_JetMass->Write();
  NF_WZ_JetMass->Write();
  NF_TTZ_JetMass->Write();
  NF_LW200_JetMass->Write();
  NF_LW300_JetMass->Write();
  //NF_LW400_JetMass->Write();
  //NF_LW500_JetMass->Write();
  NF_dataRunB_LWMass->Write();
  NF_dataRunC_LWMass->Write();
  NF_ZLL_LWMass->Write();
  NF_TT_LWMass->Write();
  NF_W3J_LWMass->Write();
  NF_W2J_LWMass->Write();
  NF_W1J_LWMass->Write();
  NF_WW_LWMass->Write();
  NF_WZ_LWMass->Write();
  NF_TTZ_LWMass->Write();
  NF_LW200_LWMass->Write();
  NF_LW300_LWMass->Write();
  //NF_LW400_LWMass->Write();
  //NF_LW500_LWMass->Write();
  NF_dataRunB_nsv->Write();
  NF_dataRunC_nsv->Write();
  NF_ZLL_nsv->Write();
  NF_TT_nsv->Write();
  NF_W3J_nsv->Write();
  NF_W2J_nsv->Write();
  NF_W1J_nsv->Write();
  NF_WW_nsv->Write();
  NF_WZ_nsv->Write();
  NF_TTZ_nsv->Write();
  NF_LW200_nsv->Write();
  NF_LW300_nsv->Write();
  //NF_LW400_nsv->Write();
  //NF_LW500_nsv->Write();
  NF_dataRunB_svd->Write();
  NF_dataRunC_svd->Write();
  NF_ZLL_svd->Write();
  NF_TT_svd->Write();
  NF_W3J_svd->Write();
  NF_W2J_svd->Write();
  NF_W1J_svd->Write();
  NF_WW_svd->Write();
  NF_WZ_svd->Write();
  NF_TTZ_svd->Write();
  NF_LW200_svd->Write();
  NF_LW300_svd->Write();
  //NF_LW400_svd->Write();
  //NF_LW500_svd->Write();
  NF_dataRunB_Elept->Write();
  NF_dataRunC_Elept->Write();
  NF_ZLL_Elept->Write();
  NF_TT_Elept->Write();
  NF_W3J_Elept->Write();
  NF_W2J_Elept->Write();
  NF_W1J_Elept->Write();
  NF_WW_Elept->Write();
  NF_WZ_Elept->Write();
  NF_TTZ_Elept->Write();
  NF_LW200_Elept->Write();
  NF_LW300_Elept->Write();
  //NF_LW400_Elept->Write();
  //NF_LW500_Elept->Write();
  NF_dataRunB_DieledR->Write();
  NF_dataRunC_DieledR->Write();
  NF_ZLL_DieledR->Write();
  NF_TT_DieledR->Write();
  NF_W3J_DieledR->Write();
  NF_W2J_DieledR->Write();
  NF_W1J_DieledR->Write();
  NF_WW_DieledR->Write();
  NF_WZ_DieledR->Write();
  NF_TTZ_DieledR->Write();
  NF_LW200_DieledR->Write();
  NF_LW300_DieledR->Write();
  //NF_LW400_DieledR->Write();
  //NF_LW500_DieledR->Write();
  NF_dataRunB_LWdR->Write();
  NF_dataRunC_LWdR->Write();
  NF_ZLL_LWdR->Write();
  NF_TT_LWdR->Write();
  NF_W3J_LWdR->Write();
  NF_W2J_LWdR->Write();
  NF_W1J_LWdR->Write();
  NF_WW_LWdR->Write();
  NF_WZ_LWdR->Write();
  NF_TTZ_LWdR->Write();
  NF_LW200_LWdR->Write();
  NF_LW300_LWdR->Write();
  //NF_LW400_LWdR->Write();
  //NF_LW500_LWdR->Write();
  NF_dataRunB_DiJetdR->Write();
  NF_dataRunC_DiJetdR->Write();
  NF_ZLL_DiJetdR->Write();
  NF_TT_DiJetdR->Write();
  NF_W3J_DiJetdR->Write();
  NF_W2J_DiJetdR->Write();
  NF_W1J_DiJetdR->Write();
  NF_WW_DiJetdR->Write();
  NF_WZ_DiJetdR->Write();
  NF_TTZ_DiJetdR->Write();
  NF_LW200_DiJetdR->Write();
  NF_LW300_DiJetdR->Write();
  //NF_LW400_DiJetdR->Write();
  //NF_LW500_DiJetdR->Write();
  NF_dataRunB_BJetPt->Write();
  NF_dataRunC_BJetPt->Write();
  NF_ZLL_BJetPt->Write();
  NF_TT_BJetPt->Write();
  NF_W3J_BJetPt->Write();
  NF_W2J_BJetPt->Write();
  NF_W1J_BJetPt->Write();
  NF_WW_BJetPt->Write();
  NF_WZ_BJetPt->Write();
  NF_TTZ_BJetPt->Write();
  NF_LW200_BJetPt->Write();
  NF_LW300_BJetPt->Write();
  //NF_LW400_BJetPt->Write();
  //NF_LW500_BJetPt->Write();
  NF_dataRunB_SBJetPt->Write();
  NF_dataRunC_SBJetPt->Write();
  NF_ZLL_SBJetPt->Write();
  NF_TT_SBJetPt->Write();
  NF_W3J_SBJetPt->Write();
  NF_W2J_SBJetPt->Write();
  NF_W1J_SBJetPt->Write();
  NF_WW_SBJetPt->Write();
  NF_WZ_SBJetPt->Write();
  NF_TTZ_SBJetPt->Write();
  NF_LW200_SBJetPt->Write();
  NF_LW300_SBJetPt->Write();
  //NF_LW400_SBJetPt->Write();
  //NF_LW500_SBJetPt->Write();
  NF_dataRunB_NJet->Write();
  NF_dataRunC_NJet->Write();
  NF_ZLL_NJet->Write();
  NF_TT_NJet->Write();
  NF_W3J_NJet->Write();
  NF_W2J_NJet->Write();
  NF_W1J_NJet->Write();
  NF_WW_NJet->Write();
  NF_WZ_NJet->Write();
  NF_TTZ_NJet->Write();
  NF_LW200_NJet->Write();
  NF_LW300_NJet->Write();
  //NF_LW400_NJet->Write();
  //NF_LW500_NJet->Write();
  NF_dataRunB_NEle->Write();
  NF_dataRunC_NEle->Write();
  NF_ZLL_NEle->Write();
  NF_TT_NEle->Write();
  NF_W3J_NEle->Write();
  NF_W2J_NEle->Write();
  NF_W1J_NEle->Write();
  NF_WW_NEle->Write();
  NF_WZ_NEle->Write();
  NF_TTZ_NEle->Write();
  NF_LW200_NEle->Write();
  NF_LW300_NEle->Write();
  //NF_LW400_NEle->Write();
  //NF_LW500_NEle->Write();

  TF_dataRunB_npv->Write();
  TF_dataRunC_npv->Write();
  TF_ZLL_npv->Write();
  TF_TT_npv->Write();
  TF_W3J_npv->Write();
  TF_W2J_npv->Write();
  TF_W1J_npv->Write();
  TF_WW_npv->Write();
  TF_WZ_npv->Write();
  TF_TTZ_npv->Write();
  TF_LW200_npv->Write();
  TF_LW300_npv->Write();
  //TF_LW400_npv->Write();
  //TF_LW500_npv->Write();
  TF_dataRunB_JetMass->Write();
  TF_dataRunC_JetMass->Write();
  TF_ZLL_JetMass->Write();
  TF_TT_JetMass->Write();
  TF_W3J_JetMass->Write();
  TF_W2J_JetMass->Write();
  TF_W1J_JetMass->Write();
  TF_WW_JetMass->Write();
  TF_WZ_JetMass->Write();
  TF_TTZ_JetMass->Write();
  TF_LW200_JetMass->Write();
  TF_LW300_JetMass->Write();
  //TF_LW400_JetMass->Write();
  //TF_LW500_JetMass->Write();
  TF_dataRunB_LWMass->Write();
  TF_dataRunC_LWMass->Write();
  TF_ZLL_LWMass->Write();
  TF_TT_LWMass->Write();
  TF_W3J_LWMass->Write();
  TF_W2J_LWMass->Write();
  TF_W1J_LWMass->Write();
  TF_WW_LWMass->Write();
  TF_WZ_LWMass->Write();
  TF_TTZ_LWMass->Write();
  TF_LW200_LWMass->Write();
  TF_LW300_LWMass->Write();
  //TF_LW400_LWMass->Write();
  //TF_LW500_LWMass->Write();
  TF_dataRunB_nsv->Write();
  TF_dataRunC_nsv->Write();
  TF_ZLL_nsv->Write();
  TF_TT_nsv->Write();
  TF_W3J_nsv->Write();
  TF_W2J_nsv->Write();
  TF_W1J_nsv->Write();
  TF_WW_nsv->Write();
  TF_WZ_nsv->Write();
  TF_TTZ_nsv->Write();
  TF_LW200_nsv->Write();
  TF_LW300_nsv->Write();
  //TF_LW400_nsv->Write();
  //TF_LW500_nsv->Write();
  TF_dataRunB_svd->Write();
  TF_dataRunC_svd->Write();
  TF_ZLL_svd->Write();
  TF_TT_svd->Write();
  TF_W3J_svd->Write();
  TF_W2J_svd->Write();
  TF_W1J_svd->Write();
  TF_WW_svd->Write();
  TF_WZ_svd->Write();
  TF_TTZ_svd->Write();
  TF_LW200_svd->Write();
  TF_LW300_svd->Write();
  //TF_LW400_svd->Write();
  //TF_LW500_svd->Write();
  TF_dataRunB_Elept->Write();
  TF_dataRunC_Elept->Write();
  TF_ZLL_Elept->Write();
  TF_TT_Elept->Write();
  TF_W3J_Elept->Write();
  TF_W2J_Elept->Write();
  TF_W1J_Elept->Write();
  TF_WW_Elept->Write();
  TF_WZ_Elept->Write();
  TF_TTZ_Elept->Write();
  TF_LW200_Elept->Write();
  TF_LW300_Elept->Write();
  //TF_LW400_Elept->Write();
  //TF_LW500_Elept->Write();
  TF_dataRunB_DieledR->Write();
  TF_dataRunC_DieledR->Write();
  TF_ZLL_DieledR->Write();
  TF_TT_DieledR->Write();
  TF_W3J_DieledR->Write();
  TF_W2J_DieledR->Write();
  TF_W1J_DieledR->Write();
  TF_WW_DieledR->Write();
  TF_WZ_DieledR->Write();
  TF_TTZ_DieledR->Write();
  TF_LW200_DieledR->Write();
  TF_LW300_DieledR->Write();
  //TF_LW400_DieledR->Write();
  //TF_LW500_DieledR->Write();
  TF_dataRunB_LWdR->Write();
  TF_dataRunC_LWdR->Write();
  TF_ZLL_LWdR->Write();
  TF_TT_LWdR->Write();
  TF_W3J_LWdR->Write();
  TF_W2J_LWdR->Write();
  TF_W1J_LWdR->Write();
  TF_WW_LWdR->Write();
  TF_WZ_LWdR->Write();
  TF_TTZ_LWdR->Write();
  TF_LW200_LWdR->Write();
  TF_LW300_LWdR->Write();
  //TF_LW400_LWdR->Write();
  //TF_LW500_LWdR->Write();
  TF_dataRunB_DiJetdR->Write();
  TF_dataRunC_DiJetdR->Write();
  TF_ZLL_DiJetdR->Write();
  TF_TT_DiJetdR->Write();
  TF_W3J_DiJetdR->Write();
  TF_W2J_DiJetdR->Write();
  TF_W1J_DiJetdR->Write();
  TF_WW_DiJetdR->Write();
  TF_WZ_DiJetdR->Write();
  TF_TTZ_DiJetdR->Write();
  TF_LW200_DiJetdR->Write();
  TF_LW300_DiJetdR->Write();
  //TF_LW400_DiJetdR->Write();
  //TF_LW500_DiJetdR->Write();
  TF_dataRunB_BJetPt->Write();
  TF_dataRunC_BJetPt->Write();
  TF_ZLL_BJetPt->Write();
  TF_TT_BJetPt->Write();
  TF_W3J_BJetPt->Write();
  TF_W2J_BJetPt->Write();
  TF_W1J_BJetPt->Write();
  TF_WW_BJetPt->Write();
  TF_WZ_BJetPt->Write();
  TF_TTZ_BJetPt->Write();
  TF_LW200_BJetPt->Write();
  TF_LW300_BJetPt->Write();
  //TF_LW400_BJetPt->Write();
  //TF_LW500_BJetPt->Write();
  TF_dataRunB_SBJetPt->Write();
  TF_dataRunC_SBJetPt->Write();
  TF_ZLL_SBJetPt->Write();
  TF_TT_SBJetPt->Write();
  TF_W3J_SBJetPt->Write();
  TF_W2J_SBJetPt->Write();
  TF_W1J_SBJetPt->Write();
  TF_WW_SBJetPt->Write();
  TF_WZ_SBJetPt->Write();
  TF_TTZ_SBJetPt->Write();
  TF_LW200_SBJetPt->Write();
  TF_LW300_SBJetPt->Write();
  //TF_LW400_SBJetPt->Write();
  //TF_LW500_SBJetPt->Write();
  TF_dataRunB_NJet->Write();
  TF_dataRunC_NJet->Write();
  TF_ZLL_NJet->Write();
  TF_TT_NJet->Write();
  TF_W3J_NJet->Write();
  TF_W2J_NJet->Write();
  TF_W1J_NJet->Write();
  TF_WW_NJet->Write();
  TF_WZ_NJet->Write();
  TF_TTZ_NJet->Write();
  TF_LW200_NJet->Write();
  TF_LW300_NJet->Write();
  //TF_LW400_NJet->Write();
  //TF_LW500_NJet->Write();
  TF_dataRunB_NEle->Write();
  TF_dataRunC_NEle->Write();
  TF_ZLL_NEle->Write();
  TF_TT_NEle->Write();
  TF_W3J_NEle->Write();
  TF_W2J_NEle->Write();
  TF_W1J_NEle->Write();
  TF_WW_NEle->Write();
  TF_WZ_NEle->Write();
  TF_TTZ_NEle->Write();
  TF_LW200_NEle->Write();
  TF_LW300_NEle->Write();
  //TF_LW400_NEle->Write();
  //TF_LW500_NEle->Write();

  TO_dataRunB_npv->Write();
  TO_dataRunC_npv->Write();
  TO_ZLL_npv->Write();
  TO_TT_npv->Write();
  TO_W3J_npv->Write();
  TO_W2J_npv->Write();
  TO_W1J_npv->Write();
  TO_WW_npv->Write();
  TO_WZ_npv->Write();
  TO_TTZ_npv->Write();
  TO_LW200_npv->Write();
  TO_LW300_npv->Write();
  //TO_LW400_npv->Write();
  //TO_LW500_npv->Write();
  TO_dataRunB_JetMass->Write();
  TO_dataRunC_JetMass->Write();
  TO_ZLL_JetMass->Write();
  TO_TT_JetMass->Write();
  TO_W3J_JetMass->Write();
  TO_W2J_JetMass->Write();
  TO_W1J_JetMass->Write();
  TO_WW_JetMass->Write();
  TO_WZ_JetMass->Write();
  TO_TTZ_JetMass->Write();
  TO_LW200_JetMass->Write();
  TO_LW300_JetMass->Write();
  //TO_LW400_JetMass->Write();
  //TO_LW500_JetMass->Write();
  TO_dataRunB_LWMass->Write();
  TO_dataRunC_LWMass->Write();
  TO_ZLL_LWMass->Write();
  TO_TT_LWMass->Write();
  TO_W3J_LWMass->Write();
  TO_W2J_LWMass->Write();
  TO_W1J_LWMass->Write();
  TO_WW_LWMass->Write();
  TO_WZ_LWMass->Write();
  TO_TTZ_LWMass->Write();
  TO_LW200_LWMass->Write();
  TO_LW300_LWMass->Write();
  //TO_LW400_LWMass->Write();
  //TO_LW500_LWMass->Write();
  TO_dataRunB_nsv->Write();
  TO_dataRunC_nsv->Write();
  TO_ZLL_nsv->Write();
  TO_TT_nsv->Write();
  TO_W3J_nsv->Write();
  TO_W2J_nsv->Write();
  TO_W1J_nsv->Write();
  TO_WW_nsv->Write();
  TO_WZ_nsv->Write();
  TO_TTZ_nsv->Write();
  TO_LW200_nsv->Write();
  TO_LW300_nsv->Write();
  //TO_LW400_nsv->Write();
  //TO_LW500_nsv->Write();
  TO_dataRunB_svd->Write();
  TO_dataRunC_svd->Write();
  TO_ZLL_svd->Write();
  TO_TT_svd->Write();
  TO_W3J_svd->Write();
  TO_W2J_svd->Write();
  TO_W1J_svd->Write();
  TO_WW_svd->Write();
  TO_WZ_svd->Write();
  TO_TTZ_svd->Write();
  TO_LW200_svd->Write();
  TO_LW300_svd->Write();
  //TO_LW400_svd->Write();
  //TO_LW500_svd->Write();
  TO_dataRunB_Elept->Write();
  TO_dataRunC_Elept->Write();
  TO_ZLL_Elept->Write();
  TO_TT_Elept->Write();
  TO_W3J_Elept->Write();
  TO_W2J_Elept->Write();
  TO_W1J_Elept->Write();
  TO_WW_Elept->Write();
  TO_WZ_Elept->Write();
  TO_TTZ_Elept->Write();
  TO_LW200_Elept->Write();
  TO_LW300_Elept->Write();
  //TO_LW400_Elept->Write();
  //TO_LW500_Elept->Write();
  TO_dataRunB_DieledR->Write();
  TO_dataRunC_DieledR->Write();
  TO_ZLL_DieledR->Write();
  TO_TT_DieledR->Write();
  TO_W3J_DieledR->Write();
  TO_W2J_DieledR->Write();
  TO_W1J_DieledR->Write();
  TO_WW_DieledR->Write();
  TO_WZ_DieledR->Write();
  TO_TTZ_DieledR->Write();
  TO_LW200_DieledR->Write();
  TO_LW300_DieledR->Write();
  //TO_LW400_DieledR->Write();
  //TO_LW500_DieledR->Write();
  TO_dataRunB_LWdR->Write();
  TO_dataRunC_LWdR->Write();
  TO_ZLL_LWdR->Write();
  TO_TT_LWdR->Write();
  TO_W3J_LWdR->Write();
  TO_W2J_LWdR->Write();
  TO_W1J_LWdR->Write();
  TO_WW_LWdR->Write();
  TO_WZ_LWdR->Write();
  TO_TTZ_LWdR->Write();
  TO_LW200_LWdR->Write();
  TO_LW300_LWdR->Write();
  //TO_LW400_LWdR->Write();
  //TO_LW500_LWdR->Write();
  TO_dataRunB_DiJetdR->Write();
  TO_dataRunC_DiJetdR->Write();
  TO_ZLL_DiJetdR->Write();
  TO_TT_DiJetdR->Write();
  TO_W3J_DiJetdR->Write();
  TO_W2J_DiJetdR->Write();
  TO_W1J_DiJetdR->Write();
  TO_WW_DiJetdR->Write();
  TO_WZ_DiJetdR->Write();
  TO_TTZ_DiJetdR->Write();
  TO_LW200_DiJetdR->Write();
  TO_LW300_DiJetdR->Write();
  //TO_LW400_DiJetdR->Write();
  //TO_LW500_DiJetdR->Write();
  TO_dataRunB_BJetPt->Write();
  TO_dataRunC_BJetPt->Write();
  TO_ZLL_BJetPt->Write();
  TO_TT_BJetPt->Write();
  TO_W3J_BJetPt->Write();
  TO_W2J_BJetPt->Write();
  TO_W1J_BJetPt->Write();
  TO_WW_BJetPt->Write();
  TO_WZ_BJetPt->Write();
  TO_TTZ_BJetPt->Write();
  TO_LW200_BJetPt->Write();
  TO_LW300_BJetPt->Write();
  //TO_LW400_BJetPt->Write();
  //TO_LW500_BJetPt->Write();
  TO_dataRunB_SBJetPt->Write();
  TO_dataRunC_SBJetPt->Write();
  TO_ZLL_SBJetPt->Write();
  TO_TT_SBJetPt->Write();
  TO_W3J_SBJetPt->Write();
  TO_W2J_SBJetPt->Write();
  TO_W1J_SBJetPt->Write();
  TO_WW_SBJetPt->Write();
  TO_WZ_SBJetPt->Write();
  TO_TTZ_SBJetPt->Write();
  TO_LW200_SBJetPt->Write();
  TO_LW300_SBJetPt->Write();
  //TO_LW400_SBJetPt->Write();
  //TO_LW500_SBJetPt->Write();
  TO_dataRunB_NJet->Write();
  TO_dataRunC_NJet->Write();
  TO_ZLL_NJet->Write();
  TO_TT_NJet->Write();
  TO_W3J_NJet->Write();
  TO_W2J_NJet->Write();
  TO_W1J_NJet->Write();
  TO_WW_NJet->Write();
  TO_WZ_NJet->Write();
  TO_TTZ_NJet->Write();
  TO_LW200_NJet->Write();
  TO_LW300_NJet->Write();
  //TO_LW400_NJet->Write();
  //TO_LW500_NJet->Write();
  TO_dataRunB_NEle->Write();
  TO_dataRunC_NEle->Write();
  TO_ZLL_NEle->Write();
  TO_TT_NEle->Write();
  TO_W3J_NEle->Write();
  TO_W2J_NEle->Write();
  TO_W1J_NEle->Write();
  TO_WW_NEle->Write();
  TO_WZ_NEle->Write();
  TO_TTZ_NEle->Write();
  TO_LW200_NEle->Write();
  TO_LW300_NEle->Write();
  //TO_LW400_NEle->Write();
  //TO_LW500_NEle->Write();

  HQ_dataRunB_npv->Write();
  HQ_dataRunC_npv->Write();
  HQ_ZLL_npv->Write();
  HQ_TT_npv->Write();
  HQ_W3J_npv->Write();
  HQ_W2J_npv->Write();
  HQ_W1J_npv->Write();
  HQ_WW_npv->Write();
  HQ_WZ_npv->Write();
  HQ_TTZ_npv->Write();
  HQ_LW200_npv->Write();
  HQ_LW300_npv->Write();
  //HQ_LW400_npv->Write();
  //HQ_LW500_npv->Write();
  HQ_dataRunB_JetMass->Write();
  HQ_dataRunC_JetMass->Write();
  HQ_ZLL_JetMass->Write();
  HQ_TT_JetMass->Write();
  HQ_W3J_JetMass->Write();
  HQ_W2J_JetMass->Write();
  HQ_W1J_JetMass->Write();
  HQ_WW_JetMass->Write();
  HQ_WZ_JetMass->Write();
  HQ_TTZ_JetMass->Write();
  HQ_LW200_JetMass->Write();
  HQ_LW300_JetMass->Write();
  //HQ_LW400_JetMass->Write();
  //HQ_LW500_JetMass->Write();
  HQ_dataRunB_LWMass->Write();
  HQ_dataRunC_LWMass->Write();
  HQ_ZLL_LWMass->Write();
  HQ_TT_LWMass->Write();
  HQ_W3J_LWMass->Write();
  HQ_W2J_LWMass->Write();
  HQ_W1J_LWMass->Write();
  HQ_WW_LWMass->Write();
  HQ_WZ_LWMass->Write();
  HQ_TTZ_LWMass->Write();
  HQ_LW200_LWMass->Write();
  HQ_LW300_LWMass->Write();
  //HQ_LW400_LWMass->Write();
  //HQ_LW500_LWMass->Write();
  HQ_dataRunB_nsv->Write();
  HQ_dataRunC_nsv->Write();
  HQ_ZLL_nsv->Write();
  HQ_TT_nsv->Write();
  HQ_W3J_nsv->Write();
  HQ_W2J_nsv->Write();
  HQ_W1J_nsv->Write();
  HQ_WW_nsv->Write();
  HQ_WZ_nsv->Write();
  HQ_TTZ_nsv->Write();
  HQ_LW200_nsv->Write();
  HQ_LW300_nsv->Write();
  //HQ_LW400_nsv->Write();
  //HQ_LW500_nsv->Write();
  HQ_dataRunB_svd->Write();
  HQ_dataRunC_svd->Write();
  HQ_ZLL_svd->Write();
  HQ_TT_svd->Write();
  HQ_W3J_svd->Write();
  HQ_W2J_svd->Write();
  HQ_W1J_svd->Write();
  HQ_WW_svd->Write();
  HQ_WZ_svd->Write();
  HQ_TTZ_svd->Write();
  HQ_LW200_svd->Write();
  HQ_LW300_svd->Write();
  //HQ_LW400_svd->Write();
  //HQ_LW500_svd->Write();
  HQ_dataRunB_Elept->Write();
  HQ_dataRunC_Elept->Write();
  HQ_ZLL_Elept->Write();
  HQ_TT_Elept->Write();
  HQ_W3J_Elept->Write();
  HQ_W2J_Elept->Write();
  HQ_W1J_Elept->Write();
  HQ_WW_Elept->Write();
  HQ_WZ_Elept->Write();
  HQ_TTZ_Elept->Write();
  HQ_LW200_Elept->Write();
  HQ_LW300_Elept->Write();
  //HQ_LW400_Elept->Write();
  //HQ_LW500_Elept->Write();
  HQ_dataRunB_DieledR->Write();
  HQ_dataRunC_DieledR->Write();
  HQ_ZLL_DieledR->Write();
  HQ_TT_DieledR->Write();
  HQ_W3J_DieledR->Write();
  HQ_W2J_DieledR->Write();
  HQ_W1J_DieledR->Write();
  HQ_WW_DieledR->Write();
  HQ_WZ_DieledR->Write();
  HQ_TTZ_DieledR->Write();
  HQ_LW200_DieledR->Write();
  HQ_LW300_DieledR->Write();
  //HQ_LW400_DieledR->Write();
  //HQ_LW500_DieledR->Write();
  HQ_dataRunB_LWdR->Write();
  HQ_dataRunC_LWdR->Write();
  HQ_ZLL_LWdR->Write();
  HQ_TT_LWdR->Write();
  HQ_W3J_LWdR->Write();
  HQ_W2J_LWdR->Write();
  HQ_W1J_LWdR->Write();
  HQ_WW_LWdR->Write();
  HQ_WZ_LWdR->Write();
  HQ_TTZ_LWdR->Write();
  HQ_LW200_LWdR->Write();
  HQ_LW300_LWdR->Write();
  //HQ_LW400_LWdR->Write();
  //HQ_LW500_LWdR->Write();
  HQ_dataRunB_DiJetdR->Write();
  HQ_dataRunC_DiJetdR->Write();
  HQ_ZLL_DiJetdR->Write();
  HQ_TT_DiJetdR->Write();
  HQ_W3J_DiJetdR->Write();
  HQ_W2J_DiJetdR->Write();
  HQ_W1J_DiJetdR->Write();
  HQ_WW_DiJetdR->Write();
  HQ_WZ_DiJetdR->Write();
  HQ_TTZ_DiJetdR->Write();
  HQ_LW200_DiJetdR->Write();
  HQ_LW300_DiJetdR->Write();
  //HQ_LW400_DiJetdR->Write();
  //HQ_LW500_DiJetdR->Write();
  HQ_dataRunB_BJetPt->Write();
  HQ_dataRunC_BJetPt->Write();
  HQ_ZLL_BJetPt->Write();
  HQ_TT_BJetPt->Write();
  HQ_W3J_BJetPt->Write();
  HQ_W2J_BJetPt->Write();
  HQ_W1J_BJetPt->Write();
  HQ_WW_BJetPt->Write();
  HQ_WZ_BJetPt->Write();
  HQ_TTZ_BJetPt->Write();
  HQ_LW200_BJetPt->Write();
  HQ_LW300_BJetPt->Write();
  //HQ_LW400_BJetPt->Write();
  //HQ_LW500_BJetPt->Write();
  HQ_dataRunB_SBJetPt->Write();
  HQ_dataRunC_SBJetPt->Write();
  HQ_ZLL_SBJetPt->Write();
  HQ_TT_SBJetPt->Write();
  HQ_W3J_SBJetPt->Write();
  HQ_W2J_SBJetPt->Write();
  HQ_W1J_SBJetPt->Write();
  HQ_WW_SBJetPt->Write();
  HQ_WZ_SBJetPt->Write();
  HQ_TTZ_SBJetPt->Write();
  HQ_LW200_SBJetPt->Write();
  HQ_LW300_SBJetPt->Write();
  //HQ_LW400_SBJetPt->Write();
  //HQ_LW500_SBJetPt->Write();
  HQ_dataRunB_NJet->Write();
  HQ_dataRunC_NJet->Write();
  HQ_ZLL_NJet->Write();
  HQ_TT_NJet->Write();
  HQ_W3J_NJet->Write();
  HQ_W2J_NJet->Write();
  HQ_W1J_NJet->Write();
  HQ_WW_NJet->Write();
  HQ_WZ_NJet->Write();
  HQ_TTZ_NJet->Write();
  HQ_LW200_NJet->Write();
  HQ_LW300_NJet->Write();
  //HQ_LW400_NJet->Write();
  //HQ_LW500_NJet->Write();
  HQ_dataRunB_NEle->Write();
  HQ_dataRunC_NEle->Write();
  HQ_ZLL_NEle->Write();
  HQ_TT_NEle->Write();
  HQ_W3J_NEle->Write();
  HQ_W2J_NEle->Write();
  HQ_W1J_NEle->Write();
  HQ_WW_NEle->Write();
  HQ_WZ_NEle->Write();
  HQ_TTZ_NEle->Write();
  HQ_LW200_NEle->Write();
  HQ_LW300_NEle->Write();
  //HQ_LW400_NEle->Write();
  //HQ_LW500_NEle->Write();

  hfile->Close();


  return 0;

}
