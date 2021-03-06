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
// g++ -std=c++11 -g -O3 -Wall -Wextra -o SecvecAnalysisLW200 SecvecAnalysisLW200.cxx $(root-config --cflags --libs)
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


bool sortbysec(const pair<float,float> &a,
              const pair<float,float> &b)
{
    return (a.second < b.second);
}


/*
 * Base path to local filesystem or to EOS containing the datasets
 */
//const std::string samplesBasePath = "root://eospublic.cern.ch//eos/opendata/cms/upload/od-workshop/ws2021/";
TH1F* LW200electron_num = new TH1F("LW200electron_num","number of events with elec/phot pt>20GeV",10,0,10);
TH1F* LW200electron_pt = new TH1F("LW200electron_pt","Electrons pt for missing trigg",100,0,200);
TH1F* LW200electron_eta = new TH1F("LW200electron_eta","Electrons eta for missing trigg",100,-5,5);
TH1F* LW200photon_num = new TH1F("Photon_number","Number of photons pt>17GeV",10,0,10);
TH1F* LW200photon_pt = new TH1F("Photon_pt","Photon transverse momentum pt>17GeV",100,0,200);
TH1F* LW200photon_eta = new TH1F("Photon_eta","Photon pseudorapidity pt>17GeV",100,-5,5);
TH1F* LW200SGenele_num = new TH1F("LW200SGenele_num","Number of signal gen-electrons per event (pt<15GeV)",3,0,3);
TH1F* LW200SGenele_pt = new TH1F("LW200SGenele_pt","Signal Genele pt ",100,0,200);
TH1F* LW200SGenele_eta = new TH1F("LW200SGenele_eta","Signal Genele eta",100,-5,5);
TH1F* LW200Genphot_num = new TH1F("Genphot_num","Number of gen-photon pt>17GeV",50,0,100);
TH1F* LW200Genphot_pt = new TH1F("Genphot_pt","Gen-photon transverse momentumpt pt>17GeV",100,0,200);
TH1F* LW200Genphot_eta = new TH1F("Genphot_eta","Gen-photon pseudorapidity pt>17GeV",100,-5,5);
TH1F* LW200Genelec_num = new TH1F("LW200Genelec_num","number of gen-electrons",50,0,100);
TH1F* LW200Genelec_pt = new TH1F("LW200Genelec_pt","Genelec pt",100,0,200);
TH1F* LW200Genelec_eta = new TH1F("LW200Genelec_eta","Genelec eta",100,-5,5);
TH1F* LW200GenWdau_pt = new TH1F("LW200GenWdau_pt","GensWdau pt for missing trigg",100,0,200);
TH1F* LW200GenWdau_eta = new TH1F("LW200GenWdau_eta","GensWdau eta for missing trigg",100,-5,5);
TH1F* LW200Helec_num = new TH1F("High_electron_number","Number of Second most energetic electron pt>15GeV",3,0,3);
TH1F* LW200Helec_pt = new TH1F("High_electron_pt","Second most energetic electron transverse momentum pt>15GeV",100,0,200);
TH1F* LW200Helec_eta = new TH1F("High_electron_eta","Second most energetic electron pseudorapidity pt>15GeV",100,-5,5);
TH1F* LW200Track_num = new TH1F("Tracks_number","Number of tracks pt>15GeV",50,0,100);
TH1F* LW200Track_pt = new TH1F("Tracks_pt","Tracks transverse momentum pt>15GeV",100,0,200);
TH1F* LW200Track_eta = new TH1F("Tracks_eta","Tracks pseudorapidity pt>15GeV",100,-5,5);
TH1F* LW200Htrk_num = new TH1F("High_track_number","Number of Second most energetic track pt>15GeV",3,0,3);
TH1F* LW200Htrk_pt = new TH1F("High_track_pt","Second most energetic track transverse momentum pt>15GeV",100,0,200);
TH1F* LW200Htrk_eta = new TH1F("High_track_eta","Second most energetic track pseudorapidity pt>15GeV",100,-5,5);
TH1F* LW200jet_mass = new TH1F("LW200DiJet_Invmass","Invariant mass from DiJets ",800,0,400);
TH1F* LW200LW_mass = new TH1F("LW200LW_Invmass","Invariant mass from LW",800,0,400);
TH1F* LW200Corrjet_mass = new TH1F("LW200DiCorrJet_Invmass","Invariant mass from corrected DiJets ",800,0,400);
TH1F* LW200Sjet_mass = new TH1F("LW200SDiJet_Invmass","Invariant mass from Signal DiJets ",800,0,400);
TH1F* LW200Genjet_mass = new TH1F("LW200GenDiJet_Invmass","Invariant mass from Gen DiJets ",800,0,400);
TH1F* LW200RecoEle_mass = new TH1F("LW200RecoDiEle_Invmass","Invariant mass from Reco DiElec",800,0,400);
TH1F* LW200jet_massfilter = new TH1F("LW200DiJet_Invmass_filter","Events with DiJets invariant mass ",2,0,2);
TH1F* LW200Sjet_massfilter = new TH1F("LW200SDiJet_Invmass_filter","Events with Signal DiJets invariant mass ",2,0,2);
TH1F* LW200Genjet_massfilter = new TH1F("LW200DiGenJet_Invmass_filter","Events with Gen DiJets invariant mass ",2,0,2);
TH1F* LW200Wdau_deltaR = new TH1F("LW200Wdau_deltaR","DeltaR for Z daughters",201,0,20);

TH1F* LW200jet_pt = new TH1F("LW200jet_pt","Jet pt distribution;Pt[GeV];",100,0,200);
TH1F* LW200jet_eta = new TH1F("LW200jet_eta","Jet pseudorapidity",100,-5,5);
TH1F* LW200GenZdau_pt = new TH1F("LW200GenZdau_pt","Zdaugthers pt distribution;transversal momentum[GeV];",100,0,200);
TH1F* LW200RecoZdau_pt = new TH1F("LW200recoZdau_pt","Zdaugthers matched jets pt distribution;transversal momentum[GeV];",100,0,200);
TH1F* LW200RecoZdau_corr_pt = new TH1F("LW200recoZdau_corr_pt","Zdaugthers matched jets corrected pt distribution;transversal momentum[GeV];",100,0,200);
TH1F* LW200Genjet_eta = new TH1F("LW200Genjet_eta","Gen Jet pseudorapidity",100,-5,5);
TH1F* LW2004Jets_pt = new TH1F("LW2004Jets_pt","4 most energetic jets pt;Transversal Momentum[GeV];",100,0,200);
TH1F* LW2004GenJets_pt = new TH1F("LW2004GenJets_pt","4 most energetic matched gen jets pt;Transversal Momentum[GeV];",100,0,200);
TH1F* LW2004CorrJets_pt = new TH1F("LW2004CorrJets_pt","4 most energetic jets correccted pt;Transversal Momentum[GeV];",100,0,200);
TH1F* LW2004Jets_eta = new TH1F("LW2004Jets_eta","4 most energetic jets eta;Pseudorapidity;",100,-5,5);

