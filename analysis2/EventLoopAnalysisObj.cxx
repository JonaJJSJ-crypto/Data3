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
// g++ -std=c++11 -g -O3 -Wall -Wextra -o EventLoopAnalysisObj EventLoopAnalysisObj.cxx $(root-config --cflags --libs)
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

using namespace std;


/*
 * Base path to local filesystem or to EOS containing the datasets
 */
//const std::string samplesBasePath = "root://eospublic.cern.ch//eos/opendata/cms/upload/od-workshop/ws2021/";
const std::string samplesBasePath = "Datos/";


//book example histograms for specific variables
//copy them in the constructor if you add more
const int nhists = 3;

//Histograms for signal region
/*TH1F* dataRunB_npv = new TH1F("dataRunB_npv","Number of primary vertices",25,5,30);

TH1F* dataRunC_npv  = new TH1F("dataRunC_npv","Number of primary vertices",25,5,30);

TH1F* ZLL_npv = new TH1F("ZLL_npv","Number of primary vertices",25,5,30);

TH1F* TT_npv = new TH1F("TT_npv","Number of primary vertices",25,5,30);

TH1F* W3J_npv = new TH1F("W3J_npv","Number of primary vertices",25,5,30);

TH1F* W2J_npv = new TH1F("W2J_npv","Number of primary vertices",25,5,30);

TH1F* W1J_npv = new TH1F("W1J_npv","Number of primary vertices",25,5,30);

TH1F* ttZ_npv = new TH1F("ttZ_npv","Number of primary vertices",25,5,30);

TH1F* WW_npv = new TH1F("WW_npv","Number of primary vertices",25,5,30);

TH1F* WZ_npv = new TH1F("WZ_npv","Number of primary vertices",25,5,30);*/

TH1F* LW200_npv = new TH1F("LW200_npv","Number of primary vertices",25,5,30);

/*TH1F* LW300_npv = new TH1F("LW300_npv","Number of primary vertices",25,5,30);

TH1F* LW400_npv = new TH1F("LW400_npv","Number of primary vertices",25,5,30);

TH1F* LW500_npv = new TH1F("LW500_npv","Number of primary vertices",25,5,30);

TH1F* dataRunB_JetMass = new TH1F("dataRunB_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* dataRunC_JetMass  = new TH1F("dataRunC_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* ZLL_JetMass = new TH1F("ZLL_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* TT_JetMass = new TH1F("TT_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* W3J_JetMass = new TH1F("W3J_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* W2J_JetMass = new TH1F("W2J_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* W1J_JetMass = new TH1F("W1J_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* ttZ_JetMass = new TH1F("ttZ_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* WW_JetMass = new TH1F("WW_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* WZ_JetMass = new TH1F("WZ_JetMass","Invariant mass from DiJets",800,0,400);*/

TH1F* LW200_JetMass = new TH1F("LW200_JetMass","Invariant mass from DiJets",800,0,400);

/*TH1F* LW300_JetMass = new TH1F("LW300_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* LW400_JetMass = new TH1F("LW400_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* LW500_JetMass = new TH1F("LW500_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* dataRunB_LWMass = new TH1F("dataRunB_LWMass","Invariant mass from LW",800,0,400);

TH1F* dataRunC_LWMass  = new TH1F("dataRunC_LWMass","Invariant mass from LW",800,0,400);

TH1F* ZLL_LWMass = new TH1F("ZLL_LWMass","Invariant mass from LW",800,0,400);

TH1F* TT_LWMass = new TH1F("TT_LWMass","Invariant mass from LW",800,0,400);

TH1F* W3J_LWMass = new TH1F("W3J_LWMass","Invariant mass from LW",800,0,400);

TH1F* W2J_LWMass = new TH1F("W2J_LWMass","Invariant mass from LW",800,0,400);

TH1F* W1J_LWMass = new TH1F("W1J_LWMass","Invariant mass from LW",800,0,400);

TH1F* ttZ_LWMass = new TH1F("ttZ_LWMass","Invariant mass from LW",800,0,400);

TH1F* WW_LWMass = new TH1F("WW_LWMass","Invariant mass from LW",800,0,400);

TH1F* WZ_LWMass = new TH1F("WZ_LWMass","Invariant mass from LW",800,0,400);*/

TH1F* LW200_LWMass = new TH1F("LW200_LWMass","Invariant mass from LW",800,0,400);

