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
// g++ -std=c++11 -g -O3 -Wall -Wextra -o EventLoopAnalysisII EventLoopAnalysisII.cxx $(root-config --cflags --libs)
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

//Uncertainty Histograms

TH1F* NF_dataRunB_ppoint_uncert = new TH1F("NF_dataRunB_ppoint_uncert","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_dataRunC_ppoint_uncert  = new TH1F("NF_dataRunC_ppoint_uncert","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_ZLL_ppoint_uncert = new TH1F("NF_ZLL_ppoint_uncert","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_TT_ppoint_uncert = new TH1F("NF_TT_ppoint_uncert","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_W3J_ppoint_uncert = new TH1F("NF_W3J_ppoint_uncert","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_W2J_ppoint_uncert = new TH1F("NF_W2J_ppoint_uncert","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_W1J_ppoint_uncert = new TH1F("NF_W1J_ppoint_uncert","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //NF_TTZ_ppoint_uncert = new TH1F("//NF_TTZ_ppoint_uncert","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //NF_WW_ppoint_uncert = new TH1F("//NF_WW_ppoint_uncert","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //NF_WZ_ppoint_uncert = new TH1F("//NF_WZ_ppoint_uncert","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_LW200_ppoint_uncert = new TH1F("NF_LW200_ppoint_uncert","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_LW300_ppoint_uncert = new TH1F("NF_LW300_ppoint_uncert","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_LW400_ppoint_uncert = new TH1F("NF_LW400_ppoint_uncert","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_LW500_ppoint_uncert = new TH1F("NF_LW500_ppoint_uncert","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_dataRunB_ppoint_uncert = new TH1F("TF_dataRunB_ppoint_uncert","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_dataRunC_ppoint_uncert  = new TH1F("TF_dataRunC_ppoint_uncert","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_ZLL_ppoint_uncert = new TH1F("TF_ZLL_ppoint_uncert","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_TT_ppoint_uncert = new TH1F("TF_TT_ppoint_uncert","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_W3J_ppoint_uncert = new TH1F("TF_W3J_ppoint_uncert","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_W2J_ppoint_uncert = new TH1F("TF_W2J_ppoint_uncert","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_W1J_ppoint_uncert = new TH1F("TF_W1J_ppoint_uncert","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TF_TTZ_ppoint_uncert = new TH1F("//TF_TTZ_ppoint_uncert","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TF_WW_ppoint_uncert = new TH1F("//TF_WW_ppoint_uncert","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TF_WZ_ppoint_uncert = new TH1F("//TF_WZ_ppoint_uncert","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_LW200_ppoint_uncert = new TH1F("TF_LW200_ppoint_uncert","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_LW300_ppoint_uncert = new TH1F("TF_LW300_ppoint_uncert","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_LW400_ppoint_uncert = new TH1F("TF_LW400_ppoint_uncert","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_LW500_ppoint_uncert = new TH1F("TF_LW500_ppoint_uncert","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_dataRunB_ppoint_uncert = new TH1F("TO_dataRunB_ppoint_uncert","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_dataRunC_ppoint_uncert  = new TH1F("TO_dataRunC_ppoint_uncert","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_ZLL_ppoint_uncert = new TH1F("TO_ZLL_ppoint_uncert","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_TT_ppoint_uncert = new TH1F("TO_TT_ppoint_uncert","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_W3J_ppoint_uncert = new TH1F("TO_W3J_ppoint_uncert","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_W2J_ppoint_uncert = new TH1F("TO_W2J_ppoint_uncert","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_W1J_ppoint_uncert = new TH1F("TO_W1J_ppoint_uncert","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TO_TTZ_ppoint_uncert = new TH1F("//TO_TTZ_ppoint_uncert","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TO_WW_ppoint_uncert = new TH1F("//TO_WW_ppoint_uncert","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TO_WZ_ppoint_uncert = new TH1F("//TO_WZ_ppoint_uncert","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_LW200_ppoint_uncert = new TH1F("TO_LW200_ppoint_uncert","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_LW300_ppoint_uncert = new TH1F("TO_LW300_ppoint_uncert","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_LW400_ppoint_uncert = new TH1F("TO_LW400_ppoint_uncert","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_LW500_ppoint_uncert = new TH1F("TO_LW500_ppoint_uncert","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_dataRunB_ppoint_uncert = new TH1F("HQ_dataRunB_ppoint_uncert","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_dataRunC_ppoint_uncert  = new TH1F("HQ_dataRunC_ppoint_uncert","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_ZLL_ppoint_uncert = new TH1F("HQ_ZLL_ppoint_uncert","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_TT_ppoint_uncert = new TH1F("HQ_TT_ppoint_uncert","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_W3J_ppoint_uncert = new TH1F("HQ_W3J_ppoint_uncert","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_W2J_ppoint_uncert = new TH1F("HQ_W2J_ppoint_uncert","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_W1J_ppoint_uncert = new TH1F("HQ_W1J_ppoint_uncert","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //HQ_TTZ_ppoint_uncert = new TH1F("//HQ_TTZ_ppoint_uncert","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //HQ_WW_ppoint_uncert = new TH1F("//HQ_WW_ppoint_uncert","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //HQ_WZ_ppoint_uncert = new TH1F("//HQ_WZ_ppoint_uncert","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_LW200_ppoint_uncert = new TH1F("HQ_LW200_ppoint_uncert","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_LW300_ppoint_uncert = new TH1F("HQ_LW300_ppoint_uncert","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_LW400_ppoint_uncert = new TH1F("HQ_LW400_ppoint_uncert","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_LW500_ppoint_uncert = new TH1F("HQ_LW500_ppoint_uncert","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_dataRunB_ppoint_uncert = new TH1F("JetS_dataRunB_ppoint_uncert","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_dataRunC_ppoint_uncert  = new TH1F("JetS_dataRunC_ppoint_uncert","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_ZLL_ppoint_uncert = new TH1F("JetS_ZLL_ppoint_uncert","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_TT_ppoint_uncert = new TH1F("JetS_TT_ppoint_uncert","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_W3J_ppoint_uncert = new TH1F("JetS_W3J_ppoint_uncert","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_W2J_ppoint_uncert = new TH1F("JetS_W2J_ppoint_uncert","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_W1J_ppoint_uncert = new TH1F("JetS_W1J_ppoint_uncert","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //JetS_TTZ_ppoint_uncert = new TH1F("//JetS_TTZ_ppoint_uncert","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //JetS_WW_ppoint_uncert = new TH1F("//JetS_WW_ppoint_uncert","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //JetS_WZ_ppoint_uncert = new TH1F("//JetS_WZ_ppoint_uncert","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_LW200_ppoint_uncert = new TH1F("JetS_LW200_ppoint_uncert","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_LW300_ppoint_uncert = new TH1F("JetS_LW300_ppoint_uncert","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_LW400_ppoint_uncert = new TH1F("JetS_LW400_ppoint_uncert","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_LW500_ppoint_uncert = new TH1F("JetS_LW500_ppoint_uncert","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_dataRunB_ppoint_uncert = new TH1F("DRC_dataRunB_ppoint_uncert","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_dataRunC_ppoint_uncert  = new TH1F("DRC_dataRunC_ppoint_uncert","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_ZLL_ppoint_uncert = new TH1F("DRC_ZLL_ppoint_uncert","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_TT_ppoint_uncert = new TH1F("DRC_TT_ppoint_uncert","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_W3J_ppoint_uncert = new TH1F("DRC_W3J_ppoint_uncert","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_W2J_ppoint_uncert = new TH1F("DRC_W2J_ppoint_uncert","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_W1J_ppoint_uncert = new TH1F("DRC_W1J_ppoint_uncert","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //DRC_TTZ_ppoint_uncert = new TH1F("//DRC_TTZ_ppoint_uncert","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //DRC_WW_ppoint_uncert = new TH1F("//DRC_WW_ppoint_uncert","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //DRC_WZ_ppoint_uncert = new TH1F("//DRC_WZ_ppoint_uncert","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_LW200_ppoint_uncert = new TH1F("DRC_LW200_ppoint_uncert","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_LW300_ppoint_uncert = new TH1F("DRC_LW300_ppoint_uncert","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_LW400_ppoint_uncert = new TH1F("DRC_LW400_ppoint_uncert","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_LW500_ppoint_uncert = new TH1F("DRC_LW500_ppoint_uncert","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_dataRunB_ppoint_uncert = new TH1F("SG_dataRunB_ppoint_uncert","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_dataRunC_ppoint_uncert  = new TH1F("SG_dataRunC_ppoint_uncert","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_ZLL_ppoint_uncert = new TH1F("SG_ZLL_ppoint_uncert","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_TT_ppoint_uncert = new TH1F("SG_TT_ppoint_uncert","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_W3J_ppoint_uncert = new TH1F("SG_W3J_ppoint_uncert","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_W2J_ppoint_uncert = new TH1F("SG_W2J_ppoint_uncert","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_W1J_ppoint_uncert = new TH1F("SG_W1J_ppoint_uncert","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //SG_TTZ_ppoint_uncert = new TH1F("//SG_TTZ_ppoint_uncert","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //SG_WW_ppoint_uncert = new TH1F("//SG_WW_ppoint_uncert","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //SG_WZ_ppoint_uncert = new TH1F("//SG_WZ_ppoint_uncert","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_LW200_ppoint_uncert = new TH1F("SG_LW200_ppoint_uncert","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_LW300_ppoint_uncert = new TH1F("SG_LW300_ppoint_uncert","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_LW400_ppoint_uncert = new TH1F("SG_LW400_ppoint_uncert","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_LW500_ppoint_uncert = new TH1F("SG_LW500_ppoint_uncert","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_dataRunB_ppoint_uncert = new TH1F("IPP_dataRunB_ppoint_uncert","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_dataRunC_ppoint_uncert  = new TH1F("IPP_dataRunC_ppoint_uncert","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_ZLL_ppoint_uncert = new TH1F("IPP_ZLL_ppoint_uncert","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_TT_ppoint_uncert = new TH1F("IPP_TT_ppoint_uncert","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_W3J_ppoint_uncert = new TH1F("IPP_W3J_ppoint_uncert","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_W2J_ppoint_uncert = new TH1F("IPP_W2J_ppoint_uncert","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_W1J_ppoint_uncert = new TH1F("IPP_W1J_ppoint_uncert","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //IPP_TTZ_ppoint_uncert = new TH1F("//IPP_TTZ_ppoint_uncert","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //IPP_WW_ppoint_uncert = new TH1F("//IPP_WW_ppoint_uncert","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //IPP_WZ_ppoint_uncert = new TH1F("//IPP_WZ_ppoint_uncert","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_LW200_ppoint_uncert = new TH1F("IPP_LW200_ppoint_uncert","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_LW300_ppoint_uncert = new TH1F("IPP_LW300_ppoint_uncert","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_LW400_ppoint_uncert = new TH1F("IPP_LW400_ppoint_uncert","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_LW500_ppoint_uncert = new TH1F("IPP_LW500_ppoint_uncert","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//Histograms for signal region no Filter
TH1F* NF_dataRunB_ppointS = new TH1F("NF_dataRunB_ppointS","NF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* NF_dataRunC_ppointS  = new TH1F("NF_dataRunC_ppointS","NF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* NF_ZLL_ppointS = new TH1F("NF_ZLL_ppointS","NF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* NF_TT_ppointS = new TH1F("NF_TT_ppointS","NF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* NF_W3J_ppointS = new TH1F("NF_W3J_ppointS","NF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* NF_W2J_ppointS = new TH1F("NF_W2J_ppointS","NF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* NF_W1J_ppointS = new TH1F("NF_W1J_ppointS","NF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //NF_TTZ_ppointS = new TH1F("//NF_TTZ_ppointS","NF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //NF_WW_ppointS = new TH1F("//NF_WW_ppointS","NF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //NF_WZ_ppointS = new TH1F("//NF_WZ_ppointS","NF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* NF_LW200_ppointS = new TH1F("NF_LW200_ppointS","NF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* NF_LW300_ppointS = new TH1F("NF_LW300_ppointS","NF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* NF_LW400_ppointS = new TH1F("NF_LW400_ppointS","NF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* NF_LW500_ppointS = new TH1F("NF_LW500_ppointS","NF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* NF_dataRunB_ppoint = new TH1F("NF_dataRunB_ppoint","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_dataRunC_ppoint  = new TH1F("NF_dataRunC_ppoint","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_ZLL_ppoint = new TH1F("NF_ZLL_ppoint","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_TT_ppoint = new TH1F("NF_TT_ppoint","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_W3J_ppoint = new TH1F("NF_W3J_ppoint","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_W2J_ppoint = new TH1F("NF_W2J_ppoint","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_W1J_ppoint = new TH1F("NF_W1J_ppoint","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //NF_TTZ_ppoint = new TH1F("//NF_TTZ_ppoint","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //NF_WW_ppoint = new TH1F("//NF_WW_ppoint","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //NF_WZ_ppoint = new TH1F("//NF_WZ_ppoint","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_LW200_ppoint = new TH1F("NF_LW200_ppoint","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_LW300_ppoint = new TH1F("NF_LW300_ppoint","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_LW400_ppoint = new TH1F("NF_LW400_ppoint","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* NF_LW500_ppoint = new TH1F("NF_LW500_ppoint","NF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
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
TH1F* NF_LW300_npv = new TH1F("NF_LW300_npv","NF Number of primary vertices",25,5,30);
TH1F* NF_LW400_npv = new TH1F("NF_LW400_npv","NF Number of primary vertices",25,5,30);
TH1F* NF_LW500_npv = new TH1F("NF_LW500_npv","NF Number of primary vertices",25,5,30);
TH1F* NF_dataRunB_nsv = new TH1F("NF_dataRunB_nsv","NF Number of secondary vertices",20,0,10);
TH1F* NF_dataRunC_nsv  = new TH1F("NF_dataRunC_nsv","NF Number of secondary vertices",20,0,10);
TH1F* NF_ZLL_nsv = new TH1F("NF_ZLL_nsv","NF Number of secondary vertices",20,0,10);
TH1F* NF_TT_nsv = new TH1F("NF_TT_nsv","NF Number of secondary vertices",20,0,10);
TH1F* NF_W3J_nsv = new TH1F("NF_W3J_nsv","NF Number of secondary vertices",20,0,10);
TH1F* NF_W2J_nsv = new TH1F("NF_W2J_nsv","NF Number of secondary vertices",20,0,10);
TH1F* NF_W1J_nsv = new TH1F("NF_W1J_nsv","NF Number of secondary vertices",20,0,10);
//TH1F* //NF_TTZ_nsv = new TH1F("//NF_TTZ_nsv","NF Number of secondary vertices",20,0,10);
//TH1F* //NF_WW_nsv = new TH1F("//NF_WW_nsv","NF Number of secondary vertices",20,0,10);
//TH1F* //NF_WZ_nsv = new TH1F("//NF_WZ_nsv","NF Number of secondary vertices",20,0,10);
TH1F* NF_LW200_nsv = new TH1F("NF_LW200_nsv","NF Number of secondary vertices",20,0,10);
TH1F* NF_LW300_nsv = new TH1F("NF_LW300_nsv","NF Number of secondary vertices",20,0,10);
TH1F* NF_LW400_nsv = new TH1F("NF_LW400_nsv","NF Number of secondary vertices",20,0,10);
TH1F* NF_LW500_nsv = new TH1F("NF_LW500_nsv","NF Number of secondary vertices",20,0,10);
TH1F* NF_dataRunB_svd = new TH1F("NF_dataRunB_svd","NF secondary vertex displacement",30,0,1);
TH1F* NF_dataRunC_svd  = new TH1F("NF_dataRunC_svd","NF secondary vertex displacement",30,0,1);
TH1F* NF_ZLL_svd = new TH1F("NF_ZLL_svd","NF secondary vertex displacement",30,0,1);
TH1F* NF_TT_svd = new TH1F("NF_TT_svd","NF secondary vertex displacement",30,0,1);
TH1F* NF_W3J_svd = new TH1F("NF_W3J_svd","NF secondary vertex displacement",30,0,1);
TH1F* NF_W2J_svd = new TH1F("NF_W2J_svd","NF secondary vertex displacement",30,0,1);
TH1F* NF_W1J_svd = new TH1F("NF_W1J_svd","NF secondary vertex displacement",30,0,1);
//TH1F* //NF_TTZ_svd = new TH1F("//NF_TTZ_svd","NF secondary vertex displacement",30,0,1);
//TH1F* //NF_WW_svd = new TH1F("//NF_WW_svd","NF secondary vertex displacement",30,0,1);
//TH1F* //NF_WZ_svd = new TH1F("//NF_WZ_svd","NF secondary vertex displacement",30,0,1);
TH1F* NF_LW200_svd = new TH1F("NF_LW200_svd","NF secondary vertex displacement",30,0,1);
TH1F* NF_LW300_svd = new TH1F("NF_LW300_svd","NF secondary vertex displacement",30,0,1);
TH1F* NF_LW400_svd = new TH1F("NF_LW400_svd","NF secondary vertex displacement",30,0,1);
TH1F* NF_LW500_svd = new TH1F("NF_LW500_svd","NF secondary vertex displacement",30,0,1);
TH1F* NF_dataRunB_BSd = new TH1F("NF_dataRunB_BSd","NF Beam spot distance",30,0,1);
TH1F* NF_dataRunC_BSd  = new TH1F("NF_dataRunC_BSd","NF Beam spot distance",30,0,1);
TH1F* NF_ZLL_BSd = new TH1F("NF_ZLL_BSd","NF Beam spot distance",30,0,1);
TH1F* NF_TT_BSd = new TH1F("NF_TT_BSd","NF Beam spot distance",30,0,1);
TH1F* NF_W3J_BSd = new TH1F("NF_W3J_BSd","NF Beam spot distance",30,0,1);
TH1F* NF_W2J_BSd = new TH1F("NF_W2J_BSd","NF Beam spot distance",30,0,1);
TH1F* NF_W1J_BSd = new TH1F("NF_W1J_BSd","NF Beam spot distance",30,0,1);
//TH1F* NF_TTZ_BSd = new TH1F("NF_TTZ_BSd","NF Beam spot distance",30,0,1);
//TH1F* NF_WW_BSd = new TH1F("NF_WW_BSd","NF Beam spot distance",30,0,1);
//TH1F* NF_WZ_BSd = new TH1F("NF_WZ_BSd","NF Beam spot distance",30,0,1);
TH1F* NF_LW200_BSd = new TH1F("NF_LW200_BSd","NF Beam spot distance",30,0,1);
TH1F* NF_LW300_BSd = new TH1F("NF_LW300_BSd","NF Beam spot distance",30,0,1);
TH1F* NF_LW400_BSd = new TH1F("NF_LW400_BSd","NF Beam spot distance",30,0,1);
TH1F* NF_LW500_BSd = new TH1F("NF_LW500_BSd","NF Beam spot distance",30,0,1);
TH1F* NF_dataRunB_BSdChi2norm = new TH1F("NF_dataRunB_BSdChi2norm","NF Beam spot distance",30,0,1);
TH1F* NF_dataRunC_BSdChi2norm  = new TH1F("NF_dataRunC_BSdChi2norm","NF Beam spot distance",30,0,1);
TH1F* NF_ZLL_BSdChi2norm = new TH1F("NF_ZLL_BSdChi2norm","NF Beam spot distance",30,0,1);
TH1F* NF_TT_BSdChi2norm = new TH1F("NF_TT_BSdChi2norm","NF Beam spot distance",30,0,1);
TH1F* NF_W3J_BSdChi2norm = new TH1F("NF_W3J_BSdChi2norm","NF Beam spot distance",30,0,1);
TH1F* NF_W2J_BSdChi2norm = new TH1F("NF_W2J_BSdChi2norm","NF Beam spot distance",30,0,1);
TH1F* NF_W1J_BSdChi2norm = new TH1F("NF_W1J_BSdChi2norm","NF Beam spot distance",30,0,1);
//TH1F* NF_TTZ_BSdChi2norm = new TH1F("NF_TTZ_BSdChi2norm","NF Beam spot distance",30,0,1);
//TH1F* NF_WW_BSdChi2norm = new TH1F("NF_WW_BSdChi2norm","NF Beam spot distance",30,0,1);
//TH1F* NF_WZ_BSdChi2norm = new TH1F("NF_WZ_BSdChi2norm","NF Beam spot distance",30,0,1);
TH1F* NF_LW200_BSdChi2norm = new TH1F("NF_LW200_BSdChi2norm","NF Beam spot distance",30,0,1);
TH1F* NF_LW300_BSdChi2norm = new TH1F("NF_LW300_BSdChi2norm","NF Beam spot distance",30,0,1);
TH1F* NF_LW400_BSdChi2norm = new TH1F("NF_LW400_BSdChi2norm","NF Beam spot distance",30,0,1);
TH1F* NF_LW500_BSdChi2norm = new TH1F("NF_LW500_BSdChi2norm","NF Beam spot distance",30,0,1);
//Histograms for signal region TF
TH1F* TF_dataRunB_ppointS = new TH1F("TF_dataRunB_ppointS","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_dataRunC_ppointS  = new TH1F("TF_dataRunC_ppointS","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_ZLL_ppointS = new TH1F("TF_ZLL_ppointS","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_TT_ppointS = new TH1F("TF_TT_ppointS","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_W3J_ppointS = new TH1F("TF_W3J_ppointS","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_W2J_ppointS = new TH1F("TF_W2J_ppointS","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_W1J_ppointS = new TH1F("TF_W1J_ppointS","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //TF_TTZ_ppointS = new TH1F("//TF_TTZ_ppointS","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //TF_WW_ppointS = new TH1F("//TF_WW_ppointS","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //TF_WZ_ppointS = new TH1F("//TF_WZ_ppointS","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_LW200_ppointS = new TH1F("TF_LW200_ppointS","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_LW300_ppointS = new TH1F("TF_LW300_ppointS","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_LW400_ppointS = new TH1F("TF_LW400_ppointS","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_LW500_ppointS = new TH1F("TF_LW500_ppointS","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_dataRunB_ppoint = new TH1F("TF_dataRunB_ppoint","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_dataRunC_ppoint  = new TH1F("TF_dataRunC_ppoint","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_ZLL_ppoint = new TH1F("TF_ZLL_ppoint","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_TT_ppoint = new TH1F("TF_TT_ppoint","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_W3J_ppoint = new TH1F("TF_W3J_ppoint","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_W2J_ppoint = new TH1F("TF_W2J_ppoint","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_W1J_ppoint = new TH1F("TF_W1J_ppoint","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TF_TTZ_ppoint = new TH1F("//TF_TTZ_ppoint","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TF_WW_ppoint = new TH1F("//TF_WW_ppoint","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TF_WZ_ppoint = new TH1F("//TF_WZ_ppoint","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_LW200_ppoint = new TH1F("TF_LW200_ppoint","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_LW300_ppoint = new TH1F("TF_LW300_ppoint","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_LW400_ppoint = new TH1F("TF_LW400_ppoint","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_LW500_ppoint = new TH1F("TF_LW500_ppoint","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
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
TH1F* TF_LW300_npv = new TH1F("TF_LW300_npv","TF Number of primary vertices",25,5,30);
TH1F* TF_LW400_npv = new TH1F("TF_LW400_npv","TF Number of primary vertices",25,5,30);
TH1F* TF_LW500_npv = new TH1F("TF_LW500_npv","TF Number of primary vertices",25,5,30);
TH1F* TF_dataRunB_nsv = new TH1F("TF_dataRunB_nsv","TF Number of secondary vertices",20,0,10);
TH1F* TF_dataRunC_nsv  = new TH1F("TF_dataRunC_nsv","TF Number of secondary vertices",20,0,10);
TH1F* TF_ZLL_nsv = new TH1F("TF_ZLL_nsv","TF Number of secondary vertices",20,0,10);
TH1F* TF_TT_nsv = new TH1F("TF_TT_nsv","TF Number of secondary vertices",20,0,10);
TH1F* TF_W3J_nsv = new TH1F("TF_W3J_nsv","TF Number of secondary vertices",20,0,10);
TH1F* TF_W2J_nsv = new TH1F("TF_W2J_nsv","TF Number of secondary vertices",20,0,10);
TH1F* TF_W1J_nsv = new TH1F("TF_W1J_nsv","TF Number of secondary vertices",20,0,10);
//TH1F* //TF_TTZ_nsv = new TH1F("//TF_TTZ_nsv","TF Number of secondary vertices",20,0,10);
//TH1F* //TF_WW_nsv = new TH1F("//TF_WW_nsv","TF Number of secondary vertices",20,0,10);
//TH1F* //TF_WZ_nsv = new TH1F("//TF_WZ_nsv","TF Number of secondary vertices",20,0,10);
TH1F* TF_LW200_nsv = new TH1F("TF_LW200_nsv","TF Number of secondary vertices",20,0,10);
TH1F* TF_LW300_nsv = new TH1F("TF_LW300_nsv","TF Number of secondary vertices",20,0,10);
TH1F* TF_LW400_nsv = new TH1F("TF_LW400_nsv","TF Number of secondary vertices",20,0,10);
TH1F* TF_LW500_nsv = new TH1F("TF_LW500_nsv","TF Number of secondary vertices",20,0,10);
TH1F* TF_dataRunB_svd = new TH1F("TF_dataRunB_svd","TF secondary vertex displacement",30,0,1);
TH1F* TF_dataRunC_svd  = new TH1F("TF_dataRunC_svd","TF secondary vertex displacement",30,0,1);
TH1F* TF_ZLL_svd = new TH1F("TF_ZLL_svd","TF secondary vertex displacement",30,0,1);
TH1F* TF_TT_svd = new TH1F("TF_TT_svd","TF secondary vertex displacement",30,0,1);
TH1F* TF_W3J_svd = new TH1F("TF_W3J_svd","TF secondary vertex displacement",30,0,1);
TH1F* TF_W2J_svd = new TH1F("TF_W2J_svd","TF secondary vertex displacement",30,0,1);
TH1F* TF_W1J_svd = new TH1F("TF_W1J_svd","TF secondary vertex displacement",30,0,1);
//TH1F* //TF_TTZ_svd = new TH1F("//TF_TTZ_svd","TF secondary vertex displacement",30,0,1);
//TH1F* //TF_WW_svd = new TH1F("//TF_WW_svd","TF secondary vertex displacement",30,0,1);
//TH1F* //TF_WZ_svd = new TH1F("//TF_WZ_svd","TF secondary vertex displacement",30,0,1);
TH1F* TF_LW200_svd = new TH1F("TF_LW200_svd","TF secondary vertex displacement",30,0,1);
TH1F* TF_LW300_svd = new TH1F("TF_LW300_svd","TF secondary vertex displacement",30,0,1);
TH1F* TF_LW400_svd = new TH1F("TF_LW400_svd","TF secondary vertex displacement",30,0,1);
TH1F* TF_LW500_svd = new TH1F("TF_LW500_svd","TF secondary vertex displacement",30,0,1);
TH1F* TF_dataRunB_BSd = new TH1F("TF_dataRunB_BSd","TF Beam spot distance",30,0,1);
TH1F* TF_dataRunC_BSd  = new TH1F("TF_dataRunC_BSd","TF Beam spot distance",30,0,1);
TH1F* TF_ZLL_BSd = new TH1F("TF_ZLL_BSd","TF Beam spot distance",30,0,1);
TH1F* TF_TT_BSd = new TH1F("TF_TT_BSd","TF Beam spot distance",30,0,1);
TH1F* TF_W3J_BSd = new TH1F("TF_W3J_BSd","TF Beam spot distance",30,0,1);
TH1F* TF_W2J_BSd = new TH1F("TF_W2J_BSd","TF Beam spot distance",30,0,1);
TH1F* TF_W1J_BSd = new TH1F("TF_W1J_BSd","TF Beam spot distance",30,0,1);
//TH1F* TF_TTZ_BSd = new TH1F("TF_TTZ_BSd","TF Beam spot distance",30,0,1);
//TH1F* TF_WW_BSd = new TH1F("TF_WW_BSd","TF Beam spot distance",30,0,1);
//TH1F* TF_WZ_BSd = new TH1F("TF_WZ_BSd","TF Beam spot distance",30,0,1);
TH1F* TF_LW200_BSd = new TH1F("TF_LW200_BSd","TF Beam spot distance",30,0,1);
TH1F* TF_LW300_BSd = new TH1F("TF_LW300_BSd","TF Beam spot distance",30,0,1);
TH1F* TF_LW400_BSd = new TH1F("TF_LW400_BSd","TF Beam spot distance",30,0,1);
TH1F* TF_LW500_BSd = new TH1F("TF_LW500_BSd","TF Beam spot distance",30,0,1);
TH1F* TF_dataRunB_BSdChi2norm = new TH1F("TF_dataRunB_BSdChi2norm","TF Beam spot distance",30,0,1);
TH1F* TF_dataRunC_BSdChi2norm  = new TH1F("TF_dataRunC_BSdChi2norm","TF Beam spot distance",30,0,1);
TH1F* TF_ZLL_BSdChi2norm = new TH1F("TF_ZLL_BSdChi2norm","TF Beam spot distance",30,0,1);
TH1F* TF_TT_BSdChi2norm = new TH1F("TF_TT_BSdChi2norm","TF Beam spot distance",30,0,1);
TH1F* TF_W3J_BSdChi2norm = new TH1F("TF_W3J_BSdChi2norm","TF Beam spot distance",30,0,1);
TH1F* TF_W2J_BSdChi2norm = new TH1F("TF_W2J_BSdChi2norm","TF Beam spot distance",30,0,1);
TH1F* TF_W1J_BSdChi2norm = new TH1F("TF_W1J_BSdChi2norm","TF Beam spot distance",30,0,1);
//TH1F* TF_TTZ_BSdChi2norm = new TH1F("TF_TTZ_BSdChi2norm","TF Beam spot distance",30,0,1);
//TH1F* TF_WW_BSdChi2norm = new TH1F("TF_WW_BSdChi2norm","TF Beam spot distance",30,0,1);
//TH1F* TF_WZ_BSdChi2norm = new TH1F("TF_WZ_BSdChi2norm","TF Beam spot distance",30,0,1);
TH1F* TF_LW200_BSdChi2norm = new TH1F("TF_LW200_BSdChi2norm","TF Beam spot distance",30,0,1);
TH1F* TF_LW300_BSdChi2norm = new TH1F("TF_LW300_BSdChi2norm","TF Beam spot distance",30,0,1);
TH1F* TF_LW400_BSdChi2norm = new TH1F("TF_LW400_BSdChi2norm","TF Beam spot distance",30,0,1);
TH1F* TF_LW500_BSdChi2norm = new TH1F("TF_LW500_BSdChi2norm","TF Beam spot distance",30,0,1);
//Histograms for signal region TO
TH1F* TO_dataRunB_ppointS = new TH1F("TO_dataRunB_ppointS","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_dataRunC_ppointS  = new TH1F("TO_dataRunC_ppointS","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_ZLL_ppointS = new TH1F("TO_ZLL_ppointS","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_TT_ppointS = new TH1F("TO_TT_ppointS","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_W3J_ppointS = new TH1F("TO_W3J_ppointS","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_W2J_ppointS = new TH1F("TO_W2J_ppointS","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_W1J_ppointS = new TH1F("TO_W1J_ppointS","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //TO_TTZ_ppointS = new TH1F("//TO_TTZ_ppointS","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //TO_WW_ppointS = new TH1F("//TO_WW_ppointS","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //TO_WZ_ppointS = new TH1F("//TO_WZ_ppointS","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_LW200_ppointS = new TH1F("TO_LW200_ppointS","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_LW300_ppointS = new TH1F("TO_LW300_ppointS","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_LW400_ppointS = new TH1F("TO_LW400_ppointS","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_LW500_ppointS = new TH1F("TO_LW500_ppointS","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_dataRunB_ppoint = new TH1F("TO_dataRunB_ppoint","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_dataRunC_ppoint  = new TH1F("TO_dataRunC_ppoint","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_ZLL_ppoint = new TH1F("TO_ZLL_ppoint","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_TT_ppoint = new TH1F("TO_TT_ppoint","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_W3J_ppoint = new TH1F("TO_W3J_ppoint","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_W2J_ppoint = new TH1F("TO_W2J_ppoint","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_W1J_ppoint = new TH1F("TO_W1J_ppoint","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TO_TTZ_ppoint = new TH1F("//TO_TTZ_ppoint","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TO_WW_ppoint = new TH1F("//TO_WW_ppoint","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TO_WZ_ppoint = new TH1F("//TO_WZ_ppoint","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_LW200_ppoint = new TH1F("TO_LW200_ppoint","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_LW300_ppoint = new TH1F("TO_LW300_ppoint","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_LW400_ppoint = new TH1F("TO_LW400_ppoint","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_LW500_ppoint = new TH1F("TO_LW500_ppoint","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_dataRunB_npv = new TH1F("TO_dataRunB_npv","TO Number of primary vertices",25,5,30);
TH1F* TO_dataRunC_npv  = new TH1F("TO_dataRunC_npv","TO Number of primary vertices",25,5,30);
TH1F* TO_ZLL_npv = new TH1F("TO_ZLL_npv","TO Number of primary vertices",25,5,30);
TH1F* TO_TT_npv = new TH1F("TO_TT_npv","TO Number of primary vertices",25,5,30);
TH1F* TO_W3J_npv = new TH1F("TO_W3J_npv","TO Number of primary vertices",25,5,30);
TH1F* TO_W2J_npv = new TH1F("TO_W2J_npv","TO Number of primary vertices",25,5,30);
TH1F* TO_W1J_npv = new TH1F("TO_W1J_npv","TO Number of primary vertices",25,5,30);
//TH1F* //TO_TTZ_npv = new TH1F("//TO_TTZ_npv","TO Number of primary vertices",25,5,30);
//TH1F* //TO_WW_npv = new TH1F("//TO_WW_npv","TO Number of primary vertices",25,5,30);
//TH1F* //TO_WZ_npv = new TH1F("//TO_WZ_npv","TO Number of primary vertices",25,5,30);
TH1F* TO_LW200_npv = new TH1F("TO_LW200_npv","TO Number of primary vertices",25,5,30);
TH1F* TO_LW300_npv = new TH1F("TO_LW300_npv","TO Number of primary vertices",25,5,30);
TH1F* TO_LW400_npv = new TH1F("TO_LW400_npv","TO Number of primary vertices",25,5,30);
TH1F* TO_LW500_npv = new TH1F("TO_LW500_npv","TO Number of primary vertices",25,5,30);
TH1F* TO_dataRunB_nsv = new TH1F("TO_dataRunB_nsv","TO Number of secondary vertices",20,0,10);
TH1F* TO_dataRunC_nsv  = new TH1F("TO_dataRunC_nsv","TO Number of secondary vertices",20,0,10);
TH1F* TO_ZLL_nsv = new TH1F("TO_ZLL_nsv","TO Number of secondary vertices",20,0,10);
TH1F* TO_TT_nsv = new TH1F("TO_TT_nsv","TO Number of secondary vertices",20,0,10);
TH1F* TO_W3J_nsv = new TH1F("TO_W3J_nsv","TO Number of secondary vertices",20,0,10);
TH1F* TO_W2J_nsv = new TH1F("TO_W2J_nsv","TO Number of secondary vertices",20,0,10);
TH1F* TO_W1J_nsv = new TH1F("TO_W1J_nsv","TO Number of secondary vertices",20,0,10);
//TH1F* //TO_TTZ_nsv = new TH1F("//TO_TTZ_nsv","TO Number of secondary vertices",20,0,10);
//TH1F* //TO_WW_nsv = new TH1F("//TO_WW_nsv","TO Number of secondary vertices",20,0,10);
//TH1F* //TO_WZ_nsv = new TH1F("//TO_WZ_nsv","TO Number of secondary vertices",20,0,10);
TH1F* TO_LW200_nsv = new TH1F("TO_LW200_nsv","TO Number of secondary vertices",20,0,10);
TH1F* TO_LW300_nsv = new TH1F("TO_LW300_nsv","TO Number of secondary vertices",20,0,10);
TH1F* TO_LW400_nsv = new TH1F("TO_LW400_nsv","TO Number of secondary vertices",20,0,10);
TH1F* TO_LW500_nsv = new TH1F("TO_LW500_nsv","TO Number of secondary vertices",20,0,10);
TH1F* TO_dataRunB_svd = new TH1F("TO_dataRunB_svd","TO secondary vertex displacement",30,0,1);
TH1F* TO_dataRunC_svd  = new TH1F("TO_dataRunC_svd","TO secondary vertex displacement",30,0,1);
TH1F* TO_ZLL_svd = new TH1F("TO_ZLL_svd","TO secondary vertex displacement",30,0,1);
TH1F* TO_TT_svd = new TH1F("TO_TT_svd","TO secondary vertex displacement",30,0,1);
TH1F* TO_W3J_svd = new TH1F("TO_W3J_svd","TO secondary vertex displacement",30,0,1);
TH1F* TO_W2J_svd = new TH1F("TO_W2J_svd","TO secondary vertex displacement",30,0,1);
TH1F* TO_W1J_svd = new TH1F("TO_W1J_svd","TO secondary vertex displacement",30,0,1);
//TH1F* //TO_TTZ_svd = new TH1F("//TO_TTZ_svd","TO secondary vertex displacement",30,0,1);
//TH1F* //TO_WW_svd = new TH1F("//TO_WW_svd","TO secondary vertex displacement",30,0,1);
//TH1F* //TO_WZ_svd = new TH1F("//TO_WZ_svd","TO secondary vertex displacement",30,0,1);
TH1F* TO_LW200_svd = new TH1F("TO_LW200_svd","TO secondary vertex displacement",30,0,1);
TH1F* TO_LW300_svd = new TH1F("TO_LW300_svd","TO secondary vertex displacement",30,0,1);
TH1F* TO_LW400_svd = new TH1F("TO_LW400_svd","TO secondary vertex displacement",30,0,1);
TH1F* TO_LW500_svd = new TH1F("TO_LW500_svd","TO secondary vertex displacement",30,0,1);
TH1F* TO_dataRunB_BSd = new TH1F("TO_dataRunB_BSd","TO Beam spot distance",30,0,1);
TH1F* TO_dataRunC_BSd  = new TH1F("TO_dataRunC_BSd","TO Beam spot distance",30,0,1);
TH1F* TO_ZLL_BSd = new TH1F("TO_ZLL_BSd","TO Beam spot distance",30,0,1);
TH1F* TO_TT_BSd = new TH1F("TO_TT_BSd","TO Beam spot distance",30,0,1);
TH1F* TO_W3J_BSd = new TH1F("TO_W3J_BSd","TO Beam spot distance",30,0,1);
TH1F* TO_W2J_BSd = new TH1F("TO_W2J_BSd","TO Beam spot distance",30,0,1);
TH1F* TO_W1J_BSd = new TH1F("TO_W1J_BSd","TO Beam spot distance",30,0,1);
//TH1F* TO_TTZ_BSd = new TH1F("TO_TTZ_BSd","TO Beam spot distance",30,0,1);
//TH1F* TO_WW_BSd = new TH1F("TO_WW_BSd","TO Beam spot distance",30,0,1);
//TH1F* TO_WZ_BSd = new TH1F("TO_WZ_BSd","TO Beam spot distance",30,0,1);
TH1F* TO_LW200_BSd = new TH1F("TO_LW200_BSd","TO Beam spot distance",30,0,1);
TH1F* TO_LW300_BSd = new TH1F("TO_LW300_BSd","TO Beam spot distance",30,0,1);
TH1F* TO_LW400_BSd = new TH1F("TO_LW400_BSd","TO Beam spot distance",30,0,1);
TH1F* TO_LW500_BSd = new TH1F("TO_LW500_BSd","TO Beam spot distance",30,0,1);
TH1F* TO_dataRunB_BSdChi2norm = new TH1F("TO_dataRunB_BSdChi2norm","TO Beam spot distance",30,0,1);
TH1F* TO_dataRunC_BSdChi2norm  = new TH1F("TO_dataRunC_BSdChi2norm","TO Beam spot distance",30,0,1);
TH1F* TO_ZLL_BSdChi2norm = new TH1F("TO_ZLL_BSdChi2norm","TO Beam spot distance",30,0,1);
TH1F* TO_TT_BSdChi2norm = new TH1F("TO_TT_BSdChi2norm","TO Beam spot distance",30,0,1);
TH1F* TO_W3J_BSdChi2norm = new TH1F("TO_W3J_BSdChi2norm","TO Beam spot distance",30,0,1);
TH1F* TO_W2J_BSdChi2norm = new TH1F("TO_W2J_BSdChi2norm","TO Beam spot distance",30,0,1);
TH1F* TO_W1J_BSdChi2norm = new TH1F("TO_W1J_BSdChi2norm","TO Beam spot distance",30,0,1);
//TH1F* TO_TTZ_BSdChi2norm = new TH1F("TO_TTZ_BSdChi2norm","TO Beam spot distance",30,0,1);
//TH1F* TO_WW_BSdChi2norm = new TH1F("TO_WW_BSdChi2norm","TO Beam spot distance",30,0,1);
//TH1F* TO_WZ_BSdChi2norm = new TH1F("TO_WZ_BSdChi2norm","TO Beam spot distance",30,0,1);
TH1F* TO_LW200_BSdChi2norm = new TH1F("TO_LW200_BSdChi2norm","TO Beam spot distance",30,0,1);
TH1F* TO_LW300_BSdChi2norm = new TH1F("TO_LW300_BSdChi2norm","TO Beam spot distance",30,0,1);
TH1F* TO_LW400_BSdChi2norm = new TH1F("TO_LW400_BSdChi2norm","TO Beam spot distance",30,0,1);
TH1F* TO_LW500_BSdChi2norm = new TH1F("TO_LW500_BSdChi2norm","TO Beam spot distance",30,0,1);
//Histograms for signal region HQ
TH1F* HQ_dataRunB_ppointS = new TH1F("HQ_dataRunB_ppointS","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_dataRunC_ppointS  = new TH1F("HQ_dataRunC_ppointS","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_ZLL_ppointS = new TH1F("HQ_ZLL_ppointS","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_TT_ppointS = new TH1F("HQ_TT_ppointS","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_W3J_ppointS = new TH1F("HQ_W3J_ppointS","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_W2J_ppointS = new TH1F("HQ_W2J_ppointS","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_W1J_ppointS = new TH1F("HQ_W1J_ppointS","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //HQ_TTZ_ppointS = new TH1F("//HQ_TTZ_ppointS","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //HQ_WW_ppointS = new TH1F("//HQ_WW_ppointS","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //HQ_WZ_ppointS = new TH1F("//HQ_WZ_ppointS","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_LW200_ppointS = new TH1F("HQ_LW200_ppointS","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_LW300_ppointS = new TH1F("HQ_LW300_ppointS","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_LW400_ppointS = new TH1F("HQ_LW400_ppointS","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_LW500_ppointS = new TH1F("HQ_LW500_ppointS","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_dataRunB_ppoint = new TH1F("HQ_dataRunB_ppoint","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_dataRunC_ppoint  = new TH1F("HQ_dataRunC_ppoint","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_ZLL_ppoint = new TH1F("HQ_ZLL_ppoint","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_TT_ppoint = new TH1F("HQ_TT_ppoint","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_W3J_ppoint = new TH1F("HQ_W3J_ppoint","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_W2J_ppoint = new TH1F("HQ_W2J_ppoint","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_W1J_ppoint = new TH1F("HQ_W1J_ppoint","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //HQ_TTZ_ppoint = new TH1F("//HQ_TTZ_ppoint","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //HQ_WW_ppoint = new TH1F("//HQ_WW_ppoint","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //HQ_WZ_ppoint = new TH1F("//HQ_WZ_ppoint","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_LW200_ppoint = new TH1F("HQ_LW200_ppoint","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_LW300_ppoint = new TH1F("HQ_LW300_ppoint","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_LW400_ppoint = new TH1F("HQ_LW400_ppoint","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_LW500_ppoint = new TH1F("HQ_LW500_ppoint","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_dataRunB_npv = new TH1F("HQ_dataRunB_npv","HQ Number of primary vertices",25,5,30);
TH1F* HQ_dataRunC_npv  = new TH1F("HQ_dataRunC_npv","HQ Number of primary vertices",25,5,30);
TH1F* HQ_ZLL_npv = new TH1F("HQ_ZLL_npv","HQ Number of primary vertices",25,5,30);
TH1F* HQ_TT_npv = new TH1F("HQ_TT_npv","HQ Number of primary vertices",25,5,30);
TH1F* HQ_W3J_npv = new TH1F("HQ_W3J_npv","HQ Number of primary vertices",25,5,30);
TH1F* HQ_W2J_npv = new TH1F("HQ_W2J_npv","HQ Number of primary vertices",25,5,30);
TH1F* HQ_W1J_npv = new TH1F("HQ_W1J_npv","HQ Number of primary vertices",25,5,30);
//TH1F* //HQ_TTZ_npv = new TH1F("//HQ_TTZ_npv","HQ Number of primary vertices",25,5,30);
//TH1F* //HQ_WW_npv = new TH1F("//HQ_WW_npv","HQ Number of primary vertices",25,5,30);
//TH1F* //HQ_WZ_npv = new TH1F("//HQ_WZ_npv","HQ Number of primary vertices",25,5,30);
TH1F* HQ_LW200_npv = new TH1F("HQ_LW200_npv","HQ Number of primary vertices",25,5,30);
TH1F* HQ_LW300_npv = new TH1F("HQ_LW300_npv","HQ Number of primary vertices",25,5,30);
TH1F* HQ_LW400_npv = new TH1F("HQ_LW400_npv","HQ Number of primary vertices",25,5,30);
TH1F* HQ_LW500_npv = new TH1F("HQ_LW500_npv","HQ Number of primary vertices",25,5,30);
TH1F* HQ_dataRunB_nsv = new TH1F("HQ_dataRunB_nsv","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_dataRunC_nsv  = new TH1F("HQ_dataRunC_nsv","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_ZLL_nsv = new TH1F("HQ_ZLL_nsv","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_TT_nsv = new TH1F("HQ_TT_nsv","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_W3J_nsv = new TH1F("HQ_W3J_nsv","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_W2J_nsv = new TH1F("HQ_W2J_nsv","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_W1J_nsv = new TH1F("HQ_W1J_nsv","HQ Number of secondary vertices",20,0,10);
//TH1F* //HQ_TTZ_nsv = new TH1F("//HQ_TTZ_nsv","HQ Number of secondary vertices",20,0,10);
//TH1F* //HQ_WW_nsv = new TH1F("//HQ_WW_nsv","HQ Number of secondary vertices",20,0,10);
//TH1F* //HQ_WZ_nsv = new TH1F("//HQ_WZ_nsv","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_LW200_nsv = new TH1F("HQ_LW200_nsv","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_LW300_nsv = new TH1F("HQ_LW300_nsv","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_LW400_nsv = new TH1F("HQ_LW400_nsv","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_LW500_nsv = new TH1F("HQ_LW500_nsv","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_dataRunB_svd = new TH1F("HQ_dataRunB_svd","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_dataRunC_svd  = new TH1F("HQ_dataRunC_svd","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_ZLL_svd = new TH1F("HQ_ZLL_svd","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_TT_svd = new TH1F("HQ_TT_svd","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_W3J_svd = new TH1F("HQ_W3J_svd","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_W2J_svd = new TH1F("HQ_W2J_svd","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_W1J_svd = new TH1F("HQ_W1J_svd","HQ secondary vertex displacement",30,0,1);
//TH1F* //HQ_TTZ_svd = new TH1F("//HQ_TTZ_svd","HQ secondary vertex displacement",30,0,1);
//TH1F* //HQ_WW_svd = new TH1F("//HQ_WW_svd","HQ secondary vertex displacement",30,0,1);
//TH1F* //HQ_WZ_svd = new TH1F("//HQ_WZ_svd","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_LW200_svd = new TH1F("HQ_LW200_svd","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_LW300_svd = new TH1F("HQ_LW300_svd","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_LW400_svd = new TH1F("HQ_LW400_svd","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_LW500_svd = new TH1F("HQ_LW500_svd","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_dataRunB_BSd = new TH1F("HQ_dataRunB_BSd","HQ Beam spot distance",30,0,1);
TH1F* HQ_dataRunC_BSd  = new TH1F("HQ_dataRunC_BSd","HQ Beam spot distance",30,0,1);
TH1F* HQ_ZLL_BSd = new TH1F("HQ_ZLL_BSd","HQ Beam spot distance",30,0,1);
TH1F* HQ_TT_BSd = new TH1F("HQ_TT_BSd","HQ Beam spot distance",30,0,1);
TH1F* HQ_W3J_BSd = new TH1F("HQ_W3J_BSd","HQ Beam spot distance",30,0,1);
TH1F* HQ_W2J_BSd = new TH1F("HQ_W2J_BSd","HQ Beam spot distance",30,0,1);
TH1F* HQ_W1J_BSd = new TH1F("HQ_W1J_BSd","HQ Beam spot distance",30,0,1);
//TH1F* HQ_TTZ_BSd = new TH1F("HQ_TTZ_BSd","HQ Beam spot distance",30,0,1);
//TH1F* HQ_WW_BSd = new TH1F("HQ_WW_BSd","HQ Beam spot distance",30,0,1);
//TH1F* HQ_WZ_BSd = new TH1F("HQ_WZ_BSd","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW200_BSd = new TH1F("HQ_LW200_BSd","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW300_BSd = new TH1F("HQ_LW300_BSd","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW400_BSd = new TH1F("HQ_LW400_BSd","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW500_BSd = new TH1F("HQ_LW500_BSd","HQ Beam spot distance",30,0,1);
TH1F* HQ_dataRunB_BSdChi2norm = new TH1F("HQ_dataRunB_BSdChi2norm","HQ Beam spot distance",30,0,1);
TH1F* HQ_dataRunC_BSdChi2norm  = new TH1F("HQ_dataRunC_BSdChi2norm","HQ Beam spot distance",30,0,1);
TH1F* HQ_ZLL_BSdChi2norm = new TH1F("HQ_ZLL_BSdChi2norm","HQ Beam spot distance",30,0,1);
TH1F* HQ_TT_BSdChi2norm = new TH1F("HQ_TT_BSdChi2norm","HQ Beam spot distance",30,0,1);
TH1F* HQ_W3J_BSdChi2norm = new TH1F("HQ_W3J_BSdChi2norm","HQ Beam spot distance",30,0,1);
TH1F* HQ_W2J_BSdChi2norm = new TH1F("HQ_W2J_BSdChi2norm","HQ Beam spot distance",30,0,1);
TH1F* HQ_W1J_BSdChi2norm = new TH1F("HQ_W1J_BSdChi2norm","HQ Beam spot distance",30,0,1);
//TH1F* HQ_TTZ_BSdChi2norm = new TH1F("HQ_TTZ_BSdChi2norm","HQ Beam spot distance",30,0,1);
//TH1F* HQ_WW_BSdChi2norm = new TH1F("HQ_WW_BSdChi2norm","HQ Beam spot distance",30,0,1);
//TH1F* HQ_WZ_BSdChi2norm = new TH1F("HQ_WZ_BSdChi2norm","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW200_BSdChi2norm = new TH1F("HQ_LW200_BSdChi2norm","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW300_BSdChi2norm = new TH1F("HQ_LW300_BSdChi2norm","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW400_BSdChi2norm = new TH1F("HQ_LW400_BSdChi2norm","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW500_BSdChi2norm = new TH1F("HQ_LW500_BSdChi2norm","HQ Beam spot distance",30,0,1);
//Histograms for signal region JetS
TH1F* JetS_dataRunB_ppointS = new TH1F("JetS_dataRunB_ppointS","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_dataRunC_ppointS  = new TH1F("JetS_dataRunC_ppointS","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_ZLL_ppointS = new TH1F("JetS_ZLL_ppointS","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_TT_ppointS = new TH1F("JetS_TT_ppointS","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_W3J_ppointS = new TH1F("JetS_W3J_ppointS","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_W2J_ppointS = new TH1F("JetS_W2J_ppointS","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_W1J_ppointS = new TH1F("JetS_W1J_ppointS","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //JetS_TTZ_ppointS = new TH1F("//JetS_TTZ_ppointS","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //JetS_WW_ppointS = new TH1F("//JetS_WW_ppointS","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //JetS_WZ_ppointS = new TH1F("//JetS_WZ_ppointS","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_LW200_ppointS = new TH1F("JetS_LW200_ppointS","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_LW300_ppointS = new TH1F("JetS_LW300_ppointS","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_LW400_ppointS = new TH1F("JetS_LW400_ppointS","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_LW500_ppointS = new TH1F("JetS_LW500_ppointS","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_dataRunB_ppoint = new TH1F("JetS_dataRunB_ppoint","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_dataRunC_ppoint  = new TH1F("JetS_dataRunC_ppoint","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_ZLL_ppoint = new TH1F("JetS_ZLL_ppoint","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_TT_ppoint = new TH1F("JetS_TT_ppoint","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_W3J_ppoint = new TH1F("JetS_W3J_ppoint","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_W2J_ppoint = new TH1F("JetS_W2J_ppoint","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_W1J_ppoint = new TH1F("JetS_W1J_ppoint","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //JetS_TTZ_ppoint = new TH1F("//JetS_TTZ_ppoint","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //JetS_WW_ppoint = new TH1F("//JetS_WW_ppoint","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //JetS_WZ_ppoint = new TH1F("//JetS_WZ_ppoint","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_LW200_ppoint = new TH1F("JetS_LW200_ppoint","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_LW300_ppoint = new TH1F("JetS_LW300_ppoint","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_LW400_ppoint = new TH1F("JetS_LW400_ppoint","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_LW500_ppoint = new TH1F("JetS_LW500_ppoint","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_dataRunB_npv = new TH1F("JetS_dataRunB_npv","JetS Number of primary vertices",25,5,30);
TH1F* JetS_dataRunC_npv  = new TH1F("JetS_dataRunC_npv","JetS Number of primary vertices",25,5,30);
TH1F* JetS_ZLL_npv = new TH1F("JetS_ZLL_npv","JetS Number of primary vertices",25,5,30);
TH1F* JetS_TT_npv = new TH1F("JetS_TT_npv","JetS Number of primary vertices",25,5,30);
TH1F* JetS_W3J_npv = new TH1F("JetS_W3J_npv","JetS Number of primary vertices",25,5,30);
TH1F* JetS_W2J_npv = new TH1F("JetS_W2J_npv","JetS Number of primary vertices",25,5,30);
TH1F* JetS_W1J_npv = new TH1F("JetS_W1J_npv","JetS Number of primary vertices",25,5,30);
//TH1F* //JetS_TTZ_npv = new TH1F("//JetS_TTZ_npv","JetS Number of primary vertices",25,5,30);
//TH1F* //JetS_WW_npv = new TH1F("//JetS_WW_npv","JetS Number of primary vertices",25,5,30);
//TH1F* //JetS_WZ_npv = new TH1F("//JetS_WZ_npv","JetS Number of primary vertices",25,5,30);
TH1F* JetS_LW200_npv = new TH1F("JetS_LW200_npv","JetS Number of primary vertices",25,5,30);
TH1F* JetS_LW300_npv = new TH1F("JetS_LW300_npv","JetS Number of primary vertices",25,5,30);
TH1F* JetS_LW400_npv = new TH1F("JetS_LW400_npv","JetS Number of primary vertices",25,5,30);
TH1F* JetS_LW500_npv = new TH1F("JetS_LW500_npv","JetS Number of primary vertices",25,5,30);
TH1F* JetS_dataRunB_nsv = new TH1F("JetS_dataRunB_nsv","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_dataRunC_nsv  = new TH1F("JetS_dataRunC_nsv","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_ZLL_nsv = new TH1F("JetS_ZLL_nsv","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_TT_nsv = new TH1F("JetS_TT_nsv","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_W3J_nsv = new TH1F("JetS_W3J_nsv","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_W2J_nsv = new TH1F("JetS_W2J_nsv","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_W1J_nsv = new TH1F("JetS_W1J_nsv","JetS Number of secondary vertices",20,0,10);
//TH1F* //JetS_TTZ_nsv = new TH1F("//JetS_TTZ_nsv","JetS Number of secondary vertices",20,0,10);
//TH1F* //JetS_WW_nsv = new TH1F("//JetS_WW_nsv","JetS Number of secondary vertices",20,0,10);
//TH1F* //JetS_WZ_nsv = new TH1F("//JetS_WZ_nsv","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_LW200_nsv = new TH1F("JetS_LW200_nsv","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_LW300_nsv = new TH1F("JetS_LW300_nsv","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_LW400_nsv = new TH1F("JetS_LW400_nsv","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_LW500_nsv = new TH1F("JetS_LW500_nsv","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_dataRunB_svd = new TH1F("JetS_dataRunB_svd","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_dataRunC_svd  = new TH1F("JetS_dataRunC_svd","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_ZLL_svd = new TH1F("JetS_ZLL_svd","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_TT_svd = new TH1F("JetS_TT_svd","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_W3J_svd = new TH1F("JetS_W3J_svd","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_W2J_svd = new TH1F("JetS_W2J_svd","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_W1J_svd = new TH1F("JetS_W1J_svd","JetS secondary vertex displacement",30,0,1);
//TH1F* //JetS_TTZ_svd = new TH1F("//JetS_TTZ_svd","JetS secondary vertex displacement",30,0,1);
//TH1F* //JetS_WW_svd = new TH1F("//JetS_WW_svd","JetS secondary vertex displacement",30,0,1);
//TH1F* //JetS_WZ_svd = new TH1F("//JetS_WZ_svd","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_LW200_svd = new TH1F("JetS_LW200_svd","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_LW300_svd = new TH1F("JetS_LW300_svd","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_LW400_svd = new TH1F("JetS_LW400_svd","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_LW500_svd = new TH1F("JetS_LW500_svd","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_dataRunB_BSd = new TH1F("JetS_dataRunB_BSd","JetS Beam spot distance",30,0,1);
TH1F* JetS_dataRunC_BSd  = new TH1F("JetS_dataRunC_BSd","JetS Beam spot distance",30,0,1);
TH1F* JetS_ZLL_BSd = new TH1F("JetS_ZLL_BSd","JetS Beam spot distance",30,0,1);
TH1F* JetS_TT_BSd = new TH1F("JetS_TT_BSd","JetS Beam spot distance",30,0,1);
TH1F* JetS_W3J_BSd = new TH1F("JetS_W3J_BSd","JetS Beam spot distance",30,0,1);
TH1F* JetS_W2J_BSd = new TH1F("JetS_W2J_BSd","JetS Beam spot distance",30,0,1);
TH1F* JetS_W1J_BSd = new TH1F("JetS_W1J_BSd","JetS Beam spot distance",30,0,1);
//TH1F* JetS_TTZ_BSd = new TH1F("JetS_TTZ_BSd","JetS Beam spot distance",30,0,1);
//TH1F* JetS_WW_BSd = new TH1F("JetS_WW_BSd","JetS Beam spot distance",30,0,1);
//TH1F* JetS_WZ_BSd = new TH1F("JetS_WZ_BSd","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW200_BSd = new TH1F("JetS_LW200_BSd","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW300_BSd = new TH1F("JetS_LW300_BSd","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW400_BSd = new TH1F("JetS_LW400_BSd","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW500_BSd = new TH1F("JetS_LW500_BSd","JetS Beam spot distance",30,0,1);
TH1F* JetS_dataRunB_BSdChi2norm = new TH1F("JetS_dataRunB_BSdChi2norm","JetS Beam spot distance",30,0,1);
TH1F* JetS_dataRunC_BSdChi2norm  = new TH1F("JetS_dataRunC_BSdChi2norm","JetS Beam spot distance",30,0,1);
TH1F* JetS_ZLL_BSdChi2norm = new TH1F("JetS_ZLL_BSdChi2norm","JetS Beam spot distance",30,0,1);
TH1F* JetS_TT_BSdChi2norm = new TH1F("JetS_TT_BSdChi2norm","JetS Beam spot distance",30,0,1);
TH1F* JetS_W3J_BSdChi2norm = new TH1F("JetS_W3J_BSdChi2norm","JetS Beam spot distance",30,0,1);
TH1F* JetS_W2J_BSdChi2norm = new TH1F("JetS_W2J_BSdChi2norm","JetS Beam spot distance",30,0,1);
TH1F* JetS_W1J_BSdChi2norm = new TH1F("JetS_W1J_BSdChi2norm","JetS Beam spot distance",30,0,1);
//TH1F* JetS_TTZ_BSdChi2norm = new TH1F("JetS_TTZ_BSdChi2norm","JetS Beam spot distance",30,0,1);
//TH1F* JetS_WW_BSdChi2norm = new TH1F("JetS_WW_BSdChi2norm","JetS Beam spot distance",30,0,1);
//TH1F* JetS_WZ_BSdChi2norm = new TH1F("JetS_WZ_BSdChi2norm","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW200_BSdChi2norm = new TH1F("JetS_LW200_BSdChi2norm","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW300_BSdChi2norm = new TH1F("JetS_LW300_BSdChi2norm","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW400_BSdChi2norm = new TH1F("JetS_LW400_BSdChi2norm","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW500_BSdChi2norm = new TH1F("JetS_LW500_BSdChi2norm","JetS Beam spot distance",30,0,1);
//Histograms for signal region DRC
TH1F* DRC_dataRunB_ppointS = new TH1F("DRC_dataRunB_ppointS","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_dataRunC_ppointS  = new TH1F("DRC_dataRunC_ppointS","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_ZLL_ppointS = new TH1F("DRC_ZLL_ppointS","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_TT_ppointS = new TH1F("DRC_TT_ppointS","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_W3J_ppointS = new TH1F("DRC_W3J_ppointS","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_W2J_ppointS = new TH1F("DRC_W2J_ppointS","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_W1J_ppointS = new TH1F("DRC_W1J_ppointS","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //DRC_TTZ_ppointS = new TH1F("//DRC_TTZ_ppointS","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //DRC_WW_ppointS = new TH1F("//DRC_WW_ppointS","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //DRC_WZ_ppointS = new TH1F("//DRC_WZ_ppointS","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_LW200_ppointS = new TH1F("DRC_LW200_ppointS","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_LW300_ppointS = new TH1F("DRC_LW300_ppointS","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_LW400_ppointS = new TH1F("DRC_LW400_ppointS","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_LW500_ppointS = new TH1F("DRC_LW500_ppointS","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_dataRunB_ppoint = new TH1F("DRC_dataRunB_ppoint","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_dataRunC_ppoint  = new TH1F("DRC_dataRunC_ppoint","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_ZLL_ppoint = new TH1F("DRC_ZLL_ppoint","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_TT_ppoint = new TH1F("DRC_TT_ppoint","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_W3J_ppoint = new TH1F("DRC_W3J_ppoint","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_W2J_ppoint = new TH1F("DRC_W2J_ppoint","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_W1J_ppoint = new TH1F("DRC_W1J_ppoint","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //DRC_TTZ_ppoint = new TH1F("//DRC_TTZ_ppoint","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //DRC_WW_ppoint = new TH1F("//DRC_WW_ppoint","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //DRC_WZ_ppoint = new TH1F("//DRC_WZ_ppoint","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_LW200_ppoint = new TH1F("DRC_LW200_ppoint","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_LW300_ppoint = new TH1F("DRC_LW300_ppoint","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_LW400_ppoint = new TH1F("DRC_LW400_ppoint","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_LW500_ppoint = new TH1F("DRC_LW500_ppoint","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_dataRunB_npv = new TH1F("DRC_dataRunB_npv","DRC Number of primary vertices",25,5,30);
TH1F* DRC_dataRunC_npv  = new TH1F("DRC_dataRunC_npv","DRC Number of primary vertices",25,5,30);
TH1F* DRC_ZLL_npv = new TH1F("DRC_ZLL_npv","DRC Number of primary vertices",25,5,30);
TH1F* DRC_TT_npv = new TH1F("DRC_TT_npv","DRC Number of primary vertices",25,5,30);
TH1F* DRC_W3J_npv = new TH1F("DRC_W3J_npv","DRC Number of primary vertices",25,5,30);
TH1F* DRC_W2J_npv = new TH1F("DRC_W2J_npv","DRC Number of primary vertices",25,5,30);
TH1F* DRC_W1J_npv = new TH1F("DRC_W1J_npv","DRC Number of primary vertices",25,5,30);
//TH1F* //DRC_TTZ_npv = new TH1F("//DRC_TTZ_npv","DRC Number of primary vertices",25,5,30);
//TH1F* //DRC_WW_npv = new TH1F("//DRC_WW_npv","DRC Number of primary vertices",25,5,30);
//TH1F* //DRC_WZ_npv = new TH1F("//DRC_WZ_npv","DRC Number of primary vertices",25,5,30);
TH1F* DRC_LW200_npv = new TH1F("DRC_LW200_npv","DRC Number of primary vertices",25,5,30);
TH1F* DRC_LW300_npv = new TH1F("DRC_LW300_npv","DRC Number of primary vertices",25,5,30);
TH1F* DRC_LW400_npv = new TH1F("DRC_LW400_npv","DRC Number of primary vertices",25,5,30);
TH1F* DRC_LW500_npv = new TH1F("DRC_LW500_npv","DRC Number of primary vertices",25,5,30);
TH1F* DRC_dataRunB_nsv = new TH1F("DRC_dataRunB_nsv","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_dataRunC_nsv  = new TH1F("DRC_dataRunC_nsv","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_ZLL_nsv = new TH1F("DRC_ZLL_nsv","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_TT_nsv = new TH1F("DRC_TT_nsv","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_W3J_nsv = new TH1F("DRC_W3J_nsv","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_W2J_nsv = new TH1F("DRC_W2J_nsv","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_W1J_nsv = new TH1F("DRC_W1J_nsv","DRC Number of secondary vertices",20,0,10);
//TH1F* //DRC_TTZ_nsv = new TH1F("//DRC_TTZ_nsv","DRC Number of secondary vertices",20,0,10);
//TH1F* //DRC_WW_nsv = new TH1F("//DRC_WW_nsv","DRC Number of secondary vertices",20,0,10);
//TH1F* //DRC_WZ_nsv = new TH1F("//DRC_WZ_nsv","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_LW200_nsv = new TH1F("DRC_LW200_nsv","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_LW300_nsv = new TH1F("DRC_LW300_nsv","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_LW400_nsv = new TH1F("DRC_LW400_nsv","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_LW500_nsv = new TH1F("DRC_LW500_nsv","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_dataRunB_svd = new TH1F("DRC_dataRunB_svd","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_dataRunC_svd  = new TH1F("DRC_dataRunC_svd","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_ZLL_svd = new TH1F("DRC_ZLL_svd","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_TT_svd = new TH1F("DRC_TT_svd","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_W3J_svd = new TH1F("DRC_W3J_svd","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_W2J_svd = new TH1F("DRC_W2J_svd","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_W1J_svd = new TH1F("DRC_W1J_svd","DRC secondary vertex displacement",30,0,1);
//TH1F* //DRC_TTZ_svd = new TH1F("//DRC_TTZ_svd","DRC secondary vertex displacement",30,0,1);
//TH1F* //DRC_WW_svd = new TH1F("//DRC_WW_svd","DRC secondary vertex displacement",30,0,1);
//TH1F* //DRC_WZ_svd = new TH1F("//DRC_WZ_svd","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_LW200_svd = new TH1F("DRC_LW200_svd","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_LW300_svd = new TH1F("DRC_LW300_svd","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_LW400_svd = new TH1F("DRC_LW400_svd","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_LW500_svd = new TH1F("DRC_LW500_svd","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_dataRunB_BSd = new TH1F("DRC_dataRunB_BSd","DRC Beam spot distance",30,0,1);
TH1F* DRC_dataRunC_BSd  = new TH1F("DRC_dataRunC_BSd","DRC Beam spot distance",30,0,1);
TH1F* DRC_ZLL_BSd = new TH1F("DRC_ZLL_BSd","DRC Beam spot distance",30,0,1);
TH1F* DRC_TT_BSd = new TH1F("DRC_TT_BSd","DRC Beam spot distance",30,0,1);
TH1F* DRC_W3J_BSd = new TH1F("DRC_W3J_BSd","DRC Beam spot distance",30,0,1);
TH1F* DRC_W2J_BSd = new TH1F("DRC_W2J_BSd","DRC Beam spot distance",30,0,1);
TH1F* DRC_W1J_BSd = new TH1F("DRC_W1J_BSd","DRC Beam spot distance",30,0,1);
//TH1F* DRC_TTZ_BSd = new TH1F("DRC_TTZ_BSd","DRC Beam spot distance",30,0,1);
//TH1F* DRC_WW_BSd = new TH1F("DRC_WW_BSd","DRC Beam spot distance",30,0,1);
//TH1F* DRC_WZ_BSd = new TH1F("DRC_WZ_BSd","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW200_BSd = new TH1F("DRC_LW200_BSd","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW300_BSd = new TH1F("DRC_LW300_BSd","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW400_BSd = new TH1F("DRC_LW400_BSd","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW500_BSd = new TH1F("DRC_LW500_BSd","DRC Beam spot distance",30,0,1);
TH1F* DRC_dataRunB_BSdChi2norm = new TH1F("DRC_dataRunB_BSdChi2norm","DRC Beam spot distance",30,0,1);
TH1F* DRC_dataRunC_BSdChi2norm  = new TH1F("DRC_dataRunC_BSdChi2norm","DRC Beam spot distance",30,0,1);
TH1F* DRC_ZLL_BSdChi2norm = new TH1F("DRC_ZLL_BSdChi2norm","DRC Beam spot distance",30,0,1);
TH1F* DRC_TT_BSdChi2norm = new TH1F("DRC_TT_BSdChi2norm","DRC Beam spot distance",30,0,1);
TH1F* DRC_W3J_BSdChi2norm = new TH1F("DRC_W3J_BSdChi2norm","DRC Beam spot distance",30,0,1);
TH1F* DRC_W2J_BSdChi2norm = new TH1F("DRC_W2J_BSdChi2norm","DRC Beam spot distance",30,0,1);
TH1F* DRC_W1J_BSdChi2norm = new TH1F("DRC_W1J_BSdChi2norm","DRC Beam spot distance",30,0,1);
//TH1F* DRC_TTZ_BSdChi2norm = new TH1F("DRC_TTZ_BSdChi2norm","DRC Beam spot distance",30,0,1);
//TH1F* DRC_WW_BSdChi2norm = new TH1F("DRC_WW_BSdChi2norm","DRC Beam spot distance",30,0,1);
//TH1F* DRC_WZ_BSdChi2norm = new TH1F("DRC_WZ_BSdChi2norm","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW200_BSdChi2norm = new TH1F("DRC_LW200_BSdChi2norm","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW300_BSdChi2norm = new TH1F("DRC_LW300_BSdChi2norm","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW400_BSdChi2norm = new TH1F("DRC_LW400_BSdChi2norm","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW500_BSdChi2norm = new TH1F("DRC_LW500_BSdChi2norm","DRC Beam spot distance",30,0,1);
//Histograms for signal region SG
TH1F* SG_dataRunB_ppointS = new TH1F("SG_dataRunB_ppointS","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_dataRunC_ppointS  = new TH1F("SG_dataRunC_ppointS","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_ZLL_ppointS = new TH1F("SG_ZLL_ppointS","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_TT_ppointS = new TH1F("SG_TT_ppointS","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_W3J_ppointS = new TH1F("SG_W3J_ppointS","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_W2J_ppointS = new TH1F("SG_W2J_ppointS","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_W1J_ppointS = new TH1F("SG_W1J_ppointS","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //SG_TTZ_ppointS = new TH1F("//SG_TTZ_ppointS","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //SG_WW_ppointS = new TH1F("//SG_WW_ppointS","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //SG_WZ_ppointS = new TH1F("//SG_WZ_ppointS","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_LW200_ppointS = new TH1F("SG_LW200_ppointS","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_LW300_ppointS = new TH1F("SG_LW300_ppointS","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_LW400_ppointS = new TH1F("SG_LW400_ppointS","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_LW500_ppointS = new TH1F("SG_LW500_ppointS","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_dataRunB_ppoint = new TH1F("SG_dataRunB_ppoint","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_dataRunC_ppoint  = new TH1F("SG_dataRunC_ppoint","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_ZLL_ppoint = new TH1F("SG_ZLL_ppoint","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_TT_ppoint = new TH1F("SG_TT_ppoint","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_W3J_ppoint = new TH1F("SG_W3J_ppoint","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_W2J_ppoint = new TH1F("SG_W2J_ppoint","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_W1J_ppoint = new TH1F("SG_W1J_ppoint","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //SG_TTZ_ppoint = new TH1F("//SG_TTZ_ppoint","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //SG_WW_ppoint = new TH1F("//SG_WW_ppoint","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //SG_WZ_ppoint = new TH1F("//SG_WZ_ppoint","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_LW200_ppoint = new TH1F("SG_LW200_ppoint","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_LW300_ppoint = new TH1F("SG_LW300_ppoint","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_LW400_ppoint = new TH1F("SG_LW400_ppoint","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_LW500_ppoint = new TH1F("SG_LW500_ppoint","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_dataRunB_npv = new TH1F("SG_dataRunB_npv","SG Number of primary vertices",25,5,30);
TH1F* SG_dataRunC_npv  = new TH1F("SG_dataRunC_npv","SG Number of primary vertices",25,5,30);
TH1F* SG_ZLL_npv = new TH1F("SG_ZLL_npv","SG Number of primary vertices",25,5,30);
TH1F* SG_TT_npv = new TH1F("SG_TT_npv","SG Number of primary vertices",25,5,30);
TH1F* SG_W3J_npv = new TH1F("SG_W3J_npv","SG Number of primary vertices",25,5,30);
TH1F* SG_W2J_npv = new TH1F("SG_W2J_npv","SG Number of primary vertices",25,5,30);
TH1F* SG_W1J_npv = new TH1F("SG_W1J_npv","SG Number of primary vertices",25,5,30);
//TH1F* //SG_TTZ_npv = new TH1F("//SG_TTZ_npv","SG Number of primary vertices",25,5,30);
//TH1F* //SG_WW_npv = new TH1F("//SG_WW_npv","SG Number of primary vertices",25,5,30);
//TH1F* //SG_WZ_npv = new TH1F("//SG_WZ_npv","SG Number of primary vertices",25,5,30);
TH1F* SG_LW200_npv = new TH1F("SG_LW200_npv","SG Number of primary vertices",25,5,30);
TH1F* SG_LW300_npv = new TH1F("SG_LW300_npv","SG Number of primary vertices",25,5,30);
TH1F* SG_LW400_npv = new TH1F("SG_LW400_npv","SG Number of primary vertices",25,5,30);
TH1F* SG_LW500_npv = new TH1F("SG_LW500_npv","SG Number of primary vertices",25,5,30);
TH1F* SG_dataRunB_nsv = new TH1F("SG_dataRunB_nsv","SG Number of secondary vertices",20,0,10);
TH1F* SG_dataRunC_nsv  = new TH1F("SG_dataRunC_nsv","SG Number of secondary vertices",20,0,10);
TH1F* SG_ZLL_nsv = new TH1F("SG_ZLL_nsv","SG Number of secondary vertices",20,0,10);
TH1F* SG_TT_nsv = new TH1F("SG_TT_nsv","SG Number of secondary vertices",20,0,10);
TH1F* SG_W3J_nsv = new TH1F("SG_W3J_nsv","SG Number of secondary vertices",20,0,10);
TH1F* SG_W2J_nsv = new TH1F("SG_W2J_nsv","SG Number of secondary vertices",20,0,10);
TH1F* SG_W1J_nsv = new TH1F("SG_W1J_nsv","SG Number of secondary vertices",20,0,10);
//TH1F* //SG_TTZ_nsv = new TH1F("//SG_TTZ_nsv","SG Number of secondary vertices",20,0,10);
//TH1F* //SG_WW_nsv = new TH1F("//SG_WW_nsv","SG Number of secondary vertices",20,0,10);
//TH1F* //SG_WZ_nsv = new TH1F("//SG_WZ_nsv","SG Number of secondary vertices",20,0,10);
TH1F* SG_LW200_nsv = new TH1F("SG_LW200_nsv","SG Number of secondary vertices",20,0,10);
TH1F* SG_LW300_nsv = new TH1F("SG_LW300_nsv","SG Number of secondary vertices",20,0,10);
TH1F* SG_LW400_nsv = new TH1F("SG_LW400_nsv","SG Number of secondary vertices",20,0,10);
TH1F* SG_LW500_nsv = new TH1F("SG_LW500_nsv","SG Number of secondary vertices",20,0,10);
TH1F* SG_dataRunB_svd = new TH1F("SG_dataRunB_svd","SG secondary vertex displacement",30,0,1);
TH1F* SG_dataRunC_svd  = new TH1F("SG_dataRunC_svd","SG secondary vertex displacement",30,0,1);
TH1F* SG_ZLL_svd = new TH1F("SG_ZLL_svd","SG secondary vertex displacement",30,0,1);
TH1F* SG_TT_svd = new TH1F("SG_TT_svd","SG secondary vertex displacement",30,0,1);
TH1F* SG_W3J_svd = new TH1F("SG_W3J_svd","SG secondary vertex displacement",30,0,1);
TH1F* SG_W2J_svd = new TH1F("SG_W2J_svd","SG secondary vertex displacement",30,0,1);
TH1F* SG_W1J_svd = new TH1F("SG_W1J_svd","SG secondary vertex displacement",30,0,1);
//TH1F* //SG_TTZ_svd = new TH1F("//SG_TTZ_svd","SG secondary vertex displacement",30,0,1);
//TH1F* //SG_WW_svd = new TH1F("//SG_WW_svd","SG secondary vertex displacement",30,0,1);
//TH1F* //SG_WZ_svd = new TH1F("//SG_WZ_svd","SG secondary vertex displacement",30,0,1);
TH1F* SG_LW200_svd = new TH1F("SG_LW200_svd","SG secondary vertex displacement",30,0,1);
TH1F* SG_LW300_svd = new TH1F("SG_LW300_svd","SG secondary vertex displacement",30,0,1);
TH1F* SG_LW400_svd = new TH1F("SG_LW400_svd","SG secondary vertex displacement",30,0,1);
TH1F* SG_LW500_svd = new TH1F("SG_LW500_svd","SG secondary vertex displacement",30,0,1);
TH1F* SG_dataRunB_BSd = new TH1F("SG_dataRunB_BSd","SG Beam spot distance",30,0,1);
TH1F* SG_dataRunC_BSd  = new TH1F("SG_dataRunC_BSd","SG Beam spot distance",30,0,1);
TH1F* SG_ZLL_BSd = new TH1F("SG_ZLL_BSd","SG Beam spot distance",30,0,1);
TH1F* SG_TT_BSd = new TH1F("SG_TT_BSd","SG Beam spot distance",30,0,1);
TH1F* SG_W3J_BSd = new TH1F("SG_W3J_BSd","SG Beam spot distance",30,0,1);
TH1F* SG_W2J_BSd = new TH1F("SG_W2J_BSd","SG Beam spot distance",30,0,1);
TH1F* SG_W1J_BSd = new TH1F("SG_W1J_BSd","SG Beam spot distance",30,0,1);
//TH1F* SG_TTZ_BSd = new TH1F("SG_TTZ_BSd","SG Beam spot distance",30,0,1);
//TH1F* SG_WW_BSd = new TH1F("SG_WW_BSd","SG Beam spot distance",30,0,1);
//TH1F* SG_WZ_BSd = new TH1F("SG_WZ_BSd","SG Beam spot distance",30,0,1);
TH1F* SG_LW200_BSd = new TH1F("SG_LW200_BSd","SG Beam spot distance",30,0,1);
TH1F* SG_LW300_BSd = new TH1F("SG_LW300_BSd","SG Beam spot distance",30,0,1);
TH1F* SG_LW400_BSd = new TH1F("SG_LW400_BSd","SG Beam spot distance",30,0,1);
TH1F* SG_LW500_BSd = new TH1F("SG_LW500_BSd","SG Beam spot distance",30,0,1);
TH1F* SG_dataRunB_BSdChi2norm = new TH1F("SG_dataRunB_BSdChi2norm","SG Beam spot distance",30,0,1);
TH1F* SG_dataRunC_BSdChi2norm  = new TH1F("SG_dataRunC_BSdChi2norm","SG Beam spot distance",30,0,1);
TH1F* SG_ZLL_BSdChi2norm = new TH1F("SG_ZLL_BSdChi2norm","SG Beam spot distance",30,0,1);
TH1F* SG_TT_BSdChi2norm = new TH1F("SG_TT_BSdChi2norm","SG Beam spot distance",30,0,1);
TH1F* SG_W3J_BSdChi2norm = new TH1F("SG_W3J_BSdChi2norm","SG Beam spot distance",30,0,1);
TH1F* SG_W2J_BSdChi2norm = new TH1F("SG_W2J_BSdChi2norm","SG Beam spot distance",30,0,1);
TH1F* SG_W1J_BSdChi2norm = new TH1F("SG_W1J_BSdChi2norm","SG Beam spot distance",30,0,1);
//TH1F* SG_TTZ_BSdChi2norm = new TH1F("SG_TTZ_BSdChi2norm","SG Beam spot distance",30,0,1);
//TH1F* SG_WW_BSdChi2norm = new TH1F("SG_WW_BSdChi2norm","SG Beam spot distance",30,0,1);
//TH1F* SG_WZ_BSdChi2norm = new TH1F("SG_WZ_BSdChi2norm","SG Beam spot distance",30,0,1);
TH1F* SG_LW200_BSdChi2norm = new TH1F("SG_LW200_BSdChi2norm","SG Beam spot distance",30,0,1);
TH1F* SG_LW300_BSdChi2norm = new TH1F("SG_LW300_BSdChi2norm","SG Beam spot distance",30,0,1);
TH1F* SG_LW400_BSdChi2norm = new TH1F("SG_LW400_BSdChi2norm","SG Beam spot distance",30,0,1);
TH1F* SG_LW500_BSdChi2norm = new TH1F("SG_LW500_BSdChi2norm","SG Beam spot distance",30,0,1);
//Histograms for signal region IPP
TH1F* IPP_dataRunB_ppointS = new TH1F("IPP_dataRunB_ppointS","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_dataRunC_ppointS  = new TH1F("IPP_dataRunC_ppointS","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_ZLL_ppointS = new TH1F("IPP_ZLL_ppointS","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_TT_ppointS = new TH1F("IPP_TT_ppointS","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_W3J_ppointS = new TH1F("IPP_W3J_ppointS","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_W2J_ppointS = new TH1F("IPP_W2J_ppointS","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_W1J_ppointS = new TH1F("IPP_W1J_ppointS","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //IPP_TTZ_ppointS = new TH1F("//IPP_TTZ_ppointS","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //IPP_WW_ppointS = new TH1F("//IPP_WW_ppointS","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //IPP_WZ_ppointS = new TH1F("//IPP_WZ_ppointS","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_LW200_ppointS = new TH1F("IPP_LW200_ppointS","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_LW300_ppointS = new TH1F("IPP_LW300_ppointS","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_LW400_ppointS = new TH1F("IPP_LW400_ppointS","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_LW500_ppointS = new TH1F("IPP_LW500_ppointS","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_dataRunB_ppoint = new TH1F("IPP_dataRunB_ppoint","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_dataRunC_ppoint  = new TH1F("IPP_dataRunC_ppoint","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_ZLL_ppoint = new TH1F("IPP_ZLL_ppoint","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_TT_ppoint = new TH1F("IPP_TT_ppoint","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_W3J_ppoint = new TH1F("IPP_W3J_ppoint","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_W2J_ppoint = new TH1F("IPP_W2J_ppoint","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_W1J_ppoint = new TH1F("IPP_W1J_ppoint","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //IPP_TTZ_ppoint = new TH1F("//IPP_TTZ_ppoint","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //IPP_WW_ppoint = new TH1F("//IPP_WW_ppoint","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //IPP_WZ_ppoint = new TH1F("//IPP_WZ_ppoint","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_LW200_ppoint = new TH1F("IPP_LW200_ppoint","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_LW300_ppoint = new TH1F("IPP_LW300_ppoint","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_LW400_ppoint = new TH1F("IPP_LW400_ppoint","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_LW500_ppoint = new TH1F("IPP_LW500_ppoint","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_dataRunB_npv = new TH1F("IPP_dataRunB_npv","IPP Number of primary vertices",25,5,30);
TH1F* IPP_dataRunC_npv  = new TH1F("IPP_dataRunC_npv","IPP Number of primary vertices",25,5,30);
TH1F* IPP_ZLL_npv = new TH1F("IPP_ZLL_npv","IPP Number of primary vertices",25,5,30);
TH1F* IPP_TT_npv = new TH1F("IPP_TT_npv","IPP Number of primary vertices",25,5,30);
TH1F* IPP_W3J_npv = new TH1F("IPP_W3J_npv","IPP Number of primary vertices",25,5,30);
TH1F* IPP_W2J_npv = new TH1F("IPP_W2J_npv","IPP Number of primary vertices",25,5,30);
TH1F* IPP_W1J_npv = new TH1F("IPP_W1J_npv","IPP Number of primary vertices",25,5,30);
//TH1F* //IPP_TTZ_npv = new TH1F("//IPP_TTZ_npv","IPP Number of primary vertices",25,5,30);
//TH1F* //IPP_WW_npv = new TH1F("//IPP_WW_npv","IPP Number of primary vertices",25,5,30);
//TH1F* //IPP_WZ_npv = new TH1F("//IPP_WZ_npv","IPP Number of primary vertices",25,5,30);
TH1F* IPP_LW200_npv = new TH1F("IPP_LW200_npv","IPP Number of primary vertices",25,5,30);
TH1F* IPP_LW300_npv = new TH1F("IPP_LW300_npv","IPP Number of primary vertices",25,5,30);
TH1F* IPP_LW400_npv = new TH1F("IPP_LW400_npv","IPP Number of primary vertices",25,5,30);
TH1F* IPP_LW500_npv = new TH1F("IPP_LW500_npv","IPP Number of primary vertices",25,5,30);
TH1F* IPP_dataRunB_nsv = new TH1F("IPP_dataRunB_nsv","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_dataRunC_nsv  = new TH1F("IPP_dataRunC_nsv","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_ZLL_nsv = new TH1F("IPP_ZLL_nsv","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_TT_nsv = new TH1F("IPP_TT_nsv","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_W3J_nsv = new TH1F("IPP_W3J_nsv","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_W2J_nsv = new TH1F("IPP_W2J_nsv","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_W1J_nsv = new TH1F("IPP_W1J_nsv","IPP Number of secondary vertices",20,0,10);
//TH1F* //IPP_TTZ_nsv = new TH1F("//IPP_TTZ_nsv","IPP Number of secondary vertices",20,0,10);
//TH1F* //IPP_WW_nsv = new TH1F("//IPP_WW_nsv","IPP Number of secondary vertices",20,0,10);
//TH1F* //IPP_WZ_nsv = new TH1F("//IPP_WZ_nsv","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_LW200_nsv = new TH1F("IPP_LW200_nsv","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_LW300_nsv = new TH1F("IPP_LW300_nsv","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_LW400_nsv = new TH1F("IPP_LW400_nsv","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_LW500_nsv = new TH1F("IPP_LW500_nsv","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_dataRunB_svd = new TH1F("IPP_dataRunB_svd","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_dataRunC_svd  = new TH1F("IPP_dataRunC_svd","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_ZLL_svd = new TH1F("IPP_ZLL_svd","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_TT_svd = new TH1F("IPP_TT_svd","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_W3J_svd = new TH1F("IPP_W3J_svd","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_W2J_svd = new TH1F("IPP_W2J_svd","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_W1J_svd = new TH1F("IPP_W1J_svd","IPP secondary vertex displacement",30,0,1);
//TH1F* //IPP_TTZ_svd = new TH1F("//IPP_TTZ_svd","IPP secondary vertex displacement",30,0,1);
//TH1F* //IPP_WW_svd = new TH1F("//IPP_WW_svd","IPP secondary vertex displacement",30,0,1);
//TH1F* //IPP_WZ_svd = new TH1F("//IPP_WZ_svd","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_LW200_svd = new TH1F("IPP_LW200_svd","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_LW300_svd = new TH1F("IPP_LW300_svd","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_LW400_svd = new TH1F("IPP_LW400_svd","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_LW500_svd = new TH1F("IPP_LW500_svd","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_dataRunB_BSd = new TH1F("IPP_dataRunB_BSd","IPP Beam spot distance",30,0,1);
TH1F* IPP_dataRunC_BSd  = new TH1F("IPP_dataRunC_BSd","IPP Beam spot distance",30,0,1);
TH1F* IPP_ZLL_BSd = new TH1F("IPP_ZLL_BSd","IPP Beam spot distance",30,0,1);
TH1F* IPP_TT_BSd = new TH1F("IPP_TT_BSd","IPP Beam spot distance",30,0,1);
TH1F* IPP_W3J_BSd = new TH1F("IPP_W3J_BSd","IPP Beam spot distance",30,0,1);
TH1F* IPP_W2J_BSd = new TH1F("IPP_W2J_BSd","IPP Beam spot distance",30,0,1);
TH1F* IPP_W1J_BSd = new TH1F("IPP_W1J_BSd","IPP Beam spot distance",30,0,1);
//TH1F* IPP_TTZ_BSd = new TH1F("IPP_TTZ_BSd","IPP Beam spot distance",30,0,1);
//TH1F* IPP_WW_BSd = new TH1F("IPP_WW_BSd","IPP Beam spot distance",30,0,1);
//TH1F* IPP_WZ_BSd = new TH1F("IPP_WZ_BSd","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW200_BSd = new TH1F("IPP_LW200_BSd","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW300_BSd = new TH1F("IPP_LW300_BSd","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW400_BSd = new TH1F("IPP_LW400_BSd","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW500_BSd = new TH1F("IPP_LW500_BSd","IPP Beam spot distance",30,0,1);
TH1F* IPP_dataRunB_BSdChi2norm = new TH1F("IPP_dataRunB_BSdChi2norm","IPP Beam spot distance",30,0,1);
TH1F* IPP_dataRunC_BSdChi2norm  = new TH1F("IPP_dataRunC_BSdChi2norm","IPP Beam spot distance",30,0,1);
TH1F* IPP_ZLL_BSdChi2norm = new TH1F("IPP_ZLL_BSdChi2norm","IPP Beam spot distance",30,0,1);
TH1F* IPP_TT_BSdChi2norm = new TH1F("IPP_TT_BSdChi2norm","IPP Beam spot distance",30,0,1);
TH1F* IPP_W3J_BSdChi2norm = new TH1F("IPP_W3J_BSdChi2norm","IPP Beam spot distance",30,0,1);
TH1F* IPP_W2J_BSdChi2norm = new TH1F("IPP_W2J_BSdChi2norm","IPP Beam spot distance",30,0,1);
TH1F* IPP_W1J_BSdChi2norm = new TH1F("IPP_W1J_BSdChi2norm","IPP Beam spot distance",30,0,1);
//TH1F* IPP_TTZ_BSdChi2norm = new TH1F("IPP_TTZ_BSdChi2norm","IPP Beam spot distance",30,0,1);
//TH1F* IPP_WW_BSdChi2norm = new TH1F("IPP_WW_BSdChi2norm","IPP Beam spot distance",30,0,1);
//TH1F* IPP_WZ_BSdChi2norm = new TH1F("IPP_WZ_BSdChi2norm","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW200_BSdChi2norm = new TH1F("IPP_LW200_BSdChi2norm","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW300_BSdChi2norm = new TH1F("IPP_LW300_BSdChi2norm","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW400_BSdChi2norm = new TH1F("IPP_LW400_BSdChi2norm","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW500_BSdChi2norm = new TH1F("IPP_LW500_BSdChi2norm","IPP Beam spot distance",30,0,1);
//////////////////Histograms ofr control region
//Histograms for signal region TF
TH1F* TF_dataRunB_ppointS_cr = new TH1F("TF_dataRunB_ppointS_cr","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_dataRunC_ppointS_cr = new TH1F("TF_dataRunC_ppointS_cr","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_ZLL_ppointS_cr = new TH1F("TF_ZLL_ppointS_cr","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_TT_ppointS_cr = new TH1F("TF_TT_ppointS_cr","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_W3J_ppointS_cr = new TH1F("TF_W3J_ppointS_cr","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_W2J_ppointS_cr = new TH1F("TF_W2J_ppointS_cr","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_W1J_ppointS_cr = new TH1F("TF_W1J_ppointS_cr","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //TF_TTZ_ppointS_cr = new TH1F("//TF_TTZ_ppointS_cr","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //TF_WW_ppointS_cr = new TH1F("//TF_WW_ppointS_cr","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //TF_WZ_ppointS_cr = new TH1F("//TF_WZ_ppointS_cr","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_LW200_ppointS_cr = new TH1F("TF_LW200_ppointS_cr","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_LW300_ppointS_cr = new TH1F("TF_LW300_ppointS_cr","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_LW400_ppointS_cr = new TH1F("TF_LW400_ppointS_cr","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_LW500_ppointS_cr = new TH1F("TF_LW500_ppointS_cr","TF Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TF_dataRunB_ppoint_cr = new TH1F("TF_dataRunB_ppoint_cr","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_dataRunC_ppoint_cr = new TH1F("TF_dataRunC_ppoint_cr","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_ZLL_ppoint_cr = new TH1F("TF_ZLL_ppoint_cr","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_TT_ppoint_cr = new TH1F("TF_TT_ppoint_cr","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_W3J_ppoint_cr = new TH1F("TF_W3J_ppoint_cr","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_W2J_ppoint_cr = new TH1F("TF_W2J_ppoint_cr","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_W1J_ppoint_cr = new TH1F("TF_W1J_ppoint_cr","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TF_TTZ_ppoint_cr = new TH1F("//TF_TTZ_ppoint_cr","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TF_WW_ppoint_cr = new TH1F("//TF_WW_ppoint_cr","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TF_WZ_ppoint_cr = new TH1F("//TF_WZ_ppoint_cr","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_LW200_ppoint_cr = new TH1F("TF_LW200_ppoint_cr","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_LW300_ppoint_cr = new TH1F("TF_LW300_ppoint_cr","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_LW400_ppoint_cr = new TH1F("TF_LW400_ppoint_cr","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_LW500_ppoint_cr = new TH1F("TF_LW500_ppoint_cr","TF Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TF_dataRunB_npv_cr = new TH1F("TF_dataRunB_npv_cr","TF Number of primary vertices",25,5,30);
TH1F* TF_dataRunC_npv_cr = new TH1F("TF_dataRunC_npv_cr","TF Number of primary vertices",25,5,30);
TH1F* TF_ZLL_npv_cr = new TH1F("TF_ZLL_npv_cr","TF Number of primary vertices",25,5,30);
TH1F* TF_TT_npv_cr = new TH1F("TF_TT_npv_cr","TF Number of primary vertices",25,5,30);
TH1F* TF_W3J_npv_cr = new TH1F("TF_W3J_npv_cr","TF Number of primary vertices",25,5,30);
TH1F* TF_W2J_npv_cr = new TH1F("TF_W2J_npv_cr","TF Number of primary vertices",25,5,30);
TH1F* TF_W1J_npv_cr = new TH1F("TF_W1J_npv_cr","TF Number of primary vertices",25,5,30);
//TH1F* //TF_TTZ_npv_cr = new TH1F("//TF_TTZ_npv_cr","TF Number of primary vertices",25,5,30);
//TH1F* //TF_WW_npv_cr = new TH1F("//TF_WW_npv_cr","TF Number of primary vertices",25,5,30);
//TH1F* //TF_WZ_npv_cr = new TH1F("//TF_WZ_npv_cr","TF Number of primary vertices",25,5,30);
TH1F* TF_LW200_npv_cr = new TH1F("TF_LW200_npv_cr","TF Number of primary vertices",25,5,30);
TH1F* TF_LW300_npv_cr = new TH1F("TF_LW300_npv_cr","TF Number of primary vertices",25,5,30);
TH1F* TF_LW400_npv_cr = new TH1F("TF_LW400_npv_cr","TF Number of primary vertices",25,5,30);
TH1F* TF_LW500_npv_cr = new TH1F("TF_LW500_npv_cr","TF Number of primary vertices",25,5,30);
TH1F* TF_dataRunB_nsv_cr = new TH1F("TF_dataRunB_nsv_cr","TF Number of secondary vertices",20,0,10);
TH1F* TF_dataRunC_nsv_cr = new TH1F("TF_dataRunC_nsv_cr","TF Number of secondary vertices",20,0,10);
TH1F* TF_ZLL_nsv_cr = new TH1F("TF_ZLL_nsv_cr","TF Number of secondary vertices",20,0,10);
TH1F* TF_TT_nsv_cr = new TH1F("TF_TT_nsv_cr","TF Number of secondary vertices",20,0,10);
TH1F* TF_W3J_nsv_cr = new TH1F("TF_W3J_nsv_cr","TF Number of secondary vertices",20,0,10);
TH1F* TF_W2J_nsv_cr = new TH1F("TF_W2J_nsv_cr","TF Number of secondary vertices",20,0,10);
TH1F* TF_W1J_nsv_cr = new TH1F("TF_W1J_nsv_cr","TF Number of secondary vertices",20,0,10);
//TH1F* //TF_TTZ_nsv_cr = new TH1F("//TF_TTZ_nsv_cr","TF Number of secondary vertices",20,0,10);
//TH1F* //TF_WW_nsv_cr = new TH1F("//TF_WW_nsv_cr","TF Number of secondary vertices",20,0,10);
//TH1F* //TF_WZ_nsv_cr = new TH1F("//TF_WZ_nsv_cr","TF Number of secondary vertices",20,0,10);
TH1F* TF_LW200_nsv_cr = new TH1F("TF_LW200_nsv_cr","TF Number of secondary vertices",20,0,10);
TH1F* TF_LW300_nsv_cr = new TH1F("TF_LW300_nsv_cr","TF Number of secondary vertices",20,0,10);
TH1F* TF_LW400_nsv_cr = new TH1F("TF_LW400_nsv_cr","TF Number of secondary vertices",20,0,10);
TH1F* TF_LW500_nsv_cr = new TH1F("TF_LW500_nsv_cr","TF Number of secondary vertices",20,0,10);
TH1F* TF_dataRunB_svd_cr = new TH1F("TF_dataRunB_svd_cr","TF secondary vertex displacement",30,0,1);
TH1F* TF_dataRunC_svd_cr = new TH1F("TF_dataRunC_svd_cr","TF secondary vertex displacement",30,0,1);
TH1F* TF_ZLL_svd_cr = new TH1F("TF_ZLL_svd_cr","TF secondary vertex displacement",30,0,1);
TH1F* TF_TT_svd_cr = new TH1F("TF_TT_svd_cr","TF secondary vertex displacement",30,0,1);
TH1F* TF_W3J_svd_cr = new TH1F("TF_W3J_svd_cr","TF secondary vertex displacement",30,0,1);
TH1F* TF_W2J_svd_cr = new TH1F("TF_W2J_svd_cr","TF secondary vertex displacement",30,0,1);
TH1F* TF_W1J_svd_cr = new TH1F("TF_W1J_svd_cr","TF secondary vertex displacement",30,0,1);
//TH1F* //TF_TTZ_svd_cr = new TH1F("//TF_TTZ_svd_cr","TF secondary vertex displacement",30,0,1);
//TH1F* //TF_WW_svd_cr = new TH1F("//TF_WW_svd_cr","TF secondary vertex displacement",30,0,1);
//TH1F* //TF_WZ_svd_cr = new TH1F("//TF_WZ_svd_cr","TF secondary vertex displacement",30,0,1);
TH1F* TF_LW200_svd_cr = new TH1F("TF_LW200_svd_cr","TF secondary vertex displacement",30,0,1);
TH1F* TF_LW300_svd_cr = new TH1F("TF_LW300_svd_cr","TF secondary vertex displacement",30,0,1);
TH1F* TF_LW400_svd_cr = new TH1F("TF_LW400_svd_cr","TF secondary vertex displacement",30,0,1);
TH1F* TF_LW500_svd_cr = new TH1F("TF_LW500_svd_cr","TF secondary vertex displacement",30,0,1);
TH1F* TF_dataRunB_BSd_cr = new TH1F("TF_dataRunB_BSd_cr","TF Beam spot distance",30,0,1);
TH1F* TF_dataRunC_BSd_cr = new TH1F("TF_dataRunC_BSd_cr","TF Beam spot distance",30,0,1);
TH1F* TF_ZLL_BSd_cr = new TH1F("TF_ZLL_BSd_cr","TF Beam spot distance",30,0,1);
TH1F* TF_TT_BSd_cr = new TH1F("TF_TT_BSd_cr","TF Beam spot distance",30,0,1);
TH1F* TF_W3J_BSd_cr = new TH1F("TF_W3J_BSd_cr","TF Beam spot distance",30,0,1);
TH1F* TF_W2J_BSd_cr = new TH1F("TF_W2J_BSd_cr","TF Beam spot distance",30,0,1);
TH1F* TF_W1J_BSd_cr = new TH1F("TF_W1J_BSd_cr","TF Beam spot distance",30,0,1);
//TH1F* TF_TTZ_BSd_cr = new TH1F("TF_TTZ_BSd_cr","TF Beam spot distance",30,0,1);
//TH1F* TF_WW_BSd_cr = new TH1F("TF_WW_BSd_cr","TF Beam spot distance",30,0,1);
//TH1F* TF_WZ_BSd_cr = new TH1F("TF_WZ_BSd_cr","TF Beam spot distance",30,0,1);
TH1F* TF_LW200_BSd_cr = new TH1F("TF_LW200_BSd_cr","TF Beam spot distance",30,0,1);
TH1F* TF_LW300_BSd_cr = new TH1F("TF_LW300_BSd_cr","TF Beam spot distance",30,0,1);
TH1F* TF_LW400_BSd_cr = new TH1F("TF_LW400_BSd_cr","TF Beam spot distance",30,0,1);
TH1F* TF_LW500_BSd_cr = new TH1F("TF_LW500_BSd_cr","TF Beam spot distance",30,0,1);
TH1F* TF_dataRunB_BSdChi2norm_cr = new TH1F("TF_dataRunB_BSdChi2norm_cr","TF Beam spot distance",30,0,1);
TH1F* TF_dataRunC_BSdChi2norm_cr = new TH1F("TF_dataRunC_BSdChi2norm_cr","TF Beam spot distance",30,0,1);
TH1F* TF_ZLL_BSdChi2norm_cr = new TH1F("TF_ZLL_BSdChi2norm_cr","TF Beam spot distance",30,0,1);
TH1F* TF_TT_BSdChi2norm_cr = new TH1F("TF_TT_BSdChi2norm_cr","TF Beam spot distance",30,0,1);
TH1F* TF_W3J_BSdChi2norm_cr = new TH1F("TF_W3J_BSdChi2norm_cr","TF Beam spot distance",30,0,1);
TH1F* TF_W2J_BSdChi2norm_cr = new TH1F("TF_W2J_BSdChi2norm_cr","TF Beam spot distance",30,0,1);
TH1F* TF_W1J_BSdChi2norm_cr = new TH1F("TF_W1J_BSdChi2norm_cr","TF Beam spot distance",30,0,1);
//TH1F* TF_TTZ_BSdChi2norm_cr = new TH1F("TF_TTZ_BSdChi2norm_cr","TF Beam spot distance",30,0,1);
//TH1F* TF_WW_BSdChi2norm_cr = new TH1F("TF_WW_BSdChi2norm_cr","TF Beam spot distance",30,0,1);
//TH1F* TF_WZ_BSdChi2norm_cr = new TH1F("TF_WZ_BSdChi2norm_cr","TF Beam spot distance",30,0,1);
TH1F* TF_LW200_BSdChi2norm_cr = new TH1F("TF_LW200_BSdChi2norm_cr","TF Beam spot distance",30,0,1);
TH1F* TF_LW300_BSdChi2norm_cr = new TH1F("TF_LW300_BSdChi2norm_cr","TF Beam spot distance",30,0,1);
TH1F* TF_LW400_BSdChi2norm_cr = new TH1F("TF_LW400_BSdChi2norm_cr","TF Beam spot distance",30,0,1);
TH1F* TF_LW500_BSdChi2norm_cr = new TH1F("TF_LW500_BSdChi2norm_cr","TF Beam spot distance",30,0,1);
//Histograms for signal region TO
TH1F* TO_dataRunB_ppointS_cr = new TH1F("TO_dataRunB_ppointS_cr","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_dataRunC_ppointS_cr = new TH1F("TO_dataRunC_ppointS_cr","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_ZLL_ppointS_cr = new TH1F("TO_ZLL_ppointS_cr","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_TT_ppointS_cr = new TH1F("TO_TT_ppointS_cr","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_W3J_ppointS_cr = new TH1F("TO_W3J_ppointS_cr","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_W2J_ppointS_cr = new TH1F("TO_W2J_ppointS_cr","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_W1J_ppointS_cr = new TH1F("TO_W1J_ppointS_cr","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //TO_TTZ_ppointS_cr = new TH1F("//TO_TTZ_ppointS_cr","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //TO_WW_ppointS_cr = new TH1F("//TO_WW_ppointS_cr","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //TO_WZ_ppointS_cr = new TH1F("//TO_WZ_ppointS_cr","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_LW200_ppointS_cr = new TH1F("TO_LW200_ppointS_cr","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_LW300_ppointS_cr = new TH1F("TO_LW300_ppointS_cr","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_LW400_ppointS_cr = new TH1F("TO_LW400_ppointS_cr","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_LW500_ppointS_cr = new TH1F("TO_LW500_ppointS_cr","TO Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* TO_dataRunB_ppoint_cr = new TH1F("TO_dataRunB_ppoint_cr","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_dataRunC_ppoint_cr = new TH1F("TO_dataRunC_ppoint_cr","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_ZLL_ppoint_cr = new TH1F("TO_ZLL_ppoint_cr","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_TT_ppoint_cr = new TH1F("TO_TT_ppoint_cr","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_W3J_ppoint_cr = new TH1F("TO_W3J_ppoint_cr","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_W2J_ppoint_cr = new TH1F("TO_W2J_ppoint_cr","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_W1J_ppoint_cr = new TH1F("TO_W1J_ppoint_cr","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TO_TTZ_ppoint_cr = new TH1F("//TO_TTZ_ppoint_cr","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TO_WW_ppoint_cr = new TH1F("//TO_WW_ppoint_cr","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //TO_WZ_ppoint_cr = new TH1F("//TO_WZ_ppoint_cr","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_LW200_ppoint_cr = new TH1F("TO_LW200_ppoint_cr","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_LW300_ppoint_cr = new TH1F("TO_LW300_ppoint_cr","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_LW400_ppoint_cr = new TH1F("TO_LW400_ppoint_cr","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_LW500_ppoint_cr = new TH1F("TO_LW500_ppoint_cr","TO Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* TO_dataRunB_npv_cr = new TH1F("TO_dataRunB_npv_cr","TO Number of primary vertices",25,5,30);
TH1F* TO_dataRunC_npv_cr = new TH1F("TO_dataRunC_npv_cr","TO Number of primary vertices",25,5,30);
TH1F* TO_ZLL_npv_cr = new TH1F("TO_ZLL_npv_cr","TO Number of primary vertices",25,5,30);
TH1F* TO_TT_npv_cr = new TH1F("TO_TT_npv_cr","TO Number of primary vertices",25,5,30);
TH1F* TO_W3J_npv_cr = new TH1F("TO_W3J_npv_cr","TO Number of primary vertices",25,5,30);
TH1F* TO_W2J_npv_cr = new TH1F("TO_W2J_npv_cr","TO Number of primary vertices",25,5,30);
TH1F* TO_W1J_npv_cr = new TH1F("TO_W1J_npv_cr","TO Number of primary vertices",25,5,30);
//TH1F* //TO_TTZ_npv_cr = new TH1F("//TO_TTZ_npv_cr","TO Number of primary vertices",25,5,30);
//TH1F* //TO_WW_npv_cr = new TH1F("//TO_WW_npv_cr","TO Number of primary vertices",25,5,30);
//TH1F* //TO_WZ_npv_cr = new TH1F("//TO_WZ_npv_cr","TO Number of primary vertices",25,5,30);
TH1F* TO_LW200_npv_cr = new TH1F("TO_LW200_npv_cr","TO Number of primary vertices",25,5,30);
TH1F* TO_LW300_npv_cr = new TH1F("TO_LW300_npv_cr","TO Number of primary vertices",25,5,30);
TH1F* TO_LW400_npv_cr = new TH1F("TO_LW400_npv_cr","TO Number of primary vertices",25,5,30);
TH1F* TO_LW500_npv_cr = new TH1F("TO_LW500_npv_cr","TO Number of primary vertices",25,5,30);
TH1F* TO_dataRunB_nsv_cr = new TH1F("TO_dataRunB_nsv_cr","TO Number of secondary vertices",20,0,10);
TH1F* TO_dataRunC_nsv_cr = new TH1F("TO_dataRunC_nsv_cr","TO Number of secondary vertices",20,0,10);
TH1F* TO_ZLL_nsv_cr = new TH1F("TO_ZLL_nsv_cr","TO Number of secondary vertices",20,0,10);
TH1F* TO_TT_nsv_cr = new TH1F("TO_TT_nsv_cr","TO Number of secondary vertices",20,0,10);
TH1F* TO_W3J_nsv_cr = new TH1F("TO_W3J_nsv_cr","TO Number of secondary vertices",20,0,10);
TH1F* TO_W2J_nsv_cr = new TH1F("TO_W2J_nsv_cr","TO Number of secondary vertices",20,0,10);
TH1F* TO_W1J_nsv_cr = new TH1F("TO_W1J_nsv_cr","TO Number of secondary vertices",20,0,10);
//TH1F* //TO_TTZ_nsv_cr = new TH1F("//TO_TTZ_nsv_cr","TO Number of secondary vertices",20,0,10);
//TH1F* //TO_WW_nsv_cr = new TH1F("//TO_WW_nsv_cr","TO Number of secondary vertices",20,0,10);
//TH1F* //TO_WZ_nsv_cr = new TH1F("//TO_WZ_nsv_cr","TO Number of secondary vertices",20,0,10);
TH1F* TO_LW200_nsv_cr = new TH1F("TO_LW200_nsv_cr","TO Number of secondary vertices",20,0,10);
TH1F* TO_LW300_nsv_cr = new TH1F("TO_LW300_nsv_cr","TO Number of secondary vertices",20,0,10);
TH1F* TO_LW400_nsv_cr = new TH1F("TO_LW400_nsv_cr","TO Number of secondary vertices",20,0,10);
TH1F* TO_LW500_nsv_cr = new TH1F("TO_LW500_nsv_cr","TO Number of secondary vertices",20,0,10);
TH1F* TO_dataRunB_svd_cr = new TH1F("TO_dataRunB_svd_cr","TO secondary vertex displacement",30,0,1);
TH1F* TO_dataRunC_svd_cr = new TH1F("TO_dataRunC_svd_cr","TO secondary vertex displacement",30,0,1);
TH1F* TO_ZLL_svd_cr = new TH1F("TO_ZLL_svd_cr","TO secondary vertex displacement",30,0,1);
TH1F* TO_TT_svd_cr = new TH1F("TO_TT_svd_cr","TO secondary vertex displacement",30,0,1);
TH1F* TO_W3J_svd_cr = new TH1F("TO_W3J_svd_cr","TO secondary vertex displacement",30,0,1);
TH1F* TO_W2J_svd_cr = new TH1F("TO_W2J_svd_cr","TO secondary vertex displacement",30,0,1);
TH1F* TO_W1J_svd_cr = new TH1F("TO_W1J_svd_cr","TO secondary vertex displacement",30,0,1);
//TH1F* //TO_TTZ_svd_cr = new TH1F("//TO_TTZ_svd_cr","TO secondary vertex displacement",30,0,1);
//TH1F* //TO_WW_svd_cr = new TH1F("//TO_WW_svd_cr","TO secondary vertex displacement",30,0,1);
//TH1F* //TO_WZ_svd_cr = new TH1F("//TO_WZ_svd_cr","TO secondary vertex displacement",30,0,1);
TH1F* TO_LW200_svd_cr = new TH1F("TO_LW200_svd_cr","TO secondary vertex displacement",30,0,1);
TH1F* TO_LW300_svd_cr = new TH1F("TO_LW300_svd_cr","TO secondary vertex displacement",30,0,1);
TH1F* TO_LW400_svd_cr = new TH1F("TO_LW400_svd_cr","TO secondary vertex displacement",30,0,1);
TH1F* TO_LW500_svd_cr = new TH1F("TO_LW500_svd_cr","TO secondary vertex displacement",30,0,1);
TH1F* TO_dataRunB_BSd_cr = new TH1F("TO_dataRunB_BSd_cr","TO Beam spot distance",30,0,1);
TH1F* TO_dataRunC_BSd_cr = new TH1F("TO_dataRunC_BSd_cr","TO Beam spot distance",30,0,1);
TH1F* TO_ZLL_BSd_cr = new TH1F("TO_ZLL_BSd_cr","TO Beam spot distance",30,0,1);
TH1F* TO_TT_BSd_cr = new TH1F("TO_TT_BSd_cr","TO Beam spot distance",30,0,1);
TH1F* TO_W3J_BSd_cr = new TH1F("TO_W3J_BSd_cr","TO Beam spot distance",30,0,1);
TH1F* TO_W2J_BSd_cr = new TH1F("TO_W2J_BSd_cr","TO Beam spot distance",30,0,1);
TH1F* TO_W1J_BSd_cr = new TH1F("TO_W1J_BSd_cr","TO Beam spot distance",30,0,1);
//TH1F* TO_TTZ_BSd_cr = new TH1F("TO_TTZ_BSd_cr","TO Beam spot distance",30,0,1);
//TH1F* TO_WW_BSd_cr = new TH1F("TO_WW_BSd_cr","TO Beam spot distance",30,0,1);
//TH1F* TO_WZ_BSd_cr = new TH1F("TO_WZ_BSd_cr","TO Beam spot distance",30,0,1);
TH1F* TO_LW200_BSd_cr = new TH1F("TO_LW200_BSd_cr","TO Beam spot distance",30,0,1);
TH1F* TO_LW300_BSd_cr = new TH1F("TO_LW300_BSd_cr","TO Beam spot distance",30,0,1);
TH1F* TO_LW400_BSd_cr = new TH1F("TO_LW400_BSd_cr","TO Beam spot distance",30,0,1);
TH1F* TO_LW500_BSd_cr = new TH1F("TO_LW500_BSd_cr","TO Beam spot distance",30,0,1);
TH1F* TO_dataRunB_BSdChi2norm_cr = new TH1F("TO_dataRunB_BSdChi2norm_cr","TO Beam spot distance",30,0,1);
TH1F* TO_dataRunC_BSdChi2norm_cr = new TH1F("TO_dataRunC_BSdChi2norm_cr","TO Beam spot distance",30,0,1);
TH1F* TO_ZLL_BSdChi2norm_cr = new TH1F("TO_ZLL_BSdChi2norm_cr","TO Beam spot distance",30,0,1);
TH1F* TO_TT_BSdChi2norm_cr = new TH1F("TO_TT_BSdChi2norm_cr","TO Beam spot distance",30,0,1);
TH1F* TO_W3J_BSdChi2norm_cr = new TH1F("TO_W3J_BSdChi2norm_cr","TO Beam spot distance",30,0,1);
TH1F* TO_W2J_BSdChi2norm_cr = new TH1F("TO_W2J_BSdChi2norm_cr","TO Beam spot distance",30,0,1);
TH1F* TO_W1J_BSdChi2norm_cr = new TH1F("TO_W1J_BSdChi2norm_cr","TO Beam spot distance",30,0,1);
//TH1F* TO_TTZ_BSdChi2norm_cr = new TH1F("TO_TTZ_BSdChi2norm_cr","TO Beam spot distance",30,0,1);
//TH1F* TO_WW_BSdChi2norm_cr = new TH1F("TO_WW_BSdChi2norm_cr","TO Beam spot distance",30,0,1);
//TH1F* TO_WZ_BSdChi2norm_cr = new TH1F("TO_WZ_BSdChi2norm_cr","TO Beam spot distance",30,0,1);
TH1F* TO_LW200_BSdChi2norm_cr = new TH1F("TO_LW200_BSdChi2norm_cr","TO Beam spot distance",30,0,1);
TH1F* TO_LW300_BSdChi2norm_cr = new TH1F("TO_LW300_BSdChi2norm_cr","TO Beam spot distance",30,0,1);
TH1F* TO_LW400_BSdChi2norm_cr = new TH1F("TO_LW400_BSdChi2norm_cr","TO Beam spot distance",30,0,1);
TH1F* TO_LW500_BSdChi2norm_cr = new TH1F("TO_LW500_BSdChi2norm_cr","TO Beam spot distance",30,0,1);
//Histograms for signal region HQ
TH1F* HQ_dataRunB_ppointS_cr = new TH1F("HQ_dataRunB_ppointS_cr","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_dataRunC_ppointS_cr = new TH1F("HQ_dataRunC_ppointS_cr","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_ZLL_ppointS_cr = new TH1F("HQ_ZLL_ppointS_cr","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_TT_ppointS_cr = new TH1F("HQ_TT_ppointS_cr","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_W3J_ppointS_cr = new TH1F("HQ_W3J_ppointS_cr","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_W2J_ppointS_cr = new TH1F("HQ_W2J_ppointS_cr","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_W1J_ppointS_cr = new TH1F("HQ_W1J_ppointS_cr","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //HQ_TTZ_ppointS_cr = new TH1F("//HQ_TTZ_ppointS_cr","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //HQ_WW_ppointS_cr = new TH1F("//HQ_WW_ppointS_cr","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //HQ_WZ_ppointS_cr = new TH1F("//HQ_WZ_ppointS_cr","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_LW200_ppointS_cr = new TH1F("HQ_LW200_ppointS_cr","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_LW300_ppointS_cr = new TH1F("HQ_LW300_ppointS_cr","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_LW400_ppointS_cr = new TH1F("HQ_LW400_ppointS_cr","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_LW500_ppointS_cr = new TH1F("HQ_LW500_ppointS_cr","HQ Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* HQ_dataRunB_ppoint_cr = new TH1F("HQ_dataRunB_ppoint_cr","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_dataRunC_ppoint_cr = new TH1F("HQ_dataRunC_ppoint_cr","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_ZLL_ppoint_cr = new TH1F("HQ_ZLL_ppoint_cr","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_TT_ppoint_cr = new TH1F("HQ_TT_ppoint_cr","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_W3J_ppoint_cr = new TH1F("HQ_W3J_ppoint_cr","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_W2J_ppoint_cr = new TH1F("HQ_W2J_ppoint_cr","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_W1J_ppoint_cr = new TH1F("HQ_W1J_ppoint_cr","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //HQ_TTZ_ppoint_cr = new TH1F("//HQ_TTZ_ppoint_cr","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //HQ_WW_ppoint_cr = new TH1F("//HQ_WW_ppoint_cr","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //HQ_WZ_ppoint_cr = new TH1F("//HQ_WZ_ppoint_cr","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_LW200_ppoint_cr = new TH1F("HQ_LW200_ppoint_cr","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_LW300_ppoint_cr = new TH1F("HQ_LW300_ppoint_cr","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_LW400_ppoint_cr = new TH1F("HQ_LW400_ppoint_cr","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_LW500_ppoint_cr = new TH1F("HQ_LW500_ppoint_cr","HQ Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* HQ_dataRunB_npv_cr = new TH1F("HQ_dataRunB_npv_cr","HQ Number of primary vertices",25,5,30);
TH1F* HQ_dataRunC_npv_cr = new TH1F("HQ_dataRunC_npv_cr","HQ Number of primary vertices",25,5,30);
TH1F* HQ_ZLL_npv_cr = new TH1F("HQ_ZLL_npv_cr","HQ Number of primary vertices",25,5,30);
TH1F* HQ_TT_npv_cr = new TH1F("HQ_TT_npv_cr","HQ Number of primary vertices",25,5,30);
TH1F* HQ_W3J_npv_cr = new TH1F("HQ_W3J_npv_cr","HQ Number of primary vertices",25,5,30);
TH1F* HQ_W2J_npv_cr = new TH1F("HQ_W2J_npv_cr","HQ Number of primary vertices",25,5,30);
TH1F* HQ_W1J_npv_cr = new TH1F("HQ_W1J_npv_cr","HQ Number of primary vertices",25,5,30);
//TH1F* //HQ_TTZ_npv_cr = new TH1F("//HQ_TTZ_npv_cr","HQ Number of primary vertices",25,5,30);
//TH1F* //HQ_WW_npv_cr = new TH1F("//HQ_WW_npv_cr","HQ Number of primary vertices",25,5,30);
//TH1F* //HQ_WZ_npv_cr = new TH1F("//HQ_WZ_npv_cr","HQ Number of primary vertices",25,5,30);
TH1F* HQ_LW200_npv_cr = new TH1F("HQ_LW200_npv_cr","HQ Number of primary vertices",25,5,30);
TH1F* HQ_LW300_npv_cr = new TH1F("HQ_LW300_npv_cr","HQ Number of primary vertices",25,5,30);
TH1F* HQ_LW400_npv_cr = new TH1F("HQ_LW400_npv_cr","HQ Number of primary vertices",25,5,30);
TH1F* HQ_LW500_npv_cr = new TH1F("HQ_LW500_npv_cr","HQ Number of primary vertices",25,5,30);
TH1F* HQ_dataRunB_nsv_cr = new TH1F("HQ_dataRunB_nsv_cr","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_dataRunC_nsv_cr = new TH1F("HQ_dataRunC_nsv_cr","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_ZLL_nsv_cr = new TH1F("HQ_ZLL_nsv_cr","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_TT_nsv_cr = new TH1F("HQ_TT_nsv_cr","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_W3J_nsv_cr = new TH1F("HQ_W3J_nsv_cr","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_W2J_nsv_cr = new TH1F("HQ_W2J_nsv_cr","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_W1J_nsv_cr = new TH1F("HQ_W1J_nsv_cr","HQ Number of secondary vertices",20,0,10);
//TH1F* //HQ_TTZ_nsv_cr = new TH1F("//HQ_TTZ_nsv_cr","HQ Number of secondary vertices",20,0,10);
//TH1F* //HQ_WW_nsv_cr = new TH1F("//HQ_WW_nsv_cr","HQ Number of secondary vertices",20,0,10);
//TH1F* //HQ_WZ_nsv_cr = new TH1F("//HQ_WZ_nsv_cr","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_LW200_nsv_cr = new TH1F("HQ_LW200_nsv_cr","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_LW300_nsv_cr = new TH1F("HQ_LW300_nsv_cr","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_LW400_nsv_cr = new TH1F("HQ_LW400_nsv_cr","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_LW500_nsv_cr = new TH1F("HQ_LW500_nsv_cr","HQ Number of secondary vertices",20,0,10);
TH1F* HQ_dataRunB_svd_cr = new TH1F("HQ_dataRunB_svd_cr","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_dataRunC_svd_cr = new TH1F("HQ_dataRunC_svd_cr","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_ZLL_svd_cr = new TH1F("HQ_ZLL_svd_cr","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_TT_svd_cr = new TH1F("HQ_TT_svd_cr","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_W3J_svd_cr = new TH1F("HQ_W3J_svd_cr","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_W2J_svd_cr = new TH1F("HQ_W2J_svd_cr","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_W1J_svd_cr = new TH1F("HQ_W1J_svd_cr","HQ secondary vertex displacement",30,0,1);
//TH1F* //HQ_TTZ_svd_cr = new TH1F("//HQ_TTZ_svd_cr","HQ secondary vertex displacement",30,0,1);
//TH1F* //HQ_WW_svd_cr = new TH1F("//HQ_WW_svd_cr","HQ secondary vertex displacement",30,0,1);
//TH1F* //HQ_WZ_svd_cr = new TH1F("//HQ_WZ_svd_cr","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_LW200_svd_cr = new TH1F("HQ_LW200_svd_cr","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_LW300_svd_cr = new TH1F("HQ_LW300_svd_cr","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_LW400_svd_cr = new TH1F("HQ_LW400_svd_cr","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_LW500_svd_cr = new TH1F("HQ_LW500_svd_cr","HQ secondary vertex displacement",30,0,1);
TH1F* HQ_dataRunB_BSd_cr = new TH1F("HQ_dataRunB_BSd_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_dataRunC_BSd_cr = new TH1F("HQ_dataRunC_BSd_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_ZLL_BSd_cr = new TH1F("HQ_ZLL_BSd_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_TT_BSd_cr = new TH1F("HQ_TT_BSd_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_W3J_BSd_cr = new TH1F("HQ_W3J_BSd_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_W2J_BSd_cr = new TH1F("HQ_W2J_BSd_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_W1J_BSd_cr = new TH1F("HQ_W1J_BSd_cr","HQ Beam spot distance",30,0,1);
//TH1F* HQ_TTZ_BSd_cr = new TH1F("HQ_TTZ_BSd_cr","HQ Beam spot distance",30,0,1);
//TH1F* HQ_WW_BSd_cr = new TH1F("HQ_WW_BSd_cr","HQ Beam spot distance",30,0,1);
//TH1F* HQ_WZ_BSd_cr = new TH1F("HQ_WZ_BSd_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW200_BSd_cr = new TH1F("HQ_LW200_BSd_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW300_BSd_cr = new TH1F("HQ_LW300_BSd_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW400_BSd_cr = new TH1F("HQ_LW400_BSd_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW500_BSd_cr = new TH1F("HQ_LW500_BSd_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_dataRunB_BSdChi2norm_cr = new TH1F("HQ_dataRunB_BSdChi2norm_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_dataRunC_BSdChi2norm_cr = new TH1F("HQ_dataRunC_BSdChi2norm_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_ZLL_BSdChi2norm_cr = new TH1F("HQ_ZLL_BSdChi2norm_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_TT_BSdChi2norm_cr = new TH1F("HQ_TT_BSdChi2norm_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_W3J_BSdChi2norm_cr = new TH1F("HQ_W3J_BSdChi2norm_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_W2J_BSdChi2norm_cr = new TH1F("HQ_W2J_BSdChi2norm_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_W1J_BSdChi2norm_cr = new TH1F("HQ_W1J_BSdChi2norm_cr","HQ Beam spot distance",30,0,1);
//TH1F* HQ_TTZ_BSdChi2norm_cr = new TH1F("HQ_TTZ_BSdChi2norm_cr","HQ Beam spot distance",30,0,1);
//TH1F* HQ_WW_BSdChi2norm_cr = new TH1F("HQ_WW_BSdChi2norm_cr","HQ Beam spot distance",30,0,1);
//TH1F* HQ_WZ_BSdChi2norm_cr = new TH1F("HQ_WZ_BSdChi2norm_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW200_BSdChi2norm_cr = new TH1F("HQ_LW200_BSdChi2norm_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW300_BSdChi2norm_cr = new TH1F("HQ_LW300_BSdChi2norm_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW400_BSdChi2norm_cr = new TH1F("HQ_LW400_BSdChi2norm_cr","HQ Beam spot distance",30,0,1);
TH1F* HQ_LW500_BSdChi2norm_cr = new TH1F("HQ_LW500_BSdChi2norm_cr","HQ Beam spot distance",30,0,1);
//Histograms for signal region JetS
TH1F* JetS_dataRunB_ppointS_cr = new TH1F("JetS_dataRunB_ppointS_cr","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_dataRunC_ppointS_cr = new TH1F("JetS_dataRunC_ppointS_cr","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_ZLL_ppointS_cr = new TH1F("JetS_ZLL_ppointS_cr","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_TT_ppointS_cr = new TH1F("JetS_TT_ppointS_cr","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_W3J_ppointS_cr = new TH1F("JetS_W3J_ppointS_cr","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_W2J_ppointS_cr = new TH1F("JetS_W2J_ppointS_cr","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_W1J_ppointS_cr = new TH1F("JetS_W1J_ppointS_cr","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //JetS_TTZ_ppointS_cr = new TH1F("//JetS_TTZ_ppointS_cr","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //JetS_WW_ppointS_cr = new TH1F("//JetS_WW_ppointS_cr","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //JetS_WZ_ppointS_cr = new TH1F("//JetS_WZ_ppointS_cr","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_LW200_ppointS_cr = new TH1F("JetS_LW200_ppointS_cr","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_LW300_ppointS_cr = new TH1F("JetS_LW300_ppointS_cr","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_LW400_ppointS_cr = new TH1F("JetS_LW400_ppointS_cr","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_LW500_ppointS_cr = new TH1F("JetS_LW500_ppointS_cr","JetS Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* JetS_dataRunB_ppoint_cr = new TH1F("JetS_dataRunB_ppoint_cr","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_dataRunC_ppoint_cr = new TH1F("JetS_dataRunC_ppoint_cr","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_ZLL_ppoint_cr = new TH1F("JetS_ZLL_ppoint_cr","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_TT_ppoint_cr = new TH1F("JetS_TT_ppoint_cr","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_W3J_ppoint_cr = new TH1F("JetS_W3J_ppoint_cr","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_W2J_ppoint_cr = new TH1F("JetS_W2J_ppoint_cr","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_W1J_ppoint_cr = new TH1F("JetS_W1J_ppoint_cr","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //JetS_TTZ_ppoint_cr = new TH1F("//JetS_TTZ_ppoint_cr","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //JetS_WW_ppoint_cr = new TH1F("//JetS_WW_ppoint_cr","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //JetS_WZ_ppoint_cr = new TH1F("//JetS_WZ_ppoint_cr","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_LW200_ppoint_cr = new TH1F("JetS_LW200_ppoint_cr","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_LW300_ppoint_cr = new TH1F("JetS_LW300_ppoint_cr","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_LW400_ppoint_cr = new TH1F("JetS_LW400_ppoint_cr","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_LW500_ppoint_cr = new TH1F("JetS_LW500_ppoint_cr","JetS Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* JetS_dataRunB_npv_cr = new TH1F("JetS_dataRunB_npv_cr","JetS Number of primary vertices",25,5,30);
TH1F* JetS_dataRunC_npv_cr = new TH1F("JetS_dataRunC_npv_cr","JetS Number of primary vertices",25,5,30);
TH1F* JetS_ZLL_npv_cr = new TH1F("JetS_ZLL_npv_cr","JetS Number of primary vertices",25,5,30);
TH1F* JetS_TT_npv_cr = new TH1F("JetS_TT_npv_cr","JetS Number of primary vertices",25,5,30);
TH1F* JetS_W3J_npv_cr = new TH1F("JetS_W3J_npv_cr","JetS Number of primary vertices",25,5,30);
TH1F* JetS_W2J_npv_cr = new TH1F("JetS_W2J_npv_cr","JetS Number of primary vertices",25,5,30);
TH1F* JetS_W1J_npv_cr = new TH1F("JetS_W1J_npv_cr","JetS Number of primary vertices",25,5,30);
//TH1F* //JetS_TTZ_npv_cr = new TH1F("//JetS_TTZ_npv_cr","JetS Number of primary vertices",25,5,30);
//TH1F* //JetS_WW_npv_cr = new TH1F("//JetS_WW_npv_cr","JetS Number of primary vertices",25,5,30);
//TH1F* //JetS_WZ_npv_cr = new TH1F("//JetS_WZ_npv_cr","JetS Number of primary vertices",25,5,30);
TH1F* JetS_LW200_npv_cr = new TH1F("JetS_LW200_npv_cr","JetS Number of primary vertices",25,5,30);
TH1F* JetS_LW300_npv_cr = new TH1F("JetS_LW300_npv_cr","JetS Number of primary vertices",25,5,30);
TH1F* JetS_LW400_npv_cr = new TH1F("JetS_LW400_npv_cr","JetS Number of primary vertices",25,5,30);
TH1F* JetS_LW500_npv_cr = new TH1F("JetS_LW500_npv_cr","JetS Number of primary vertices",25,5,30);
TH1F* JetS_dataRunB_nsv_cr = new TH1F("JetS_dataRunB_nsv_cr","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_dataRunC_nsv_cr = new TH1F("JetS_dataRunC_nsv_cr","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_ZLL_nsv_cr = new TH1F("JetS_ZLL_nsv_cr","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_TT_nsv_cr = new TH1F("JetS_TT_nsv_cr","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_W3J_nsv_cr = new TH1F("JetS_W3J_nsv_cr","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_W2J_nsv_cr = new TH1F("JetS_W2J_nsv_cr","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_W1J_nsv_cr = new TH1F("JetS_W1J_nsv_cr","JetS Number of secondary vertices",20,0,10);
//TH1F* //JetS_TTZ_nsv_cr = new TH1F("//JetS_TTZ_nsv_cr","JetS Number of secondary vertices",20,0,10);
//TH1F* //JetS_WW_nsv_cr = new TH1F("//JetS_WW_nsv_cr","JetS Number of secondary vertices",20,0,10);
//TH1F* //JetS_WZ_nsv_cr = new TH1F("//JetS_WZ_nsv_cr","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_LW200_nsv_cr = new TH1F("JetS_LW200_nsv_cr","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_LW300_nsv_cr = new TH1F("JetS_LW300_nsv_cr","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_LW400_nsv_cr = new TH1F("JetS_LW400_nsv_cr","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_LW500_nsv_cr = new TH1F("JetS_LW500_nsv_cr","JetS Number of secondary vertices",20,0,10);
TH1F* JetS_dataRunB_svd_cr = new TH1F("JetS_dataRunB_svd_cr","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_dataRunC_svd_cr = new TH1F("JetS_dataRunC_svd_cr","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_ZLL_svd_cr = new TH1F("JetS_ZLL_svd_cr","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_TT_svd_cr = new TH1F("JetS_TT_svd_cr","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_W3J_svd_cr = new TH1F("JetS_W3J_svd_cr","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_W2J_svd_cr = new TH1F("JetS_W2J_svd_cr","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_W1J_svd_cr = new TH1F("JetS_W1J_svd_cr","JetS secondary vertex displacement",30,0,1);
//TH1F* //JetS_TTZ_svd_cr = new TH1F("//JetS_TTZ_svd_cr","JetS secondary vertex displacement",30,0,1);
//TH1F* //JetS_WW_svd_cr = new TH1F("//JetS_WW_svd_cr","JetS secondary vertex displacement",30,0,1);
//TH1F* //JetS_WZ_svd_cr = new TH1F("//JetS_WZ_svd_cr","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_LW200_svd_cr = new TH1F("JetS_LW200_svd_cr","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_LW300_svd_cr = new TH1F("JetS_LW300_svd_cr","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_LW400_svd_cr = new TH1F("JetS_LW400_svd_cr","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_LW500_svd_cr = new TH1F("JetS_LW500_svd_cr","JetS secondary vertex displacement",30,0,1);
TH1F* JetS_dataRunB_BSd_cr = new TH1F("JetS_dataRunB_BSd_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_dataRunC_BSd_cr = new TH1F("JetS_dataRunC_BSd_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_ZLL_BSd_cr = new TH1F("JetS_ZLL_BSd_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_TT_BSd_cr = new TH1F("JetS_TT_BSd_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_W3J_BSd_cr = new TH1F("JetS_W3J_BSd_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_W2J_BSd_cr = new TH1F("JetS_W2J_BSd_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_W1J_BSd_cr = new TH1F("JetS_W1J_BSd_cr","JetS Beam spot distance",30,0,1);
//TH1F* JetS_TTZ_BSd_cr = new TH1F("JetS_TTZ_BSd_cr","JetS Beam spot distance",30,0,1);
//TH1F* JetS_WW_BSd_cr = new TH1F("JetS_WW_BSd_cr","JetS Beam spot distance",30,0,1);
//TH1F* JetS_WZ_BSd_cr = new TH1F("JetS_WZ_BSd_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW200_BSd_cr = new TH1F("JetS_LW200_BSd_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW300_BSd_cr = new TH1F("JetS_LW300_BSd_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW400_BSd_cr = new TH1F("JetS_LW400_BSd_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW500_BSd_cr = new TH1F("JetS_LW500_BSd_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_dataRunB_BSdChi2norm_cr = new TH1F("JetS_dataRunB_BSdChi2norm_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_dataRunC_BSdChi2norm_cr = new TH1F("JetS_dataRunC_BSdChi2norm_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_ZLL_BSdChi2norm_cr = new TH1F("JetS_ZLL_BSdChi2norm_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_TT_BSdChi2norm_cr = new TH1F("JetS_TT_BSdChi2norm_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_W3J_BSdChi2norm_cr = new TH1F("JetS_W3J_BSdChi2norm_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_W2J_BSdChi2norm_cr = new TH1F("JetS_W2J_BSdChi2norm_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_W1J_BSdChi2norm_cr = new TH1F("JetS_W1J_BSdChi2norm_cr","JetS Beam spot distance",30,0,1);
//TH1F* JetS_TTZ_BSdChi2norm_cr = new TH1F("JetS_TTZ_BSdChi2norm_cr","JetS Beam spot distance",30,0,1);
//TH1F* JetS_WW_BSdChi2norm_cr = new TH1F("JetS_WW_BSdChi2norm_cr","JetS Beam spot distance",30,0,1);
//TH1F* JetS_WZ_BSdChi2norm_cr = new TH1F("JetS_WZ_BSdChi2norm_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW200_BSdChi2norm_cr = new TH1F("JetS_LW200_BSdChi2norm_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW300_BSdChi2norm_cr = new TH1F("JetS_LW300_BSdChi2norm_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW400_BSdChi2norm_cr = new TH1F("JetS_LW400_BSdChi2norm_cr","JetS Beam spot distance",30,0,1);
TH1F* JetS_LW500_BSdChi2norm_cr = new TH1F("JetS_LW500_BSdChi2norm_cr","JetS Beam spot distance",30,0,1);
//Histograms for signal region DRC
TH1F* DRC_dataRunB_ppointS_cr = new TH1F("DRC_dataRunB_ppointS_cr","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_dataRunC_ppointS_cr = new TH1F("DRC_dataRunC_ppointS_cr","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_ZLL_ppointS_cr = new TH1F("DRC_ZLL_ppointS_cr","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_TT_ppointS_cr = new TH1F("DRC_TT_ppointS_cr","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_W3J_ppointS_cr = new TH1F("DRC_W3J_ppointS_cr","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_W2J_ppointS_cr = new TH1F("DRC_W2J_ppointS_cr","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_W1J_ppointS_cr = new TH1F("DRC_W1J_ppointS_cr","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //DRC_TTZ_ppointS_cr = new TH1F("//DRC_TTZ_ppointS_cr","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //DRC_WW_ppointS_cr = new TH1F("//DRC_WW_ppointS_cr","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //DRC_WZ_ppointS_cr = new TH1F("//DRC_WZ_ppointS_cr","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_LW200_ppointS_cr = new TH1F("DRC_LW200_ppointS_cr","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_LW300_ppointS_cr = new TH1F("DRC_LW300_ppointS_cr","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_LW400_ppointS_cr = new TH1F("DRC_LW400_ppointS_cr","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_LW500_ppointS_cr = new TH1F("DRC_LW500_ppointS_cr","DRC Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* DRC_dataRunB_ppoint_cr = new TH1F("DRC_dataRunB_ppoint_cr","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_dataRunC_ppoint_cr = new TH1F("DRC_dataRunC_ppoint_cr","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_ZLL_ppoint_cr = new TH1F("DRC_ZLL_ppoint_cr","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_TT_ppoint_cr = new TH1F("DRC_TT_ppoint_cr","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_W3J_ppoint_cr = new TH1F("DRC_W3J_ppoint_cr","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_W2J_ppoint_cr = new TH1F("DRC_W2J_ppoint_cr","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_W1J_ppoint_cr = new TH1F("DRC_W1J_ppoint_cr","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //DRC_TTZ_ppoint_cr = new TH1F("//DRC_TTZ_ppoint_cr","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //DRC_WW_ppoint_cr = new TH1F("//DRC_WW_ppoint_cr","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //DRC_WZ_ppoint_cr = new TH1F("//DRC_WZ_ppoint_cr","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_LW200_ppoint_cr = new TH1F("DRC_LW200_ppoint_cr","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_LW300_ppoint_cr = new TH1F("DRC_LW300_ppoint_cr","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_LW400_ppoint_cr = new TH1F("DRC_LW400_ppoint_cr","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_LW500_ppoint_cr = new TH1F("DRC_LW500_ppoint_cr","DRC Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* DRC_dataRunB_npv_cr = new TH1F("DRC_dataRunB_npv_cr","DRC Number of primary vertices",25,5,30);
TH1F* DRC_dataRunC_npv_cr = new TH1F("DRC_dataRunC_npv_cr","DRC Number of primary vertices",25,5,30);
TH1F* DRC_ZLL_npv_cr = new TH1F("DRC_ZLL_npv_cr","DRC Number of primary vertices",25,5,30);
TH1F* DRC_TT_npv_cr = new TH1F("DRC_TT_npv_cr","DRC Number of primary vertices",25,5,30);
TH1F* DRC_W3J_npv_cr = new TH1F("DRC_W3J_npv_cr","DRC Number of primary vertices",25,5,30);
TH1F* DRC_W2J_npv_cr = new TH1F("DRC_W2J_npv_cr","DRC Number of primary vertices",25,5,30);
TH1F* DRC_W1J_npv_cr = new TH1F("DRC_W1J_npv_cr","DRC Number of primary vertices",25,5,30);
//TH1F* //DRC_TTZ_npv_cr = new TH1F("//DRC_TTZ_npv_cr","DRC Number of primary vertices",25,5,30);
//TH1F* //DRC_WW_npv_cr = new TH1F("//DRC_WW_npv_cr","DRC Number of primary vertices",25,5,30);
//TH1F* //DRC_WZ_npv_cr = new TH1F("//DRC_WZ_npv_cr","DRC Number of primary vertices",25,5,30);
TH1F* DRC_LW200_npv_cr = new TH1F("DRC_LW200_npv_cr","DRC Number of primary vertices",25,5,30);
TH1F* DRC_LW300_npv_cr = new TH1F("DRC_LW300_npv_cr","DRC Number of primary vertices",25,5,30);
TH1F* DRC_LW400_npv_cr = new TH1F("DRC_LW400_npv_cr","DRC Number of primary vertices",25,5,30);
TH1F* DRC_LW500_npv_cr = new TH1F("DRC_LW500_npv_cr","DRC Number of primary vertices",25,5,30);
TH1F* DRC_dataRunB_nsv_cr = new TH1F("DRC_dataRunB_nsv_cr","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_dataRunC_nsv_cr = new TH1F("DRC_dataRunC_nsv_cr","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_ZLL_nsv_cr = new TH1F("DRC_ZLL_nsv_cr","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_TT_nsv_cr = new TH1F("DRC_TT_nsv_cr","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_W3J_nsv_cr = new TH1F("DRC_W3J_nsv_cr","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_W2J_nsv_cr = new TH1F("DRC_W2J_nsv_cr","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_W1J_nsv_cr = new TH1F("DRC_W1J_nsv_cr","DRC Number of secondary vertices",20,0,10);
//TH1F* //DRC_TTZ_nsv_cr = new TH1F("//DRC_TTZ_nsv_cr","DRC Number of secondary vertices",20,0,10);
//TH1F* //DRC_WW_nsv_cr = new TH1F("//DRC_WW_nsv_cr","DRC Number of secondary vertices",20,0,10);
//TH1F* //DRC_WZ_nsv_cr = new TH1F("//DRC_WZ_nsv_cr","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_LW200_nsv_cr = new TH1F("DRC_LW200_nsv_cr","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_LW300_nsv_cr = new TH1F("DRC_LW300_nsv_cr","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_LW400_nsv_cr = new TH1F("DRC_LW400_nsv_cr","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_LW500_nsv_cr = new TH1F("DRC_LW500_nsv_cr","DRC Number of secondary vertices",20,0,10);
TH1F* DRC_dataRunB_svd_cr = new TH1F("DRC_dataRunB_svd_cr","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_dataRunC_svd_cr = new TH1F("DRC_dataRunC_svd_cr","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_ZLL_svd_cr = new TH1F("DRC_ZLL_svd_cr","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_TT_svd_cr = new TH1F("DRC_TT_svd_cr","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_W3J_svd_cr = new TH1F("DRC_W3J_svd_cr","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_W2J_svd_cr = new TH1F("DRC_W2J_svd_cr","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_W1J_svd_cr = new TH1F("DRC_W1J_svd_cr","DRC secondary vertex displacement",30,0,1);
//TH1F* //DRC_TTZ_svd_cr = new TH1F("//DRC_TTZ_svd_cr","DRC secondary vertex displacement",30,0,1);
//TH1F* //DRC_WW_svd_cr = new TH1F("//DRC_WW_svd_cr","DRC secondary vertex displacement",30,0,1);
//TH1F* //DRC_WZ_svd_cr = new TH1F("//DRC_WZ_svd_cr","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_LW200_svd_cr = new TH1F("DRC_LW200_svd_cr","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_LW300_svd_cr = new TH1F("DRC_LW300_svd_cr","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_LW400_svd_cr = new TH1F("DRC_LW400_svd_cr","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_LW500_svd_cr = new TH1F("DRC_LW500_svd_cr","DRC secondary vertex displacement",30,0,1);
TH1F* DRC_dataRunB_BSd_cr = new TH1F("DRC_dataRunB_BSd_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_dataRunC_BSd_cr = new TH1F("DRC_dataRunC_BSd_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_ZLL_BSd_cr = new TH1F("DRC_ZLL_BSd_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_TT_BSd_cr = new TH1F("DRC_TT_BSd_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_W3J_BSd_cr = new TH1F("DRC_W3J_BSd_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_W2J_BSd_cr = new TH1F("DRC_W2J_BSd_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_W1J_BSd_cr = new TH1F("DRC_W1J_BSd_cr","DRC Beam spot distance",30,0,1);
//TH1F* DRC_TTZ_BSd_cr = new TH1F("DRC_TTZ_BSd_cr","DRC Beam spot distance",30,0,1);
//TH1F* DRC_WW_BSd_cr = new TH1F("DRC_WW_BSd_cr","DRC Beam spot distance",30,0,1);
//TH1F* DRC_WZ_BSd_cr = new TH1F("DRC_WZ_BSd_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW200_BSd_cr = new TH1F("DRC_LW200_BSd_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW300_BSd_cr = new TH1F("DRC_LW300_BSd_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW400_BSd_cr = new TH1F("DRC_LW400_BSd_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW500_BSd_cr = new TH1F("DRC_LW500_BSd_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_dataRunB_BSdChi2norm_cr = new TH1F("DRC_dataRunB_BSdChi2norm_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_dataRunC_BSdChi2norm_cr = new TH1F("DRC_dataRunC_BSdChi2norm_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_ZLL_BSdChi2norm_cr = new TH1F("DRC_ZLL_BSdChi2norm_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_TT_BSdChi2norm_cr = new TH1F("DRC_TT_BSdChi2norm_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_W3J_BSdChi2norm_cr = new TH1F("DRC_W3J_BSdChi2norm_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_W2J_BSdChi2norm_cr = new TH1F("DRC_W2J_BSdChi2norm_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_W1J_BSdChi2norm_cr = new TH1F("DRC_W1J_BSdChi2norm_cr","DRC Beam spot distance",30,0,1);
//TH1F* DRC_TTZ_BSdChi2norm_cr = new TH1F("DRC_TTZ_BSdChi2norm_cr","DRC Beam spot distance",30,0,1);
//TH1F* DRC_WW_BSdChi2norm_cr = new TH1F("DRC_WW_BSdChi2norm_cr","DRC Beam spot distance",30,0,1);
//TH1F* DRC_WZ_BSdChi2norm_cr = new TH1F("DRC_WZ_BSdChi2norm_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW200_BSdChi2norm_cr = new TH1F("DRC_LW200_BSdChi2norm_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW300_BSdChi2norm_cr = new TH1F("DRC_LW300_BSdChi2norm_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW400_BSdChi2norm_cr = new TH1F("DRC_LW400_BSdChi2norm_cr","DRC Beam spot distance",30,0,1);
TH1F* DRC_LW500_BSdChi2norm_cr = new TH1F("DRC_LW500_BSdChi2norm_cr","DRC Beam spot distance",30,0,1);
//Histograms for signal region SG
TH1F* SG_dataRunB_ppointS_cr = new TH1F("SG_dataRunB_ppointS_cr","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_dataRunC_ppointS_cr = new TH1F("SG_dataRunC_ppointS_cr","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_ZLL_ppointS_cr = new TH1F("SG_ZLL_ppointS_cr","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_TT_ppointS_cr = new TH1F("SG_TT_ppointS_cr","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_W3J_ppointS_cr = new TH1F("SG_W3J_ppointS_cr","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_W2J_ppointS_cr = new TH1F("SG_W2J_ppointS_cr","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_W1J_ppointS_cr = new TH1F("SG_W1J_ppointS_cr","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //SG_TTZ_ppointS_cr = new TH1F("//SG_TTZ_ppointS_cr","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //SG_WW_ppointS_cr = new TH1F("//SG_WW_ppointS_cr","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //SG_WZ_ppointS_cr = new TH1F("//SG_WZ_ppointS_cr","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_LW200_ppointS_cr = new TH1F("SG_LW200_ppointS_cr","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_LW300_ppointS_cr = new TH1F("SG_LW300_ppointS_cr","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_LW400_ppointS_cr = new TH1F("SG_LW400_ppointS_cr","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_LW500_ppointS_cr = new TH1F("SG_LW500_ppointS_cr","SG Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* SG_dataRunB_ppoint_cr = new TH1F("SG_dataRunB_ppoint_cr","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_dataRunC_ppoint_cr = new TH1F("SG_dataRunC_ppoint_cr","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_ZLL_ppoint_cr = new TH1F("SG_ZLL_ppoint_cr","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_TT_ppoint_cr = new TH1F("SG_TT_ppoint_cr","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_W3J_ppoint_cr = new TH1F("SG_W3J_ppoint_cr","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_W2J_ppoint_cr = new TH1F("SG_W2J_ppoint_cr","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_W1J_ppoint_cr = new TH1F("SG_W1J_ppoint_cr","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //SG_TTZ_ppoint_cr = new TH1F("//SG_TTZ_ppoint_cr","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //SG_WW_ppoint_cr = new TH1F("//SG_WW_ppoint_cr","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //SG_WZ_ppoint_cr = new TH1F("//SG_WZ_ppoint_cr","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_LW200_ppoint_cr = new TH1F("SG_LW200_ppoint_cr","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_LW300_ppoint_cr = new TH1F("SG_LW300_ppoint_cr","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_LW400_ppoint_cr = new TH1F("SG_LW400_ppoint_cr","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_LW500_ppoint_cr = new TH1F("SG_LW500_ppoint_cr","SG Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* SG_dataRunB_npv_cr = new TH1F("SG_dataRunB_npv_cr","SG Number of primary vertices",25,5,30);
TH1F* SG_dataRunC_npv_cr = new TH1F("SG_dataRunC_npv_cr","SG Number of primary vertices",25,5,30);
TH1F* SG_ZLL_npv_cr = new TH1F("SG_ZLL_npv_cr","SG Number of primary vertices",25,5,30);
TH1F* SG_TT_npv_cr = new TH1F("SG_TT_npv_cr","SG Number of primary vertices",25,5,30);
TH1F* SG_W3J_npv_cr = new TH1F("SG_W3J_npv_cr","SG Number of primary vertices",25,5,30);
TH1F* SG_W2J_npv_cr = new TH1F("SG_W2J_npv_cr","SG Number of primary vertices",25,5,30);
TH1F* SG_W1J_npv_cr = new TH1F("SG_W1J_npv_cr","SG Number of primary vertices",25,5,30);
//TH1F* //SG_TTZ_npv_cr = new TH1F("//SG_TTZ_npv_cr","SG Number of primary vertices",25,5,30);
//TH1F* //SG_WW_npv_cr = new TH1F("//SG_WW_npv_cr","SG Number of primary vertices",25,5,30);
//TH1F* //SG_WZ_npv_cr = new TH1F("//SG_WZ_npv_cr","SG Number of primary vertices",25,5,30);
TH1F* SG_LW200_npv_cr = new TH1F("SG_LW200_npv_cr","SG Number of primary vertices",25,5,30);
TH1F* SG_LW300_npv_cr = new TH1F("SG_LW300_npv_cr","SG Number of primary vertices",25,5,30);
TH1F* SG_LW400_npv_cr = new TH1F("SG_LW400_npv_cr","SG Number of primary vertices",25,5,30);
TH1F* SG_LW500_npv_cr = new TH1F("SG_LW500_npv_cr","SG Number of primary vertices",25,5,30);
TH1F* SG_dataRunB_nsv_cr = new TH1F("SG_dataRunB_nsv_cr","SG Number of secondary vertices",20,0,10);
TH1F* SG_dataRunC_nsv_cr = new TH1F("SG_dataRunC_nsv_cr","SG Number of secondary vertices",20,0,10);
TH1F* SG_ZLL_nsv_cr = new TH1F("SG_ZLL_nsv_cr","SG Number of secondary vertices",20,0,10);
TH1F* SG_TT_nsv_cr = new TH1F("SG_TT_nsv_cr","SG Number of secondary vertices",20,0,10);
TH1F* SG_W3J_nsv_cr = new TH1F("SG_W3J_nsv_cr","SG Number of secondary vertices",20,0,10);
TH1F* SG_W2J_nsv_cr = new TH1F("SG_W2J_nsv_cr","SG Number of secondary vertices",20,0,10);
TH1F* SG_W1J_nsv_cr = new TH1F("SG_W1J_nsv_cr","SG Number of secondary vertices",20,0,10);
//TH1F* //SG_TTZ_nsv_cr = new TH1F("//SG_TTZ_nsv_cr","SG Number of secondary vertices",20,0,10);
//TH1F* //SG_WW_nsv_cr = new TH1F("//SG_WW_nsv_cr","SG Number of secondary vertices",20,0,10);
//TH1F* //SG_WZ_nsv_cr = new TH1F("//SG_WZ_nsv_cr","SG Number of secondary vertices",20,0,10);
TH1F* SG_LW200_nsv_cr = new TH1F("SG_LW200_nsv_cr","SG Number of secondary vertices",20,0,10);
TH1F* SG_LW300_nsv_cr = new TH1F("SG_LW300_nsv_cr","SG Number of secondary vertices",20,0,10);
TH1F* SG_LW400_nsv_cr = new TH1F("SG_LW400_nsv_cr","SG Number of secondary vertices",20,0,10);
TH1F* SG_LW500_nsv_cr = new TH1F("SG_LW500_nsv_cr","SG Number of secondary vertices",20,0,10);
TH1F* SG_dataRunB_svd_cr = new TH1F("SG_dataRunB_svd_cr","SG secondary vertex displacement",30,0,1);
TH1F* SG_dataRunC_svd_cr = new TH1F("SG_dataRunC_svd_cr","SG secondary vertex displacement",30,0,1);
TH1F* SG_ZLL_svd_cr = new TH1F("SG_ZLL_svd_cr","SG secondary vertex displacement",30,0,1);
TH1F* SG_TT_svd_cr = new TH1F("SG_TT_svd_cr","SG secondary vertex displacement",30,0,1);
TH1F* SG_W3J_svd_cr = new TH1F("SG_W3J_svd_cr","SG secondary vertex displacement",30,0,1);
TH1F* SG_W2J_svd_cr = new TH1F("SG_W2J_svd_cr","SG secondary vertex displacement",30,0,1);
TH1F* SG_W1J_svd_cr = new TH1F("SG_W1J_svd_cr","SG secondary vertex displacement",30,0,1);
//TH1F* //SG_TTZ_svd_cr = new TH1F("//SG_TTZ_svd_cr","SG secondary vertex displacement",30,0,1);
//TH1F* //SG_WW_svd_cr = new TH1F("//SG_WW_svd_cr","SG secondary vertex displacement",30,0,1);
//TH1F* //SG_WZ_svd_cr = new TH1F("//SG_WZ_svd_cr","SG secondary vertex displacement",30,0,1);
TH1F* SG_LW200_svd_cr = new TH1F("SG_LW200_svd_cr","SG secondary vertex displacement",30,0,1);
TH1F* SG_LW300_svd_cr = new TH1F("SG_LW300_svd_cr","SG secondary vertex displacement",30,0,1);
TH1F* SG_LW400_svd_cr = new TH1F("SG_LW400_svd_cr","SG secondary vertex displacement",30,0,1);
TH1F* SG_LW500_svd_cr = new TH1F("SG_LW500_svd_cr","SG secondary vertex displacement",30,0,1);
TH1F* SG_dataRunB_BSd_cr = new TH1F("SG_dataRunB_BSd_cr","SG Beam spot distance",30,0,1);
TH1F* SG_dataRunC_BSd_cr = new TH1F("SG_dataRunC_BSd_cr","SG Beam spot distance",30,0,1);
TH1F* SG_ZLL_BSd_cr = new TH1F("SG_ZLL_BSd_cr","SG Beam spot distance",30,0,1);
TH1F* SG_TT_BSd_cr = new TH1F("SG_TT_BSd_cr","SG Beam spot distance",30,0,1);
TH1F* SG_W3J_BSd_cr = new TH1F("SG_W3J_BSd_cr","SG Beam spot distance",30,0,1);
TH1F* SG_W2J_BSd_cr = new TH1F("SG_W2J_BSd_cr","SG Beam spot distance",30,0,1);
TH1F* SG_W1J_BSd_cr = new TH1F("SG_W1J_BSd_cr","SG Beam spot distance",30,0,1);
//TH1F* SG_TTZ_BSd_cr = new TH1F("SG_TTZ_BSd_cr","SG Beam spot distance",30,0,1);
//TH1F* SG_WW_BSd_cr = new TH1F("SG_WW_BSd_cr","SG Beam spot distance",30,0,1);
//TH1F* SG_WZ_BSd_cr = new TH1F("SG_WZ_BSd_cr","SG Beam spot distance",30,0,1);
TH1F* SG_LW200_BSd_cr = new TH1F("SG_LW200_BSd_cr","SG Beam spot distance",30,0,1);
TH1F* SG_LW300_BSd_cr = new TH1F("SG_LW300_BSd_cr","SG Beam spot distance",30,0,1);
TH1F* SG_LW400_BSd_cr = new TH1F("SG_LW400_BSd_cr","SG Beam spot distance",30,0,1);
TH1F* SG_LW500_BSd_cr = new TH1F("SG_LW500_BSd_cr","SG Beam spot distance",30,0,1);
TH1F* SG_dataRunB_BSdChi2norm_cr = new TH1F("SG_dataRunB_BSdChi2norm_cr","SG Beam spot distance",30,0,1);
TH1F* SG_dataRunC_BSdChi2norm_cr = new TH1F("SG_dataRunC_BSdChi2norm_cr","SG Beam spot distance",30,0,1);
TH1F* SG_ZLL_BSdChi2norm_cr = new TH1F("SG_ZLL_BSdChi2norm_cr","SG Beam spot distance",30,0,1);
TH1F* SG_TT_BSdChi2norm_cr = new TH1F("SG_TT_BSdChi2norm_cr","SG Beam spot distance",30,0,1);
TH1F* SG_W3J_BSdChi2norm_cr = new TH1F("SG_W3J_BSdChi2norm_cr","SG Beam spot distance",30,0,1);
TH1F* SG_W2J_BSdChi2norm_cr = new TH1F("SG_W2J_BSdChi2norm_cr","SG Beam spot distance",30,0,1);
TH1F* SG_W1J_BSdChi2norm_cr = new TH1F("SG_W1J_BSdChi2norm_cr","SG Beam spot distance",30,0,1);
//TH1F* SG_TTZ_BSdChi2norm_cr = new TH1F("SG_TTZ_BSdChi2norm_cr","SG Beam spot distance",30,0,1);
//TH1F* SG_WW_BSdChi2norm_cr = new TH1F("SG_WW_BSdChi2norm_cr","SG Beam spot distance",30,0,1);
//TH1F* SG_WZ_BSdChi2norm_cr = new TH1F("SG_WZ_BSdChi2norm_cr","SG Beam spot distance",30,0,1);
TH1F* SG_LW200_BSdChi2norm_cr = new TH1F("SG_LW200_BSdChi2norm_cr","SG Beam spot distance",30,0,1);
TH1F* SG_LW300_BSdChi2norm_cr = new TH1F("SG_LW300_BSdChi2norm_cr","SG Beam spot distance",30,0,1);
TH1F* SG_LW400_BSdChi2norm_cr = new TH1F("SG_LW400_BSdChi2norm_cr","SG Beam spot distance",30,0,1);
TH1F* SG_LW500_BSdChi2norm_cr = new TH1F("SG_LW500_BSdChi2norm_cr","SG Beam spot distance",30,0,1);
//Histograms for signal region IPP
TH1F* IPP_dataRunB_ppointS_cr = new TH1F("IPP_dataRunB_ppointS_cr","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_dataRunC_ppointS_cr = new TH1F("IPP_dataRunC_ppointS_cr","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_ZLL_ppointS_cr = new TH1F("IPP_ZLL_ppointS_cr","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_TT_ppointS_cr = new TH1F("IPP_TT_ppointS_cr","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_W3J_ppointS_cr = new TH1F("IPP_W3J_ppointS_cr","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_W2J_ppointS_cr = new TH1F("IPP_W2J_ppointS_cr","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_W1J_ppointS_cr = new TH1F("IPP_W1J_ppointS_cr","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //IPP_TTZ_ppointS_cr = new TH1F("//IPP_TTZ_ppointS_cr","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //IPP_WW_ppointS_cr = new TH1F("//IPP_WW_ppointS_cr","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
//TH1F* //IPP_WZ_ppointS_cr = new TH1F("//IPP_WZ_ppointS_cr","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_LW200_ppointS_cr = new TH1F("IPP_LW200_ppointS_cr","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_LW300_ppointS_cr = new TH1F("IPP_LW300_ppointS_cr","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_LW400_ppointS_cr = new TH1F("IPP_LW400_ppointS_cr","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_LW500_ppointS_cr = new TH1F("IPP_LW500_ppointS_cr","IPP Scalar product sign displacement and total momentum of secondary vertex",2,0,2);
TH1F* IPP_dataRunB_ppoint_cr = new TH1F("IPP_dataRunB_ppoint_cr","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_dataRunC_ppoint_cr = new TH1F("IPP_dataRunC_ppoint_cr","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_ZLL_ppoint_cr = new TH1F("IPP_ZLL_ppoint_cr","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_TT_ppoint_cr = new TH1F("IPP_TT_ppoint_cr","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_W3J_ppoint_cr = new TH1F("IPP_W3J_ppoint_cr","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_W2J_ppoint_cr = new TH1F("IPP_W2J_ppoint_cr","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_W1J_ppoint_cr = new TH1F("IPP_W1J_ppoint_cr","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //IPP_TTZ_ppoint_cr = new TH1F("//IPP_TTZ_ppoint_cr","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //IPP_WW_ppoint_cr = new TH1F("//IPP_WW_ppoint_cr","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
//TH1F* //IPP_WZ_ppoint_cr = new TH1F("//IPP_WZ_ppoint_cr","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_LW200_ppoint_cr = new TH1F("IPP_LW200_ppoint_cr","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_LW300_ppoint_cr = new TH1F("IPP_LW300_ppoint_cr","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_LW400_ppoint_cr = new TH1F("IPP_LW400_ppoint_cr","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_LW500_ppoint_cr = new TH1F("IPP_LW500_ppoint_cr","IPP Scalar product displacement and total momentum of secondary vertex",30,-150,150);
TH1F* IPP_dataRunB_npv_cr = new TH1F("IPP_dataRunB_npv_cr","IPP Number of primary vertices",25,5,30);
TH1F* IPP_dataRunC_npv_cr = new TH1F("IPP_dataRunC_npv_cr","IPP Number of primary vertices",25,5,30);
TH1F* IPP_ZLL_npv_cr = new TH1F("IPP_ZLL_npv_cr","IPP Number of primary vertices",25,5,30);
TH1F* IPP_TT_npv_cr = new TH1F("IPP_TT_npv_cr","IPP Number of primary vertices",25,5,30);
TH1F* IPP_W3J_npv_cr = new TH1F("IPP_W3J_npv_cr","IPP Number of primary vertices",25,5,30);
TH1F* IPP_W2J_npv_cr = new TH1F("IPP_W2J_npv_cr","IPP Number of primary vertices",25,5,30);
TH1F* IPP_W1J_npv_cr = new TH1F("IPP_W1J_npv_cr","IPP Number of primary vertices",25,5,30);
//TH1F* //IPP_TTZ_npv_cr = new TH1F("//IPP_TTZ_npv_cr","IPP Number of primary vertices",25,5,30);
//TH1F* //IPP_WW_npv_cr = new TH1F("//IPP_WW_npv_cr","IPP Number of primary vertices",25,5,30);
//TH1F* //IPP_WZ_npv_cr = new TH1F("//IPP_WZ_npv_cr","IPP Number of primary vertices",25,5,30);
TH1F* IPP_LW200_npv_cr = new TH1F("IPP_LW200_npv_cr","IPP Number of primary vertices",25,5,30);
TH1F* IPP_LW300_npv_cr = new TH1F("IPP_LW300_npv_cr","IPP Number of primary vertices",25,5,30);
TH1F* IPP_LW400_npv_cr = new TH1F("IPP_LW400_npv_cr","IPP Number of primary vertices",25,5,30);
TH1F* IPP_LW500_npv_cr = new TH1F("IPP_LW500_npv_cr","IPP Number of primary vertices",25,5,30);
TH1F* IPP_dataRunB_nsv_cr = new TH1F("IPP_dataRunB_nsv_cr","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_dataRunC_nsv_cr = new TH1F("IPP_dataRunC_nsv_cr","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_ZLL_nsv_cr = new TH1F("IPP_ZLL_nsv_cr","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_TT_nsv_cr = new TH1F("IPP_TT_nsv_cr","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_W3J_nsv_cr = new TH1F("IPP_W3J_nsv_cr","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_W2J_nsv_cr = new TH1F("IPP_W2J_nsv_cr","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_W1J_nsv_cr = new TH1F("IPP_W1J_nsv_cr","IPP Number of secondary vertices",20,0,10);
//TH1F* //IPP_TTZ_nsv_cr = new TH1F("//IPP_TTZ_nsv_cr","IPP Number of secondary vertices",20,0,10);
//TH1F* //IPP_WW_nsv_cr = new TH1F("//IPP_WW_nsv_cr","IPP Number of secondary vertices",20,0,10);
//TH1F* //IPP_WZ_nsv_cr = new TH1F("//IPP_WZ_nsv_cr","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_LW200_nsv_cr = new TH1F("IPP_LW200_nsv_cr","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_LW300_nsv_cr = new TH1F("IPP_LW300_nsv_cr","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_LW400_nsv_cr = new TH1F("IPP_LW400_nsv_cr","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_LW500_nsv_cr = new TH1F("IPP_LW500_nsv_cr","IPP Number of secondary vertices",20,0,10);
TH1F* IPP_dataRunB_svd_cr = new TH1F("IPP_dataRunB_svd_cr","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_dataRunC_svd_cr = new TH1F("IPP_dataRunC_svd_cr","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_ZLL_svd_cr = new TH1F("IPP_ZLL_svd_cr","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_TT_svd_cr = new TH1F("IPP_TT_svd_cr","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_W3J_svd_cr = new TH1F("IPP_W3J_svd_cr","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_W2J_svd_cr = new TH1F("IPP_W2J_svd_cr","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_W1J_svd_cr = new TH1F("IPP_W1J_svd_cr","IPP secondary vertex displacement",30,0,1);
//TH1F* //IPP_TTZ_svd_cr = new TH1F("//IPP_TTZ_svd_cr","IPP secondary vertex displacement",30,0,1);
//TH1F* //IPP_WW_svd_cr = new TH1F("//IPP_WW_svd_cr","IPP secondary vertex displacement",30,0,1);
//TH1F* //IPP_WZ_svd_cr = new TH1F("//IPP_WZ_svd_cr","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_LW200_svd_cr = new TH1F("IPP_LW200_svd_cr","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_LW300_svd_cr = new TH1F("IPP_LW300_svd_cr","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_LW400_svd_cr = new TH1F("IPP_LW400_svd_cr","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_LW500_svd_cr = new TH1F("IPP_LW500_svd_cr","IPP secondary vertex displacement",30,0,1);
TH1F* IPP_dataRunB_BSd_cr = new TH1F("IPP_dataRunB_BSd_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_dataRunC_BSd_cr = new TH1F("IPP_dataRunC_BSd_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_ZLL_BSd_cr = new TH1F("IPP_ZLL_BSd_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_TT_BSd_cr = new TH1F("IPP_TT_BSd_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_W3J_BSd_cr = new TH1F("IPP_W3J_BSd_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_W2J_BSd_cr = new TH1F("IPP_W2J_BSd_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_W1J_BSd_cr = new TH1F("IPP_W1J_BSd_cr","IPP Beam spot distance",30,0,1);
//TH1F* IPP_TTZ_BSd_cr = new TH1F("IPP_TTZ_BSd_cr","IPP Beam spot distance",30,0,1);
//TH1F* IPP_WW_BSd_cr = new TH1F("IPP_WW_BSd_cr","IPP Beam spot distance",30,0,1);
//TH1F* IPP_WZ_BSd_cr = new TH1F("IPP_WZ_BSd_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW200_BSd_cr = new TH1F("IPP_LW200_BSd_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW300_BSd_cr = new TH1F("IPP_LW300_BSd_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW400_BSd_cr = new TH1F("IPP_LW400_BSd_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW500_BSd_cr = new TH1F("IPP_LW500_BSd_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_dataRunB_BSdChi2norm_cr = new TH1F("IPP_dataRunB_BSdChi2norm_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_dataRunC_BSdChi2norm_cr = new TH1F("IPP_dataRunC_BSdChi2norm_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_ZLL_BSdChi2norm_cr = new TH1F("IPP_ZLL_BSdChi2norm_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_TT_BSdChi2norm_cr = new TH1F("IPP_TT_BSdChi2norm_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_W3J_BSdChi2norm_cr = new TH1F("IPP_W3J_BSdChi2norm_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_W2J_BSdChi2norm_cr = new TH1F("IPP_W2J_BSdChi2norm_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_W1J_BSdChi2norm_cr = new TH1F("IPP_W1J_BSdChi2norm_cr","IPP Beam spot distance",30,0,1);
//TH1F* IPP_TTZ_BSdChi2norm_cr = new TH1F("IPP_TTZ_BSdChi2norm_cr","IPP Beam spot distance",30,0,1);
//TH1F* IPP_WW_BSdChi2norm_cr = new TH1F("IPP_WW_BSdChi2norm_cr","IPP Beam spot distance",30,0,1);
//TH1F* IPP_WZ_BSdChi2norm_cr = new TH1F("IPP_WZ_BSdChi2norm_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW200_BSdChi2norm_cr = new TH1F("IPP_LW200_BSdChi2norm_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW300_BSdChi2norm_cr = new TH1F("IPP_LW300_BSdChi2norm_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW400_BSdChi2norm_cr = new TH1F("IPP_LW400_BSdChi2norm_cr","IPP Beam spot distance",30,0,1);
TH1F* IPP_LW500_BSdChi2norm_cr = new TH1F("IPP_LW500_BSdChi2norm_cr","IPP Beam spot distance",30,0,1);


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
  std::vector<TH1F*> Uhists;

  // Declaration of example leaf types
  Int_t           run;
  UInt_t          luminosityBlock;
  ULong64_t	   event;
  Int_t           PV_npvs;
  Int_t           PV_npvsGood;
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
  vector<float>   *electron_ch;
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
  vector<float>   *Esecvec_posx;
  vector<float>   *Esecvec_posy;
  vector<float>   *Esecvec_posz;
  vector<float>   *Esecvec_poserrorx;
  vector<float>   *Esecvec_poserrory;
  vector<float>   *Esecvec_poserrorz;
  vector<size_t>   *Esecvec_eleTag;
  vector<float>   *Esecvec_normchi2;
  vector<float>   *Esecvec_px;
  vector<float>   *Esecvec_py;
  vector<float>   *Bsp_x;
  vector<float>   *Bsp_y;
  vector<float>   *Bsp_z;
  vector<float>   *Bsp_widthx;
  vector<float>   *Bsp_widthy;
  Float_t         met_pt;
  Float_t         met_phi;

  // List of example branches
  TBranch        *b_run;   //!
  TBranch        *b_luminosityBlock;   //!
  TBranch        *b_event;   //!
  TBranch        *b_PV_npvs;   //!
  TBranch        *b_PV_npvsGood;   //!
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
  TBranch        *b_electron_ch;
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
  TBranch    *b_Esecvec_posx;
  TBranch    *b_Esecvec_posy;
  TBranch    *b_Esecvec_posz;
  TBranch    *b_Esecvec_poserrorx;
  TBranch    *b_Esecvec_poserrory;
  TBranch    *b_Esecvec_poserrorz;
  TBranch    *b_Esecvec_eleTag;
  TBranch    *b_Esecvec_normchi2;
  TBranch    *b_Esecvec_px;
  TBranch    *b_Esecvec_py;
  TBranch    *b_Bsp_x;
  TBranch    *b_Bsp_y;
  TBranch    *b_Bsp_z;
  TBranch    *b_Bsp_widthx;
  TBranch    *b_Bsp_widthy;

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
  hists.clear();
  Uhists.clear();

  //Load histograms for uncertainty
  Uhists.push_back(NF_dataRunB_ppoint_uncert);
  Uhists.push_back(NF_dataRunC_ppoint_uncert);
  Uhists.push_back(NF_ZLL_ppoint_uncert);
  Uhists.push_back(NF_TT_ppoint_uncert);
  Uhists.push_back(NF_W3J_ppoint_uncert);
  Uhists.push_back(NF_W2J_ppoint_uncert);
  Uhists.push_back(NF_W1J_ppoint_uncert);
  Uhists.push_back(NF_LW200_ppoint_uncert);

  Uhists.push_back(TF_dataRunB_ppoint_uncert);
  Uhists.push_back(TF_dataRunC_ppoint_uncert);
  Uhists.push_back(TF_ZLL_ppoint_uncert);
  Uhists.push_back(TF_TT_ppoint_uncert);
  Uhists.push_back(TF_W3J_ppoint_uncert);
  Uhists.push_back(TF_W2J_ppoint_uncert);
  Uhists.push_back(TF_W1J_ppoint_uncert);
  Uhists.push_back(TF_LW200_ppoint_uncert);

  Uhists.push_back(TO_dataRunB_ppoint_uncert);
  Uhists.push_back(TO_dataRunC_ppoint_uncert);
  Uhists.push_back(TO_ZLL_ppoint_uncert);
  Uhists.push_back(TO_TT_ppoint_uncert);
  Uhists.push_back(TO_W3J_ppoint_uncert);
  Uhists.push_back(TO_W2J_ppoint_uncert);
  Uhists.push_back(TO_W1J_ppoint_uncert);
  Uhists.push_back(TO_LW200_ppoint_uncert);

  Uhists.push_back(HQ_dataRunB_ppoint_uncert);
  Uhists.push_back(HQ_dataRunC_ppoint_uncert);
  Uhists.push_back(HQ_ZLL_ppoint_uncert);
  Uhists.push_back(HQ_TT_ppoint_uncert);
  Uhists.push_back(HQ_W3J_ppoint_uncert);
  Uhists.push_back(HQ_W2J_ppoint_uncert);
  Uhists.push_back(HQ_W1J_ppoint_uncert);
  Uhists.push_back(HQ_LW200_ppoint_uncert);

  Uhists.push_back(JetS_dataRunB_ppoint_uncert);
  Uhists.push_back(JetS_dataRunC_ppoint_uncert);
  Uhists.push_back(JetS_ZLL_ppoint_uncert);
  Uhists.push_back(JetS_TT_ppoint_uncert);
  Uhists.push_back(JetS_W3J_ppoint_uncert);
  Uhists.push_back(JetS_W2J_ppoint_uncert);
  Uhists.push_back(JetS_W1J_ppoint_uncert);
  Uhists.push_back(JetS_LW200_ppoint_uncert);

  Uhists.push_back(DRC_dataRunB_ppoint_uncert);
  Uhists.push_back(DRC_dataRunC_ppoint_uncert);
  Uhists.push_back(DRC_ZLL_ppoint_uncert);
  Uhists.push_back(DRC_TT_ppoint_uncert);
  Uhists.push_back(DRC_W3J_ppoint_uncert);
  Uhists.push_back(DRC_W2J_ppoint_uncert);
  Uhists.push_back(DRC_W1J_ppoint_uncert);
  Uhists.push_back(DRC_LW200_ppoint_uncert);

  Uhists.push_back(SG_dataRunB_ppoint_uncert);
  Uhists.push_back(SG_dataRunC_ppoint_uncert);
  Uhists.push_back(SG_ZLL_ppoint_uncert);
  Uhists.push_back(SG_TT_ppoint_uncert);
  Uhists.push_back(SG_W3J_ppoint_uncert);
  Uhists.push_back(SG_W2J_ppoint_uncert);
  Uhists.push_back(SG_W1J_ppoint_uncert);
  Uhists.push_back(SG_LW200_ppoint_uncert);

  Uhists.push_back(IPP_dataRunB_ppoint_uncert);
  Uhists.push_back(IPP_dataRunC_ppoint_uncert);
  Uhists.push_back(IPP_ZLL_ppoint_uncert);
  Uhists.push_back(IPP_TT_ppoint_uncert);
  Uhists.push_back(IPP_W3J_ppoint_uncert);
  Uhists.push_back(IPP_W2J_ppoint_uncert);
  Uhists.push_back(IPP_W1J_ppoint_uncert);
  Uhists.push_back(IPP_LW200_ppoint_uncert);

  //Load histograms for signal region
  hists.push_back(NF_dataRunB_ppointS);
  hists.push_back(NF_dataRunC_ppointS );
  hists.push_back(NF_ZLL_ppointS);
  hists.push_back(NF_TT_ppointS);
  hists.push_back(NF_W3J_ppointS);
  hists.push_back(NF_W2J_ppointS);
  hists.push_back(NF_W1J_ppointS);
  //hists.push_back(//NF_TTZ_ppointS);
  //hists.push_back(//NF_WW_ppointS);
  //hists.push_back(//NF_WZ_ppointS);
  hists.push_back(NF_LW200_ppointS);
  hists.push_back(NF_LW300_ppointS);
  hists.push_back(NF_LW400_ppointS);
  hists.push_back(NF_LW500_ppointS);
  hists.push_back(NF_dataRunB_ppoint);
  hists.push_back(NF_dataRunC_ppoint );
  hists.push_back(NF_ZLL_ppoint);
  hists.push_back(NF_TT_ppoint);
  hists.push_back(NF_W3J_ppoint);
  hists.push_back(NF_W2J_ppoint);
  hists.push_back(NF_W1J_ppoint);
  //hists.push_back(//NF_TTZ_ppoint);
  //hists.push_back(//NF_WW_ppoint);
  //hists.push_back(//NF_WZ_ppoint);
  hists.push_back(NF_LW200_ppoint);
  hists.push_back(NF_LW300_ppoint);
  hists.push_back(NF_LW400_ppoint);
  hists.push_back(NF_LW500_ppoint);
  hists.push_back(NF_dataRunB_npv);
  hists.push_back(NF_dataRunC_npv );
  hists.push_back(NF_ZLL_npv);
  hists.push_back(NF_TT_npv);
  hists.push_back(NF_W3J_npv);
  hists.push_back(NF_W2J_npv);
  hists.push_back(NF_W1J_npv);
  //hists.push_back(//NF_TTZ_npv);
  //hists.push_back(//NF_WW_npv);
  //hists.push_back(//NF_WZ_npv);
  hists.push_back(NF_LW200_npv);
  hists.push_back(NF_LW300_npv);
  hists.push_back(NF_LW400_npv);
  hists.push_back(NF_LW500_npv);
  hists.push_back(NF_dataRunB_nsv);
  hists.push_back(NF_dataRunC_nsv );
  hists.push_back(NF_ZLL_nsv);
  hists.push_back(NF_TT_nsv);
  hists.push_back(NF_W3J_nsv);
  hists.push_back(NF_W2J_nsv);
  hists.push_back(NF_W1J_nsv);
  //hists.push_back(//NF_TTZ_nsv);
  //hists.push_back(//NF_WW_nsv);
  //hists.push_back(//NF_WZ_nsv);
  hists.push_back(NF_LW200_nsv);
  hists.push_back(NF_LW300_nsv);
  hists.push_back(NF_LW400_nsv);
  hists.push_back(NF_LW500_nsv);
  hists.push_back(NF_dataRunB_svd);
  hists.push_back(NF_dataRunC_svd );
  hists.push_back(NF_ZLL_svd);
  hists.push_back(NF_TT_svd);
  hists.push_back(NF_W3J_svd);
  hists.push_back(NF_W2J_svd);
  hists.push_back(NF_W1J_svd);
  //hists.push_back(//NF_TTZ_svd);
  //hists.push_back(//NF_WW_svd);
  //hists.push_back(//NF_WZ_svd);
  hists.push_back(NF_LW200_svd);
  hists.push_back(NF_LW300_svd);
  hists.push_back(NF_LW400_svd);
  hists.push_back(NF_LW500_svd);
  hists.push_back(NF_dataRunB_BSd);
  hists.push_back(NF_dataRunC_BSd );
  hists.push_back(NF_ZLL_BSd);
  hists.push_back(NF_TT_BSd);
  hists.push_back(NF_W3J_BSd);
  hists.push_back(NF_W2J_BSd);
  hists.push_back(NF_W1J_BSd);
  //hists.push_back(NF_TTZ_BSd);
  //hists.push_back(NF_WW_BSd);
  //hists.push_back(NF_WZ_BSd);
  hists.push_back(NF_LW200_BSd);
  hists.push_back(NF_LW300_BSd);
  hists.push_back(NF_LW400_BSd);
  hists.push_back(NF_LW500_BSd);
  hists.push_back(NF_dataRunB_BSdChi2norm);
  hists.push_back(NF_dataRunC_BSdChi2norm );
  hists.push_back(NF_ZLL_BSdChi2norm);
  hists.push_back(NF_TT_BSdChi2norm);
  hists.push_back(NF_W3J_BSdChi2norm);
  hists.push_back(NF_W2J_BSdChi2norm);
  hists.push_back(NF_W1J_BSdChi2norm);
  //hists.push_back(NF_TTZ_BSdChi2norm);
  //hists.push_back(NF_WW_BSdChi2norm);
  //hists.push_back(NF_WZ_BSdChi2norm);
  hists.push_back(NF_LW200_BSdChi2norm);
  hists.push_back(NF_LW300_BSdChi2norm);
  hists.push_back(NF_LW400_BSdChi2norm);
  hists.push_back(NF_LW500_BSdChi2norm);
  //Histograms for signal region TF
  hists.push_back(TF_dataRunB_ppointS);
  hists.push_back(TF_dataRunC_ppointS );
  hists.push_back(TF_ZLL_ppointS);
  hists.push_back(TF_TT_ppointS);
  hists.push_back(TF_W3J_ppointS);
  hists.push_back(TF_W2J_ppointS);
  hists.push_back(TF_W1J_ppointS);
  //hists.push_back(//TF_TTZ_ppointS);
  //hists.push_back(//TF_WW_ppointS);
  //hists.push_back(//TF_WZ_ppointS);
  hists.push_back(TF_LW200_ppointS);
  hists.push_back(TF_LW300_ppointS);
  hists.push_back(TF_LW400_ppointS);
  hists.push_back(TF_LW500_ppointS);
  hists.push_back(TF_dataRunB_ppoint);
  hists.push_back(TF_dataRunC_ppoint );
  hists.push_back(TF_ZLL_ppoint);
  hists.push_back(TF_TT_ppoint);
  hists.push_back(TF_W3J_ppoint);
  hists.push_back(TF_W2J_ppoint);
  hists.push_back(TF_W1J_ppoint);
  //hists.push_back(//TF_TTZ_ppoint);
  //hists.push_back(//TF_WW_ppoint);
  //hists.push_back(//TF_WZ_ppoint);
  hists.push_back(TF_LW200_ppoint);
  hists.push_back(TF_LW300_ppoint);
  hists.push_back(TF_LW400_ppoint);
  hists.push_back(TF_LW500_ppoint);
  hists.push_back(TF_dataRunB_npv);
  hists.push_back(TF_dataRunC_npv );
  hists.push_back(TF_ZLL_npv);
  hists.push_back(TF_TT_npv);
  hists.push_back(TF_W3J_npv);
  hists.push_back(TF_W2J_npv);
  hists.push_back(TF_W1J_npv);
  //hists.push_back(//TF_TTZ_npv);
  //hists.push_back(//TF_WW_npv);
  //hists.push_back(//TF_WZ_npv);
  hists.push_back(TF_LW200_npv);
  hists.push_back(TF_LW300_npv);
  hists.push_back(TF_LW400_npv);
  hists.push_back(TF_LW500_npv);
  hists.push_back(TF_dataRunB_nsv);
  hists.push_back(TF_dataRunC_nsv );
  hists.push_back(TF_ZLL_nsv);
  hists.push_back(TF_TT_nsv);
  hists.push_back(TF_W3J_nsv);
  hists.push_back(TF_W2J_nsv);
  hists.push_back(TF_W1J_nsv);
  //hists.push_back(//TF_TTZ_nsv);
  //hists.push_back(//TF_WW_nsv);
  //hists.push_back(//TF_WZ_nsv);
  hists.push_back(TF_LW200_nsv);
  hists.push_back(TF_LW300_nsv);
  hists.push_back(TF_LW400_nsv);
  hists.push_back(TF_LW500_nsv);
  hists.push_back(TF_dataRunB_svd);
  hists.push_back(TF_dataRunC_svd );
  hists.push_back(TF_ZLL_svd);
  hists.push_back(TF_TT_svd);
  hists.push_back(TF_W3J_svd);
  hists.push_back(TF_W2J_svd);
  hists.push_back(TF_W1J_svd);
  //hists.push_back(//TF_TTZ_svd);
  //hists.push_back(//TF_WW_svd);
  //hists.push_back(//TF_WZ_svd);
  hists.push_back(TF_LW200_svd);
  hists.push_back(TF_LW300_svd);
  hists.push_back(TF_LW400_svd);
  hists.push_back(TF_LW500_svd);
  hists.push_back(TF_dataRunB_BSd);
  hists.push_back(TF_dataRunC_BSd );
  hists.push_back(TF_ZLL_BSd);
  hists.push_back(TF_TT_BSd);
  hists.push_back(TF_W3J_BSd);
  hists.push_back(TF_W2J_BSd);
  hists.push_back(TF_W1J_BSd);
  //hists.push_back(TF_TTZ_BSd);
  //hists.push_back(TF_WW_BSd);
  //hists.push_back(TF_WZ_BSd);
  hists.push_back(TF_LW200_BSd);
  hists.push_back(TF_LW300_BSd);
  hists.push_back(TF_LW400_BSd);
  hists.push_back(TF_LW500_BSd);
  hists.push_back(TF_dataRunB_BSdChi2norm);
  hists.push_back(TF_dataRunC_BSdChi2norm );
  hists.push_back(TF_ZLL_BSdChi2norm);
  hists.push_back(TF_TT_BSdChi2norm);
  hists.push_back(TF_W3J_BSdChi2norm);
  hists.push_back(TF_W2J_BSdChi2norm);
  hists.push_back(TF_W1J_BSdChi2norm);
  //hists.push_back(TF_TTZ_BSdChi2norm);
  //hists.push_back(TF_WW_BSdChi2norm);
  //hists.push_back(TF_WZ_BSdChi2norm);
  hists.push_back(TF_LW200_BSdChi2norm);
  hists.push_back(TF_LW300_BSdChi2norm);
  hists.push_back(TF_LW400_BSdChi2norm);
  hists.push_back(TF_LW500_BSdChi2norm);
  //Histograms for signal region TO
  hists.push_back(TO_dataRunB_ppointS);
  hists.push_back(TO_dataRunC_ppointS );
  hists.push_back(TO_ZLL_ppointS);
  hists.push_back(TO_TT_ppointS);
  hists.push_back(TO_W3J_ppointS);
  hists.push_back(TO_W2J_ppointS);
  hists.push_back(TO_W1J_ppointS);
  //hists.push_back(//TO_TTZ_ppointS);
  //hists.push_back(//TO_WW_ppointS);
  //hists.push_back(//TO_WZ_ppointS);
  hists.push_back(TO_LW200_ppointS);
  hists.push_back(TO_LW300_ppointS);
  hists.push_back(TO_LW400_ppointS);
  hists.push_back(TO_LW500_ppointS);
  hists.push_back(TO_dataRunB_ppoint);
  hists.push_back(TO_dataRunC_ppoint );
  hists.push_back(TO_ZLL_ppoint);
  hists.push_back(TO_TT_ppoint);
  hists.push_back(TO_W3J_ppoint);
  hists.push_back(TO_W2J_ppoint);
  hists.push_back(TO_W1J_ppoint);
  //hists.push_back(//TO_TTZ_ppoint);
  //hists.push_back(//TO_WW_ppoint);
  //hists.push_back(//TO_WZ_ppoint);
  hists.push_back(TO_LW200_ppoint);
  hists.push_back(TO_LW300_ppoint);
  hists.push_back(TO_LW400_ppoint);
  hists.push_back(TO_LW500_ppoint);
  hists.push_back(TO_dataRunB_npv);
  hists.push_back(TO_dataRunC_npv );
  hists.push_back(TO_ZLL_npv);
  hists.push_back(TO_TT_npv);
  hists.push_back(TO_W3J_npv);
  hists.push_back(TO_W2J_npv);
  hists.push_back(TO_W1J_npv);
  //hists.push_back(//TO_TTZ_npv);
  //hists.push_back(//TO_WW_npv);
  //hists.push_back(//TO_WZ_npv);
  hists.push_back(TO_LW200_npv);
  hists.push_back(TO_LW300_npv);
  hists.push_back(TO_LW400_npv);
  hists.push_back(TO_LW500_npv);
  hists.push_back(TO_dataRunB_nsv);
  hists.push_back(TO_dataRunC_nsv );
  hists.push_back(TO_ZLL_nsv);
  hists.push_back(TO_TT_nsv);
  hists.push_back(TO_W3J_nsv);
  hists.push_back(TO_W2J_nsv);
  hists.push_back(TO_W1J_nsv);
  //hists.push_back(//TO_TTZ_nsv);
  //hists.push_back(//TO_WW_nsv);
  //hists.push_back(//TO_WZ_nsv);
  hists.push_back(TO_LW200_nsv);
  hists.push_back(TO_LW300_nsv);
  hists.push_back(TO_LW400_nsv);
  hists.push_back(TO_LW500_nsv);
  hists.push_back(TO_dataRunB_svd);
  hists.push_back(TO_dataRunC_svd );
  hists.push_back(TO_ZLL_svd);
  hists.push_back(TO_TT_svd);
  hists.push_back(TO_W3J_svd);
  hists.push_back(TO_W2J_svd);
  hists.push_back(TO_W1J_svd);
  //hists.push_back(//TO_TTZ_svd);
  //hists.push_back(//TO_WW_svd);
  //hists.push_back(//TO_WZ_svd);
  hists.push_back(TO_LW200_svd);
  hists.push_back(TO_LW300_svd);
  hists.push_back(TO_LW400_svd);
  hists.push_back(TO_LW500_svd);
  hists.push_back(TO_dataRunB_BSd);
  hists.push_back(TO_dataRunC_BSd );
  hists.push_back(TO_ZLL_BSd);
  hists.push_back(TO_TT_BSd);
  hists.push_back(TO_W3J_BSd);
  hists.push_back(TO_W2J_BSd);
  hists.push_back(TO_W1J_BSd);
  //hists.push_back(TO_TTZ_BSd);
  //hists.push_back(TO_WW_BSd);
  //hists.push_back(TO_WZ_BSd);
  hists.push_back(TO_LW200_BSd);
  hists.push_back(TO_LW300_BSd);
  hists.push_back(TO_LW400_BSd);
  hists.push_back(TO_LW500_BSd);
  hists.push_back(TO_dataRunB_BSdChi2norm);
  hists.push_back(TO_dataRunC_BSdChi2norm );
  hists.push_back(TO_ZLL_BSdChi2norm);
  hists.push_back(TO_TT_BSdChi2norm);
  hists.push_back(TO_W3J_BSdChi2norm);
  hists.push_back(TO_W2J_BSdChi2norm);
  hists.push_back(TO_W1J_BSdChi2norm);
  //hists.push_back(TO_TTZ_BSdChi2norm);
  //hists.push_back(TO_WW_BSdChi2norm);
  //hists.push_back(TO_WZ_BSdChi2norm);
  hists.push_back(TO_LW200_BSdChi2norm);
  hists.push_back(TO_LW300_BSdChi2norm);
  hists.push_back(TO_LW400_BSdChi2norm);
  hists.push_back(TO_LW500_BSdChi2norm);
  //Histograms for signal region HQ
  hists.push_back(HQ_dataRunB_ppointS);
  hists.push_back(HQ_dataRunC_ppointS );
  hists.push_back(HQ_ZLL_ppointS);
  hists.push_back(HQ_TT_ppointS);
  hists.push_back(HQ_W3J_ppointS);
  hists.push_back(HQ_W2J_ppointS);
  hists.push_back(HQ_W1J_ppointS);
  //hists.push_back(//HQ_TTZ_ppointS);
  //hists.push_back(//HQ_WW_ppointS);
  //hists.push_back(//HQ_WZ_ppointS);
  hists.push_back(HQ_LW200_ppointS);
  hists.push_back(HQ_LW300_ppointS);
  hists.push_back(HQ_LW400_ppointS);
  hists.push_back(HQ_LW500_ppointS);
  hists.push_back(HQ_dataRunB_ppoint);
  hists.push_back(HQ_dataRunC_ppoint );
  hists.push_back(HQ_ZLL_ppoint);
  hists.push_back(HQ_TT_ppoint);
  hists.push_back(HQ_W3J_ppoint);
  hists.push_back(HQ_W2J_ppoint);
  hists.push_back(HQ_W1J_ppoint);
  //hists.push_back(//HQ_TTZ_ppoint);
  //hists.push_back(//HQ_WW_ppoint);
  //hists.push_back(//HQ_WZ_ppoint);
  hists.push_back(HQ_LW200_ppoint);
  hists.push_back(HQ_LW300_ppoint);
  hists.push_back(HQ_LW400_ppoint);
  hists.push_back(HQ_LW500_ppoint);
  hists.push_back(HQ_dataRunB_npv);
  hists.push_back(HQ_dataRunC_npv );
  hists.push_back(HQ_ZLL_npv);
  hists.push_back(HQ_TT_npv);
  hists.push_back(HQ_W3J_npv);
  hists.push_back(HQ_W2J_npv);
  hists.push_back(HQ_W1J_npv);
  //hists.push_back(//HQ_TTZ_npv);
  //hists.push_back(//HQ_WW_npv);
  //hists.push_back(//HQ_WZ_npv);
  hists.push_back(HQ_LW200_npv);
  hists.push_back(HQ_LW300_npv);
  hists.push_back(HQ_LW400_npv);
  hists.push_back(HQ_LW500_npv);
  hists.push_back(HQ_dataRunB_nsv);
  hists.push_back(HQ_dataRunC_nsv );
  hists.push_back(HQ_ZLL_nsv);
  hists.push_back(HQ_TT_nsv);
  hists.push_back(HQ_W3J_nsv);
  hists.push_back(HQ_W2J_nsv);
  hists.push_back(HQ_W1J_nsv);
  //hists.push_back(//HQ_TTZ_nsv);
  //hists.push_back(//HQ_WW_nsv);
  //hists.push_back(//HQ_WZ_nsv);
  hists.push_back(HQ_LW200_nsv);
  hists.push_back(HQ_LW300_nsv);
  hists.push_back(HQ_LW400_nsv);
  hists.push_back(HQ_LW500_nsv);
  hists.push_back(HQ_dataRunB_svd);
  hists.push_back(HQ_dataRunC_svd );
  hists.push_back(HQ_ZLL_svd);
  hists.push_back(HQ_TT_svd);
  hists.push_back(HQ_W3J_svd);
  hists.push_back(HQ_W2J_svd);
  hists.push_back(HQ_W1J_svd);
  //hists.push_back(//HQ_TTZ_svd);
  //hists.push_back(//HQ_WW_svd);
  //hists.push_back(//HQ_WZ_svd);
  hists.push_back(HQ_LW200_svd);
  hists.push_back(HQ_LW300_svd);
  hists.push_back(HQ_LW400_svd);
  hists.push_back(HQ_LW500_svd);
  hists.push_back(HQ_dataRunB_BSd);
  hists.push_back(HQ_dataRunC_BSd );
  hists.push_back(HQ_ZLL_BSd);
  hists.push_back(HQ_TT_BSd);
  hists.push_back(HQ_W3J_BSd);
  hists.push_back(HQ_W2J_BSd);
  hists.push_back(HQ_W1J_BSd);
  //hists.push_back(HQ_TTZ_BSd);
  //hists.push_back(HQ_WW_BSd);
  //hists.push_back(HQ_WZ_BSd);
  hists.push_back(HQ_LW200_BSd);
  hists.push_back(HQ_LW300_BSd);
  hists.push_back(HQ_LW400_BSd);
  hists.push_back(HQ_LW500_BSd);
  hists.push_back(HQ_dataRunB_BSdChi2norm);
  hists.push_back(HQ_dataRunC_BSdChi2norm );
  hists.push_back(HQ_ZLL_BSdChi2norm);
  hists.push_back(HQ_TT_BSdChi2norm);
  hists.push_back(HQ_W3J_BSdChi2norm);
  hists.push_back(HQ_W2J_BSdChi2norm);
  hists.push_back(HQ_W1J_BSdChi2norm);
  //hists.push_back(HQ_TTZ_BSdChi2norm);
  //hists.push_back(HQ_WW_BSdChi2norm);
  //hists.push_back(HQ_WZ_BSdChi2norm);
  hists.push_back(HQ_LW200_BSdChi2norm);
  hists.push_back(HQ_LW300_BSdChi2norm);
  hists.push_back(HQ_LW400_BSdChi2norm);
  hists.push_back(HQ_LW500_BSdChi2norm);
  //Histograms for signal region JetS
  hists.push_back(JetS_dataRunB_ppointS);
  hists.push_back(JetS_dataRunC_ppointS );
  hists.push_back(JetS_ZLL_ppointS);
  hists.push_back(JetS_TT_ppointS);
  hists.push_back(JetS_W3J_ppointS);
  hists.push_back(JetS_W2J_ppointS);
  hists.push_back(JetS_W1J_ppointS);
  //hists.push_back(//JetS_TTZ_ppointS);
  //hists.push_back(//JetS_WW_ppointS);
  //hists.push_back(//JetS_WZ_ppointS);
  hists.push_back(JetS_LW200_ppointS);
  hists.push_back(JetS_LW300_ppointS);
  hists.push_back(JetS_LW400_ppointS);
  hists.push_back(JetS_LW500_ppointS);
  hists.push_back(JetS_dataRunB_ppoint);
  hists.push_back(JetS_dataRunC_ppoint );
  hists.push_back(JetS_ZLL_ppoint);
  hists.push_back(JetS_TT_ppoint);
  hists.push_back(JetS_W3J_ppoint);
  hists.push_back(JetS_W2J_ppoint);
  hists.push_back(JetS_W1J_ppoint);
  //hists.push_back(//JetS_TTZ_ppoint);
  //hists.push_back(//JetS_WW_ppoint);
  //hists.push_back(//JetS_WZ_ppoint);
  hists.push_back(JetS_LW200_ppoint);
  hists.push_back(JetS_LW300_ppoint);
  hists.push_back(JetS_LW400_ppoint);
  hists.push_back(JetS_LW500_ppoint);
  hists.push_back(JetS_dataRunB_npv);
  hists.push_back(JetS_dataRunC_npv );
  hists.push_back(JetS_ZLL_npv);
  hists.push_back(JetS_TT_npv);
  hists.push_back(JetS_W3J_npv);
  hists.push_back(JetS_W2J_npv);
  hists.push_back(JetS_W1J_npv);
  //hists.push_back(//JetS_TTZ_npv);
  //hists.push_back(//JetS_WW_npv);
  //hists.push_back(//JetS_WZ_npv);
  hists.push_back(JetS_LW200_npv);
  hists.push_back(JetS_LW300_npv);
  hists.push_back(JetS_LW400_npv);
  hists.push_back(JetS_LW500_npv);
  hists.push_back(JetS_dataRunB_nsv);
  hists.push_back(JetS_dataRunC_nsv );
  hists.push_back(JetS_ZLL_nsv);
  hists.push_back(JetS_TT_nsv);
  hists.push_back(JetS_W3J_nsv);
  hists.push_back(JetS_W2J_nsv);
  hists.push_back(JetS_W1J_nsv);
  //hists.push_back(//JetS_TTZ_nsv);
  //hists.push_back(//JetS_WW_nsv);
  //hists.push_back(//JetS_WZ_nsv);
  hists.push_back(JetS_LW200_nsv);
  hists.push_back(JetS_LW300_nsv);
  hists.push_back(JetS_LW400_nsv);
  hists.push_back(JetS_LW500_nsv);
  hists.push_back(JetS_dataRunB_svd);
  hists.push_back(JetS_dataRunC_svd );
  hists.push_back(JetS_ZLL_svd);
  hists.push_back(JetS_TT_svd);
  hists.push_back(JetS_W3J_svd);
  hists.push_back(JetS_W2J_svd);
  hists.push_back(JetS_W1J_svd);
  //hists.push_back(//JetS_TTZ_svd);
  //hists.push_back(//JetS_WW_svd);
  //hists.push_back(//JetS_WZ_svd);
  hists.push_back(JetS_LW200_svd);
  hists.push_back(JetS_LW300_svd);
  hists.push_back(JetS_LW400_svd);
  hists.push_back(JetS_LW500_svd);
  hists.push_back(JetS_dataRunB_BSd);
  hists.push_back(JetS_dataRunC_BSd );
  hists.push_back(JetS_ZLL_BSd);
  hists.push_back(JetS_TT_BSd);
  hists.push_back(JetS_W3J_BSd);
  hists.push_back(JetS_W2J_BSd);
  hists.push_back(JetS_W1J_BSd);
  //hists.push_back(JetS_TTZ_BSd);
  //hists.push_back(JetS_WW_BSd);
  //hists.push_back(JetS_WZ_BSd);
  hists.push_back(JetS_LW200_BSd);
  hists.push_back(JetS_LW300_BSd);
  hists.push_back(JetS_LW400_BSd);
  hists.push_back(JetS_LW500_BSd);
  hists.push_back(JetS_dataRunB_BSdChi2norm);
  hists.push_back(JetS_dataRunC_BSdChi2norm );
  hists.push_back(JetS_ZLL_BSdChi2norm);
  hists.push_back(JetS_TT_BSdChi2norm);
  hists.push_back(JetS_W3J_BSdChi2norm);
  hists.push_back(JetS_W2J_BSdChi2norm);
  hists.push_back(JetS_W1J_BSdChi2norm);
  //hists.push_back(JetS_TTZ_BSdChi2norm);
  //hists.push_back(JetS_WW_BSdChi2norm);
  //hists.push_back(JetS_WZ_BSdChi2norm);
  hists.push_back(JetS_LW200_BSdChi2norm);
  hists.push_back(JetS_LW300_BSdChi2norm);
  hists.push_back(JetS_LW400_BSdChi2norm);
  hists.push_back(JetS_LW500_BSdChi2norm);
  //Histograms for signal region DRC
  hists.push_back(DRC_dataRunB_ppointS);
  hists.push_back(DRC_dataRunC_ppointS );
  hists.push_back(DRC_ZLL_ppointS);
  hists.push_back(DRC_TT_ppointS);
  hists.push_back(DRC_W3J_ppointS);
  hists.push_back(DRC_W2J_ppointS);
  hists.push_back(DRC_W1J_ppointS);
  //hists.push_back(//DRC_TTZ_ppointS);
  //hists.push_back(//DRC_WW_ppointS);
  //hists.push_back(//DRC_WZ_ppointS);
  hists.push_back(DRC_LW200_ppointS);
  hists.push_back(DRC_LW300_ppointS);
  hists.push_back(DRC_LW400_ppointS);
  hists.push_back(DRC_LW500_ppointS);
  hists.push_back(DRC_dataRunB_ppoint);
  hists.push_back(DRC_dataRunC_ppoint );
  hists.push_back(DRC_ZLL_ppoint);
  hists.push_back(DRC_TT_ppoint);
  hists.push_back(DRC_W3J_ppoint);
  hists.push_back(DRC_W2J_ppoint);
  hists.push_back(DRC_W1J_ppoint);
  //hists.push_back(//DRC_TTZ_ppoint);
  //hists.push_back(//DRC_WW_ppoint);
  //hists.push_back(//DRC_WZ_ppoint);
  hists.push_back(DRC_LW200_ppoint);
  hists.push_back(DRC_LW300_ppoint);
  hists.push_back(DRC_LW400_ppoint);
  hists.push_back(DRC_LW500_ppoint);
  hists.push_back(DRC_dataRunB_npv);
  hists.push_back(DRC_dataRunC_npv );
  hists.push_back(DRC_ZLL_npv);
  hists.push_back(DRC_TT_npv);
  hists.push_back(DRC_W3J_npv);
  hists.push_back(DRC_W2J_npv);
  hists.push_back(DRC_W1J_npv);
  //hists.push_back(//DRC_TTZ_npv);
  //hists.push_back(//DRC_WW_npv);
  //hists.push_back(//DRC_WZ_npv);
  hists.push_back(DRC_LW200_npv);
  hists.push_back(DRC_LW300_npv);
  hists.push_back(DRC_LW400_npv);
  hists.push_back(DRC_LW500_npv);
  hists.push_back(DRC_dataRunB_nsv);
  hists.push_back(DRC_dataRunC_nsv );
  hists.push_back(DRC_ZLL_nsv);
  hists.push_back(DRC_TT_nsv);
  hists.push_back(DRC_W3J_nsv);
  hists.push_back(DRC_W2J_nsv);
  hists.push_back(DRC_W1J_nsv);
  //hists.push_back(//DRC_TTZ_nsv);
  //hists.push_back(//DRC_WW_nsv);
  //hists.push_back(//DRC_WZ_nsv);
  hists.push_back(DRC_LW200_nsv);
  hists.push_back(DRC_LW300_nsv);
  hists.push_back(DRC_LW400_nsv);
  hists.push_back(DRC_LW500_nsv);
  hists.push_back(DRC_dataRunB_svd);
  hists.push_back(DRC_dataRunC_svd );
  hists.push_back(DRC_ZLL_svd);
  hists.push_back(DRC_TT_svd);
  hists.push_back(DRC_W3J_svd);
  hists.push_back(DRC_W2J_svd);
  hists.push_back(DRC_W1J_svd);
  //hists.push_back(//DRC_TTZ_svd);
  //hists.push_back(//DRC_WW_svd);
  //hists.push_back(//DRC_WZ_svd);
  hists.push_back(DRC_LW200_svd);
  hists.push_back(DRC_LW300_svd);
  hists.push_back(DRC_LW400_svd);
  hists.push_back(DRC_LW500_svd);
  hists.push_back(DRC_dataRunB_BSd);
  hists.push_back(DRC_dataRunC_BSd );
  hists.push_back(DRC_ZLL_BSd);
  hists.push_back(DRC_TT_BSd);
  hists.push_back(DRC_W3J_BSd);
  hists.push_back(DRC_W2J_BSd);
  hists.push_back(DRC_W1J_BSd);
  //hists.push_back(DRC_TTZ_BSd);
  //hists.push_back(DRC_WW_BSd);
  //hists.push_back(DRC_WZ_BSd);
  hists.push_back(DRC_LW200_BSd);
  hists.push_back(DRC_LW300_BSd);
  hists.push_back(DRC_LW400_BSd);
  hists.push_back(DRC_LW500_BSd);
  hists.push_back(DRC_dataRunB_BSdChi2norm);
  hists.push_back(DRC_dataRunC_BSdChi2norm );
  hists.push_back(DRC_ZLL_BSdChi2norm);
  hists.push_back(DRC_TT_BSdChi2norm);
  hists.push_back(DRC_W3J_BSdChi2norm);
  hists.push_back(DRC_W2J_BSdChi2norm);
  hists.push_back(DRC_W1J_BSdChi2norm);
  //hists.push_back(DRC_TTZ_BSdChi2norm);
  //hists.push_back(DRC_WW_BSdChi2norm);
  //hists.push_back(DRC_WZ_BSdChi2norm);
  hists.push_back(DRC_LW200_BSdChi2norm);
  hists.push_back(DRC_LW300_BSdChi2norm);
  hists.push_back(DRC_LW400_BSdChi2norm);
  hists.push_back(DRC_LW500_BSdChi2norm);
  //Histograms for signal region SG
  hists.push_back(SG_dataRunB_ppointS);
  hists.push_back(SG_dataRunC_ppointS );
  hists.push_back(SG_ZLL_ppointS);
  hists.push_back(SG_TT_ppointS);
  hists.push_back(SG_W3J_ppointS);
  hists.push_back(SG_W2J_ppointS);
  hists.push_back(SG_W1J_ppointS);
  //hists.push_back(//SG_TTZ_ppointS);
  //hists.push_back(//SG_WW_ppointS);
  //hists.push_back(//SG_WZ_ppointS);
  hists.push_back(SG_LW200_ppointS);
  hists.push_back(SG_LW300_ppointS);
  hists.push_back(SG_LW400_ppointS);
  hists.push_back(SG_LW500_ppointS);
  hists.push_back(SG_dataRunB_ppoint);
  hists.push_back(SG_dataRunC_ppoint );
  hists.push_back(SG_ZLL_ppoint);
  hists.push_back(SG_TT_ppoint);
  hists.push_back(SG_W3J_ppoint);
  hists.push_back(SG_W2J_ppoint);
  hists.push_back(SG_W1J_ppoint);
  //hists.push_back(//SG_TTZ_ppoint);
  //hists.push_back(//SG_WW_ppoint);
  //hists.push_back(//SG_WZ_ppoint);
  hists.push_back(SG_LW200_ppoint);
  hists.push_back(SG_LW300_ppoint);
  hists.push_back(SG_LW400_ppoint);
  hists.push_back(SG_LW500_ppoint);
  hists.push_back(SG_dataRunB_npv);
  hists.push_back(SG_dataRunC_npv );
  hists.push_back(SG_ZLL_npv);
  hists.push_back(SG_TT_npv);
  hists.push_back(SG_W3J_npv);
  hists.push_back(SG_W2J_npv);
  hists.push_back(SG_W1J_npv);
  //hists.push_back(//SG_TTZ_npv);
  //hists.push_back(//SG_WW_npv);
  //hists.push_back(//SG_WZ_npv);
  hists.push_back(SG_LW200_npv);
  hists.push_back(SG_LW300_npv);
  hists.push_back(SG_LW400_npv);
  hists.push_back(SG_LW500_npv);
  hists.push_back(SG_dataRunB_nsv);
  hists.push_back(SG_dataRunC_nsv );
  hists.push_back(SG_ZLL_nsv);
  hists.push_back(SG_TT_nsv);
  hists.push_back(SG_W3J_nsv);
  hists.push_back(SG_W2J_nsv);
  hists.push_back(SG_W1J_nsv);
  //hists.push_back(//SG_TTZ_nsv);
  //hists.push_back(//SG_WW_nsv);
  //hists.push_back(//SG_WZ_nsv);
  hists.push_back(SG_LW200_nsv);
  hists.push_back(SG_LW300_nsv);
  hists.push_back(SG_LW400_nsv);
  hists.push_back(SG_LW500_nsv);
  hists.push_back(SG_dataRunB_svd);
  hists.push_back(SG_dataRunC_svd );
  hists.push_back(SG_ZLL_svd);
  hists.push_back(SG_TT_svd);
  hists.push_back(SG_W3J_svd);
  hists.push_back(SG_W2J_svd);
  hists.push_back(SG_W1J_svd);
  //hists.push_back(//SG_TTZ_svd);
  //hists.push_back(//SG_WW_svd);
  //hists.push_back(//SG_WZ_svd);
  hists.push_back(SG_LW200_svd);
  hists.push_back(SG_LW300_svd);
  hists.push_back(SG_LW400_svd);
  hists.push_back(SG_LW500_svd);
  hists.push_back(SG_dataRunB_BSd);
  hists.push_back(SG_dataRunC_BSd );
  hists.push_back(SG_ZLL_BSd);
  hists.push_back(SG_TT_BSd);
  hists.push_back(SG_W3J_BSd);
  hists.push_back(SG_W2J_BSd);
  hists.push_back(SG_W1J_BSd);
  //hists.push_back(SG_TTZ_BSd);
  //hists.push_back(SG_WW_BSd);
  //hists.push_back(SG_WZ_BSd);
  hists.push_back(SG_LW200_BSd);
  hists.push_back(SG_LW300_BSd);
  hists.push_back(SG_LW400_BSd);
  hists.push_back(SG_LW500_BSd);
  hists.push_back(SG_dataRunB_BSdChi2norm);
  hists.push_back(SG_dataRunC_BSdChi2norm );
  hists.push_back(SG_ZLL_BSdChi2norm);
  hists.push_back(SG_TT_BSdChi2norm);
  hists.push_back(SG_W3J_BSdChi2norm);
  hists.push_back(SG_W2J_BSdChi2norm);
  hists.push_back(SG_W1J_BSdChi2norm);
  //hists.push_back(SG_TTZ_BSdChi2norm);
  //hists.push_back(SG_WW_BSdChi2norm);
  //hists.push_back(SG_WZ_BSdChi2norm);
  hists.push_back(SG_LW200_BSdChi2norm);
  hists.push_back(SG_LW300_BSdChi2norm);
  hists.push_back(SG_LW400_BSdChi2norm);
  hists.push_back(SG_LW500_BSdChi2norm);
  //Histograms for signal region IPP
  hists.push_back(IPP_dataRunB_ppointS);
  hists.push_back(IPP_dataRunC_ppointS );
  hists.push_back(IPP_ZLL_ppointS);
  hists.push_back(IPP_TT_ppointS);
  hists.push_back(IPP_W3J_ppointS);
  hists.push_back(IPP_W2J_ppointS);
  hists.push_back(IPP_W1J_ppointS);
  //hists.push_back(//IPP_TTZ_ppointS);
  //hists.push_back(//IPP_WW_ppointS);
  //hists.push_back(//IPP_WZ_ppointS);
  hists.push_back(IPP_LW200_ppointS);
  hists.push_back(IPP_LW300_ppointS);
  hists.push_back(IPP_LW400_ppointS);
  hists.push_back(IPP_LW500_ppointS);
  hists.push_back(IPP_dataRunB_ppoint);
  hists.push_back(IPP_dataRunC_ppoint );
  hists.push_back(IPP_ZLL_ppoint);
  hists.push_back(IPP_TT_ppoint);
  hists.push_back(IPP_W3J_ppoint);
  hists.push_back(IPP_W2J_ppoint);
  hists.push_back(IPP_W1J_ppoint);
  //hists.push_back(//IPP_TTZ_ppoint);
  //hists.push_back(//IPP_WW_ppoint);
  //hists.push_back(//IPP_WZ_ppoint);
  hists.push_back(IPP_LW200_ppoint);
  hists.push_back(IPP_LW300_ppoint);
  hists.push_back(IPP_LW400_ppoint);
  hists.push_back(IPP_LW500_ppoint);
  hists.push_back(IPP_dataRunB_npv);
  hists.push_back(IPP_dataRunC_npv );
  hists.push_back(IPP_ZLL_npv);
  hists.push_back(IPP_TT_npv);
  hists.push_back(IPP_W3J_npv);
  hists.push_back(IPP_W2J_npv);
  hists.push_back(IPP_W1J_npv);
  //hists.push_back(//IPP_TTZ_npv);
  //hists.push_back(//IPP_WW_npv);
  //hists.push_back(//IPP_WZ_npv);
  hists.push_back(IPP_LW200_npv);
  hists.push_back(IPP_LW300_npv);
  hists.push_back(IPP_LW400_npv);
  hists.push_back(IPP_LW500_npv);
  hists.push_back(IPP_dataRunB_nsv);
  hists.push_back(IPP_dataRunC_nsv );
  hists.push_back(IPP_ZLL_nsv);
  hists.push_back(IPP_TT_nsv);
  hists.push_back(IPP_W3J_nsv);
  hists.push_back(IPP_W2J_nsv);
  hists.push_back(IPP_W1J_nsv);
  //hists.push_back(//IPP_TTZ_nsv);
  //hists.push_back(//IPP_WW_nsv);
  //hists.push_back(//IPP_WZ_nsv);
  hists.push_back(IPP_LW200_nsv);
  hists.push_back(IPP_LW300_nsv);
  hists.push_back(IPP_LW400_nsv);
  hists.push_back(IPP_LW500_nsv);
  hists.push_back(IPP_dataRunB_svd);
  hists.push_back(IPP_dataRunC_svd );
  hists.push_back(IPP_ZLL_svd);
  hists.push_back(IPP_TT_svd);
  hists.push_back(IPP_W3J_svd);
  hists.push_back(IPP_W2J_svd);
  hists.push_back(IPP_W1J_svd);
  //hists.push_back(//IPP_TTZ_svd);
  //hists.push_back(//IPP_WW_svd);
  //hists.push_back(//IPP_WZ_svd);
  hists.push_back(IPP_LW200_svd);
  hists.push_back(IPP_LW300_svd);
  hists.push_back(IPP_LW400_svd);
  hists.push_back(IPP_LW500_svd);
  hists.push_back(IPP_dataRunB_BSd);
  hists.push_back(IPP_dataRunC_BSd );
  hists.push_back(IPP_ZLL_BSd);
  hists.push_back(IPP_TT_BSd);
  hists.push_back(IPP_W3J_BSd);
  hists.push_back(IPP_W2J_BSd);
  hists.push_back(IPP_W1J_BSd);
  //hists.push_back(IPP_TTZ_BSd);
  //hists.push_back(IPP_WW_BSd);
  //hists.push_back(IPP_WZ_BSd);
  hists.push_back(IPP_LW200_BSd);
  hists.push_back(IPP_LW300_BSd);
  hists.push_back(IPP_LW400_BSd);
  hists.push_back(IPP_LW500_BSd);
  hists.push_back(IPP_dataRunB_BSdChi2norm);
  hists.push_back(IPP_dataRunC_BSdChi2norm );
  hists.push_back(IPP_ZLL_BSdChi2norm);
  hists.push_back(IPP_TT_BSdChi2norm);
  hists.push_back(IPP_W3J_BSdChi2norm);
  hists.push_back(IPP_W2J_BSdChi2norm);
  hists.push_back(IPP_W1J_BSdChi2norm);
  //hists.push_back(IPP_TTZ_BSdChi2norm);
  //hists.push_back(IPP_WW_BSdChi2norm);
  //hists.push_back(IPP_WZ_BSdChi2norm);
  hists.push_back(IPP_LW200_BSdChi2norm);
  hists.push_back(IPP_LW300_BSdChi2norm);
  hists.push_back(IPP_LW400_BSdChi2norm);
  hists.push_back(IPP_LW500_BSdChi2norm);
  //////////////////Histograms ofr control region
  //Histograms for signal region TF
  hists.push_back(TF_dataRunB_ppointS_cr);
  hists.push_back(TF_dataRunC_ppointS_cr);
  hists.push_back(TF_ZLL_ppointS_cr);
  hists.push_back(TF_TT_ppointS_cr);
  hists.push_back(TF_W3J_ppointS_cr);
  hists.push_back(TF_W2J_ppointS_cr);
  hists.push_back(TF_W1J_ppointS_cr);
  //hists.push_back(//TF_TTZ_ppointS_cr);
  //hists.push_back(//TF_WW_ppointS_cr);
  //hists.push_back(//TF_WZ_ppointS_cr);
  hists.push_back(TF_LW200_ppointS_cr);
  hists.push_back(TF_LW300_ppointS_cr);
  hists.push_back(TF_LW400_ppointS_cr);
  hists.push_back(TF_LW500_ppointS_cr);
  hists.push_back(TF_dataRunB_ppoint_cr);
  hists.push_back(TF_dataRunC_ppoint_cr);
  hists.push_back(TF_ZLL_ppoint_cr);
  hists.push_back(TF_TT_ppoint_cr);
  hists.push_back(TF_W3J_ppoint_cr);
  hists.push_back(TF_W2J_ppoint_cr);
  hists.push_back(TF_W1J_ppoint_cr);
  //hists.push_back(//TF_TTZ_ppoint_cr);
  //hists.push_back(//TF_WW_ppoint_cr);
  //hists.push_back(//TF_WZ_ppoint_cr);
  hists.push_back(TF_LW200_ppoint_cr);
  hists.push_back(TF_LW300_ppoint_cr);
  hists.push_back(TF_LW400_ppoint_cr);
  hists.push_back(TF_LW500_ppoint_cr);
  hists.push_back(TF_dataRunB_npv_cr);
  hists.push_back(TF_dataRunC_npv_cr);
  hists.push_back(TF_ZLL_npv_cr);
  hists.push_back(TF_TT_npv_cr);
  hists.push_back(TF_W3J_npv_cr);
  hists.push_back(TF_W2J_npv_cr);
  hists.push_back(TF_W1J_npv_cr);
  //hists.push_back(//TF_TTZ_npv_cr);
  //hists.push_back(//TF_WW_npv_cr);
  //hists.push_back(//TF_WZ_npv_cr);
  hists.push_back(TF_LW200_npv_cr);
  hists.push_back(TF_LW300_npv_cr);
  hists.push_back(TF_LW400_npv_cr);
  hists.push_back(TF_LW500_npv_cr);
  hists.push_back(TF_dataRunB_nsv_cr);
  hists.push_back(TF_dataRunC_nsv_cr);
  hists.push_back(TF_ZLL_nsv_cr);
  hists.push_back(TF_TT_nsv_cr);
  hists.push_back(TF_W3J_nsv_cr);
  hists.push_back(TF_W2J_nsv_cr);
  hists.push_back(TF_W1J_nsv_cr);
  //hists.push_back(//TF_TTZ_nsv_cr);
  //hists.push_back(//TF_WW_nsv_cr);
  //hists.push_back(//TF_WZ_nsv_cr);
  hists.push_back(TF_LW200_nsv_cr);
  hists.push_back(TF_LW300_nsv_cr);
  hists.push_back(TF_LW400_nsv_cr);
  hists.push_back(TF_LW500_nsv_cr);
  hists.push_back(TF_dataRunB_svd_cr);
  hists.push_back(TF_dataRunC_svd_cr);
  hists.push_back(TF_ZLL_svd_cr);
  hists.push_back(TF_TT_svd_cr);
  hists.push_back(TF_W3J_svd_cr);
  hists.push_back(TF_W2J_svd_cr);
  hists.push_back(TF_W1J_svd_cr);
  //hists.push_back(//TF_TTZ_svd_cr);
  //hists.push_back(//TF_WW_svd_cr);
  //hists.push_back(//TF_WZ_svd_cr);
  hists.push_back(TF_LW200_svd_cr);
  hists.push_back(TF_LW300_svd_cr);
  hists.push_back(TF_LW400_svd_cr);
  hists.push_back(TF_LW500_svd_cr);
  hists.push_back(TF_dataRunB_BSd_cr);
  hists.push_back(TF_dataRunC_BSd_cr);
  hists.push_back(TF_ZLL_BSd_cr);
  hists.push_back(TF_TT_BSd_cr);
  hists.push_back(TF_W3J_BSd_cr);
  hists.push_back(TF_W2J_BSd_cr);
  hists.push_back(TF_W1J_BSd_cr);
  //hists.push_back(TF_TTZ_BSd_cr);
  //hists.push_back(TF_WW_BSd_cr);
  //hists.push_back(TF_WZ_BSd_cr);
  hists.push_back(TF_LW200_BSd_cr);
  hists.push_back(TF_LW300_BSd_cr);
  hists.push_back(TF_LW400_BSd_cr);
  hists.push_back(TF_LW500_BSd_cr);
  hists.push_back(TF_dataRunB_BSdChi2norm_cr);
  hists.push_back(TF_dataRunC_BSdChi2norm_cr);
  hists.push_back(TF_ZLL_BSdChi2norm_cr);
  hists.push_back(TF_TT_BSdChi2norm_cr);
  hists.push_back(TF_W3J_BSdChi2norm_cr);
  hists.push_back(TF_W2J_BSdChi2norm_cr);
  hists.push_back(TF_W1J_BSdChi2norm_cr);
  //hists.push_back(TF_TTZ_BSdChi2norm_cr);
  //hists.push_back(TF_WW_BSdChi2norm_cr);
  //hists.push_back(TF_WZ_BSdChi2norm_cr);
  hists.push_back(TF_LW200_BSdChi2norm_cr);
  hists.push_back(TF_LW300_BSdChi2norm_cr);
  hists.push_back(TF_LW400_BSdChi2norm_cr);
  hists.push_back(TF_LW500_BSdChi2norm_cr);
  //Histograms for signal region TO
  hists.push_back(TO_dataRunB_ppointS_cr);
  hists.push_back(TO_dataRunC_ppointS_cr);
  hists.push_back(TO_ZLL_ppointS_cr);
  hists.push_back(TO_TT_ppointS_cr);
  hists.push_back(TO_W3J_ppointS_cr);
  hists.push_back(TO_W2J_ppointS_cr);
  hists.push_back(TO_W1J_ppointS_cr);
  //hists.push_back(//TO_TTZ_ppointS_cr);
  //hists.push_back(//TO_WW_ppointS_cr);
  //hists.push_back(//TO_WZ_ppointS_cr);
  hists.push_back(TO_LW200_ppointS_cr);
  hists.push_back(TO_LW300_ppointS_cr);
  hists.push_back(TO_LW400_ppointS_cr);
  hists.push_back(TO_LW500_ppointS_cr);
  hists.push_back(TO_dataRunB_ppoint_cr);
  hists.push_back(TO_dataRunC_ppoint_cr);
  hists.push_back(TO_ZLL_ppoint_cr);
  hists.push_back(TO_TT_ppoint_cr);
  hists.push_back(TO_W3J_ppoint_cr);
  hists.push_back(TO_W2J_ppoint_cr);
  hists.push_back(TO_W1J_ppoint_cr);
  //hists.push_back(//TO_TTZ_ppoint_cr);
  //hists.push_back(//TO_WW_ppoint_cr);
  //hists.push_back(//TO_WZ_ppoint_cr);
  hists.push_back(TO_LW200_ppoint_cr);
  hists.push_back(TO_LW300_ppoint_cr);
  hists.push_back(TO_LW400_ppoint_cr);
  hists.push_back(TO_LW500_ppoint_cr);
  hists.push_back(TO_dataRunB_npv_cr);
  hists.push_back(TO_dataRunC_npv_cr);
  hists.push_back(TO_ZLL_npv_cr);
  hists.push_back(TO_TT_npv_cr);
  hists.push_back(TO_W3J_npv_cr);
  hists.push_back(TO_W2J_npv_cr);
  hists.push_back(TO_W1J_npv_cr);
  //hists.push_back(//TO_TTZ_npv_cr);
  //hists.push_back(//TO_WW_npv_cr);
  //hists.push_back(//TO_WZ_npv_cr);
  hists.push_back(TO_LW200_npv_cr);
  hists.push_back(TO_LW300_npv_cr);
  hists.push_back(TO_LW400_npv_cr);
  hists.push_back(TO_LW500_npv_cr);
  hists.push_back(TO_dataRunB_nsv_cr);
  hists.push_back(TO_dataRunC_nsv_cr);
  hists.push_back(TO_ZLL_nsv_cr);
  hists.push_back(TO_TT_nsv_cr);
  hists.push_back(TO_W3J_nsv_cr);
  hists.push_back(TO_W2J_nsv_cr);
  hists.push_back(TO_W1J_nsv_cr);
  //hists.push_back(//TO_TTZ_nsv_cr);
  //hists.push_back(//TO_WW_nsv_cr);
  //hists.push_back(//TO_WZ_nsv_cr);
  hists.push_back(TO_LW200_nsv_cr);
  hists.push_back(TO_LW300_nsv_cr);
  hists.push_back(TO_LW400_nsv_cr);
  hists.push_back(TO_LW500_nsv_cr);
  hists.push_back(TO_dataRunB_svd_cr);
  hists.push_back(TO_dataRunC_svd_cr);
  hists.push_back(TO_ZLL_svd_cr);
  hists.push_back(TO_TT_svd_cr);
  hists.push_back(TO_W3J_svd_cr);
  hists.push_back(TO_W2J_svd_cr);
  hists.push_back(TO_W1J_svd_cr);
  //hists.push_back(//TO_TTZ_svd_cr);
  //hists.push_back(//TO_WW_svd_cr);
  //hists.push_back(//TO_WZ_svd_cr);
  hists.push_back(TO_LW200_svd_cr);
  hists.push_back(TO_LW300_svd_cr);
  hists.push_back(TO_LW400_svd_cr);
  hists.push_back(TO_LW500_svd_cr);
  hists.push_back(TO_dataRunB_BSd_cr);
  hists.push_back(TO_dataRunC_BSd_cr);
  hists.push_back(TO_ZLL_BSd_cr);
  hists.push_back(TO_TT_BSd_cr);
  hists.push_back(TO_W3J_BSd_cr);
  hists.push_back(TO_W2J_BSd_cr);
  hists.push_back(TO_W1J_BSd_cr);
  //hists.push_back(TO_TTZ_BSd_cr);
  //hists.push_back(TO_WW_BSd_cr);
  //hists.push_back(TO_WZ_BSd_cr);
  hists.push_back(TO_LW200_BSd_cr);
  hists.push_back(TO_LW300_BSd_cr);
  hists.push_back(TO_LW400_BSd_cr);
  hists.push_back(TO_LW500_BSd_cr);
  hists.push_back(TO_dataRunB_BSdChi2norm_cr);
  hists.push_back(TO_dataRunC_BSdChi2norm_cr);
  hists.push_back(TO_ZLL_BSdChi2norm_cr);
  hists.push_back(TO_TT_BSdChi2norm_cr);
  hists.push_back(TO_W3J_BSdChi2norm_cr);
  hists.push_back(TO_W2J_BSdChi2norm_cr);
  hists.push_back(TO_W1J_BSdChi2norm_cr);
  //hists.push_back(TO_TTZ_BSdChi2norm_cr);
  //hists.push_back(TO_WW_BSdChi2norm_cr);
  //hists.push_back(TO_WZ_BSdChi2norm_cr);
  hists.push_back(TO_LW200_BSdChi2norm_cr);
  hists.push_back(TO_LW300_BSdChi2norm_cr);
  hists.push_back(TO_LW400_BSdChi2norm_cr);
  hists.push_back(TO_LW500_BSdChi2norm_cr);
  //Histograms for signal region HQ
  hists.push_back(HQ_dataRunB_ppointS_cr);
  hists.push_back(HQ_dataRunC_ppointS_cr);
  hists.push_back(HQ_ZLL_ppointS_cr);
  hists.push_back(HQ_TT_ppointS_cr);
  hists.push_back(HQ_W3J_ppointS_cr);
  hists.push_back(HQ_W2J_ppointS_cr);
  hists.push_back(HQ_W1J_ppointS_cr);
  //hists.push_back(//HQ_TTZ_ppointS_cr);
  //hists.push_back(//HQ_WW_ppointS_cr);
  //hists.push_back(//HQ_WZ_ppointS_cr);
  hists.push_back(HQ_LW200_ppointS_cr);
  hists.push_back(HQ_LW300_ppointS_cr);
  hists.push_back(HQ_LW400_ppointS_cr);
  hists.push_back(HQ_LW500_ppointS_cr);
  hists.push_back(HQ_dataRunB_ppoint_cr);
  hists.push_back(HQ_dataRunC_ppoint_cr);
  hists.push_back(HQ_ZLL_ppoint_cr);
  hists.push_back(HQ_TT_ppoint_cr);
  hists.push_back(HQ_W3J_ppoint_cr);
  hists.push_back(HQ_W2J_ppoint_cr);
  hists.push_back(HQ_W1J_ppoint_cr);
  //hists.push_back(//HQ_TTZ_ppoint_cr);
  //hists.push_back(//HQ_WW_ppoint_cr);
  //hists.push_back(//HQ_WZ_ppoint_cr);
  hists.push_back(HQ_LW200_ppoint_cr);
  hists.push_back(HQ_LW300_ppoint_cr);
  hists.push_back(HQ_LW400_ppoint_cr);
  hists.push_back(HQ_LW500_ppoint_cr);
  hists.push_back(HQ_dataRunB_npv_cr);
  hists.push_back(HQ_dataRunC_npv_cr);
  hists.push_back(HQ_ZLL_npv_cr);
  hists.push_back(HQ_TT_npv_cr);
  hists.push_back(HQ_W3J_npv_cr);
  hists.push_back(HQ_W2J_npv_cr);
  hists.push_back(HQ_W1J_npv_cr);
  //hists.push_back(//HQ_TTZ_npv_cr);
  //hists.push_back(//HQ_WW_npv_cr);
  //hists.push_back(//HQ_WZ_npv_cr);
  hists.push_back(HQ_LW200_npv_cr);
  hists.push_back(HQ_LW300_npv_cr);
  hists.push_back(HQ_LW400_npv_cr);
  hists.push_back(HQ_LW500_npv_cr);
  hists.push_back(HQ_dataRunB_nsv_cr);
  hists.push_back(HQ_dataRunC_nsv_cr);
  hists.push_back(HQ_ZLL_nsv_cr);
  hists.push_back(HQ_TT_nsv_cr);
  hists.push_back(HQ_W3J_nsv_cr);
  hists.push_back(HQ_W2J_nsv_cr);
  hists.push_back(HQ_W1J_nsv_cr);
  //hists.push_back(//HQ_TTZ_nsv_cr);
  //hists.push_back(//HQ_WW_nsv_cr);
  //hists.push_back(//HQ_WZ_nsv_cr);
  hists.push_back(HQ_LW200_nsv_cr);
  hists.push_back(HQ_LW300_nsv_cr);
  hists.push_back(HQ_LW400_nsv_cr);
  hists.push_back(HQ_LW500_nsv_cr);
  hists.push_back(HQ_dataRunB_svd_cr);
  hists.push_back(HQ_dataRunC_svd_cr);
  hists.push_back(HQ_ZLL_svd_cr);
  hists.push_back(HQ_TT_svd_cr);
  hists.push_back(HQ_W3J_svd_cr);
  hists.push_back(HQ_W2J_svd_cr);
  hists.push_back(HQ_W1J_svd_cr);
  //hists.push_back(//HQ_TTZ_svd_cr);
  //hists.push_back(//HQ_WW_svd_cr);
  //hists.push_back(//HQ_WZ_svd_cr);
  hists.push_back(HQ_LW200_svd_cr);
  hists.push_back(HQ_LW300_svd_cr);
  hists.push_back(HQ_LW400_svd_cr);
  hists.push_back(HQ_LW500_svd_cr);
  hists.push_back(HQ_dataRunB_BSd_cr);
  hists.push_back(HQ_dataRunC_BSd_cr);
  hists.push_back(HQ_ZLL_BSd_cr);
  hists.push_back(HQ_TT_BSd_cr);
  hists.push_back(HQ_W3J_BSd_cr);
  hists.push_back(HQ_W2J_BSd_cr);
  hists.push_back(HQ_W1J_BSd_cr);
  //hists.push_back(HQ_TTZ_BSd_cr);
  //hists.push_back(HQ_WW_BSd_cr);
  //hists.push_back(HQ_WZ_BSd_cr);
  hists.push_back(HQ_LW200_BSd_cr);
  hists.push_back(HQ_LW300_BSd_cr);
  hists.push_back(HQ_LW400_BSd_cr);
  hists.push_back(HQ_LW500_BSd_cr);
  hists.push_back(HQ_dataRunB_BSdChi2norm_cr);
  hists.push_back(HQ_dataRunC_BSdChi2norm_cr);
  hists.push_back(HQ_ZLL_BSdChi2norm_cr);
  hists.push_back(HQ_TT_BSdChi2norm_cr);
  hists.push_back(HQ_W3J_BSdChi2norm_cr);
  hists.push_back(HQ_W2J_BSdChi2norm_cr);
  hists.push_back(HQ_W1J_BSdChi2norm_cr);
  //hists.push_back(HQ_TTZ_BSdChi2norm_cr);
  //hists.push_back(HQ_WW_BSdChi2norm_cr);
  //hists.push_back(HQ_WZ_BSdChi2norm_cr);
  hists.push_back(HQ_LW200_BSdChi2norm_cr);
  hists.push_back(HQ_LW300_BSdChi2norm_cr);
  hists.push_back(HQ_LW400_BSdChi2norm_cr);
  hists.push_back(HQ_LW500_BSdChi2norm_cr);
  //Histograms for signal region JetS
  hists.push_back(JetS_dataRunB_ppointS_cr);
  hists.push_back(JetS_dataRunC_ppointS_cr);
  hists.push_back(JetS_ZLL_ppointS_cr);
  hists.push_back(JetS_TT_ppointS_cr);
  hists.push_back(JetS_W3J_ppointS_cr);
  hists.push_back(JetS_W2J_ppointS_cr);
  hists.push_back(JetS_W1J_ppointS_cr);
  //hists.push_back(//JetS_TTZ_ppointS_cr);
  //hists.push_back(//JetS_WW_ppointS_cr);
  //hists.push_back(//JetS_WZ_ppointS_cr);
  hists.push_back(JetS_LW200_ppointS_cr);
  hists.push_back(JetS_LW300_ppointS_cr);
  hists.push_back(JetS_LW400_ppointS_cr);
  hists.push_back(JetS_LW500_ppointS_cr);
  hists.push_back(JetS_dataRunB_ppoint_cr);
  hists.push_back(JetS_dataRunC_ppoint_cr);
  hists.push_back(JetS_ZLL_ppoint_cr);
  hists.push_back(JetS_TT_ppoint_cr);
  hists.push_back(JetS_W3J_ppoint_cr);
  hists.push_back(JetS_W2J_ppoint_cr);
  hists.push_back(JetS_W1J_ppoint_cr);
  //hists.push_back(//JetS_TTZ_ppoint_cr);
  //hists.push_back(//JetS_WW_ppoint_cr);
  //hists.push_back(//JetS_WZ_ppoint_cr);
  hists.push_back(JetS_LW200_ppoint_cr);
  hists.push_back(JetS_LW300_ppoint_cr);
  hists.push_back(JetS_LW400_ppoint_cr);
  hists.push_back(JetS_LW500_ppoint_cr);
  hists.push_back(JetS_dataRunB_npv_cr);
  hists.push_back(JetS_dataRunC_npv_cr);
  hists.push_back(JetS_ZLL_npv_cr);
  hists.push_back(JetS_TT_npv_cr);
  hists.push_back(JetS_W3J_npv_cr);
  hists.push_back(JetS_W2J_npv_cr);
  hists.push_back(JetS_W1J_npv_cr);
  //hists.push_back(//JetS_TTZ_npv_cr);
  //hists.push_back(//JetS_WW_npv_cr);
  //hists.push_back(//JetS_WZ_npv_cr);
  hists.push_back(JetS_LW200_npv_cr);
  hists.push_back(JetS_LW300_npv_cr);
  hists.push_back(JetS_LW400_npv_cr);
  hists.push_back(JetS_LW500_npv_cr);
  hists.push_back(JetS_dataRunB_nsv_cr);
  hists.push_back(JetS_dataRunC_nsv_cr);
  hists.push_back(JetS_ZLL_nsv_cr);
  hists.push_back(JetS_TT_nsv_cr);
  hists.push_back(JetS_W3J_nsv_cr);
  hists.push_back(JetS_W2J_nsv_cr);
  hists.push_back(JetS_W1J_nsv_cr);
  //hists.push_back(//JetS_TTZ_nsv_cr);
  //hists.push_back(//JetS_WW_nsv_cr);
  //hists.push_back(//JetS_WZ_nsv_cr);
  hists.push_back(JetS_LW200_nsv_cr);
  hists.push_back(JetS_LW300_nsv_cr);
  hists.push_back(JetS_LW400_nsv_cr);
  hists.push_back(JetS_LW500_nsv_cr);
  hists.push_back(JetS_dataRunB_svd_cr);
  hists.push_back(JetS_dataRunC_svd_cr);
  hists.push_back(JetS_ZLL_svd_cr);
  hists.push_back(JetS_TT_svd_cr);
  hists.push_back(JetS_W3J_svd_cr);
  hists.push_back(JetS_W2J_svd_cr);
  hists.push_back(JetS_W1J_svd_cr);
  //hists.push_back(//JetS_TTZ_svd_cr);
  //hists.push_back(//JetS_WW_svd_cr);
  //hists.push_back(//JetS_WZ_svd_cr);
  hists.push_back(JetS_LW200_svd_cr);
  hists.push_back(JetS_LW300_svd_cr);
  hists.push_back(JetS_LW400_svd_cr);
  hists.push_back(JetS_LW500_svd_cr);
  hists.push_back(JetS_dataRunB_BSd_cr);
  hists.push_back(JetS_dataRunC_BSd_cr);
  hists.push_back(JetS_ZLL_BSd_cr);
  hists.push_back(JetS_TT_BSd_cr);
  hists.push_back(JetS_W3J_BSd_cr);
  hists.push_back(JetS_W2J_BSd_cr);
  hists.push_back(JetS_W1J_BSd_cr);
  //hists.push_back(JetS_TTZ_BSd_cr);
  //hists.push_back(JetS_WW_BSd_cr);
  //hists.push_back(JetS_WZ_BSd_cr);
  hists.push_back(JetS_LW200_BSd_cr);
  hists.push_back(JetS_LW300_BSd_cr);
  hists.push_back(JetS_LW400_BSd_cr);
  hists.push_back(JetS_LW500_BSd_cr);
  hists.push_back(JetS_dataRunB_BSdChi2norm_cr);
  hists.push_back(JetS_dataRunC_BSdChi2norm_cr);
  hists.push_back(JetS_ZLL_BSdChi2norm_cr);
  hists.push_back(JetS_TT_BSdChi2norm_cr);
  hists.push_back(JetS_W3J_BSdChi2norm_cr);
  hists.push_back(JetS_W2J_BSdChi2norm_cr);
  hists.push_back(JetS_W1J_BSdChi2norm_cr);
  //hists.push_back(JetS_TTZ_BSdChi2norm_cr);
  //hists.push_back(JetS_WW_BSdChi2norm_cr);
  //hists.push_back(JetS_WZ_BSdChi2norm_cr);
  hists.push_back(JetS_LW200_BSdChi2norm_cr);
  hists.push_back(JetS_LW300_BSdChi2norm_cr);
  hists.push_back(JetS_LW400_BSdChi2norm_cr);
  hists.push_back(JetS_LW500_BSdChi2norm_cr);
  //Histograms for signal region DRC
  hists.push_back(DRC_dataRunB_ppointS_cr);
  hists.push_back(DRC_dataRunC_ppointS_cr);
  hists.push_back(DRC_ZLL_ppointS_cr);
  hists.push_back(DRC_TT_ppointS_cr);
  hists.push_back(DRC_W3J_ppointS_cr);
  hists.push_back(DRC_W2J_ppointS_cr);
  hists.push_back(DRC_W1J_ppointS_cr);
  //hists.push_back(//DRC_TTZ_ppointS_cr);
  //hists.push_back(//DRC_WW_ppointS_cr);
  //hists.push_back(//DRC_WZ_ppointS_cr);
  hists.push_back(DRC_LW200_ppointS_cr);
  hists.push_back(DRC_LW300_ppointS_cr);
  hists.push_back(DRC_LW400_ppointS_cr);
  hists.push_back(DRC_LW500_ppointS_cr);
  hists.push_back(DRC_dataRunB_ppoint_cr);
  hists.push_back(DRC_dataRunC_ppoint_cr);
  hists.push_back(DRC_ZLL_ppoint_cr);
  hists.push_back(DRC_TT_ppoint_cr);
  hists.push_back(DRC_W3J_ppoint_cr);
  hists.push_back(DRC_W2J_ppoint_cr);
  hists.push_back(DRC_W1J_ppoint_cr);
  //hists.push_back(//DRC_TTZ_ppoint_cr);
  //hists.push_back(//DRC_WW_ppoint_cr);
  //hists.push_back(//DRC_WZ_ppoint_cr);
  hists.push_back(DRC_LW200_ppoint_cr);
  hists.push_back(DRC_LW300_ppoint_cr);
  hists.push_back(DRC_LW400_ppoint_cr);
  hists.push_back(DRC_LW500_ppoint_cr);
  hists.push_back(DRC_dataRunB_npv_cr);
  hists.push_back(DRC_dataRunC_npv_cr);
  hists.push_back(DRC_ZLL_npv_cr);
  hists.push_back(DRC_TT_npv_cr);
  hists.push_back(DRC_W3J_npv_cr);
  hists.push_back(DRC_W2J_npv_cr);
  hists.push_back(DRC_W1J_npv_cr);
  //hists.push_back(//DRC_TTZ_npv_cr);
  //hists.push_back(//DRC_WW_npv_cr);
  //hists.push_back(//DRC_WZ_npv_cr);
  hists.push_back(DRC_LW200_npv_cr);
  hists.push_back(DRC_LW300_npv_cr);
  hists.push_back(DRC_LW400_npv_cr);
  hists.push_back(DRC_LW500_npv_cr);
  hists.push_back(DRC_dataRunB_nsv_cr);
  hists.push_back(DRC_dataRunC_nsv_cr);
  hists.push_back(DRC_ZLL_nsv_cr);
  hists.push_back(DRC_TT_nsv_cr);
  hists.push_back(DRC_W3J_nsv_cr);
  hists.push_back(DRC_W2J_nsv_cr);
  hists.push_back(DRC_W1J_nsv_cr);
  //hists.push_back(//DRC_TTZ_nsv_cr);
  //hists.push_back(//DRC_WW_nsv_cr);
  //hists.push_back(//DRC_WZ_nsv_cr);
  hists.push_back(DRC_LW200_nsv_cr);
  hists.push_back(DRC_LW300_nsv_cr);
  hists.push_back(DRC_LW400_nsv_cr);
  hists.push_back(DRC_LW500_nsv_cr);
  hists.push_back(DRC_dataRunB_svd_cr);
  hists.push_back(DRC_dataRunC_svd_cr);
  hists.push_back(DRC_ZLL_svd_cr);
  hists.push_back(DRC_TT_svd_cr);
  hists.push_back(DRC_W3J_svd_cr);
  hists.push_back(DRC_W2J_svd_cr);
  hists.push_back(DRC_W1J_svd_cr);
  //hists.push_back(//DRC_TTZ_svd_cr);
  //hists.push_back(//DRC_WW_svd_cr);
  //hists.push_back(//DRC_WZ_svd_cr);
  hists.push_back(DRC_LW200_svd_cr);
  hists.push_back(DRC_LW300_svd_cr);
  hists.push_back(DRC_LW400_svd_cr);
  hists.push_back(DRC_LW500_svd_cr);
  hists.push_back(DRC_dataRunB_BSd_cr);
  hists.push_back(DRC_dataRunC_BSd_cr);
  hists.push_back(DRC_ZLL_BSd_cr);
  hists.push_back(DRC_TT_BSd_cr);
  hists.push_back(DRC_W3J_BSd_cr);
  hists.push_back(DRC_W2J_BSd_cr);
  hists.push_back(DRC_W1J_BSd_cr);
  //hists.push_back(DRC_TTZ_BSd_cr);
  //hists.push_back(DRC_WW_BSd_cr);
  //hists.push_back(DRC_WZ_BSd_cr);
  hists.push_back(DRC_LW200_BSd_cr);
  hists.push_back(DRC_LW300_BSd_cr);
  hists.push_back(DRC_LW400_BSd_cr);
  hists.push_back(DRC_LW500_BSd_cr);
  hists.push_back(DRC_dataRunB_BSdChi2norm_cr);
  hists.push_back(DRC_dataRunC_BSdChi2norm_cr);
  hists.push_back(DRC_ZLL_BSdChi2norm_cr);
  hists.push_back(DRC_TT_BSdChi2norm_cr);
  hists.push_back(DRC_W3J_BSdChi2norm_cr);
  hists.push_back(DRC_W2J_BSdChi2norm_cr);
  hists.push_back(DRC_W1J_BSdChi2norm_cr);
  //hists.push_back(DRC_TTZ_BSdChi2norm_cr);
  //hists.push_back(DRC_WW_BSdChi2norm_cr);
  //hists.push_back(DRC_WZ_BSdChi2norm_cr);
  hists.push_back(DRC_LW200_BSdChi2norm_cr);
  hists.push_back(DRC_LW300_BSdChi2norm_cr);
  hists.push_back(DRC_LW400_BSdChi2norm_cr);
  hists.push_back(DRC_LW500_BSdChi2norm_cr);
  //Histograms for signal region SG
  hists.push_back(SG_dataRunB_ppointS_cr);
  hists.push_back(SG_dataRunC_ppointS_cr);
  hists.push_back(SG_ZLL_ppointS_cr);
  hists.push_back(SG_TT_ppointS_cr);
  hists.push_back(SG_W3J_ppointS_cr);
  hists.push_back(SG_W2J_ppointS_cr);
  hists.push_back(SG_W1J_ppointS_cr);
  //hists.push_back(//SG_TTZ_ppointS_cr);
  //hists.push_back(//SG_WW_ppointS_cr);
  //hists.push_back(//SG_WZ_ppointS_cr);
  hists.push_back(SG_LW200_ppointS_cr);
  hists.push_back(SG_LW300_ppointS_cr);
  hists.push_back(SG_LW400_ppointS_cr);
  hists.push_back(SG_LW500_ppointS_cr);
  hists.push_back(SG_dataRunB_ppoint_cr);
  hists.push_back(SG_dataRunC_ppoint_cr);
  hists.push_back(SG_ZLL_ppoint_cr);
  hists.push_back(SG_TT_ppoint_cr);
  hists.push_back(SG_W3J_ppoint_cr);
  hists.push_back(SG_W2J_ppoint_cr);
  hists.push_back(SG_W1J_ppoint_cr);
  //hists.push_back(//SG_TTZ_ppoint_cr);
  //hists.push_back(//SG_WW_ppoint_cr);
  //hists.push_back(//SG_WZ_ppoint_cr);
  hists.push_back(SG_LW200_ppoint_cr);
  hists.push_back(SG_LW300_ppoint_cr);
  hists.push_back(SG_LW400_ppoint_cr);
  hists.push_back(SG_LW500_ppoint_cr);
  hists.push_back(SG_dataRunB_npv_cr);
  hists.push_back(SG_dataRunC_npv_cr);
  hists.push_back(SG_ZLL_npv_cr);
  hists.push_back(SG_TT_npv_cr);
  hists.push_back(SG_W3J_npv_cr);
  hists.push_back(SG_W2J_npv_cr);
  hists.push_back(SG_W1J_npv_cr);
  //hists.push_back(//SG_TTZ_npv_cr);
  //hists.push_back(//SG_WW_npv_cr);
  //hists.push_back(//SG_WZ_npv_cr);
  hists.push_back(SG_LW200_npv_cr);
  hists.push_back(SG_LW300_npv_cr);
  hists.push_back(SG_LW400_npv_cr);
  hists.push_back(SG_LW500_npv_cr);
  hists.push_back(SG_dataRunB_nsv_cr);
  hists.push_back(SG_dataRunC_nsv_cr);
  hists.push_back(SG_ZLL_nsv_cr);
  hists.push_back(SG_TT_nsv_cr);
  hists.push_back(SG_W3J_nsv_cr);
  hists.push_back(SG_W2J_nsv_cr);
  hists.push_back(SG_W1J_nsv_cr);
  //hists.push_back(//SG_TTZ_nsv_cr);
  //hists.push_back(//SG_WW_nsv_cr);
  //hists.push_back(//SG_WZ_nsv_cr);
  hists.push_back(SG_LW200_nsv_cr);
  hists.push_back(SG_LW300_nsv_cr);
  hists.push_back(SG_LW400_nsv_cr);
  hists.push_back(SG_LW500_nsv_cr);
  hists.push_back(SG_dataRunB_svd_cr);
  hists.push_back(SG_dataRunC_svd_cr);
  hists.push_back(SG_ZLL_svd_cr);
  hists.push_back(SG_TT_svd_cr);
  hists.push_back(SG_W3J_svd_cr);
  hists.push_back(SG_W2J_svd_cr);
  hists.push_back(SG_W1J_svd_cr);
  //hists.push_back(//SG_TTZ_svd_cr);
  //hists.push_back(//SG_WW_svd_cr);
  //hists.push_back(//SG_WZ_svd_cr);
  hists.push_back(SG_LW200_svd_cr);
  hists.push_back(SG_LW300_svd_cr);
  hists.push_back(SG_LW400_svd_cr);
  hists.push_back(SG_LW500_svd_cr);
  hists.push_back(SG_dataRunB_BSd_cr);
  hists.push_back(SG_dataRunC_BSd_cr);
  hists.push_back(SG_ZLL_BSd_cr);
  hists.push_back(SG_TT_BSd_cr);
  hists.push_back(SG_W3J_BSd_cr);
  hists.push_back(SG_W2J_BSd_cr);
  hists.push_back(SG_W1J_BSd_cr);
  //hists.push_back(SG_TTZ_BSd_cr);
  //hists.push_back(SG_WW_BSd_cr);
  //hists.push_back(SG_WZ_BSd_cr);
  hists.push_back(SG_LW200_BSd_cr);
  hists.push_back(SG_LW300_BSd_cr);
  hists.push_back(SG_LW400_BSd_cr);
  hists.push_back(SG_LW500_BSd_cr);
  hists.push_back(SG_dataRunB_BSdChi2norm_cr);
  hists.push_back(SG_dataRunC_BSdChi2norm_cr);
  hists.push_back(SG_ZLL_BSdChi2norm_cr);
  hists.push_back(SG_TT_BSdChi2norm_cr);
  hists.push_back(SG_W3J_BSdChi2norm_cr);
  hists.push_back(SG_W2J_BSdChi2norm_cr);
  hists.push_back(SG_W1J_BSdChi2norm_cr);
  //hists.push_back(SG_TTZ_BSdChi2norm_cr);
  //hists.push_back(SG_WW_BSdChi2norm_cr);
  //hists.push_back(SG_WZ_BSdChi2norm_cr);
  hists.push_back(SG_LW200_BSdChi2norm_cr);
  hists.push_back(SG_LW300_BSdChi2norm_cr);
  hists.push_back(SG_LW400_BSdChi2norm_cr);
  hists.push_back(SG_LW500_BSdChi2norm_cr);
  //Histograms for signal region IPP
  hists.push_back(IPP_dataRunB_ppointS_cr);
  hists.push_back(IPP_dataRunC_ppointS_cr);
  hists.push_back(IPP_ZLL_ppointS_cr);
  hists.push_back(IPP_TT_ppointS_cr);
  hists.push_back(IPP_W3J_ppointS_cr);
  hists.push_back(IPP_W2J_ppointS_cr);
  hists.push_back(IPP_W1J_ppointS_cr);
  //hists.push_back(//IPP_TTZ_ppointS_cr);
  //hists.push_back(//IPP_WW_ppointS_cr);
  //hists.push_back(//IPP_WZ_ppointS_cr);
  hists.push_back(IPP_LW200_ppointS_cr);
  hists.push_back(IPP_LW300_ppointS_cr);
  hists.push_back(IPP_LW400_ppointS_cr);
  hists.push_back(IPP_LW500_ppointS_cr);
  hists.push_back(IPP_dataRunB_ppoint_cr);
  hists.push_back(IPP_dataRunC_ppoint_cr);
  hists.push_back(IPP_ZLL_ppoint_cr);
  hists.push_back(IPP_TT_ppoint_cr);
  hists.push_back(IPP_W3J_ppoint_cr);
  hists.push_back(IPP_W2J_ppoint_cr);
  hists.push_back(IPP_W1J_ppoint_cr);
  //hists.push_back(//IPP_TTZ_ppoint_cr);
  //hists.push_back(//IPP_WW_ppoint_cr);
  //hists.push_back(//IPP_WZ_ppoint_cr);
  hists.push_back(IPP_LW200_ppoint_cr);
  hists.push_back(IPP_LW300_ppoint_cr);
  hists.push_back(IPP_LW400_ppoint_cr);
  hists.push_back(IPP_LW500_ppoint_cr);
  hists.push_back(IPP_dataRunB_npv_cr);
  hists.push_back(IPP_dataRunC_npv_cr);
  hists.push_back(IPP_ZLL_npv_cr);
  hists.push_back(IPP_TT_npv_cr);
  hists.push_back(IPP_W3J_npv_cr);
  hists.push_back(IPP_W2J_npv_cr);
  hists.push_back(IPP_W1J_npv_cr);
  //hists.push_back(//IPP_TTZ_npv_cr);
  //hists.push_back(//IPP_WW_npv_cr);
  //hists.push_back(//IPP_WZ_npv_cr);
  hists.push_back(IPP_LW200_npv_cr);
  hists.push_back(IPP_LW300_npv_cr);
  hists.push_back(IPP_LW400_npv_cr);
  hists.push_back(IPP_LW500_npv_cr);
  hists.push_back(IPP_dataRunB_nsv_cr);
  hists.push_back(IPP_dataRunC_nsv_cr);
  hists.push_back(IPP_ZLL_nsv_cr);
  hists.push_back(IPP_TT_nsv_cr);
  hists.push_back(IPP_W3J_nsv_cr);
  hists.push_back(IPP_W2J_nsv_cr);
  hists.push_back(IPP_W1J_nsv_cr);
  //hists.push_back(//IPP_TTZ_nsv_cr);
  //hists.push_back(//IPP_WW_nsv_cr);
  //hists.push_back(//IPP_WZ_nsv_cr);
  hists.push_back(IPP_LW200_nsv_cr);
  hists.push_back(IPP_LW300_nsv_cr);
  hists.push_back(IPP_LW400_nsv_cr);
  hists.push_back(IPP_LW500_nsv_cr);
  hists.push_back(IPP_dataRunB_svd_cr);
  hists.push_back(IPP_dataRunC_svd_cr);
  hists.push_back(IPP_ZLL_svd_cr);
  hists.push_back(IPP_TT_svd_cr);
  hists.push_back(IPP_W3J_svd_cr);
  hists.push_back(IPP_W2J_svd_cr);
  hists.push_back(IPP_W1J_svd_cr);
  //hists.push_back(//IPP_TTZ_svd_cr);
  //hists.push_back(//IPP_WW_svd_cr);
  //hists.push_back(//IPP_WZ_svd_cr);
  hists.push_back(IPP_LW200_svd_cr);
  hists.push_back(IPP_LW300_svd_cr);
  hists.push_back(IPP_LW400_svd_cr);
  hists.push_back(IPP_LW500_svd_cr);
  hists.push_back(IPP_dataRunB_BSd_cr);
  hists.push_back(IPP_dataRunC_BSd_cr);
  hists.push_back(IPP_ZLL_BSd_cr);
  hists.push_back(IPP_TT_BSd_cr);
  hists.push_back(IPP_W3J_BSd_cr);
  hists.push_back(IPP_W2J_BSd_cr);
  hists.push_back(IPP_W1J_BSd_cr);
  //hists.push_back(IPP_TTZ_BSd_cr);
  //hists.push_back(IPP_WW_BSd_cr);
  //hists.push_back(IPP_WZ_BSd_cr);
  hists.push_back(IPP_LW200_BSd_cr);
  hists.push_back(IPP_LW300_BSd_cr);
  hists.push_back(IPP_LW400_BSd_cr);
  hists.push_back(IPP_LW500_BSd_cr);
  hists.push_back(IPP_dataRunB_BSdChi2norm_cr);
  hists.push_back(IPP_dataRunC_BSdChi2norm_cr);
  hists.push_back(IPP_ZLL_BSdChi2norm_cr);
  hists.push_back(IPP_TT_BSdChi2norm_cr);
  hists.push_back(IPP_W3J_BSdChi2norm_cr);
  hists.push_back(IPP_W2J_BSdChi2norm_cr);
  hists.push_back(IPP_W1J_BSdChi2norm_cr);
  //hists.push_back(IPP_TTZ_BSdChi2norm_cr);
  //hists.push_back(IPP_WW_BSdChi2norm_cr);
  //hists.push_back(IPP_WZ_BSdChi2norm_cr);
  hists.push_back(IPP_LW200_BSdChi2norm_cr);
  hists.push_back(IPP_LW300_BSdChi2norm_cr);
  hists.push_back(IPP_LW400_BSdChi2norm_cr);
  hists.push_back(IPP_LW500_BSdChi2norm_cr);

      ////////////////save uncertainty value///////////////////////
        for (size_t n=0;n<Uhists.size();++n){
          hists.at(n)->Sumw2();
        }
      //////////////// end uncertainty save//////////////////


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
   electron_ch = 0;
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
   Esecvec_posx=0;
   Esecvec_posy=0;
   Esecvec_posz=0;
   Esecvec_poserrorx=0;
   Esecvec_poserrory=0;
   Esecvec_poserrorz=0;
   Esecvec_eleTag=0;
   Esecvec_normchi2=0;
   Esecvec_px=0;
   Esecvec_py=0;
   Bsp_x=0;
   Bsp_y=0;
   Bsp_z=0;
   Bsp_widthx=0;
   Bsp_widthy=0;

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
   fChain->SetBranchAddress("PV_npvsGood", &PV_npvsGood, &b_PV_npvsGood);
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
   fChain->SetBranchAddress("electron_ch",&electron_ch,&b_electron_ch);
   fChain->SetBranchAddress("trk_isHQ",&trk_isHQ,&b_trk_isHQ);
   fChain->SetBranchAddress("trigobj_px",&trigobj_px,&b_trigobj_px);
   fChain->SetBranchAddress("trigobj_py",&trigobj_py,&b_trigobj_py);
   fChain->SetBranchAddress("trigobj_pz",&trigobj_pz,&b_trigobj_pz);
   fChain->SetBranchAddress("trigobj_phi",&trigobj_phi,&b_trigobj_phi);
   fChain->SetBranchAddress("trigobj_eta",&trigobj_eta,&b_trigobj_eta);
   fChain->SetBranchAddress("trigobj_e",&trigobj_e,&b_trigobj_e);
   fChain->SetBranchAddress("Esecvec_posx",&Esecvec_posx,&b_Esecvec_posx);
   fChain->SetBranchAddress("Esecvec_posy",&Esecvec_posy,&b_Esecvec_posy);
   fChain->SetBranchAddress("Esecvec_posz",&Esecvec_posz,&b_Esecvec_posz);
   fChain->SetBranchAddress("Esecvec_poserrorx",&Esecvec_poserrorx,&b_Esecvec_poserrorx);
   fChain->SetBranchAddress("Esecvec_poserrory",&Esecvec_poserrory,&b_Esecvec_poserrory);
   fChain->SetBranchAddress("Esecvec_poserrorz",&Esecvec_poserrorz,&b_Esecvec_poserrorz);
   fChain->SetBranchAddress("Esecvec_eleTag",&Esecvec_eleTag,&b_Esecvec_eleTag);
   fChain->SetBranchAddress("Esecvec_normchi2",&Esecvec_normchi2,&b_Esecvec_normchi2);
   fChain->SetBranchAddress("Esecvec_px",&Esecvec_px,&b_Esecvec_px);
   fChain->SetBranchAddress("Esecvec_py",&Esecvec_py,&b_Esecvec_py);
   fChain->SetBranchAddress("Bsp_x",&Bsp_x,&b_Bsp_x);
   fChain->SetBranchAddress("Bsp_y",&Bsp_y,&b_Bsp_y);
   fChain->SetBranchAddress("Bsp_z",&Bsp_z,&b_Bsp_z);
   fChain->SetBranchAddress("Bsp_widthx",&Bsp_widthx,&b_Bsp_widthx);
   fChain->SetBranchAddress("Bsp_widthy",&Bsp_widthy,&b_Bsp_widthy);

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

  ///////////////////Neutral current Check/////////////////
  bool Neutralcheck=false;
  vector<pair<float,size_t>> ElecPtTemp;
  vector<pair<float,size_t>> PosiPtTemp;
  float Neutral=0;


  for (size_t i = 0; i < electron_pt->size(); i++) {
    ElecPtTemp.push_back(make_pair(electron_pt->at(i),i));
  }
  if(ElecPtTemp.size()>=2){
    sort(ElecPtTemp.begin(),ElecPtTemp.end());
    Neutral=electron_ch->at(ElecPtTemp.back().second)*electron_ch->at(ElecPtTemp.end()[-2].second);
  }
  //cout<<"Charge mult: "<<Neutral<<endl;
  if(Neutral==-1){
    //minimal selection including trigger requirement
    if (!MinimalSelection()) return;
    //counter_ms++;


    //fill histograms for signal region
    histograms("TF");

    /////Identify electron as Trig OBJ
    std::vector<bool> TobjisFound;
    TobjisFound.clear();
    size_t objcount=0;

    vector<int>  TobjisHQ;
    TobjisHQ.clear();
    size_t hqcount=0;

    for (size_t y=0; y<trigobj_e->size(); y++){
      float saveDR=100;
      int saveQ=false;
      for (size_t x=0; x<electron_e->size(); x++){
        if(abs(electron_eta->at(x))<1.44 && abs(trigobj_eta->at(y))<1.44){
          float DRet=deltaR(electron_eta->at(x),electron_phi->at(x),trigobj_eta->at(y),trigobj_phi->at(y));
          if(DRet<saveDR){
             saveDR=DRet;
             saveQ=trk_isHQ->at(x);
          }
        }
      }
      if (saveDR<0.1){
        TobjisFound.push_back(true);
        objcount++;

        TobjisHQ.push_back(saveQ);
        if(saveQ==1) hqcount++;

      }
      else{
        TobjisFound.push_back(false);
        TobjisHQ.push_back(saveQ);
      }
    }
    if(objcount<2) return;

    histograms("TO");

    //////////////HQ gsf electrons

    if(hqcount<2) return;

    histograms("HQ");

    //////////JetSelection///////
    vector<bool> JetisHQ;
    JetisHQ.clear();
    size_t Jhqcount=0;
    for(size_t x=0; x<jet_e->size(); x++){
      if(abs(jet_eta->at(x))<1.33){
        if(NConstituents->at(x)>1 && NeutralHF->at(x)<0.9 && MuonF->at(x)<0.8 && ChargedEMF->at(x)<0.6){
          JetisHQ.push_back(true);
          Jhqcount++;
        }
        else JetisHQ.push_back(false);
      }
    }
    //cout<<"No paso: "<< Jhqcount<<endl;
    if(Jhqcount<4) return;
    //cout<<" Paso: "<< Jhqcount<<endl;

    histograms("JetS");

  ///////////////////////////////////////DRcut selection//////////////////////
    vector<pair<float,size_t>> JetPtTemp;
    vector<float> EleDRTemp;
    ElecPtTemp.clear();
    PosiPtTemp.clear();
    JetPtTemp.clear();
    EleDRTemp.clear();
    float DRdiff1=100;
    float DRdiff2=100;
    Neutralcheck=false;

    for (size_t i = 0; i < electron_pt->size(); i++) {
      if(abs(electron_eta->at(i))<1.44) ElecPtTemp.push_back(make_pair(electron_pt->at(i),i));
    }
    sort(ElecPtTemp.begin(),ElecPtTemp.end());

    for(size_t x=0; x<jet_pt->size(); x++){
      if(abs(jet_eta->at(x))<1.33) JetPtTemp.push_back(make_pair(corr_jet_pt->at(x),x));
    }
    sort(JetPtTemp.begin(),JetPtTemp.end());

    if(JetPtTemp.size()>=4 && ElecPtTemp.size()>=2 && ElecPtTemp.back().first>40 && ElecPtTemp.end()[-2].first>25){
      for (size_t i = 0; i < electron_pt->size(); i++) {
        if(i==ElecPtTemp.back().second || i==ElecPtTemp.end()[-2].second){
          EleDRTemp.clear();
          for(size_t x=0; x<corr_jet_pt->size(); x++){
            if(x==JetPtTemp.back().second||x==JetPtTemp.end()[-2].second||x==JetPtTemp.end()[-3].second||x==JetPtTemp.end()[-4].second){
              EleDRTemp.push_back(deltaR(jet_eta->at(x),jet_phi->at(x),electron_eta->at(i),electron_phi->at(i)));
            }
          }
          sort(EleDRTemp.begin(),EleDRTemp.end());
          if(i==ElecPtTemp.back().second) DRdiff1=abs(EleDRTemp.at(1)-EleDRTemp.front());
          if(i==ElecPtTemp.end()[-2].second) DRdiff2=abs(EleDRTemp.at(1)-EleDRTemp.front());
        }
      }
    }
    //cout<<"No Paso: "<<DRdiff1<<" "<<DRdiff2<<endl;
    if(DRdiff1 < 0.2 || DRdiff2 < 0.2) return;
    //cout<<"\n Paso: "<<DRdiff1<<" "<<DRdiff2<<"\n\n";
   histograms("DRC");

    /////////Signal selection//////////////////
    ElecPtTemp.clear();
    PosiPtTemp.clear();
    JetPtTemp.clear();
    EleDRTemp.clear();

    Neutralcheck=false;

    for (size_t i = 0; i < electron_pt->size(); i++) {
      if(electron_ch->at(i)==1) ElecPtTemp.push_back(make_pair(electron_pt->at(i),i));
      else if(electron_ch->at(i)==-1) PosiPtTemp.push_back(make_pair(electron_pt->at(i),i));
    }
    if(ElecPtTemp.size()>=1 && PosiPtTemp.size()>=1){
      sort(ElecPtTemp.begin(),ElecPtTemp.end());
      sort(PosiPtTemp.begin(),PosiPtTemp.end());
      if( (ElecPtTemp.back().first>25 && PosiPtTemp.back().first>40) || (ElecPtTemp.back().first>40 && PosiPtTemp.back().first>25) ){
        Neutralcheck=true;
      }
    }

    //cout<<"No paso: "<<Neutralcheck<<endl;
    if(!Neutralcheck) return;
    //cout<<"Paso: "<< Neutralcheck<<endl;
     histograms("SG");
  }
  else{
    //minimal selection including trigger requirement
    if (!MinimalSelection()) return;
    //counter_ms++;


    //fill histograms for signal region
    histograms("TF");

    /////Identify electron as Trig OBJ
    std::vector<bool> TobjisFound;
    TobjisFound.clear();
    size_t objcount=0;

    vector<int>  TobjisHQ;
    TobjisHQ.clear();
    size_t hqcount=0;

    for (size_t y=0; y<trigobj_e->size(); y++){
      float saveDR=100;
      int saveQ=false;
      for (size_t x=0; x<electron_e->size(); x++){
        if(abs(electron_eta->at(x))<1.44 && abs(trigobj_eta->at(y))<1.44){
          float DRet=deltaR(electron_eta->at(x),electron_phi->at(x),trigobj_eta->at(y),trigobj_phi->at(y));
          if(DRet<saveDR){
             saveDR=DRet;
             saveQ=trk_isHQ->at(x);
          }
        }
      }
      if (saveDR<0.1){
        TobjisFound.push_back(true);
        objcount++;

        TobjisHQ.push_back(saveQ);
        if(saveQ==1) hqcount++;

      }
      else{
        TobjisFound.push_back(false);
        TobjisHQ.push_back(saveQ);
      }
    }
    if(objcount<2) return;

    histograms("TO");

    //////////////HQ gsf electrons

    if(hqcount<2) return;

    histograms("HQ");

    //////////JetSelection///////
    vector<bool> JetisHQ;
    JetisHQ.clear();
    size_t Jhqcount=0;
    for(size_t x=0; x<jet_e->size(); x++){
      if(abs(jet_eta->at(x))<1.33){
        if(NConstituents->at(x)>1 && NeutralHF->at(x)<0.9 && MuonF->at(x)<0.8 && ChargedEMF->at(x)<0.6){
          JetisHQ.push_back(true);
          Jhqcount++;
        }
        else JetisHQ.push_back(false);
      }
    }
    //cout<<"No paso: "<< Jhqcount<<endl;
    if(Jhqcount<4) return;
    //cout<<" Paso: "<< Jhqcount<<endl;

    histograms("JetS");

  ///////////////////////////////////////DRcut selection//////////////////////
    vector<pair<float,size_t>> JetPtTemp;
    vector<float> EleDRTemp;
    ElecPtTemp.clear();
    PosiPtTemp.clear();
    JetPtTemp.clear();
    EleDRTemp.clear();
    float DRdiff1=100;
    float DRdiff2=100;
    Neutralcheck=false;

    for (size_t i = 0; i < electron_pt->size(); i++) {
      if(abs(electron_eta->at(i))<1.44) ElecPtTemp.push_back(make_pair(electron_pt->at(i),i));
    }
    sort(ElecPtTemp.begin(),ElecPtTemp.end());

    for(size_t x=0; x<jet_pt->size(); x++){
      if(abs(jet_eta->at(x))<1.33) JetPtTemp.push_back(make_pair(corr_jet_pt->at(x),x));
    }
    sort(JetPtTemp.begin(),JetPtTemp.end());

    if(JetPtTemp.size()>=4 && ElecPtTemp.size()>=2 && ElecPtTemp.back().first>40 && ElecPtTemp.end()[-2].first>25){
      for (size_t i = 0; i < electron_pt->size(); i++) {
        if(i==ElecPtTemp.back().second || i==ElecPtTemp.end()[-2].second){
          EleDRTemp.clear();
          for(size_t x=0; x<corr_jet_pt->size(); x++){
            if(x==JetPtTemp.back().second||x==JetPtTemp.end()[-2].second||x==JetPtTemp.end()[-3].second||x==JetPtTemp.end()[-4].second){
              EleDRTemp.push_back(deltaR(jet_eta->at(x),jet_phi->at(x),electron_eta->at(i),electron_phi->at(i)));
            }
          }
          sort(EleDRTemp.begin(),EleDRTemp.end());
          if(i==ElecPtTemp.back().second) DRdiff1=abs(EleDRTemp.at(1)-EleDRTemp.front());
          if(i==ElecPtTemp.end()[-2].second) DRdiff2=abs(EleDRTemp.at(1)-EleDRTemp.front());
        }
      }
    }
    //cout<<"No Paso: "<<DRdiff1<<" "<<DRdiff2<<endl;
    if(DRdiff1 < 0.2 || DRdiff2 < 0.2) return;
    //cout<<"\n Paso: "<<DRdiff1<<" "<<DRdiff2<<"\n\n";
   histograms("DRC");

    /////////Signal selection//////////////////
    ElecPtTemp.clear();
    PosiPtTemp.clear();
    JetPtTemp.clear();
    EleDRTemp.clear();

    Neutralcheck=false;

    for (size_t i = 0; i < electron_pt->size(); i++) {
      ElecPtTemp.push_back(make_pair(electron_pt->at(i),i));
    }
    if(ElecPtTemp.size()>=2){
      sort(ElecPtTemp.begin(),ElecPtTemp.end());
      if( ElecPtTemp.back().first>25 && ElecPtTemp.end()[-2].first>40 ){
        Neutralcheck=true;
      }
    }

    //cout<<"No paso: "<<Neutralcheck<<endl;
    if(!Neutralcheck) return;
    //cout<<"Paso: "<< Neutralcheck<<endl;
     histograms("SG");

     /////////////////////////Is antiparallel selection////////////////////
     histograms("IPP");
  }

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


  //Int_t histsize = sizeof(hists)/sizeof(hists[0]);
  for (size_t j=0;j<hists.size();++j){
    TString histname = TString(hists.at(j)->GetName());
    TString thecut = histname(0,histname.First("_"));
    histname = histname(histname.First("_")+1,histname.Sizeof());
    TString thelabel = histname(0,histname.First("_"));
    histname = histname(histname.First("_")+1,histname.Sizeof());
    TString thevar = histname(0,histname.Sizeof());

    //cout<<"Variable: "<<thevar<<" Cut: "<<thecut<<" Label: "<<thelabel<<" hist: "<<histname<<endl;


    /////////////////////////////Electron Storage/////////////////////////////////////////
    vector<float> JetDRTemp;
    vector<pair <float,size_t> > ElePtTemp;
    vector<float> EleDRTemp;

    for (size_t i = 0; i < electron_pt->size(); i++) {
      if(abs(electron_eta->at(i))<1.44) ElePtTemp.push_back(make_pair(electron_pt->at(i),i));
    }
    sort(ElePtTemp.begin(),ElePtTemp.end());
    ///////////////////////////////////////////////////////////////////////////




    if (thecut == cut && thelabel == labeltag){
      /////////////////Antiparallel ///////////////////////////
      bool EleTagIsDisp[electron_pt->size()]={0};
      bool isAntiParallel=true;

      for(size_t i=0; i<Esecvec_posx->size(); i++){
        float Vx=Esecvec_posx->at(i)-Bsp_x->at(0);
        float Vy=Esecvec_posy->at(i)-Bsp_y->at(0);
        if(sqrt(Vx*Vx+Vy*Vy)<0.02){
          EleTagIsDisp[Esecvec_eleTag->at(i)]=true;
        }
      }

      if(cut=="IPP"){
        isAntiParallel=false;
        for(size_t i=0; i<Esecvec_posx->size(); i++){
          if(EleTagIsDisp[Esecvec_eleTag->at(i)]==false){
            float Vx=Esecvec_posx->at(i)-Bsp_x->at(0);
            float Vy=Esecvec_posy->at(i)-Bsp_y->at(0);
            float Pt=sqrt(Esecvec_px->at(i)*Esecvec_px->at(i) + Esecvec_py->at(i)*Esecvec_py->at(i));
            if(sqrt(Vx*Vx+Vy*Vy)>0.02 && Pt>20){
              float ppoint = Vx*Esecvec_px->at(i) + Vy*Esecvec_py->at(i);
              if(thelabel(0,2)=="LW"){
                if(ppoint>0) isAntiParallel=true;
              }
              else{
                if(ppoint<0) isAntiParallel=true;
              }
            }
          }
        }
      }

      if(!isAntiParallel) return;

      //primary vertices
      //cout<<"npv\n";
      float Vx,Vy,ppoint;
      if(thevar == "ppointS" || thevar == "ppointS_cr"){
        if(ElePtTemp.size()>=1){
          for(size_t i=0; i<Esecvec_posx->size(); i++){
            //if( EleTagIsDisp[Esecvec_eleTag->at(i)]==false && Esecvec_eleTag->at(i)==ElePtTemp.back().second ){
            if( EleTagIsDisp[Esecvec_eleTag->at(i)]==false ){
              Vx=Esecvec_posx->at(i)-Bsp_x->at(0);
              Vy=Esecvec_posy->at(i)-Bsp_y->at(0);
              float Pt=sqrt(Esecvec_px->at(i)*Esecvec_px->at(i) + Esecvec_py->at(i)*Esecvec_py->at(i));
              if(sqrt(Vx*Vx+Vy*Vy)>0.02 && Pt>20){
                ppoint = Vx*Esecvec_px->at(i) + Vy*Esecvec_py->at(i);
                if(thelabel(0,2)=="LW"){
                  if(ppoint<0) hists.at(j)->Fill(1, theweight);
                  else if(ppoint>0) hists.at(j)->Fill(0.0, theweight);
                }
                else{
                  if(ppoint>0) hists.at(j)->Fill(1, theweight);
                  else if(ppoint<0) hists.at(j)->Fill(0.0, theweight);
                }
              }
            }
          }
        }
      }

      if(thevar == "ppoint" || thevar == "ppoint_cr"){
        //cout<<"Variable: "<<thevar<<" Cut: "<<thecut<<" Label: "<<thelabel<<" hist: "<<histname<<endl;
        for(size_t i=0; i<Esecvec_posx->size(); i++){
          if(EleTagIsDisp[Esecvec_eleTag->at(i)]==false){
            Vx=Esecvec_posx->at(i)-Bsp_x->at(0);
            Vy=Esecvec_posy->at(i)-Bsp_y->at(0);
            float Pt=sqrt(Esecvec_px->at(i)*Esecvec_px->at(i) + Esecvec_py->at(i)*Esecvec_py->at(i));
            if(sqrt(Vx*Vx+Vy*Vy)>0.02 && Pt>20){
              ppoint = Vx*Esecvec_px->at(i) + Vy*Esecvec_py->at(i);
              //////////////save uncertainty value///////////////////////
              for (size_t n=0;n<Uhists.size();++n){
                TString Uhistname = TString(Uhists.at(n)->GetName());
                TString Uthecut = Uhistname(0,Uhistname.First("_"));
                Uhistname = Uhistname(Uhistname.First("_")+1,Uhistname.Sizeof());
                TString Uthelabel = Uhistname(0,Uhistname.First("_"));
                if( Uthecut == thecut && Uthelabel == thelabel ){
                  //cout<<" Cut: "<<Uthecut<<" Label: "<<Uthelabel<<" hist: "<<Uhistname<<endl;
                  if(Uthelabel(0,2)=="LW"){
                    //cout<<" Cut: "<<Uthecut<<" Label: "<<Uthelabel<<" hist: "<<Uhistname<<endl;
                    float uncert = sqrt(Vx*Vx*0.0001+Esecvec_px->at(i)*Esecvec_px->at(i)*0.0001
                                        +Vy*Vy*0.0001+Esecvec_py->at(i)*Esecvec_py->at(i)*0.0001);
                    Uhists.at(n)->Fill(-1*ppoint, uncert);
                  }
                  else{
                    float uncert = sqrt(Vx*Vx*0.0001+Esecvec_px->at(i)*Esecvec_px->at(i)*0.0001
                                        +Vy*Vy*0.0001+Esecvec_py->at(i)*Esecvec_py->at(i)*0.0001);
                    Uhists.at(n)->Fill(ppoint, uncert);
                  }
                }
              }
              //////////////// end uncertainty save//////////////////
              if(thelabel(0,2)=="LW"){
                hists.at(j)->Fill(-1*ppoint, theweight);
              }
              else{
                hists.at(j)->Fill(ppoint, theweight);
              }
            }
          }
        }
      }

      if(thevar == "npv" || thevar == "npv_cr"){
	       hists.at(j)->Fill(PV_npvsGood,theweight);
      }

      //secondary Vertices
      //cout<<"nsv\n";
      if(thevar == "nsv" || thevar == "nsv_cr"){
        size_t nsecvec = 0;
        for (size_t i = 0; i < Esecvec_posx->size(); i++) {
          if(Esecvec_eleTag->at(i)!=-1){
            nsecvec++;
          }
        }
	       hists.at(j)->Fill(nsecvec,theweight);
      }

      //NF secondary vertex displacements
      //cout<<"svd\n";
      if(thevar == "svd" || thevar == "svd_cr"){
        float dx,dy,dz,disp;
        for (size_t i = 0; i < Esecvec_posx->size(); i++) {
          if(Esecvec_eleTag->at(i)!=-1){
            dx=PV_x->at(0)-Esecvec_posx->at(i);
            dy=PV_y->at(0)-Esecvec_posy->at(i);
            dz=PV_z->at(0)-Esecvec_posz->at(i);
            disp=sqrt( dx*dx + dy*dy );
            hists.at(j)->Fill(disp,theweight);
          }
        }
      }
      //JetMass
      //cout<<"JetMass\n";
      /*if(thevar == "JetMass" || thevar == "JetMass_cr"){
        ////////Jet Inv Mass ///////////////////
        float px,py,pz,e,m;
        //correctedJetMass
        //float corr_pt;
        for(size_t i=0; i < jet_e->size(); i++){
          for(size_t k=i+1; k < jet_e->size(); k++){
            px=0,py=0,pz=0,e=0,m=0;
            if(abs(jet_eta->at(i))<1.33 && abs(jet_eta->at(k))<1.33){
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
      if(thevar == "LWMass" || thevar == "LWMass_cr"){
        ////////Jet Inv Mass ///////////////////
        float px,py,pz,e,m;
        //correctedJetMass
        //float corr_pt;
        for(size_t i=0; i < jet_e->size(); i++){
          for(size_t k=i+1; k < jet_e->size(); k++){
            for(size_t l=0; l < electron_e->size(); l++){
              px=0,py=0,pz=0,e=0,m=0;
              if(abs(jet_eta->at(i))<1.33 && abs(jet_eta->at(k))<1.33 && abs(electron_eta->at(l))<1.44){
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
      if(thevar == "Elept" || thevar == "Elept_cr"){
        for(size_t l=0; l < electron_e->size(); l++){
          if(abs(electron_eta->at(l))<1.44) hists.at(j)->Fill(electron_pt->at(l),theweight);
        }
      }
      //cout<<"DieledR\n";
      if(thevar == "DieledR" || thevar == "DieledR_cr"){
        for(size_t l=0; l < electron_e->size(); l++){
          for(size_t k=l+1; k < electron_e->size(); k++){
            if(abs(electron_eta->at(l))<1.44 && abs(electron_eta->at(k))<1.44){
              float dieledR= deltaR(electron_eta->at(l),electron_phi->at(l),electron_eta->at(k),electron_phi->at(k));
              hists.at(j)->Fill(dieledR,theweight);
            }
          }
        }
      }
      //cout<<"LWdR\n";
      if(thevar == "LWdR" || thevar == "LWdR_cr"){
        for(size_t l=0; l < electron_e->size(); l++){
          for(size_t k=0; k < jet_e->size(); k++){
            if(abs(electron_eta->at(l))<1.44 && abs(jet_eta->at(k))<1.33){
              float LWdR= deltaR(electron_eta->at(l),electron_phi->at(l),jet_eta->at(k),jet_phi->at(k));
              hists.at(j)->Fill(LWdR,theweight);
            }
          }
        }
      }
      //cout<<"DiJetdR\n";
      if(thevar == "DiJetdR" || thevar == "DiJetdR_cr"){
        for(size_t l=0; l < jet_e->size(); l++){
          for(size_t k=l+1; k < jet_e->size(); k++){
            if(abs(jet_eta->at(l))<1.33 && abs(jet_eta->at(k))<1.33){
              float DiJetdR= deltaR(jet_eta->at(l),jet_phi->at(l),jet_eta->at(k),jet_phi->at(k));
              hists.at(j)->Fill(DiJetdR,theweight);
            }
          }
        }
      }

      //////////////////////////////////Jet Storage///////////////////////////////////
      vector<pair<float,size_t>> JetPtTemp;
      for(size_t x=0; x<corr_jet_pt->size(); x++){
        if(abs(jet_eta->at(x))<1.33) JetPtTemp.push_back(make_pair(corr_jet_pt->at(x),x));
      }
      sort(JetPtTemp.begin(),JetPtTemp.end());
      //cout<<"BJetPt\n";
      ////////////////////////////////////////////////////////////////////////////////

      if(thevar == "BJetPt" || thevar == "BJetPt_cr"){

        if(JetPtTemp.size()>0){
          hists.at(j)->Fill(JetPtTemp.back().first,theweight);
        }

      }
      //cout<<"SBJetPT\n";
      if(thevar == "SBJetPt" || thevar == "SBJetPt_cr"){
        if(JetPtTemp.size()>1){
          hists.at(j)->Fill(JetPtTemp.at(1).first,theweight);
        }
      }
      //cout<<"NJet\n";
      if(thevar == "NJet" || thevar == "NJet_cr"){
        size_t JetC=0;
        for(size_t x=0; x<corr_jet_pt->size(); x++){
          if(abs(jet_eta->at(x))<1.33) JetC++;
        }
        hists.at(j)->Fill(JetC,theweight);
      }
      //cout<<"NEle\n";
      if(thevar == "NEle" || thevar == "NEle_cr"){
        size_t EleC=0;
        for(size_t x=0; x<electron_pt->size(); x++){
          if(abs(electron_eta->at(x))<1.44) EleC++;
        }
        hists.at(j)->Fill(EleC,theweight);
      }*/

      if(thevar == "BSd" || thevar == "BSd_cr"){
        float dx,dy,dz,disp,sigmax,sigmay,sigma;
        for (size_t i = 0; i < Esecvec_posx->size(); i++) {
          if(Esecvec_eleTag->at(i)!=-1){

            dx=Bsp_x->at(0)-Esecvec_posx->at(i);
            dy=Bsp_y->at(0)-Esecvec_posy->at(i);
            //dz=Bsp_z->at(0)-Esecvec_posz->at(i);
            sigmax=Bsp_widthx->at(0)+Esecvec_poserrorx->at(0);
            sigmay=Bsp_widthy->at(0)+Esecvec_poserrory->at(0);

            disp = sqrt( dx*dx + dy*dy );
            sigma = sqrt( sigmax*sigmax + sigmay*sigmay );
            hists.at(j)->Fill(disp/sigma,theweight);
          }
        }
      }


      if(thevar == "BSdChi2norm" || thevar == "BSdChi2norm_cr"){
        float dx,dy,dz,disp;
        for (size_t i = 0; i < Esecvec_posx->size(); i++) {
          if(Esecvec_eleTag->at(i)!=-1){

            dx=Bsp_x->at(0)-Esecvec_posx->at(i);
            dy=Bsp_y->at(0)-Esecvec_posy->at(i);
            //dz=Bsp_z->at(0)-Esecvec_posz->at(i);

            disp = sqrt( dx*dx + dy*dy );
            hists.at(j)->Fill(disp/Esecvec_normchi2->at(i),theweight);
          }
        }
      }



      /*if(thevar == "EleJet1DR" || thevar == "EleJet1DR_cr"){
        if(JetPtTemp.size()>=4 && ElePtTemp.size()>=2 && ElePtTemp.back().first>40 && ElePtTemp.end()[-2].first>25){
          for (size_t i = 0; i < electron_pt->size(); i++) {
            if(i==ElePtTemp.back().second || i==ElePtTemp.end()[-2].second){
              EleDRTemp.clear();
              for(size_t x=0; x<corr_jet_pt->size(); x++){
                if(x==JetPtTemp.back().second||x==JetPtTemp.end()[-2].second||x==JetPtTemp.end()[-3].second||x==JetPtTemp.end()[-4].second){
                  EleDRTemp.push_back(deltaR(jet_eta->at(x),jet_phi->at(x),electron_eta->at(i),electron_phi->at(i)));
                }
              }
              sort(EleDRTemp.begin(),EleDRTemp.end());
              hists.at(j)->Fill(EleDRTemp.front());
            }
          }
        }
      }


      if(thevar == "EleJet2DR" || thevar == "EleJet2DR_cr"){
        if(JetPtTemp.size()>=4 && ElePtTemp.size()>=2 && ElePtTemp.back().first>40 && ElePtTemp.end()[-2].first>25){
          for (size_t i = 0; i < electron_pt->size(); i++) {
            if(i==ElePtTemp.back().second || i==ElePtTemp.end()[-2].second){
              EleDRTemp.clear();
              for(size_t x=0; x<corr_jet_pt->size(); x++){
                if(x==JetPtTemp.back().second||x==JetPtTemp.end()[-2].second||x==JetPtTemp.end()[-3].second||x==JetPtTemp.end()[-4].second){
                  EleDRTemp.push_back(deltaR(jet_eta->at(x),jet_phi->at(x),electron_eta->at(i),electron_phi->at(i)));
                }
              }
              sort(EleDRTemp.begin(),EleDRTemp.end());
              hists.at(j)->Fill(EleDRTemp.at(1));
            }
          }
        }
      }

      if(thevar == "JetJet1DR" || thevar == "JetJet1DR_cr"){
        if(JetPtTemp.size()>=4 && ElePtTemp.size()>=2 && ElePtTemp.back().first>40 && ElePtTemp.end()[-2].first>25){
          for(size_t x=0; x<corr_jet_pt->size(); x++){
            if(x==JetPtTemp.back().second||x==JetPtTemp.end()[-2].second||x==JetPtTemp.end()[-3].second||x==JetPtTemp.end()[-4].second){
              JetDRTemp.clear();
              for(size_t y=x+1; y<corr_jet_pt->size(); y++){
                if(y==JetPtTemp.back().second||y==JetPtTemp.end()[-2].second||y==JetPtTemp.end()[-3].second||y==JetPtTemp.end()[-4].second){
                  JetDRTemp.push_back(deltaR(jet_eta->at(x),jet_phi->at(x),jet_eta->at(y),jet_phi->at(y)));
                }
              }
              sort(JetDRTemp.begin(),JetDRTemp.end());
              hists.at(j)->Fill(JetDRTemp.front());
            }
          }
        }
      }

      if(thevar == "JetJet2DR" || thevar == "JetJet2DR_cr"){
        if(JetPtTemp.size()>=4 && ElePtTemp.size()>=2 && ElePtTemp.back().first>40 && ElePtTemp.end()[-2].first>25){
          for(size_t x=0; x<corr_jet_pt->size(); x++){
            if(x==JetPtTemp.back().second||x==JetPtTemp.end()[-2].second||x==JetPtTemp.end()[-3].second||x==JetPtTemp.end()[-4].second){
              JetDRTemp.clear();
              for(size_t y=x+1; y<corr_jet_pt->size(); y++){
                if(y==JetPtTemp.back().second||y==JetPtTemp.end()[-2].second||y==JetPtTemp.end()[-3].second||y==JetPtTemp.end()[-4].second){
                  JetDRTemp.push_back(deltaR(jet_eta->at(x),jet_phi->at(x),jet_eta->at(y),jet_phi->at(y)));

                }
              }

              sort(JetDRTemp.begin(),JetDRTemp.end());
              if(JetDRTemp.size()>=2)hists.at(j)->Fill(JetDRTemp.at(1));
            }
          }
        }
      }

      if(thevar == "JetJetFDR" || thevar == "JetJetFDR_cr"){
        if(JetPtTemp.size()>=4 && ElePtTemp.size()>=2 && ElePtTemp.back().first>40 && ElePtTemp.end()[-2].first>25){
          for(size_t x=0; x<corr_jet_pt->size(); x++){
            if(x==JetPtTemp.back().second||x==JetPtTemp.end()[-2].second||x==JetPtTemp.end()[-3].second||x==JetPtTemp.end()[-4].second){
              JetDRTemp.clear();
              for(size_t y=x+1; y<corr_jet_pt->size(); y++){
                if(y==JetPtTemp.back().second||y==JetPtTemp.end()[-2].second||y==JetPtTemp.end()[-3].second||y==JetPtTemp.end()[-4].second){
                  JetDRTemp.push_back(deltaR(jet_eta->at(x),jet_phi->at(x),jet_eta->at(y),jet_phi->at(y)));
                }
              }

              sort(JetDRTemp.begin(),JetDRTemp.end());
              hists.at(j)->Fill(JetDRTemp.back());
            }
          }
        }
      }*/
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

  TFile* hfile = new TFile("Histograms/histogramsII.root","RECREATE");

  //Save uncertainty histograms
  NF_dataRunB_ppoint_uncert->Write();
  NF_dataRunC_ppoint_uncert->Write();
  NF_ZLL_ppoint_uncert->Write();
  NF_TT_ppoint_uncert->Write();
  NF_W3J_ppoint_uncert->Write();
  NF_W2J_ppoint_uncert->Write();
  NF_W1J_ppoint_uncert->Write();
  //NF_WW_ppoint_uncert->Write();
  //NF_WZ_ppoint_uncert->Write();
  //NF_TTZ_ppoint_uncert->Write();
  NF_LW200_ppoint_uncert->Write();
  //NF_LW300_ppoint_uncert->Write();
  //NF_LW400_ppoint_uncert->Write();
  //NF_LW500_ppoint_uncert->Write();

  TF_dataRunB_ppoint_uncert->Write();
  TF_dataRunC_ppoint_uncert->Write();
  TF_ZLL_ppoint_uncert->Write();
  TF_TT_ppoint_uncert->Write();
  TF_W3J_ppoint_uncert->Write();
  TF_W2J_ppoint_uncert->Write();
  TF_W1J_ppoint_uncert->Write();
  //TF_WW_ppoint_uncert->Write();
  //TF_WZ_ppoint_uncert->Write();
  //TF_TTZ_ppoint_uncert->Write();
  TF_LW200_ppoint_uncert->Write();
  //TF_LW300_ppoint_uncert->Write();
  //TF_LW400_ppoint_uncert->Write();
  //TF_LW500_ppoint_uncert->Write();

  TO_dataRunB_ppoint_uncert->Write();
  TO_dataRunC_ppoint_uncert->Write();
  TO_ZLL_ppoint_uncert->Write();
  TO_TT_ppoint_uncert->Write();
  TO_W3J_ppoint_uncert->Write();
  TO_W2J_ppoint_uncert->Write();
  TO_W1J_ppoint_uncert->Write();
  //TO_WW_ppoint_uncert->Write();
  //TO_WZ_ppoint_uncert->Write();
  //TO_TTZ_ppoint_uncert->Write();
  TO_LW200_ppoint_uncert->Write();
  //TO_LW300_ppoint_uncert->Write();
  //TO_LW400_ppoint_uncert->Write();
  //TO_LW500_ppoint_uncert->Write();

  HQ_dataRunB_ppoint_uncert->Write();
  HQ_dataRunC_ppoint_uncert->Write();
  HQ_ZLL_ppoint_uncert->Write();
  HQ_TT_ppoint_uncert->Write();
  HQ_W3J_ppoint_uncert->Write();
  HQ_W2J_ppoint_uncert->Write();
  HQ_W1J_ppoint_uncert->Write();
  //HQ_WW_ppoint_uncert->Write();
  //HQ_WZ_ppoint_uncert->Write();
  //HQ_TTZ_ppoint_uncert->Write();
  HQ_LW200_ppoint_uncert->Write();
  //HQ_LW300_ppoint_uncert->Write();
  //HQ_LW400_ppoint_uncert->Write();
  //HQ_LW500_ppoint_uncert->Write();

  SG_dataRunB_ppoint_uncert->Write();
  SG_dataRunC_ppoint_uncert->Write();
  SG_ZLL_ppoint_uncert->Write();
  SG_TT_ppoint_uncert->Write();
  SG_W3J_ppoint_uncert->Write();
  SG_W2J_ppoint_uncert->Write();
  SG_W1J_ppoint_uncert->Write();
  //SG_WW_ppoint_uncert->Write();
  //SG_WZ_ppoint_uncert->Write();
  //SG_TTZ_ppoint_uncert->Write();
  SG_LW200_ppoint_uncert->Write();
  //SG_LW300_ppoint_uncert->Write();
  //SG_LW400_ppoint_uncert->Write();
  //SG_LW500_ppoint_uncert->Write();

  JetS_dataRunB_ppoint_uncert->Write();
  JetS_dataRunC_ppoint_uncert->Write();
  JetS_ZLL_ppoint_uncert->Write();
  JetS_TT_ppoint_uncert->Write();
  JetS_W3J_ppoint_uncert->Write();
  JetS_W2J_ppoint_uncert->Write();
  JetS_W1J_ppoint_uncert->Write();
  //JetS_WW_ppoint_uncert->Write();
  //JetS_WZ_ppoint_uncert->Write();
  //JetS_TTZ_ppoint_uncert->Write();
  JetS_LW200_ppoint_uncert->Write();
  //JetS_LW300_ppoint_uncert->Write();
  //JetS_LW400_ppoint_uncert->Write();
  //JetS_LW500_ppoint_uncert->Write();

  DRC_dataRunB_ppoint_uncert->Write();
  DRC_dataRunC_ppoint_uncert->Write();
  DRC_ZLL_ppoint_uncert->Write();
  DRC_TT_ppoint_uncert->Write();
  DRC_W3J_ppoint_uncert->Write();
  DRC_W2J_ppoint_uncert->Write();
  DRC_W1J_ppoint_uncert->Write();
  //DRC_WW_ppoint_uncert->Write();
  //DRC_WZ_ppoint_uncert->Write();
  //DRC_TTZ_ppoint_uncert->Write();
  DRC_LW200_ppoint_uncert->Write();
  //DRC_LW300_ppoint_uncert->Write();
  //DRC_LW400_ppoint_uncert->Write();
  //DRC_LW500_ppoint_uncert->Write();

  IPP_dataRunB_ppoint_uncert->Write();
  IPP_dataRunC_ppoint_uncert->Write();
  IPP_ZLL_ppoint_uncert->Write();
  IPP_TT_ppoint_uncert->Write();
  IPP_W3J_ppoint_uncert->Write();
  IPP_W2J_ppoint_uncert->Write();
  IPP_W1J_ppoint_uncert->Write();
  //IPP_WW_ppoint_uncert->Write();
  //IPP_WZ_ppoint_uncert->Write();
  //IPP_TTZ_ppoint_uncert->Write();
  IPP_LW200_ppoint_uncert->Write();
  //IPP_LW300_ppoint_uncert->Write();
  //IPP_LW400_ppoint_uncert->Write();
  //IPP_LW500_ppoint_uncert->Write();

  //Save signal region histos
  NF_dataRunB_ppointS->Write();
  NF_dataRunC_ppointS ->Write();
  NF_ZLL_ppointS->Write();
  NF_TT_ppointS->Write();
  NF_W3J_ppointS->Write();
  NF_W2J_ppointS->Write();
  NF_W1J_ppointS->Write();
  ////NF_TTZ_ppointS->Write();
  ////NF_WW_ppointS->Write();
  ////NF_WZ_ppointS->Write();
  NF_LW200_ppointS->Write();
  NF_LW300_ppointS->Write();
  NF_LW400_ppointS->Write();
  NF_LW500_ppointS->Write();
  NF_dataRunB_ppoint->Write();
  NF_dataRunC_ppoint ->Write();
  NF_ZLL_ppoint->Write();
  NF_TT_ppoint->Write();
  NF_W3J_ppoint->Write();
  NF_W2J_ppoint->Write();
  NF_W1J_ppoint->Write();
  ////NF_TTZ_ppoint->Write();
  ////NF_WW_ppoint->Write();
  ////NF_WZ_ppoint->Write();
  NF_LW200_ppoint->Write();
  NF_LW300_ppoint->Write();
  NF_LW400_ppoint->Write();
  NF_LW500_ppoint->Write();
  NF_dataRunB_npv->Write();
  NF_dataRunC_npv ->Write();
  NF_ZLL_npv->Write();
  NF_TT_npv->Write();
  NF_W3J_npv->Write();
  NF_W2J_npv->Write();
  NF_W1J_npv->Write();
  ////NF_TTZ_npv->Write();
  ////NF_WW_npv->Write();
  ////NF_WZ_npv->Write();
  NF_LW200_npv->Write();
  NF_LW300_npv->Write();
  NF_LW400_npv->Write();
  NF_LW500_npv->Write();
  NF_dataRunB_nsv->Write();
  NF_dataRunC_nsv ->Write();
  NF_ZLL_nsv->Write();
  NF_TT_nsv->Write();
  NF_W3J_nsv->Write();
  NF_W2J_nsv->Write();
  NF_W1J_nsv->Write();
  ////NF_TTZ_nsv->Write();
  ////NF_WW_nsv->Write();
  ////NF_WZ_nsv->Write();
  NF_LW200_nsv->Write();
  NF_LW300_nsv->Write();
  NF_LW400_nsv->Write();
  NF_LW500_nsv->Write();
  NF_dataRunB_svd->Write();
  NF_dataRunC_svd ->Write();
  NF_ZLL_svd->Write();
  NF_TT_svd->Write();
  NF_W3J_svd->Write();
  NF_W2J_svd->Write();
  NF_W1J_svd->Write();
  ////NF_TTZ_svd->Write();
  ////NF_WW_svd->Write();
  ////NF_WZ_svd->Write();
  NF_LW200_svd->Write();
  NF_LW300_svd->Write();
  NF_LW400_svd->Write();
  NF_LW500_svd->Write();
  NF_dataRunB_BSd->Write();
  NF_dataRunC_BSd ->Write();
  NF_ZLL_BSd->Write();
  NF_TT_BSd->Write();
  NF_W3J_BSd->Write();
  NF_W2J_BSd->Write();
  NF_W1J_BSd->Write();
  //NF_TTZ_BSd->Write();
  //NF_WW_BSd->Write();
  //NF_WZ_BSd->Write();
  NF_LW200_BSd->Write();
  NF_LW300_BSd->Write();
  NF_LW400_BSd->Write();
  NF_LW500_BSd->Write();
  NF_dataRunB_BSdChi2norm->Write();
  NF_dataRunC_BSdChi2norm ->Write();
  NF_ZLL_BSdChi2norm->Write();
  NF_TT_BSdChi2norm->Write();
  NF_W3J_BSdChi2norm->Write();
  NF_W2J_BSdChi2norm->Write();
  NF_W1J_BSdChi2norm->Write();
  //NF_TTZ_BSdChi2norm->Write();
  //NF_WW_BSdChi2norm->Write();
  //NF_WZ_BSdChi2norm->Write();
  NF_LW200_BSdChi2norm->Write();
  NF_LW300_BSdChi2norm->Write();
  NF_LW400_BSdChi2norm->Write();
  NF_LW500_BSdChi2norm->Write();
  //Histograms for signal region TF
  TF_dataRunB_ppointS->Write();
  TF_dataRunC_ppointS ->Write();
  TF_ZLL_ppointS->Write();
  TF_TT_ppointS->Write();
  TF_W3J_ppointS->Write();
  TF_W2J_ppointS->Write();
  TF_W1J_ppointS->Write();
  ////TF_TTZ_ppointS->Write();
  ////TF_WW_ppointS->Write();
  ////TF_WZ_ppointS->Write();
  TF_LW200_ppointS->Write();
  TF_LW300_ppointS->Write();
  TF_LW400_ppointS->Write();
  TF_LW500_ppointS->Write();
  TF_dataRunB_ppoint->Write();
  TF_dataRunC_ppoint ->Write();
  TF_ZLL_ppoint->Write();
  TF_TT_ppoint->Write();
  TF_W3J_ppoint->Write();
  TF_W2J_ppoint->Write();
  TF_W1J_ppoint->Write();
  ////TF_TTZ_ppoint->Write();
  ////TF_WW_ppoint->Write();
  ////TF_WZ_ppoint->Write();
  TF_LW200_ppoint->Write();
  TF_LW300_ppoint->Write();
  TF_LW400_ppoint->Write();
  TF_LW500_ppoint->Write();
  TF_dataRunB_npv->Write();
  TF_dataRunC_npv ->Write();
  TF_ZLL_npv->Write();
  TF_TT_npv->Write();
  TF_W3J_npv->Write();
  TF_W2J_npv->Write();
  TF_W1J_npv->Write();
  ////TF_TTZ_npv->Write();
  ////TF_WW_npv->Write();
  ////TF_WZ_npv->Write();
  TF_LW200_npv->Write();
  TF_LW300_npv->Write();
  TF_LW400_npv->Write();
  TF_LW500_npv->Write();
  TF_dataRunB_nsv->Write();
  TF_dataRunC_nsv ->Write();
  TF_ZLL_nsv->Write();
  TF_TT_nsv->Write();
  TF_W3J_nsv->Write();
  TF_W2J_nsv->Write();
  TF_W1J_nsv->Write();
  ////TF_TTZ_nsv->Write();
  ////TF_WW_nsv->Write();
  ////TF_WZ_nsv->Write();
  TF_LW200_nsv->Write();
  TF_LW300_nsv->Write();
  TF_LW400_nsv->Write();
  TF_LW500_nsv->Write();
  TF_dataRunB_svd->Write();
  TF_dataRunC_svd ->Write();
  TF_ZLL_svd->Write();
  TF_TT_svd->Write();
  TF_W3J_svd->Write();
  TF_W2J_svd->Write();
  TF_W1J_svd->Write();
  ////TF_TTZ_svd->Write();
  ////TF_WW_svd->Write();
  ////TF_WZ_svd->Write();
  TF_LW200_svd->Write();
  TF_LW300_svd->Write();
  TF_LW400_svd->Write();
  TF_LW500_svd->Write();
  TF_dataRunB_BSd->Write();
  TF_dataRunC_BSd ->Write();
  TF_ZLL_BSd->Write();
  TF_TT_BSd->Write();
  TF_W3J_BSd->Write();
  TF_W2J_BSd->Write();
  TF_W1J_BSd->Write();
  //TF_TTZ_BSd->Write();
  //TF_WW_BSd->Write();
  //TF_WZ_BSd->Write();
  TF_LW200_BSd->Write();
  TF_LW300_BSd->Write();
  TF_LW400_BSd->Write();
  TF_LW500_BSd->Write();
  TF_dataRunB_BSdChi2norm->Write();
  TF_dataRunC_BSdChi2norm ->Write();
  TF_ZLL_BSdChi2norm->Write();
  TF_TT_BSdChi2norm->Write();
  TF_W3J_BSdChi2norm->Write();
  TF_W2J_BSdChi2norm->Write();
  TF_W1J_BSdChi2norm->Write();
  //TF_TTZ_BSdChi2norm->Write();
  //TF_WW_BSdChi2norm->Write();
  //TF_WZ_BSdChi2norm->Write();
  TF_LW200_BSdChi2norm->Write();
  TF_LW300_BSdChi2norm->Write();
  TF_LW400_BSdChi2norm->Write();
  TF_LW500_BSdChi2norm->Write();
  //Histograms for signal region TO
  TO_dataRunB_ppointS->Write();
  TO_dataRunC_ppointS ->Write();
  TO_ZLL_ppointS->Write();
  TO_TT_ppointS->Write();
  TO_W3J_ppointS->Write();
  TO_W2J_ppointS->Write();
  TO_W1J_ppointS->Write();
  ////TO_TTZ_ppointS->Write();
  ////TO_WW_ppointS->Write();
  ////TO_WZ_ppointS->Write();
  TO_LW200_ppointS->Write();
  TO_LW300_ppointS->Write();
  TO_LW400_ppointS->Write();
  TO_LW500_ppointS->Write();
  TO_dataRunB_ppoint->Write();
  TO_dataRunC_ppoint ->Write();
  TO_ZLL_ppoint->Write();
  TO_TT_ppoint->Write();
  TO_W3J_ppoint->Write();
  TO_W2J_ppoint->Write();
  TO_W1J_ppoint->Write();
  ////TO_TTZ_ppoint->Write();
  ////TO_WW_ppoint->Write();
  ////TO_WZ_ppoint->Write();
  TO_LW200_ppoint->Write();
  TO_LW300_ppoint->Write();
  TO_LW400_ppoint->Write();
  TO_LW500_ppoint->Write();
  TO_dataRunB_npv->Write();
  TO_dataRunC_npv ->Write();
  TO_ZLL_npv->Write();
  TO_TT_npv->Write();
  TO_W3J_npv->Write();
  TO_W2J_npv->Write();
  TO_W1J_npv->Write();
  ////TO_TTZ_npv->Write();
  ////TO_WW_npv->Write();
  ////TO_WZ_npv->Write();
  TO_LW200_npv->Write();
  TO_LW300_npv->Write();
  TO_LW400_npv->Write();
  TO_LW500_npv->Write();
  TO_dataRunB_nsv->Write();
  TO_dataRunC_nsv ->Write();
  TO_ZLL_nsv->Write();
  TO_TT_nsv->Write();
  TO_W3J_nsv->Write();
  TO_W2J_nsv->Write();
  TO_W1J_nsv->Write();
  ////TO_TTZ_nsv->Write();
  ////TO_WW_nsv->Write();
  ////TO_WZ_nsv->Write();
  TO_LW200_nsv->Write();
  TO_LW300_nsv->Write();
  TO_LW400_nsv->Write();
  TO_LW500_nsv->Write();
  TO_dataRunB_svd->Write();
  TO_dataRunC_svd ->Write();
  TO_ZLL_svd->Write();
  TO_TT_svd->Write();
  TO_W3J_svd->Write();
  TO_W2J_svd->Write();
  TO_W1J_svd->Write();
  ////TO_TTZ_svd->Write();
  ////TO_WW_svd->Write();
  ////TO_WZ_svd->Write();
  TO_LW200_svd->Write();
  TO_LW300_svd->Write();
  TO_LW400_svd->Write();
  TO_LW500_svd->Write();
  TO_dataRunB_BSd->Write();
  TO_dataRunC_BSd ->Write();
  TO_ZLL_BSd->Write();
  TO_TT_BSd->Write();
  TO_W3J_BSd->Write();
  TO_W2J_BSd->Write();
  TO_W1J_BSd->Write();
  //TO_TTZ_BSd->Write();
  //TO_WW_BSd->Write();
  //TO_WZ_BSd->Write();
  TO_LW200_BSd->Write();
  TO_LW300_BSd->Write();
  TO_LW400_BSd->Write();
  TO_LW500_BSd->Write();
  TO_dataRunB_BSdChi2norm->Write();
  TO_dataRunC_BSdChi2norm ->Write();
  TO_ZLL_BSdChi2norm->Write();
  TO_TT_BSdChi2norm->Write();
  TO_W3J_BSdChi2norm->Write();
  TO_W2J_BSdChi2norm->Write();
  TO_W1J_BSdChi2norm->Write();
  //TO_TTZ_BSdChi2norm->Write();
  //TO_WW_BSdChi2norm->Write();
  //TO_WZ_BSdChi2norm->Write();
  TO_LW200_BSdChi2norm->Write();
  TO_LW300_BSdChi2norm->Write();
  TO_LW400_BSdChi2norm->Write();
  TO_LW500_BSdChi2norm->Write();
  //Histograms for signal region HQ
  HQ_dataRunB_ppointS->Write();
  HQ_dataRunC_ppointS ->Write();
  HQ_ZLL_ppointS->Write();
  HQ_TT_ppointS->Write();
  HQ_W3J_ppointS->Write();
  HQ_W2J_ppointS->Write();
  HQ_W1J_ppointS->Write();
  ////HQ_TTZ_ppointS->Write();
  ////HQ_WW_ppointS->Write();
  ////HQ_WZ_ppointS->Write();
  HQ_LW200_ppointS->Write();
  HQ_LW300_ppointS->Write();
  HQ_LW400_ppointS->Write();
  HQ_LW500_ppointS->Write();
  HQ_dataRunB_ppoint->Write();
  HQ_dataRunC_ppoint ->Write();
  HQ_ZLL_ppoint->Write();
  HQ_TT_ppoint->Write();
  HQ_W3J_ppoint->Write();
  HQ_W2J_ppoint->Write();
  HQ_W1J_ppoint->Write();
  ////HQ_TTZ_ppoint->Write();
  ////HQ_WW_ppoint->Write();
  ////HQ_WZ_ppoint->Write();
  HQ_LW200_ppoint->Write();
  HQ_LW300_ppoint->Write();
  HQ_LW400_ppoint->Write();
  HQ_LW500_ppoint->Write();
  HQ_dataRunB_npv->Write();
  HQ_dataRunC_npv ->Write();
  HQ_ZLL_npv->Write();
  HQ_TT_npv->Write();
  HQ_W3J_npv->Write();
  HQ_W2J_npv->Write();
  HQ_W1J_npv->Write();
  ////HQ_TTZ_npv->Write();
  ////HQ_WW_npv->Write();
  ////HQ_WZ_npv->Write();
  HQ_LW200_npv->Write();
  HQ_LW300_npv->Write();
  HQ_LW400_npv->Write();
  HQ_LW500_npv->Write();
  HQ_dataRunB_nsv->Write();
  HQ_dataRunC_nsv ->Write();
  HQ_ZLL_nsv->Write();
  HQ_TT_nsv->Write();
  HQ_W3J_nsv->Write();
  HQ_W2J_nsv->Write();
  HQ_W1J_nsv->Write();
  ////HQ_TTZ_nsv->Write();
  ////HQ_WW_nsv->Write();
  ////HQ_WZ_nsv->Write();
  HQ_LW200_nsv->Write();
  HQ_LW300_nsv->Write();
  HQ_LW400_nsv->Write();
  HQ_LW500_nsv->Write();
  HQ_dataRunB_svd->Write();
  HQ_dataRunC_svd ->Write();
  HQ_ZLL_svd->Write();
  HQ_TT_svd->Write();
  HQ_W3J_svd->Write();
  HQ_W2J_svd->Write();
  HQ_W1J_svd->Write();
  ////HQ_TTZ_svd->Write();
  ////HQ_WW_svd->Write();
  ////HQ_WZ_svd->Write();
  HQ_LW200_svd->Write();
  HQ_LW300_svd->Write();
  HQ_LW400_svd->Write();
  HQ_LW500_svd->Write();
  HQ_dataRunB_BSd->Write();
  HQ_dataRunC_BSd ->Write();
  HQ_ZLL_BSd->Write();
  HQ_TT_BSd->Write();
  HQ_W3J_BSd->Write();
  HQ_W2J_BSd->Write();
  HQ_W1J_BSd->Write();
  //HQ_TTZ_BSd->Write();
  //HQ_WW_BSd->Write();
  //HQ_WZ_BSd->Write();
  HQ_LW200_BSd->Write();
  HQ_LW300_BSd->Write();
  HQ_LW400_BSd->Write();
  HQ_LW500_BSd->Write();
  HQ_dataRunB_BSdChi2norm->Write();
  HQ_dataRunC_BSdChi2norm ->Write();
  HQ_ZLL_BSdChi2norm->Write();
  HQ_TT_BSdChi2norm->Write();
  HQ_W3J_BSdChi2norm->Write();
  HQ_W2J_BSdChi2norm->Write();
  HQ_W1J_BSdChi2norm->Write();
  //HQ_TTZ_BSdChi2norm->Write();
  //HQ_WW_BSdChi2norm->Write();
  //HQ_WZ_BSdChi2norm->Write();
  HQ_LW200_BSdChi2norm->Write();
  HQ_LW300_BSdChi2norm->Write();
  HQ_LW400_BSdChi2norm->Write();
  HQ_LW500_BSdChi2norm->Write();
  //Histograms for signal region JetS
  JetS_dataRunB_ppointS->Write();
  JetS_dataRunC_ppointS ->Write();
  JetS_ZLL_ppointS->Write();
  JetS_TT_ppointS->Write();
  JetS_W3J_ppointS->Write();
  JetS_W2J_ppointS->Write();
  JetS_W1J_ppointS->Write();
  ////JetS_TTZ_ppointS->Write();
  ////JetS_WW_ppointS->Write();
  ////JetS_WZ_ppointS->Write();
  JetS_LW200_ppointS->Write();
  JetS_LW300_ppointS->Write();
  JetS_LW400_ppointS->Write();
  JetS_LW500_ppointS->Write();
  JetS_dataRunB_ppoint->Write();
  JetS_dataRunC_ppoint ->Write();
  JetS_ZLL_ppoint->Write();
  JetS_TT_ppoint->Write();
  JetS_W3J_ppoint->Write();
  JetS_W2J_ppoint->Write();
  JetS_W1J_ppoint->Write();
  ////JetS_TTZ_ppoint->Write();
  ////JetS_WW_ppoint->Write();
  ////JetS_WZ_ppoint->Write();
  JetS_LW200_ppoint->Write();
  JetS_LW300_ppoint->Write();
  JetS_LW400_ppoint->Write();
  JetS_LW500_ppoint->Write();
  JetS_dataRunB_npv->Write();
  JetS_dataRunC_npv ->Write();
  JetS_ZLL_npv->Write();
  JetS_TT_npv->Write();
  JetS_W3J_npv->Write();
  JetS_W2J_npv->Write();
  JetS_W1J_npv->Write();
  ////JetS_TTZ_npv->Write();
  ////JetS_WW_npv->Write();
  ////JetS_WZ_npv->Write();
  JetS_LW200_npv->Write();
  JetS_LW300_npv->Write();
  JetS_LW400_npv->Write();
  JetS_LW500_npv->Write();
  JetS_dataRunB_nsv->Write();
  JetS_dataRunC_nsv ->Write();
  JetS_ZLL_nsv->Write();
  JetS_TT_nsv->Write();
  JetS_W3J_nsv->Write();
  JetS_W2J_nsv->Write();
  JetS_W1J_nsv->Write();
  ////JetS_TTZ_nsv->Write();
  ////JetS_WW_nsv->Write();
  ////JetS_WZ_nsv->Write();
  JetS_LW200_nsv->Write();
  JetS_LW300_nsv->Write();
  JetS_LW400_nsv->Write();
  JetS_LW500_nsv->Write();
  JetS_dataRunB_svd->Write();
  JetS_dataRunC_svd ->Write();
  JetS_ZLL_svd->Write();
  JetS_TT_svd->Write();
  JetS_W3J_svd->Write();
  JetS_W2J_svd->Write();
  JetS_W1J_svd->Write();
  ////JetS_TTZ_svd->Write();
  ////JetS_WW_svd->Write();
  ////JetS_WZ_svd->Write();
  JetS_LW200_svd->Write();
  JetS_LW300_svd->Write();
  JetS_LW400_svd->Write();
  JetS_LW500_svd->Write();
  JetS_dataRunB_BSd->Write();
  JetS_dataRunC_BSd ->Write();
  JetS_ZLL_BSd->Write();
  JetS_TT_BSd->Write();
  JetS_W3J_BSd->Write();
  JetS_W2J_BSd->Write();
  JetS_W1J_BSd->Write();
  //JetS_TTZ_BSd->Write();
  //JetS_WW_BSd->Write();
  //JetS_WZ_BSd->Write();
  JetS_LW200_BSd->Write();
  JetS_LW300_BSd->Write();
  JetS_LW400_BSd->Write();
  JetS_LW500_BSd->Write();
  JetS_dataRunB_BSdChi2norm->Write();
  JetS_dataRunC_BSdChi2norm ->Write();
  JetS_ZLL_BSdChi2norm->Write();
  JetS_TT_BSdChi2norm->Write();
  JetS_W3J_BSdChi2norm->Write();
  JetS_W2J_BSdChi2norm->Write();
  JetS_W1J_BSdChi2norm->Write();
  //JetS_TTZ_BSdChi2norm->Write();
  //JetS_WW_BSdChi2norm->Write();
  //JetS_WZ_BSdChi2norm->Write();
  JetS_LW200_BSdChi2norm->Write();
  JetS_LW300_BSdChi2norm->Write();
  JetS_LW400_BSdChi2norm->Write();
  JetS_LW500_BSdChi2norm->Write();
  //Histograms for signal region DRC
  DRC_dataRunB_ppointS->Write();
  DRC_dataRunC_ppointS ->Write();
  DRC_ZLL_ppointS->Write();
  DRC_TT_ppointS->Write();
  DRC_W3J_ppointS->Write();
  DRC_W2J_ppointS->Write();
  DRC_W1J_ppointS->Write();
  ////DRC_TTZ_ppointS->Write();
  ////DRC_WW_ppointS->Write();
  ////DRC_WZ_ppointS->Write();
  DRC_LW200_ppointS->Write();
  DRC_LW300_ppointS->Write();
  DRC_LW400_ppointS->Write();
  DRC_LW500_ppointS->Write();
  DRC_dataRunB_ppoint->Write();
  DRC_dataRunC_ppoint ->Write();
  DRC_ZLL_ppoint->Write();
  DRC_TT_ppoint->Write();
  DRC_W3J_ppoint->Write();
  DRC_W2J_ppoint->Write();
  DRC_W1J_ppoint->Write();
  ////DRC_TTZ_ppoint->Write();
  ////DRC_WW_ppoint->Write();
  ////DRC_WZ_ppoint->Write();
  DRC_LW200_ppoint->Write();
  DRC_LW300_ppoint->Write();
  DRC_LW400_ppoint->Write();
  DRC_LW500_ppoint->Write();
  DRC_dataRunB_npv->Write();
  DRC_dataRunC_npv ->Write();
  DRC_ZLL_npv->Write();
  DRC_TT_npv->Write();
  DRC_W3J_npv->Write();
  DRC_W2J_npv->Write();
  DRC_W1J_npv->Write();
  ////DRC_TTZ_npv->Write();
  ////DRC_WW_npv->Write();
  ////DRC_WZ_npv->Write();
  DRC_LW200_npv->Write();
  DRC_LW300_npv->Write();
  DRC_LW400_npv->Write();
  DRC_LW500_npv->Write();
  DRC_dataRunB_nsv->Write();
  DRC_dataRunC_nsv ->Write();
  DRC_ZLL_nsv->Write();
  DRC_TT_nsv->Write();
  DRC_W3J_nsv->Write();
  DRC_W2J_nsv->Write();
  DRC_W1J_nsv->Write();
  ////DRC_TTZ_nsv->Write();
  ////DRC_WW_nsv->Write();
  ////DRC_WZ_nsv->Write();
  DRC_LW200_nsv->Write();
  DRC_LW300_nsv->Write();
  DRC_LW400_nsv->Write();
  DRC_LW500_nsv->Write();
  DRC_dataRunB_svd->Write();
  DRC_dataRunC_svd ->Write();
  DRC_ZLL_svd->Write();
  DRC_TT_svd->Write();
  DRC_W3J_svd->Write();
  DRC_W2J_svd->Write();
  DRC_W1J_svd->Write();
  ////DRC_TTZ_svd->Write();
  ////DRC_WW_svd->Write();
  ////DRC_WZ_svd->Write();
  DRC_LW200_svd->Write();
  DRC_LW300_svd->Write();
  DRC_LW400_svd->Write();
  DRC_LW500_svd->Write();
  DRC_dataRunB_BSd->Write();
  DRC_dataRunC_BSd ->Write();
  DRC_ZLL_BSd->Write();
  DRC_TT_BSd->Write();
  DRC_W3J_BSd->Write();
  DRC_W2J_BSd->Write();
  DRC_W1J_BSd->Write();
  //DRC_TTZ_BSd->Write();
  //DRC_WW_BSd->Write();
  //DRC_WZ_BSd->Write();
  DRC_LW200_BSd->Write();
  DRC_LW300_BSd->Write();
  DRC_LW400_BSd->Write();
  DRC_LW500_BSd->Write();
  DRC_dataRunB_BSdChi2norm->Write();
  DRC_dataRunC_BSdChi2norm ->Write();
  DRC_ZLL_BSdChi2norm->Write();
  DRC_TT_BSdChi2norm->Write();
  DRC_W3J_BSdChi2norm->Write();
  DRC_W2J_BSdChi2norm->Write();
  DRC_W1J_BSdChi2norm->Write();
  //DRC_TTZ_BSdChi2norm->Write();
  //DRC_WW_BSdChi2norm->Write();
  //DRC_WZ_BSdChi2norm->Write();
  DRC_LW200_BSdChi2norm->Write();
  DRC_LW300_BSdChi2norm->Write();
  DRC_LW400_BSdChi2norm->Write();
  DRC_LW500_BSdChi2norm->Write();
  //Histograms for signal region SG
  SG_dataRunB_ppointS->Write();
  SG_dataRunC_ppointS ->Write();
  SG_ZLL_ppointS->Write();
  SG_TT_ppointS->Write();
  SG_W3J_ppointS->Write();
  SG_W2J_ppointS->Write();
  SG_W1J_ppointS->Write();
  ////SG_TTZ_ppointS->Write();
  ////SG_WW_ppointS->Write();
  ////SG_WZ_ppointS->Write();
  SG_LW200_ppointS->Write();
  SG_LW300_ppointS->Write();
  SG_LW400_ppointS->Write();
  SG_LW500_ppointS->Write();
  SG_dataRunB_ppoint->Write();
  SG_dataRunC_ppoint ->Write();
  SG_ZLL_ppoint->Write();
  SG_TT_ppoint->Write();
  SG_W3J_ppoint->Write();
  SG_W2J_ppoint->Write();
  SG_W1J_ppoint->Write();
  ////SG_TTZ_ppoint->Write();
  ////SG_WW_ppoint->Write();
  ////SG_WZ_ppoint->Write();
  SG_LW200_ppoint->Write();
  SG_LW300_ppoint->Write();
  SG_LW400_ppoint->Write();
  SG_LW500_ppoint->Write();
  SG_dataRunB_npv->Write();
  SG_dataRunC_npv ->Write();
  SG_ZLL_npv->Write();
  SG_TT_npv->Write();
  SG_W3J_npv->Write();
  SG_W2J_npv->Write();
  SG_W1J_npv->Write();
  ////SG_TTZ_npv->Write();
  ////SG_WW_npv->Write();
  ////SG_WZ_npv->Write();
  SG_LW200_npv->Write();
  SG_LW300_npv->Write();
  SG_LW400_npv->Write();
  SG_LW500_npv->Write();
  SG_dataRunB_nsv->Write();
  SG_dataRunC_nsv ->Write();
  SG_ZLL_nsv->Write();
  SG_TT_nsv->Write();
  SG_W3J_nsv->Write();
  SG_W2J_nsv->Write();
  SG_W1J_nsv->Write();
  ////SG_TTZ_nsv->Write();
  ////SG_WW_nsv->Write();
  ////SG_WZ_nsv->Write();
  SG_LW200_nsv->Write();
  SG_LW300_nsv->Write();
  SG_LW400_nsv->Write();
  SG_LW500_nsv->Write();
  SG_dataRunB_svd->Write();
  SG_dataRunC_svd ->Write();
  SG_ZLL_svd->Write();
  SG_TT_svd->Write();
  SG_W3J_svd->Write();
  SG_W2J_svd->Write();
  SG_W1J_svd->Write();
  ////SG_TTZ_svd->Write();
  ////SG_WW_svd->Write();
  ////SG_WZ_svd->Write();
  SG_LW200_svd->Write();
  SG_LW300_svd->Write();
  SG_LW400_svd->Write();
  SG_LW500_svd->Write();
  SG_dataRunB_BSd->Write();
  SG_dataRunC_BSd ->Write();
  SG_ZLL_BSd->Write();
  SG_TT_BSd->Write();
  SG_W3J_BSd->Write();
  SG_W2J_BSd->Write();
  SG_W1J_BSd->Write();
  //SG_TTZ_BSd->Write();
  //SG_WW_BSd->Write();
  //SG_WZ_BSd->Write();
  SG_LW200_BSd->Write();
  SG_LW300_BSd->Write();
  SG_LW400_BSd->Write();
  SG_LW500_BSd->Write();
  SG_dataRunB_BSdChi2norm->Write();
  SG_dataRunC_BSdChi2norm ->Write();
  SG_ZLL_BSdChi2norm->Write();
  SG_TT_BSdChi2norm->Write();
  SG_W3J_BSdChi2norm->Write();
  SG_W2J_BSdChi2norm->Write();
  SG_W1J_BSdChi2norm->Write();
  //SG_TTZ_BSdChi2norm->Write();
  //SG_WW_BSdChi2norm->Write();
  //SG_WZ_BSdChi2norm->Write();
  SG_LW200_BSdChi2norm->Write();
  SG_LW300_BSdChi2norm->Write();
  SG_LW400_BSdChi2norm->Write();
  SG_LW500_BSdChi2norm->Write();
  //Histograms for signal region IPP
  IPP_dataRunB_ppointS->Write();
  IPP_dataRunC_ppointS ->Write();
  IPP_ZLL_ppointS->Write();
  IPP_TT_ppointS->Write();
  IPP_W3J_ppointS->Write();
  IPP_W2J_ppointS->Write();
  IPP_W1J_ppointS->Write();
  ////IPP_TTZ_ppointS->Write();
  ////IPP_WW_ppointS->Write();
  ////IPP_WZ_ppointS->Write();
  IPP_LW200_ppointS->Write();
  IPP_LW300_ppointS->Write();
  IPP_LW400_ppointS->Write();
  IPP_LW500_ppointS->Write();
  IPP_dataRunB_ppoint->Write();
  IPP_dataRunC_ppoint ->Write();
  IPP_ZLL_ppoint->Write();
  IPP_TT_ppoint->Write();
  IPP_W3J_ppoint->Write();
  IPP_W2J_ppoint->Write();
  IPP_W1J_ppoint->Write();
  ////IPP_TTZ_ppoint->Write();
  ////IPP_WW_ppoint->Write();
  ////IPP_WZ_ppoint->Write();
  IPP_LW200_ppoint->Write();
  IPP_LW300_ppoint->Write();
  IPP_LW400_ppoint->Write();
  IPP_LW500_ppoint->Write();
  IPP_dataRunB_npv->Write();
  IPP_dataRunC_npv ->Write();
  IPP_ZLL_npv->Write();
  IPP_TT_npv->Write();
  IPP_W3J_npv->Write();
  IPP_W2J_npv->Write();
  IPP_W1J_npv->Write();
  ////IPP_TTZ_npv->Write();
  ////IPP_WW_npv->Write();
  ////IPP_WZ_npv->Write();
  IPP_LW200_npv->Write();
  IPP_LW300_npv->Write();
  IPP_LW400_npv->Write();
  IPP_LW500_npv->Write();
  IPP_dataRunB_nsv->Write();
  IPP_dataRunC_nsv ->Write();
  IPP_ZLL_nsv->Write();
  IPP_TT_nsv->Write();
  IPP_W3J_nsv->Write();
  IPP_W2J_nsv->Write();
  IPP_W1J_nsv->Write();
  ////IPP_TTZ_nsv->Write();
  ////IPP_WW_nsv->Write();
  ////IPP_WZ_nsv->Write();
  IPP_LW200_nsv->Write();
  IPP_LW300_nsv->Write();
  IPP_LW400_nsv->Write();
  IPP_LW500_nsv->Write();
  IPP_dataRunB_svd->Write();
  IPP_dataRunC_svd ->Write();
  IPP_ZLL_svd->Write();
  IPP_TT_svd->Write();
  IPP_W3J_svd->Write();
  IPP_W2J_svd->Write();
  IPP_W1J_svd->Write();
  ////IPP_TTZ_svd->Write();
  ////IPP_WW_svd->Write();
  ////IPP_WZ_svd->Write();
  IPP_LW200_svd->Write();
  IPP_LW300_svd->Write();
  IPP_LW400_svd->Write();
  IPP_LW500_svd->Write();
  IPP_dataRunB_BSd->Write();
  IPP_dataRunC_BSd ->Write();
  IPP_ZLL_BSd->Write();
  IPP_TT_BSd->Write();
  IPP_W3J_BSd->Write();
  IPP_W2J_BSd->Write();
  IPP_W1J_BSd->Write();
  //IPP_TTZ_BSd->Write();
  //IPP_WW_BSd->Write();
  //IPP_WZ_BSd->Write();
  IPP_LW200_BSd->Write();
  IPP_LW300_BSd->Write();
  IPP_LW400_BSd->Write();
  IPP_LW500_BSd->Write();
  IPP_dataRunB_BSdChi2norm->Write();
  IPP_dataRunC_BSdChi2norm ->Write();
  IPP_ZLL_BSdChi2norm->Write();
  IPP_TT_BSdChi2norm->Write();
  IPP_W3J_BSdChi2norm->Write();
  IPP_W2J_BSdChi2norm->Write();
  IPP_W1J_BSdChi2norm->Write();
  //IPP_TTZ_BSdChi2norm->Write();
  //IPP_WW_BSdChi2norm->Write();
  //IPP_WZ_BSdChi2norm->Write();
  IPP_LW200_BSdChi2norm->Write();
  IPP_LW300_BSdChi2norm->Write();
  IPP_LW400_BSdChi2norm->Write();
  IPP_LW500_BSdChi2norm->Write();
  //////////////////Histograms ofr control region
  //Histograms for signal region TF
  TF_dataRunB_ppointS_cr->Write();
  TF_dataRunC_ppointS_cr->Write();
  TF_ZLL_ppointS_cr->Write();
  TF_TT_ppointS_cr->Write();
  TF_W3J_ppointS_cr->Write();
  TF_W2J_ppointS_cr->Write();
  TF_W1J_ppointS_cr->Write();
  ////TF_TTZ_ppointS_cr->Write();
  ////TF_WW_ppointS_cr->Write();
  ////TF_WZ_ppointS_cr->Write();
  TF_LW200_ppointS_cr->Write();
  TF_LW300_ppointS_cr->Write();
  TF_LW400_ppointS_cr->Write();
  TF_LW500_ppointS_cr->Write();
  TF_dataRunB_ppoint_cr->Write();
  TF_dataRunC_ppoint_cr->Write();
  TF_ZLL_ppoint_cr->Write();
  TF_TT_ppoint_cr->Write();
  TF_W3J_ppoint_cr->Write();
  TF_W2J_ppoint_cr->Write();
  TF_W1J_ppoint_cr->Write();
  ////TF_TTZ_ppoint_cr->Write();
  ////TF_WW_ppoint_cr->Write();
  ////TF_WZ_ppoint_cr->Write();
  TF_LW200_ppoint_cr->Write();
  TF_LW300_ppoint_cr->Write();
  TF_LW400_ppoint_cr->Write();
  TF_LW500_ppoint_cr->Write();
  TF_dataRunB_npv_cr->Write();
  TF_dataRunC_npv_cr->Write();
  TF_ZLL_npv_cr->Write();
  TF_TT_npv_cr->Write();
  TF_W3J_npv_cr->Write();
  TF_W2J_npv_cr->Write();
  TF_W1J_npv_cr->Write();
  ////TF_TTZ_npv_cr->Write();
  ////TF_WW_npv_cr->Write();
  ////TF_WZ_npv_cr->Write();
  TF_LW200_npv_cr->Write();
  TF_LW300_npv_cr->Write();
  TF_LW400_npv_cr->Write();
  TF_LW500_npv_cr->Write();
  TF_dataRunB_nsv_cr->Write();
  TF_dataRunC_nsv_cr->Write();
  TF_ZLL_nsv_cr->Write();
  TF_TT_nsv_cr->Write();
  TF_W3J_nsv_cr->Write();
  TF_W2J_nsv_cr->Write();
  TF_W1J_nsv_cr->Write();
  ////TF_TTZ_nsv_cr->Write();
  ////TF_WW_nsv_cr->Write();
  ////TF_WZ_nsv_cr->Write();
  TF_LW200_nsv_cr->Write();
  TF_LW300_nsv_cr->Write();
  TF_LW400_nsv_cr->Write();
  TF_LW500_nsv_cr->Write();
  TF_dataRunB_svd_cr->Write();
  TF_dataRunC_svd_cr->Write();
  TF_ZLL_svd_cr->Write();
  TF_TT_svd_cr->Write();
  TF_W3J_svd_cr->Write();
  TF_W2J_svd_cr->Write();
  TF_W1J_svd_cr->Write();
  ////TF_TTZ_svd_cr->Write();
  ////TF_WW_svd_cr->Write();
  ////TF_WZ_svd_cr->Write();
  TF_LW200_svd_cr->Write();
  TF_LW300_svd_cr->Write();
  TF_LW400_svd_cr->Write();
  TF_LW500_svd_cr->Write();
  TF_dataRunB_BSd_cr->Write();
  TF_dataRunC_BSd_cr->Write();
  TF_ZLL_BSd_cr->Write();
  TF_TT_BSd_cr->Write();
  TF_W3J_BSd_cr->Write();
  TF_W2J_BSd_cr->Write();
  TF_W1J_BSd_cr->Write();
  //TF_TTZ_BSd_cr->Write();
  //TF_WW_BSd_cr->Write();
  //TF_WZ_BSd_cr->Write();
  TF_LW200_BSd_cr->Write();
  TF_LW300_BSd_cr->Write();
  TF_LW400_BSd_cr->Write();
  TF_LW500_BSd_cr->Write();
  TF_dataRunB_BSdChi2norm_cr->Write();
  TF_dataRunC_BSdChi2norm_cr->Write();
  TF_ZLL_BSdChi2norm_cr->Write();
  TF_TT_BSdChi2norm_cr->Write();
  TF_W3J_BSdChi2norm_cr->Write();
  TF_W2J_BSdChi2norm_cr->Write();
  TF_W1J_BSdChi2norm_cr->Write();
  //TF_TTZ_BSdChi2norm_cr->Write();
  //TF_WW_BSdChi2norm_cr->Write();
  //TF_WZ_BSdChi2norm_cr->Write();
  TF_LW200_BSdChi2norm_cr->Write();
  TF_LW300_BSdChi2norm_cr->Write();
  TF_LW400_BSdChi2norm_cr->Write();
  TF_LW500_BSdChi2norm_cr->Write();
  //Histograms for signal region TO
  TO_dataRunB_ppointS_cr->Write();
  TO_dataRunC_ppointS_cr->Write();
  TO_ZLL_ppointS_cr->Write();
  TO_TT_ppointS_cr->Write();
  TO_W3J_ppointS_cr->Write();
  TO_W2J_ppointS_cr->Write();
  TO_W1J_ppointS_cr->Write();
  ////TO_TTZ_ppointS_cr->Write();
  ////TO_WW_ppointS_cr->Write();
  ////TO_WZ_ppointS_cr->Write();
  TO_LW200_ppointS_cr->Write();
  TO_LW300_ppointS_cr->Write();
  TO_LW400_ppointS_cr->Write();
  TO_LW500_ppointS_cr->Write();
  TO_dataRunB_ppoint_cr->Write();
  TO_dataRunC_ppoint_cr->Write();
  TO_ZLL_ppoint_cr->Write();
  TO_TT_ppoint_cr->Write();
  TO_W3J_ppoint_cr->Write();
  TO_W2J_ppoint_cr->Write();
  TO_W1J_ppoint_cr->Write();
  ////TO_TTZ_ppoint_cr->Write();
  ////TO_WW_ppoint_cr->Write();
  ////TO_WZ_ppoint_cr->Write();
  TO_LW200_ppoint_cr->Write();
  TO_LW300_ppoint_cr->Write();
  TO_LW400_ppoint_cr->Write();
  TO_LW500_ppoint_cr->Write();
  TO_dataRunB_npv_cr->Write();
  TO_dataRunC_npv_cr->Write();
  TO_ZLL_npv_cr->Write();
  TO_TT_npv_cr->Write();
  TO_W3J_npv_cr->Write();
  TO_W2J_npv_cr->Write();
  TO_W1J_npv_cr->Write();
  ////TO_TTZ_npv_cr->Write();
  ////TO_WW_npv_cr->Write();
  ////TO_WZ_npv_cr->Write();
  TO_LW200_npv_cr->Write();
  TO_LW300_npv_cr->Write();
  TO_LW400_npv_cr->Write();
  TO_LW500_npv_cr->Write();
  TO_dataRunB_nsv_cr->Write();
  TO_dataRunC_nsv_cr->Write();
  TO_ZLL_nsv_cr->Write();
  TO_TT_nsv_cr->Write();
  TO_W3J_nsv_cr->Write();
  TO_W2J_nsv_cr->Write();
  TO_W1J_nsv_cr->Write();
  ////TO_TTZ_nsv_cr->Write();
  ////TO_WW_nsv_cr->Write();
  ////TO_WZ_nsv_cr->Write();
  TO_LW200_nsv_cr->Write();
  TO_LW300_nsv_cr->Write();
  TO_LW400_nsv_cr->Write();
  TO_LW500_nsv_cr->Write();
  TO_dataRunB_svd_cr->Write();
  TO_dataRunC_svd_cr->Write();
  TO_ZLL_svd_cr->Write();
  TO_TT_svd_cr->Write();
  TO_W3J_svd_cr->Write();
  TO_W2J_svd_cr->Write();
  TO_W1J_svd_cr->Write();
  ////TO_TTZ_svd_cr->Write();
  ////TO_WW_svd_cr->Write();
  ////TO_WZ_svd_cr->Write();
  TO_LW200_svd_cr->Write();
  TO_LW300_svd_cr->Write();
  TO_LW400_svd_cr->Write();
  TO_LW500_svd_cr->Write();
  TO_dataRunB_BSd_cr->Write();
  TO_dataRunC_BSd_cr->Write();
  TO_ZLL_BSd_cr->Write();
  TO_TT_BSd_cr->Write();
  TO_W3J_BSd_cr->Write();
  TO_W2J_BSd_cr->Write();
  TO_W1J_BSd_cr->Write();
  //TO_TTZ_BSd_cr->Write();
  //TO_WW_BSd_cr->Write();
  //TO_WZ_BSd_cr->Write();
  TO_LW200_BSd_cr->Write();
  TO_LW300_BSd_cr->Write();
  TO_LW400_BSd_cr->Write();
  TO_LW500_BSd_cr->Write();
  TO_dataRunB_BSdChi2norm_cr->Write();
  TO_dataRunC_BSdChi2norm_cr->Write();
  TO_ZLL_BSdChi2norm_cr->Write();
  TO_TT_BSdChi2norm_cr->Write();
  TO_W3J_BSdChi2norm_cr->Write();
  TO_W2J_BSdChi2norm_cr->Write();
  TO_W1J_BSdChi2norm_cr->Write();
  //TO_TTZ_BSdChi2norm_cr->Write();
  //TO_WW_BSdChi2norm_cr->Write();
  //TO_WZ_BSdChi2norm_cr->Write();
  TO_LW200_BSdChi2norm_cr->Write();
  TO_LW300_BSdChi2norm_cr->Write();
  TO_LW400_BSdChi2norm_cr->Write();
  TO_LW500_BSdChi2norm_cr->Write();
  //Histograms for signal region HQ
  HQ_dataRunB_ppointS_cr->Write();
  HQ_dataRunC_ppointS_cr->Write();
  HQ_ZLL_ppointS_cr->Write();
  HQ_TT_ppointS_cr->Write();
  HQ_W3J_ppointS_cr->Write();
  HQ_W2J_ppointS_cr->Write();
  HQ_W1J_ppointS_cr->Write();
  ////HQ_TTZ_ppointS_cr->Write();
  ////HQ_WW_ppointS_cr->Write();
  ////HQ_WZ_ppointS_cr->Write();
  HQ_LW200_ppointS_cr->Write();
  HQ_LW300_ppointS_cr->Write();
  HQ_LW400_ppointS_cr->Write();
  HQ_LW500_ppointS_cr->Write();
  HQ_dataRunB_ppoint_cr->Write();
  HQ_dataRunC_ppoint_cr->Write();
  HQ_ZLL_ppoint_cr->Write();
  HQ_TT_ppoint_cr->Write();
  HQ_W3J_ppoint_cr->Write();
  HQ_W2J_ppoint_cr->Write();
  HQ_W1J_ppoint_cr->Write();
  ////HQ_TTZ_ppoint_cr->Write();
  ////HQ_WW_ppoint_cr->Write();
  ////HQ_WZ_ppoint_cr->Write();
  HQ_LW200_ppoint_cr->Write();
  HQ_LW300_ppoint_cr->Write();
  HQ_LW400_ppoint_cr->Write();
  HQ_LW500_ppoint_cr->Write();
  HQ_dataRunB_npv_cr->Write();
  HQ_dataRunC_npv_cr->Write();
  HQ_ZLL_npv_cr->Write();
  HQ_TT_npv_cr->Write();
  HQ_W3J_npv_cr->Write();
  HQ_W2J_npv_cr->Write();
  HQ_W1J_npv_cr->Write();
  ////HQ_TTZ_npv_cr->Write();
  ////HQ_WW_npv_cr->Write();
  ////HQ_WZ_npv_cr->Write();
  HQ_LW200_npv_cr->Write();
  HQ_LW300_npv_cr->Write();
  HQ_LW400_npv_cr->Write();
  HQ_LW500_npv_cr->Write();
  HQ_dataRunB_nsv_cr->Write();
  HQ_dataRunC_nsv_cr->Write();
  HQ_ZLL_nsv_cr->Write();
  HQ_TT_nsv_cr->Write();
  HQ_W3J_nsv_cr->Write();
  HQ_W2J_nsv_cr->Write();
  HQ_W1J_nsv_cr->Write();
  ////HQ_TTZ_nsv_cr->Write();
  ////HQ_WW_nsv_cr->Write();
  ////HQ_WZ_nsv_cr->Write();
  HQ_LW200_nsv_cr->Write();
  HQ_LW300_nsv_cr->Write();
  HQ_LW400_nsv_cr->Write();
  HQ_LW500_nsv_cr->Write();
  HQ_dataRunB_svd_cr->Write();
  HQ_dataRunC_svd_cr->Write();
  HQ_ZLL_svd_cr->Write();
  HQ_TT_svd_cr->Write();
  HQ_W3J_svd_cr->Write();
  HQ_W2J_svd_cr->Write();
  HQ_W1J_svd_cr->Write();
  ////HQ_TTZ_svd_cr->Write();
  ////HQ_WW_svd_cr->Write();
  ////HQ_WZ_svd_cr->Write();
  HQ_LW200_svd_cr->Write();
  HQ_LW300_svd_cr->Write();
  HQ_LW400_svd_cr->Write();
  HQ_LW500_svd_cr->Write();
  HQ_dataRunB_BSd_cr->Write();
  HQ_dataRunC_BSd_cr->Write();
  HQ_ZLL_BSd_cr->Write();
  HQ_TT_BSd_cr->Write();
  HQ_W3J_BSd_cr->Write();
  HQ_W2J_BSd_cr->Write();
  HQ_W1J_BSd_cr->Write();
  //HQ_TTZ_BSd_cr->Write();
  //HQ_WW_BSd_cr->Write();
  //HQ_WZ_BSd_cr->Write();
  HQ_LW200_BSd_cr->Write();
  HQ_LW300_BSd_cr->Write();
  HQ_LW400_BSd_cr->Write();
  HQ_LW500_BSd_cr->Write();
  HQ_dataRunB_BSdChi2norm_cr->Write();
  HQ_dataRunC_BSdChi2norm_cr->Write();
  HQ_ZLL_BSdChi2norm_cr->Write();
  HQ_TT_BSdChi2norm_cr->Write();
  HQ_W3J_BSdChi2norm_cr->Write();
  HQ_W2J_BSdChi2norm_cr->Write();
  HQ_W1J_BSdChi2norm_cr->Write();
  //HQ_TTZ_BSdChi2norm_cr->Write();
  //HQ_WW_BSdChi2norm_cr->Write();
  //HQ_WZ_BSdChi2norm_cr->Write();
  HQ_LW200_BSdChi2norm_cr->Write();
  HQ_LW300_BSdChi2norm_cr->Write();
  HQ_LW400_BSdChi2norm_cr->Write();
  HQ_LW500_BSdChi2norm_cr->Write();
  //Histograms for signal region JetS
  JetS_dataRunB_ppointS_cr->Write();
  JetS_dataRunC_ppointS_cr->Write();
  JetS_ZLL_ppointS_cr->Write();
  JetS_TT_ppointS_cr->Write();
  JetS_W3J_ppointS_cr->Write();
  JetS_W2J_ppointS_cr->Write();
  JetS_W1J_ppointS_cr->Write();
  ////JetS_TTZ_ppointS_cr->Write();
  ////JetS_WW_ppointS_cr->Write();
  ////JetS_WZ_ppointS_cr->Write();
  JetS_LW200_ppointS_cr->Write();
  JetS_LW300_ppointS_cr->Write();
  JetS_LW400_ppointS_cr->Write();
  JetS_LW500_ppointS_cr->Write();
  JetS_dataRunB_ppoint_cr->Write();
  JetS_dataRunC_ppoint_cr->Write();
  JetS_ZLL_ppoint_cr->Write();
  JetS_TT_ppoint_cr->Write();
  JetS_W3J_ppoint_cr->Write();
  JetS_W2J_ppoint_cr->Write();
  JetS_W1J_ppoint_cr->Write();
  ////JetS_TTZ_ppoint_cr->Write();
  ////JetS_WW_ppoint_cr->Write();
  ////JetS_WZ_ppoint_cr->Write();
  JetS_LW200_ppoint_cr->Write();
  JetS_LW300_ppoint_cr->Write();
  JetS_LW400_ppoint_cr->Write();
  JetS_LW500_ppoint_cr->Write();
  JetS_dataRunB_npv_cr->Write();
  JetS_dataRunC_npv_cr->Write();
  JetS_ZLL_npv_cr->Write();
  JetS_TT_npv_cr->Write();
  JetS_W3J_npv_cr->Write();
  JetS_W2J_npv_cr->Write();
  JetS_W1J_npv_cr->Write();
  ////JetS_TTZ_npv_cr->Write();
  ////JetS_WW_npv_cr->Write();
  ////JetS_WZ_npv_cr->Write();
  JetS_LW200_npv_cr->Write();
  JetS_LW300_npv_cr->Write();
  JetS_LW400_npv_cr->Write();
  JetS_LW500_npv_cr->Write();
  JetS_dataRunB_nsv_cr->Write();
  JetS_dataRunC_nsv_cr->Write();
  JetS_ZLL_nsv_cr->Write();
  JetS_TT_nsv_cr->Write();
  JetS_W3J_nsv_cr->Write();
  JetS_W2J_nsv_cr->Write();
  JetS_W1J_nsv_cr->Write();
  ////JetS_TTZ_nsv_cr->Write();
  ////JetS_WW_nsv_cr->Write();
  ////JetS_WZ_nsv_cr->Write();
  JetS_LW200_nsv_cr->Write();
  JetS_LW300_nsv_cr->Write();
  JetS_LW400_nsv_cr->Write();
  JetS_LW500_nsv_cr->Write();
  JetS_dataRunB_svd_cr->Write();
  JetS_dataRunC_svd_cr->Write();
  JetS_ZLL_svd_cr->Write();
  JetS_TT_svd_cr->Write();
  JetS_W3J_svd_cr->Write();
  JetS_W2J_svd_cr->Write();
  JetS_W1J_svd_cr->Write();
  ////JetS_TTZ_svd_cr->Write();
  ////JetS_WW_svd_cr->Write();
  ////JetS_WZ_svd_cr->Write();
  JetS_LW200_svd_cr->Write();
  JetS_LW300_svd_cr->Write();
  JetS_LW400_svd_cr->Write();
  JetS_LW500_svd_cr->Write();
  JetS_dataRunB_BSd_cr->Write();
  JetS_dataRunC_BSd_cr->Write();
  JetS_ZLL_BSd_cr->Write();
  JetS_TT_BSd_cr->Write();
  JetS_W3J_BSd_cr->Write();
  JetS_W2J_BSd_cr->Write();
  JetS_W1J_BSd_cr->Write();
  //JetS_TTZ_BSd_cr->Write();
  //JetS_WW_BSd_cr->Write();
  //JetS_WZ_BSd_cr->Write();
  JetS_LW200_BSd_cr->Write();
  JetS_LW300_BSd_cr->Write();
  JetS_LW400_BSd_cr->Write();
  JetS_LW500_BSd_cr->Write();
  JetS_dataRunB_BSdChi2norm_cr->Write();
  JetS_dataRunC_BSdChi2norm_cr->Write();
  JetS_ZLL_BSdChi2norm_cr->Write();
  JetS_TT_BSdChi2norm_cr->Write();
  JetS_W3J_BSdChi2norm_cr->Write();
  JetS_W2J_BSdChi2norm_cr->Write();
  JetS_W1J_BSdChi2norm_cr->Write();
  //JetS_TTZ_BSdChi2norm_cr->Write();
  //JetS_WW_BSdChi2norm_cr->Write();
  //JetS_WZ_BSdChi2norm_cr->Write();
  JetS_LW200_BSdChi2norm_cr->Write();
  JetS_LW300_BSdChi2norm_cr->Write();
  JetS_LW400_BSdChi2norm_cr->Write();
  JetS_LW500_BSdChi2norm_cr->Write();
  //Histograms for signal region DRC
  DRC_dataRunB_ppointS_cr->Write();
  DRC_dataRunC_ppointS_cr->Write();
  DRC_ZLL_ppointS_cr->Write();
  DRC_TT_ppointS_cr->Write();
  DRC_W3J_ppointS_cr->Write();
  DRC_W2J_ppointS_cr->Write();
  DRC_W1J_ppointS_cr->Write();
  ////DRC_TTZ_ppointS_cr->Write();
  ////DRC_WW_ppointS_cr->Write();
  ////DRC_WZ_ppointS_cr->Write();
  DRC_LW200_ppointS_cr->Write();
  DRC_LW300_ppointS_cr->Write();
  DRC_LW400_ppointS_cr->Write();
  DRC_LW500_ppointS_cr->Write();
  DRC_dataRunB_ppoint_cr->Write();
  DRC_dataRunC_ppoint_cr->Write();
  DRC_ZLL_ppoint_cr->Write();
  DRC_TT_ppoint_cr->Write();
  DRC_W3J_ppoint_cr->Write();
  DRC_W2J_ppoint_cr->Write();
  DRC_W1J_ppoint_cr->Write();
  ////DRC_TTZ_ppoint_cr->Write();
  ////DRC_WW_ppoint_cr->Write();
  ////DRC_WZ_ppoint_cr->Write();
  DRC_LW200_ppoint_cr->Write();
  DRC_LW300_ppoint_cr->Write();
  DRC_LW400_ppoint_cr->Write();
  DRC_LW500_ppoint_cr->Write();
  DRC_dataRunB_npv_cr->Write();
  DRC_dataRunC_npv_cr->Write();
  DRC_ZLL_npv_cr->Write();
  DRC_TT_npv_cr->Write();
  DRC_W3J_npv_cr->Write();
  DRC_W2J_npv_cr->Write();
  DRC_W1J_npv_cr->Write();
  ////DRC_TTZ_npv_cr->Write();
  ////DRC_WW_npv_cr->Write();
  ////DRC_WZ_npv_cr->Write();
  DRC_LW200_npv_cr->Write();
  DRC_LW300_npv_cr->Write();
  DRC_LW400_npv_cr->Write();
  DRC_LW500_npv_cr->Write();
  DRC_dataRunB_nsv_cr->Write();
  DRC_dataRunC_nsv_cr->Write();
  DRC_ZLL_nsv_cr->Write();
  DRC_TT_nsv_cr->Write();
  DRC_W3J_nsv_cr->Write();
  DRC_W2J_nsv_cr->Write();
  DRC_W1J_nsv_cr->Write();
  ////DRC_TTZ_nsv_cr->Write();
  ////DRC_WW_nsv_cr->Write();
  ////DRC_WZ_nsv_cr->Write();
  DRC_LW200_nsv_cr->Write();
  DRC_LW300_nsv_cr->Write();
  DRC_LW400_nsv_cr->Write();
  DRC_LW500_nsv_cr->Write();
  DRC_dataRunB_svd_cr->Write();
  DRC_dataRunC_svd_cr->Write();
  DRC_ZLL_svd_cr->Write();
  DRC_TT_svd_cr->Write();
  DRC_W3J_svd_cr->Write();
  DRC_W2J_svd_cr->Write();
  DRC_W1J_svd_cr->Write();
  ////DRC_TTZ_svd_cr->Write();
  ////DRC_WW_svd_cr->Write();
  ////DRC_WZ_svd_cr->Write();
  DRC_LW200_svd_cr->Write();
  DRC_LW300_svd_cr->Write();
  DRC_LW400_svd_cr->Write();
  DRC_LW500_svd_cr->Write();
  DRC_dataRunB_BSd_cr->Write();
  DRC_dataRunC_BSd_cr->Write();
  DRC_ZLL_BSd_cr->Write();
  DRC_TT_BSd_cr->Write();
  DRC_W3J_BSd_cr->Write();
  DRC_W2J_BSd_cr->Write();
  DRC_W1J_BSd_cr->Write();
  //DRC_TTZ_BSd_cr->Write();
  //DRC_WW_BSd_cr->Write();
  //DRC_WZ_BSd_cr->Write();
  DRC_LW200_BSd_cr->Write();
  DRC_LW300_BSd_cr->Write();
  DRC_LW400_BSd_cr->Write();
  DRC_LW500_BSd_cr->Write();
  DRC_dataRunB_BSdChi2norm_cr->Write();
  DRC_dataRunC_BSdChi2norm_cr->Write();
  DRC_ZLL_BSdChi2norm_cr->Write();
  DRC_TT_BSdChi2norm_cr->Write();
  DRC_W3J_BSdChi2norm_cr->Write();
  DRC_W2J_BSdChi2norm_cr->Write();
  DRC_W1J_BSdChi2norm_cr->Write();
  //DRC_TTZ_BSdChi2norm_cr->Write();
  //DRC_WW_BSdChi2norm_cr->Write();
  //DRC_WZ_BSdChi2norm_cr->Write();
  DRC_LW200_BSdChi2norm_cr->Write();
  DRC_LW300_BSdChi2norm_cr->Write();
  DRC_LW400_BSdChi2norm_cr->Write();
  DRC_LW500_BSdChi2norm_cr->Write();
  //Histograms for signal region SG
  SG_dataRunB_ppointS_cr->Write();
  SG_dataRunC_ppointS_cr->Write();
  SG_ZLL_ppointS_cr->Write();
  SG_TT_ppointS_cr->Write();
  SG_W3J_ppointS_cr->Write();
  SG_W2J_ppointS_cr->Write();
  SG_W1J_ppointS_cr->Write();
  ////SG_TTZ_ppointS_cr->Write();
  ////SG_WW_ppointS_cr->Write();
  ////SG_WZ_ppointS_cr->Write();
  SG_LW200_ppointS_cr->Write();
  SG_LW300_ppointS_cr->Write();
  SG_LW400_ppointS_cr->Write();
  SG_LW500_ppointS_cr->Write();
  SG_dataRunB_ppoint_cr->Write();
  SG_dataRunC_ppoint_cr->Write();
  SG_ZLL_ppoint_cr->Write();
  SG_TT_ppoint_cr->Write();
  SG_W3J_ppoint_cr->Write();
  SG_W2J_ppoint_cr->Write();
  SG_W1J_ppoint_cr->Write();
  ////SG_TTZ_ppoint_cr->Write();
  ////SG_WW_ppoint_cr->Write();
  ////SG_WZ_ppoint_cr->Write();
  SG_LW200_ppoint_cr->Write();
  SG_LW300_ppoint_cr->Write();
  SG_LW400_ppoint_cr->Write();
  SG_LW500_ppoint_cr->Write();
  SG_dataRunB_npv_cr->Write();
  SG_dataRunC_npv_cr->Write();
  SG_ZLL_npv_cr->Write();
  SG_TT_npv_cr->Write();
  SG_W3J_npv_cr->Write();
  SG_W2J_npv_cr->Write();
  SG_W1J_npv_cr->Write();
  ////SG_TTZ_npv_cr->Write();
  ////SG_WW_npv_cr->Write();
  ////SG_WZ_npv_cr->Write();
  SG_LW200_npv_cr->Write();
  SG_LW300_npv_cr->Write();
  SG_LW400_npv_cr->Write();
  SG_LW500_npv_cr->Write();
  SG_dataRunB_nsv_cr->Write();
  SG_dataRunC_nsv_cr->Write();
  SG_ZLL_nsv_cr->Write();
  SG_TT_nsv_cr->Write();
  SG_W3J_nsv_cr->Write();
  SG_W2J_nsv_cr->Write();
  SG_W1J_nsv_cr->Write();
  ////SG_TTZ_nsv_cr->Write();
  ////SG_WW_nsv_cr->Write();
  ////SG_WZ_nsv_cr->Write();
  SG_LW200_nsv_cr->Write();
  SG_LW300_nsv_cr->Write();
  SG_LW400_nsv_cr->Write();
  SG_LW500_nsv_cr->Write();
  SG_dataRunB_svd_cr->Write();
  SG_dataRunC_svd_cr->Write();
  SG_ZLL_svd_cr->Write();
  SG_TT_svd_cr->Write();
  SG_W3J_svd_cr->Write();
  SG_W2J_svd_cr->Write();
  SG_W1J_svd_cr->Write();
  ////SG_TTZ_svd_cr->Write();
  ////SG_WW_svd_cr->Write();
  ////SG_WZ_svd_cr->Write();
  SG_LW200_svd_cr->Write();
  SG_LW300_svd_cr->Write();
  SG_LW400_svd_cr->Write();
  SG_LW500_svd_cr->Write();
  SG_dataRunB_BSd_cr->Write();
  SG_dataRunC_BSd_cr->Write();
  SG_ZLL_BSd_cr->Write();
  SG_TT_BSd_cr->Write();
  SG_W3J_BSd_cr->Write();
  SG_W2J_BSd_cr->Write();
  SG_W1J_BSd_cr->Write();
  //SG_TTZ_BSd_cr->Write();
  //SG_WW_BSd_cr->Write();
  //SG_WZ_BSd_cr->Write();
  SG_LW200_BSd_cr->Write();
  SG_LW300_BSd_cr->Write();
  SG_LW400_BSd_cr->Write();
  SG_LW500_BSd_cr->Write();
  SG_dataRunB_BSdChi2norm_cr->Write();
  SG_dataRunC_BSdChi2norm_cr->Write();
  SG_ZLL_BSdChi2norm_cr->Write();
  SG_TT_BSdChi2norm_cr->Write();
  SG_W3J_BSdChi2norm_cr->Write();
  SG_W2J_BSdChi2norm_cr->Write();
  SG_W1J_BSdChi2norm_cr->Write();
  //SG_TTZ_BSdChi2norm_cr->Write();
  //SG_WW_BSdChi2norm_cr->Write();
  //SG_WZ_BSdChi2norm_cr->Write();
  SG_LW200_BSdChi2norm_cr->Write();
  SG_LW300_BSdChi2norm_cr->Write();
  SG_LW400_BSdChi2norm_cr->Write();
  SG_LW500_BSdChi2norm_cr->Write();
  //Histograms for signal region IPP
  IPP_dataRunB_ppointS_cr->Write();
  IPP_dataRunC_ppointS_cr->Write();
  IPP_ZLL_ppointS_cr->Write();
  IPP_TT_ppointS_cr->Write();
  IPP_W3J_ppointS_cr->Write();
  IPP_W2J_ppointS_cr->Write();
  IPP_W1J_ppointS_cr->Write();
  ////IPP_TTZ_ppointS_cr->Write();
  ////IPP_WW_ppointS_cr->Write();
  ////IPP_WZ_ppointS_cr->Write();
  IPP_LW200_ppointS_cr->Write();
  IPP_LW300_ppointS_cr->Write();
  IPP_LW400_ppointS_cr->Write();
  IPP_LW500_ppointS_cr->Write();
  IPP_dataRunB_ppoint_cr->Write();
  IPP_dataRunC_ppoint_cr->Write();
  IPP_ZLL_ppoint_cr->Write();
  IPP_TT_ppoint_cr->Write();
  IPP_W3J_ppoint_cr->Write();
  IPP_W2J_ppoint_cr->Write();
  IPP_W1J_ppoint_cr->Write();
  ////IPP_TTZ_ppoint_cr->Write();
  ////IPP_WW_ppoint_cr->Write();
  ////IPP_WZ_ppoint_cr->Write();
  IPP_LW200_ppoint_cr->Write();
  IPP_LW300_ppoint_cr->Write();
  IPP_LW400_ppoint_cr->Write();
  IPP_LW500_ppoint_cr->Write();
  IPP_dataRunB_npv_cr->Write();
  IPP_dataRunC_npv_cr->Write();
  IPP_ZLL_npv_cr->Write();
  IPP_TT_npv_cr->Write();
  IPP_W3J_npv_cr->Write();
  IPP_W2J_npv_cr->Write();
  IPP_W1J_npv_cr->Write();
  ////IPP_TTZ_npv_cr->Write();
  ////IPP_WW_npv_cr->Write();
  ////IPP_WZ_npv_cr->Write();
  IPP_LW200_npv_cr->Write();
  IPP_LW300_npv_cr->Write();
  IPP_LW400_npv_cr->Write();
  IPP_LW500_npv_cr->Write();
  IPP_dataRunB_nsv_cr->Write();
  IPP_dataRunC_nsv_cr->Write();
  IPP_ZLL_nsv_cr->Write();
  IPP_TT_nsv_cr->Write();
  IPP_W3J_nsv_cr->Write();
  IPP_W2J_nsv_cr->Write();
  IPP_W1J_nsv_cr->Write();
  ////IPP_TTZ_nsv_cr->Write();
  ////IPP_WW_nsv_cr->Write();
  ////IPP_WZ_nsv_cr->Write();
  IPP_LW200_nsv_cr->Write();
  IPP_LW300_nsv_cr->Write();
  IPP_LW400_nsv_cr->Write();
  IPP_LW500_nsv_cr->Write();
  IPP_dataRunB_svd_cr->Write();
  IPP_dataRunC_svd_cr->Write();
  IPP_ZLL_svd_cr->Write();
  IPP_TT_svd_cr->Write();
  IPP_W3J_svd_cr->Write();
  IPP_W2J_svd_cr->Write();
  IPP_W1J_svd_cr->Write();
  ////IPP_TTZ_svd_cr->Write();
  ////IPP_WW_svd_cr->Write();
  ////IPP_WZ_svd_cr->Write();
  IPP_LW200_svd_cr->Write();
  IPP_LW300_svd_cr->Write();
  IPP_LW400_svd_cr->Write();
  IPP_LW500_svd_cr->Write();
  IPP_dataRunB_BSd_cr->Write();
  IPP_dataRunC_BSd_cr->Write();
  IPP_ZLL_BSd_cr->Write();
  IPP_TT_BSd_cr->Write();
  IPP_W3J_BSd_cr->Write();
  IPP_W2J_BSd_cr->Write();
  IPP_W1J_BSd_cr->Write();
  //IPP_TTZ_BSd_cr->Write();
  //IPP_WW_BSd_cr->Write();
  //IPP_WZ_BSd_cr->Write();
  IPP_LW200_BSd_cr->Write();
  IPP_LW300_BSd_cr->Write();
  IPP_LW400_BSd_cr->Write();
  IPP_LW500_BSd_cr->Write();
  IPP_dataRunB_BSdChi2norm_cr->Write();
  IPP_dataRunC_BSdChi2norm_cr->Write();
  IPP_ZLL_BSdChi2norm_cr->Write();
  IPP_TT_BSdChi2norm_cr->Write();
  IPP_W3J_BSdChi2norm_cr->Write();
  IPP_W2J_BSdChi2norm_cr->Write();
  IPP_W1J_BSdChi2norm_cr->Write();
  //IPP_TTZ_BSdChi2norm_cr->Write();
  //IPP_WW_BSdChi2norm_cr->Write();
  //IPP_WZ_BSdChi2norm_cr->Write();
  IPP_LW200_BSdChi2norm_cr->Write();
  IPP_LW300_BSdChi2norm_cr->Write();
  IPP_LW400_BSdChi2norm_cr->Write();
  IPP_LW500_BSdChi2norm_cr->Write();

  hfile->Close();


  return 0;

}