TH1F* LW200W_jet_pt = new TH1F("LW200W_jet_pt","Jet pt distribution AR;Pt[GeV];",100,0,200);
TH1F* LW200W_jet_eta = new TH1F("LW200W_jet_eta","Jet pseudorapidity AR;pseudorapidity",100,-5,5);
TH1F* LW200W_GenZdau_pt = new TH1F("LW200W_GenZdau_pt","Zdaugthers pt distribution  AR;transversal momentum[GeV];",100,0,200);
TH1F* LW200W_RecoZdau_pt = new TH1F("LW200W_recoZdau_pt","Zdaugthers matched jets pt distribution AR;transversal momentum[GeV];",100,0,200);
TH1F* LW200W_RecoZdau_corr_pt = new TH1F("LW200W_recoZdau_corr_pt","Zdaugthers matched jets corrected pt distribution AR;transversal momentum[GeV];",100,0,200);
TH1F* LW200W_Genjet_eta = new TH1F("LW200W_Genjet_eta","Gen Jet pseudorapidity AR;pseudorapidity",100,-5,5);
TH1F* LW200W_4Jets_pt = new TH1F("LW200W_4Jets_pt","4 most energetic jets pt AR;Transversal Momentum[GeV];",100,0,200);
TH1F* LW200W_4GenJets_pt = new TH1F("LW200W_4GenJets_pt","4 most energetic matched gen jets pt AR;Transversal Momentum[GeV];",100,0,200);
TH1F* LW200W_4CorrJets_pt = new TH1F("LW200W_4CorrJets_pt","4 most energetic jets correccted pt AR;Transversal Momentum[GeV];",100,0,200);
TH1F* LW200W_4Jets_eta = new TH1F("LW200W_4Jets_eta","4 most energetic jets eta;Pseudorapidity AR;pseudorapidity;",100,-5,5);


TH1F* LW2004Jets_DR = new TH1F("LW2004Jets_DR","4 most energetic jets deltaR;DeltaR;",100,0,5);
TH1F* LW200EleJet_DR1 = new TH1F("LW200EleJet_DR1","Electron DR 1 to the closest energetic jet DeltaR;DeltaR;",100,0,3);
TH1F* LW200EleJet_DR2 = new TH1F("LW200EleJet_DR2","Electron DR 2 to the closest energetic jet DeltaR;DeltaR;",100,0,3);
TH1F* LW200EleJet_DRdiff = new TH1F("LW200EleJet_DRdiff","Electron DR diff to the closest energetic jet DeltaR;DeltaR;",100,0,3);
TH1F* LW200Gen_EleJet_DR1 = new TH1F("LW200Gen_EleJet_DR1","Electron DR 1 to the closest energetic jet Gen DeltaR;DeltaR;",100,0,3);
TH1F* LW200Gen_EleJet_DR2 = new TH1F("LW200Gen_EleJet_DR2","Electron DR 2 to the closest energetic jet Gen DeltaR;DeltaR;",100,0,3);
TH1F* LW200Gen_EleJet_DRdiff = new TH1F("LW200Gen_EleJet_DRdiff","Electron DR diff to the closest energetic jet Gen DeltaR;DeltaR;",100,0,3);
TH1F* LW200DiJet_DR = new TH1F("LW200DiJet_DR","Pair of most energetic jets DR;DeltaR;",100,0,100);

TH1F* LW200SecVec_bydist = new TH1F("LW200SecVec_bydist","Most energetic electron secondary vertex by distance;diatance[mm];",100,0,0.2);
TH1F* LW200SecVec_bysigma = new TH1F("LW200SecVec_bysigma","Most energetic electron secondary vertex by uncertainty;diatance[mm];",100,0,0.2);
TH1F* LW200SecVec_Gen = new TH1F("LW200SecVec_Gen","Most energetic gen-electron;diatance[mm];",100,0,0.2);
TH1F* LW200SecVec_dist = new TH1F("LW200SecVec_dist","Secvec displacement distribution;diatance[mm];",100,0,0.2);
TH1F* LW200SecVec_sigma = new TH1F("LW200SecVec_sigma","Secvec sigma distribution;diatance[mm];",100,0,0.01);
TH1F* LW200SecVec_MatchEle_dist = new TH1F("LW200SecVec_MatchEle_dist","Secvec for match Gen electron displacement;diatance[mm];",100,0,0.2);
TH1F* LW200SecVec_Chi2 = new TH1F("LW200SecVec_Chi2","Secvec chi2;Chi2;",100,0,5);

TH1F* LW200Esecvec_bydist = new TH1F("LW200Esecvec_bydist","Most energetic electron secondary vertex by distance;diatance[mm];",100,0,0.2);
TH1F* LW200Esecvec_bysigma = new TH1F("LW200Esecvec_bysigma","Most energetic electron secondary vertex by uncertainty;diatance[mm];",100,0,0.2);
TH1F* LW200Esecvec_Gen = new TH1F("LW200Esecvec_Gen","Most energetic gen-electron;diatance[mm];",100,0,0.2);
TH1F* LW200Esecvec_dist = new TH1F("LW200Esecvec_dist","Secvec displacement distribution;diatance[mm];",100,0,0.2);
TH1F* LW200Esecvec_sigma = new TH1F("LW200Esecvec_sigma","Secvec sigma distribution;diatance[mm];",100,0,0.01);
TH1F* LW200Esecvec_MatchEle_dist = new TH1F("LW200EsecvecMatchEle_dist","Secvec for match Gen electron displacement;diatance[mm];",100,0,0.2);
TH1F* LW200Esecvec_Chi2 = new TH1F("LW200Esecvec_Chi2","Secvec chi2;Chi2;",100,0,5);

TH1F* LW200GenZ_pt = new TH1F("LW200GenZ_pt","Generated Z bosons pt;Transversal momentum[GeV];",100,0,200);
TH1F* LW200GenLW_pt = new TH1F("LW200GenLW_pt","Generated LW electron pt;Transversal momentum[GeV];",100,0,300);
TH1F* LW200GenZ_ele_dR = new TH1F("LW200GenZ_ele_dR","Generated Z-Ele DeltaR;DeltaR;",100,0,5);
TH1F* LW200LW_dR = new TH1F("LW200LW_dR","LW-LW deltaR;DeltaR;",100,0,25);
TH1F* LW200GenZ_dR = new TH1F("LW200GenZ_dR","Generated Z-Z DeltaR;DeltaR;",100,0,25);
TH1F* LW200GenZ_LW_dR = new TH1F("LW200GenZ_LW_dR","Generated Z-LW DeltaR;DeltaR;",100,0,5);
TH2F* LW200BJet_GenJet_pt = new TH2F("LW200BJet_GenJet_pt","Most energetic Jet vs Matched Gen jet pt;Reco_pt[GeV];Gen_pt[GeV]",100,0,600,100,0,600);
TH2F* LW200BJet_GenJet_corr_pt = new TH2F("LW200BJet_GenJet_corr_pt","Most energetic Jet vs Matched Gen jet corrected pt;Reco_corr_pt[GeV];Gen_pt[GeV]",100,0,600,100,0,600);
////////////////strange region for bad fitted Jets
TH1F* LW200W_GenZ_pt = new TH1F("LW200W_GenZ_pt","Generated Z bosons pt AR;Transversal momentum[GeV];",100,0,200);
TH1F* LW200W_GenLW_pt = new TH1F("LW200W_GenLW_pt","Generated LW electron pt AR;Transversal momentum[GeV];",100,0,300);
TH1F* LW200W_GenZ_ele_dR = new TH1F("LW200W_GenZ_ele_dR","Generated Z-Ele DeltaR AR;DeltaR;",100,0,5);
TH1F* LW200W_LW_dR = new TH1F("LW200W_LW_dR","LW-LW deltaR AR;DeltaR;",100,0,25);
TH1F* LW200W_GenZ_dR = new TH1F("LW200W_GenZ_dR","Generated Z-Z DeltaR AR;DeltaR;",100,0,25);
TH1F* LW200W_GenZ_LW_dR = new TH1F("LW200W_GenZ_LW_dR","Generated Z-LW DeltaR AR;DeltaR;",100,0,5);
TH2F* LW200W_BJet_GenJet_pt = new TH2F("LW200W_BJet_GenJet_pt","Most energetic Jet vs Matched Gen jet pt AR;Reco_pt[GeV];Gen_pt[GeV]",100,0,600,100,0,600);
TH2F* LW200W_BJet_GenJet_corr_pt = new TH2F("LW200W_BJet_GenJet_corr_pt","Most energetic Jet vs Matched Gen jet corrected pt AR;Reco_corr_pt[GeV];Gen_pt[GeV]",100,0,600,100,0,600);
TH1F* LW200W_GenJet_GenEle_DR = new TH1F("LW200W_GenJet_GenEle_DR","DeltaR between genjet and electron AR;DeltaR;",100,0,25);
TH1F* LW200GenJet_GenEle_DR = new TH1F("LW200GenJet_GenEle_DR","DeltaR between genjet and electron;DeltaR;",100,0,25);
TH1F* LW200W_NConst = new TH1F("LW200W_NConst","Jet Number of constituents AR;#;",100,0,25);
TH1F* LW200NConst = new TH1F("LW200NConst","Jet Number of constituents;#;",100,0,25);
TH1F* LW200W_ChargedEMF = new TH1F("LW200W_ChargedEMF","Jet Charged Electromagnetic Fraction AR;#;",100,0,1);
TH1F* LW200ChargedEMF = new TH1F("LW200ChargedEMF","Jet Charged Electromagnetic Fraction;#;",100,0,1);
TH1F* LW200W_NeutralEMF = new TH1F("LW200W_NeutralEMF","Jet Neutral Electromagnetic Fraction AR;#;",100,0,1);
TH1F* LW200NeutralEMF = new TH1F("LW200NeutralEMF","Jet Neutral Electromagnetic Fraction;#;",100,0,1);

