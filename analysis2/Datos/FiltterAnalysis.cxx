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
// g++ -std=c++11 -g -O3 -Wall -Wextra -o FiltterAnalysis FiltterAnalysis.cxx $(root-config --cflags --libs)
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
TH1F* DYelectron_num = new TH1F("DYelectron_num","number of events with elec/phot pt>20GeV",10,0,10);
TH1F* DYelectron_pt = new TH1F("DYelectron_pt","Electrons pt for missing trigg",100,0,200);
TH1F* DYelectron_eta = new TH1F("DYelectron_eta","Electrons eta for missing trigg",100,-5,5);
TH1F* DYphoton_num = new TH1F("Photon_number","Number of photons pt>17GeV",10,0,10);
TH1F* DYphoton_pt = new TH1F("Photon_pt","Photon transverse momentum pt>17GeV",100,0,200);
TH1F* DYphoton_eta = new TH1F("Photon_eta","Photon pseudorapidity pt>17GeV",100,-5,5);
TH1F* DYSGenele_num = new TH1F("DYSGenele_num","Number of signal gen-electrons per event (pt<15GeV)",3,0,3);
TH1F* DYSGenele_pt = new TH1F("DYSGenele_pt","Signal Genele pt ",100,0,200);
TH1F* DYSGenele_eta = new TH1F("DYSGenele_eta","Signal Genele eta",100,-5,5);
TH1F* DYGenphot_num = new TH1F("Genphot_num","Number of gen-photon pt>17GeV",50,0,100);
TH1F* DYGenphot_pt = new TH1F("Genphot_pt","Gen-photon transverse momentumpt pt>17GeV",100,0,200);
TH1F* DYGenphot_eta = new TH1F("Genphot_eta","Gen-photon pseudorapidity pt>17GeV",100,-5,5);
TH1F* DYGenelec_num = new TH1F("DYGenelec_num","number of gen-electrons",50,0,100);
TH1F* DYGenelec_pt = new TH1F("DYGenelec_pt","Genelec pt",100,0,200);
TH1F* DYGenelec_eta = new TH1F("DYGenelec_eta","Genelec eta",100,-5,5);
TH1F* DYGenZdau_pt = new TH1F("DYGenZdau_pt","GensZdau pt for missing trigg",100,0,200);
TH1F* DYGenZdau_eta = new TH1F("DYGenZdau_eta","GensZdau eta for missing trigg",100,-5,5);
TH1F* DYHelec_num = new TH1F("High_electron_number","Number of Second most energetic electron pt>15GeV",3,0,3);
TH1F* DYHelec_pt = new TH1F("High_electron_pt","Second most energetic electron transverse momentum pt>15GeV",100,0,200);
TH1F* DYHelec_eta = new TH1F("High_electron_eta","Second most energetic electron pseudorapidity pt>15GeV",100,-5,5);
TH1F* DYTrack_num = new TH1F("Tracks_number","Number of tracks pt>15GeV",50,0,100);
TH1F* DYTrack_pt = new TH1F("Tracks_pt","Tracks transverse momentum pt>15GeV",100,0,200);
TH1F* DYTrack_eta = new TH1F("Tracks_eta","Tracks pseudorapidity pt>15GeV",100,-5,5);
TH1F* DYHtrk_num = new TH1F("High_track_number","Number of Second most energetic track pt>15GeV",3,0,3);
TH1F* DYHtrk_pt = new TH1F("High_track_pt","Second most energetic track transverse momentum pt>15GeV",100,0,200);
TH1F* DYHtrk_eta = new TH1F("High_track_eta","Second most energetic track pseudorapidity pt>15GeV",100,-5,5);
TH1F* DYjet_mass = new TH1F("DiJet_Invmass","Invariant mass from DiJets ",800,0,400);
TH1F* DYLW_mass = new TH1F("LW_Invmass","Invariant mass from LW",800,0,400);
TH1F* DYCorrjet_mass = new TH1F("DiCorrJet_Invmass","Invariant mass from corrected DiJets ",800,0,400);
TH1F* DYSjet_mass = new TH1F("SDiJet_Invmass","Invariant mass from Signal DiJets ",800,0,400);
TH1F* DYGenjet_mass = new TH1F("RecoDiEle_Invmass","Invariant mass from Gen DiJets ",800,0,400);
TH1F* DYRecoEle_mass = new TH1F("RecoDiEle_Invmass","Invariant mass from Reco DiElec",800,0,400);
TH1F* DYjet_massfilter = new TH1F("DiJet_Invmass_filter","Events with DiJets invariant mass ",2,0,2);
TH1F* DYSjet_massfilter = new TH1F("SDiJet_Invmass_filter","Events with Signal DiJets invariant mass ",2,0,2);
TH1F* DYGenjet_massfilter = new TH1F("DiGenJet_Invmass_filter","Events with Gen DiJets invariant mass ",2,0,2);
//TH1F* DYEleBsecvec = new TH1F("Electron best match","Best matched secondary vertex displacement",100,0,0.1);
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
  vector<float>   *genjet_e;
  vector<float>   *genjet_pt;
  vector<float>   *genjet_pz;
  vector<float>   *genjet_px;
  vector<float>   *genjet_py;
  vector<float>   *genjet_DRscore;
  vector<float>   *photon_pt;
  vector<float>   *photon_eta;
  vector<float>   *GenPart_pt;
  vector<float>   *GenPart_eta;
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
  TBranch        *b_genjet_e;
  TBranch        *b_genjet_pt;
  TBranch        *b_genjet_pz;
  TBranch        *b_genjet_px;
  TBranch        *b_genjet_py;
  TBranch        *b_genjet_DRscore;
  TBranch        *b_photon_pt;
  TBranch        *b_photon_eta;
  TBranch        *b_GenPart_pt;
  TBranch        *b_GenPart_eta;
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


  EventLoopAnalysisTemplate(TString filename, TString labeltag, Float_t theweight);
  virtual ~EventLoopAnalysisTemplate();
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  void analysis();
  Float_t MinimalSelection(Int_t entry);

};