/*TH1F* LW300_LWMass = new TH1F("LW300_LWMass","Invariant mass from LW",800,0,400);

TH1F* LW400_LWMass = new TH1F("LW400_LWMass","Invariant mass from LW",800,0,400);

TH1F* LW500_LWMass = new TH1F("LW500_LWMass","Invariant mass from LW",800,0,400);*/


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
  vector<float>   *jet_phi;
  vector<float>   *electron_e;
  vector<float>   *electron_pt;
  vector<float>   *electron_pz;
  vector<float>   *electron_px;
  vector<float>   *electron_py;
  vector<float>   *trigobj_e;
  vector<float>   *trigobj_pt;
  vector<float>   *trigobj_pz;
  vector<float>   *trigobj_px;
  vector<float>   *trigobj_py;
  Float_t         met_pt;
  Float_t         met_phi;

  // List of example branches
  TBranch        *b_run;   //!
  TBranch        *b_luminosityBlock;   //!
  TBranch        *b_event;   //!
  TBranch        *b_PV_npvs;   //!
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
  TBranch        *b_electron_e;
  TBranch        *b_electron_pt;
  TBranch        *b_electron_pz;
  TBranch        *b_electron_px;
  TBranch        *b_electron_py;
  TBranch        *b_trigobj_e;
  TBranch        *b_trigobj_pt;
  TBranch        *b_trigobj_pz;
  TBranch        *b_trigobj_px;
  TBranch        *b_trigobj_py;

  EventLoopAnalysisTemplate(TString filename, TString labeltag, Float_t theweight);
  virtual ~EventLoopAnalysisTemplate();
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  void analysis();
  bool MinimalSelection();

};



EventLoopAnalysisTemplate::EventLoopAnalysisTemplate(TString thefile, TString thelabel, Float_t sampleweight) : fChain(0)
{
  //Prepare some info for the object:
  filename = thefile;
  labeltag = thelabel;
  theweight = sampleweight;


  //Load histograms for signal region
  /*hists[0] = dataRunB_npv;
  hists[1] = dataRunC_npv;
  hists[2] = ZLL_npv;
  hists[3] = TT_npv;
  hists[4] = W3J_npv;
  hists[5] = W2J_npv;
  hists[6] = W1J_npv;*/
  hists[0] = LW200_npv;
/*  hists[7] = dataRunB_JetMass;
  hists[8] = dataRunC_JetMass;
  hists[9] = ZLL_JetMass;
  hists[10] = TT_JetMass;
  hists[11] = W3J_JetMass;
  hists[12] = W2J_JetMass;
  hists[13] = W1J_JetMass;*/
  hists[1] = LW200_JetMass;
/*  hists[14] = dataRunB_LWMass;
  hists[15] = dataRunC_LWMass;
  hists[16] = ZLL_LWMass;
  hists[17] = TT_LWMass;
  hists[18] = W3J_LWMass;
  hists[19] = W2J_LWMass;
  hists[20] = W1J_LWMass;*/
  hists[2] = LW200_LWMass;
  /*hists[24] = WW_npv;
  hists[25] = WZ_npv;
  hists[26] = ttZ_npv;
  hists[27] = WW_JetMass;
  hists[28] = WZ_JetMass;
  hists[29] = ttZ_JetMass;
  hists[30] = WW_LWMass;
  hists[31] = WZ_LWMass;
  hists[32] = ttZ_LWMass;
  hists[33] = LW300_LWMass;
  hists[34] = LW400_LWMass;
  hists[35] = LW500_LWMass;
  hists[36] = LW300_JetMass;
  hists[37] = LW400_JetMass;
  hists[38] = LW500_JetMass;
  hists[39] = LW300_npv;
  hists[40] = LW400_npv;
  hists[41] = LW500_npv;*/


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
   electron_e = 0;
   electron_pt = 0;
   electron_px = 0;
   electron_py = 0;
   electron_pz = 0;
   trigobj_e = 0;
   trigobj_pt = 0;
   trigobj_px = 0;
   trigobj_py = 0;
   trigobj_pz = 0;

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
   fChain->SetBranchAddress("triggermap",&triggermap,&b_triggermap);
   fChain->SetBranchAddress("muon_pt", &muon_pt, &b_muon_pt);
   fChain->SetBranchAddress("muon_eta", &muon_eta, &b_muon_eta);
   fChain->SetBranchAddress("muon_phi", &muon_phi, &b_muon_phi);
   fChain->SetBranchAddress("muon_ch", &muon_ch, &b_muon_ch);
   fChain->SetBranchAddress("muon_tightid", &muon_tightid, &b_muon_tightid);
   fChain->SetBranchAddress("muon_pfreliso03all", &muon_pfreliso03all, &b_muon_pfreliso03all);
   fChain->SetBranchAddress("muon_mass", &muon_mass, &b_muon_mass);
   fChain->SetBranchAddress("tau_pt", &tau_pt, &b_tau_pt);
   fChain->SetBranchAddress("tau_eta", &tau_eta, &b_tau_eta);
   fChain->SetBranchAddress("tau_phi", &tau_phi, &b_tau_phi);
   fChain->SetBranchAddress("tau_ch", &tau_ch, &b_tau_ch);
   fChain->SetBranchAddress("tau_iddecaymode", &tau_iddecaymode, &b_tau_iddecaymode);
   fChain->SetBranchAddress("tau_idisotight", &tau_idisotight, &b_tau_idisotight);
   fChain->SetBranchAddress("tau_idantieletight", &tau_idantieletight, &b_tau_idantieletight);
   fChain->SetBranchAddress("tau_idantimutight", &tau_idantimutight, &b_tau_idantimutight);
   fChain->SetBranchAddress("tau_reliso_all", &tau_reliso_all, &b_tau_reliso_all);
   fChain->SetBranchAddress("tau_mass", &tau_mass, &b_tau_mass);
   fChain->SetBranchAddress("met_pt", &met_pt, &b_met_pt);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("jet_pt",&jet_pt,&b_jet_pt);
   fChain->SetBranchAddress("corr_jet_pt",&corr_jet_pt,&b_corr_jet_pt);
   fChain->SetBranchAddress("jet_px",&jet_px,&b_jet_px);
   fChain->SetBranchAddress("jet_py",&jet_py,&b_jet_py);
   fChain->SetBranchAddress("jet_pz",&jet_pz,&b_jet_pz);
   fChain->SetBranchAddress("jet_phi",&jet_phi,&b_jet_phi);
   fChain->SetBranchAddress("jet_e",&jet_e,&b_jet_e);
   fChain->SetBranchAddress("electron_px",&electron_px,&b_electron_px);
   fChain->SetBranchAddress("electron_py",&electron_py,&b_electron_py);
   fChain->SetBranchAddress("electron_pz",&electron_pz,&b_electron_pz);
   fChain->SetBranchAddress("electron_e",&electron_e,&b_electron_e);
   fChain->SetBranchAddress("trigobj_px",&trigobj_px,&b_trigobj_px);
   fChain->SetBranchAddress("trigobj_py",&trigobj_py,&b_trigobj_py);
   fChain->SetBranchAddress("trigobj_pz",&trigobj_pz,&b_trigobj_pz);
   fChain->SetBranchAddress("trigobj_e",&trigobj_e,&b_trigobj_e);

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
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    analysis();

  }


}