TH1F* LW200EleZdauDR = new TH1F("LW200EleZdauDR","Electron Zdau DR;DeltaR;",100,0,25);
TH1F* LW200EleSZdauDR = new TH1F("LW200EleSZdauDR","Electron Selected Zdau DR;DeltaR;",100,0,25);
TH1F* LW200EleBZdauDR = new TH1F("LW200EleBZdauDR","Electron closest Selected Zdau DR;DeltaR;",100,0,25);
TH1F* LW200ZdauSZdauDR = new TH1F("LW200ZdauSZdauDR","Zdau Selected Zdau DR;DeltaR;",100,0,25);
TH1F* LW200EleNSZdauDR = new TH1F("LW200EleNSZdauDR","Electron Non Selected Zdau DR;DeltaR;",100,0,25);
TH1F* LW200EleZdauPT = new TH1F("LW200EleZdauPT","Electron Zdau Total momentum;Momentum[GeV];",100,0,400);
TH1F* LW200EleSZdauPT = new TH1F("LW200EleSZdauPT","Electron Signal Zdau Total momentum;Momentum[GeV];",100,0,400);
TH1F* LW200EleSZdau_ptdiff = new TH1F("LW200EleSZdau_ptdiff","Electron Signal Zdau Pt diff;Momentum[GeV];",100,0,0.01);
TH1F* LW200ZdauInvmass = new TH1F("LW200ZdauInvmass","Zdau Invariant mass;InvariantMass[GeV];",100,0,200);
TH1F* LW200ZdauCharge = new TH1F("LW200ZdauCharge","Zdau Charge;Charge[e+];",200,-100,100);
TH1F* LW200RecoZdauInvmass = new TH1F("LW200RecoZdauInvmass","Reco Zdau Invariant mass;InvariantMass[GeV];",100,0,200);
TH1F* LW200RecoZdauEleInvmass = new TH1F("LW200RecoZdauEleInvmass","Reco Zdau plus Reco Electron Invariant mass;InvariantMass[GeV];",100,0,500);
TH1F* LW200RecoZdauCharge = new TH1F("LW200RecoZdauCharge","Reco Zdau Charge;Charge[e+];",20,-10,10);

TH1F* LW200EleDijet_Ppoint = new TH1F("LW200EleDijet_Ppoint","Electron dijet total momentum Secondary vertex point;Ppoint[GeV*mm];",100,-100,100);
TH1F* LW200EleDijet_PpointS = new TH1F("LW200EleDijet_PpointS","Electron dijet total momentum Secondary vertex point sign;Ppoint sign;",100,-2,2);
TH1F* LW200EleJetInvM_Ppoint = new TH1F("LW200EleJetInvM_Ppoint","Electron Jet total momentum Secondary vertex point;Ppoint[GeV*mm];",100,-100,100);
TH1F* LW200EleJetInvM_PpointS = new TH1F("LW200EleJetInvM_PpointS","Electron Jet total momentum Secondary vertex point sign;Ppoint sign;",100,-2,2);
TH1F* LW200SecVec_Ppoint = new TH1F("LW200SecVec_Ppoint","Secondary vertex total momentum Secondary vertex point;Ppoint[GeV*mm];",100,-100,100);
TH1F* LW200SecVec_PpointS = new TH1F("LW200SecVec_PpointS","Secondary vertex total momentum Secondary vertex point sign;Ppoint sign;",100,-2,2);
TH1F* LW200GenSecVec_Ppoint = new TH1F("LW200GenSecVec_Ppoint","Gen Secondary vertex total momentum Secondary vertex point;Ppoint[GeV*mm];",100,-100,100);
TH1F* LW200GenSecVec_PpointS = new TH1F("LW200GenSecVec_PpointS","Gen Secondary vertex total momentum Secondary vertex point sign;Ppoint sign;",100,-2,2);
TH1F* LW200SecVec_EleJet_Ppoint = new TH1F("LW200SecVec_EleJet_Ppoint","Secondary vertex matched jet total momentum Secondary vertex point;Ppoint[GeV*mm];",100,-100,100);
TH1F* LW200SecVec_EleJet_PpointS = new TH1F("LW200SecVec_EleJet_PpointS","Secondary vertex matched jet total momentum Secondary vertex point sign;Ppoint sign;",100,-2,2);

TH1F* LW200Zdau_GenjetMatch = new TH1F("LW200Zdau_GenjetMatch","Zdau is Matched in a jet;Boolean;",2,0,2);
TH1F* LW200Zdau_BjetMatch = new TH1F("LW200Zdau_BjetMatch","Zdau is matched in the most energetic jet;Boolean;",2,0,2);
TH1F* LW200Zdau_SBjetMatch = new TH1F("LW200Zdau_SBjetMatch","Zdau is matched in a second most energetic jet;Boolean;",2,0,2);
TH1F* LW200Zdau_3jetMatch = new TH1F("LW200Zdau_3jetMatch","Zdau is matched in a third most energetic jet;Boolean;",2,0,2);
TH1F* LW200Zdau_4jetMatch = new TH1F("LW200Zdau_4jetMatch","Zdau is matched in a Fourth most energetic jet;Boolean;",2,0,2);

TH1F* LW200BZdau_GenjetMatch = new TH1F("LW200BZdau_GenjetMatch","Most energetic Zdau is Matched in a jet;Boolean;",2,0,2);
TH1F* LW200BZdau_BjetMatch = new TH1F("LW200BZdau_BjetMatch","Most energetic Zdau is matched in the most energetic jet;Boolean;",2,0,2);
TH1F* LW200BZdau_SBjetMatch = new TH1F("LW200BZdau_SBjetMatch","Most energetic Zdau is matched in a second most energetic jet;Boolean;",2,0,2);
TH1F* LW200BZdau_3jetMatch = new TH1F("LW200BZdau_3jetMatch","Most energetic Zdau is matched in a third most energetic jet;Boolean;",2,0,2);
TH1F* LW200BZdau_4jetMatch = new TH1F("LW200BZdau_4jetMatch","Most energetic Zdau is matched in a Fourth most energetic jet;Boolean;",2,0,2);

TH1F* LW200Elec_GenElecMatch = new TH1F("LW200Elec_GenElecMatch","GenElectron is Matched in a RecoElectron;Boolean;",2,0,2);
TH1F* LW200Elec_BElecMatch = new TH1F("LW200Elec_BElecMatch","GenElectron is matched in the most energetic RecoElectron;Boolean;",2,0,2);
TH1F* LW200Elec_SBElecMatch = new TH1F("LW200Elec_SBElecMatch","GenElectron is matched in the second most energetic RecoElectron;Boolean;",2,0,2);

