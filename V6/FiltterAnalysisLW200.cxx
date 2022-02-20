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
// g++ -std=c++11 -g -O3 -Wall -Wextra -o FiltterAnalysisLW200 FiltterAnalysisLW200.cxx $(root-config --cflags --libs)
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
TH1F* LW200RecoZdauInvmass = new TH1F("LW200RecoZdauInvmass","Reco Zdau Invariant mass;InvariantMass[GeV];",100,0,200);
TH1F* LW200RecoZdauEleInvmass = new TH1F("LW200RecoZdauEleInvmass","Reco Zdau plus Reco Electron Invariant mass;InvariantMass[GeV];",100,0,500);

TH1F* LW200EleDijet_Ppoint = new TH1F("LW200EleDijet_Ppoint","Electron dijet total momentum Secondary vertex point;Ppoint[GeV*mm];",100,-100,100);
TH1F* LW200EleDijet_PpointS = new TH1F("LW200EleDijet_PpointS","Electron dijet total momentum Secondary vertex point sign;Ppoint sign;",100,-2,2);
TH1F* LW200EleJetInvM_Ppoint = new TH1F("LW200EleJetInvM_Ppoint","Electron Jet total momentum Secondary vertex point;Ppoint[GeV*mm];",100,-100,100);
TH1F* LW200EleJetInvM_PpointS = new TH1F("LW200EleJetInvM_PpointS","Electron Jet total momentum Secondary vertex point sign;Ppoint sign;",100,-2,2);
TH1F* LW200SecVec_Ppoint = new TH1F("LW200SecVec_Ppoint","Secondary vertex total momentum Secondary vertex point;Ppoint[GeV*mm];",100,-100,100);
TH1F* LW200SecVec_PpointS = new TH1F("LW200SecVec_PpointS","Secondary vertex total momentum Secondary vertex point sign;Ppoint sign;",100,-2,2);
TH1F* LW200GenSecVec_Ppoint = new TH1F("LW200GenSecVec_Ppoint","Gen Secondary vertex total momentum Secondary vertex point;Ppoint[GeV*mm];",100,-100,100);
TH1F* LW200GenSecVec_PpointS = new TH1F("LW200GenSecVec_PpointS","Gen Secondary vertex total momentum Secondary vertex point sign;Ppoint sign;",100,-2,2);

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
//-----------------------------------------------------------------

  //cout<<"analysis() execution"<<endl;

  //minimal selection including trigger requirement
  //if (!MinimalSelection()) return;
  //counter_ms++;


  //fill histograms for signal region
  //Int_t histsize = sizeof(hists)/sizeof(hists[0]);
  //Float_t pstmp;
//Filling Electrons pt
  vector <pair<float,float>> vect;
  int Hcount=0;
  if(electron_pt->size()!=0){
    for (size_t i = 0; i < electron_pt->size(); i++) {
      if (electron_pt->at(i)>Minpt) {
        hists[1]->Fill(electron_pt->at(i));
        hists[2]->Fill(electron_eta->at(i));
      }
      vect.push_back(make_pair(electron_pt->at(i),electron_eta->at(i)));
    }

    sort(vect.begin(),vect.end());
    /*if(vect[vect.size()-1].first>Minpt){
      Hcount++;
      LW200Helec_pt->Fill(vect[vect.size()-1].first);
      LW200Helec_eta->Fill(vect[vect.size()-1].second);
    }*/
    if(vect.size()>=2){
      if(vect[vect.size()-2].first>Minpt){
        LW200Helec_pt->Fill(vect[vect.size()-2].first);
        LW200Helec_eta->Fill(vect[vect.size()-2].second);
        Hcount++;
      }
    }
  }
  LW200Helec_num->Fill(Hcount);
  vect.clear();
  Hcount=0;

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
        }
      }
    }
  }

  //Filling tracks
  int ntrk=0;
  if(track_pt->size()!=0){
    for (size_t i = 0; i < track_pt->size(); i++) {
      if (track_pt->at(i)>Minpt && track_chi2->at(i)<1) {
        ntrk++;
        LW200Track_pt->Fill(track_pt->at(i));
        LW200Track_eta->Fill(track_eta->at(i));
      }
      vect.push_back(make_pair(track_pt->at(i),track_eta->at(i)));
    }
    sort(vect.begin(),vect.end());
    /*if(vect[vect.size()-1].first>Minpt){
      Hcount++;
      LW200Htrk_pt->Fill(vect[vect.size()-1].first);
      LW200Htrk_eta->Fill(vect[vect.size()-1].second);
    }*/
    if(vect.size()>=2){
      if(vect[vect.size()-2].first>Minpt){
        LW200Htrk_pt->Fill(vect[vect.size()-2].first);
        LW200Htrk_eta->Fill(vect[vect.size()-2].second);
        Hcount++;
      }
    }
  }
  LW200Track_num->Fill(ntrk);
  LW200Htrk_num->Fill(Hcount);
  //Filling photons pt
  int nphot=0;
  if(photon_pt->size()!=0){
    for (size_t i = 0; i < photon_pt->size(); i++) {
      if (photon_pt->at(i)>Minpt) {
        nphot++;
        hists[4]->Fill(photon_pt->at(i));
        hists[5]->Fill(photon_eta->at(i));
      }
    }
  }
  hists[3]->Fill(nphot);
  //Filling Genpart pt
  int genelec=0;
  int genphot=0;
  int nsgenelec=0;
  //cout<<GenPart_mompdgId->size()<<' '<<GenPart_pt->size() <<'\n';
  for (size_t i = 0; i < GenDau_pt->size(); i++) {
    if (abs(GenDau_mompdgId->at(i)) == 556) {
      //cout <<GenDau_mompdgId->at(i)<<' '<< GenDau_pdgId->at(i) << '\n';
      if( abs(GenDau_pdgId->at(i)) == 11 && GenDau_pt->at(i)>Minpt){
        if(GenDau_pt->at(i)<Minpt)genelec++;
        hists[7]->Fill(GenDau_pt->at(i));
        hists[8]->Fill(GenDau_eta->at (i));
      }
    }
    if (abs(GenDau_mompdgId->at(i)) == 24) {
      hists[12]->Fill(GenDau_pt->at(i));
      hists[13]->Fill(GenDau_eta->at (i));
    }
  }
  for (size_t i = 0; i < GenPart_pt->size(); i++) {
    if( abs(GenPart_pdgId->at(i)) == 22 && GenPart_pt->at(i)>Minpt ){
      genphot++;
      hists[10]->Fill(GenPart_pt->at(i));
      hists[11]->Fill(GenPart_eta->at (i));
    }
    if( abs(GenPart_pdgId->at(i)) == 11 && GenPart_pt->at(i)>Minpt ){
      nsgenelec++;
      hists[15]->Fill(GenPart_pt->at(i));
      hists[16]->Fill(GenPart_eta->at (i));
    }
  }
  hists[6]->Fill(genelec);
  hists[9]->Fill(genphot);
  hists[14]->Fill(nsgenelec);