EventLoopAnalysisTemplate::EventLoopAnalysisTemplate(TString thefile, TString thelabel, Float_t sampleweight) : fChain(0)
{
  //Prepare some info for the object:
  filename = thefile;
  labeltag = thelabel;
  theweight = sampleweight;

  hists[0]=DYelectron_num;
  hists[1]=DYelectron_pt;
  hists[2]=DYelectron_eta;
  hists[3]=DYphoton_num;
  hists[4]=DYphoton_pt;
  hists[5]=DYphoton_eta;
  hists[6]=DYSGenele_num;
  hists[7]=DYSGenele_pt;
  hists[8]=DYSGenele_eta;
  hists[9]=DYGenphot_num;
  hists[10]=DYGenphot_pt;
  hists[11]=DYGenphot_eta;
  hists[12]=DYGenZdau_pt;
  hists[13]=DYGenZdau_eta;
  hists[14]=DYGenelec_num;
  hists[15]=DYGenelec_pt;
  hists[16]=DYGenelec_eta;

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
   //Make friends so we can have access to friends variables
   //we may not use all of the available information
   //it is just an example
   tree->AddFriend(tevents);
   tree->AddFriend(telectrons);
   tree->AddFriend(tphotons);
   tree->AddFriend(tGenPart);
   tree->AddFriend(tTrack);
   tree->AddFriend(tJet);
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
   genjet_e=0;
   genjet_pt=0;
   genjet_pz=0;
   genjet_px=0;
   genjet_py=0;
   genjet_DRscore=0;
   track_pt=0;
   track_eta=0;
   track_chi2=0;
   photon_pt=0;
   photon_eta=0;
   GenPart_pt=0;
   GenPart_eta=0;
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
   fChain->SetBranchAddress("GenPart_eta",&GenPart_eta,&b_GenPart_eta);
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
   fChain->SetBranchAddress("genjet_e",&genjet_e,&b_genjet_e);
   fChain->SetBranchAddress("genjet_pt",&genjet_pt,&b_genjet_pt);
   fChain->SetBranchAddress("genjet_pz",&genjet_pz,&b_genjet_pz);
   fChain->SetBranchAddress("genjet_px",&genjet_px,&b_genjet_px);
   fChain->SetBranchAddress("genjet_py",&genjet_py,&b_genjet_py);
   fChain->SetBranchAddress("genjet_DRscore",&genjet_DRscore,&b_genjet_DRscore);
   /*fChain->SetBranchAddress("electron_Bsecvec",&electron_Bsecvec,&b_electron_Bsecvec);
   fChain->SetBranchAddress("secvec_deltaR",&secvec_deltaR,&b_secvec_deltaR);
   fChain->SetBranchAddress("secvec_disp",&secvec_disp,&b_secvec_disp);*/

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
      DYHelec_pt->Fill(vect[vect.size()-1].first);
      DYHelec_eta->Fill(vect[vect.size()-1].second);
    }*/
    if(vect.size()>=2){
      if(vect[vect.size()-2].first>Minpt){
        DYHelec_pt->Fill(vect[vect.size()-2].first);
        DYHelec_eta->Fill(vect[vect.size()-2].second);
        Hcount++;
      }
    }
  }
  DYHelec_num->Fill(Hcount);
  vect.clear();
  Hcount=0;

  //Filling tracks
  int ntrk=0;
  if(track_pt->size()!=0){
    for (size_t i = 0; i < track_pt->size(); i++) {
      if (track_pt->at(i)>Minpt && track_chi2->at(i)<1) {
        ntrk++;
        DYTrack_pt->Fill(track_pt->at(i));
        DYTrack_eta->Fill(track_eta->at(i));
      }
      vect.push_back(make_pair(track_pt->at(i),track_eta->at(i)));
    }
    sort(vect.begin(),vect.end());
    /*if(vect[vect.size()-1].first>Minpt){
      Hcount++;
      DYHtrk_pt->Fill(vect[vect.size()-1].first);
      DYHtrk_eta->Fill(vect[vect.size()-1].second);
    }*/
    if(vect.size()>=2){
      if(vect[vect.size()-2].first>Minpt){
        DYHtrk_pt->Fill(vect[vect.size()-2].first);
        DYHtrk_eta->Fill(vect[vect.size()-2].second);
        Hcount++;
      }
    }
  }
  DYTrack_num->Fill(ntrk);
  DYHtrk_num->Fill(Hcount);
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
    if (abs(GenDau_mompdgId->at(i)) == 23) {
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
      if (abs(GenDau_mompdgId->at(i)) == 23) {
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
    for(size_t j=0; j < jet_mass->size(); j++){
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
          DYjet_mass->Fill(m);
        }
      }
    }
  }
  if(zcount>=1) DYjet_massfilter->Fill(1);
  else DYjet_massfilter->Fill(0);