TH1F* LW200BElec_GenElecMatch = new TH1F("LW200BElec_GenElecMatch","Most energetic GenElectron is Matched in a RecoElectron;Boolean;",2,0,2);
TH1F* LW200BElec_BElecMatch = new TH1F("LW200BElec_BElecMatch","Most energetic GenElectron is matched in the most energetic RecoElectron;Boolean;",2,0,2);
TH1F* LW200BElec_SBElecMatch = new TH1F("LW200BElec_SBElecMatch","Most energetic GenElectron is matched in the second most energetic RecoElectron;Boolean;",2,0,2);

TH1F* LW200SBElec_GenElecMatch = new TH1F("LW200SBElec_GenElecMatch","Second most energetic GenElectron is Matched in a RecoElectron;Boolean;",2,0,2);
TH1F* LW200SBElec_BElecMatch = new TH1F("LW200SBElec_BElecMatch","Second most energetic GenElectron is matched in the most energetic RecoElectron;Boolean;",2,0,2);
TH1F* LW200SBElec_SBElecMatch = new TH1F("LW200SBElec_SBElecMatch","Second most energetic GenElectron is matched in the second most energetic RecoElectron;Boolean;",2,0,2);
TH1F* LW200SBElec_3ElecMatch = new TH1F("LW200SBElec_3ElecMatch","Second most energetic GenElectron is matched in the third most energetic RecoElectron;Boolean;",2,0,2);
TH1F* LW200SBElec_4ElecMatch = new TH1F("LW200SBElec_4ElecMatch","Second most energetic GenElectron is matched in the fourth most energetic RecoElectron;Boolean;",2,0,2);

TH1F* LW200Secvec_jet = new TH1F("LW200Secvec_jet","Secvec jet pt differece to Reco Zdau;TrAnsversal momentum difference[GeV];",100,0,200);
TH1F* LW200Electron_ZdauCand_DR = new TH1F("LW200Electron_ZdauCand_DR","Electron Zdau candidates dR;DeltaR;",100,0,25);
TH1F* LW200Electron_ZdauCand_Count = new TH1F("LW200Electron_ZdauCand_Count","Electron Zdau candidates per electron;#Zcandidates;",100,0,25);
TH1F* LW200Electron_ZdauCand_InvMass = new TH1F("LW200Electron_ZdauCand_InvMass","Electron Zdau candidates invariant mass;InvMass[GeV];",100,0,500);
TH1F* LW200BElectron_ZdauCand_DR = new TH1F("LW200BElectron_ZdauCand_DR","Most energetic electron Zdau candidates dR;DeltaR;",100,0,25);
TH1F* LW200BElectron_ZdauCand_Count = new TH1F("LW200BElectron_ZdauCand_Count","Most energetic electron Zdau candidates per electron;#Zcandidates;",100,0,25);
TH1F* LW200BElectron_ZdauCand_InvMass = new TH1F("LW200BElectron_ZdauCand_InvMass","Most energetic electron Zdau candidates invariant mass;InvMass[GeV];",100,0,500);
TH1F* LW200Electron_ZdauCand_RecoZdauMatch = new TH1F("LW200Electron_ZdauCand_RecoZdauMatch","Electron Zdau candidates is match;InvMass[GeV];",3,0,3);
TH1F* LW200BElectron_ZdauCand_RecoZdauMatch = new TH1F("LW200BElectron_ZdauCand_RecoZdauMatch","Most energetic electron Zdau candidates is match;InvMass[GeV];",3,0,3);

TH1F* LW200JetZdau_IP = new TH1F("LW200JetZdau_IP","Zdau impact parameter to secvec;Impact parameter[mm];",100,0,1);


const std::string samplesBasePath = "";


//book example histograms for specific variables
//copy them in the constructor if you add more
const int nhists = 17;
const float Minpt = 15;
const float MinZm = -1000;
const float MaxZm = 1000;

//Histograms for signal region


//Requiered trigger
string triggerRequest[] = {"HLT_Photon26_Photon18"};

// Fixed size dimensions of array or collections stored in the TTree if any.


class EventLoopAnalysisTemplate {
public :

  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  TTree          *tevents;
  TTree          *ttrigger;
  TTree          *telectrons;
  TTree          *tphotons;
  TTree          *tGenPart;
  TTree          *tTrack;
  TTree          *tJet;
  TTree          *tVertex;


  Int_t           fCurrent; //!current Tree number in a TChain
  TString          labeltag;
  TString         filename;
  Float_t          theweight;
  Long64_t         Triggcount;

  //array to keep histograms to be written and easily loop over them
  TH1F            *hists[nhists];

  // Declaration of example leaf types
  Int_t           run;
  UInt_t          luminosityBlock;
  ULong64_t	      event;
  std::map<std::string, int> *triggermap;
  vector<float>   *electron_pt;
  vector<float>   *electron_e;
  vector<float>   *electron_px;
  vector<float>   *electron_py;
  vector<float>   *electron_pz;
  vector<float>   *electron_eta;
  vector<float>   *electron_phi;
  vector<float>   *genelec_pt;
  vector<float>   *genelec_DRscore;
  vector<float>   *track_pt;
  vector<float>   *track_eta;
  vector<float>   *track_chi2;
  vector<float>   *jet_mass;
  vector<float>   *jet_e;
  vector<float>   *jet_pt;
  vector<float>   *corr_jet_pt;
  vector<float>   *jet_pz;
  vector<float>   *jet_px;
  vector<float>   *jet_py;
  vector<float>   *jet_phi;
  vector<float>   *jet_eta;
  vector<float>   *jet_ch;
  vector<float>   *genjet_e;
  vector<float>   *genjet_pt;
  vector<float>   *genjet_pz;
  vector<float>   *genjet_px;
  vector<float>   *genjet_py;
  vector<float>   *genjet_eta;
  vector<float>   *genjet_phi;
  vector<float>   *genjet_DRscore;
  vector<float>   *NConstituents;
  vector<float>   *NeutralHF;
  vector<float>   *NeutralEMF;
  vector<float>   *MuonF;
  vector<float>   *ChargedEMF;
  vector<float>   *ChargedHF;
  vector<float>   *ChargedMult;
  vector<float>   *photon_pt;
  vector<float>   *photon_eta;
  vector<float>   *GenPart_pt;
  vector<float>   *GenPart_px;
  vector<float>   *GenPart_py;
  vector<float>   *GenPart_pz;
  vector<float>   *GenPart_vx;
  vector<float>   *GenPart_vy;
  vector<float>   *GenPart_vz;
  vector<float>   *GenPart_eta;
  vector<float>   *GenPart_phi;
  vector<float>   *GenPart_mass;
  vector<float>   *GenPart_pdgId;
  vector<float>   *GenPart_mompdgId;
  vector<float>   *GenDau_pt;
  vector<float>   *GenDau_px;
  vector<float>   *GenDau_py;
  vector<float>   *GenDau_pz;
  vector<float>   *GenDau_mass;
  vector<float>   *GenDau_eta;
  vector<float>   *GenDau_phi;
  vector<float>   *GenDau_pdgId;
  vector<float>   *GenDau_mompdgId;
  /*vector<float>   *electron_Bsecvec;
  vector<float>   *secvec_deltaR;
  vector<float>   *secvec_disp;*/
  vector<float>   *secvec_posx;
  vector<float>   *secvec_posy;
  vector<float>   *secvec_posz;
  vector<float>   *secvec_poserrorx;
  vector<float>   *secvec_poserrory;
  vector<float>   *secvec_poserrorz;
  vector<float>   *secvec_px;
  vector<float>   *secvec_py;
  vector<float>   *secvec_pz;
  vector<float>   *secvec_eleTag;
  vector<float>   *secvec_normchi2;
  vector<float>   *Esecvec_posx;
  vector<float>   *Esecvec_posy;
  vector<float>   *Esecvec_posz;
  vector<float>   *Esecvec_poserrorx;
  vector<float>   *Esecvec_poserrory;
  vector<float>   *Esecvec_poserrorz;
  vector<float>   *Esecvec_eleTag;
  vector<float>   *Esecvec_normchi2;
  vector<float>   *PV_x;
  vector<float>   *PV_y;
  vector<float>   *PV_z;
  vector<float>   *Bsp_x;
  vector<float>   *Bsp_y;
  vector<float>   *Bsp_z;
  vector<float> *secvec_jet_px;
  vector<float> *secvec_jet_py;
  vector<float> *secvec_jet_pz;
  vector<float> *secvec_jet_pt1;
  vector<float> *secvec_jet_eta1;
  vector<float> *secvec_jet_phi1;
  vector<float> *secvec_jet_pt2;
  vector<float> *secvec_jet_eta2;
  vector<float> *secvec_jet_phi2;
  vector<float> *secvec_jet_d1;
  vector<float> *secvec_jet_d2;
  vector<float> *secvec_jet_eleTag;