//cheking number of phtons and elec
  bool isFill=false;

  if(electron_pt->size()!=0){
    for (size_t i = 0; i < electron_pt->size(); i++) {
      if (electron_pt->at(i)>Minpt) {
        hists[0]->Fill(1);
        isFill=true;
        i=electron_pt->size();
      }
    }
    if(!isFill && photon_pt->size()!=0 ){
      for (size_t j = 0; j < photon_pt->size(); j++) {
        if (photon_pt->at(j)>Minpt) {
          hists[0]->Fill(1);
          j=photon_pt->size();
          isFill=true;
        }
      }
      if(!isFill){
        hists[0]->Fill(0);//Electrones malos photones malos
        isFill=true;
      }
    }
    else if(!isFill){
      hists[0]->Fill(2);//Electrones malos no Photones
      isFill=true;
    }
  }
  else if(photon_pt->size()!=0){
    for (size_t i = 0; i < photon_pt->size(); i++) {
      if (photon_pt->at(i)>Minpt) {
        hists[0]->Fill(1);
        i=photon_pt->size();
        isFill=true;
      }
    }
    if(!isFill){
      hists[0]->Fill(3);//no Electrones Fotones malos
      isFill=true;
    }
  }
  else {
    hists[0]->Fill(4);//no Electrones no Fotones
    for (size_t i = 0; i < GenDau_pt->size(); i++) {
      if (abs(GenDau_mompdgId->at(i)) == 556) {
        //cout <<GenDau_mompdgId->at(i)<<' '<< GenDau_pdgId->at(i) << '\n';
        if( abs(GenDau_pdgId->at(i)) == 11 ){
          cout<<"Elept: "<<GenDau_pt->at(i)<<" eta: "<<GenDau_eta->at(i)<<" phi: "<<GenDau_phi->at(i)<<'\n';
        }
      }
      if (abs(GenDau_mompdgId->at(i)) == 24) {
        hists[12]->Fill(GenDau_pt->at(i));
        hists[13]->Fill(GenDau_eta->at (i));
      }
    }
    isFill=true;
  }
///chekeando masa invariante Zjets
  //cout<<"\n\n";
  float px,py,pz,e,m,Mlw;
  int zcount=0;
  for(size_t i=0; i < jet_mass->size(); i++){
    for(size_t j=i+1; j < jet_mass->size(); j++){
      if(i!=j){
        px=0,py=0,pz=0,e=0,m=0,Mlw=0;
        //cout<<mass1+jet_mass->at(j)<<endl;
        px=jet_px->at(i)+jet_px->at(j);
        py=jet_py->at(i)+jet_py->at(j);
        pz=jet_pz->at(i)+jet_pz->at(j);
        e=jet_e->at(i)+jet_e->at(j);
        m=sqrt( e*e - px*px - py*py - pz*pz );
        if(m>MinZm && m<MaxZm){
          zcount++;
          LW200jet_mass->Fill(m);
        }
      }
    }
  }
  if(zcount>=1) LW200jet_massfilter->Fill(1);
  else LW200jet_massfilter->Fill(0);
//correctedJetMass
  float corr_pt;
  for(size_t i=0; i < jet_mass->size(); i++){
    for(size_t j=i+1; j < jet_mass->size(); j++){
      if(j!=i){
        corr_pt=0,pz=0,e=0,m=0;
        //cout<<mass1+jet_mass->at(j)<<endl;
        px=cos(jet_phi->at(i))*corr_jet_pt->at(i) + cos(jet_phi->at(j))*corr_jet_pt->at(j);
        py=sin(jet_phi->at(i))*corr_jet_pt->at(i) + sin(jet_phi->at(j))*corr_jet_pt->at(j);
        float corr1=corr_jet_pt->at(i)/jet_pt->at(i);
        float corr2=corr_jet_pt->at(j)/jet_pt->at(j);
        pz=jet_pz->at(i)*corr1+jet_pz->at(j)*corr2;
        e=jet_e->at(i)*corr1+jet_e->at(j)*corr2;
        m=sqrt( e*e - px*px - py*py - pz*pz );

        if(m>MinZm && m<MaxZm){
          LW200Corrjet_mass->Fill(m);
        }
      }
    }
  }
//matching Jets With gen quarks
  zcount=0;
  vector<float> gjet_DRscore, gjet_index;
  gjet_DRscore.clear();
  gjet_index.clear();
  float saveDR, jetDR;
  size_t saveInd;
  for(size_t i=0; i < GenDau_pt->size(); i++){
    saveDR=100;
    saveInd=0;
    if(abs(GenDau_mompdgId->at(i))==24 && abs(GenDau_pdgId->at(i))!=24){
      for(size_t j=0; j < jet_e->size(); j++){
        jetDR=deltaR(GenDau_eta->at(i),GenDau_phi->at(i),jet_eta->at(j),jet_phi->at(j));
        if(jetDR<saveDR){
          saveDR=jetDR;
          saveInd=j;
        }
      }
      gjet_DRscore.push_back(saveDR);
      gjet_index.push_back(saveInd);
    }
  }

//CheckJet and DR score size
  //if(gjet_DRscore.size()!=jet_pt->size()) cout<<"sizeError: "<<gjet_DRscore.size()<<' '<<jet_pt->size()<<'\n';
///Signal Dijet Invariant mass
if(gjet_DRscore.size()>1){
  for(size_t i=0; i < gjet_DRscore.size(); i++){
    //if(gjet_index.at(i)>jet_e->size())cout<<"sizeError: "<<gjet_index.at(i)<<' '<<jet_pt->size()<<endl;
    for(size_t j=i+1; j < gjet_DRscore.size(); j++){
      //if(gjet_index.at(j)>jet_e->size())cout<<"sizeError: "<<gjet_index.at(j)<<' '<<jet_pt->size()<<endl;
      px=0,py=0,pz=0,e=0,m=0;
      if(i!=j){
        if( gjet_DRscore.at(i)<0.5 && gjet_DRscore.at(j)<0.5){
          //cout<<mass1+genjet_mass.at(j)<<endl;
          px=cos(jet_phi->at(gjet_index.at(i)))*corr_jet_pt->at(gjet_index.at(i)) + cos(jet_phi->at(gjet_index.at(j)))*corr_jet_pt->at(gjet_index.at(j));
          py=sin(jet_phi->at(gjet_index.at(i)))*corr_jet_pt->at(gjet_index.at(i)) + sin(jet_phi->at(gjet_index.at(j)))*corr_jet_pt->at(gjet_index.at(j));
          float corr1=corr_jet_pt->at(gjet_index.at(i))/jet_pt->at(gjet_index.at(i));
          float corr2=corr_jet_pt->at(gjet_index.at(j))/jet_pt->at(gjet_index.at(j));
          pz=jet_pz->at(gjet_index.at(i))*corr1+jet_pz->at(gjet_index.at(j))*corr2;
          e=jet_e->at(gjet_index.at(i))*corr1+jet_e->at(gjet_index.at(j))*corr2;
          m=sqrt( e*e - px*px - py*py - pz*pz );

          for(size_t k=0; k < electron_pt->size(); k++){
            px=px+electron_px->at(k);
            py=py+electron_py->at(k);
            pz=pz+electron_pz->at(k);
            Mlw=sqrt( e*e - px*px - py*py - pz*pz );
            LW200LW_mass->Fill(Mlw);
          }

          if(m>MinZm && m<MaxZm){
            zcount++;
            LW200Sjet_mass->Fill(m);
          }
        }
      }
    }
  }
}

  if(zcount>=1) LW200Sjet_massfilter->Fill(1);
  else LW200Sjet_massfilter->Fill(0);