//correctedJetMass
  float corr_pt;
  for(size_t i=0; i < jet_mass->size(); i++){
    for(size_t j=0; j < jet_mass->size(); j++){
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
          DYCorrjet_mass->Fill(m);
        }
      }
    }
  }

  zcount=0;
  for(size_t i=0; i < genjet_pt->size(); i++){
    for(size_t j=0; j < genjet_pt->size(); j++){
      px=0,py=0,pz=0,e=0,m=0;
      if(i!=j){
        if( genjet_DRscore->at(i)<0.1 && genjet_DRscore->at(j)<0.1){
          //cout<<mass1+genjet_mass->at(j)<<endl;
          px=cos(jet_phi->at(i))*corr_jet_pt->at(i) + cos(jet_phi->at(j))*corr_jet_pt->at(j);
          py=sin(jet_phi->at(i))*corr_jet_pt->at(i) + sin(jet_phi->at(j))*corr_jet_pt->at(j);
          float corr1=corr_jet_pt->at(i)/jet_pt->at(i);
          float corr2=corr_jet_pt->at(j)/jet_pt->at(j);
          pz=jet_pz->at(i)*corr1+jet_pz->at(j)*corr2;
          e=jet_e->at(i)*corr1+jet_e->at(j)*corr2;
          m=sqrt( e*e - px*px - py*py - pz*pz );

          for(size_t k=0; k < electron_pt->size(); k++){
            px=px+electron_px->at(k);
            py=py+electron_py->at(k);
            pz=pz+electron_pz->at(k);
            Mlw=sqrt( e*e - px*px - py*py - pz*pz );
            DYLW_mass->Fill(Mlw);
          }

          if(m>MinZm && m<MaxZm){
            zcount++;
            DYSjet_mass->Fill(m);
          }
        }
      }
    }
  }
  if(zcount>=1) DYSjet_massfilter->Fill(1);
  else DYSjet_massfilter->Fill(0);