  TBranch        *b_run;   //!
  TBranch        *b_luminosityBlock;   //!
  TBranch        *b_event;   //!
  TBranch        *b_triggermap;   //!
  TBranch        *b_electron_pt;
  TBranch        *b_electron_e;
  TBranch        *b_electron_px;
  TBranch        *b_electron_py;
  TBranch        *b_electron_pz;
  TBranch        *b_electron_eta;
  TBranch        *b_electron_phi;
  TBranch        *b_genelec_pt;
  TBranch        *b_genelec_DRscore;
  TBranch        *b_track_pt;
  TBranch        *b_track_eta;
  TBranch        *b_track_chi2;
  TBranch        *b_jet_mass;
  TBranch        *b_jet_e;
  TBranch        *b_jet_pt;
  TBranch        *b_corr_jet_pt;
  TBranch        *b_jet_pz;
  TBranch        *b_jet_px;
  TBranch        *b_jet_py;
  TBranch        *b_jet_phi;
  TBranch        *b_jet_eta;
  TBranch        *b_jet_ch;
  TBranch        *b_genjet_e;
  TBranch        *b_genjet_pt;
  TBranch        *b_genjet_pz;
  TBranch        *b_genjet_px;
  TBranch        *b_genjet_py;
  TBranch        *b_genjet_eta;
  TBranch        *b_genjet_phi;
  TBranch        *b_genjet_DRscore;
  TBranch        *b_NConstituents;
  TBranch        *b_NeutralHF;
  TBranch        *b_NeutralEMF;
  TBranch        *b_MuonF;
  TBranch        *b_ChargedEMF;
  TBranch        *b_ChargedHF;
  TBranch        *b_ChargedMult;
  TBranch        *b_photon_pt;
  TBranch        *b_photon_eta;
  TBranch        *b_GenPart_pt;
  TBranch        *b_GenPart_px;
  TBranch        *b_GenPart_py;
  TBranch        *b_GenPart_pz;
  TBranch        *b_GenPart_vx;
  TBranch        *b_GenPart_vy;
  TBranch        *b_GenPart_vz;
  TBranch        *b_GenPart_eta;
  TBranch        *b_GenPart_phi;
  TBranch        *b_GenPart_mass;
  TBranch        *b_GenPart_pdgId;
  TBranch        *b_GenPart_mompdgId;
  TBranch        *b_GenDau_pt;
  TBranch        *b_GenDau_px;
  TBranch        *b_GenDau_py;
  TBranch        *b_GenDau_pz;
  TBranch        *b_GenDau_mass;
  TBranch        *b_GenDau_eta;
  TBranch        *b_GenDau_phi;
  TBranch        *b_GenDau_pdgId;
  TBranch        *b_GenDau_mompdgId;
  /*TBranch        *b_electron_Bsecvec;
  TBranch        *b_secvec_deltaR;
  TBranch        *b_secvec_disp;*/
  TBranch    *b_secvec_posx;
  TBranch    *b_secvec_posy;
  TBranch    *b_secvec_posz;
  TBranch    *b_secvec_px;
  TBranch    *b_secvec_py;
  TBranch    *b_secvec_pz;
  TBranch    *b_secvec_poserrorx;
  TBranch    *b_secvec_poserrory;
  TBranch    *b_secvec_poserrorz;
  TBranch    *b_secvec_eleTag;
  TBranch    *b_secvec_normchi2;
  TBranch    *b_Esecvec_posx;
  TBranch    *b_Esecvec_posy;
  TBranch    *b_Esecvec_posz;
  TBranch    *b_Esecvec_poserrorx;
  TBranch    *b_Esecvec_poserrory;
  TBranch    *b_Esecvec_poserrorz;
  TBranch    *b_Esecvec_eleTag;
  TBranch    *b_Esecvec_normchi2;
  TBranch    *b_PV_x;
  TBranch    *b_PV_y;
  TBranch    *b_PV_z;
  TBranch    *b_Bsp_x;
  TBranch    *b_Bsp_y;
  TBranch    *b_Bsp_z;
  TBranch *b_secvec_jet_px;
  TBranch *b_secvec_jet_py;
  TBranch *b_secvec_jet_pz;
  TBranch *b_secvec_jet_pt1;
  TBranch *b_secvec_jet_eta1;
  TBranch *b_secvec_jet_phi1;
  TBranch *b_secvec_jet_pt2;
  TBranch *b_secvec_jet_eta2;
  TBranch *b_secvec_jet_phi2;
  TBranch *b_secvec_jet_d1;
  TBranch *b_secvec_jet_d2;
  TBranch *b_secvec_jet_eleTag;



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
  bool MinimalSelection();

};