/////////////////////////Generated Inva Mass/////////////////////////////////
  zcount=0;
  for (size_t i = 0; i < GenDau_pt->size(); i++) {
    for (size_t j = i+1; j < GenDau_pt->size(); j++) {
      if(abs(GenDau_mompdgId->at(i))==24 && abs(GenDau_mompdgId->at(j))==24
        && abs(GenDau_pdgId->at(i))!=24 && abs(GenDau_pdgId->at(j))!=24){
        if(i!=j){
          float drWdau=deltaR(GenDau_eta->at(i),GenDau_phi->at(i),GenDau_eta->at(j),GenDau_phi->at(j));
          LW200Wdau_deltaR->Fill(drWdau);
          //LW200Wdau_deltaR->Fill(GenDau_pdgId->at(i));
          float e1=sqrt(GenDau_mass->at(i)*GenDau_mass->at(i)+GenDau_pt->at(i)*GenDau_pt->at(i)+GenDau_pz->at(i)*GenDau_pz->at(i));
          float e2=sqrt(GenDau_mass->at(j)*GenDau_mass->at(j)+GenDau_pt->at(j)*GenDau_pt->at(j)+GenDau_pz->at(j)*GenDau_pz->at(j));
          px=GenDau_px->at(i)+GenDau_px->at(j);
          py=GenDau_py->at(i)+GenDau_py->at(j);
          pz=GenDau_pz->at(i)+GenDau_pz->at(j);
          e=e1+e2;
          m=sqrt( e*e - px*px - py*py - pz*pz );
          //cout<<GenDau_pdgId->at(i)<<' '<<GenDau_pdgId->at(j)<<' '<<m<<endl;
          LW200Genjet_mass->Fill(m);
          if(GenDau_pdgId->at(i)==11 && GenDau_pdgId->at(j)==-11){
            //zcount++;
            //float drWdau=deltaR(GenDau_eta->at(i),GenDau_phi->at(i),GenDau_eta->at(j),GenDau_phi->at(j));
            //LW200Wdau_deltaR->Fill(drWdau);
            /*float e1=sqrt(GenDau_mass->at(i)*GenDau_mass->at(i)+GenDau_pt->at(i)*GenDau_pt->at(i)+GenDau_pz->at(i)*GenDau_pz->at(i));
            float e2=sqrt(GenDau_mass->at(j)*GenDau_mass->at(j)+GenDau_pt->at(j)*GenDau_pt->at(j)+GenDau_pz->at(j)*GenDau_pz->at(j));
            px=GenDau_px->at(i)+GenDau_px->at(j);
            py=GenDau_py->at(i)+GenDau_py->at(j);
            pz=GenDau_pz->at(i)+GenDau_pz->at(j);
            e=e1+e2;
            m=sqrt( e*e - px*px - py*py - pz*pz );
            LW200Genjet_mass->Fill(m);*/

            for (size_t k = 0; k < electron_pt->size(); k++) {
              for (size_t l = 0; l < electron_pt->size(); l++) {
                if( genelec_DRscore->at(k)<0.1 && genelec_pt->at(k)==GenDau_pt->at(i) ){
                  if( genelec_DRscore->at(l)<0.1 && genelec_pt->at(l)==GenDau_pt->at(j) ){
                    px=electron_px->at(k)+electron_px->at(l);
                    py=electron_py->at(k)+electron_py->at(l);
                    pz=electron_pz->at(k)+electron_pz->at(l);
                    e =electron_e->at(k) +electron_e->at(l);
                    m=sqrt( e*e - px*px - py*py - pz*pz );
                    LW200RecoEle_mass->Fill(m);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if(zcount>=1) LW200Genjet_massfilter->Fill(1);
  else LW200Genjet_massfilter->Fill(0);
  //////////////////////Reco Electron Inv Mass/////////////////////////////

  //////////////////////////////////Strange matched jet region analysis////////////////



  //////////////////////Jet and Ele DR analysis/////////////
  vector<pair <float,size_t> > JetPtTemp;
  vector<float> JetDRTemp;
  vector<pair <float,size_t> > ElePtTemp;
  vector<float> EleDRTemp;

  for (size_t i = 0; i < electron_pt->size(); i++) {ElePtTemp.push_back(make_pair(electron_pt->at(i),i));}
  sort(ElePtTemp.begin(),ElePtTemp.end());

  if(corr_jet_pt->size()>4 && ElePtTemp.size()>1 && ElePtTemp.back().first>40 && ElePtTemp.end()[-2].first>25){
    ElePtTemp.clear();
    JetPtTemp.clear();
    for(size_t x=0; x<corr_jet_pt->size(); x++ ){JetPtTemp.push_back(make_pair(corr_jet_pt->at(x),x));}
    sort(JetPtTemp.begin(), JetPtTemp.end());
    float DiJetDR=deltaR(jet_eta->at(JetPtTemp.back().second),jet_phi->at(JetPtTemp.back().second),jet_eta->at(JetPtTemp.end()[-2].second),jet_phi->at(JetPtTemp.end()[-2].second));
    LW200DiJet_DR->Fill(DiJetDR);

    if(genjet_DRscore->at(JetPtTemp.back().second)<0.1){
      LW200BJet_GenJet_pt->Fill(jet_pt->at(JetPtTemp.back().second),genjet_pt->at(JetPtTemp.back().second));
      if(ChargedEMF->at(JetPtTemp.back().second)<0.6) LW200W_BJet_GenJet_pt->Fill(jet_pt->at(JetPtTemp.back().second),genjet_pt->at(JetPtTemp.back().second));
    }
    if(genjet_DRscore->at(JetPtTemp.back().second)<0.1){
      LW200BJet_GenJet_corr_pt->Fill(corr_jet_pt->at(JetPtTemp.back().second),genjet_pt->at(JetPtTemp.back().second));
      if(ChargedEMF->at(JetPtTemp.back().second)<0.6) LW200W_BJet_GenJet_corr_pt->Fill(corr_jet_pt->at(JetPtTemp.back().second),genjet_pt->at(JetPtTemp.back().second));
    }

    for (size_t i = 0; i < electron_pt->size(); i++) {
      if(i==ElePtTemp.back().second || i==ElePtTemp.end()[-2].second){
        for(size_t x=0; x<corr_jet_pt->size(); x++){
          if(x==JetPtTemp.back().second||x==JetPtTemp.end()[-2].second||x==JetPtTemp.end()[-3].second||x==JetPtTemp.end()[-4].second){
            EleDRTemp.push_back(deltaR(jet_eta->at(x),jet_phi->at(x),electron_eta->at(i),electron_phi->at(i)));
          }
        }
        sort(EleDRTemp.begin(),EleDRTemp.end());
        LW200EleJet_DR1->Fill(EleDRTemp.front());
        LW200EleJet_DR2->Fill(EleDRTemp.at(1));
        LW200EleJet_DRdiff->Fill(abs(EleDRTemp.at(1)-EleDRTemp.front()));
      }
    }
    for(size_t x=0; x<corr_jet_pt->size(); x++){
      if(x==JetPtTemp.back().second||x==JetPtTemp.end()[-2].second||x==JetPtTemp.end()[-3].second||x==JetPtTemp.end()[-4].second){
        LW2004Jets_pt->Fill(jet_pt->at(x));
        LW2004CorrJets_pt->Fill(corr_jet_pt->at(x));
        LW2004Jets_eta->Fill(jet_eta->at(x));
        if(corr_jet_pt->at(x)>200 && genjet_pt->at(x) <100){
          LW200W_4Jets_pt->Fill(jet_pt->at(x));
          LW200W_4CorrJets_pt->Fill(corr_jet_pt->at(x));
          LW200W_4Jets_eta->Fill(jet_eta->at(x));
        }
        for(size_t y=x+1; y<corr_jet_pt->size(); y++){
          if(y==JetPtTemp.back().second||y==JetPtTemp.end()[-2].second||y==JetPtTemp.end()[-3].second||y==JetPtTemp.end()[-4].second){
            JetDRTemp.push_back(deltaR(jet_eta->at(x),jet_phi->at(x),jet_eta->at(y),jet_phi->at(y)));

          }
        }

        sort(JetDRTemp.begin(),JetDRTemp.end());
        LW2004Jets_DR->Fill(JetDRTemp.front());

        if(genjet_DRscore->at(x)<0.5){
          LW2004GenJets_pt->Fill(genjet_pt->at(x));
          if(jet_pt->at(x)>200 && genjet_pt->at(x)<100){
            LW200W_4GenJets_pt->Fill(genjet_pt->at(x));
          }
        }
      }
    }

  }

  ///////////////lw_pt y Z_pt/////////////////////
  for(size_t i=0; i<GenPart_pt->size(); i++){
    if(GenPart_pdgId->at(i)==23 && abs(GenPart_mompdgId->at(i))==556){
      LW200GenZ_pt->Fill(GenPart_pt->at(i));
      if(GenPart_pt->at(i)<200) LW200W_GenZ_pt->Fill(GenPart_pt->at(i));
    }
    if(abs(GenPart_pdgId->at(i))==556){
      LW200GenLW_pt->Fill(GenPart_pt->at(i));
    }
  }
  ////////////////////dR Z-Ele///////////////////
  for(size_t i=0; i<GenDau_pt->size();i++){
    if(GenDau_mompdgId->at(i)==556){
      for(size_t j=0; j<GenDau_pt->size();j++){
        if(GenDau_mompdgId->at(j)==556){
          if(GenDau_pdgId->at(i)==11 && GenDau_pdgId->at(j)==23){
            LW200GenZ_ele_dR->Fill(deltaR(GenDau_eta->at(i),GenDau_phi->at(i),GenDau_eta->at(j),GenDau_phi->at(j)));
            if(GenDau_pt->at(j)<200) LW200W_GenZ_ele_dR->Fill(deltaR(GenDau_eta->at(i),GenDau_phi->at(i),GenDau_eta->at(j),GenDau_phi->at(j)));
          }
        }
      }
    }
  }
  /////////////////////////////////DRZ-Z
  for(size_t i=0; i<GenDau_pt->size();i++){
    if(GenDau_mompdgId->at(i)==556 && GenDau_pdgId->at(i)==23){
      for(size_t j=0; j<GenDau_pt->size();j++){
        if(GenDau_mompdgId->at(j)==-556 && GenDau_pdgId->at(j)==23){
          LW200GenZ_dR->Fill(deltaR(GenDau_eta->at(i),GenDau_phi->at(i),GenDau_eta->at(j),GenDau_phi->at(j)));
          if(GenDau_pt->at(j)<200) LW200W_GenZ_dR->Fill(deltaR(GenDau_eta->at(i),GenDau_phi->at(i),GenDau_eta->at(j),GenDau_phi->at(j)));
        }
      }
    }
  }
  for(size_t i=0; i<GenPart_pt->size();i++){
    if(GenPart_pdgId->at(i)==556){
      for(size_t j=0; j<GenPart_pt->size();j++){
        if(GenPart_pdgId->at(j)==-556){
          LW200LW_dR->Fill(deltaR(GenPart_eta->at(i),GenPart_phi->at(i),GenPart_eta->at(j),GenPart_phi->at(j)));
        }
      }
    }
  }
  for(size_t i=0; i<GenPart_pt->size();i++){
    if(GenPart_pdgId->at(i)==556){
      for(size_t j=0; j<GenPart_pt->size();j++){
        if(GenPart_mompdgId->at(j)==556 && GenPart_pdgId->at(j)==23){
          LW200GenZ_LW_dR->Fill(deltaR(GenPart_eta->at(i),GenPart_phi->at(i),GenPart_eta->at(j),GenPart_phi->at(j)));
          if(GenPart_pt->at(j)<200) LW200W_GenZ_LW_dR->Fill(deltaR(GenPart_eta->at(i),GenPart_phi->at(i),GenPart_eta->at(j),GenPart_phi->at(j)));
        }
      }
    }
  }

  /*vector<float> GenEleDRTemp;
  float Zx,Zy,Zz;
  for (size_t x = 0; x < GenPart_pt->size(); x++) {

    if(GenPart_mompdgId->at(x)==556){
      if(GenPart_pdgId->at(x)==23){
        Zx=GenPart_px->at(x);
        Zy=GenPart_py->at(x);
        Zz=GenPart_pz->at(x);
      }
    }
  }
  vector<pair<float, size_t>> vZx;
  vector<pair<float, size_t>> vZy;
  vector<pair<float, size_t>> vZz;
  for (size_t y = 0; y < GenDau_pt->size(); y++) {
    if(GenDau_mompdgId->at(y)==23){
      vZx.push_back(make_pair(GenDau_px->at(y),y));
      vZy.push_back(make_pair(GenDau_py->at(y),y));
      vZz.push_back(make_pair(GenDau_pz->at(y),y));
    }
  }
  size_t iZ1, iZ2;
  for(size_t x=0; x<vZx.size(); x++){
    for(size_t y=x+1; y<vZy.size(); y++){
      if((vZx.at(x).first+vZx.at(y).first)==Zx &&(vZy.at(x).first+vZy.at(y).first)==Zy && (vZz.at(x).first+vZz.at(y).first)==Zz){
        iZ1=vZx.at(x).second;
        iZ2=vZx.at(y).second;
      }
    }
  }
  for (size_t x = 0; x < GenPart_pt->size(); x++) {

    if(GenPart_mompdgId->at(x)==556 && GenPart_pdgId->at(x)==11){
      GenEleDRTemp.push_back(deltaR(GenPart_eta->at(x),GenPart_phi->at(x),GenDau_eta->at(iZ1),GenDau_phi->at(iZ1)));
      GenEleDRTemp.push_back(deltaR(GenPart_eta->at(x),GenPart_phi->at(x),GenDau_eta->at(iZ2),GenDau_phi->at(iZ2)));
    }
  }

  sort(GenEleDRTemp.begin(),GenEleDRTemp.end());
  LW200Gen_EleJet_DR1->Fill(GenEleDRTemp.front());
  LW200Gen_EleJet_DR2->Fill(GenEleDRTemp.at(1));
  LW200Gen_EleJet_DRdiff->Fill(abs(GenEleDRTemp.at(1)-GenEleDRTemp.front()));*/


    //if(GenPart_mompdgId->at(x)==-556 &&GenPart_pdgId->at(x)==-11){}
    vector<pair<float,float>> dist;
    dist.clear();
    float dx,dy,dz,sigma;
    float vx,vy,vz;
    if(MinimalSelection()){
      /////////////////GenPart vertices///////////////////////////
      for(size_t y=0; y<GenPart_pt->size(); y++){
        if(abs(GenPart_pdgId->at(y))==556){
          vx=GenPart_vx->at(y);
          vy=GenPart_vy->at(y);
          vz=GenPart_vz->at(y);
        }
      }
      for(size_t y=0; y<GenPart_pt->size(); y++){
        if( abs(GenPart_pdgId->at(y))==11 && abs(GenPart_mompdgId->at(y))==556 ){// && GenPart_pt->at(y)==electron_pt->at(secvec_eleTag->at(x)) ){
          dx=GenPart_vx->at(y)-vx;
          dy=GenPart_vy->at(y)-vy;
          dz=GenPart_vz->at(y)-vz;
          LW200SecVec_Gen->Fill(sqrt(dx*dx+dy*dy+dz*dz));
        }
      }
      /////////////////////////////Electron secvec/////////////////////////
      vector<size_t> MatchEleTag;
      MatchEleTag.clear();
      for(size_t y=0; y<electron_pt->size();y++){
        if(genelec_DRscore->at(y)<0.1){
          for(size_t k=0; k<GenPart_pt->size(); k++){
            if(abs(GenPart_pdgId->at(k))==11 && abs(GenPart_mompdgId->at(k))==556 && GenPart_pt->at(k)==genelec_pt->at(y)){
              MatchEleTag.push_back(y);
            }
          }
        }
      }
      for(size_t x=0; x<secvec_posx->size(); x++){
        if(secvec_eleTag->at(x)==ElePtTemp.back().second){
          dx=secvec_posx->at(x)-PV_x->at(0);
          dy=secvec_posy->at(x)-PV_y->at(0);
          dz=secvec_posz->at(x)-PV_z->at(0);
          sigma=sqrt(secvec_poserrorx->at(x)*secvec_poserrorx->at(x)+secvec_poserrory->at(x)*secvec_poserrory->at(x)+secvec_poserrorz->at(x)*secvec_poserrorz->at(x));
          dist.push_back(make_pair(sqrt(dx*dx+dy*dy+dz*dz)/secvec_normchi2->at(x),sigma));
        }
        dx=secvec_posx->at(x)-PV_x->at(0);
        dy=secvec_posy->at(x)-PV_y->at(0);
        dz=secvec_posz->at(x)-PV_z->at(0);
        LW200SecVec_dist->Fill(sqrt(dx*dx+dy*dy+dz*dz)/secvec_normchi2->at(x));
        LW200SecVec_sigma->Fill(sigma);
        LW200SecVec_Chi2->Fill(secvec_normchi2->at(x));

        if(MatchEleTag.size()>0){
          for(size_t y=0; y<MatchEleTag.size(); y++){
            if(secvec_eleTag->at(x)==MatchEleTag.at(y)){
              dx=secvec_posx->at(x)-PV_x->at(0);
              dy=secvec_posy->at(x)-PV_y->at(0);
              dz=secvec_posz->at(x)-PV_z->at(0);
              LW200SecVec_MatchEle_dist->Fill(sqrt(dx*dx+dy*dy+dz*dz)/secvec_normchi2->at(x));
            }
          }
        }
      }

      if(dist.size()>0){
        sort(dist.begin(),dist.end());
        LW200SecVec_bydist->Fill(dist.back().first);

        sort(dist.begin(), dist.end(), sortbysec);
        LW200SecVec_bysigma->Fill(dist.back().first);
      }


    }

    dist.clear();

    if(MinimalSelection()){
      vector<size_t> MatchEleTag;
      MatchEleTag.clear();
      for(size_t y=0; y<electron_pt->size();y++){
        if(genelec_DRscore->at(y)<0.1){
          for(size_t k=0; k<GenPart_pt->size(); k++){
            if(abs(GenPart_pdgId->at(k))==11 && abs(GenPart_mompdgId->at(k))==556 && GenPart_pt->at(k)==genelec_pt->at(y)){
              MatchEleTag.push_back(y);
            }
          }
        }
      }
      for(size_t x=0; x<Esecvec_posx->size(); x++){
        if(Esecvec_eleTag->at(x)==ElePtTemp.back().second){
          dx=Esecvec_posx->at(x)-PV_x->at(0);
          dy=Esecvec_posy->at(x)-PV_y->at(0);
          dz=Esecvec_posz->at(x)-PV_z->at(0);
          sigma=sqrt(Esecvec_poserrorx->at(x)*Esecvec_poserrorx->at(x)+Esecvec_poserrory->at(x)*Esecvec_poserrory->at(x)+Esecvec_poserrorz->at(x)*Esecvec_poserrorz->at(x));
          dist.push_back(make_pair(sqrt(dx*dx+dy*dy+dz*dz),sigma));
        }
        dx=Esecvec_posx->at(x)-PV_x->at(0);
        dy=Esecvec_posy->at(x)-PV_y->at(0);
        dz=Esecvec_posz->at(x)-PV_z->at(0);
        LW200Esecvec_dist->Fill(sqrt(dx*dx+dy*dy+dz*dz));
        LW200Esecvec_sigma->Fill(sigma);
        LW200Esecvec_Chi2->Fill(Esecvec_normchi2->at(x));

        if(MatchEleTag.size()>0){
          for(size_t y=0; y<MatchEleTag.size(); y++){
            if(Esecvec_eleTag->at(x)==MatchEleTag.at(y)){
              dx=Esecvec_posx->at(x)-PV_x->at(0);
              dy=Esecvec_posy->at(x)-PV_y->at(0);
              dz=Esecvec_posz->at(x)-PV_z->at(0);
              LW200Esecvec_MatchEle_dist->Fill(sqrt(dx*dx+dy*dy+dz*dz));
            }
          }
        }
      }
      if(dist.size()>0){
        sort(dist.begin(),dist.end());
        LW200Esecvec_bydist->Fill(dist.back().first);

        sort(dist.begin(), dist.end(), sortbysec);
        LW200Esecvec_bysigma->Fill(dist.back().first);
      }

      //bool StrageRegime=false;
      vector<pair<size_t,size_t>> GenDauIndex;

      for(size_t y=0; y<jet_pt->size();y++){
        vector<float> Jet_Ele_DR;
        if(corr_jet_pt->at(y)>200 && genjet_pt->at(y)<100 && genjet_DRscore->at(y)<0.1){
          //StangerRegime= true;
          LW200W_NConst->Fill(NConstituents->at(y));
          LW200W_ChargedEMF->Fill(ChargedEMF->at(y));
          LW200W_NeutralEMF->Fill(NeutralEMF->at(y));
          for(size_t z=0; z<GenDau_pt->size(); z++){
            if(GenDau_pdgId->at(z)==23 && GenDau_pt->at(z)==genjet_pt->at(y)){
              GenDauIndex.push_back(make_pair(y,z));
            }
          }
          Jet_Ele_DR.clear();
          for(size_t x=0; x<GenPart_pt->size(); x++){
            if(abs(GenPart_pdgId->at(x))==11){
              Jet_Ele_DR.push_back(deltaR(GenPart_eta->at(x),GenPart_phi->at(x),genjet_eta->at(y),genjet_phi->at(y)));
            }
          }
          sort(Jet_Ele_DR.begin(),Jet_Ele_DR.end());
          LW200W_GenJet_GenEle_DR->Fill(Jet_Ele_DR.front());
        }
        else if(genjet_DRscore->at(y)<0.1){
          LW200NConst->Fill(NConstituents->at(y));
          LW200ChargedEMF->Fill(ChargedEMF->at(y));
          LW200NeutralEMF->Fill(NeutralEMF->at(y));

          Jet_Ele_DR.clear();
          for(size_t x=0; x<GenPart_pt->size(); x++){
            if(abs(GenPart_pdgId->at(x))==11){
              Jet_Ele_DR.push_back(deltaR(GenPart_eta->at(x),GenPart_phi->at(x),genjet_eta->at(y),genjet_phi->at(y)));
            }
          }
          sort(Jet_Ele_DR.begin(),Jet_Ele_DR.end());
          LW200GenJet_GenEle_DR->Fill(Jet_Ele_DR.front());
        }
      }

    }

    //////////////////////////EleZdauDR/////////////////////////
    float Zpt=0;
    size_t Zindex[2];
    size_t Eindex;
    bool Zbool = false;
    for(size_t x=0; x<GenDau_pt->size(); x++){
      if(GenDau_pdgId->at(x)==23 && GenDau_mompdgId->at(x)==556){
        Zpt=GenDau_pt->at(x);
      }
      if(GenDau_pdgId->at(x)==11 && GenDau_mompdgId->at(x)==556) Eindex=x;
    }

    for(size_t x=0; x<GenDau_pt->size(); x++){
      for(size_t y=x+1; y<GenDau_pt->size(); y++){

        if(GenDau_mompdgId->at(x)==23 && GenDau_mompdgId->at(y)==23){
          float px= GenDau_px->at(x)+GenDau_px->at(y);
          float py= GenDau_py->at(x)+GenDau_py->at(y);

          LW200EleSZdau_ptdiff->Fill(abs(sqrt(px*px+py*py)-Zpt));

          if(abs(sqrt(px*px+py*py)-Zpt)<0.001){
            Zindex[0]=x;
            Zindex[1]=y;
            Zbool=true;
          }
        }
      }
    }
    if(Zbool){
      float ZdR1=deltaR(GenDau_eta->at(Eindex),GenDau_phi->at(Eindex),GenDau_eta->at(Zindex[0]),GenDau_phi->at(Zindex[0]));
      float ZdR2=deltaR(GenDau_eta->at(Eindex),GenDau_phi->at(Eindex),GenDau_eta->at(Zindex[1]),GenDau_phi->at(Zindex[1]));
      LW200EleSZdauDR->Fill(ZdR1);
      LW200EleSZdauDR->Fill(ZdR2);
      LW200EleBZdauDR->Fill(min(ZdR1,ZdR2));
      LW200ZdauSZdauDR->Fill(deltaR(GenDau_eta->at(Zindex[0]),GenDau_phi->at(Zindex[0]),GenDau_eta->at(Zindex[1]),GenDau_phi->at(Zindex[1])));

      float ZTE=0;//GenDau_e->at(Zindex[0]) + GenDau_e->at(Zindex[1]);
      float ZTpx=GenDau_px->at(Zindex[0]) + GenDau_px->at(Zindex[1]);
      float ZTpy=GenDau_py->at(Zindex[0]) + GenDau_py->at(Zindex[1]);
      float ZTpz=GenDau_pz->at(Zindex[0]) + GenDau_pz->at(Zindex[1]);
      LW200ZdauInvmass->Fill(sqrt(ZTE*ZTE-ZTpx*ZTpx-ZTpy*ZTpy-ZTpz*ZTpz));

      ZTE=0;
      ZTpx=0;
      ZTpy=0;
      ZTpz=0;
      size_t Zcount=0;

      for(size_t i=0; i<jet_pt->size(); i++){
        if((genjet_DRscore->at(i)<0.5 && genjet_pt->at(i)==GenDau_pt->at(Zindex[0])) || (genjet_DRscore->at(i)<0.5 && genjet_pt->at(i)==GenDau_pt->at(Zindex[1]))){
          ZTE=ZTE+jet_e->at(i);
          ZTpx=ZTpx+jet_px->at(i);
          ZTpy=ZTpy+jet_py->at(i);
          ZTpz=ZTpz+jet_pz->at(i);
          Zcount++;
        }
      }
      if(Zcount>=2){
        LW200RecoZdauInvmass->Fill(sqrt(ZTE*ZTE-ZTpx*ZTpx-ZTpy*ZTpy-ZTpz*ZTpz));
        for(size_t i=0; i<electron_pt->size(); i++){
          if(genelec_DRscore->at(i)<0.1 && genelec_pt->at(i)==GenDau_pt->at(Eindex)){
            ZTE=ZTE+electron_e->at(i);
            ZTpx=ZTpx+electron_px->at(i);
            ZTpy=ZTpy+electron_px->at(i);
            ZTpz=ZTpz+electron_px->at(i);
          }
        }
        LW200RecoZdauEleInvmass->Fill(sqrt(ZTE*ZTE-ZTpx*ZTpx-ZTpy*ZTpy-ZTpz*ZTpz));
      }
    }


    for(size_t x=0; x<GenDau_pt->size(); x++){
      for(size_t y=0; y<GenDau_pt->size(); y++){

        if(abs(GenDau_pdgId->at(x))==11 && GenDau_mompdgId->at(y)==23){
          LW200EleZdauDR->Fill(deltaR(GenDau_eta->at(x),GenDau_phi->at(x),GenDau_eta->at(y),GenDau_phi->at(y)));
        }
      }
    }

    for(size_t x=0; x<GenDau_pt->size(); x++){
      for(size_t y=0; y<GenDau_pt->size(); y++){

        if(abs(GenDau_pdgId->at(x))==11 && GenDau_mompdgId->at(y)==23 && Zindex[0]!=x && Zindex[1]!=y){
          LW200EleNSZdauDR->Fill(deltaR(GenDau_eta->at(x),GenDau_phi->at(x),GenDau_eta->at(y),GenDau_phi->at(y)));
        }
      }
    }

    if(Zbool){
      px=GenDau_px->at(Eindex)+GenDau_px->at(Zindex[0])+GenDau_px->at(Zindex[1]);
      py=GenDau_py->at(Eindex)+GenDau_py->at(Zindex[0])+GenDau_py->at(Zindex[1]);
      pz=GenDau_pz->at(Eindex)+GenDau_pz->at(Zindex[0])+GenDau_pz->at(Zindex[1]);
      LW200EleSZdauPT->Fill(sqrt(px*px+py*py+pz*pz));
    }

    for(size_t x=0; x<GenDau_pt->size(); x++){
      for(size_t y=0; y<GenDau_pt->size(); y++){
        for(size_t z=y+1; z<GenDau_pt->size(); z++){
          if(GenDau_pdgId->at(x)==11 && GenDau_mompdgId->at(y)==23 && GenDau_mompdgId->at(z)){
            px=GenDau_px->at(x)+GenDau_px->at(y)+GenDau_px->at(z);
            py=GenDau_py->at(x)+GenDau_py->at(y)+GenDau_py->at(z);
            pz=GenDau_pz->at(x)+GenDau_pz->at(y)+GenDau_pz->at(z);
            LW200EleZdauPT->Fill(sqrt(px*px+py*py+pz*pz));
          }
        }
      }
    }
    ///////////////////////////////secvec displacement direction///////////////////
    float Vx=0,Vy=0,Vz=0;
    float Px=0,Py=0,Pz=0;
    float Ppoint=0;

    vector<pair <float,size_t> > EleJetDRTemp;
    vector<pair <float,size_t> > EleJetInvMass;

    ElePtTemp.clear();
    JetPtTemp.clear();
    EleJetDRTemp.clear();
    EleJetInvMass.clear();

    for (size_t i = 0; i < electron_pt->size(); i++) {ElePtTemp.push_back(make_pair(electron_pt->at(i),i));}
    sort(ElePtTemp.begin(),ElePtTemp.end());

    if(corr_jet_pt->size()>4 && ElePtTemp.size()>1 && ElePtTemp.back().first>40 && ElePtTemp.end()[-2].first>25){
      ElePtTemp.clear();
      JetPtTemp.clear();
      EleJetDRTemp.clear();
      EleJetInvMass.clear();

      for(size_t x=0; x<corr_jet_pt->size(); x++ ){JetPtTemp.push_back(make_pair(corr_jet_pt->at(x),x));}
      sort(JetPtTemp.begin(), JetPtTemp.end());

      for (size_t i = 0; i < electron_pt->size(); i++) {
        if(i==ElePtTemp.back().second || i==ElePtTemp.end()[-2].second){
          for(size_t x=0; x<corr_jet_pt->size(); x++){
            if(x==JetPtTemp.back().second||x==JetPtTemp.end()[-2].second||x==JetPtTemp.end()[-3].second||x==JetPtTemp.end()[-4].second){
              EleJetDRTemp.push_back(make_pair(deltaR(jet_eta->at(x),jet_phi->at(x),electron_eta->at(i),electron_phi->at(i)), x));
              float Etemp=electron_e->at(i) + jet_e->at(x);
              float Pxtemp=electron_px->at(i)+ jet_px->at(x);
              float Pytemp=electron_py->at(i)+ jet_py->at(x);
              float Pztemp=electron_pz->at(i)+ jet_pz->at(x);
              EleJetInvMass.push_back(make_pair(sqrt(Etemp*Etemp-Pxtemp*Pxtemp-Pytemp*Pytemp-Pztemp*Pztemp),x));
            }
          }
          sort(EleJetDRTemp.begin(),EleJetDRTemp.end());
          sort(EleJetInvMass.begin(),EleJetInvMass.end());

          for(size_t y=0; y<secvec_posx->size(); y++){
            if (secvec_eleTag->at(y)==i){
              Vx=secvec_posx->at(y)-PV_x->at(0);
              Vy=secvec_posy->at(y)-PV_y->at(0);
              Vz=secvec_posz->at(y)-PV_z->at(0);
              Px=electron_px->at(i)+jet_px->at(EleJetDRTemp.front().second)+jet_px->at(EleJetDRTemp.at(1).second);
              Py=electron_py->at(i)+jet_py->at(EleJetDRTemp.front().second)+jet_py->at(EleJetDRTemp.at(1).second);
              Pz=electron_pz->at(i)+jet_pz->at(EleJetDRTemp.front().second)+jet_pz->at(EleJetDRTemp.at(1).second);
              Ppoint= Px*Vx+Py*Vy+Pz*Vz;

              LW200EleDijet_Ppoint->Fill(Ppoint);
              if(Ppoint>0)LW200EleDijet_PpointS->Fill(1);
              else if(Ppoint<0) LW200EleDijet_PpointS->Fill(-1);

              Vx=secvec_posx->at(y)-PV_x->at(0);
              Vy=secvec_posy->at(y)-PV_y->at(0);
              Vz=secvec_posz->at(y)-PV_z->at(0);
              Px=electron_px->at(i)+jet_px->at(EleJetInvMass.front().second)+jet_px->at(EleJetInvMass.at(1).second);
              Py=electron_py->at(i)+jet_py->at(EleJetInvMass.front().second)+jet_py->at(EleJetInvMass.at(1).second);
              Pz=electron_pz->at(i)+jet_pz->at(EleJetInvMass.front().second)+jet_pz->at(EleJetInvMass.at(1).second);
              Ppoint= Px*Vx+Py*Vy+Pz*Vz;

              LW200EleJetInvM_Ppoint->Fill(Ppoint);
              if(Ppoint>0)LW200EleJetInvM_PpointS->Fill(1);
              else if(Ppoint<0) LW200EleJetInvM_PpointS->Fill(-1);

            }

          }
        }

      }
    }


    ///////////////New Secvecdisplacement///////

    for(size_t x=0; x<secvec_posx->size(); x++){
      if(secvec_eleTag->at(x)!=-1){
        Vx=secvec_posx->at(x)-PV_x->at(0);
        Vy=secvec_posy->at(x)-PV_y->at(0);
        Vz=secvec_posz->at(x)-PV_z->at(0);
        Ppoint= secvec_px->at(x)*Vx+secvec_py->at(x)*Vy+secvec_pz->at(x)*Vz;
        LW200SecVec_Ppoint->Fill(Ppoint);
        if(Ppoint>0)LW200SecVec_PpointS->Fill(1);
        else if(Ppoint<0) LW200SecVec_PpointS->Fill(-1);
      }
    }

    float pvx,pvy,pvz,ppx,ppy,ppz;
    for(size_t x=0; x<GenPart_pt->size(); x++){
      if(GenPart_pdgId->at(x)==556){
        pvx=GenPart_vx->at(x);
        ppx=GenPart_px->at(x);
        pvy=GenPart_vy->at(x);
        ppy=GenPart_py->at(x);
        pvz=GenPart_vz->at(x);
        ppz=GenPart_pz->at(x);
      }
    }
    for(size_t x=0; x<GenPart_pt->size(); x++){
      if(GenPart_pdgId->at(x)==23 && GenPart_mompdgId->at(x)==556){
        Vx=GenPart_vx->at(x)-pvx;
        Vy=GenPart_vy->at(x)-pvy;
        Vz=GenPart_vz->at(x)-pvz;
        Ppoint=ppx*Vx+ppy*Vy+ppz*Vz;
        LW200GenSecVec_Ppoint->Fill(Ppoint);
        if(Ppoint>0)LW200GenSecVec_PpointS->Fill(1);
        else if(Ppoint<0) LW200GenSecVec_PpointS->Fill(-1);
      }
    }

    if(jet_pt->size()>=4){

      JetPtTemp.clear();

      for(size_t x=0; x<corr_jet_pt->size(); x++ ){JetPtTemp.push_back(make_pair(corr_jet_pt->at(x),x));}
      sort(JetPtTemp.begin(), JetPtTemp.end());

      vector<pair<float,size_t>> GenDauPtTemp;
      GenDauPtTemp.clear();
      for(size_t x=0; x<GenDau_pt->size(); x++){
        if(GenDau_mompdgId->at(x)==23) GenDauPtTemp.push_back(make_pair(GenDau_pt->at(x),x));
      }
      sort(GenDauPtTemp.begin(), GenDauPtTemp.end());

      for(size_t x=0; x<GenDau_pt->size(); x++){
        if(GenDau_mompdgId->at(x)==23){
          bool IsMatchFlag=false;
          bool IsBFlag=false;
          bool IsSBFlag=false;
          bool Is3Flag=false;
          bool Is4Flag=false;

          for(size_t y=0; y<jet_pt->size(); y++){
            if(genjet_DRscore->at(y)<0.5 && genjet_pt->at(y)==GenDau_pt->at(x)){

              IsMatchFlag=true;

              if(y==JetPtTemp.back().second) IsBFlag=true;

              if(y==JetPtTemp.end()[-2].second) IsSBFlag=true;

              if(y==JetPtTemp.end()[-3].second) Is3Flag=true;

              if(y==JetPtTemp.end()[-4].second) Is4Flag=true;

            }
          }

          if(IsMatchFlag) LW200Zdau_GenjetMatch->Fill(1);
          else LW200Zdau_GenjetMatch->Fill(0);

          if(IsBFlag) LW200Zdau_BjetMatch->Fill(1);
          else LW200Zdau_BjetMatch->Fill(0);

          if(IsSBFlag) LW200Zdau_SBjetMatch->Fill(1);
          else LW200Zdau_SBjetMatch->Fill(0);

          if(Is3Flag) LW200Zdau_3jetMatch->Fill(1);
          else LW200Zdau_3jetMatch->Fill(0);

          if(Is4Flag) LW200Zdau_4jetMatch->Fill(1);
          else LW200Zdau_4jetMatch->Fill(0);

          if(x==GenDauPtTemp.back().second){

            IsMatchFlag=false;
            IsBFlag=false;
            IsSBFlag=false;
            Is3Flag=false;
            Is4Flag=false;

            for(size_t y=0; y<jet_pt->size(); y++){
              if(genjet_DRscore->at(y)<0.5 && genjet_pt->at(y)==GenDau_pt->at(x)){
                IsMatchFlag=true;

                if(y==JetPtTemp.back().second) IsBFlag=true;

                if(y==JetPtTemp.end()[-2].second) IsSBFlag=true;

                if(y==JetPtTemp.end()[-3].second) Is3Flag=true;

                if(y==JetPtTemp.end()[-4].second) Is4Flag=true;

              }
            }

            if(IsMatchFlag) LW200BZdau_GenjetMatch->Fill(1);
            else LW200BZdau_GenjetMatch->Fill(0);

            if(IsBFlag) LW200BZdau_BjetMatch->Fill(1);
            else LW200BZdau_BjetMatch->Fill(0);

            if(IsSBFlag) LW200BZdau_SBjetMatch->Fill(1);
            else LW200BZdau_SBjetMatch->Fill(0);

            if(Is3Flag) LW200BZdau_3jetMatch->Fill(1);
            else LW200BZdau_3jetMatch->Fill(0);

            if(Is4Flag) LW200BZdau_4jetMatch->Fill(1);
            else LW200BZdau_4jetMatch->Fill(0);

          }
        }
      }
    }


    if(electron_e->size()>=4){
      ElePtTemp.clear();
      for(size_t y=0; y<electron_e->size(); y++){ElePtTemp.push_back(make_pair(electron_pt->at(y),y));}
      sort(ElePtTemp.begin(),ElePtTemp.end());

      vector<pair<float,size_t>> GenDauPtTemp;
      GenDauPtTemp.clear();
      for(size_t x=0; x<GenDau_pt->size(); x++){
        if(abs(GenDau_pdgId->at(x))==11 && abs(GenDau_mompdgId->at(x))==556) GenDauPtTemp.push_back(make_pair(GenDau_pt->at(x),x));
      }
      sort(GenDauPtTemp.begin(), GenDauPtTemp.end());

      for(size_t x=0; x<GenDau_pt->size(); x++){
        if(abs(GenDau_pdgId->at(x))==11 && abs(GenDau_mompdgId->at(x))==556){

          bool IsMatchFlag=false;
          bool IsBFlag=false;
          bool IsSBFlag=false;
          bool Is3Flag=false;
          bool Is4Flag=false;

          for(size_t y=0; y<electron_e->size(); y++){
            if(genelec_DRscore->at(y)<0.1 && genelec_pt->at(y)==GenDau_pt->at(x)){
              IsMatchFlag=true;

              if(y==ElePtTemp.back().second) IsBFlag=true;

              if(y==ElePtTemp.end()[-2].second) IsSBFlag=true;

            }
          }

          if(IsMatchFlag) LW200Elec_GenElecMatch->Fill(1);
          else LW200Elec_GenElecMatch->Fill(0);

          if(IsBFlag) LW200Elec_BElecMatch->Fill(1);
          else LW200Elec_BElecMatch->Fill(0);

          if(IsSBFlag) LW200Elec_SBElecMatch->Fill(1);
          else LW200Elec_SBElecMatch->Fill(0);

          if(x==GenDauPtTemp.back().second){
            IsMatchFlag=false;
            IsBFlag=false;
            IsSBFlag=false;

            for(size_t y=0; y<electron_pt->size(); y++){
              if(genelec_DRscore->at(y)<0.1 && genelec_pt->at(y)==GenDau_pt->at(x)){
                IsMatchFlag=true;

                if(y==ElePtTemp.back().second) IsBFlag=true;

                if(y==ElePtTemp.end()[-2].second) IsSBFlag=true;

              }
            }

            if(IsMatchFlag) LW200BElec_GenElecMatch->Fill(1);
            else LW200BElec_GenElecMatch->Fill(0);

            if(IsBFlag) LW200BElec_BElecMatch->Fill(1);
            else LW200BElec_BElecMatch->Fill(0);

            if(IsSBFlag) LW200BElec_SBElecMatch->Fill(1);
            else LW200BElec_SBElecMatch->Fill(0);

          }

          if(x==GenDauPtTemp.end()[-2].second){
            IsMatchFlag=false;
            IsBFlag=false;
            IsSBFlag=false;
            Is3Flag=false;
            Is4Flag=false;

            for(size_t y=0; y<electron_pt->size(); y++){
              if(genelec_DRscore->at(y)<0.1 && genelec_pt->at(y)==GenDau_pt->at(x)){
                IsMatchFlag=true;

                if(y==ElePtTemp.back().second) IsBFlag=true;

                if(y==ElePtTemp.end()[-2].second) IsSBFlag=true;

                if(y==ElePtTemp.end()[-3].second) Is3Flag=true;

                if(y==ElePtTemp.end()[-4].second) Is4Flag=true;

              }
            }

            if(IsMatchFlag) LW200SBElec_GenElecMatch->Fill(1);
            else LW200SBElec_GenElecMatch->Fill(0);

            if(IsBFlag) LW200SBElec_BElecMatch->Fill(1);
            else LW200SBElec_BElecMatch->Fill(0);

            if(IsSBFlag) LW200SBElec_SBElecMatch->Fill(1);
            else LW200SBElec_SBElecMatch->Fill(0);

            if(Is3Flag) LW200SBElec_3ElecMatch->Fill(1);
            else LW200SBElec_3ElecMatch->Fill(0);

            if(Is4Flag) LW200SBElec_4ElecMatch->Fill(1);
            else LW200SBElec_4ElecMatch->Fill(0);

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
  LW200RecoZdauInvmass->Write();
  LW200RecoZdauEleInvmass->Write();

  LW200SecVec_Ppoint->Write();
  LW200SecVec_PpointS->Write();
  LW200EleDijet_Ppoint->Write();
  LW200EleDijet_PpointS->Write();
  LW200EleJetInvM_Ppoint->Write();
  LW200EleJetInvM_PpointS->Write();
  LW200GenSecVec_PpointS->Write();
  LW200GenSecVec_Ppoint->Write();

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


  hfile->Close();


  return 0;

}