/////////////////////////Generated Inva Mass/////////////////////////////////
  zcount=0;
  for (size_t i = 0; i < GenDau_pt->size(); i++) {
    for (size_t j = 0; j < GenDau_pt->size(); j++) {
      if(GenDau_mompdgId->at(i)==23 && GenDau_mompdgId->at(j)==23){
        if(i!=j){
          if(GenDau_pdgId->at(i)==11 && GenDau_pdgId->at(j)==-11){
            //zcount++;
            float e1=sqrt(GenDau_mass->at(i)*GenDau_mass->at(i)+GenDau_pt->at(i)*GenDau_pt->at(i)+GenDau_pz->at(i)*GenDau_pz->at(i));
            float e2=sqrt(GenDau_mass->at(j)*GenDau_mass->at(j)+GenDau_pt->at(j)*GenDau_pt->at(j)+GenDau_pz->at(j)*GenDau_pz->at(j));
            px=GenDau_px->at(i)+GenDau_px->at(j);
            py=GenDau_py->at(i)+GenDau_py->at(j);
            pz=GenDau_pz->at(i)+GenDau_pz->at(j);
            e=e1+e2;
            m=sqrt( e*e - px*px - py*py - pz*pz );
            DYGenjet_mass->Fill(m);

            for (size_t k = 0; k < electron_pt->size(); k++) {
              for (size_t l = 0; l < electron_pt->size(); l++) {
                if( genelec_DRscore->at(k)<0.1 && genelec_pt->at(k)==GenDau_pt->at(i) ){
                  if( genelec_DRscore->at(l)<0.1 && genelec_pt->at(l)==GenDau_pt->at(j) ){
                    px=electron_px->at(k)+electron_px->at(l);
                    py=electron_py->at(k)+electron_py->at(l);
                    pz=electron_pz->at(k)+electron_pz->at(l);
                    e =electron_e->at(k) +electron_e->at(l);
                    m=sqrt( e*e - px*px - py*py - pz*pz );
                    DYRecoEle_mass->Fill(m);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if(zcount>=1) DYGenjet_massfilter->Fill(1);
  else DYGenjet_massfilter->Fill(0);
  //////////////////////Reco Electron Inv Mass/////////////////////////////





  if(!isFill)cout<<"Aqui"<<'\n';



}//------analysis()

/*
 * Perform a selection on the minimal requirements of an event
 */
//-----------------------------------------------------------------
Float_t EventLoopAnalysisTemplate::MinimalSelection(Int_t entry)
{
//-----------------------------------------------------------------

 //cout<<"Applying minimal selection"<<endl;
  Float_t isTrigger = 0;

  //Check trigger and acceptance bit
  for (map<string, int>::iterator it=triggermap->begin();it!=triggermap->end();it++){
    //for (size_t i = 0; i < 6; i++) {

      if(it->first.find(triggerRequest[entry])!=string::npos){
        isTrigger = it->second;
        //if(isTrigger!=1)cout<<it->first<<"  "<<it->second<<endl;
      }
    //}

  }


  return isTrigger;

}//------MinimalSelection




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
  sampleNames.insert(make_pair("DYJetsToLL",make_pair("DY",1)));




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

  TFile* hfile = new TFile("FiltterAnalysis.root","RECREATE");

  //Save signal region histos
  DYelectron_num->Write();
  DYelectron_pt->Write();
  DYelectron_eta->Write();
  DYphoton_num->Write();
  DYphoton_pt->Write();
  DYphoton_eta->Write();
  DYSGenele_num->Write();
  DYSGenele_pt->Write();
  DYSGenele_eta->Write();
  DYGenphot_num->Write();
  DYGenphot_pt->Write();
  DYGenphot_eta->Write();
  DYGenZdau_pt->Write();
  DYGenZdau_eta->Write();
  DYGenelec_num->Write();
  DYGenelec_pt->Write();
  DYGenelec_eta->Write();
  DYHelec_pt->Write();
  DYHelec_eta->Write();
  DYHelec_num->Write();
  DYTrack_pt->Write();
  DYTrack_eta->Write();
  DYTrack_num->Write();
  DYHtrk_pt->Write();
  DYHtrk_eta->Write();
  DYHtrk_num->Write();
  DYjet_mass->Write();
  DYCorrjet_mass->Write();
  DYSjet_mass->Write();
  DYGenjet_mass->Write();
  DYjet_massfilter->Write();
  DYSjet_massfilter->Write();
  DYGenjet_massfilter->Write();
  DYLW_mass->Write();
  DYRecoEle_mass->Write();

  hfile->Close();


  return 0;

}