EventLoopAnalysisTemplate::EventLoopAnalysisTemplate(TString thefile, TString thelabel, Float_t sampleweight) : fChain(0)
{
  //Prepare some info for the object:
  filename = thefile;
  labeltag = thelabel;
  theweight = sampleweight;

  hists[0]=LW200electron_num;
  hists[1]=LW200electron_pt;
  hists[2]=LW200electron_eta;
  hists[3]=LW200photon_num;
  hists[4]=LW200photon_pt;
  hists[5]=LW200photon_eta;
  hists[6]=LW200SGenele_num;
  hists[7]=LW200SGenele_pt;
  hists[8]=LW200SGenele_eta;
  hists[9]=LW200Genphot_num;
  hists[10]=LW200Genphot_pt;
  hists[11]=LW200Genphot_eta;
  hists[12]=LW200GenWdau_pt;
  hists[13]=LW200GenWdau_eta;
  hists[14]=LW200Genelec_num;
  hists[15]=LW200Genelec_pt;
  hists[16]=LW200Genelec_eta;

// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   TTree* tree = 0;
   TFile *f = TFile::Open(filename);
   //trigger should go first as it is the more complicated one
   tree = (TTree*)f->Get("mytriggers/Events");
   //Get trees for friendship
   tevents = (TTree*)f->Get("myevents/Events");
   telectrons = (TTree*)f->Get("myelectrons/Events");
   tphotons = (TTree*)f->Get("myphotons/Events");
   tGenPart = (TTree*)f->Get("mygenparticle/Events");
   tTrack = (TTree*)f->Get("mytracks/Events");
   tJet = (TTree*)f->Get("myjets/Events");
   tVertex = (TTree*)f->Get("mypvertex/Events");
   //Make friends so we can have access to friends variables
   //we may not use all of the available information
   //it is just an example
   tree->AddFriend(tevents);
   tree->AddFriend(telectrons);
   tree->AddFriend(tphotons);
   tree->AddFriend(tGenPart);
   tree->AddFriend(tTrack);
   tree->AddFriend(tJet);
   tree->AddFriend(tVertex);
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
   electron_pt=0;
   electron_e=0;
   electron_px=0;
   electron_py=0;
   electron_pz=0;
   electron_eta=0;
   electron_phi=0;
   genelec_pt=0;
   genelec_DRscore=0;
   jet_mass=0;
   jet_e=0;
   jet_pt=0;
   corr_jet_pt=0;
   jet_pz=0;
   jet_px=0;
   jet_py=0;
   jet_phi=0;
   jet_eta=0;
   jet_ch=0;
   genjet_e=0;
   genjet_pt=0;
   genjet_pz=0;
   genjet_px=0;
   genjet_py=0;
   genjet_eta=0;
   genjet_phi=0;
   genjet_DRscore=0;
   NConstituents = 0;
   NeutralHF = 0;
   NeutralEMF = 0;
   MuonF = 0;
   ChargedEMF = 0;
   ChargedHF = 0;
   ChargedMult = 0;
   track_pt=0;
   track_eta=0;
   track_chi2=0;
   photon_pt=0;
   photon_eta=0;
   GenPart_pt=0;
   GenPart_px=0;
   GenPart_py=0;
   GenPart_pz=0;
   GenPart_vx=0;
   GenPart_vy=0;
   GenPart_vz=0;
   GenPart_eta=0;
   GenPart_phi=0;
   GenPart_mass=0;
   GenPart_pdgId=0;
   GenPart_mompdgId=0;
   GenDau_pt=0;
   GenDau_px=0;
   GenDau_py=0;
   GenDau_pz=0;
   GenDau_mass=0;
   GenDau_eta=0;
   GenDau_phi=0;
   GenDau_pdgId=0;
   GenDau_mompdgId=0;
   /*electron_Bsecvec=0;
   secvec_deltaR=0;
   secvec_disp=0;*/
   secvec_posx=0;
   secvec_posy=0;
   secvec_posz=0;
   secvec_px=0;
   secvec_py=0;
   secvec_pz=0;
   secvec_poserrorx=0;
   secvec_poserrory=0;
   secvec_poserrorz=0;
   secvec_eleTag=0;
   secvec_normchi2=0;
   Esecvec_posx=0;
   Esecvec_posy=0;
   Esecvec_posz=0;
   Esecvec_poserrorx=0;
   Esecvec_poserrory=0;
   Esecvec_poserrorz=0;
   Esecvec_eleTag=0;
   Esecvec_normchi2=0;
   PV_x=0;
   PV_y=0;
   PV_z=0;
   Bsp_x=0;
   Bsp_y=0;
   Bsp_z=0;
   secvec_jet_px=0;
   secvec_jet_py=0;
   secvec_jet_pz=0;
   secvec_jet_pt1=0;
   secvec_jet_eta1=0;
   secvec_jet_phi1=0;
   secvec_jet_pt2=0;
   secvec_jet_eta2=0;
   secvec_jet_phi2=0;
   secvec_jet_d1=0;
   secvec_jet_d2=0;
   secvec_jet_eleTag=0;

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
   fChain->SetBranchAddress("triggermap",&triggermap,&b_triggermap);
   fChain->SetBranchAddress("electron_pt",&electron_pt,&b_electron_pt);
   fChain->SetBranchAddress("electron_e",&electron_e,&b_electron_e);
   fChain->SetBranchAddress("electron_px",&electron_px,&b_electron_px);
   fChain->SetBranchAddress("electron_py",&electron_py,&b_electron_py);
   fChain->SetBranchAddress("electron_pz",&electron_pz,&b_electron_pz);
   fChain->SetBranchAddress("electron_eta",&electron_eta,&b_electron_eta);
   fChain->SetBranchAddress("electron_phi",&electron_phi,&b_electron_phi);
   fChain->SetBranchAddress("genelec_pt",&genelec_pt,&b_genelec_pt);
   fChain->SetBranchAddress("genelec_DRscore",&genelec_DRscore,&b_genelec_DRscore);
   fChain->SetBranchAddress("photon_pt",&photon_pt,&b_photon_pt);
   fChain->SetBranchAddress("photon_eta",&photon_eta,&b_photon_eta);
   fChain->SetBranchAddress("GenPart_pt",&GenPart_pt,&b_GenPart_pt);
   fChain->SetBranchAddress("GenPart_px",&GenPart_px,&b_GenPart_px);
   fChain->SetBranchAddress("GenPart_py",&GenPart_py,&b_GenPart_py);
   fChain->SetBranchAddress("GenPart_pz",&GenPart_pz,&b_GenPart_pz);
   fChain->SetBranchAddress("GenPart_vx",&GenPart_vx,&b_GenPart_vx);
   fChain->SetBranchAddress("GenPart_vy",&GenPart_vy,&b_GenPart_vy);
   fChain->SetBranchAddress("GenPart_vz",&GenPart_vz,&b_GenPart_vz);
   fChain->SetBranchAddress("GenPart_eta",&GenPart_eta,&b_GenPart_eta);
   fChain->SetBranchAddress("GenPart_phi",&GenPart_phi,&b_GenPart_phi);
   fChain->SetBranchAddress("GenPart_mass",&GenPart_mass,&b_GenPart_mass);
   fChain->SetBranchAddress("GenPart_pdgId",&GenPart_pdgId,&b_GenPart_pdgId);
   fChain->SetBranchAddress("GenPart_mompdgId",&GenPart_mompdgId,&b_GenPart_mompdgId);
   fChain->SetBranchAddress("GenDau_pt",&GenDau_pt,&b_GenDau_pt);
   fChain->SetBranchAddress("GenDau_px",&GenDau_px,&b_GenDau_px);
   fChain->SetBranchAddress("GenDau_py",&GenDau_py,&b_GenDau_py);
   fChain->SetBranchAddress("GenDau_pz",&GenDau_pz,&b_GenDau_pz);
   fChain->SetBranchAddress("GenDau_mass",&GenDau_mass,&b_GenDau_mass);
   fChain->SetBranchAddress("GenDau_eta",&GenDau_eta,&b_GenDau_eta);
   fChain->SetBranchAddress("GenDau_phi",&GenDau_phi,&b_GenDau_phi);
   fChain->SetBranchAddress("GenDau_pdgId",&GenDau_pdgId,&b_GenDau_pdgId);
   fChain->SetBranchAddress("GenDau_mompdgId",&GenDau_mompdgId,&b_GenDau_mompdgId);
   fChain->SetBranchAddress("track_pt",&track_pt,&b_track_pt);
   fChain->SetBranchAddress("track_eta",&track_eta,&b_track_eta);
   fChain->SetBranchAddress("track_chi2",&track_chi2,&b_track_chi2);
   fChain->SetBranchAddress("jet_mass",&jet_mass,&b_jet_mass);
   fChain->SetBranchAddress("jet_e",&jet_e,&b_jet_e);
   fChain->SetBranchAddress("jet_pt",&jet_pt,&b_jet_pt);
   fChain->SetBranchAddress("corr_jet_pt",&corr_jet_pt,&b_corr_jet_pt);
   fChain->SetBranchAddress("jet_pz",&jet_pz,&b_jet_pz);
   fChain->SetBranchAddress("jet_px",&jet_px,&b_jet_px);
   fChain->SetBranchAddress("jet_py",&jet_py,&b_jet_py);
   fChain->SetBranchAddress("jet_phi",&jet_phi,&b_jet_phi);
   fChain->SetBranchAddress("jet_eta",&jet_eta,&b_jet_eta);
   fChain->SetBranchAddress("jet_ch",&jet_ch,&b_jet_ch);
   fChain->SetBranchAddress("genjet_e",&genjet_e,&b_genjet_e);
   fChain->SetBranchAddress("genjet_pt",&genjet_pt,&b_genjet_pt);
   fChain->SetBranchAddress("genjet_pz",&genjet_pz,&b_genjet_pz);
   fChain->SetBranchAddress("genjet_px",&genjet_px,&b_genjet_px);
   fChain->SetBranchAddress("genjet_py",&genjet_py,&b_genjet_py);
   fChain->SetBranchAddress("genjet_eta",&genjet_eta,&b_genjet_eta);
   fChain->SetBranchAddress("genjet_phi",&genjet_phi,&b_genjet_phi);
   fChain->SetBranchAddress("genjet_DRscore",&genjet_DRscore,&b_genjet_DRscore);
   fChain->SetBranchAddress("NConstituents",&NConstituents,&b_NConstituents);
   fChain->SetBranchAddress("NeutralHF",&NeutralHF,&b_NeutralHF);
   fChain->SetBranchAddress("NeutralEMF",&NeutralEMF,&b_NeutralEMF);
   fChain->SetBranchAddress("MuonF",&MuonF,&b_MuonF);
   fChain->SetBranchAddress("ChargedEMF",&ChargedEMF,&b_ChargedEMF);
   fChain->SetBranchAddress("ChargedHF",&ChargedHF,&b_ChargedHF);
   fChain->SetBranchAddress("ChargedMult",&ChargedMult,&b_ChargedMult);
   /*fChain->SetBranchAddress("electron_Bsecvec",&electron_Bsecvec,&b_electron_Bsecvec);
   fChain->SetBranchAddress("secvec_deltaR",&secvec_deltaR,&b_secvec_deltaR);
   fChain->SetBranchAddress("secvec_disp",&secvec_disp,&b_secvec_disp);*/
   fChain->SetBranchAddress("secvec_posx",&secvec_posx,&b_secvec_posx);
   fChain->SetBranchAddress("secvec_posy",&secvec_posy,&b_secvec_posy);
   fChain->SetBranchAddress("secvec_posz",&secvec_posz,&b_secvec_posz);
   fChain->SetBranchAddress("secvec_px",&secvec_px,&b_secvec_px);
   fChain->SetBranchAddress("secvec_py",&secvec_py,&b_secvec_py);
   fChain->SetBranchAddress("secvec_pz",&secvec_pz,&b_secvec_pz);
   fChain->SetBranchAddress("secvec_poserrorx",&secvec_poserrorx,&b_secvec_poserrorx);
   fChain->SetBranchAddress("secvec_poserrory",&secvec_poserrory,&b_secvec_poserrory);
   fChain->SetBranchAddress("secvec_poserrorz",&secvec_poserrorz,&b_secvec_poserrorz);
   fChain->SetBranchAddress("secvec_eleTag",&secvec_eleTag,&b_secvec_eleTag);
   fChain->SetBranchAddress("secvec_normchi2",&secvec_normchi2,&b_secvec_normchi2);
   fChain->SetBranchAddress("Esecvec_posx",&Esecvec_posx,&b_Esecvec_posx);
   fChain->SetBranchAddress("Esecvec_posy",&Esecvec_posy,&b_Esecvec_posy);
   fChain->SetBranchAddress("Esecvec_posz",&Esecvec_posz,&b_Esecvec_posz);
   fChain->SetBranchAddress("Esecvec_poserrorx",&Esecvec_poserrorx,&b_Esecvec_poserrorx);
   fChain->SetBranchAddress("Esecvec_poserrory",&Esecvec_poserrory,&b_Esecvec_poserrory);
   fChain->SetBranchAddress("Esecvec_poserrorz",&Esecvec_poserrorz,&b_Esecvec_poserrorz);
   fChain->SetBranchAddress("Esecvec_eleTag",&Esecvec_eleTag,&b_Esecvec_eleTag);
   fChain->SetBranchAddress("Esecvec_normchi2",&Esecvec_normchi2,&b_Esecvec_normchi2);
   fChain->SetBranchAddress("PV_x",&PV_x,&b_PV_x);
   fChain->SetBranchAddress("PV_y",&PV_y,&b_PV_y);
   fChain->SetBranchAddress("PV_z",&PV_z,&b_PV_z);
   fChain->SetBranchAddress("Bsp_x",&Bsp_x,&b_Bsp_x);
   fChain->SetBranchAddress("Bsp_y",&Bsp_y,&b_Bsp_y);
   fChain->SetBranchAddress("Bsp_z",&Bsp_z,&b_Bsp_z);
   fChain->SetBranchAddress("secvec_jet_px",&secvec_jet_px,&b_secvec_jet_px);
   fChain->SetBranchAddress("secvec_jet_py",&secvec_jet_py,&b_secvec_jet_py);
   fChain->SetBranchAddress("secvec_jet_pz",&secvec_jet_pz,&b_secvec_jet_pz);
   fChain->SetBranchAddress("secvec_jet_pt1",&secvec_jet_pt1,&b_secvec_jet_pt1);
   fChain->SetBranchAddress("secvec_jet_eta1",&secvec_jet_eta1,&b_secvec_jet_eta1);
   fChain->SetBranchAddress("secvec_jet_phi1",&secvec_jet_phi1,&b_secvec_jet_phi1);
   fChain->SetBranchAddress("secvec_jet_pt2",&secvec_jet_pt2,&b_secvec_jet_pt2);
   fChain->SetBranchAddress("secvec_jet_eta2",&secvec_jet_eta2,&b_secvec_jet_eta2);
   fChain->SetBranchAddress("secvec_jet_phi2",&secvec_jet_phi2,&b_secvec_jet_phi2);
   fChain->SetBranchAddress("secvec_jet_d1",&secvec_jet_d1,&b_secvec_jet_d1);
   fChain->SetBranchAddress("secvec_jet_d2",&secvec_jet_d2,&b_secvec_jet_d2);
   fChain->SetBranchAddress("secvec_jet_eleTag",&secvec_jet_eleTag,&b_secvec_jet_eleTag);


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

  Long64_t Elecount=0;
  Triggcount=0;

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //Just an informative printout
    if(jentry%10000 == 0) {
      cout<<"Processed "<<jentry<<" events out of "<<nentries<<endl;
    }
    if(electron_pt->size()==0)Elecount++;//cout<<"Load the current event "<<jentry<<" 0 ele"<<'\n';
    if(electron_pt->size()==1)Elecount++;//cout<<"Load the current event "<<jentry<<" 1 ele"<<'\n';
    Long64_t ientry = LoadTree(jentry);
    //cout<<ientry<<endl;
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    analysis();

  }
  cout<<"Number Ele "<<Elecount<<endl;
  cout<<"Triggcount "<<Triggcount<<endl;


}