//-----------------------------------------------------------------
void EventLoopAnalysisTemplate::analysis()
{
//-----------------------------------------------------------------

  //cout<<"analysis() execution"<<endl;

  //minimal selection including trigger requirement
  if (!MinimalSelection()) return;
  //counter_ms++;

  /////Identify electron as Trig OBJ
  std::vector<bool> TobjisFound;
  tobj.clear()
  for (size_t y=0; y<trigobj_e->size(); y++){
    float saveDR=100;
    int saveQ=false;
    for (size_t x=0; x<electron_e->size(); x++){
      DRet=deltaR(electron_eta->at(x),electron_phi->at(x),trigobj_eta->at(y),trigobj_phi->at(y));
      if(DRet<saveDR){
         saveDR=DRet;
         saveQ=trk_isHQ;
      }
    }
    if (saveDR<0.1) TobjisFound.push_back(true);
    else TobjisFound.push_back(false);
  }

  //fill histograms for signal region
  Int_t histsize = sizeof(hists)/sizeof(hists[0]);
  for (Int_t j=0;j<histsize;++j){
    TString histname = TString(hists[j]->GetName());
    TString thelabel = histname(0,histname.First("_"));
    TString thevar = histname(histname.First("_")+1,histname.Sizeof());

    if (thelabel == labeltag){

      //primary vertices
      if(thevar == "npv"){
	       hists[j]->Fill(PV_npvs,theweight);
      }

      //JetMass
      if(thevar == "JetMass"){
        ////////Jet Inv Mass ///////////////////
        float px,py,pz,e,m;
        //correctedJetMass
        //float corr_pt;
        for(size_t i=0; i < jet_e->size(); i++){
          for(size_t k=0; k < jet_e->size(); k++){
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
      if(thevar == "LWMass"){
        ////////Jet Inv Mass ///////////////////
        float px,py,pz,e,m;
        //correctedJetMass
        //float corr_pt;
        for(size_t i=0; i < jet_e->size(); i++){
          for(size_t k=0; k < jet_e->size(); k++){
            for(size_t l=0; l < trigobj_e->size(); l++){
              px=0,py=0,pz=0,e=0,m=0;
              if(i!=k){
                if(TobjisFound->at(k)){
                  px=cos(jet_phi->at(i))*corr_jet_pt->at(i) + cos(jet_phi->at(k))*corr_jet_pt->at(k) + electron_px->at(l);
                  py=sin(jet_phi->at(i))*corr_jet_pt->at(i) + sin(jet_phi->at(k))*corr_jet_pt->at(k) + electron_py->at(l);
                  float corr1=corr_jet_pt->at(i)/jet_pt->at(i);
                  float corr2=corr_jet_pt->at(k)/jet_pt->at(k);
                  pz=jet_pz->at(i)*corr1+jet_pz->at(k)*corr2+trigobj_pz->at(l);
                  e=jet_e->at(i)*corr1+jet_e->at(k)*corr2+trigobj_e->at(l);
                  m=sqrt( e*e - px*px - py*py - pz*pz );

                  hists[j]->Fill(m,theweight);
                }
              }
            }
          }
        }
      }
    }
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

  /*const float W1J_w =  6381.2 / 29784800.0 * integratedLuminosity;
  const float W2J_w =  2039.8 / 30693853.0 * integratedLuminosity;
  const float W3J_w =  612.5 / 15241144.0 * integratedLuminosity;
  const float TT_w = 225.2 / 6423106.0 * integratedLuminosity;
  const float ZLL_w = 3503.7 / 30458871.0 * integratedLuminosity;*/
  const float LW200_w = 0.0059 / 150000 * integratedLuminosity;
  /*const float LW300_w = 0.00096 / 150000 * integratedLuminosity;
  const float LW400_w = 0.00023 / 150000 * integratedLuminosity;
  const float LW500_w = 0.00006 / 150000 * integratedLuminosity;
  const float WW_w = 5.824 / 1933120 * integratedLuminosity;
  const float WZ_w = 2.207 / 3215990 * integratedLuminosity;
  const float ttZ_w = 0.175 / 787495 * integratedLuminosity;
  const float dataRunB_w = 1.0;
  const float dataRunC_w = 1.0;*/


  map<string, pair<string,float> > sampleNames;
  /*sampleNames.insert(make_pair("WWJetsTo2L2Nu",make_pair("WW",WW_w)));
  sampleNames.insert(make_pair("WZJetsTo2L2Q",make_pair("WZ",WZ_w)));
  sampleNames.insert(make_pair("ttbarZ",make_pair("ttZ",ttZ_w)));
  sampleNames.insert(make_pair("W1JetsToLNu",make_pair("W1J",W1J_w)));
  sampleNames.insert(make_pair("W2JetsToLNu",make_pair("W2J",W2J_w)));
  sampleNames.insert(make_pair("W3JetsToLNu",make_pair("W3J",W3J_w)));
  sampleNames.insert(make_pair("TTbar",make_pair("TT",TT_w)));
  sampleNames.insert(make_pair("DYJetsToLL",make_pair("ZLL",ZLL_w)));*/
  sampleNames.insert(make_pair("myoutput_Data",make_pair("LW200",LW200_w)));
  /*sampleNames.insert(make_pair("LWSM300DnR",make_pair("LW300",LW300_w)));
  sampleNames.insert(make_pair("LWSM400DnR",make_pair("LW400",LW400_w)));
  sampleNames.insert(make_pair("LWSM500DnR",make_pair("LW500",LW500_w)));
  sampleNames.insert(make_pair("Run2012B_DoublePhoton",make_pair("dataRunB",dataRunB_w)));
  sampleNames.insert(make_pair("Run2012C_DoublePhoton",make_pair("dataRunC",dataRunC_w)));*/




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

  TFile* hfile = new TFile("OBJ/histogramsObj.root","RECREATE");

  //Save signal region histos
  /*dataRunB_npv->Write();
  dataRunC_npv->Write();
  ZLL_npv->Write();
  TT_npv->Write();
  W3J_npv->Write();
  W2J_npv->Write();
  W1J_npv->Write();
  WW_npv->Write();
  WZ_npv->Write();
  ttZ_npv->Write();*/
  LW200_npv->Write();
  /*LW300_npv->Write();
  LW400_npv->Write();
  LW500_npv->Write();
  dataRunB_JetMass->Write();
  dataRunC_JetMass->Write();
  ZLL_JetMass->Write();
  TT_JetMass->Write();
  W3J_JetMass->Write();
  W2J_JetMass->Write();
  W1J_JetMass->Write();
  WW_JetMass->Write();
  WZ_JetMass->Write();
  ttZ_JetMass->Write();*/
  LW200_JetMass->Write();
  /*LW300_JetMass->Write();
  LW400_JetMass->Write();
  LW500_JetMass->Write();
  dataRunB_LWMass->Write();
  dataRunC_LWMass->Write();
  ZLL_LWMass->Write();
  TT_LWMass->Write();
  W3J_LWMass->Write();
  W2J_LWMass->Write();
  W1J_LWMass->Write();
  WW_LWMass->Write();
  WZ_LWMass->Write();
  ttZ_LWMass->Write();*/
  LW200_LWMass->Write();
  /*LW300_LWMass->Write();
  LW400_LWMass->Write();
  LW500_LWMass->Write();*/

  hfile->Close();


  return 0;

}