//-----------------------------------------------------------------
void EventLoopAnalysisTemplate::analysis()
{

  /////Jet pt info
  for(size_t x=0; x<jet_pt->size();x++){
    LW200jet_pt->Fill(jet_pt->at(x));
    LW200jet_eta->Fill(jet_eta->at(x));
    if(ChargedEMF->at(x)<0.6){
      LW200W_jet_pt->Fill(jet_pt->at(x));
      LW200W_jet_eta->Fill(jet_eta->at(x));
    }
  }
  for(size_t x=0; x<GenDau_pt->size();x++){
    if(GenDau_mompdgId->at(x)==23){
      LW200GenZdau_pt->Fill(GenDau_pt->at(x));
      LW200Genjet_eta->Fill(GenDau_eta->at(x));

      for(size_t y=0; y<corr_jet_pt->size(); y++){
        if(genjet_DRscore->at(y)<0.5 && genjet_pt->at(y)==GenDau_pt->at(x)){
          LW200RecoZdau_pt->Fill(jet_pt->at(y));
          LW200RecoZdau_corr_pt->Fill(corr_jet_pt->at(y));
          if(ChargedEMF->at(y)<0.6){
            LW200W_GenZdau_pt->Fill(GenDau_pt->at(x));
            LW200W_Genjet_eta->Fill(GenDau_eta->at(x));
            LW200W_RecoZdau_pt->Fill(jet_pt->at(y));
            LW200W_RecoZdau_corr_pt->Fill(corr_jet_pt->at(y));
          }
          /*for(size_t k=0; k<secvec_jet_eta1->size();k++){
            if(secvec_jet_px->at(k)!=-1 ){
              if(jet_pt->at(y)-secvec_jet_pt1->at(k)==0){
                LW200Secvec_jet->Fill(jet_pt->at(y)-secvec_jet_pt1->at(k));
              }
              if(jet_pt->at(y)-secvec_jet_pt2->at(k)==0){
                LW200Secvec_jet->Fill(jet_pt->at(y)-secvec_jet_pt2->at(k));
              }
            }
          }*/
        }
      }
    }
  }





  if(!isFill)cout<<"Aqui"<<'\n';



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

float EventLoopAnalysisTemplate::deltaR(float eta1, float phi1, float eta2, float phi2) {
  float deta = eta1 - eta2;
  float dphi = std::abs(phi1 - phi2);
  if (dphi > 3.14159)
    dphi -= (2 * 3.14159);
  return deta * deta + dphi * dphi;
}




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


  map<string, pair<string,float> > sampleNames;
  sampleNames.insert(make_pair("LWSM200DnR",make_pair("LW200",1)));




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

  TFile* hfile = new TFile("FiltterAnalysisLW200.root","RECREATE");

  //Save signal region histos
  LW200electron_num->Write();
  LW200electron_pt->Write();
  LW200electron_eta->Write();
  LW200photon_num->Write();
  LW200photon_pt->Write();
  LW200photon_eta->Write();
  LW200SGenele_num->Write();
  LW200SGenele_pt->Write();
  LW200SGenele_eta->Write();
  LW200Genphot_num->Write();
  LW200Genphot_pt->Write();
  LW200Genphot_eta->Write();
  LW200GenWdau_pt->Write();
  LW200GenWdau_eta->Write();
  LW200Genelec_num->Write();
  LW200Genelec_pt->Write();
  LW200Genelec_eta->Write();
  LW200Helec_pt->Write();
  LW200Helec_eta->Write();
  LW200Helec_num->Write();
  LW200Track_pt->Write();
  LW200Track_eta->Write();
  LW200Track_num->Write();
  LW200Htrk_pt->Write();
  LW200Htrk_eta->Write();
  LW200Htrk_num->Write();
  LW200jet_mass->Write();
  LW200Corrjet_mass->Write();
  LW200Sjet_mass->Write();
  LW200Genjet_mass->Write();
  LW200jet_massfilter->Write();
  LW200Sjet_massfilter->Write();
  LW200Genjet_massfilter->Write();
  LW200LW_mass->Write();
  LW200RecoEle_mass->Write();
  LW200Wdau_deltaR->Write();

  LW200jet_pt->Write();
  LW200jet_eta->Write();
  LW200GenZdau_pt->Write();
  LW200RecoZdau_pt->Write();
  LW200RecoZdau_corr_pt->Write();
  LW200Genjet_eta->Write();
  LW2004Jets_DR->Write();
  LW2004Jets_pt->Write();
  LW2004GenJets_pt->Write();
  LW2004CorrJets_pt->Write();
  LW2004Jets_eta->Write();

  LW200W_jet_pt->Write();
  LW200W_jet_eta->Write();
  LW200W_GenZdau_pt->Write();
  LW200W_RecoZdau_pt->Write();
  LW200W_RecoZdau_corr_pt->Write();
  LW200W_Genjet_eta->Write();
  LW200W_4Jets_pt->Write();
  LW200W_4GenJets_pt->Write();
  LW200W_4CorrJets_pt->Write();
  LW200W_4Jets_eta->Write();

  LW200EleJet_DR1->Write();
  LW200EleJet_DR2->Write();
  LW200EleJet_DRdiff->Write();
  LW200Gen_EleJet_DR1->Write();
  LW200Gen_EleJet_DR2->Write();
  LW200Gen_EleJet_DRdiff->Write();
  LW200DiJet_DR->Write();
  LW200SecVec_dist->Write();
  LW200SecVec_sigma->Write();
  LW200SecVec_Chi2->Write();
  LW200SecVec_MatchEle_dist->Write();
  LW200SecVec_bydist->Write();
  LW200SecVec_bysigma->Write();
  LW200SecVec_Gen->Write();
  LW200Esecvec_dist->Write();
  LW200Esecvec_sigma->Write();
  LW200Esecvec_Chi2->Write();
  LW200Esecvec_MatchEle_dist->Write();
  LW200Esecvec_bydist->Write();
  LW200Esecvec_bysigma->Write();
  LW200Esecvec_Gen->Write();

  LW200GenZ_pt->Write();
  LW200GenLW_pt->Write();
  LW200GenZ_ele_dR->Write();
  LW200GenZ_LW_dR->Write();
  LW200GenZ_dR->Write();
  LW200LW_dR->Write();

  LW200W_GenZ_pt->Write();
  LW200W_GenLW_pt->Write();
  LW200W_GenZ_ele_dR->Write();
  LW200W_GenZ_LW_dR->Write();
  LW200W_GenZ_dR->Write();
  LW200W_LW_dR->Write();
  LW200W_BJet_GenJet_pt->Write();
  LW200W_BJet_GenJet_corr_pt->Write();
  LW200BJet_GenJet_pt->Write();
  LW200BJet_GenJet_corr_pt->Write();

  LW200W_GenJet_GenEle_DR->Write();
  LW200GenJet_GenEle_DR->Write();
  LW200W_NConst->Write();
  LW200W_ChargedEMF->Write();
  LW200W_NeutralEMF->Write();
  LW200NConst->Write();
  LW200ChargedEMF->Write();
  LW200NeutralEMF->Write();

  LW200EleZdauDR->Write();
  LW200EleSZdauDR->Write();
  LW200EleNSZdauDR->Write();
  LW200EleZdauPT->Write();
  LW200EleSZdauPT->Write();
  LW200EleSZdau_ptdiff->Write();
  LW200ZdauSZdauDR->Write();
  LW200EleBZdauDR->Write();
  LW200ZdauInvmass->Write();
  LW200ZdauCharge->Write();
  LW200RecoZdauInvmass->Write();
  LW200RecoZdauEleInvmass->Write();
  LW200RecoZdauCharge->Write();

  LW200SecVec_Ppoint->Write();
  LW200SecVec_PpointS->Write();
  LW200EleDijet_Ppoint->Write();
  LW200EleDijet_PpointS->Write();
  LW200EleJetInvM_Ppoint->Write();
  LW200EleJetInvM_PpointS->Write();
  LW200GenSecVec_PpointS->Write();
  LW200GenSecVec_Ppoint->Write();
  LW200SecVec_EleJet_Ppoint->Write();
  LW200SecVec_EleJet_PpointS->Write();

  LW200Zdau_GenjetMatch->Write();
  LW200Zdau_BjetMatch->Write();
  LW200Zdau_SBjetMatch->Write();
  LW200Zdau_3jetMatch->Write();
  LW200Zdau_4jetMatch->Write();

  LW200BZdau_GenjetMatch->Write();
  LW200BZdau_BjetMatch->Write();
  LW200BZdau_SBjetMatch->Write();
  LW200BZdau_3jetMatch->Write();
  LW200BZdau_4jetMatch->Write();

  LW200Elec_GenElecMatch->Write();
  LW200Elec_BElecMatch->Write();
  LW200Elec_SBElecMatch->Write();

  LW200BElec_GenElecMatch->Write();
  LW200BElec_BElecMatch->Write();
  LW200BElec_SBElecMatch->Write();

  LW200SBElec_GenElecMatch->Write();
  LW200SBElec_BElecMatch->Write();
  LW200SBElec_SBElecMatch->Write();
  LW200SBElec_3ElecMatch->Write();
  LW200SBElec_4ElecMatch->Write();

  LW200Secvec_jet->Write();
  LW200Electron_ZdauCand_DR->Write();
  LW200Electron_ZdauCand_Count->Write();
  LW200Electron_ZdauCand_InvMass->Write();
  LW200BElectron_ZdauCand_DR->Write();
  LW200BElectron_ZdauCand_Count->Write();
  LW200BElectron_ZdauCand_InvMass->Write();
  LW200Electron_ZdauCand_RecoZdauMatch->Write();
  LW200BElectron_ZdauCand_RecoZdauMatch->Write();

  LW200JetZdau_IP->Write();


  hfile->Close();


  return 0;

}
